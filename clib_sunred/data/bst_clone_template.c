//////////////////////////////////////
// bst_clone_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "bstnode_define_declare.h"
#include "bst_init_template.c"
#include "bst_clean_template.c"


#ifndef clone_bst
// 克隆	（复制树的结构以及数据）
static SR_INLINE result_t __clone_bst(bst_node_allocator_t*	PARAM_INOUT alloc_ptr,
	               tree_node_ptr* PARAM_INOUT root_dec_ptrptr,
				   const tree_node_ptr PARAM_IN other_root_ptr)
{
	result_t            status;		   
	tree_node_ptr       temp_dec_node_ptr;
	const tree_node_ptr temp_src_node_ptr;
	tree_node_ptr       new_node_ptr;


	if (null == alloc_ptr ||
		null == alloc_ptr->new_node ||
		null == alloc_ptr->release_node)
	{
		return STATUS_INVALID_PARAMS;
	}
	if (null == root_dec_ptrptr  || 
		null == other_root_ptr||
		other_root_ptr == *root_dec_ptrptr)
	{
		return STATUS_OK;
	}
	if (null != *root_dec_ptrptr)
	{
		return STATUS_UNIQUE;
	}

	new_node_ptr = alloc_new_node_p(alloc_ptr, other_root_ptr);


	if (null == new_node_ptr)
	{
		return STATUS_MEM_LOW;
	}

	init_bst_node_unsafe(new_node_ptr,null, null, null);
	*root_dec_ptrptr = new_node_ptr;

	temp_dec_node_ptr = new_node_ptr;
	temp_src_node_ptr = other_root_ptr;

	status = STATUS_OK;
	do
	{
		if (null == get_tree_left(temp_dec_node_ptr))
		{
			if (null != get_tree_const_left(temp_src_node_ptr))
			{
				new_node_ptr = alloc_new_node_p
					(alloc_ptr, 
					get_tree_const_left(temp_src_node_ptr));

				BREAK_LOOP_CONDITION_SETS(!new_node_ptr, status, STATUS_MEM_LOW);

				init_bst_node_unsafe(new_node_ptr, null, null, temp_dec_node_ptr);

				set_tree_left(temp_dec_node_ptr, new_node_ptr);
				temp_dec_node_ptr = new_node_ptr;

				temp_src_node_ptr = get_tree_const_left(temp_src_node_ptr);
				continue;
			}
		}

		if (null == get_tree_left(temp_dec_node_ptr))
		{
			if (null != get_tree_const_right(temp_src_node_ptr))
			{
				new_node_ptr = alloc_new_node_p
					(alloc_ptr,
					get_tree_const_right(temp_src_node_ptr));

				BREAK_LOOP_CONDITION_SETS(!new_node_ptr, status, STATUS_MEM_LOW);

				init_bst_node_unsafe(new_node_ptr, null, null, temp_dec_node_ptr);

				set_tree_right(temp_dec_node_ptr, new_node_ptr);
				temp_dec_node_ptr = new_node_ptr;

				temp_src_node_ptr = get_tree_const_right(temp_src_node_ptr);
				continue;
			}
		}

		temp_dec_node_ptr = get_tree_parent(temp_dec_node_ptr);
		temp_src_node_ptr = get_tree_const_parent(temp_src_node_ptr);
	} while (temp_dec_node_ptr);

	if (STATUS_OK > status)
	{
		clear_bst(alloc_ptr, root_dec_ptrptr);
	}
	return status;
}

#define clone_bst __clone_bst 
#endif//clone_bst