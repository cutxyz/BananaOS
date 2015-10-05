//////////////////////////////////////
// rbbst_add_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "rbbstnode_define_declare.h"
#include "rbbst_init_template.c"
#include "bst_add_template.c"

#ifndef insert_rbbst_node_base
#define insert_rbbst_node_base insert_bst_node
#endif//insert_rbbst_node_base

#ifndef update_rbbst_insert_rotate_unsafe

static SR_INLINE result_t __rbt_add_rotate_fixup (
	rbbst_node_ptr* PARAM_INOUT root_node_ptrptr,
	rbbst_node_ptr  PARAM_INOUT add_node_ptr)
{
	rbbst_node_ptr temp_node_ptr;
	bool_t         is_red_node;
	result_t       status;

	is_red_node = FALSE;

	// 根节点的颜色一定是黑的
	if (add_node_ptr == *root_node_ptrptr)
	{
		set_tree_blackcolor(add_node_ptr);
		return STATUS_OK;
	}

	status = STATUS_OK;
	while (add_node_ptr != *root_node_ptrptr)
	{
		rbbst_node_ptr parent_node_ptr;
		rbbst_node_ptr grand_parent_node_ptr;

		parent_node_ptr = get_tree_parent(add_node_ptr);
		is_red_node     = check_tree_redcolor(parent_node_ptr);

		BREAK_LOOP_CONDITION(!is_red_node);

		// 新添加的父节点为红色

		grand_parent_node_ptr = get_tree_parent(parent_node_ptr);

		if (null == grand_parent_node_ptr)
		{
			// 爷爷节点不可能为空
			BREAK_LOOP(status, STATUS_MEM_ERR);
		}

		// 当爷爷的左孩子节点为父节点的时候
		if (get_tree_left(grand_parent_node_ptr) == parent_node_ptr)
		{
			temp_node_ptr = get_tree_right(grand_parent_node_ptr);
			is_red_node   = check_tree_redcolor(temp_node_ptr);

			if (is_red_node)
			{
				// 叔叔节点红色
				// 将叔叔节点变黑
				// 父节点变黑，（解决新增节点与父节点都是红色的问题）
				// 将爷爷节点变红，当作新增节点，指针上移两代
				set_tree_blackcolor(parent_node_ptr);
				set_tree_blackcolor(temp_node_ptr);
				set_tree_redcolor  (grand_parent_node_ptr);
				add_node_ptr = grand_parent_node_ptr;
			}
			else
			{
				// 叔叔节点黑色
				if (get_tree_right(parent_node_ptr) == add_node_ptr)
				{
					// 新增节点是父节点的右孩子
					// 左旋操作
					// 然后孩子父亲互换角色
					add_node_ptr = parent_node_ptr;
					rbbst_left_rotate_unsafe(root_node_ptrptr, null, add_node_ptr);

					parent_node_ptr       = get_tree_parent(add_node_ptr);
					grand_parent_node_ptr = get_tree_parent(parent_node_ptr);
				}

				set_tree_blackcolor (parent_node_ptr);
				set_tree_redcolor   (grand_parent_node_ptr);
				rbbst_right_rotate_unsafe (root_node_ptrptr, null, grand_parent_node_ptr);
			}

		}
		// 当爷爷的右孩子节点为父节点的时候
		else if (get_tree_right(grand_parent_node_ptr) == parent_node_ptr)
		{
			temp_node_ptr = get_tree_left(grand_parent_node_ptr);
			is_red_node   = check_tree_redcolor(temp_node_ptr);

			if (is_red_node)
			{
				set_tree_blackcolor(parent_node_ptr);
				set_tree_blackcolor(temp_node_ptr);
				set_tree_redcolor  (grand_parent_node_ptr);
				add_node_ptr = grand_parent_node_ptr;
			}
			else
			{
				if (get_tree_left(parent_node_ptr) == add_node_ptr)
				{
					add_node_ptr = parent_node_ptr;
					rbbst_right_rotate_unsafe(root_node_ptrptr, null, add_node_ptr);

					parent_node_ptr       = get_tree_parent(add_node_ptr);
					grand_parent_node_ptr = get_tree_parent(parent_node_ptr);
				}
				set_tree_blackcolor (parent_node_ptr);
				set_tree_redcolor   (grand_parent_node_ptr);
				rbbst_left_rotate_unsafe (root_node_ptrptr, null, grand_parent_node_ptr);
			}
		}
		// 父节点既不是爷爷的左孩子也不是右孩子，内存出错
		else
		{
			BREAK_LOOP(status, STATUS_MEM_ERR);
		}
	}

	if (STATUS_OK == status)
	{
		set_tree_blackcolor(*root_node_ptrptr);
	}

	return status;
}
#define update_rbbst_insert_rotate_unsafe __rbt_add_rotate_fixup
#endif  //update_rbbst_insert_rotate_unsafe

#ifndef insert_rbbst_node

// 黑红树插入节点
static SR_INLINE result_t rbbst_add_node(rbbst_node_ptr* PARAM_INOUT root_node_ptrptr,
	rbbst_node_ptr  PARAM_INOUT add_node_ptr,
	cmpfunc_type                compareto,
	rbbst_node_ptr* PARAM_OUT   added_node_ptrptr)
{
	result_t       status;

	DO_ONE_LOOP_BEGIN

	if (null == add_node_ptr || null == root_node_ptrptr)
	{
		BREAK_LOOP(status, STATUS_INVALID_PARAMS);
	}

	// 插入的初始节点的颜色为红色
	set_tree_redcolor (add_node_ptr);

	status = insert_rbbst_node_base(root_node_ptrptr,
		add_node_ptr, compareto, added_node_ptrptr);


	BREAK_LOOP_CONDITION(STATUS_OK != status);

	// 平衡变换
	status = update_rbbst_insert_rotate_unsafe(root_node_ptrptr, add_node_ptr);

	DO_ONE_LOOP_END
	return status;
}

#define insert_rbbst_node rbbst_add_node
#endif //insert_rbbst_node






