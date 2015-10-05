//////////////////////////////////////
// avlbst_remove_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "avlbstnode_define_declare.h"
#include "bst_remove_template.c"
#include "avlbst_init_template.c"

#ifndef remove_avlbst_node_base
#define remove_avlbst_node_base internal_remove_bst_node_unsafe
#endif//remove_avlbst_node_base

#ifndef avlbst_remove_update_fixed_unsafe

// 删除后的翻转更新
static SR_INLINE result_t __avl_update_fixed(
	tree_node_ptr* PARAM_INOUT root_node_ptrptr,
	tree_node_ptr  PARAM_INOUT begin_node_ptr)
{
	result_t         status;
	nsize__t         height;
	AVLTREE_ROTATE_t rotate_type;
	nsize__t         balance_value;
	nsize__t         same_count;
	tree_node_ptr  tmp_root_node_ptr;
	tree_node_ptr  tmp_root_parent_node_ptr;
	tree_node_ptr  parent_node_ptr;
	tree_node_ptr  parent_parent_node_ptr;
	
	tmp_root_node_ptr        = *root_node_ptrptr;
	tmp_root_parent_node_ptr = get_tree_parent(tmp_root_node_ptr);

	// 当起始节点为根节点的处理流程
	if (tmp_root_node_ptr == begin_node_ptr)
	{
		update_avlbst_height_unsafe(begin_node_ptr);

		rotate_type = avlbst_single_rotate_unsafe
			(calculate_avlbst_balance_value(tmp_root_node_ptr), 
			tmp_root_node_ptr, 
			root_node_ptrptr);

		if (AVLTREE_ROTATE_ERR > rotate_type)
		{
			status = STATUS_OK;
		}
		else if (AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			status = STATUS_FAIL;
		}
		else
		{
			status = STATUS_ERROR_;
		}
		return status;
	}

	balance_value = calculate_avlbst_balance_value(begin_node_ptr);

	DO_ONE_LOOP_BEGIN

	if (2 == balance_value)
	{
		begin_node_ptr = get_tree_left(begin_node_ptr);
	}
	else if (-2 == balance_value)
	{
		begin_node_ptr = get_tree_right(begin_node_ptr);
	}

	update_avlbst_height_unsafe(begin_node_ptr);

	same_count = 0;
	// 从第一个节点的跟节点开始翻转
	do
	{
		tree_node_ptr* reference_node_ptr_ptr;
		parent_node_ptr = get_tree_parent(begin_node_ptr);

		//一般情况下必须达成 null == parent_node的条件，即轮寻翻转到跟节点的时候
		//才退出翻转处理流程
		if (tmp_root_parent_node_ptr == parent_node_ptr)
		{
			BREAK_LOOP(status, STATUS_OK);
		}

		// 节点与他的父节点的指针一样，证明内存已经出错
		if (begin_node_ptr == parent_node_ptr)
		{
			BREAK_LOOP(status, STATUS_MEM_ERR);
		}
		height = get_tree_height(parent_node_ptr);
		update_avlbst_height_unsafe(parent_node_ptr);
		balance_value = calculate_avlbst_balance_value(parent_node_ptr);


		// 高度一样，平衡，连续出现2次，则退出
		if (height == get_tree_height(parent_node_ptr) && 
			balance_value > -2 && balance_value <2)
		{
			++same_count;
			if (same_count > 1)
			{
				BREAK_LOOP(status, STATUS_OK);
			}
		}
		else
		{
			same_count = 0;
		}

		parent_parent_node_ptr = get_tree_parent(parent_node_ptr);
		begin_node_ptr = parent_node_ptr;

		reference_node_ptr_ptr = null;
		// 注：这利用相关节点的关联引用进行操作，在翻转过程中快速替换被关联节点对应的节点指针
		if (parent_node_ptr == tmp_root_node_ptr ||
			tmp_root_parent_node_ptr == parent_parent_node_ptr)
		{
			rotate_type = avlbst_single_rotate_unsafe
				(balance_value, parent_node_ptr, root_node_ptrptr);
		}
		else
		{
			if (get_tree_left(parent_parent_node_ptr) == parent_node_ptr)
			{
				reference_node_ptr_ptr =
					get_tree_left_ref(parent_parent_node_ptr);

				rotate_type = avlbst_single_rotate_unsafe
					(balance_value, parent_node_ptr, reference_node_ptr_ptr);

			}
			else if (get_tree_right(parent_parent_node_ptr) == parent_node_ptr)
			{
				reference_node_ptr_ptr =
					get_avlbst_right_ref_unsafe(parent_parent_node_ptr);

				rotate_type = avlbst_single_rotate_unsafe
					(balance_value, parent_node_ptr, reference_node_ptr_ptr);
			}
			else
			{
				// 父节点既不是爷节点的左儿子也不是爷节点的右儿子，肯定是出问题了
				BREAK_LOOP(status, STATUS_MEM_ERR);
			}
		}

		if (AVLTREE_ROTATE_ERR > rotate_type)
		{
			status = STATUS_OK;
			continue;
		}
		// 翻转出错，退出流程
		else if (AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			BREAK_LOOP(status, STATUS_FAIL);
		}
		else
		{
			BREAK_LOOP(status, STATUS_ERROR_);
		}

	} while (1);

	DO_ONE_LOOP_END

	return status;
}
#define avlbst_remove_update_fixed_unsafe __avl_update_fixed
#endif // avlbst_remove_update_fixed_unsafe

