//////////////////////////////////////
// bst_aligned_remove_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "bst_init_template.c"
#include "bst_minmax_template.c"
#include "bst_remove_template.c"


#ifndef remove_aligned_bst_node
#define remove_aligned_bst_node aligned_bst_remove_node
#endif // remove_aligned_bst_node

#ifndef internal_remove_aligned_bst_node_unsafe 
#define internal_remove_aligned_bst_node_unsafe   __aligned_bst_remove_node_internal
#endif //internal_aligned_remove_bst_node_unsafe

#ifndef internal_remove_aligned_bst_node_unsafe_ex 
#define internal_remove_aligned_bst_node_unsafe_ex   __aligned_bst_remove_node_internal_with_spec_null
#endif //internal_aligned_remove_bst_node_unsafe_ex

#ifndef aligned_bst_remove_funcs
#define aligned_bst_remove_funcs


// 移除节点(删除内部使用)
static SR_INLINE result_t __aligned_bst_remove_node_internal_with_spec_null
(bst_node_ptr* PARAM_INOUT root_node_ptr,
bst_node_ptr PARAM_INOUT remove_node_ptr,
bst_node_ptr PARAM_INOUT sub_remove_node_ptr,
bst_node_ptr PARAM_INOUT sub_remove_node_ref_ptr,
const bst_node_ptr PARAM_IN null_node_ptr,
reg_t  aligned_mask)
{

	bst_node_ptr tmp_root_node_ptr;
	bst_node_ptr parant_node_ptr;
	bst_node_ptr left_node_ptr;
	bst_node_ptr right_node_ptr;

	result_t status;

	tmp_root_node_ptr = *root_node_ptr;
	parant_node_ptr = null;
	status = STATUS_OK;

#define BST_ALIGNED_GET_PARENT_STORE  get_bst_parent_unsafe
#undef 	get_bst_parent_unsafe
#define get_bst_parent_unsafe(X)  get_aligned_bst_parent_unsafe(X, aligned_mask)
#define BST_ALIGNED_SET_PARENT_STORE  set_bst_parent_unsafe
#undef  set_bst_parent_unsafe
#define set_bst_parent_unsafe(X,Y)  set_aligned_bst_parent(X, Y, aligned_mask)

	DO_ONE_LOOP_BEGIN

		// 处理替换节点

		// 子节点是根节点
	if (sub_remove_node_ptr == tmp_root_node_ptr)
	{
		parant_node_ptr = get_bst_parent_unsafe(tmp_root_node_ptr);
		if (null != parant_node_ptr)
		{
			if (get_bst_left_unsafe(parant_node_ptr) == tmp_root_node_ptr)
			{
				set_bst_left_unsafe(parant_node_ptr, sub_remove_node_ref_ptr);
			}
			else if (get_bst_right_unsafe(parant_node_ptr) == tmp_root_node_ptr)
			{
				set_bst_right_unsafe(parant_node_ptr, sub_remove_node_ref_ptr);
			}
			else
			{
				BREAK_LOOP(status, STATUS_MEM_ERR);
			}
		}

		if (sub_remove_node_ref_ptr)
		{
			set_bst_parent_unsafe(sub_remove_node_ref_ptr, parant_node_ptr);
		}

		*root_node_ptr = sub_remove_node_ref_ptr;

		init_bst_node_unsafe(remove_node_ptr, null, null, null);
		BREAK_LOOP(status, STATUS_OK);
	}

	// 子节点是非根节点
	parant_node_ptr = get_bst_parent_unsafe(sub_remove_node_ptr);

	if (get_bst_left_unsafe(parant_node_ptr) == sub_remove_node_ptr)
	{
		set_bst_left_unsafe(parant_node_ptr, sub_remove_node_ref_ptr);
	}
	else if (get_bst_right_unsafe(parant_node_ptr) == sub_remove_node_ptr)
	{
		set_bst_right_unsafe(parant_node_ptr, sub_remove_node_ref_ptr);
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
			set_bst_parent_unsafe(sub_remove_node_ref_ptr, parant_node_ptr);
		}
		init_bst_node_unsafe(remove_node_ptr, null, null, null);
		BREAK_LOOP(status, STATUS_OK);
	}

	// 父节点是需要移除的节点
	if (parant_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			set_bst_parent_unsafe(sub_remove_node_ref_ptr, sub_remove_node_ptr);
		}
	}
	// 其他节点
	else
	{
		if (sub_remove_node_ref_ptr)
		{
			set_bst_parent_unsafe(sub_remove_node_ref_ptr, parant_node_ptr);
		}
	}

	// 将remove node相关的指针复制
	set_bst_left_unsafe(sub_remove_node_ptr, get_bst_left_unsafe(remove_node_ptr));
	set_bst_right_unsafe(sub_remove_node_ptr, get_bst_right_unsafe(remove_node_ptr));
	set_bst_parent_unsafe(sub_remove_node_ptr, get_bst_parent_unsafe(remove_node_ptr));

	if (remove_node_ptr == tmp_root_node_ptr)// 移除节点是根节点
	{
		*root_node_ptr = sub_remove_node_ptr;		// 将根节点替换为psub_node
	}
	else
	{
		parant_node_ptr = get_bst_parent_unsafe(remove_node_ptr);
		// 替换移除节点父节点的相关指针
		if (remove_node_ptr == get_bst_left_unsafe(parant_node_ptr))
		{
			set_bst_left_unsafe(parant_node_ptr, sub_remove_node_ptr);
		}
		else if (remove_node_ptr == get_bst_right_unsafe(parant_node_ptr))
		{
			set_bst_right_unsafe(parant_node_ptr, sub_remove_node_ptr);
		}
		else
		{
			BREAK_LOOP(status, STATUS_MEM_ERR);
		}
	}

	// 更新现在新的左右节点的父节点指针
	left_node_ptr = get_bst_left_unsafe(sub_remove_node_ptr);
	right_node_ptr = get_bst_right_unsafe(sub_remove_node_ptr);


	if (!null_node_ptr)
	{
		if (left_node_ptr)
		{
			set_bst_parent_unsafe(left_node_ptr, sub_remove_node_ptr);
		}

		if (right_node_ptr)
		{
			set_bst_parent_unsafe(right_node_ptr, sub_remove_node_ptr);
		}
	}
	else
	{
		if (left_node_ptr != null_node_ptr && left_node_ptr)
		{
			set_bst_parent_unsafe(left_node_ptr, sub_remove_node_ptr);
		}

		if (right_node_ptr != null_node_ptr && right_node_ptr)
		{
			set_bst_parent_unsafe(right_node_ptr, sub_remove_node_ptr);
		}
	}

	init_bst_node_unsafe(remove_node_ptr, null, null, null);
	BREAK_LOOP(status, STATUS_OK);
	DO_ONE_LOOP_END

