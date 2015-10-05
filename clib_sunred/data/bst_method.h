//////////////////////////////////////
// bst_method.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef SUNRED_BST_METHOD_H_
#define SUNRED_BST_METHOD_H_

#include "compareto.h"
#include "bst_node.h"
#include "rbbst_node.h"
#include "avlbst_node.h"
#include "bst_new_release_node.h"

typedef  compare_to_func  compare_bst_node_func;

typedef bst_node_ptr(*init_bst_node_linked_func)(
	bst_node_ptr PARAM_OUT node_ptr,
	bst_node_ptr PARAM_IN parent_ptr,
	bst_node_ptr PARAM_IN left_ptr,
	bst_node_ptr PARAM_IN right_ptr);

typedef bst_node_ptr(*bst_max_node_func)(bst_node_ptr PARAM_IN root_node_ptr);

typedef const bst_node_ptr(*bst_max_node_const_func)(const bst_node_ptr PARAM_IN root_node_ptr);

typedef bst_node_ptr(*bst_min_node_func)(bst_node_ptr PARAM_IN root_node_ptr);

typedef const bst_node_ptr(*bst_min_node_const_func)(const bst_node_ptr PARAM_IN root_node_ptr);

typedef bst_node_ptr(*bst_find_node_func)(
	bst_node_ptr PARAM_IN root_ptr,
	const bst_node_ptr PARAM_IN key_ptr,
	compare_bst_node_func cmp);

typedef const bst_node_ptr(*bst_find_node_const_func)(
	const bst_node_ptr PARAM_IN root_ptr,
	const bst_node_ptr PARAM_IN key_ptr,
	compare_bst_node_func cmp);

typedef bst_node_ptr(*bst_find_near_node_func)(
	bst_node_ptr PARAM_IN root_ptr,
	const bst_node_ptr PARAM_IN key_ptr,
	compare_bst_node_func cmp,
	int* PARAM_OUT last_cmp_result_ptr);

typedef const bst_node_ptr(*bst_find_near_node_const_func)(
	const bst_node_ptr PARAM_IN root_ptr,
	const bst_node_ptr PARAM_IN key_ptr,
	compare_bst_node_func cmp,
	int* PARAM_OUT last_cmp_result_ptr);

typedef result_t(*bst_add_node_func)(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT add_node_ptr,
	compare_bst_node_func     cmp,
	bst_node_ptr* PARAM_OUT   added_node_ptrptr);

typedef result_t(*bst_remove_node_func)(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT remove_node_ptr);

typedef result_t(*bst_clear_func)(bst_node_allocator_t*	PARAM_IN alloc_ptr,
	bst_node_ptr* PARAM_INOUT root_dec_ptrptr);

typedef result_t(*clone_bst_func)(bst_node_allocator_t*	PARAM_INOUT alloc_ptr,
	bst_node_ptr* PARAM_INOUT root_dec_ptrptr,
	const bst_node_ptr PARAM_IN other_root_ptr);

typedef result_t(*copy_bstree_func)(
	struct st_bstree_header* PARAM_INOUT dec_tree_ptr,
	const struct st_bstree_header* PARAM_IN src_tree_ptr);


#endif	 //SUNRED_BST_METHOD_H_
