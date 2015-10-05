//////////////////////////////////////
// bst_clear_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bstnode_define_declare.h"

#include "bst_new_release_node.h"
#include "iterator_bst_posorder_template.c"

#ifndef bst_clean_init_itr
#define bst_clean_init_itr(ITR_PTR, ROOT_PTR)	init_bst_posorder_iterator_unsafe(ITR_PTR, ROOT_PTR, null)
#endif//bst_clean_init_itr

#ifndef bst_clean_itr_increase
#define bst_clean_itr_increase increase_bst_posorder_iterator_unsafe
#endif//bst_clean_itr_increase

#ifndef bst_clean_begin_itr
#define bst_clean_begin_itr  get_bst_begin_posorder_iterator_unsafe
#endif//bst_clean_begin_itr

#ifndef clear_bst
// 清除
static SR_INLINE result_t bst_clean(bst_node_allocator_t*	PARAM_IN alloc_ptr,
	tree_node_ptr* PARAM_INOUT root_dec_ptrptr)
{
	bst_posorder_iterator_t  itr;
	bst_posorder_iterator_t* itr_ptr;
	result_t                 status;
	if (null == alloc_ptr ||
		null == alloc_ptr->release_node)
	{
		return STATUS_INVALID_PARAMS;
	}
	if (null == root_dec_ptrptr || null == *root_dec_ptrptr)
	{
		return STATUS_OK;
	}

	status = STATUS_OK;

	bst_clean_init_itr(&itr, root_dec_ptrptr);
	itr_ptr = bst_clean_begin_itr(&itr);

	while (itr_ptr)
	{
		tree_node_ptr del_node_ptr;
		del_node_ptr = get_pos_itr_this(itr_ptr->itr);
		itr_ptr      = bst_clean_itr_increase(itr_ptr);

		status = alloc_ptr->release_node(&(alloc_ptr->m_alloc_inst), del_node_ptr);
		if (STATUS_OK != status)
		{
			break;
		}
	}

	return status;
}

#define clear_bst  bst_clean
#endif//clear_bst