#undef 	get_bst_parent_unsafe
#define get_bst_parent_unsafe 	  BST_ALIGNED_GET_PARENT_STORE
#undef BST_ALIGNED_GET_PARENT_STORE
#undef 	set_bst_parent_unsafe
#define set_bst_parent_unsafe 	  BST_ALIGNED_SET_PARENT_STORE
#undef BST_ALIGNED_SET_PARENT_STORE

	return status;
}

// 移除节点(删除内部使用)
static SR_INLINE result_t __aligned_bst_remove_node_internal
(bst_node_ptr* PARAM_INOUT root_node_ptrptr,
bst_node_ptr PARAM_INOUT remove_node_ptr,
bst_node_ptr PARAM_INOUT sub_remove_node_ptr,
bst_node_ptr PARAM_INOUT sub_remove_node_ref_ptr,
reg_t  aligned_mask)
{
	bst_node_ptr tmp_root_node_ptr;
	bst_node_ptr parant_node_ptr;
	bst_node_ptr left_node_ptr;
	bst_node_ptr right_node_ptr;

	result_t status;

	tmp_root_node_ptr = *root_node_ptrptr;
	parant_node_ptr = null;
	status = STATUS_OK;

#define BST_ALIGNED_GET_PARENT_STORE  get_bst_parent_unsafe
#undef 	get_bst_parent_unsafe
#define get_bst_parent_unsafe(X)  get_aligned_bst_parent_unsafe(X, aligned_mask)
#define BST_ALIGNED_SET_PARENT_STORE  set_bst_parent_unsafe
#undef  set_bst_parent_unsafe
#define set_bst_parent_unsafe(X,Y)  set_aligned_bst_parent(X, Y, aligned_mask)

	DO_ONE_LOOP_BEGIN

		// 处理替换节点

		// 子节点是根节点
	if (sub_remove_node_ptr == tmp_root_node_ptr)
	{
		parant_node_ptr = get_bst_parent_unsafe(tmp_root_node_ptr);
		if (null != parant_node_ptr)
		{
			if (get_bst_left_unsafe(parant_node_ptr) == tmp_root_node_ptr)
			{
				set_bst_left_unsafe(parant_node_ptr, sub_remove_node_ref_ptr);
			}
			else if (get_bst_right_unsafe(parant_node_ptr) == tmp_root_node_ptr)
			{
				set_bst_right_unsafe(parant_node_ptr, sub_remove_node_ref_ptr);
			}
			else
			{
				BREAK_LOOP(status, STATUS_MEM_ERR);
			}
		}

		if (sub_remove_node_ref_ptr)
		{
			set_bst_parent_unsafe(sub_remove_node_ref_ptr, parant_node_ptr);
		}

		*root_node_ptrptr = sub_remove_node_ref_ptr;

		init_bst_node_unsafe(remove_node_ptr, null, null, null);
		BREAK_LOOP(status, STATUS_OK);
	}

	// 子节点是非根节点
	parant_node_ptr = get_bst_parent_unsafe(sub_remove_node_ptr);

	if (get_bst_left_unsafe(parant_node_ptr) == sub_remove_node_ptr)
	{
		set_bst_left_unsafe(parant_node_ptr, sub_remove_node_ref_ptr);
	}
	else if (get_bst_right_unsafe(parant_node_ptr) == sub_remove_node_ptr)
	{
		set_bst_right_unsafe(parant_node_ptr, sub_remove_node_ref_ptr);
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
			set_bst_parent_unsafe(sub_remove_node_ref_ptr, parant_node_ptr);
		}
		init_bst_node_unsafe(remove_node_ptr, null, null, null);
		BREAK_LOOP(status, STATUS_OK);
	}

	// 父节点是需要移除的节点
	if (parant_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			set_bst_parent_unsafe(sub_remove_node_ref_ptr, sub_remove_node_ptr);
		}
	}
	// 其他节点
	else
	{
		if (sub_remove_node_ref_ptr)
		{
			set_bst_parent_unsafe(sub_remove_node_ref_ptr, parant_node_ptr);
		}
	}

	// 将remove node相关的指针复制
	set_bst_left_unsafe(sub_remove_node_ptr, get_bst_left_unsafe(remove_node_ptr));
	set_bst_right_unsafe(sub_remove_node_ptr, get_bst_right_unsafe(remove_node_ptr));
	set_bst_parent_unsafe(sub_remove_node_ptr, get_bst_parent_unsafe(remove_node_ptr));

	if (remove_node_ptr == tmp_root_node_ptr)// 移除节点是根节点
	{
		*root_node_ptrptr = sub_remove_node_ptr;		// 将根节点替换为psub_node
	}
	else
	{
		parant_node_ptr = get_bst_parent_unsafe(remove_node_ptr);
		// 替换移除节点父节点的相关指针
		if (remove_node_ptr == get_bst_left_unsafe(parant_node_ptr))
		{
			set_bst_left_unsafe(parant_node_ptr, sub_remove_node_ptr);
		}
		else if (remove_node_ptr == get_bst_right_unsafe(parant_node_ptr))
		{
			set_bst_right_unsafe(parant_node_ptr, sub_remove_node_ptr);
		}
		else
		{
			BREAK_LOOP(status, STATUS_MEM_ERR);
		}
	}

	// 更新现在新的左右节点的父节点指针
	left_node_ptr = get_bst_left_unsafe(sub_remove_node_ptr);
	right_node_ptr = get_bst_right_unsafe(sub_remove_node_ptr);

	if (left_node_ptr)
	{
		set_bst_parent_unsafe(left_node_ptr, sub_remove_node_ptr);
	}

	if (right_node_ptr)
	{
		set_bst_parent_unsafe(right_node_ptr, sub_remove_node_ptr);
	}

	init_bst_node_unsafe(remove_node_ptr, null, null, null);
	BREAK_LOOP(status, STATUS_OK);
	DO_ONE_LOOP_END

