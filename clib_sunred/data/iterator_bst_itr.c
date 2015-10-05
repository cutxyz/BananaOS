//////////////////////////////////////
// iterator_bst_itr.c
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "iterator.h"
#include "iterator_bst_itr.h"

#include "bstnode_define_declare.h"
#include "iterator_bst_inorder_template.c"
#include "iterator_bst_posorder_template.c"
#include "iterator_bst_preorder_template.c"

static SR_INLINE void* bst_inorder_init(
	                          void* PARAM_OUT itr_ptr,
	                          void* PARAM_IN contain_ptr)
{
	if (null == contain_ptr || null == itr_ptr)
	{
		return null;
	}
	
	init_bst_const_inorder_iterator_unsafe((bst_inorder_iterator_t*)itr_ptr,
		(const tree_node_ptr*)contain_ptr,
		null);

	return itr_ptr;
}

static SR_INLINE void* bst_inorder_begin(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return get_bst_begin_inorder_iterator_unsafe((bst_inorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}	
}

static SR_INLINE void* bst_inorder_end(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return get_bst_end_inorder_iterator_unsafe((bst_inorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}

static SR_INLINE void* bst_inorder_increase(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return increase_bst_inorder_iterator_unsafe((bst_inorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}

static SR_INLINE void* bst_inorder_decrease(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return decrease_bst_inorder_iterator_unsafe((bst_inorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}

static SR_INLINE void* bst_posorder_init(void* PARAM_IN contain_ptr, void* PARAM_OUT itr_ptr)
{
	if (null == contain_ptr || null == itr_ptr)
	{
		return null;
	}

	init_bst_const_posorder_iterator_unsafe((bst_posorder_iterator_t*)itr_ptr,
		(const tree_node_ptr*)contain_ptr,
		null);

	return itr_ptr;
}

static SR_INLINE void* bst_posorder_begin(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return get_bst_begin_posorder_iterator_unsafe((bst_posorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}

static SR_INLINE void* bst_posorder_end(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return get_bst_end_posorder_iterator_unsafe((bst_posorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}

static SR_INLINE void* bst_posorder_increase(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return increase_bst_posorder_iterator_unsafe((bst_posorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}

static SR_INLINE void* bst_preorder_init(void* PARAM_IN contain_ptr, void* PARAM_OUT itr_ptr)
{
	if (null == contain_ptr || null == itr_ptr)
	{
		return null;
	}

	init_bst_const_preorder_iterator_unsafe((bst_preorder_iterator_t*)itr_ptr,
		(const tree_node_ptr*)contain_ptr,
		null);

	return itr_ptr;
}

static SR_INLINE void* bst_preorder_begin(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return get_bst_begin_preorder_iterator_unsafe((bst_preorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}

static SR_INLINE void* bst_preorder_end(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return get_bst_end_preorder_iterator_unsafe((bst_preorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}

static SR_INLINE void* bst_preorder_increase(void* PARAM_OUT itr_ptr)
{
	if (itr_ptr)
	{
		return increase_bst_preorder_iterator_unsafe((bst_preorder_iterator_t*)itr_ptr);
	}
	else
	{
		return null;
	}
}











