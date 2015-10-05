//////////////////////////////////////
// block_static_mem.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
// 
// 内存块, 用于索引对应的内存块，记录对应的内存的地址、大小以及该块内存的使用简单情况，
//        每一个块是内存分配的最小单位，一个块内只有一个正在使用的连续地址的内存数组，
//        该内存数组在重分配时候，新内存数组的大小只能小于块大小的时候才能成功
/////////////////////////////////////
#include "blockheader_define_declare.h"

//////////////////////////////////////////////////////////////////////////
#ifndef block_push_back_unsafe
static SR_INLINE result_t __block_push_back(blockinfo_ptr PARAM_INOUT blk_ptr,
	usize__t buf_size, 
	bool_t auto_fixsize,
	buffer_offsetinfo_t* PARAM_OUT push_success_info_ptr)
{
	result_t status;
	usize__t old_size;
	usize__t new_size;
	old_size = get_blockinfo_using_size(blk_ptr);
	new_size = old_size + buf_size;
	DO_ONE_LOOP_BEGIN
	
	status = set_blockinfo_using_size(blk_ptr, new_size, auto_fixsize);
	if (STATUS_OK != status)
	{
		if (push_success_info_ptr)
		{
			push_success_info_ptr->m_begin = 0;
			push_success_info_ptr->m_size  = 0;
		}
		break;
	}

	if (push_success_info_ptr)
	{
		push_success_info_ptr->m_begin = old_size;
		push_success_info_ptr->m_size = 
			get_block_usingbuff_size_unsafe(blk_ptr)
			- old_size;
	}
	DO_ONE_LOOP_END
	return status;
}
#define  block_push_back_unsafe	 __block_push_back
#endif//block_push_back_unsafe

//////////////////////////////////////////////////////////////////////////

#ifndef block_push_buf_back_unsafe

static SR_INLINE result_t __block_push_buf_back(blockinfo_ptr PARAM_INOUT blk_ptr,
	const void*	PARAM_IN buf_ptr,
	usize__t buf_size,
	bool_t auto_fixsize,
	buffer_offsetinfo_t* PARAM_OUT push_success_info_ptr)
{
	buffer_offsetinfo_t offsetinfo;
	result_t status;
	if (null == push_success_info_ptr)
	{
		push_success_info_ptr = &offsetinfo;
	}
	DO_ONE_LOOP_BEGIN

	status = block_push_back_unsafe(blk_ptr, buf_size, auto_fixsize, push_success_info_ptr);
	BREAK_LOOP_CONDITION(STATUS_OK != status);

	set_blockinfo_usingbuf(blk_ptr, push_success_info_ptr->m_begin, 
		buf_ptr, push_success_info_ptr->m_size);

	DO_ONE_LOOP_END
	return status;
}

#define block_push_buf_back_unsafe __block_push_buf_back
#endif//block_push_buf_back_unsafe

//////////////////////////////////////////////////////////////////////////
#ifndef block_pop_back_unsafe
static SR_INLINE result_t __block_pop_back(blockinfo_ptr PARAM_INOUT blk_ptr,
	usize__t buf_size,
	buffer_offsetinfo_t* PARAM_OUT push_success_info_ptr)
{
	result_t status;
	usize__t old_size;
	usize__t new_size;
	old_size = get_blockinfo_using_size(blk_ptr);
	new_size = (old_size > buf_size) ? (old_size - buf_size) : (0);
	DO_ONE_LOOP_BEGIN

	status = set_blockinfo_using_size(blk_ptr, new_size, TRUE);
	if (STATUS_OK != status)
	{
		if (push_success_info_ptr)
		{
			push_success_info_ptr->m_begin = 0;
			push_success_info_ptr->m_size = 0;
		}
		break;
	}

	if (push_success_info_ptr)
	{
		push_success_info_ptr->m_begin = new_size;
		push_success_info_ptr->m_size  = old_size - new_size;
	}
	DO_ONE_LOOP_END
	return status;
}
#define  block_pop_back_unsafe	 __block_pop_back
#endif//block_pop_back_unsafe

//////////////////////////////////////////////////////////////////////////
#ifndef block_pop_back_2buf_unsafe
static SR_INLINE usize__t __block_pop_back_2buf(blockinfo_ptr PARAM_INOUT blk_ptr,
	void* PARAM_OUT buf_ptr,
	usize__t buf_size,
	buffer_offsetinfo_t* PARAM_OUT push_success_info_ptr)
{
	usize__t success_size;
	usize__t old_size;
	usize__t new_size;
	buffer_offsetinfo_t offsetinfo;
	result_t status;

	success_size = 0;
	DO_ONE_LOOP_BEGIN

	if (null == buf_ptr || 0 == buf_size)
	{
		if (push_success_info_ptr)
		{
			push_success_info_ptr->m_begin = 0;
			push_success_info_ptr->m_size = 0;
		}
		break;
	}

	if (null == push_success_info_ptr)
	{
		push_success_info_ptr = &offsetinfo;
	}

	old_size = get_blockinfo_using_size(blk_ptr);
	status = block_pop_back_unsafe(blk_ptr, buf_size, push_success_info_ptr);

	BREAK_LOOP_CONDITION(STATUS_OK != status);
	
	new_size = get_blockinfo_using_size(blk_ptr);

	set_blockinfo_using_size(blk_ptr, old_size, TRUE);
	success_size = copy_blockinfo_usingbuf(blk_ptr, 
		push_success_info_ptr->m_begin,
		buf_ptr, 
		push_success_info_ptr->m_size);


	DO_ONE_LOOP_END
	return success_size;
}
#define  block_pop_back_2buf_unsafe	 __block_pop_back_2buf
#endif//block_pop_back_2buf_unsafe












