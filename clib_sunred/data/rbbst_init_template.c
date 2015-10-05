//////////////////////////////////////
// rbbst_init_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "rbbstnode_define_declare.h"

#include "bst_init_template.c"


#ifndef  copy_rbbst_color_unsafe

static SR_INLINE void __copy_tree_color(
	tree_node_ptr PARAM_INOUT dec_node_ptr, 
	const tree_node_ptr PARAM_IN src_node_ptr)
{
	set_tree_color(dec_node_ptr, get_tree_color(src_node_ptr));
}
#define  copy_rbbst_color_unsafe __copy_tree_color
#endif //copy_rbbst_color_unsafe


#ifndef rbbst_left_rotate_unsafe
static SR_INLINE void __rbt_left_rotate (
	tree_node_ptr* PARAM_INOUT root_node_ptrptr,
	tree_node_ptr  PARAM_IN    sentinel_node_ptr,
	tree_node_ptr  PARAM_INOUT node_ptr)
{
	tree_node_ptr temp_node_ptr;
	tree_node_ptr tmp_letf_node_ptr;
	tree_node_ptr tmp_parent_node_ptr;

	temp_node_ptr     = get_tree_right(node_ptr);
	tmp_letf_node_ptr = get_tree_left(temp_node_ptr);
	set_tree_right(node_ptr, tmp_letf_node_ptr);

	if (tmp_letf_node_ptr != sentinel_node_ptr)
	{
		set_tree_parent(tmp_letf_node_ptr, node_ptr);
	}

	tmp_parent_node_ptr = get_tree_parent(node_ptr);
	set_tree_parent(temp_node_ptr, tmp_parent_node_ptr);

	if (node_ptr == *root_node_ptrptr)
	{
		*root_node_ptrptr = temp_node_ptr;
	}
	else
	{
		if (get_tree_left(tmp_parent_node_ptr) == node_ptr)
		{
			set_tree_left(tmp_parent_node_ptr, temp_node_ptr);
		}
		else
		{
			set_tree_right(tmp_parent_node_ptr, temp_node_ptr);
		}
	}

	set_tree_left  (temp_node_ptr, node_ptr);
	set_tree_parent(node_ptr, temp_node_ptr);
}
#define rbbst_left_rotate_unsafe __rbt_left_rotate
#endif //rbbst_left_rotate_unsafe

#ifndef rbbst_right_rotate_unsafe
static SR_INLINE void __rbt_right_rotate (
	tree_node_ptr* PARAM_INOUT root_node_ptrptr,
	tree_node_ptr  PARAM_IN    sentinel_node_ptr,
	tree_node_ptr  PARAM_INOUT node_ptr)
{
	tree_node_ptr temp_node_ptr;
	tree_node_ptr temp_right_node_ptr;
	tree_node_ptr tmp_parent_node_ptr;

	temp_node_ptr       = get_tree_left(node_ptr);
	temp_right_node_ptr = get_tree_right(temp_node_ptr);
	set_tree_right(node_ptr, temp_right_node_ptr);

	if (temp_right_node_ptr != sentinel_node_ptr)
	{
		set_tree_parent(temp_right_node_ptr, node_ptr);
	}

	tmp_parent_node_ptr = get_tree_parent(node_ptr);
	set_tree_parent(temp_node_ptr, tmp_parent_node_ptr);

	if (node_ptr == *root_node_ptrptr)
	{
		*root_node_ptrptr = temp_node_ptr;
	}
	else
	{
		if (get_tree_right(tmp_parent_node_ptr) == node_ptr)
		{
			set_tree_right(tmp_parent_node_ptr, temp_node_ptr);
		}
		else
		{
			set_tree_left(tmp_parent_node_ptr, temp_node_ptr);
		}
	}

	set_tree_right(temp_node_ptr, node_ptr);
	set_tree_parent(node_ptr, temp_node_ptr);
}
#define rbbst_right_rotate_unsafe __rbt_right_rotate
#endif //rbbst_right_rotate_unsafe

