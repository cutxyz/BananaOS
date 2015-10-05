//////////////////////////////////////
// bst_copy_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bst.h"
#include "bst_init_template.c"
#include "bst_clean_template.c"
#include "iterator_bst_inorder_template.c"

#ifndef bst_copy_init_itr
#define bst_copy_init_itr(ITR_PTR, ROOT_PTR)	init_bst_const_inorder_iterator_unsafe(ITR_PTR, ROOT_PTR, null)
#endif//bst_copy_init_itr

#ifndef bst_copy_itr_increase
#define bst_copy_itr_increase increase_bst_inorder_iterator_unsafe
#endif//bst_copy_itr_increase

#ifndef bst_copy_begin_itr
#define bst_copy_begin_itr  get_bst_begin_inorder_iterator_unsafe
#endif//bst_copy_begin_itr

#ifndef copy_bst
//复制（复制树的数据，但结构不一样）
static SR_INLINE result_t copy_bstree(
	bstree_header_t* PARAM_INOUT dec_tree_ptr,
	const bstree_header_t* PARAM_IN src_tree_ptr)
{
	bst_inorder_iterator_t  itr;
	bst_inorder_iterator_t* itr_ptr;
	result_t                status;

	if (null == dec_tree_ptr || 
		null == dec_tree_ptr->m_alloc.new_node ||
		null == dec_tree_ptr->add ||
		null == dec_tree_ptr->m_cmp ||
		null == dec_tree_ptr->m_alloc.release_node)
	{
		return STATUS_INVALID_PARAMS;
	}
	if (null != get_bst_root(dec_tree_ptr))
	{
		return STATUS_UNIQUE;
	}
	if (null == get_bst_root(src_tree_ptr))
	{
		return STATUS_OK;
	}

	status = STATUS_OK;

	bst_copy_init_itr(&itr, (const tree_node_ptr*)covnode_ptrptr(&(src_tree_ptr->m_root_node_ptr)));
	
	itr_ptr = bst_copy_begin_itr(&itr);
	while (itr_ptr)
	{
		const bst_node_ptr be_copy_node_ptr; 
		bst_node_ptr       new_node_ptr;

		be_copy_node_ptr = recovnode_ptr(get_in_itr_this(itr_ptr->const_itr));
		new_node_ptr     = recovnode_ptr(alloc_new_node(dec_tree_ptr->m_alloc, be_copy_node_ptr));

		if (null == new_node_ptr)
		{
			status = STATUS_MEM_LOW;
			break;
		}
		status = dec_tree_ptr->add(&(dec_tree_ptr->m_root_node_ptr), 
			new_node_ptr, 
			dec_tree_ptr->m_cmp, 
			null);

		if (STATUS_OK != status)
		{
			break;
		}
		itr_ptr = bst_copy_itr_increase(itr_ptr);
	}

	if (STATUS_OK != status)
	{
		clear_bst(&(dec_tree_ptr->m_alloc), &(dec_tree_ptr->m_root_node_ptr));
	}
	return status;
}

#define copy_bst copy_bstree
#endif//copy_bst
