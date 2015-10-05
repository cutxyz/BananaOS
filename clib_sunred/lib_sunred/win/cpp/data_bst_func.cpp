//////////////////////////////////////
// dlllib_sunred.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "clib_sunred.h"
#include < Windows.h >
#define _STR_(X) X

init_bst_node_linked_func       bstnode_init = NULL;
bst_max_node_func	            bst_max = NULL;
bst_max_node_const_func         bst_max_const = NULL;
bst_min_node_func			    bst_min = NULL;
bst_min_node_const_func	        bst_min_const = NULL;
bst_find_node_func			    bst_find = NULL;
bst_find_node_const_func	    bst_find_const = NULL;
bst_find_near_node_func	        bst_find_near = NULL;
bst_find_near_node_const_func   bst_find_near_const = NULL;

bst_clear_func                  bst_clear = NULL;
clone_bst_func                  bst_clone = NULL;
copy_bstree_func                bst_copy = NULL;

get_iterator_method_func        get_inorder_iterator_method = NULL;
get_iterator_method_func        get_posorder_iterator_method = NULL;
get_iterator_method_func        get_preorder_iterator_method = NULL;

bst_add_node_func		        bst_avltree_add_node = NULL;
bst_remove_node_func	        bst_avltree_remove = NULL;

bst_add_node_func		        bst_rbtree_add_node = NULL;
bst_remove_node_func		    bst_rbtree_remove = NULL;
bst_clear_func                  bst_rbtree_clear = NULL;
clone_bst_func                  bst_rbtree_clone = NULL;
copy_bstree_func                bst_rbtree_copy = NULL;

get_iterator_method_func        get_rbbst_inorder_iterator_method = NULL;
get_iterator_method_func        get_rbbst_posorder_iterator_method = NULL;
get_iterator_method_func        get_rbbst_preorder_iterator_method = NULL;

