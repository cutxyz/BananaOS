//////////////////////////////////////
// bst_define_begin.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "rbbst_node.h"

#ifndef tree_node
#define tree_node             rbbst_node
#endif//tree_node

#ifndef covnode_ptrptr 
#define covnode_ptrptr __bstptr_to_rbbstptr
#endif//covnode_ptrptr

#ifndef covnode_ptr 
#define covnode_ptr    bst_to_rbbst_unsafe
#endif//covnode_ptr

#ifndef recovnode_ptr 
#define recovnode_ptr  rbbst_to_bst_unsafe
#endif//recovnode_ptr



#ifndef tree_node_ptr
#define tree_node_ptr         rbbst_node_ptr
#endif// tree_node_ptr

#ifndef get_tree_color
#define get_tree_color		  get_rbbst_color_unsafe
#endif//get_tree_color

#ifndef set_tree_color
#define set_tree_color		  set_rbbst_color_unsafe
#endif//set_tree_color

#ifndef set_tree_blackcolor
#define set_tree_blackcolor	  rbbst_set_to_black_color_unsafe
#endif//set_tree_blackcolor

#ifndef set_tree_redcolor
#define set_tree_redcolor	  rbbst_set_to_red_color_unsafe
#endif//set_tree_redcolor

#ifndef check_tree_blackcolor
#define check_tree_blackcolor rbbst_check_black_color
#endif//check_tree_blackcolor

#ifndef check_tree_redcolor
#define check_tree_redcolor	  rbbst_check_red_color
#endif//check_tree_redcolor


#ifndef set_tree_left
#define set_tree_left         set_rbbst_left_unsafe
#endif//set_tree_left

#ifndef set_tree_right
#define set_tree_right        set_rbbst_right_unsafe
#endif//set_tree_right

#ifndef set_tree_parent
#define set_tree_parent       set_rbbst_parent_unsafe
#endif//set_tree_parent

#ifndef get_tree_left
#define get_tree_left         get_rbbst_left_unsafe
#endif//get_tree_left

#ifndef get_tree_right
#define get_tree_right        get_rbbst_right_unsafe
#endif//get_tree_right

#ifndef get_tree_parent
#define get_tree_parent       get_rbbst_parent_unsafe
#endif//get_tree_parent

#ifndef get_tree_const_left
#define get_tree_const_left   get_rbbst_left_const_unsafe
#endif//get_tree_const_left

#ifndef get_tree_const_right
#define get_tree_const_right  get_rbbst_right_const_unsafe
#endif//get_tree_const_right

#ifndef get_tree_const_parent
#define get_tree_const_parent get_rbbst_parent_const_unsafe
#endif//get_tree_const_parent




