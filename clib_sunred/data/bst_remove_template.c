//////////////////////////////////////
// bst_remove_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "bst_init_template.c"
#include "bst_minmax_template.c"

#include "bstnode_define_declare.h"

#ifndef remove_bst_node
//找出需要移除的节点
static SR_INLINE tree_node_ptr __bst_find_remove_replace_node
(tree_node_ptr PARAM_IN remove_node_ptr,
tree_node_ptr* PARAM_OUT sub_remove_node_ptrptr)
{
	tree_node_ptr sub_remove_ref_node_ptr = null;
	tree_node_ptr tmp_sub_remove_node_ptr = null;
	tree_node_ptr left_node_ptr = get_tree_left(remove_node_ptr);
	tree_node_ptr right_node_ptr = get_tree_right(remove_node_ptr);

	if (null == left_node_ptr)
	{
		// 左子树为空则用右节点替代
		sub_remove_ref_node_ptr = right_node_ptr;
		tmp_sub_remove_node_ptr = remove_node_ptr;
	}
	else if (null == right_node_ptr)
	{
		// 右子树为空则用左节点替代
		sub_remove_ref_node_ptr = left_node_ptr;
		tmp_sub_remove_node_ptr = remove_node_ptr;
	}
	else
	{
		// 左右都不空的时候，选择右子树最小的那个节点替代
		tmp_sub_remove_node_ptr = get_bst_min_node(right_node_ptr);

		left_node_ptr = get_tree_left(tmp_sub_remove_node_ptr);

		if (left_node_ptr != null)
		{
			sub_remove_ref_node_ptr = left_node_ptr;
		}
		else
		{
			sub_remove_ref_node_ptr = get_tree_right(tmp_sub_remove_node_ptr);
		}
	}

	*sub_remove_node_ptrptr = tmp_sub_remove_node_ptr;
	return sub_remove_ref_node_ptr;
}
#define remove_bst_node bst_remove_node
#endif // remove_bst_node

//////////////////////////////////////////////////////////////////////////
#ifndef find_bst_remove_replace_node_unsafe
//找出需要移除的节点
static SR_INLINE tree_node_ptr __bst_find_remove_replace_node_with_spec_null
	(tree_node_ptr PARAM_IN remove_node_ptr,
	tree_node_ptr* PARAM_OUT sub_remove_node_ptrptr,
	const tree_node_ptr PARAM_IN null_node_ptr)
{
	tree_node_ptr sub_remove_ref_node_ptr = null;
	tree_node_ptr tmp_sub_remove_node_ptr = null;
	tree_node_ptr left_node_ptr  = get_tree_left(remove_node_ptr);
	tree_node_ptr right_node_ptr = get_tree_right(remove_node_ptr);

	if (null_node_ptr == left_node_ptr || null == left_node_ptr)
	{
		// 左子树为空则用右节点替代
		sub_remove_ref_node_ptr = right_node_ptr;
		tmp_sub_remove_node_ptr = remove_node_ptr;
	}
	else if (null_node_ptr == right_node_ptr || null == right_node_ptr)
	{
		// 右子树为空则用左节点替代
		sub_remove_ref_node_ptr = left_node_ptr;
		tmp_sub_remove_node_ptr = remove_node_ptr;
	}
	else
	{
		// 左右都不空的时候，选择右子树最小的那个节点替代
		tmp_sub_remove_node_ptr = get_bst_min_node_ex
			(right_node_ptr, null_node_ptr);
		left_node_ptr = get_tree_left(tmp_sub_remove_node_ptr);

		if (left_node_ptr != null_node_ptr && left_node_ptr != null)
		{
			sub_remove_ref_node_ptr = left_node_ptr;
		}
		else
		{
			sub_remove_ref_node_ptr = get_tree_right(tmp_sub_remove_node_ptr);
		}
	}

	*sub_remove_node_ptrptr = tmp_sub_remove_node_ptr;
	return sub_remove_ref_node_ptr;
}
#define  find_bst_remove_replace_node_unsafe __bst_find_remove_replace_node
#endif // find_bst_remove_replace_node_unsafe

