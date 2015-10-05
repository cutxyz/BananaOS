//////////////////////////////////////
// bst_common.c
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "bstnode_define_clean.h"
#include "bstnode_define_declare.h"

#include "../include/data/sr_bst.h"
#include "bst_method.h"
#include "bst_init_template.c"
#include "bst_minmax_template.c"
#include "bst_find_template.c"
#include "iterator_bst_itr.c"
#include "bst_clean_template.c"
#include "bst_clone_template.c"
#include "bst_copy_template.c"

//static SR_INLINE 
bst_node_ptr bstnode_init(
	bst_node_ptr PARAM_OUT node_ptr,
	bst_node_ptr PARAM_IN parent_ptr,
	bst_node_ptr PARAM_IN left_ptr,
	bst_node_ptr PARAM_IN right_ptr)
{
	if (node_ptr)
	{
		return init_bst_node_unsafe(node_ptr,
			parent_ptr, left_ptr, right_ptr);
	}
	else
	{
		return null;
	}
}

tree_node_ptr bst_max(tree_node_ptr PARAM_IN root_node_ptr)
{
	return get_bst_max_node(root_node_ptr);
}

const tree_node_ptr bst_max_const(const tree_node_ptr PARAM_IN root_node_ptr)
{
	return get_bst_max_node_const(root_node_ptr);
}

tree_node_ptr bst_min(tree_node_ptr PARAM_IN root_node_ptr)
{
	return get_bst_min_node(root_node_ptr);
}

const tree_node_ptr bst_min_const(const tree_node_ptr PARAM_IN root_node_ptr)
{
	return get_bst_min_node_const(root_node_ptr);
}

tree_node_ptr bst_find (tree_node_ptr PARAM_IN root_ptr,
	const tree_node_ptr PARAM_IN key_ptr,
	cmpfunc_type compareto)
{
	return find_bst_node(root_ptr, key_ptr, compareto);
}

const tree_node_ptr bst_find_const (const tree_node_ptr PARAM_IN root_ptr,
	const tree_node_ptr PARAM_IN key_ptr,
	cmpfunc_type compareto)
{
	return find_bst_node_const(root_ptr, key_ptr, compareto);
}

tree_node_ptr bst_find_near (tree_node_ptr PARAM_IN root_ptr,
	const tree_node_ptr PARAM_IN key_ptr,
	cmpfunc_type compareto,
	int* PARAM_OUT last_cmp_result_ptr)
{
	return find_bst_near_node(root_ptr, key_ptr, compareto, last_cmp_result_ptr);
}

const tree_node_ptr bst_find_near_const(const tree_node_ptr PARAM_IN root_ptr,
	const tree_node_ptr PARAM_IN key_ptr,
	cmpfunc_type compareto,
	int* PARAM_OUT last_cmp_result_ptr)
{
	return find_bst_near_node_const(root_ptr, key_ptr, compareto, last_cmp_result_ptr);
}

result_t bst_clear(bst_node_allocator_t*	PARAM_IN alloc_ptr,
	tree_node_ptr* PARAM_INOUT root_dec_ptrptr)
{
	return clear_bst(alloc_ptr, root_dec_ptrptr);
}

result_t bst_clone(bst_node_allocator_t*	PARAM_INOUT alloc_ptr,
	tree_node_ptr* PARAM_INOUT root_dec_ptrptr,
	const tree_node_ptr PARAM_IN other_root_ptr)
{
	return clone_bst(alloc_ptr, root_dec_ptrptr, other_root_ptr);
}

result_t bst_copy(
	bstree_header_t* PARAM_INOUT dec_tree_ptr,
	const bstree_header_t* PARAM_IN src_tree_ptr)
{
	return copy_bst(dec_tree_ptr, src_tree_ptr);
}

//#include "bstnode_define_close.h"




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

const iterator_method_t* get_inorder_iterator_method()
{
	return &gbst_inorder_iterator;
}

const iterator_method_t* get_posorder_iterator_method()
{
	return &gbst_posorder_iterator;
}

const iterator_method_t* get_preorder_iterator_method()
{
	return &gbst_preorder_iterator;
}



//const init_bst_node_linked_func     bst_init            = bst_node_init;
//const bst_max_node_func	            bst_max             = get_bst_max_node;
//const bst_max_node_const_func       bst_max_const       = get_bst_max_node_const;
//const bst_min_node_func			    bst_min             = get_bst_min_node;
//const bst_min_node_const_func	    bst_min_const       = get_bst_min_node_const;
//const bst_find_node_func			bst_find            = find_bst_node;
//const bst_find_node_const_func	    bst_find_const      = find_bst_node_const;
//const bst_find_near_node_func	    bst_find_near       = find_bst_near_node;
//const bst_find_near_node_const_func bst_find_near_const = find_bst_near_node_const;
//const bst_clear_func                bst_clear			= clear_bst;
//const clone_bst_func                bst_clone           = clone_bst;
//const copy_bstree_func              bst_copy            = copy_bst;

//#include "../clib_sunred_interal.h"
//void __init_sunred_lib_bst(clib_sunred_funcions_t* PARAM_INOUT lib_ptr)
//{
//	lib_ptr->bst_init = bstnode_init;
//	lib_ptr->bst_max                        = get_bst_max_node;
//	lib_ptr->bst_max_const           = get_bst_max_node_const;
//	lib_ptr->bst_min                         = get_bst_min_node;
//	lib_ptr->bst_min_const            = get_bst_min_node_const;
//	lib_ptr->bst_find                         = find_bst_node;
//	lib_ptr->bst_find_const            = find_bst_node_const;
//	lib_ptr->bst_find_near              = find_bst_near_node;
//	lib_ptr->bst_find_near_const = find_bst_near_node_const;
//	lib_ptr->bst_clear                       = clear_bst;
//	lib_ptr->bst_clone                      = clone_bst;
//	lib_ptr->bst_copy                       = copy_bst;
//	lib_ptr->bst_inorder_iterator_method    = &gbst_inorder_iterator;
//	lib_ptr->bst_posorder_iterator_method = &gbst_posorder_iterator;
//	lib_ptr->bst_preorder_iterator_method = &gbst_preorder_iterator;
//}
