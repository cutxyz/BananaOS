///////////////////////////////////////
// posorder_bst_iterator_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bstnode_define_declare.h"
#include "iterator_bst_itr.h"

#undef  get_pos_itr_this
#define get_pos_itr_this(X)     get_bst_itr_this_traits(tree_node_ptr,X)

#undef  get_pos_itr_root_ref
#define get_pos_itr_root_ref(X) get_bst_itr_root_ref_traits(tree_node_ptr,X)

#ifndef init_bst_posorder_iterator_unsafe
// 初始化迭代器
static SR_FORCE_INLINE void __bst_init_posorder_iterator (
	bst_posorder_iterator_t* PARAM_OUT itrptr,
	tree_node_ptr* PARAM_IN root_ref,
	tree_node_ptr PARAM_IN this_node_ptr)
{
	itrptr->itr.m_tree_root_ref = root_ref;
	itrptr->itr.m_this_node_ptr = this_node_ptr;
}
#define init_bst_posorder_iterator_unsafe 	     __bst_init_posorder_iterator
#endif//init_bst_posorder_iterator_unsafe


#ifndef init_bst_const_posorder_iterator_unsafe
static SR_FORCE_INLINE void __bst_init_const_posorder_iterator(
	bst_posorder_iterator_t* PARAM_OUT itrptr,
	const tree_node_ptr* PARAM_IN root_ref,
	const tree_node_ptr PARAM_IN this_node_ptr)
{
	itrptr->const_itr.m_tree_root_ref = root_ref;
	itrptr->const_itr.m_this_node_ptr = this_node_ptr;
}
#define init_bst_const_posorder_iterator_unsafe	 __bst_init_const_posorder_iterator
#endif//init_bst_const_posorder_iterator_unsafe

#ifndef init_bst_posorder_iterator_default_unsafe
static SR_FORCE_INLINE void __bst_init_posorder_iterator_default(
	bst_posorder_iterator_t* PARAM_OUT itrptr)
{
	__bst_init_posorder_iterator(itrptr, null, null);
}
#define init_bst_posorder_iterator_default_unsafe __bst_init_posorder_iterator_default
#endif//init_bst_posorder_iterator_default_unsafe


#ifndef get_bst_begin_posorder_iterator_unsafe
// 开始节点
static SR_INLINE bst_posorder_iterator_t*  __bst_begin_posorder_iterator(
	bst_posorder_iterator_t* PARAM_INOUT itrptr)
{

	tree_node_ptr begin_node_ptr;
	tree_node_ptr tmp_node_ptr;
	tree_node_ptr tmp_lr_node_ptr;

	if ((null ==  get_pos_itr_root_ref(itrptr->itr)) ||
		(null == *get_pos_itr_root_ref(itrptr->itr)))
	{
		itrptr->itr.m_this_node_ptr = null;
		return null;
	}

	tmp_node_ptr = *get_pos_itr_root_ref(itrptr->itr);
	begin_node_ptr = null;
	while (tmp_node_ptr)
	{
		begin_node_ptr  = tmp_node_ptr;
		tmp_lr_node_ptr = get_tree_left(tmp_node_ptr);

		if (tmp_lr_node_ptr)
		{
			tmp_node_ptr = tmp_lr_node_ptr;
			continue;
		}

		tmp_lr_node_ptr = get_tree_right(tmp_node_ptr);

		if (tmp_lr_node_ptr)
		{
			tmp_node_ptr = tmp_lr_node_ptr;
			continue;
		}

		break;
	}
	itrptr->itr.m_this_node_ptr = begin_node_ptr;
	return itrptr;
}
#define get_bst_begin_posorder_iterator_unsafe    __bst_begin_posorder_iterator
#endif//get_bst_begin_posorder_iterator_unsafe

#ifndef get_bst_end_posorder_iterator_unsafe
// 结束节点
static SR_FORCE_INLINE bst_posorder_iterator_t*  __bst_end_posorder_iterator(
	bst_posorder_iterator_t* PARAM_INOUT itrptr)
{
	if ((null == get_pos_itr_root_ref(itrptr->itr)) ||
		(null == *get_pos_itr_root_ref(itrptr->itr)))
	{
		itrptr->itr.m_this_node_ptr = null;
		return null;
	}

	itrptr->itr.m_this_node_ptr = *get_pos_itr_root_ref(itrptr->itr);
	return itrptr;
}
#define get_bst_end_posorder_iterator_unsafe      __bst_end_posorder_iterator
#endif//get_bst_end_posorder_iterator_unsafe


#ifndef increase_bst_posorder_iterator_unsafe
// ++
static SR_INLINE bst_posorder_iterator_t* __bst_posorder_iterator_increase
   (bst_posorder_iterator_t* PARAM_INOUT itrptr)
{
	tree_node_ptr tmp_parent_node_ptr;
	tree_node_ptr tmp_r_node_ptr;
	tree_node_ptr tmp_l_node_ptr;
	tree_node_ptr return_node_ptr;
	tree_node_ptr current_node_ptr;

	if ((null == get_pos_itr_root_ref(itrptr->itr))  ||
		(null == *get_pos_itr_root_ref(itrptr->itr)) ||
		(null == get_pos_itr_this(itrptr->itr)))
	{
		return null;
	}

	current_node_ptr = get_pos_itr_this(itrptr->itr);

	if (current_node_ptr == *get_pos_itr_root_ref(itrptr->itr))
	{
		return null;
	}

	tmp_parent_node_ptr = get_tree_parent(current_node_ptr);
	if (null == tmp_parent_node_ptr)
	{
		return null;
	}

	return_node_ptr = null;
	DO_ONE_LOOP_BEGIN
	
	tmp_r_node_ptr = get_tree_right(tmp_parent_node_ptr);

	if (tmp_r_node_ptr == current_node_ptr)
	{
		return_node_ptr = tmp_parent_node_ptr;
		break;
	}

	tmp_l_node_ptr = get_tree_left(tmp_parent_node_ptr);
	if (tmp_l_node_ptr == current_node_ptr)
	{
		if (tmp_r_node_ptr)
		{
			bst_posorder_iterator_t  tmpitr;
			bst_posorder_iterator_t* tmpitr_ptr;
			tmpitr.itr.m_tree_root_ref = &tmp_r_node_ptr;
			 
			tmpitr_ptr = get_bst_begin_posorder_iterator_unsafe(&tmpitr);
			if (tmpitr_ptr)
			{
				return_node_ptr = get_pos_itr_this(tmpitr_ptr->itr);
			}
			else
			{
				return_node_ptr = null;
			}
		}
		else
		{
			return_node_ptr = tmp_parent_node_ptr;
		}
		break;
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
#define increase_bst_posorder_iterator_unsafe     __bst_posorder_iterator_increase
#endif//increase_bst_posorder_iterator_unsafe









