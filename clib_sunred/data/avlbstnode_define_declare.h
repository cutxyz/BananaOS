//////////////////////////////////////
// bst_define_begin.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "avlbst_node.h"

#ifndef tree_node
#define tree_node             avlbst_node
#endif//tree_node

#ifndef tree_node_ptr
#define tree_node_ptr         avlbst_node_ptr
#endif// tree_node_ptr

#ifndef covnode_ptrptr 
#define covnode_ptrptr        __bstptr_to_avlbstptr
#endif//covnode_ptrptr        
					          
#ifndef covnode_ptr           
#define covnode_ptr           bst_to_avlbst_unsafe
#endif//covnode_ptr	          
					          
#ifndef recovnode_ptr         
#define recovnode_ptr         avlbst_to_bst_unsafe
#endif//recovnode_ptr


#ifndef get_tree_height
#define get_tree_height		  get_avlbst_height
#endif//get_tree_height

#ifndef set_tree_height
#define set_tree_height		  set_avlbst_height_unsafe
#endif//set_tree_height


#ifndef set_tree_left
#define set_tree_left         set_avlbst_left_unsafe
#endif//set_tree_left

#ifndef set_tree_right
#define set_tree_right        set_avlbst_right_unsafe
#endif//set_tree_right

#ifndef set_tree_parent
#define set_tree_parent       set_avlbst_parent_unsafe
#endif//set_tree_parent

#ifndef set_tree_parent_ref
#define set_tree_parent_ref   set_avlbst_parent_ref_unsafe
#endif//set_tree_parent_ref

#ifndef get_tree_left_ref
#define get_tree_left_ref     get_avlbst_left_ref_unsafe
#endif//get_tree_left_ref

#ifndef get_tree_right_ref
#define get_tree_right_ref    get_avlbst_right_ref_unsafe
#endif//get_tree_right_ref

#ifndef get_tree_left
#define get_tree_left         get_avlbst_left_unsafe
#endif//get_tree_left

#ifndef get_tree_right
#define get_tree_right        get_avlbst_right_unsafe
#endif//get_tree_right

#ifndef get_tree_parent
#define get_tree_parent       get_avlbst_parent_unsafe
#endif//get_tree_parent

#ifndef get_tree_const_left
#define get_tree_const_left   get_avlbst_left_const_unsafe
#endif//get_tree_const_left

#ifndef get_tree_const_right
#define get_tree_const_right  get_avlbst_right_const_unsafe
#endif//get_tree_const_right

#ifndef get_tree_const_parent
#define get_tree_const_parent get_avlbst_parent_const_unsafe
#endif//get_tree_const_parent




