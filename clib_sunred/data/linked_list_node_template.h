//////////////////////////////////////
// linked_list_node_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "type.h"

#ifndef SUNRED_LINKED_LIST
#define SUNRED_LINKED_LIST
typedef struct st_linkedlist_node
{
	struct st_linkedlist_node* m_prev_node_ptr;
	struct st_linkedlist_node* m_next_node_ptr;
}linkedlist_node_t;

#define  linkedlist_node_ptr        linkedlist_node_t*
#define  get_list_prev_node_unsafe  __get_list_prev_node
#define  get_list_next_node_unsafe	__get_list_next_node
#define  set_list_prev_node_unsafe  __set_list_prev_node
#define  set_list_next_node_unsafe	__set_list_next_node
#define  get_list_prev_node_const_unsafe  __get_list_prev_node_const
#define  get_list_next_node_const_unsafe  __get_list_next_node_const

static SR_FORCE_INLINE 	linkedlist_node_ptr 
__get_list_prev_node
(linkedlist_node_ptr PARAM_IN node_ptr)
{
	return node_ptr->m_prev_node_ptr;
}
static SR_FORCE_INLINE 	linkedlist_node_ptr 
__get_list_next_node
(linkedlist_node_ptr PARAM_IN node_ptr)
{
	return node_ptr->m_next_node_ptr;
}

static SR_FORCE_INLINE 	void
__set_list_prev_node
(linkedlist_node_ptr PARAM_IN node_ptr, 
linkedlist_node_ptr PARAM_IN set_node_ptr)
{
	node_ptr->m_prev_node_ptr = set_node_ptr;
}
static SR_FORCE_INLINE 	void
__set_list_next_node
(linkedlist_node_ptr PARAM_IN node_ptr,
linkedlist_node_ptr PARAM_IN set_node_ptr)
{
	node_ptr->m_next_node_ptr = set_node_ptr;
}

static SR_FORCE_INLINE 	const linkedlist_node_ptr 
__get_list_prev_node_const
(const linkedlist_node_ptr PARAM_IN node_ptr)
{
	return node_ptr->m_prev_node_ptr;
}
static SR_FORCE_INLINE 	const linkedlist_node_ptr 
__get_list_next_node_const
(const linkedlist_node_ptr PARAM_IN node_ptr)
{
	return node_ptr->m_next_node_ptr;
}
#endif	 //SUNRED_LINKED_LIST


#ifndef listnode_init_unsafe  
#define listnode_init_unsafe         __init_listnode
#endif//listnode_init_unsafe

#ifndef listnode_reset_unsafe  
#define listnode_reset_unsafe        __reset_listnode
#endif//listnode_reset_unsafe

#ifndef listnode_insertback_unsafe  
#define listnode_insertback_unsafe   __insert_listnode_back
#endif//listnode_insertback_unsafe

#ifndef listnode_insertfront_unsafe  
#define listnode_insertfront_unsafe  __insert_listnode_front
#endif//listnode_insertfront_unsafe

#ifndef listnode_replace_unsafe  
#define listnode_replace_unsafe      __replace_listnode
#endif//listnode_replace_unsafe

#ifndef listnode_delete_unsafe  
#define listnode_delete_unsafe       __delete_listnode
#endif//listnode_delete_unsafe

#ifndef listnode_remove_unsafe  
#define listnode_remove_unsafe       __remove_listnode
#endif//listnode_remove_unsafe

#ifndef linkedlist_node_funcs
#define linkedlist_node_funcs
static SR_FORCE_INLINE void __init_listnode(linkedlist_node_ptr PARAM_INOUT node_ptr,
	linkedlist_node_ptr PARAM_IN prev_ptr, linkedlist_node_ptr PARAM_IN next_ptr)
{
	set_list_prev_node_unsafe(node_ptr, prev_ptr);
	set_list_next_node_unsafe(node_ptr, next_ptr);
}

static SR_FORCE_INLINE void __reset_listnode(linkedlist_node_ptr PARAM_INOUT node_ptr)
{
	__init_listnode(node_ptr, node_ptr, node_ptr);
}

static SR_FORCE_INLINE linkedlist_node_ptr __insert_listnode_back(linkedlist_node_ptr PARAM_INOUT node_ptr,
	linkedlist_node_ptr PARAM_INOUT addnode_ptr)
{
	set_list_prev_node_unsafe(addnode_ptr, node_ptr);
	set_list_next_node_unsafe(addnode_ptr, get_list_next_node_unsafe(node_ptr));
	set_list_prev_node_unsafe(get_list_next_node_unsafe(node_ptr), addnode_ptr);
	set_list_next_node_unsafe(node_ptr, addnode_ptr);
	return addnode_ptr;
}

static SR_FORCE_INLINE linkedlist_node_ptr __insert_listnode_front(linkedlist_node_ptr PARAM_INOUT node_ptr,
	linkedlist_node_ptr PARAM_INOUT addnode_ptr)
{
	set_list_next_node_unsafe(addnode_ptr, node_ptr);
	set_list_prev_node_unsafe(addnode_ptr, get_list_prev_node_unsafe(node_ptr));
	set_list_next_node_unsafe(get_list_prev_node_unsafe(node_ptr), addnode_ptr);
	set_list_prev_node_unsafe(node_ptr, addnode_ptr);
	return addnode_ptr;
}

static SR_FORCE_INLINE linkedlist_node_ptr __replace_listnode(linkedlist_node_ptr PARAM_INOUT from, 
	linkedlist_node_ptr PARAM_INOUT to)
{
	to->m_prev_node_ptr = from->m_prev_node_ptr;
	to->m_next_node_ptr = from->m_next_node_ptr;
	from->m_next_node_ptr->m_prev_node_ptr = to;
	from->m_prev_node_ptr->m_next_node_ptr = to;
}

static SR_FORCE_INLINE void __delete_listnode(linkedlist_node_ptr PARAM_INOUT node_ptr)
{
	set_list_next_node_unsafe(get_list_prev_node_unsafe(node_ptr),
		get_list_next_node_unsafe(node_ptr));
	set_list_prev_node_unsafe(get_list_next_node_unsafe(node_ptr),
		get_list_prev_node_unsafe(node_ptr));
	__init_listnode(node_ptr, null, null);
}

static SR_FORCE_INLINE linkedlist_node_ptr __remove_listnode(linkedlist_node_ptr PARAM_INOUT node_ptr)
{
	set_list_next_node_unsafe(get_list_prev_node_unsafe(node_ptr),
		get_list_next_node_unsafe(node_ptr));
	set_list_prev_node_unsafe(get_list_next_node_unsafe(node_ptr),
		get_list_prev_node_unsafe(node_ptr));
	__reset_listnode(node_ptr);
}
#endif //linkedlist_node_funcs









