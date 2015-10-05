//////////////////////////////////////
// preorder_bst_iterator_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bstnode_define_declare.h"
#include "iterator_bst_itr.h"
#include "bst_minmax_template.c"

#undef  get_pre_itr_this
#define get_pre_itr_this(X)     get_bst_itr_this_traits(tree_node_ptr,X)

#undef  get_pre_itr_root_ref
#define get_pre_itr_root_ref(X) get_bst_itr_root_ref_traits(tree_node_ptr,X)

#ifndef init_bst_preorder_iterator_unsafe
// 初始化迭代器
static SR_FORCE_INLINE void __bst_init_preorder_iterator (
	bst_preorder_iterator_t* PARAM_OUT itrptr,
	tree_node_ptr* PARAM_IN root_ref,
	tree_node_ptr PARAM_IN this_node_ptr)
{
	itrptr->itr.m_tree_root_ref = root_ref;
	itrptr->itr.m_this_node_ptr = this_node_ptr;

	itrptr->itr.m_next_step     = PREORDER_NEXT_LEFT;
	itrptr->itr.m_last_result   = STATUS_OK;
}
#define init_bst_preorder_iterator_unsafe __bst_init_preorder_iterator
#endif//init_bst_preorder_iterator_unsafe

#ifndef init_bst_const_preorder_iterator_unsafe
static SR_FORCE_INLINE void __bst_init_const_preorder_iterator(
	bst_preorder_iterator_t* PARAM_OUT itrptr,
	const tree_node_ptr* PARAM_IN root_ref,
	const tree_node_ptr PARAM_IN this_node_ptr)
{
	itrptr->const_itr.m_tree_root_ref = root_ref;
	itrptr->const_itr.m_this_node_ptr = this_node_ptr;

	itrptr->itr.m_next_step           = PREORDER_NEXT_LEFT;
	itrptr->itr.m_last_result         = STATUS_OK;
}
#define init_bst_const_preorder_iterator_unsafe	 __bst_init_const_preorder_iterator
#endif//init_bst_const_preorder_iterator_unsafe


#ifndef init_bst_preorder_iterator_default_unsafe
static SR_FORCE_INLINE void __bst_init_preorder_iterator_default(
	bst_preorder_iterator_t* PARAM_OUT itrptr)
{
	__bst_init_preorder_iterator(itrptr, null, null);
}
#define init_bst_preorder_iterator_default_unsafe __bst_init_preorder_iterator_default
#endif//init_bst_preorder_iterator_default_unsafe

#ifndef get_bst_begin_preorder_iterator_unsafe
// 开始节点
static SR_INLINE bst_preorder_iterator_t*  __bst_begin_preorder_iterator(
	bst_preorder_iterator_t* PARAM_INOUT itrptr)
{

	tree_node_ptr begin_node_ptr;

	if ((null ==  get_pre_itr_root_ref(itrptr->itr)) ||
		(null == *get_pre_itr_root_ref(itrptr->itr)))
	{
		itrptr->itr.m_this_node_ptr = null;
		return null;
	}

	begin_node_ptr = *get_pre_itr_root_ref(itrptr->itr);
	if (get_tree_left(begin_node_ptr))
	{
		itrptr->itr.m_next_step = PREORDER_NEXT_LEFT;
	}
	else if (get_tree_right(begin_node_ptr))
	{
		itrptr->itr.m_next_step = PREORDER_NEXT_RIGHT;
	}
	else
	{
		itrptr->itr.m_next_step = PREORDER_FIN;
	}
	itrptr->itr.m_last_result   = STATUS_OK;
	itrptr->itr.m_this_node_ptr = begin_node_ptr;
	return itrptr;
}
#define get_bst_begin_preorder_iterator_unsafe    __bst_begin_preorder_iterator
#endif//get_bst_begin_preorder_iterator_unsafe

#ifndef get_bst_end_preorder_iterator_unsafe
// 结束节点
static SR_FORCE_INLINE bst_preorder_iterator_t*  __bst_end_preorder_iterator(
	bst_preorder_iterator_t* PARAM_INOUT itrptr)
{

	tree_node_ptr temp_node_ptr;
	tree_node_ptr end_node_ptr;
	tree_node_ptr temp_rl_node_ptr;

	if ((null ==  get_pre_itr_root_ref(itrptr->itr)) ||
		(null == *get_pre_itr_root_ref(itrptr->itr)))
	{
		itrptr->itr.m_this_node_ptr = null;
		return null;
	}

	temp_node_ptr = *get_pre_itr_root_ref(itrptr->itr);
	end_node_ptr  = null;

	while (temp_node_ptr)
	{
		end_node_ptr = temp_node_ptr;
		temp_rl_node_ptr = get_tree_right(temp_node_ptr);
		if (temp_rl_node_ptr)
		{
			temp_node_ptr = temp_rl_node_ptr;
			continue;
		}

		temp_rl_node_ptr = get_tree_left(temp_node_ptr);
		if (temp_rl_node_ptr)
		{
			temp_node_ptr = temp_rl_node_ptr;
			continue;
		}

		break;
	}

	itrptr->itr.m_this_node_ptr  = end_node_ptr;
	itrptr->itr.m_next_step      = PREORDER_FIN;
	itrptr->itr.m_last_result    = STATUS_OK;

	return itrptr;
}
#define get_bst_end_preorder_iterator_unsafe      __bst_end_preorder_iterator
#endif//get_bst_end_preorder_iterator_unsafe