#undef 	get_bst_parent_unsafe
#define get_bst_parent_unsafe 	  BST_ALIGNED_GET_PARENT_STORE
#undef BST_ALIGNED_GET_PARENT_STORE
#undef 	set_bst_parent_unsafe
#define set_bst_parent_unsafe 	  BST_ALIGNED_SET_PARENT_STORE
#undef BST_ALIGNED_SET_PARENT_STORE

	return status;
}

// 移除节点
static SR_INLINE result_t aligned_bst_remove_node
(bst_node_ptr* PARAM_INOUT root_node_ptr,
bst_node_ptr PARAM_INOUT remove_node_ptr,
reg_t  aligned_mask)
{
	bst_node_ptr sub_romove_ref_node_ptr;
	bst_node_ptr sub_remove_node_ptr;
	result_t status;

	RETURN_INVALID_RESULT(null == remove_node_ptr || null == root_node_ptr,
		STATUS_INVALID_PARAMS);
	RETURN_RESULT(null == *root_node_ptr, STATUS_OK);

	status = STATUS_OK;

	sub_romove_ref_node_ptr = find_bst_remove_replace_node_unsafe
		(remove_node_ptr, &sub_remove_node_ptr);

	status = internal_remove_aligned_bst_node_unsafe(root_node_ptr,
		remove_node_ptr,
		sub_remove_node_ptr,
		sub_romove_ref_node_ptr,
		aligned_mask);

	return status;
}
#endif //aligned_bst_remove_funcs



