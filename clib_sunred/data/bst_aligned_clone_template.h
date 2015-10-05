//////////////////////////////////////
// bst_clone_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "bst_init_template.h"
#include "bst_clear_template.h"


#ifndef bst_clone_funs
#define bst_clone_funs

// 克隆	（复制树的结构以及数据）
static SR_INLINE result_t aligned_clone_bst(bst_node_allocator_t*	PARAM_INOUT alloc_ptr,
	               bst_node_ptr* PARAM_INOUT root_dec_ptrptr,
				   const bst_node_ptr PARAM_IN other_root_ptr,
				   reg_t aligned_mask)
{
	result_t           status;
	bst_node_ptr       temp_dec_node_ptr;
	const bst_node_ptr temp_src_node_ptr;
	bst_node_ptr       new_node_ptr;


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


	new_node_ptr = alloc_ptr->new_node
		(&(alloc_ptr->m_alloc_inst), other_root_ptr);

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
		if (null == get_bst_left_unsafe(temp_dec_node_ptr))
		{
			if (null != get_bst_left_const_unsafe(temp_src_node_ptr))
			{
				new_node_ptr = alloc_ptr->new_node
					(&(alloc_ptr->m_alloc_inst), 
					get_bst_left_const_unsafe(temp_src_node_ptr));

				BREAK_LOOP_CONDITION_SETS(!new_node_ptr, status, STATUS_MEM_LOW);

				init_bst_node_unsafe(new_node_ptr, null, null, temp_dec_node_ptr);

				set_bst_left_unsafe(temp_dec_node_ptr, new_node_ptr);
				temp_dec_node_ptr = new_node_ptr;

				temp_src_node_ptr = get_bst_left_const_unsafe(temp_src_node_ptr);
				continue;
			}
		}

		if (null == get_bst_left_unsafe(temp_dec_node_ptr))
		{
			if (null != get_bst_right_const_unsafe(temp_src_node_ptr))
			{
				new_node_ptr = alloc_ptr->new_node
					(&(alloc_ptr->m_alloc_inst),
					get_bst_right_const_unsafe(temp_src_node_ptr));

				BREAK_LOOP_CONDITION_SETS(!new_node_ptr, status, STATUS_MEM_LOW);

				init_bst_node_unsafe(new_node_ptr, null, null, temp_dec_node_ptr);

				set_bst_right_unsafe(temp_dec_node_ptr, new_node_ptr);
				temp_dec_node_ptr = new_node_ptr;

				temp_src_node_ptr = get_bst_right_const_unsafe(temp_src_node_ptr);
				continue;
			}
		}

		temp_dec_node_ptr = get_aligned_bst_parent_unsafe(temp_dec_node_ptr, aligned_mask);
		temp_src_node_ptr = get_aligned_bst_parent_const_unsafe(temp_src_node_ptr, aligned_mask);
	} while (temp_dec_node_ptr);

	if (STATUS_OK > status)
	{
		clear_bst(alloc_ptr, root_dec_ptrptr);
	}
	return status;
}

#endif//bst_clone_funs