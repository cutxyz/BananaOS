//////////////////////////////////////
// bst_node.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef SUNRED_BST_NODE_H_
#define SUNRED_BST_NODE_H_

#include "../include/type.h"

typedef struct st_bst_node_header
{
	struct st_bst_node_header* m_parent_ptr;
	struct st_bst_node_header* m_left_ptr;
	struct st_bst_node_header* m_right_ptr;

#ifdef BST_NODE_DEBUG_INFO
	const char* m_debug_str;
#endif//BST_NODE_DEBUG_INFO
}st_bst_node_header_t;

#define ALIGNED_SIZE 4
typedef 
ALIGNED_VARIABLE_ATTRIBUTE(ALIGNED_SIZE,
		struct st_aligned_bst_node_header
		{
			ptr_t					   m_parent_ptr;
			struct st_bst_node_header* m_left_ptr;
			struct st_bst_node_header* m_right_ptr;
		}
)
st_aligned_bst_node_header_t;

typedef
ALIGNED_VARIABLE_ATTRIBUTE(ALIGNED_SIZE,
	union un_bst_node_header
	{
		st_bst_node_header_t         m_node;
		st_aligned_bst_node_header_t m_aligned_node;
	}
)
bst_node_header_t;

#define bst_node              st_bst_node_header_t
#define _bst_node_ptr         struct st_bst_node_header*
#define constbst_node_ptr 	  const struct st_bst_node_header*
#define bst_node_ptr          struct st_bst_node_header*

#define aligned_bst_node_ptr  st_aligned_bst_node_header_t*

// 左值操作右值操作均OK的get函数
#define get_bst_left_ref_unsafe       __get_bst_left_ref
#define get_bst_right_ref_unsafe      __get_bst_right_ref
#define get_bst_parent_ref_unsafe     __get_bst_parent_ref

// 左值操作的get函数
#define get_bst_left_unsafe           __get_bst_left
#define get_bst_right_unsafe          __get_bst_right
#define get_bst_parent_unsafe         __get_bst_parent
#define get_aligned_bst_parent_unsafe __get_aligned_bst_parent

#define get_bst_left_const_unsafe           __get_bst_left_const
#define get_bst_right_const_unsafe          __get_bst_right_const
#define get_bst_parent_const_unsafe         __get_bst_parent_const
#define get_aligned_bst_parent_const_unsafe __get_aligned_bst_parent_const

#define set_bst_left_unsafe           __set_bst_left
#define set_bst_right_unsafe          __set_bst_right
#define set_bst_parent_unsafe         __set_bst_parent
#define set_aligned_bst_parent        __set_aligned_bst_parent

#define set_bst_parent_ref_unsafe             __set_bst_parent_ref
#define set_aligned_bst_parent_ref_unsafe     __set_aligned_bst_parent_ref

//////////////////////////////////////////////////////////////////////////
#define __get_bst_left_ref(node_ptr)   (&(node_ptr)->m_left_ptr)
#define __get_bst_right_ref(node_ptr)  (&(node_ptr)->m_right_ptr)
#define __get_bst_parent_ref(node_ptr) (&(node_ptr)->m_parent_ptr)


static SR_FORCE_INLINE st_bst_node_header_t* __get_bst_left(st_bst_node_header_t* PARAM_IN node_ptr)
{
	return node_ptr->m_left_ptr;
}

static SR_FORCE_INLINE const st_bst_node_header_t* __get_bst_left_const(const st_bst_node_header_t* PARAM_IN node_ptr)
{
	return __get_bst_left((st_bst_node_header_t*)node_ptr);
}

static SR_FORCE_INLINE void __set_bst_left(st_bst_node_header_t* PARAM_OUT node_ptr,
	st_bst_node_header_t* PARAM_IN left_ptr)
{
	node_ptr->m_left_ptr = left_ptr;
}

static SR_FORCE_INLINE st_bst_node_header_t* __get_bst_right(st_bst_node_header_t* PARAM_IN node_ptr)
{
	return node_ptr->m_right_ptr;
}
static SR_FORCE_INLINE const st_bst_node_header_t* __get_bst_right_const(const st_bst_node_header_t* PARAM_IN node_ptr)
{
	return __get_bst_right((st_bst_node_header_t*)node_ptr);
}

static SR_FORCE_INLINE void __set_bst_right(st_bst_node_header_t* PARAM_OUT node_ptr,
	st_bst_node_header_t* PARAM_IN right_ptr)
{
	node_ptr->m_right_ptr = right_ptr;
}

static SR_FORCE_INLINE st_bst_node_header_t* __get_bst_parent(st_bst_node_header_t* PARAM_IN node_ptr)
{
	return node_ptr->m_parent_ptr;
}

static SR_FORCE_INLINE const st_bst_node_header_t* __get_bst_parent_const(const st_bst_node_header_t* PARAM_IN node_ptr)
{
	return __get_bst_parent((st_bst_node_header_t*)node_ptr);
}


static SR_FORCE_INLINE void __set_bst_parent(st_bst_node_header_t* PARAM_OUT node_ptr,
	st_bst_node_header_t* PARAM_IN parent_ptr)
{
	node_ptr->m_parent_ptr = parent_ptr;
}



#define BST_ALIGNED_MASK(ALIGNED_BYTE_COUNT) (~((ALIGNED_BYTE_COUNT)-1))
#define BST_ALIGNED_LONG BST_ALIGNED_MASK(sizeof(unsigned long))

static SR_FORCE_INLINE st_bst_node_header_t* __get_aligned_bst_parent
	(st_bst_node_header_t* PARAM_IN node_ptr,
	reg_t aligned_mask)
{
	return (st_bst_node_header_t*)(((st_aligned_bst_node_header_t*)node_ptr)->m_parent_ptr & aligned_mask);
}

static SR_FORCE_INLINE void __set_aligned_bst_parent(st_bst_node_header_t* PARAM_OUT node_ptr,
	st_bst_node_header_t* PARAM_IN parent_ptr, reg_t aligned_mask)
{
	st_aligned_bst_node_header_t* aligned_node_ptr = (st_aligned_bst_node_header_t*)node_ptr;
	aligned_node_ptr->m_parent_ptr = 
		((ptr_t)parent_ptr & aligned_mask) | 
		(aligned_node_ptr->m_parent_ptr & (~aligned_mask));
}

static SR_FORCE_INLINE const st_bst_node_header_t* __get_aligned_bst_parent_const
(const st_bst_node_header_t* PARAM_IN node_ptr,
reg_t aligned_mask)
{
	return __get_aligned_bst_parent((st_bst_node_header_t*)node_ptr, aligned_mask);
}

#define __set_bst_parent_ref(parent_ptrptr, parent_ptr) \
	*(parent_ptrptr) = (parent_ptr);

#define __set_aligned_bst_parent_ref(parent_ptrptr, parent_ptr, aligned_mask) \
	*(parent_ptrptr) = ((ptr_t)parent_ptr & aligned_mask) |((*(parent_ptrptr)) & (~aligned_mask));










#endif	 //SUNRED_BST_NODE_H_