#ifndef remove_avlbst_node

// 移除节点
static SR_INLINE result_t avlbst_remove_node (
	tree_node_ptr* PARAM_INOUT root_node_ptrptr,
	tree_node_ptr PARAM_INOUT remove_node_ptr)
{
	result_t status;

	DO_ONE_LOOP_BEGIN

	tree_node_ptr temp_node_ptr = null;
	tree_node_ptr parent_node_ptr;
	tree_node_ptr sub_remove_node_ptr;
	tree_node_ptr sub_romove_ref_node_ptr;
	
	
	if (null == remove_node_ptr || 
		null == root_node_ptrptr)
	{
		BREAK_LOOP(status, STATUS_INVALID_PARAMS);
	}

	sub_romove_ref_node_ptr = find_bst_remove_replace_node_unsafe
		(remove_node_ptr, &sub_remove_node_ptr);

	if (sub_remove_node_ptr)
	{
		parent_node_ptr = get_tree_parent(sub_remove_node_ptr);
	}

	status = remove_avlbst_node_base(root_node_ptrptr,
		remove_node_ptr,
		sub_remove_node_ptr,
		sub_romove_ref_node_ptr);

	BREAK_LOOP_CONDITION(null == *root_node_ptrptr);
	BREAK_LOOP_CONDITION(STATUS_OK != status);

	if (sub_remove_node_ptr)
	{
		set_tree_height(sub_remove_node_ptr,
			get_tree_height(remove_node_ptr));
	}
	temp_node_ptr = sub_romove_ref_node_ptr;

	if (null == sub_romove_ref_node_ptr)
	{
		if (null != sub_remove_node_ptr)
		{
			if (remove_node_ptr != parent_node_ptr)
			{
				temp_node_ptr = parent_node_ptr;
			}
			else
			{
				temp_node_ptr = bst_to_avlbst_unsafe(sub_remove_node_ptr);
			}
		}

		if (null == temp_node_ptr)
		{
			temp_node_ptr = *root_node_ptrptr;
		}
	}
	status = avlbst_remove_update_fixed_unsafe(root_node_ptrptr, temp_node_ptr);

	DO_ONE_LOOP_END
	return status;
}

#define remove_avlbst_node avlbst_remove_node
#endif // remove_avlbst_node






