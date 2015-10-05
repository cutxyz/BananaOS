//////////////////////////////////////
// bst_minmax_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "bstnode_define_declare.h"

#ifndef get_bst_max_node
// 获取最大节点
static SR_INLINE tree_node_ptr bst_max_node(tree_node_ptr PARAM_IN root_node_ptr)
{
	tree_node_ptr max_node_ptr = root_node_ptr;
	if (max_node_ptr)
	{
		tree_node_ptr right_node_ptr = get_tree_right(max_node_ptr);
		while (right_node_ptr)
		{
			max_node_ptr = right_node_ptr;
			right_node_ptr = get_tree_right(max_node_ptr);
		}
	}
	return max_node_ptr;
}
#define get_bst_max_node bst_max_node
#endif


#ifndef get_bst_max_node_const 

static SR_INLINE const tree_node_ptr bst_max_node_const(const tree_node_ptr PARAM_IN root_node_ptr)
{
	return bst_max_node((tree_node_ptr)root_node_ptr);
}
#define get_bst_max_node_const	bst_max_node_const

#endif//get_bst_max_node_const



#ifndef get_bst_min_node
// 获取最小节点
static SR_INLINE tree_node_ptr bst_min_node(tree_node_ptr PARAM_IN root_node_ptr)
{
	tree_node_ptr min_node_ptr = root_node_ptr;
	if (min_node_ptr)
	{
		tree_node_ptr left_node_ptr = //get_bst_left_unsafe(min_node_ptr);
			get_tree_left(min_node_ptr);
		while (left_node_ptr)
		{
			min_node_ptr = left_node_ptr;
			left_node_ptr = //get_bst_left_unsafe(min_node_ptr);
				get_tree_left(min_node_ptr);
		}
	}
	return min_node_ptr;
}
#define get_bst_min_node bst_min_node
#endif

#ifndef get_bst_min_node_const
static SR_INLINE const tree_node_ptr bst_min_node_const(const tree_node_ptr PARAM_IN root_node_ptr)
{
	return bst_min_node((tree_node_ptr)root_node_ptr);
}
#define get_bst_min_node_const bst_min_node_const
#endif//get_bst_min_node_const

#ifndef get_bst_max_node_ex
// 获取最大节点（通过特殊的null节点）
static SR_INLINE tree_node_ptr bst_max_node_with_spec_null(tree_node_ptr PARAM_IN root_node_ptr, 
	const tree_node_ptr PARAM_IN null_node_ptr)
{
	if (null == null_node_ptr)
	{
		return get_bst_max_node(root_node_ptr);
	}
	else
	{
		tree_node_ptr max_node_ptr = root_node_ptr;
		if (max_node_ptr && max_node_ptr != null_node_ptr)
		{
			tree_node_ptr right_node_ptr = get_tree_right(max_node_ptr);
			while (right_node_ptr && right_node_ptr != null_node_ptr)
			{
				max_node_ptr = right_node_ptr;
				right_node_ptr = get_tree_right(max_node_ptr);
			}
		}
		return max_node_ptr;
	}
}
#define get_bst_max_node_ex	 bst_max_node_with_spec_null
#endif//get_bst_max_node_ex

#ifndef get_bst_max_node_ex_const
static SR_INLINE const tree_node_ptr bst_max_node_with_spec_null_const(const tree_node_ptr PARAM_IN root_node_ptr,
	const tree_node_ptr PARAM_IN null_node_ptr)
{
	return bst_max_node_with_spec_null((tree_node_ptr)root_node_ptr, null_node_ptr);
}
#define get_bst_max_node_ex_const bst_max_node_with_spec_null_const
#endif//get_bst_max_node_ex_const

#ifndef get_bst_min_node_ex
// 获取最小节点（通过特殊的null节点）
static SR_INLINE tree_node_ptr bst_min_node_with_spec_null(tree_node_ptr PARAM_IN root_node_ptr,
	const tree_node_ptr PARAM_IN null_node_ptr)
{
	if (null == null_node_ptr)
	{
		return get_bst_min_node(root_node_ptr);
	}
	else
	{
		tree_node_ptr min_node_ptr = root_node_ptr;
		if (min_node_ptr && min_node_ptr != null_node_ptr)
		{
			tree_node_ptr left_node_ptr = //get_bst_left_unsafe(min_node_ptr);
				get_tree_left(min_node_ptr);
			while (left_node_ptr && left_node_ptr != null_node_ptr)
			{
				min_node_ptr = left_node_ptr;
				left_node_ptr = //get_bst_left_unsafe(min_node_ptr);
					get_tree_left(min_node_ptr);
			}
		}
		return min_node_ptr;
	}
}
#define get_bst_min_node_ex	bst_min_node_with_spec_null
#endif//get_bst_min_node_ex

#ifndef get_bst_min_node_ex_const
static SR_INLINE const tree_node_ptr bst_min_node_with_spec_null_const(const tree_node_ptr PARAM_IN root_node_ptr,
	const tree_node_ptr PARAM_IN null_node_ptr)
{
	return bst_min_node_with_spec_null((tree_node_ptr)root_node_ptr, null_node_ptr);
}
#define get_bst_min_node_ex_const  bst_min_node_with_spec_null_const
#endif//get_bst_min_node_ex_const

