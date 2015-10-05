//////////////////////////////////////
// bst_aligned_add_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "bst_init_template.c"
#include "bst_find_template.c"

#ifndef insert_bst_aligned_node
#define insert_bst_aligned_node bst_aligned_add_node
#endif // insert_bst_node


#ifndef bst_aligned_add_funcs
#define bst_aligned_add_funcs
// 插入节点
static SR_INLINE result_t bst_aligned_add_node(bst_node_ptr* PARAM_INOUT root_node_ptrptr,
	bst_node_ptr  PARAM_INOUT add_node_ptr,
	bst_node_cmp_func         compareto,
	reg_t                     aligned_mask,
	bst_node_ptr* PARAM_OUT   added_node_ptrptr)
{
#define BST_ALIGNED_METHOD_STORE  get_bst_parent_unsafe
#undef 	get_bst_parent_unsafe
#define get_bst_parent_unsafe(X)  get_aligned_bst_parent_unsafe(X, aligned_mask)

	result_t status;
	int cmp_result;
	bst_node_ptr tmp_root_node_ptr;
	bst_node_ptr node_to_be_add_ptr;
	bst_node_ptr parent_node_ptr;

	RETURN_RESULT(null == root_node_ptrptr || null == add_node_ptr,
		STATUS_INVALID_PARAMS);

	status = STATUS_OK;
	tmp_root_node_ptr = *root_node_ptrptr;

	// 添加第一个节点
	if (null == tmp_root_node_ptr)
	{
		*root_node_ptrptr = add_node_ptr;
		init_bst_node_unsafe(add_node_ptr, null, null, null);
		if (added_node_ptrptr)
		{
			*added_node_ptrptr = add_node_ptr;
		}
		return STATUS_OK;
	}

	DO_ONE_LOOP_BEGIN

	node_to_be_add_ptr = find_bst_near_node
		(add_node_ptr, tmp_root_node_ptr, compareto, &cmp_result);

	// 已经存在一个同样key的节点, added_node_ptr返回的是已有节点的指针
	if (null != node_to_be_add_ptr && 0 == cmp_result)
	{
		if (added_node_ptrptr)
		{
			*added_node_ptrptr = node_to_be_add_ptr;
		}
		status = STATUS_UNIQUE;
		break;
	}

	parent_node_ptr = get_bst_parent_unsafe(node_to_be_add_ptr);

	if (0 > cmp_result)
	{
		if (null == get_bst_left_unsafe(node_to_be_add_ptr))
		{
			set_bst_left_unsafe(node_to_be_add_ptr, add_node_ptr);
			init_bst_node_unsafe(add_node_ptr, null, null, node_to_be_add_ptr);
		}
		else
		{
			// 内存数据被损坏
			status = STATUS_MEM_ERR;
			break;
		}
	}
	else
	{
		if (null == get_bst_right_unsafe(node_to_be_add_ptr))
		{
			set_bst_right_unsafe(node_to_be_add_ptr, add_node_ptr);
			init_bst_node_unsafe(add_node_ptr, null, null, node_to_be_add_ptr);
		}
		else
		{
			// 内存数据被损坏
			status = STATUS_MEM_ERR;
			break;
		}
	}

	if (added_node_ptrptr)
	{
		*added_node_ptrptr = node_to_be_add_ptr;
	}
	status = STATUS_OK;
	DO_ONE_LOOP_END

#undef 	get_bst_parent_unsafe
#define get_bst_parent_unsafe 	  BST_ALIGNED_METHOD_STORE
#undef BST_ALIGNED_METHOD_STORE

	return status;
}

#endif //bst_aligned_add_funcs

