//////////////////////////////////////
// bst.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef SUNRED_BST_H_
#define SUNRED_BST_H_

#include "bst_method.h"
#include "iterator.h"
#include "iterator_bst_itr.h"

typedef struct st_bstree_header
{
	bst_node_ptr           m_root_node_ptr;
	int                    m_size;
	compare_bst_node_func  m_cmp;
	bst_node_allocator_t   m_alloc;

	bst_add_node_func      add;
	bst_remove_node_func   remove;

	bst_clear_func         clean;
	clone_bst_func         clone;

	const iterator_method_t*     itr;
}bstree_header_t;


static SR_INLINE bst_node_ptr new_bsttree_node
	(bstree_header_t* PARAM_INOUT tree_ptr, 
	const bst_node_ptr copy_param_ptr)
{
	if (tree_ptr && tree_ptr->m_alloc.new_node)
	{
		return (bst_node_ptr)alloc_new_node
			(tree_ptr->m_alloc, copy_param_ptr);
	}
	else
	{
		return null;
	}
}

static SR_FORCE_INLINE result_t release_bsttree_node
	(bstree_header_t* PARAM_INOUT tree_ptr, 
		bst_node_ptr PARAM_INOUT relesae_node_ptr)
{
	if (tree_ptr && tree_ptr->m_alloc.release_node)
	{
		return dealloc_release_node
			(tree_ptr->m_alloc, relesae_node_ptr);
	}
	else
	{
		return STATUS_INVALID_PARAMS;
	}
}


static SR_FORCE_INLINE const bst_node_ptr get_bst_root
	(const bstree_header_t* PARAM_IN tree_ptr)
{
	if (tree_ptr)
	{
		return tree_ptr->m_root_node_ptr;
	}
	else
	{
		return null;
	}
}

static SR_FORCE_INLINE usize__t get_bst_size
	(const bstree_header_t* PARAM_IN tree_ptr)
{
	if (tree_ptr)
	{
		return tree_ptr->m_size;
	}
	else
	{
		return 0;
	}
}

static SR_FORCE_INLINE result_t add_bsttree_node
	(bstree_header_t* PARAM_INOUT tree_ptr,
	bst_node_ptr  PARAM_INOUT add_node_ptr,
	bst_node_ptr* PARAM_OUT   added_node_ptrptr)
{
	if (tree_ptr && tree_ptr->add)
	{
		result_t res = tree_ptr->add(&tree_ptr->m_root_node_ptr,
			add_node_ptr,
			tree_ptr->m_cmp,
			added_node_ptrptr);
		if (STATUS_OK == res)
		{
			++tree_ptr->m_size;
		}
		return res;
	}
	else
	{
		return STATUS_INVALID_PARAMS;
	}
}

static SR_FORCE_INLINE result_t remove_bsttree_node
	(bstree_header_t* PARAM_INOUT tree_ptr,
	bst_node_ptr  PARAM_INOUT remove_node_ptr)
{
	if (tree_ptr && tree_ptr->remove)
	{
		result_t res = tree_ptr->remove(&tree_ptr->m_root_node_ptr,
			remove_node_ptr);
		if (STATUS_OK == res && tree_ptr->m_size > 0)
		{
			--tree_ptr->m_size;
		}
		return res;
	}
	else
	{
		return STATUS_INVALID_PARAMS;
	}
}


static SR_FORCE_INLINE result_t clean_bsttree_node
	(bstree_header_t* PARAM_INOUT tree_ptr)
{
	if (tree_ptr && tree_ptr->clean)
	{
		return tree_ptr->clean(&tree_ptr->m_alloc, 
			&tree_ptr->m_root_node_ptr);
	}
	else
	{
		return STATUS_INVALID_PARAMS;
	}
}

static SR_FORCE_INLINE result_t clone_bsttree_node
	(bstree_header_t* PARAM_INOUT tree_ptr, 
	const bstree_header_t* PARAM_IN other_tree_ptr)
{
	if (tree_ptr && tree_ptr->clone)
	{
		return tree_ptr->clone(&tree_ptr->m_alloc, 
			&tree_ptr->m_root_node_ptr, 
			other_tree_ptr->m_root_node_ptr);
	}
	else
	{
		return STATUS_INVALID_PARAMS;
	}
}



#endif	 //SUNRED_BST_H_