int load_data_bst_funcs(HMODULE dlllib)
{
	int status;
	if (NULL == dlllib)
	{
		return STATUS_INVALID_PARAMS;
	}

	status = STATUS_ERROR_;
	DO_ONE_LOOP_BEGIN
		
	bstnode_init = (init_bst_node_linked_func)GetProcAddress(dlllib, _STR_("bstnode_init"));
	BREAK_LOOP_CONDITION(NULL == bstnode_init);

	bst_max = (bst_max_node_func)GetProcAddress(dlllib, _STR_("bst_max"));
	BREAK_LOOP_CONDITION(NULL == bst_max);

	bst_max_const = (bst_max_node_const_func)GetProcAddress(dlllib, _STR_("bst_max_const"));
	BREAK_LOOP_CONDITION(NULL == bst_max_const);

	bst_min = (bst_min_node_func)GetProcAddress(dlllib, _STR_("bst_min"));
	BREAK_LOOP_CONDITION(NULL == bst_min);

	bst_min_const = (bst_min_node_const_func)GetProcAddress(dlllib, _STR_("bst_min_const"));
	BREAK_LOOP_CONDITION(NULL == bst_min_const);

	bst_find = (bst_find_node_func)GetProcAddress(dlllib, _STR_("bst_find"));
	BREAK_LOOP_CONDITION(NULL == bst_find);

	bst_find_const = (bst_find_node_const_func)GetProcAddress(dlllib, _STR_("bst_find_const"));
	BREAK_LOOP_CONDITION(NULL == bst_find_const);

	bst_find_near = (bst_find_near_node_func)GetProcAddress(dlllib, _STR_("bst_find_near"));
	BREAK_LOOP_CONDITION(NULL == bst_find_near);

	bst_find_near_const = (bst_find_near_node_const_func)GetProcAddress(dlllib, _STR_("bst_find_near_const"));
	BREAK_LOOP_CONDITION(NULL == bst_find_near_const);

	bst_clear = (bst_clear_func)GetProcAddress(dlllib, _STR_("bst_clear"));
	BREAK_LOOP_CONDITION(NULL == bst_clear);

	bst_clone = (clone_bst_func)GetProcAddress(dlllib, _STR_("bst_clone"));
	BREAK_LOOP_CONDITION(NULL == bst_clone);

	bst_copy = (copy_bstree_func)GetProcAddress(dlllib, _STR_("bst_copy"));
	BREAK_LOOP_CONDITION(NULL == bst_copy);

	get_inorder_iterator_method = (get_iterator_method_func)GetProcAddress(dlllib, _STR_("get_inorder_iterator_method"));
	BREAK_LOOP_CONDITION(NULL == get_inorder_iterator_method);

	get_posorder_iterator_method = (get_iterator_method_func)GetProcAddress(dlllib, _STR_("get_posorder_iterator_method"));
	BREAK_LOOP_CONDITION(NULL == get_posorder_iterator_method);

	get_preorder_iterator_method = (get_iterator_method_func)GetProcAddress(dlllib, _STR_("get_preorder_iterator_method"));
	BREAK_LOOP_CONDITION(NULL == get_preorder_iterator_method);

	bst_avltree_add_node = (bst_add_node_func)GetProcAddress(dlllib, _STR_("bst_avltree_add_node"));
	BREAK_LOOP_CONDITION(NULL == bst_avltree_add_node);

	bst_avltree_remove = (bst_remove_node_func)GetProcAddress(dlllib, _STR_("bst_avltree_remove"));
	BREAK_LOOP_CONDITION(NULL == bst_avltree_remove);

	bst_rbtree_add_node = (bst_add_node_func)GetProcAddress(dlllib, _STR_("bst_rbtree_add_node"));
	BREAK_LOOP_CONDITION(NULL == bst_rbtree_add_node);

	bst_rbtree_remove = (bst_remove_node_func)GetProcAddress(dlllib, _STR_("bst_rbtree_remove"));
	BREAK_LOOP_CONDITION(NULL == bst_rbtree_remove);

	bst_rbtree_clear = (bst_clear_func)GetProcAddress(dlllib, _STR_("bst_rbtree_clear"));
	BREAK_LOOP_CONDITION(NULL == bst_rbtree_clear);

	bst_rbtree_clone = (clone_bst_func)GetProcAddress(dlllib, _STR_("bst_rbtree_clone"));
	BREAK_LOOP_CONDITION(NULL == bst_rbtree_clone);

	bst_rbtree_copy = (copy_bstree_func)GetProcAddress(dlllib, _STR_("bst_rbtree_copy"));
	BREAK_LOOP_CONDITION(NULL == bst_rbtree_copy);
	
	get_rbbst_inorder_iterator_method = (get_iterator_method_func)GetProcAddress(dlllib, _STR_("get_rbbst_inorder_iterator_method"));
	BREAK_LOOP_CONDITION(NULL == get_rbbst_inorder_iterator_method);

	get_rbbst_posorder_iterator_method = (get_iterator_method_func)GetProcAddress(dlllib, _STR_("get_rbbst_posorder_iterator_method"));
	BREAK_LOOP_CONDITION(NULL == get_rbbst_posorder_iterator_method);

	get_rbbst_preorder_iterator_method = (get_iterator_method_func)GetProcAddress(dlllib, _STR_("get_rbbst_preorder_iterator_method"));
	BREAK_LOOP_CONDITION(NULL == get_rbbst_preorder_iterator_method);

	status = STATUS_OK;
	DO_ONE_LOOP_END
	return status;

}

void clean_data_bst_funcs()
{
	bstnode_init = NULL;
	bst_max = NULL;
	bst_max_const = NULL;
	bst_min = NULL;
	bst_min_const = NULL;
	bst_find = NULL;
	bst_find_const = NULL;
	bst_find_near = NULL;
	bst_find_near_const = NULL;

	bst_clear = NULL;
	bst_clone = NULL;
	bst_copy = NULL;

	get_inorder_iterator_method = NULL;
	get_posorder_iterator_method = NULL;
	get_preorder_iterator_method = NULL;

	bst_avltree_add_node = NULL;
	bst_avltree_remove = NULL;

	bst_rbtree_add_node = NULL;
	bst_rbtree_remove = NULL;
	bst_rbtree_clear = NULL;
	bst_rbtree_clone = NULL;
	bst_rbtree_copy = NULL;

	get_rbbst_inorder_iterator_method = NULL;
	get_rbbst_posorder_iterator_method = NULL;
	get_rbbst_preorder_iterator_method = NULL;
}

