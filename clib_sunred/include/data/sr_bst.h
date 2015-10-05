//////////////////////////////////////
// sr_bst.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef CLIB_SUNRED_BST_H_
#define CLIB_SUNRED_BST_H_

#include "../../data/bst_method.h"
#include "../../data/iterator.h"
#include "../../data/iterator_bst_itr.h"

#ifdef STATIC_LIB_OR_SHADOW_DLL_IMPORT

SR_EXTERN_C_BEGIN
// binary search tree
bst_node_ptr bstnode_init(
	bst_node_ptr PARAM_OUT node_ptr,
	bst_node_ptr PARAM_IN parent_ptr,
	bst_node_ptr PARAM_IN left_ptr,
	bst_node_ptr PARAM_IN right_ptr);

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

const iterator_method_t* get_inorder_iterator_method();

const iterator_method_t* get_posorder_iterator_method();

const iterator_method_t* get_preorder_iterator_method();

// avl-tree
result_t bst_avltree_add_node(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT add_node_ptr,
	compare_bst_node_func     cmp,
	bst_node_ptr* PARAM_OUT   added_node_ptrptr);

result_t bst_avltree_remove(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT remove_node_ptr);
// rb-tree
result_t bst_rbtree_add_node(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT add_node_ptr,
	compare_bst_node_func     cmp,
	bst_node_ptr* PARAM_OUT   added_node_ptrptr);
 
result_t bst_rbtree_remove(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT remove_node_ptr);

result_t bst_rbtree_clear(bst_node_allocator_t*	PARAM_IN alloc_ptr,
	bst_node_ptr* PARAM_INOUT root_dec_ptrptr);

result_t bst_rbtree_clone(bst_node_allocator_t*	PARAM_INOUT alloc_ptr,
	bst_node_ptr* PARAM_INOUT root_dec_ptrptr,
	const bst_node_ptr PARAM_IN other_root_ptr);

result_t bst_rbtree_copy(
    struct st_bstree_header* PARAM_INOUT dec_tree_ptr,
	const struct st_bstree_header* PARAM_IN src_tree_ptr);

const iterator_method_t* get_rbbst_inorder_iterator_method();
const iterator_method_t* get_rbbst_posorder_iterator_method();
const iterator_method_t* get_rbbst_preorder_iterator_method();

SR_EXTERN_C_END

#else

extern init_bst_node_linked_func       bstnode_init;
extern bst_max_node_func	           bst_max;
extern bst_max_node_const_func         bst_max_const;
extern bst_min_node_func			   bst_min;
extern bst_min_node_const_func	       bst_min_const;
extern bst_find_node_func			   bst_find;
extern bst_find_node_const_func        bst_find_const;
extern bst_find_near_node_func	       bst_find_near;
extern bst_find_near_node_const_func   bst_find_near_const;

extern bst_clear_func                  bst_clear;
extern clone_bst_func                  bst_clone;
extern copy_bstree_func                bst_copy;

extern get_iterator_method_func        get_inorder_iterator_method;
extern get_iterator_method_func        get_posorder_iterator_method;
extern get_iterator_method_func        get_preorder_iterator_method;

extern bst_add_node_func		       bst_avltree_add_node;
extern bst_remove_node_func	           bst_avltree_remove;

extern bst_add_node_func		       bst_rbtree_add_node;
extern bst_remove_node_func		       bst_rbtree_remove;
extern bst_clear_func                  bst_rbtree_clear;
extern clone_bst_func                  bst_rbtree_clone;
extern copy_bstree_func                bst_rbtree_copy;

extern get_iterator_method_func        get_rbbst_inorder_iterator_method;
extern get_iterator_method_func        get_rbbst_posorder_iterator_method;
extern get_iterator_method_func        get_rbbst_preorder_iterator_method;
#endif //STATIC_LIB_OR_SHADOW_DLL_IMPORT



#endif	 //CLIB_SUNRED_BST_H_
