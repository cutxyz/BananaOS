//////////////////////////////////////
// bst_find_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bstnode_define_declare.h"

#ifndef cmpfunc_type
#define cmpfunc_type bst_node_cmp_func
// 搜索二叉树结点比较
typedef int(*bst_node_cmp_func)(const void* PARAM_OUT first,
	const void* PARAM_IN second);
#endif //cmpfunc_type 

#ifndef find_bst_node
// 查找准确节点
static SR_INLINE tree_node_ptr bst_find_node(tree_node_ptr PARAM_IN root_ptr,
	const tree_node_ptr PARAM_IN key_ptr,
	cmpfunc_type compareto)
{
	tree_node_ptr traval_ptr;

	RETURN_RESULT(
		(null == key_ptr ||
		null == compareto), null);

	traval_ptr = root_ptr;

	while (traval_ptr)
	{
		int cmp_result = compareto(key_ptr, traval_ptr);
		if (cmp_result < 0)
		{
			traval_ptr = get_tree_left(traval_ptr);
		}
		else if (cmp_result > 0)
		{
			traval_ptr = get_tree_right(traval_ptr);
		}
		else
		{
			break;
		}
	}
	return traval_ptr;
}
#define find_bst_node bst_find_node
#endif//find_bst_node

#ifndef find_bst_node_const
static SR_INLINE const tree_node_ptr bst_find_node_const(const tree_node_ptr PARAM_IN root_ptr,
	const tree_node_ptr PARAM_IN key_ptr,
	cmpfunc_type compareto)
{
	return bst_find_node((tree_node_ptr)root_ptr, key_ptr, compareto);
}
#define find_bst_node_const	 bst_find_node_const
#endif//find_bst_node_const

#ifndef find_bst_near_node
// 查找邻近节点
static SR_INLINE tree_node_ptr bst_find_near_node(tree_node_ptr PARAM_IN root_ptr,
	const tree_node_ptr PARAM_IN key_ptr,
	cmpfunc_type compareto,
	int* PARAM_OUT last_cmp_result_ptr)
{
	tree_node_ptr traval_ptr;
	tree_node_ptr near_ptr;
	int cmp_result;
	
	if (null == key_ptr || null == compareto)
	{
		if (last_cmp_result_ptr)
		{
			*last_cmp_result_ptr = 0;
		}
		return null;
	}

	traval_ptr = root_ptr;
	near_ptr   = null;
	cmp_result = 0;

	while (traval_ptr)
	{
		cmp_result = compareto(key_ptr, traval_ptr);
		near_ptr = traval_ptr;

		if (cmp_result < 0)
		{
			traval_ptr = get_tree_left(traval_ptr);
		}
		else if (cmp_result > 0)
		{
			traval_ptr = get_tree_right(traval_ptr);
		}
		else
		{
			break;
		}
	}

	if (last_cmp_result_ptr)
	{
		*last_cmp_result_ptr = cmp_result;
	}
	return near_ptr;
}
#define find_bst_near_node bst_find_near_node
#endif//find_bst_near_node

#ifndef find_bst_near_node_const
static SR_INLINE const tree_node_ptr bst_find_near_node_const(const tree_node_ptr PARAM_IN root_ptr,
	const tree_node_ptr PARAM_IN key_ptr,
	cmpfunc_type compareto,
	int* PARAM_OUT last_cmp_result_ptr)
{
	return bst_find_near_node((tree_node_ptr)root_ptr, key_ptr, compareto,last_cmp_result_ptr);
}
#define find_bst_near_node_const bst_find_near_node_const
#endif//find_bst_near_node_const
//#endif //bst_find_funcs


