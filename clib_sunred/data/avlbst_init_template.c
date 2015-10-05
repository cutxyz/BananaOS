//////////////////////////////////////
// avlbst_init_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "avlbstnode_define_declare.h"
#include "bst_init_template.c"

//////////////////////////////////////////////////////////////////////////
#ifndef  calculate_avlbst_height
static SR_INLINE nsize__t calculate_avl_height
(const tree_node_ptr PARAM_IN left_node_ptr,
 const tree_node_ptr PARAM_IN right_node_ptr)
{
	nsize__t left_height  = get_tree_height(left_node_ptr);
	nsize__t right_height = get_tree_height(right_node_ptr);

	if (left_height > right_height)
	{
		return (left_height + 1);
	}
	else
	{
		return (right_height + 1);
	}
}
#define calculate_avlbst_height calculate_avl_height
#endif //calculate_avlbst_height

#ifndef  calculate_avlbst_height_byself
static SR_INLINE nsize__t calculate_avl_height_byself(const tree_node_ptr PARAM_IN node_ptr)
{
	nsize__t height_value = -1;
	if (node_ptr)
	{
		height_value = calculate_avlbst_height
			((const tree_node_ptr)get_tree_const_left(node_ptr),
			(const tree_node_ptr)get_tree_const_right(node_ptr));
			//((const tree_node_ptr)get_tree_const_left (&node_ptr->m_bst_header),
			// (const tree_node_ptr)get_tree_const_right(&node_ptr->m_bst_header));
	}
	return height_value;
}
#define calculate_avlbst_height_byself calculate_avl_height_byself
#endif //calculate_avlbst_height_byself

#ifndef  calculate_avlbst_balance_value
static SR_INLINE nsize__t calculate_avl_balance_value
(const tree_node_ptr PARAM_IN node_ptr)
{
	nsize__t balance_value = 0;
	if (node_ptr)
	{
		balance_value = get_tree_height(get_tree_const_left(node_ptr))
			          - get_tree_height(get_tree_const_right(node_ptr));
	}
	return balance_value;
}
#define calculate_avlbst_balance_value calculate_avl_balance_value
#endif //calculate_avlbst_balance_value


#ifndef  update_avlbst_height_unsafe 
static SR_INLINE void __update_avl_height(tree_node_ptr PARAM_IN node_ptr)
{
	nsize__t height_value = calculate_avlbst_height_byself(node_ptr);
	set_tree_height(node_ptr, height_value);
}
#define update_avlbst_height_unsafe __update_avl_height
#endif //update_avlbst_height_unsafe

#ifndef avlbst_rr_rotate_unsafe
static SR_INLINE tree_node_ptr __avl_rr_rotate(tree_node_ptr PARAM_INOUT node_ptr)
{
	tree_node_ptr tmp_right_node_ptr;
	tree_node_ptr rotate_node_ptr = get_tree_right(node_ptr);
	set_tree_right(node_ptr, get_tree_left(rotate_node_ptr));
	set_tree_left(rotate_node_ptr, node_ptr);


	tmp_right_node_ptr = get_tree_right(node_ptr);
	if (tmp_right_node_ptr)
	{
		set_tree_parent(tmp_right_node_ptr, node_ptr);
	}

	set_tree_parent(rotate_node_ptr, get_tree_parent(node_ptr));
	set_tree_parent(node_ptr, rotate_node_ptr);

	update_avlbst_height_unsafe(node_ptr);
	update_avlbst_height_unsafe(rotate_node_ptr);

	return rotate_node_ptr;
}
#define avlbst_rr_rotate_unsafe __avl_rr_rotate
#endif //avlbst_rr_rotate_unsafe

#ifndef avlbst_ll_rotate_unsafe
static SR_INLINE tree_node_ptr __avl_ll_rotate(tree_node_ptr PARAM_INOUT node_ptr)
{
	tree_node_ptr tmp_left_node_ptr;

	tree_node_ptr rotate_node_ptr = get_tree_left(node_ptr);

	set_tree_left(node_ptr, get_tree_right(rotate_node_ptr));
	set_tree_right(rotate_node_ptr, node_ptr);

	tmp_left_node_ptr = get_tree_left(node_ptr);
	if (tmp_left_node_ptr)
	{
		set_tree_parent(tmp_left_node_ptr, node_ptr);
	}

	set_tree_parent(rotate_node_ptr, get_tree_parent(node_ptr));
	set_tree_parent(node_ptr, rotate_node_ptr);

	update_avlbst_height_unsafe(node_ptr);
	update_avlbst_height_unsafe(rotate_node_ptr);

	return rotate_node_ptr;
}
#define avlbst_ll_rotate_unsafe __avl_ll_rotate
#endif //avlbst_ll_rotate_unsafe

