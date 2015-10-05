//////////////////////////////////////
// avlbst_node.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef SUNRED_AVL_BST_NODE_H_
#define SUNRED_AVL_BST_NODE_H_

#include "bst_node.h"


typedef struct st_avl_bst_node_header
{
	st_bst_node_header_t m_bst_header;
	nsize__t             m_height;
}st_avl_bst_node_header_t;

//AVL旋转类型
typedef enum enumAVLTREE_ROTATE_TYPE
{
	AVLTREE_NONE_ROTATE = 0,
	AVLTREE_LL_ROTATE,
	AVLTREE_RR_ROTATE,
	AVLTREE_RL_ROTATE,
	AVLTREE_LR_ROTATE,
	AVLTREE_ROTATE_ERR,
	AVLTREE_NOT_SIMPLE_ROTATE,
	AVLTREE_ROTATE_TYPE_COUNT
}AVLTREE_ROTATE_t;

#define avlbst_node              st_avl_bst_node_header_t
#define _avlbst_node_ptr         struct st_avl_bst_node_header*
#define constavlbst_node_ptr 	 const struct st_avl_bst_node_header*
#define avlbst_node_ptr          struct st_avl_bst_node_header*

// 左值操作右值操作均OK的get函数
#define get_avlbst_left_ref_unsafe   __get_avlbst_left_ref  
#define get_avlbst_right_ref_unsafe  __get_avlbst_right_ref 
#define get_avlbst_parent_ref_unsafe __get_avlbst_parent_ref

// 左值操作的get函数
#define get_avlbst_height_unsafe		 __get_avl_height
#define get_avlbst_height		         get_avl_height
#define set_avlbst_height_unsafe         __set_avl_height

#define get_avlbst_left_unsafe           __get_avlbst_left
#define get_avlbst_right_unsafe          __get_avlbst_right
#define get_avlbst_parent_unsafe         __get_avlbst_parent

#define get_avlbst_left_const_unsafe     __get_avlbst_left_const
#define get_avlbst_right_const_unsafe    __get_avlbst_right_const
#define get_avlbst_parent_const_unsafe   __get_avlbst_parent_const

#define set_avlbst_left_unsafe           __set_avlbst_left
#define set_avlbst_right_unsafe          __set_avlbst_right
#define set_avlbst_parent_unsafe         __set_avlbst_parent

#define avlbst_to_bst_unsafe 			__avlbst_to_bst
#define bst_to_avlbst_unsafe			__bst_to_avlbst

#define set_avlbst_parent_ref_unsafe    set_bst_parent_ref_unsafe         


//////////////////////////////////////////////////////////////////////////

#define __avlbst_to_bst(node_ptr)	(&((node_ptr)->m_bst_header))
#define __bst_to_avlbst(node_ptr)   (st_avl_bst_node_header_t*)(node_ptr)
#define __bstptr_to_avlbstptr(node_ptrptr)   (st_avl_bst_node_header_t**)(node_ptrptr)

#define __get_avlbst_left_ref(node_ptr)   __bstptr_to_avlbstptr(__get_bst_left_ref  (&((node_ptr)->m_bst_header)))
#define __get_avlbst_right_ref(node_ptr)  __bstptr_to_avlbstptr(__get_bst_right_ref (&((node_ptr)->m_bst_header)))
#define __get_avlbst_parent_ref(node_ptr) __bstptr_to_avlbstptr(__get_bst_parent_ref(&((node_ptr)->m_bst_header)))






static SR_FORCE_INLINE st_avl_bst_node_header_t* __get_avlbst_left(st_avl_bst_node_header_t* PARAM_IN node_ptr)
{
	return bst_to_avlbst_unsafe(get_bst_left_unsafe(&node_ptr->m_bst_header));
}

static SR_FORCE_INLINE const st_avl_bst_node_header_t* __get_avlbst_left_const(const st_avl_bst_node_header_t* PARAM_IN node_ptr)
{
	return __get_avlbst_left((st_avl_bst_node_header_t*)node_ptr);
}

static SR_FORCE_INLINE void __set_avlbst_left(st_avl_bst_node_header_t* PARAM_OUT node_ptr,
	st_avl_bst_node_header_t* PARAM_IN left_ptr)
{
	set_bst_left_unsafe(&node_ptr->m_bst_header, &left_ptr->m_bst_header);
}

static SR_FORCE_INLINE st_avl_bst_node_header_t* __get_avlbst_right(st_avl_bst_node_header_t* PARAM_IN node_ptr)
{
	return bst_to_avlbst_unsafe(get_bst_right_unsafe(&node_ptr->m_bst_header));
}
static SR_FORCE_INLINE const st_avl_bst_node_header_t* __get_avlbst_right_const(const st_avl_bst_node_header_t* PARAM_IN node_ptr)
{
	return __get_avlbst_right((st_avl_bst_node_header_t*)node_ptr);
}

static SR_FORCE_INLINE void __set_avlbst_right(st_avl_bst_node_header_t* PARAM_OUT node_ptr,
	st_avl_bst_node_header_t* PARAM_IN right_ptr)
{
	set_bst_right_unsafe(&node_ptr->m_bst_header, &right_ptr->m_bst_header);
}

static SR_FORCE_INLINE st_avl_bst_node_header_t* __get_avlbst_parent(st_avl_bst_node_header_t* PARAM_IN node_ptr)
{
	return bst_to_avlbst_unsafe(get_bst_parent_unsafe(&node_ptr->m_bst_header));
}

static SR_FORCE_INLINE const st_avl_bst_node_header_t* __get_avlbst_parent_const(const st_avl_bst_node_header_t* PARAM_IN node_ptr)
{
	return __get_avlbst_parent((st_avl_bst_node_header_t*)node_ptr);
}


static SR_FORCE_INLINE void __set_avlbst_parent(st_avl_bst_node_header_t* PARAM_OUT node_ptr,
	st_avl_bst_node_header_t* PARAM_IN parent_ptr)
{
	set_bst_parent_unsafe(&node_ptr->m_bst_header, &parent_ptr->m_bst_header);
}

static SR_FORCE_INLINE nsize__t get_avl_height(const avlbst_node_ptr PARAM_IN node_ptr)
{
	nsize__t height_value = -1;
	if (node_ptr)
	{
		height_value = node_ptr->m_height;
	}
	return height_value;
}

static SR_FORCE_INLINE nsize__t __get_avl_height(const avlbst_node_ptr PARAM_IN node_ptr)
{
	return node_ptr->m_height;
}

static SR_FORCE_INLINE void __set_avl_height(avlbst_node_ptr PARAM_OUT node_ptr,
	nsize__t height)
{
	node_ptr->m_height = height;
}


#endif	 //SUNRED_BST_NODE_H_