#ifndef increase_bst_preorder_iterator_unsafe
// ++
static SR_INLINE bst_preorder_iterator_t* __bst_preorder_iterator_increase
   (bst_preorder_iterator_t* PARAM_INOUT itrptr)
{
	PREODER_ITERATOR_NEXT_FLAG_t this_step_flag;
	PREODER_ITERATOR_NEXT_FLAG_t next_step_flag;

	tree_node_ptr next_node_ptr;
	result_t status = STATUS_OK;
	bst_preorder_iterator_t* itr_retn_ptr = itrptr;

	if ((null ==  get_pre_itr_root_ref(itrptr->itr)) ||
		(null == *get_pre_itr_root_ref(itrptr->itr)) ||
		(null ==  get_pre_itr_this(itrptr->itr)) ||
		(PREORDER_FIN == itrptr->itr.m_next_step) ||
		(STATUS_OK != itrptr->itr.m_last_result))
	{
		return null;
	}

	this_step_flag = itrptr->itr.m_next_step;

	switch (this_step_flag)
	{
		case PREORDER_NEXT_SUB_ROOT_RIGHT:
		{
			tree_node_ptr cur_node_ptr = get_pre_itr_this(itrptr->itr);
			do
			{
				next_node_ptr = get_tree_parent(cur_node_ptr);
				if (cur_node_ptr == *get_pre_itr_root_ref(itrptr->itr))
				{
					status         = STATUS_OK;
					next_step_flag = PREORDER_FIN;
					break;
				}
				else if (null == next_node_ptr)
				{
					status         = STATUS_OK;
					next_step_flag = PREORDER_FIN;
					break;
				}
				else if (get_tree_right(next_node_ptr) == cur_node_ptr)
				{
					cur_node_ptr = next_node_ptr;
					continue;
				}
				else if (get_tree_left(next_node_ptr) == cur_node_ptr)
				{
					if (null == get_tree_right(next_node_ptr))
					{
						cur_node_ptr = next_node_ptr;
						continue;
					}
					next_node_ptr = get_tree_right(next_node_ptr);
					status = STATUS_OK;

					if (null != get_tree_left(next_node_ptr))
					{
						next_step_flag = PREORDER_NEXT_LEFT;
						break;
					}
					else if (null != get_tree_right(next_node_ptr))
					{
						next_step_flag = PREORDER_NEXT_RIGHT;
						break;
					}
					else
					{
						next_step_flag = PREORDER_NEXT_SUB_ROOT_RIGHT;
						break;
					}

				}
				else
				{
					status         = STATUS_MEM_ERR;
					next_step_flag = PREORDER_FIN;
					next_node_ptr  = null;
				}
			}while (1);

			if (next_node_ptr)
			{
				itrptr->itr.m_this_node_ptr = next_node_ptr;
			}
			else
			{
				itr_retn_ptr = null;
			}
			itrptr->itr.m_next_step = next_step_flag;
			itrptr->itr.m_last_result = status;
		}
		break;
		case PREORDER_NEXT_LEFT:
		{
			next_node_ptr = get_tree_left(get_pre_itr_this(itrptr->itr));
			if (null == next_node_ptr)
			{
				status         = STATUS_MEM_ERR;
				next_step_flag = PREORDER_FIN;
				itr_retn_ptr   = null;
			}
			else if (null != get_tree_left(next_node_ptr))
			{
				next_step_flag = PREORDER_NEXT_LEFT;
			}
			else if (null != get_tree_right(next_node_ptr))
			{
				next_step_flag = PREORDER_NEXT_RIGHT;
			}
			else
			{
				next_step_flag = PREORDER_NEXT_SUB_ROOT_RIGHT;
			}
			if (next_node_ptr)
			{
				itrptr->itr.m_this_node_ptr = next_node_ptr;
			}
			else
			{
				itr_retn_ptr = null;
			}

			itrptr->itr.m_next_step   = next_step_flag;
			itrptr->itr.m_last_result = status;
		}
		break;
		case PREORDER_NEXT_RIGHT:
		{
			next_node_ptr = get_tree_right(get_pre_itr_this(itrptr->itr));
			if (null == next_node_ptr)
			{
				status         = STATUS_MEM_ERR;
				next_step_flag = PREORDER_FIN;
				itr_retn_ptr   = null;
			}
			else if (null != get_tree_left(next_node_ptr))
			{
				next_step_flag = PREORDER_NEXT_LEFT;
			}
			else if (null != get_tree_right(next_node_ptr))
			{
				next_step_flag = PREORDER_NEXT_RIGHT;
			}
			else
			{
				next_step_flag = PREORDER_NEXT_SUB_ROOT_RIGHT;
			}
			if (next_node_ptr)
			{
				itrptr->itr.m_this_node_ptr = next_node_ptr;
			}
			else
			{
				itr_retn_ptr = null;
			}
			itrptr->itr.m_next_step   = next_step_flag;
			itrptr->itr.m_last_result = status;
		}
		break;
		case PREORDER_NEXT_BEGIN:
		{
			itr_retn_ptr = get_bst_begin_preorder_iterator_unsafe(itrptr);
		}
		break;
		case PREORDER_NEXT_END:
		{
			itrptr->itr.m_next_step   = PREORDER_FIN;
			itrptr->itr.m_last_result = STATUS_OK;
			itr_retn_ptr              = null;
		}
		break;
		default:
		{
		    itrptr->itr.m_next_step   = PREORDER_FIN;
			itrptr->itr.m_last_result = STATUS_INVALID_OPERATION;
			itr_retn_ptr              = null;
		}
		break;
	}
	return itr_retn_ptr;
}																  
#define increase_bst_preorder_iterator_unsafe     __bst_preorder_iterator_increase
#endif//increase_bst_preorder_iterator_unsafe


