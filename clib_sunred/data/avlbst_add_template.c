//////////////////////////////////////
// avlbst_add_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////
#include "avlbstnode_define_declare.h"
#include "bst_add_template.c"
#include "avlbst_init_template.c"

#ifndef insert_avlbst_node_base
#define insert_avlbst_node_base insert_bst_node
#endif//insert_avlbst_node_base

#ifndef update_avlbst_insert_rotate_unsafe

static SR_INLINE result_t __avl_update_insert_rotate
   (tree_node_ptr* PARAM_INOUT root_node_ptrptr,
	tree_node_ptr  PARAM_INOUT begin_node_ptr)
{

	result_t         status;
	nsize__t         height;
	AVLTREE_ROTATE_t rotate_type;
	nsize__t         balance_value;
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

		rotate_type = avlbst_single_rotate_unsafe(
			calculate_avlbst_balance_value(tmp_root_node_ptr),
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

	update_avlbst_height_unsafe(begin_node_ptr);

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

		if (height == get_tree_height(parent_node_ptr))
		{
			// 某节点更新节点后的高度与原来的高度一样，
			// 则该节点向上方向的节点均不需进行翻转操作
			// 退出翻转流程
			BREAK_LOOP(status, STATUS_OK);
		}

		parent_parent_node_ptr = get_tree_parent (parent_node_ptr);
		begin_node_ptr         = parent_node_ptr;

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
			else if (get_avlbst_right_unsafe(parent_parent_node_ptr) == parent_node_ptr)
			{
				reference_node_ptr_ptr = 
					get_tree_right_ref(parent_parent_node_ptr);

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
	return status;
}
#define update_avlbst_insert_rotate_unsafe __avl_update_insert_rotate
#endif  //update_avlbst_insert_rotate_unsafe


#ifndef insert_avlbst_node
// AVL 树插入节点
static SR_INLINE result_t avlbst_add_node(tree_node_ptr* PARAM_INOUT root_node_ptrptr,
	tree_node_ptr  PARAM_INOUT add_node_ptr,
	cmpfunc_type               compareto,
	tree_node_ptr* PARAM_OUT   added_node_ptrptr)
{
	result_t         status;

	DO_ONE_LOOP_BEGIN

	//bst_node_ptr tmp_root_ptr;
	//bst_node_ptr tmp_add_node_ptr;
	//bst_node_ptr tmp_added_node_ptr;

	if (null == add_node_ptr || null == root_node_ptrptr)
	{
		BREAK_LOOP(status, STATUS_INVALID_PARAMS);
	}
	
	status = insert_avlbst_node_base(root_node_ptrptr,
		add_node_ptr, compareto, added_node_ptrptr);

	BREAK_LOOP_CONDITION(STATUS_OK != status);

	update_avlbst_height_unsafe(add_node_ptr);
	status = update_avlbst_insert_rotate_unsafe(root_node_ptrptr, add_node_ptr);

	DO_ONE_LOOP_END

	return status;
}

#define insert_avlbst_node avlbst_add_node
#endif //insert_avlbst_node





