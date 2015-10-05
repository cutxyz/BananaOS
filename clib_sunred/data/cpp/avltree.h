//////////////////////////////////////
// bst.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef CPP_SUNRED_BST_H_
#define CPP_SUNRED_BST_H_

#include "clib_sunred.h"

struct avltree_node_method_traits
{
	typedef bst_node link_type_t;

	static SR_INLINE link_type_t* init(link_type_t* PARAM_OUT node_ptr,
		link_type_t* PARAM_IN parent_ptr,
		link_type_t* PARAM_IN left_ptr,
		link_type_t* PARAM_IN right_ptr)
	{
		return ::bstnode_init(node_ptr, parent_ptr, left_ptr, right_ptr);
	}
	bst_node_ptr bst_max(bst_node_ptr PARAM_IN root_node_ptr);

	const bst_node_ptr bst_max_const(const bst_node_ptr PARAM_IN root_node_ptr);

	bst_node_ptr bst_min(bst_node_ptr PARAM_IN root_node_ptr);

	const bst_node_ptr bst_min_const(const bst_node_ptr PARAM_IN root_node_ptr);

	bst_node_ptr bst_find(
		bst_node_ptr PARAM_IN root_ptr,
		const bst_node_ptr PARAM_IN key_ptr,
		compare_bst_node_func cmp);

	const bst_node_ptr bst_find_const(
		const bst_node_ptr PARAM_IN root_ptr,
		const bst_node_ptr PARAM_IN key_ptr,
		compare_bst_node_func cmp);

	bst_node_ptr bst_find_near(
		bst_node_ptr PARAM_IN root_ptr,
		const bst_node_ptr PARAM_IN key_ptr,
		compare_bst_node_func cmp,
		int* PARAM_OUT last_cmp_result_ptr);

	const bst_node_ptr bst_find_near_const(
		const bst_node_ptr PARAM_IN root_ptr,
		const bst_node_ptr PARAM_IN key_ptr,
		compare_bst_node_func cmp,
		int* PARAM_OUT last_cmp_result_ptr);

	result_t bst_clear(bst_node_allocator_t*	PARAM_IN alloc_ptr,
		bst_node_ptr* PARAM_INOUT root_dec_ptrptr);

	result_t bst_clone(bst_node_allocator_t*	PARAM_INOUT alloc_ptr,
		bst_node_ptr* PARAM_INOUT root_dec_ptrptr,
		const bst_node_ptr PARAM_IN other_root_ptr);

	result_t bst_copy(struct st_bstree_header* PARAM_INOUT dec_tree_ptr,
		const struct st_bstree_header* PARAM_IN src_tree_ptr);
};

#endif	 //CPP_SUNRED_BST_H_