//////////////////////////////////////////////////////////////////////////
#ifndef find_bst_remove_replace_node_unsafe_ex
// 移除节点(删除内部使用)
static SR_INLINE result_t __bst_remove_node_internal_with_spec_null
(tree_node_ptr* PARAM_INOUT root_node_ptr,	 
tree_node_ptr PARAM_INOUT remove_node_ptr,    
tree_node_ptr PARAM_INOUT sub_remove_node_ptr,
tree_node_ptr PARAM_INOUT sub_remove_node_ref_ptr,
const tree_node_ptr PARAM_IN null_node_ptr)
{
	tree_node_ptr tmp_root_node_ptr;
	tree_node_ptr parant_node_ptr;
	tree_node_ptr left_node_ptr;
	tree_node_ptr right_node_ptr;

	result_t status;

	tmp_root_node_ptr = *root_node_ptr;
	parant_node_ptr	  = null;
	status   = STATUS_OK;

	DO_ONE_LOOP_BEGIN
		
	// 处理替换节点

	// 子节点是根节点
	if (sub_remove_node_ptr == tmp_root_node_ptr)
	{
		parant_node_ptr = get_tree_parent(tmp_root_node_ptr);
		if (null != parant_node_ptr)
		{
			if (get_tree_left(parant_node_ptr) == tmp_root_node_ptr)
			{
				set_tree_left(parant_node_ptr, sub_remove_node_ref_ptr);
			}
			else if (get_tree_right(parant_node_ptr) == tmp_root_node_ptr)
			{
				set_tree_right(parant_node_ptr, sub_remove_node_ref_ptr);
			}
			else
			{
				BREAK_LOOP(status, STATUS_MEM_ERR);
			}
		}

		if (sub_remove_node_ref_ptr)
		{
			set_tree_parent(sub_remove_node_ref_ptr, parant_node_ptr);
		}

		*root_node_ptr = sub_remove_node_ref_ptr;

		init_bst_node_unsafe(remove_node_ptr, null, null, null);
		BREAK_LOOP(status, STATUS_OK);
	}

	// 子节点是非根节点
	parant_node_ptr = get_tree_parent(sub_remove_node_ptr);

	if (get_tree_left(parant_node_ptr) == sub_remove_node_ptr)
	{
		set_tree_left(parant_node_ptr, sub_remove_node_ref_ptr);
	}
	else if (get_tree_right(parant_node_ptr) == sub_remove_node_ptr)
	{
		set_tree_right(parant_node_ptr, sub_remove_node_ref_ptr);
	}
	else
	{
		BREAK_LOOP(status, STATUS_MEM_ERR);
	}

	// 子节点是需要移除的节点
	if (sub_remove_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			set_tree_parent(sub_remove_node_ref_ptr, parant_node_ptr);
		}
		init_bst_node_unsafe(remove_node_ptr, null, null, null);
		BREAK_LOOP(status, STATUS_OK);
	}

	// 父节点是需要移除的节点
	if (parant_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			set_tree_parent(sub_remove_node_ref_ptr, sub_remove_node_ptr);
		}
	}
	// 其他节点
	else
	{
		if (sub_remove_node_ref_ptr)
		{
			set_tree_parent(sub_remove_node_ref_ptr, parant_node_ptr);
		}
	}

	// 将remove node相关的指针复制
	set_tree_left  (sub_remove_node_ptr, get_tree_left  (remove_node_ptr));
	set_tree_right (sub_remove_node_ptr, get_tree_right (remove_node_ptr));
	set_tree_parent(sub_remove_node_ptr, get_tree_parent(remove_node_ptr));

	if (remove_node_ptr == tmp_root_node_ptr)// 移除节点是根节点
	{
		*root_node_ptr = sub_remove_node_ptr;		// 将根节点替换为psub_node
	}
	else
	{
		parant_node_ptr = get_tree_parent(remove_node_ptr);
		// 替换移除节点父节点的相关指针
		if (remove_node_ptr == get_tree_left(parant_node_ptr))
		{
			set_tree_left(parant_node_ptr,sub_remove_node_ptr);
		}
		else if (remove_node_ptr == get_tree_right(parant_node_ptr))
		{
			set_tree_right(parant_node_ptr, sub_remove_node_ptr);
		}
		else
		{
			BREAK_LOOP(status, STATUS_MEM_ERR);
		}
	}

	// 更新现在新的左右节点的父节点指针
	left_node_ptr  = get_tree_left(sub_remove_node_ptr);
	right_node_ptr = get_tree_right(sub_remove_node_ptr);

	
	if (!null_node_ptr)
	{
		if (left_node_ptr)
		{
			set_tree_parent(left_node_ptr, sub_remove_node_ptr);
		}

		if (right_node_ptr)
		{
			set_tree_parent(right_node_ptr, sub_remove_node_ptr);
		}
	}
	else
	{
		if (left_node_ptr != null_node_ptr && left_node_ptr)
		{
			set_tree_parent(left_node_ptr, sub_remove_node_ptr);
		}

		if (right_node_ptr != null_node_ptr && right_node_ptr)
		{
			set_tree_parent(right_node_ptr, sub_remove_node_ptr);
		}
	}

	init_bst_node_unsafe(remove_node_ptr, null, null, null);
	BREAK_LOOP(status, STATUS_OK);
	DO_ONE_LOOP_END

	return status;
}
#define  find_bst_remove_replace_node_unsafe_ex __bst_find_remove_replace_node_with_spec_null
#endif // find_bst_remove_replace_unsafe_node