#ifndef avlbst_lr_rotate_unsafe
static SR_INLINE tree_node_ptr __avl_lr_rotate(tree_node_ptr PARAM_INOUT node_ptr)
{
	// LR = RR(node_ptr->letf) + LL(node_ptr)
	tree_node_ptr tmp_node_ptr = avlbst_rr_rotate_unsafe(get_tree_left(node_ptr));
	set_tree_left(node_ptr, tmp_node_ptr);
	return avlbst_ll_rotate_unsafe(node_ptr);
}
#define avlbst_lr_rotate_unsafe __avl_lr_rotate
#endif //avlbst_lr_rotate_unsafe

#ifndef avlbst_rl_rotate_unsafe
static SR_INLINE tree_node_ptr __avl_rl_rotate(tree_node_ptr PARAM_INOUT node_ptr)
{
	// RL = LL(node_ptr->right)) + RR(node_ptr)
	tree_node_ptr tmp_node_ptr = avlbst_ll_rotate_unsafe(get_tree_right(node_ptr));
	set_tree_right(node_ptr, tmp_node_ptr);
	return avlbst_rr_rotate_unsafe(node_ptr);
}
#define avlbst_rl_rotate_unsafe __avl_rl_rotate
#endif //avlbst_rl_rotate_unsafe

#ifndef avlbst_single_rotate_unsafe
static SR_INLINE AVLTREE_ROTATE_t __avl_single_rotate(nsize__t balance_value,
			tree_node_ptr  PARAM_INOUT node_ptr,
			tree_node_ptr* PARAM_INOUT parent_ref_node_ptrptr)
{
	AVLTREE_ROTATE_t rotate_type;

	DO_ONE_LOOP_BEGIN

	if (-2 < balance_value && balance_value < 2)
	{
		// 平衡值在[-1,1]区间不需要进行再平衡
		BREAK_LOOP(rotate_type, AVLTREE_NONE_ROTATE);
	}
	else
	if (2 == balance_value)
	{
		// 树左偏
		tree_node_ptr left_node_ptr;
		left_node_ptr = get_tree_left(node_ptr); 

		if (null == left_node_ptr)
		{
			//  出现该情况的时候左子树不可能为空
			BREAK_LOOP(rotate_type, AVLTREE_ROTATE_ERR);
		}
		else if (
			get_tree_height(get_tree_left (left_node_ptr)) >=
			get_tree_height(get_tree_right(left_node_ptr)))
		{	 // LL
			set_tree_parent_ref(parent_ref_node_ptrptr, 
				avlbst_ll_rotate_unsafe(node_ptr));

			BREAK_LOOP(rotate_type, AVLTREE_LL_ROTATE);
		}
		else
		{	// LR
			set_tree_parent_ref(parent_ref_node_ptrptr, 
				avlbst_lr_rotate_unsafe(node_ptr));

			BREAK_LOOP(rotate_type, AVLTREE_LR_ROTATE);
		}
	}
	else
	if (-2 == balance_value)
	{
		// 树右偏
		tree_node_ptr right_node_ptr;
		right_node_ptr = get_tree_right(node_ptr);
		if (null == right_node_ptr)
		{	 
			//  出现该情况的时候右子树不可能为空
			BREAK_LOOP(rotate_type, AVLTREE_ROTATE_ERR);
		}
		else if (
			get_tree_height( get_tree_right(right_node_ptr)) >=
			get_tree_height( get_tree_left (right_node_ptr)))
		{
			// RR
			set_tree_parent_ref(parent_ref_node_ptrptr, 
				avlbst_rr_rotate_unsafe(node_ptr));

			BREAK_LOOP(rotate_type, AVLTREE_RR_ROTATE);
		}
		else
		{
			//RL
			set_tree_parent_ref(parent_ref_node_ptrptr, 
				avlbst_rl_rotate_unsafe(node_ptr));

			BREAK_LOOP(rotate_type, AVLTREE_RL_ROTATE);
		}
	}
	else
	{
		//当平衡值不在[-2,2]的区间,该树严重失衡,不是简单翻转下就搞定的
		BREAK_LOOP(rotate_type, AVLTREE_NOT_SIMPLE_ROTATE);
	}

	DO_ONE_LOOP_END
	return rotate_type;
}
#define avlbst_single_rotate_unsafe __avl_single_rotate
#endif //avlbst_single_rotate_unsafe





