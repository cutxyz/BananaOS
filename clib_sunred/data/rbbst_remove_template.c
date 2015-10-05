//////////////////////////////////////																		  internal_remove_rbbst_node
// rbbst_remove_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#include "rbbstnode_define_declare.h"
#include "rbbst_init_template.c"
#include "bst_remove_template.c"

#ifndef remove_rbbst_node_base
#define remove_rbbst_node_base internal_remove_bst_node_unsafe
#endif//remove_rbbst_node_base


#ifndef rbbst_remove_update_fixed_unsafe

static SR_INLINE result_t __rbt_remove_rotate_fixup(
	tree_node_ptr* PARAM_INOUT root_node_ptrptr, 
	tree_node_ptr  PARAM_INOUT ref_node_ptr)
{
	tree_node_ptr temp_node_ptr;
	result_t       status;

	if (null == ref_node_ptr)
	{
		return STATUS_OK;
	}

	status       = STATUS_OK;

	while (ref_node_ptr != *root_node_ptrptr)
	{
		bool_t         check_color1;
		bool_t         check_color2;
		tree_node_ptr  parent_node_ptr;
		tree_node_ptr  temp_right_node_ptr;
		tree_node_ptr  temp_left_node_ptr;

		check_color1 = check_tree_redcolor(ref_node_ptr);

		BREAK_LOOP_CONDITION(!check_color1);

		parent_node_ptr = get_tree_parent(ref_node_ptr);

		if (get_tree_left(parent_node_ptr) == ref_node_ptr)
		{
			temp_node_ptr = get_tree_right(parent_node_ptr);
			check_color1  = check_tree_redcolor(temp_node_ptr);

			if (check_color1)
			{
				if (temp_node_ptr)
				{
					set_tree_blackcolor(temp_node_ptr);
				}
				set_tree_redcolor(parent_node_ptr);
				rbbst_left_rotate_unsafe(root_node_ptrptr, null, parent_node_ptr);
				
				temp_node_ptr = get_tree_right(parent_node_ptr);
			}

			if (null == temp_node_ptr)
			{
				ref_node_ptr = parent_node_ptr;
				continue;
			}

			temp_left_node_ptr  = get_tree_left(temp_node_ptr);
			temp_right_node_ptr = get_tree_right(temp_node_ptr);

			check_color1 = rbbst_check_black_color(temp_left_node_ptr);
			check_color2 = rbbst_check_black_color(temp_right_node_ptr);

			if (check_color1 && check_color2)
			{
				set_tree_redcolor (temp_node_ptr);
				ref_node_ptr = parent_node_ptr;
			}
			else
			{
				
				if (check_color2)
				{
					if (temp_left_node_ptr)
					{
						set_tree_blackcolor(temp_left_node_ptr);
					}
					set_tree_redcolor(parent_node_ptr);
					rbbst_right_rotate_unsafe(root_node_ptrptr, null, temp_node_ptr);
					temp_node_ptr = get_tree_right(parent_node_ptr);

					temp_right_node_ptr = get_tree_right(temp_node_ptr);
				}

				
				copy_rbbst_color_unsafe(temp_node_ptr, parent_node_ptr);
				set_tree_blackcolor(parent_node_ptr);

				if (temp_right_node_ptr)
				{
					set_tree_blackcolor(temp_right_node_ptr);
				}
				rbbst_right_rotate_unsafe(root_node_ptrptr, null, parent_node_ptr);

				ref_node_ptr = *root_node_ptrptr;
			}
		}
		else if (get_tree_right(parent_node_ptr) == ref_node_ptr)
		{
			temp_node_ptr = get_tree_left(parent_node_ptr);
			check_color1  = check_tree_redcolor(temp_node_ptr);

			if (check_color1)
			{
				if (temp_node_ptr)
				{
					set_tree_blackcolor(temp_node_ptr);
				}
				set_tree_redcolor(parent_node_ptr);
				rbbst_right_rotate_unsafe(root_node_ptrptr, null, parent_node_ptr);

				temp_node_ptr = get_tree_left(parent_node_ptr);
			}

			if (null == temp_node_ptr)
			{
				ref_node_ptr = parent_node_ptr;
				continue;
			}

			temp_left_node_ptr = get_tree_left(temp_node_ptr);
			temp_right_node_ptr = get_tree_right(temp_node_ptr);

			check_color1 = rbbst_check_black_color(temp_left_node_ptr);
			check_color2 = rbbst_check_black_color(temp_right_node_ptr);

			if (check_color1 && check_color2)
			{
				set_tree_blackcolor(temp_node_ptr);
				ref_node_ptr = parent_node_ptr;
			}
			else
			{
				if (check_color1)
				{
					if (temp_right_node_ptr)
					{
						set_tree_blackcolor(temp_right_node_ptr);
					}
					set_tree_redcolor(temp_node_ptr);
					rbbst_left_rotate_unsafe(root_node_ptrptr, null, temp_node_ptr);
					temp_node_ptr = get_tree_left(parent_node_ptr);

					temp_left_node_ptr = get_tree_left(temp_node_ptr);
				}

				copy_rbbst_color_unsafe(temp_node_ptr, parent_node_ptr);
				set_tree_blackcolor(parent_node_ptr);

				if (temp_right_node_ptr)
				{
					set_tree_blackcolor(temp_left_node_ptr);
				}
				rbbst_right_rotate_unsafe(root_node_ptrptr, null, parent_node_ptr);

				ref_node_ptr = *root_node_ptrptr;
			}
		}
		else
		{
			BREAK_LOOP(status, STATUS_MEM_ERR);
		}
	}

	if (STATUS_OK == status)
	{
		set_tree_blackcolor(ref_node_ptr);
	}

	return status;
}
#define rbbst_remove_update_fixed_unsafe __rbt_remove_rotate_fixup
#endif // rbbst_remove_update_fixed_unsafe

