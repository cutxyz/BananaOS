//////////////////////////////////////
// inorder_bst_iterator_template.c
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bstnode_define_declare.h"
#include "iterator_bst_itr.h"
#include "bst_minmax_template.c"

#undef  get_in_itr_this
#define get_in_itr_this(X)     get_bst_itr_this_traits(tree_node_ptr,X)

#undef  get_in_itr_root_ref
#define get_in_itr_root_ref(X) get_bst_itr_root_ref_traits(tree_node_ptr,X)

#ifndef init_bst_inorder_iterator_unsafe
// 初始化迭代器
static SR_FORCE_INLINE void __bst_init_inorder_iterator (
	bst_inorder_iterator_t* PARAM_OUT itrptr,
	tree_node_ptr* PARAM_IN root_ref,
	tree_node_ptr PARAM_IN this_node_ptr)
{
	itrptr->itr.m_tree_root_ref = root_ref;
	itrptr->itr.m_this_node_ptr = this_node_ptr;
}
#define init_bst_inorder_iterator_unsafe 	     __bst_init_inorder_iterator
#endif//init_bst_inorder_iterator_unsafe


#ifndef init_bst_const_inorder_iterator_unsafe
static SR_FORCE_INLINE void __bst_init_const_inorder_iterator(
	bst_inorder_iterator_t* PARAM_OUT itrptr,
	const tree_node_ptr* PARAM_IN root_ref,
	const tree_node_ptr PARAM_IN this_node_ptr)
{
	itrptr->const_itr.m_tree_root_ref = root_ref;
	itrptr->const_itr.m_this_node_ptr = this_node_ptr;
}
#define init_bst_const_inorder_iterator_unsafe	 __bst_init_const_inorder_iterator
#endif//init_bst_const_inorder_iterator_unsafe

#ifndef init_bst_inorder_iterator_default_unsafe
static SR_FORCE_INLINE void __bst_init_inorder_iterator_default(
	bst_inorder_iterator_t* PARAM_OUT itrptr)
{
	__bst_init_inorder_iterator(itrptr, null, null);
}
#define init_bst_inorder_iterator_default_unsafe __bst_init_inorder_iterator_default
#endif//init_bst_inorder_iterator_default_unsafe


#ifndef get_bst_begin_inorder_iterator_unsafe
// 开始节点
static SR_FORCE_INLINE bst_inorder_iterator_t*  __bst_begin_inorder_iterator(
	bst_inorder_iterator_t* PARAM_INOUT itrptr)
{
	if ((null ==  get_in_itr_root_ref(itrptr->itr)) ||
		(null == *get_in_itr_root_ref(itrptr->itr)))
	{
		itrptr->itr.m_this_node_ptr = null;
		return null;
	}
	itrptr->itr.m_this_node_ptr = get_bst_min_node(*get_in_itr_root_ref(itrptr->itr));
	return itrptr;
}
#define get_bst_begin_inorder_iterator_unsafe    __bst_begin_inorder_iterator
#endif//get_bst_begin_inorder_iterator_unsafe


#ifndef get_bst_end_inorder_iterator_unsafe
// 结束节点
static SR_FORCE_INLINE bst_inorder_iterator_t*  __bst_end_inorder_iterator(
	bst_inorder_iterator_t* PARAM_INOUT itrptr)
{
	if ((null ==  get_in_itr_root_ref(itrptr->itr)) ||
		(null == *get_in_itr_root_ref(itrptr->itr)))
	{
		itrptr->itr.m_this_node_ptr = null;
		return null;
	}
	itrptr->itr.m_this_node_ptr = get_bst_max_node(*get_in_itr_root_ref(itrptr->itr));
	return itrptr;
}
#define get_bst_end_inorder_iterator_unsafe      __bst_end_inorder_iterator
#endif//get_bst_end_inorder_iterator_unsafe


