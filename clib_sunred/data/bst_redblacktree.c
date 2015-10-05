//////////////////////////////////////
// bst_redblacktree.c
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "rbbstnode_define_clean.h"
#include "rbbstnode_define_declare.h"
#include "../include/data/sr_bst.h"
#include "bst_method.h"
#include "rbbst_add_template.c"
#include "rbbst_remove_template.c"
#include "iterator_bst_itr.c"
#include "bst_clean_template.c"
#include "bst_clone_template.c"
#include "bst_copy_template.c"

//static SR_INLINE 
result_t bst_rbtree_add_node(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT add_node_ptr,
	compare_bst_node_func     cmp,
	bst_node_ptr* PARAM_OUT   added_node_ptrptr)
{
	rbbst_node_ptr* root_ptrptr = covnode_ptrptr(root_node_ptrptr);
	rbbst_node_ptr  add_ptr     = covnode_ptr(add_node_ptr);
	rbbst_node_ptr  added_ptr   = null;
	result_t status;
	status = insert_rbbst_node(root_ptrptr, add_ptr, cmp, &added_ptr);
	if (added_node_ptrptr)
	{
		*added_node_ptrptr = recovnode_ptr(added_ptr);
	}
	return status;
}

//static SR_INLINE  
result_t bst_rbtree_remove(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT remove_node_ptr)
{
	rbbst_node_ptr* root_ptrptr = covnode_ptrptr(root_node_ptrptr);
	rbbst_node_ptr  remove_ptr  = covnode_ptr(remove_node_ptr);
	return 	  remove_rbbst_node(root_ptrptr, remove_ptr);
}

//static SR_INLINE 
result_t bst_rbtree_clear(bst_node_allocator_t*	PARAM_IN alloc_ptr,
	bst_node_ptr* PARAM_INOUT root_dec_ptrptr)
{
	tree_node_ptr* root_ptrptr = covnode_ptrptr(root_dec_ptrptr);
	return 	  clear_bst(alloc_ptr, root_ptrptr);
}

//static SR_INLINE 
result_t bst_rbtree_clone(bst_node_allocator_t*	PARAM_INOUT alloc_ptr,
	bst_node_ptr* PARAM_INOUT root_dec_ptrptr,
	const bst_node_ptr PARAM_IN other_root_ptr)
{
	tree_node_ptr* root_ptrptr = covnode_ptrptr(root_dec_ptrptr);
	return clone_bst(alloc_ptr, root_ptrptr, covnode_ptr(other_root_ptr));
}

result_t bst_rbtree_copy(
    struct st_bstree_header* PARAM_INOUT dec_tree_ptr,
	const struct st_bstree_header* PARAM_IN src_tree_ptr)
{
	return copy_bst(dec_tree_ptr, src_tree_ptr);
}


static iterator_method_t gbst_inorder_iterator =
{
	bst_inorder_init,
	null,
	null,
	bst_inorder_begin,
	bst_inorder_end,
	bst_inorder_increase,
	bst_inorder_decrease
};

static iterator_method_t gbst_posorder_iterator =
{
	bst_posorder_init,
	null,
	null,
	bst_posorder_begin,
	bst_posorder_end,
	bst_posorder_increase,
	null
};

static iterator_method_t gbst_preorder_iterator =
{
	bst_preorder_init,
	null,
	null,
	bst_preorder_begin,
	bst_preorder_end,
	bst_preorder_increase,
	null
};

const iterator_method_t* get_rbbst_inorder_iterator_method()
{
	return &gbst_inorder_iterator;
}

const iterator_method_t* get_rbbst_posorder_iterator_method()
{
	return &gbst_posorder_iterator;
}

const iterator_method_t* get_rbbst_preorder_iterator_method()
{
	return &gbst_preorder_iterator;
}


//#include "../clib_sunred_interal.h"
//void __init_sunred_lib_rbbst(clib_sunred_funcions_t* PARAM_INOUT lib_ptr)
//{
//	lib_ptr->rbbst_add        = bst_rbtree_add_node;
//	lib_ptr->rbbst_remove = bst_rbtree_remove;
//	lib_ptr->rbbst_clear      = bst_rbtree_clear;
//	lib_ptr->rbbst_clone      = bst_rbtree_clone;
//	lib_ptr->rbbst_copy       = bst_rbtree_copy;
//	lib_ptr->rbbst_inorder_iterator_method    = &gbst_inorder_iterator;
//	lib_ptr->rbbst_posorder_iterator_method = &gbst_posorder_iterator;
//	lib_ptr->rbbst_preorder_iterator_method  = &gbst_preorder_iterator;
//}