#ifndef remove_rbbst_node
// 黑红树移除节点
static SR_INLINE result_t rbbst_remove_node(
	tree_node_ptr* PARAM_INOUT root_node_ptrptr,
	tree_node_ptr PARAM_INOUT remove_node_ptr)
{
	result_t status;

	DO_ONE_LOOP_BEGIN

	bool_t   is_red_node;

	tree_node_ptr sub_remove_node_ptr;
	tree_node_ptr sub_romove_ref_node_ptr;


	if (null == remove_node_ptr ||
		null == root_node_ptrptr || 
		null == *root_node_ptrptr)
	{
		BREAK_LOOP(status, STATUS_INVALID_PARAMS);
	}

	sub_romove_ref_node_ptr = find_bst_remove_replace_node_unsafe
		(remove_node_ptr, &sub_remove_node_ptr);


	if (sub_remove_node_ptr == *root_node_ptrptr)
	{
		status = remove_rbbst_node_base(root_node_ptrptr,
			remove_node_ptr,
			sub_remove_node_ptr,
			sub_romove_ref_node_ptr);

		if (STATUS_OK == status)
		{
			if (null != sub_romove_ref_node_ptr)										   
			{
				set_tree_blackcolor(bst_to_rbbst_unsafe(sub_romove_ref_node_ptr));
			}
		}
		break;
	}

	is_red_node = check_tree_redcolor(bst_to_rbbst_unsafe(sub_remove_node_ptr));

	status = remove_rbbst_node_base(root_node_ptrptr,
		remove_node_ptr,
		sub_remove_node_ptr,
		sub_romove_ref_node_ptr);

	if (null != sub_remove_node_ptr && 
		sub_remove_node_ptr != remove_node_ptr)
	{
		copy_rbbst_color_unsafe(sub_remove_node_ptr, remove_node_ptr);
	}

	BREAK_LOOP_CONDITION(null == *root_node_ptrptr || is_red_node);
	BREAK_LOOP_CONDITION(STATUS_OK != status);

	status = rbbst_remove_update_fixed_unsafe(root_node_ptrptr, 
		sub_romove_ref_node_ptr);

	DO_ONE_LOOP_END
	return status;
}
#define remove_rbbst_node rbbst_remove_node
#endif // remove_rbbst_node