#ifndef increase_bst_inorder_iterator_unsafe
// ++
static SR_INLINE bst_inorder_iterator_t* __bst_inorder_iterator_increase
   (bst_inorder_iterator_t* PARAM_INOUT itrptr)
{

	tree_node_ptr right_node_ptr;
	tree_node_ptr parent_node_ptr;
	tree_node_ptr return_node_ptr;
	tree_node_ptr current_node_ptr;

	if ((null ==  get_in_itr_root_ref(itrptr->itr))  ||
		(null == *get_in_itr_root_ref(itrptr->itr)) ||
		(null ==  get_in_itr_this(itrptr->itr)))
	{
		return null;
	}

	DO_ONE_LOOP_BEGIN

	current_node_ptr = get_in_itr_this(itrptr->itr);

	right_node_ptr = get_tree_right(current_node_ptr);

	if (current_node_ptr == *get_in_itr_root_ref(itrptr->itr))
	{
		BREAK_LOOP_CONDITION_SETS(!right_node_ptr,
			return_node_ptr, null);

		BREAK_LOOP(return_node_ptr, get_bst_min_node(right_node_ptr));
	}

	if (null != right_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, get_bst_min_node(right_node_ptr));
	}

	parent_node_ptr = get_tree_parent(current_node_ptr);

	if (get_tree_left(parent_node_ptr) == current_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, parent_node_ptr);
	}

	if (itrptr->itr.m_this_node_ptr == parent_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, null);
	}

	current_node_ptr = get_tree_parent(current_node_ptr);
	while (1)
	{
		parent_node_ptr = get_tree_parent(current_node_ptr);
		if (null == parent_node_ptr)
		{
			return_node_ptr = null;
			break;
		}

		if (get_tree_right(parent_node_ptr) == current_node_ptr)
		{
			current_node_ptr = get_tree_parent(current_node_ptr);
			continue;
		}

		if (get_tree_left(parent_node_ptr) == current_node_ptr)
		{
			return_node_ptr = get_tree_parent(current_node_ptr);
			break;
		}

	}

	DO_ONE_LOOP_END
		
	if (null != return_node_ptr)
	{
		itrptr->itr.m_this_node_ptr = return_node_ptr;
		return itrptr;
	}
	else
	{
		return null;
	}
}																  
#define increase_bst_inorder_iterator_unsafe     __bst_inorder_iterator_increase
#endif//increase_bst_inorder_iterator_unsafe

#ifndef decrease_bst_inorder_iterator_unsafe
//--
static SR_INLINE bst_inorder_iterator_t* __bst_inorder_iterator_decrease
(bst_inorder_iterator_t* PARAM_INOUT itrptr)
{
	tree_node_ptr left_node_ptr;
	tree_node_ptr parent_node_ptr;
	tree_node_ptr return_node_ptr;
	tree_node_ptr current_node_ptr;

	if ((null ==  get_in_itr_root_ref(itrptr->itr)) ||
		(null == *get_in_itr_root_ref(itrptr->itr)) ||
		(null ==  get_in_itr_this(itrptr->itr)))
	{
		return null;
	}

	DO_ONE_LOOP_BEGIN

	current_node_ptr = get_in_itr_this(itrptr->itr);
	left_node_ptr    = get_tree_left(current_node_ptr);

	if (current_node_ptr == *get_in_itr_root_ref(itrptr->itr))
	{
		BREAK_LOOP_CONDITION_SETS(!left_node_ptr, return_node_ptr, null);
		BREAK_LOOP(return_node_ptr, get_bst_max_node(left_node_ptr));
	}

	if (null != left_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, get_bst_max_node(left_node_ptr));
	}

	parent_node_ptr = get_tree_parent(current_node_ptr);
	if (get_tree_right(parent_node_ptr) == current_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, parent_node_ptr);
	}

	if (current_node_ptr == parent_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, null);
	}

	current_node_ptr = parent_node_ptr;
	while (1)
	{
		parent_node_ptr = get_tree_parent(current_node_ptr);
		if (null == parent_node_ptr)
		{
			return_node_ptr = null;
			break;
		}
		if (get_tree_left(parent_node_ptr) == current_node_ptr)
		{
			current_node_ptr = parent_node_ptr;
			continue;
		}
		if (get_tree_right(parent_node_ptr) == current_node_ptr)
		{
			return_node_ptr = parent_node_ptr;
			break;
		}

	}
	DO_ONE_LOOP_END
	if (null != return_node_ptr)
	{
		itrptr->itr.m_this_node_ptr = return_node_ptr;
		return itrptr;
	}
	else
	{
		return null;
	}
}
#define decrease_bst_inorder_iterator_unsafe     __bst_inorder_iterator_decrease
#endif//decrease_bst_inorder_iterator_unsafe









