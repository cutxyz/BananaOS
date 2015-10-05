//////////////////////////////////////
// bst_new_release_node.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "../include/util/sr_util.h"


#ifndef BST_NEW_RELEASE_NODE_
#define BST_NEW_RELEASE_NODE_

typedef void* (*new_bst_node_func)(object_allocator_t* PARAM_INOUT ins_ptr,
	                                     const void* PARAM_IN copy_ptr);
typedef result_t (*release_bst_node_func)(object_allocator_t* PARAM_INOUT ins_ptr,
	void* PARAM_INOUT del_ptr);

typedef struct st_bst_node_allocator 
{
	object_allocator_t	   m_alloc_inst;
	new_bst_node_func      new_node;
	release_bst_node_func  release_node;
}bst_node_allocator_t;

#endif//BST_NEW_RELEASE_NODE_

#ifndef alloc_new_node_p
#define alloc_new_node_p(alloc_ptr, copy_ptr)      ((alloc_ptr)->new_node(&((alloc_ptr)->m_alloc_inst), (copy_ptr))) 
#define alloc_new_node(alloc, copy_ptr)		       alloc_new_node_p(&(alloc), (copy_ptr))
#endif//alloc_new_node_p

#ifndef dealloc_release_node_p
#define dealloc_release_node_p(alloc_ptr, del_ptr) ((alloc_ptr)->release_node(&((alloc_ptr)->m_alloc_inst),del_ptr))
#define dealloc_release_node(alloc, del_ptr)	   dealloc_release_node_p(&(alloc), del_ptr)
#endif//dealloc_release_node_p

