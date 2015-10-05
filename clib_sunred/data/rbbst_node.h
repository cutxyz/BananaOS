//////////////////////////////////////
// rbbst_node.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef SUNRED_RB_BST_NODE_H_
#define SUNRED_RB_BST_NODE_H_

#include "bst_node.h"

// 注意：该黑红树必须的节点地址必须至少满足2字节
//      对齐否则无法使用，一般建议使用4字节对齐
// 黑红树节点通过根节点的最低位保存颜色值

#define RBBSTNODE_ALIGNED_SIZE 4

typedef ALIGNED_VARIABLE_ATTRIBUTE(RBBSTNODE_ALIGNED_SIZE,
	st_bst_node_header_t
)
st_rbbst_node_header_t;

typedef enum REDBLACK_TREE_COLOR
{
    BLACK_COLOR_NODE =0,
	RED_COLOR_NODE   =1
}REDBLACK_TREE_COLOR_t;

#define RB_COLOR_MASK    (1<<0)
#define RB_NODE_MASK     (~(RB_COLOR_MASK))

#define rbbst_node              st_rbbst_node_header_t
#define _rbbst_node_ptr         st_rbbst_node_header_t*
#define constrbbst_node_ptr 	const st_rbbst_node_header_t*
#define rbbst_node_ptr          st_rbbst_node_header_t*

#define rbbst_check_black_color         is_rbt_color_black
#define rbbst_check_red_color           is_rbt_color_red
#define rbbst_set_to_red_color_unsafe   __set_rbt_color_red
#define rbbst_set_to_black_color_unsafe __set_rbt_color_black

#define get_rbbst_color_unsafe          __get_rbt_color
#define set_rbbst_color_unsafe          __set_rbt_color

// 左值操作右值操作均OK的get函数
#define get_rbbst_left_ref_unsafe            __get_bst_left_ref  
#define get_rbbst_right_ref_unsafe           __get_bst_right_ref 
#define get_rbbst_parent_ref_unsafe          __get_bst_parent_ref

// 左值操作的get函数
#define get_rbbst_left_unsafe                get_bst_left_unsafe  
#define get_rbbst_right_unsafe               get_bst_right_unsafe 
#define get_rbbst_parent_unsafe(ptr)         get_aligned_bst_parent_unsafe(ptr, RB_NODE_MASK)

#define get_rbbst_left_const_unsafe          get_bst_left_const_unsafe  
#define get_rbbst_right_const_unsafe         get_bst_right_const_unsafe 
#define get_rbbst_parent_const_unsafe(ptr)   get_aligned_bst_parent_const_unsafe(ptr, RB_NODE_MASK)

#define set_rbbst_left_unsafe                set_bst_left_unsafe  
#define set_rbbst_right_unsafe               set_bst_right_unsafe 
#define set_rbbst_parent_unsafe(ptr,set_ptr) set_aligned_bst_parent(ptr, set_ptr, RB_NODE_MASK)

#define rbbst_to_bst_unsafe(ptr) 			 (ptr)
#define bst_to_rbbst_unsafe(ptr)			 (ptr)
#define __bstptr_to_rbbstptr(node_ptrptr)    (node_ptrptr)

#define set_rbbst_parent_ref_unsafe          set_aligned_bst_parent_ref_unsafe  

// 
static SR_FORCE_INLINE void __set_rbt_color(rbbst_node_ptr PARAM_INOUT node_ptr, REDBLACK_TREE_COLOR_t color)
{
	st_aligned_bst_node_header_t* aligned_node_ptr = (st_aligned_bst_node_header_t*)node_ptr;
	aligned_node_ptr->m_parent_ptr =
		(aligned_node_ptr->m_parent_ptr & RB_NODE_MASK) |
		color;
}
static SR_FORCE_INLINE REDBLACK_TREE_COLOR_t __get_rbt_color(const rbbst_node_ptr PARAM_INOUT node_ptr)
{
	const st_aligned_bst_node_header_t* aligned_node_ptr = (const st_aligned_bst_node_header_t*)node_ptr;
	return (REDBLACK_TREE_COLOR_t)(aligned_node_ptr->m_parent_ptr & RB_COLOR_MASK);
}

static SR_FORCE_INLINE void __set_rbt_color_red (rbbst_node_ptr PARAM_INOUT node_ptr)
{
	st_aligned_bst_node_header_t* aligned_node_ptr = (st_aligned_bst_node_header_t*)node_ptr;
	aligned_node_ptr->m_parent_ptr =
		(aligned_node_ptr->m_parent_ptr & RB_NODE_MASK) |
		RED_COLOR_NODE;
}

static SR_FORCE_INLINE void __set_rbt_color_black (rbbst_node_ptr PARAM_INOUT node_ptr)
{
	st_aligned_bst_node_header_t* aligned_node_ptr = (st_aligned_bst_node_header_t*)node_ptr;
	aligned_node_ptr->m_parent_ptr =
		(aligned_node_ptr->m_parent_ptr & RB_NODE_MASK) |
		BLACK_COLOR_NODE;
}

static SR_FORCE_INLINE bool_t is_rbt_color_red (const rbbst_node_ptr PARAM_INOUT node_ptr)
{
	const st_aligned_bst_node_header_t* aligned_node_ptr;
	if (node_ptr)
	{
		return FALSE;
	}
	aligned_node_ptr = (const st_aligned_bst_node_header_t*)node_ptr;

	return (RED_COLOR_NODE == (aligned_node_ptr->m_parent_ptr & RB_COLOR_MASK));
}

static SR_FORCE_INLINE bool_t is_rbt_color_black(const rbbst_node_ptr PARAM_INOUT node_ptr)
{
	const st_aligned_bst_node_header_t* aligned_node_ptr;
	if (node_ptr)
	{
		return TRUE;
	}
	aligned_node_ptr = (const st_aligned_bst_node_header_t*)node_ptr;

	return (BLACK_COLOR_NODE == (aligned_node_ptr->m_parent_ptr & RB_COLOR_MASK));
}

#endif	 //SUNRED_RB_BST_NODE_H_


