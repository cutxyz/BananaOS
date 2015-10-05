//////////////////////////////////////
// bst_init_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bstnode_define_declare.h"

#ifndef init_bst_node_unsafe
//////////////////////////////////////////////////////////////////////////
// 初始化节点连接
static SR_FORCE_INLINE tree_node_ptr __init_bst_node_linked(
	tree_node_ptr PARAM_OUT node_ptr,
	tree_node_ptr PARAM_IN left_ptr,
	tree_node_ptr PARAM_IN right_ptr,
	tree_node_ptr PARAM_IN parent_ptr)
{
	set_tree_left  (node_ptr, left_ptr);
	set_tree_right (node_ptr, right_ptr);
	set_tree_parent(node_ptr, parent_ptr);
	return node_ptr;
}
#define init_bst_node_unsafe __init_bst_node_linked		 

#endif	//init_bst_node_unsafe