//////////////////////////////////////////////////////////////////////////
#ifndef internal_remove_bst_node_unsafe
// 移除节点(删除内部使用)
static SR_INLINE result_t __bst_remove_node_internal
(tree_node_ptr* PARAM_INOUT root_node_ptrptr,
tree_node_ptr PARAM_INOUT remove_node_ptr,
tree_node_ptr PARAM_INOUT sub_remove_node_ptr,
tree_node_ptr PARAM_INOUT sub_remove_node_ref_ptr)
{
	tree_node_ptr tmp_root_node_ptr;
	tree_node_ptr parant_node_ptr;
	tree_node_ptr left_node_ptr;
	tree_node_ptr right_node_ptr;

	result_t status;

	tmp_root_node_ptr = *root_node_ptrptr;
	parant_node_ptr = null;
	status = STATUS_OK;

	DO_ONE_LOOP_BEGIN

		// 处理替换节点

		// 子节点是根节点
	if (sub_remove_node_ptr == tmp_root_node_ptr)
	{
		parant_node_ptr = get_tree_parent(tmp_root_node_ptr);
		if (null != parant_node_ptr)
		{
			if (get_tree_left(parant_node_ptr) == tmp_root_node_ptr)
			{
				set_tree_left(parant_node_ptr, sub_remove_node_ref_ptr);
			}
			else if (get_tree_right(parant_node_ptr) == tmp_root_node_ptr)
			{
				set_tree_right(parant_node_ptr, sub_remove_node_ref_ptr);
			}
			else
			{
				BREAK_LOOP(status, STATUS_MEM_ERR);
			}
		}

		if (sub_remove_node_ref_ptr)
		{
			set_tree_parent(sub_remove_node_ref_ptr, parant_node_ptr);
		}

		*root_node_ptrptr = sub_remove_node_ref_ptr;

		init_bst_node_unsafe(remove_node_ptr, null, null, null);
		BREAK_LOOP(status, STATUS_OK);
	}

	// 子节点是非根节点
	parant_node_ptr = get_tree_parent(sub_remove_node_ptr);

	if (get_tree_left(parant_node_ptr) == sub_remove_node_ptr)
	{
		set_tree_left(parant_node_ptr, sub_remove_node_ref_ptr);
	}
	else if (get_tree_right(parant_node_ptr) == sub_remove_node_ptr)
	{
		set_tree_right(parant_node_ptr, sub_remove_node_ref_ptr);
	}
	else
	{
		BREAK_LOOP(status, STATUS_MEM_ERR);
	}

	// 子节点是需要移除的节点
	if (sub_remove_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			set_tree_parent(sub_remove_node_ref_ptr, parant_node_ptr);
		}
		init_bst_node_unsafe(remove_node_ptr, null, null, null);
		BREAK_LOOP(status, STATUS_OK);
	}

	// 父节点是需要移除的节点
	if (parant_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			set_tree_parent(sub_remove_node_ref_ptr, sub_remove_node_ptr);
		}
	}
	// 其他节点
	else
	{
		if (sub_remove_node_ref_ptr)
		{
			set_tree_parent(sub_remove_node_ref_ptr, parant_node_ptr);
		}
	}

	// 将remove node相关的指针复制
	set_tree_left(sub_remove_node_ptr, get_tree_left(remove_node_ptr));
	set_tree_right(sub_remove_node_ptr, get_tree_right(remove_node_ptr));
	set_tree_parent(sub_remove_node_ptr, get_tree_parent(remove_node_ptr));

	if (remove_node_ptr == tmp_root_node_ptr)// 移除节点是根节点
	{
		*root_node_ptrptr = sub_remove_node_ptr;		// 将根节点替换为psub_node
	}
	else
	{
		parant_node_ptr = get_tree_parent(remove_node_ptr);
		// 替换移除节点父节点的相关指针
		if (remove_node_ptr == get_tree_left(parant_node_ptr))
		{
			set_tree_left(parant_node_ptr, sub_remove_node_ptr);
		}
		else if (remove_node_ptr == get_tree_right(parant_node_ptr))
		{
			set_tree_right(parant_node_ptr, sub_remove_node_ptr);
		}
		else
		{
			BREAK_LOOP(status, STATUS_MEM_ERR);
		}
	}

	// 更新现在新的左右节点的父节点指针
	left_node_ptr = get_tree_left(sub_remove_node_ptr);
	right_node_ptr = get_tree_right(sub_remove_node_ptr);

	if (left_node_ptr)
	{
		set_tree_parent(left_node_ptr, sub_remove_node_ptr);
	}

	if (right_node_ptr)
	{
		set_tree_parent(right_node_ptr, sub_remove_node_ptr);
	}

	init_bst_node_unsafe(remove_node_ptr, null, null, null);
	BREAK_LOOP(status, STATUS_OK);
	DO_ONE_LOOP_END

	return status;
}
#define internal_remove_bst_node_unsafe   __bst_remove_node_internal
#endif //internal_remove_bst_node_unsafe

//////////////////////////////////////////////////////////////////////////
#ifndef internal_remove_bst_node_unsafe_ex
// 移除节点
static SR_INLINE result_t bst_remove_node
(tree_node_ptr* PARAM_INOUT root_node_ptr,
 tree_node_ptr  PARAM_INOUT remove_node_ptr)
{

	tree_node_ptr sub_romove_ref_node_ptr;
	tree_node_ptr sub_remove_node_ptr;
	result_t     status;

	RETURN_INVALID_RESULT(null == remove_node_ptr||null == root_node_ptr, 
		STATUS_INVALID_PARAMS);
	RETURN_RESULT(null == *root_node_ptr, STATUS_OK);

	sub_romove_ref_node_ptr = find_bst_remove_replace_node_unsafe
		(remove_node_ptr, &sub_remove_node_ptr);

	status = internal_remove_bst_node_unsafe(root_node_ptr, 
		remove_node_ptr, 
		sub_remove_node_ptr,
		sub_romove_ref_node_ptr);

	return status;
}
#define internal_remove_bst_node_unsafe_ex   __bst_remove_node_internal_with_spec_null
#endif //internal_remove_bst_node_unsafe_ex



