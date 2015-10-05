//////////////////////////////////////
// iterator_linkedlist_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "linked_list_node_template.h"



#ifndef LINKEDLIST_ITEARATOR_
#define LINKEDLIST_ITEARATOR_

typedef struct st_linkedlist_iterator
{
	linkedlist_node_ptr* m_list_root;
	linkedlist_node_ptr  m_this_node_ptr;
}st_linkedlist_iterator_t;

typedef struct st_linkedlist_const_iterator
{
	const linkedlist_node_ptr* m_list_root;
	const linkedlist_node_ptr  m_this_node_ptr;
}st_linkedlist_const_iterator_t;

typedef union un_linkedlist_iterator
{
	st_linkedlist_iterator_t         itr;
	st_linkedlist_const_iterator_t   const_itr;
}linkedlist_iterator_t;





#endif //LINKEDLIST_ITEARATOR_

#ifndef	 init_linkedlist_itreator_unsafe
#define  init_linkedlist_itreator_unsafe         __init_linkedlist_itreator
#endif// init_linkedlist_itreator_unsafe

#ifndef	 init_linkedlist_const_itreator_unsafe
#define  init_linkedlist_const_itreator_unsafe   __init_linkedlist_const_itreator
#endif// init_linkedlist_const_itreator_unsafe

#ifndef	 init_linkedlist_itreator_defualt_unsafe
#define  init_linkedlist_itreator_defualt_unsafe __init_linkedlist_itreator_defualt
#endif// init_linkedlist_itreator_defualt_unsafe

#ifndef	 linkedlist_begin_itreator_unsafe
#define  linkedlist_begin_itreator_unsafe        __linkedlist_begin_iterator
#endif// linkedlist_begin_itreator_unsafe

#ifndef	 linkedlist_end_itreator_unsafe
#define  linkedlist_end_itreator_unsafe          __linkedlist_end_iterator
#endif// linkedlist_end_itreator_unsafe

#ifndef	 linkedlist_itreator_increase_unsafe
#define  linkedlist_itreator_increase_unsafe     __linkedlist_iterator_increase
#endif// linkedlist_itreator_increase_unsafe

#ifndef	 linkedlist_itreator_decrease_unsafe
#define  linkedlist_itreator_decrease_unsafe     __linkedlist_iterator_decrease
#endif// linkedlist_itreator_decrease_unsafe

//////////////////////////////////////////////////////////////////////////
#ifndef linkedlist_iterator_funcs
#define linkedlist_iterator_funcs

static SR_FORCE_INLINE	void __init_linkedlist_itreator
(linkedlist_iterator_t* PARAM_OUT itr_ptr,
linkedlist_node_ptr* PARAM_IN list_root_ptr,
linkedlist_node_ptr  PARAM_IN this_node_ptr)
{
	itr_ptr->itr.m_list_root = list_root_ptr;
	itr_ptr->itr.m_this_node_ptr = this_node_ptr;
}

static SR_FORCE_INLINE	void __init_linkedlist_const_itreator
(linkedlist_iterator_t* PARAM_OUT itr_ptr,
const linkedlist_node_ptr* PARAM_IN list_root_ptr,
const linkedlist_node_ptr  PARAM_IN this_node_ptr)
{
	itr_ptr->const_itr.m_list_root = list_root_ptr;
	itr_ptr->const_itr.m_this_node_ptr = this_node_ptr;
}

static SR_FORCE_INLINE	void __init_linkedlist_itreator_defualt
(linkedlist_iterator_t* PARAM_OUT itr_ptr)
{
	__init_linkedlist_itreator(itr_ptr, null, null);
}

static SR_FORCE_INLINE linkedlist_iterator_t* __linkedlist_begin_iterator
(linkedlist_iterator_t* PARAM_INOUT itr_ptr)
{
	if ((itr_ptr->itr.m_list_root) &&
		(null != *(itr_ptr->itr.m_list_root)))
	{
		itr_ptr->itr.m_this_node_ptr = *(itr_ptr->itr.m_list_root);
		return itr_ptr;
	}
	return null;
}

static SR_FORCE_INLINE linkedlist_iterator_t* __linkedlist_end_iterator
(linkedlist_iterator_t* PARAM_INOUT itr_ptr)
{
	if ((itr_ptr->itr.m_list_root) &&
		(null != *(itr_ptr->itr.m_list_root)))
	{
		linkedlist_node_ptr end_ptr = get_list_prev_node_unsafe(*(itr_ptr->itr.m_list_root));
		if (end_ptr)
		{
			itr_ptr->itr.m_this_node_ptr = end_ptr;
		}
		else
		{
			itr_ptr->itr.m_this_node_ptr = *(itr_ptr->itr.m_list_root);
		}
		return itr_ptr;
	}
	return null;
}

static SR_INLINE linkedlist_iterator_t* __linkedlist_iterator_increase
(linkedlist_iterator_t* PARAM_INOUT itr_ptr)
{
	linkedlist_node_ptr next_ptr;
	if (null == itr_ptr->itr.m_this_node_ptr)
	{
		return null;
	}
	next_ptr = get_list_next_node_unsafe(itr_ptr->itr.m_this_node_ptr);
	if (null == next_ptr || next_ptr == itr_ptr->itr.m_this_node_ptr)
	{
		return null;
	}
	itr_ptr->itr.m_this_node_ptr = next_ptr;
	return itr_ptr;
}

static SR_INLINE linkedlist_iterator_t* __linkedlist_iterator_decrease
(linkedlist_iterator_t* PARAM_INOUT itr_ptr)
{
	linkedlist_node_ptr prev_ptr;
	if (null == itr_ptr->itr.m_this_node_ptr)
	{
		return null;
	}
	prev_ptr = get_list_prev_node_unsafe(itr_ptr->itr.m_this_node_ptr);
	if (null == prev_ptr || prev_ptr == itr_ptr->itr.m_this_node_ptr)
	{
		return null;
	}
	itr_ptr->itr.m_this_node_ptr = prev_ptr;
	return itr_ptr;
}


#endif // linkedlist_iterator_funcs














