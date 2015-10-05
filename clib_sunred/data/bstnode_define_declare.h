//////////////////////////////////////
// bst_define_begin.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bst_node.h"

#ifndef tree_node
#define tree_node             bst_node
#endif//tree_node

#ifndef tree_node_ptr
#define tree_node_ptr         bst_node_ptr
#endif//tree_node_ptr

#ifndef covnode_ptrptr 
#define covnode_ptrptr(x)  (x)
#endif//covnode_ptrptr

#ifndef covnode_ptr 
#define covnode_ptr(x)  (x)
#endif//covnode_ptr

#ifndef recovnode_ptr 
#define recovnode_ptr(x)  (x)
#endif//recovnode_ptr

#ifndef set_tree_left
#define set_tree_left         set_bst_left_unsafe
#endif//set_tree_left

#ifndef set_tree_right
#define set_tree_right        set_bst_right_unsafe
#endif//set_tree_right

#ifndef set_tree_parent
#define set_tree_parent       set_bst_parent_unsafe
#endif//set_tree_parent

#ifndef get_tree_left
#define get_tree_left         get_bst_left_unsafe
#endif//get_tree_left

#ifndef get_tree_right
#define get_tree_right        get_bst_right_unsafe
#endif//get_tree_right

#ifndef get_tree_parent
#define get_tree_parent       get_bst_parent_unsafe
#endif//get_tree_parent

#ifndef get_tree_const_left
#define get_tree_const_left   get_bst_left_const_unsafe
#endif//get_tree_const_left

#ifndef get_tree_const_right
#define get_tree_const_right  get_bst_right_const_unsafe
#endif//get_tree_const_right

#ifndef get_tree_const_parent
#define get_tree_const_parent get_bst_parent_const_unsafe
#endif//get_tree_const_parent




