//////////////////////////////////////
// bst_avltree.c
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "avlbstnode_define_clean.h"
#include "avlbstnode_define_declare.h"
//#include "bst.h"
#include "../include/data/sr_bst.h"
#include "avlbst_add_template.c"
#include "avlbst_remove_template.c"

//static SR_INLINE 
result_t bst_avltree_add_node(
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT add_node_ptr,
	compare_bst_node_func     cmp,
	bst_node_ptr* PARAM_OUT   added_node_ptrptr)
{
	avlbst_node_ptr* root_ptrptr = covnode_ptrptr(root_node_ptrptr);
	avlbst_node_ptr  add_ptr     = covnode_ptr(add_node_ptr);
	avlbst_node_ptr  added_ptr   = null;
	result_t status;
	status = insert_avlbst_node(root_ptrptr, add_ptr, cmp, &added_ptr);
	if (added_node_ptrptr)
	{
		*added_node_ptrptr = avlbst_to_bst_unsafe(added_ptr);
	}
	return status;
}

//static SR_INLINE  
result_t bst_avltree_remove (
	bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT remove_node_ptr)
{							   
	avlbst_node_ptr* root_ptrptr = covnode_ptrptr(root_node_ptrptr);
	avlbst_node_ptr  remove_ptr  = covnode_ptr(remove_node_ptr);
	return 	  remove_avlbst_node(root_ptrptr, remove_ptr);
}


//const bst_add_node_func		       avlbst_add         = avlbst_add;
//const bst_remove_node_func	   avlbst_remove  = bst_avltree_remove ;

//#include "../clib_sunred_interal.h"
//void __init_sunred_lib_avlbst(clib_sunred_funcions_t* PARAM_INOUT lib_ptr)
//{
//	lib_ptr->avlbst_add         = avlbst_add;
//	lib_ptr->avlbst_remove = bst_avltree_remove;
//}



