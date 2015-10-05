//////////////////////////////////////
// block_header.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
// 
// 内存块, 用于索引对应的内存块，记录对应的内存的地址、大小以及该块内存的使用简单情况，
//        每一个块是内存分配的最小单位，一个块内只有一个正在使用的连续地址的内存数组，
//        该内存数组在重分配时候，新内存数组的大小只能小于块大小的时候才能成功
/////////////////////////////////////
#include "../include/type.h"
#include "../include/util.h"

#ifndef SUNRED_LIB_BLOCK_HEADER
#define SUNRED_LIB_BLOCK_HEADER

// 块缓存
typedef struct st_blockbuffer_header
{
	usize__t m_size;
	void*    m_blockbuffer_ptr;
}blockbuffer_header_t;

// 块偏移缓存
typedef buffer_offsetinfo_t blockbuffer_offsetinfo_t;

// 块
typedef struct st_block_buffinfo
{
	blockbuffer_header_t     m_pool;  
	blockbuffer_offsetinfo_t m_using; 
}block_buffinfo_t;


//////////////////////////////////////////////////////////////////////////
#ifndef init_blockbuffer_header_unsafe 		  
#define init_blockbuffer_header_unsafe        __init_blockbuffer_header
#endif//init_blockbuffer_header_unsafe		  
											  
#ifndef init_block_offsetinfo_unsafe 		  
#define init_block_offsetinfo_unsafe          __init_block_offsetinfo
#endif//init_block_offsetinfo_unsafe		  
											  
#ifndef get_block_poolbuff_size_unsafe 		  
#define get_block_poolbuff_size_unsafe        __get_block_bufferinfo_poolbuff_size
#endif//get_block_poolbuff_size_unsafe		  
											  
#ifndef get_block_usingbuff_size_unsafe 	  
#define get_block_usingbuff_size_unsafe       __get_block_bufferinfo_usingbuff_size
#endif//get_block_usingbuff_size_unsafe		  
											  
#ifndef get_block_poolbuff_ptr_unsafe 		  
#define get_block_poolbuff_ptr_unsafe         __get_block_bufferinfo_poolbuff_ptr
#endif//get_block_poolbuff_ptr_unsafe		  
											  
#ifndef get_block_usingbuff_ptr_unsafe 		  
#define get_block_usingbuff_ptr_unsafe        __get_block_bufferinfo_usingbuff_ptr
#endif//get_block_usingbuff_ptr_unsafe		  
											  
#ifndef get_block_poolbuff_ptr_const_unsafe   
#define get_block_poolbuff_ptr_const_unsafe   __get_block_bufferinfo_poolbuff_ptr_const
#endif//get_block_poolbuff_ptr_const_unsafe	  
											  
#ifndef get_block_usingbuff_ptr_const_unsafe  
#define get_block_usingbuff_ptr_const_unsafe  __get_block_bufferinfo_usingbuff_ptr_const
#endif//get_block_usingbuff_ptr_const_unsafe

#ifndef get_block_usingbuff_beginindex_unsafe 
#define get_block_usingbuff_beginindex_unsafe __get_block_bufferinfo_usingbuff_beginindex
#endif//get_block_usingbuff_beginindex_unsafe

#ifndef set_block_usingbuff_beginindex_unsafe 
#define set_block_usingbuff_beginindex_unsafe __set_block_bufferinfo_usingbuff_beginindex
#endif//set_block_usingbuff_beginindex_unsafe

#ifndef set_block_usingbuff_size_unsafe 
#define set_block_usingbuff_size_unsafe       __set_block_bufferinfo_usingbuff_size
#endif//set_block_usingbuff_size_unsafe

#ifndef init_block_buffinfo_unsafe 
#define init_block_buffinfo_unsafe            __init_block_buffinfo
#endif//init_block_buffinfo_unsafe

#ifndef set_buffer_to_block_buffinfo_unsafe 
#define set_buffer_to_block_buffinfo_unsafe  __set_buffer_to_block_buffinfo
#endif//set_buffer_to_block_buffinfo_unsafe

#ifndef copy_buffer_from_block_buffinfo_unsafe 
#define copy_buffer_from_block_buffinfo_unsafe  __copy_buffer_from_block_buffinfo
#endif//copy_buffer_from_block_buffinfo_unsafe

#ifndef copy_block_to_block_unsafe
#define copy_block_to_block_unsafe  __copy_block_to_block
#endif//copy_block_to_block_unsafe

//////////////////////////////////////////////////////////////////////////
static SR_FORCE_INLINE blockbuffer_header_t* __init_blockbuffer_header(
	blockbuffer_header_t* PARAM_IN header_ptr,
	void* PARAM_IN buf_ptr,
	usize__t size)
{
	header_ptr->m_size            = size;
	header_ptr->m_blockbuffer_ptr = buf_ptr;
	return header_ptr;
}

static SR_FORCE_INLINE blockbuffer_offsetinfo_t* __init_block_offsetinfo(
	blockbuffer_offsetinfo_t* PARAM_IN offset_ptr,
	uindex_t beginidx,
	usize__t size)
{
	offset_ptr->m_size  = size;
	offset_ptr->m_begin = beginidx;
	return offset_ptr;
}

static SR_FORCE_INLINE usize__t __get_block_bufferinfo_poolbuff_size(const block_buffinfo_t* PARAM_IN buff_ptr)
{
	return buff_ptr->m_pool.m_size;
}
static SR_FORCE_INLINE usize__t __get_block_bufferinfo_usingbuff_size(const block_buffinfo_t* PARAM_IN buff_ptr)
{
	return buff_ptr->m_using.m_size;
}
static SR_FORCE_INLINE void* __get_block_bufferinfo_poolbuff_ptr(block_buffinfo_t* PARAM_IN buff_ptr)
{
	return buff_ptr->m_pool.m_blockbuffer_ptr;
}
static SR_FORCE_INLINE void* __get_block_bufferinfo_usingbuff_ptr(block_buffinfo_t* PARAM_IN buff_ptr)
{
	return ADDRESS_2_VOID_PTR(POINTER_2_ADDRESS(buff_ptr->m_pool.m_blockbuffer_ptr) + 
		buff_ptr->m_using.m_begin);
}
static SR_FORCE_INLINE const void* __get_block_bufferinfo_poolbuff_ptr_const(const block_buffinfo_t* PARAM_IN buff_ptr)
{
	return buff_ptr->m_pool.m_blockbuffer_ptr;
}
static SR_FORCE_INLINE const void* __get_block_bufferinfo_usingbuff_ptr_const(const block_buffinfo_t* PARAM_IN buff_ptr)
{
	return 	__get_block_bufferinfo_usingbuff_ptr((block_buffinfo_t*)buff_ptr);
}
static SR_FORCE_INLINE uindex_t __get_block_bufferinfo_usingbuff_beginindex(
	block_buffinfo_t* PARAM_IN buff_ptr)
{
	return buff_ptr->m_using.m_begin;
}
static SR_INLINE result_t __set_block_bufferinfo_usingbuff_beginindex(
	block_buffinfo_t* PARAM_IN buff_ptr,
	uindex_t new_index)
{
	result_t status;
	usize__t offset;

	DO_ONE_LOOP_BEGIN

	if (new_index >= buff_ptr->m_pool.m_size)
	{
		status = STATUS_OVERRANGE;
		break;
	}

	offset = buff_ptr->m_using.m_begin + buff_ptr->m_using.m_size;

	buff_ptr->m_using.m_begin = new_index;
	buff_ptr->m_using.m_size = (offset > new_index) ? (offset-new_index) : (0);

	status = STATUS_OK;

	DO_ONE_LOOP_END
	return status;

}

static SR_INLINE result_t __set_block_bufferinfo_usingbuff_size(
	block_buffinfo_t* PARAM_IN buff_ptr,
	uindex_t new_size,
	bool_t   auto_fixsize)
{
	result_t status;
	usize__t offset;

	offset = new_size + buff_ptr->m_using.m_begin;
	if (offset < buff_ptr->m_pool.m_size)
	{
		buff_ptr->m_using.m_size = new_size;
		status = STATUS_OK;
	}
	else if (auto_fixsize)
	{
		buff_ptr->m_using.m_size = buff_ptr->m_pool.m_size - 
			                       buff_ptr->m_using.m_begin;
		status = STATUS_OK;
	}
	else
	{
		status = STATUS_MEM_LOW;
	}
	
	return status;

}


static SR_INLINE block_buffinfo_t* __init_block_buffinfo(
	block_buffinfo_t* PARAM_IN buff_ptr,
	void* PARAM_IN buf_ptr,
	usize__t buf_size,
	uindex_t using_beginidx,
	usize__t using_size)
{
	result_t status;
	init_blockbuffer_header_unsafe (&buff_ptr->m_pool, buf_ptr, buf_size);

	DO_ONE_LOOP_BEGIN
	status = set_block_usingbuff_beginindex_unsafe(buff_ptr, using_beginidx);
	BREAK_LOOP_CONDITION(status);

	status = set_block_usingbuff_size_unsafe(buff_ptr, using_size, TRUE);

	DO_ONE_LOOP_END

	if (status)
	{
		init_block_offsetinfo_unsafe(&buff_ptr->m_using, 0, 0);
	}


	return buff_ptr;
}

static SR_INLINE usize__t __set_buffer_to_block_buffinfo(block_buffinfo_t* PARAM_INOUT buff_ptr,
	uindex_t offset,
	const void* PARAM_IN buf_ptr,
	usize__t buf_size)
{
	usize__t success_count;
	DO_ONE_LOOP_BEGIN
	
	if (null == buf_ptr || 
		0 == buf_size   || 
		offset >= buff_ptr->m_using.m_size)
	{
		success_count = 0;
		break;
	}

	success_count = offset + buf_size;
	if (success_count > buff_ptr->m_using.m_size)
	{
		success_count = buff_ptr->m_using.m_size - offset;
	}
	else
	{
		success_count = buf_size;
	}

	sr_memory_move_s(
		ADDRESS_2_VOID_PTR(POINTER_2_ADDRESS(buff_ptr->m_pool.m_blockbuffer_ptr) +
		buff_ptr->m_using.m_begin + offset),
		success_count,
		buf_ptr,
		success_count);


	DO_ONE_LOOP_END

	return success_count;
}

static SR_INLINE usize__t __copy_buffer_from_block_buffinfo(
	const block_buffinfo_t* PARAM_IN buff_ptr,
	uindex_t offset,
	void* PARAM_OUT buf_ptr,
	usize__t buf_size)
{
	usize__t success_count;
	DO_ONE_LOOP_BEGIN
	
	if (null == buf_ptr ||
		0 == buf_size   ||
		offset >= buff_ptr->m_using.m_size)
	{
		success_count = 0;
		break;
	}
	success_count = offset + buf_size;
	if (success_count > buff_ptr->m_using.m_size)
	{
		success_count = buff_ptr->m_using.m_size - offset;
	}
	else
	{
		success_count = buf_size;
	}

	sr_memory_move_s(
		buf_ptr,
		success_count,
		ADDRESS_2_VOID_PTR(POINTER_2_ADDRESS(buff_ptr->m_pool.m_blockbuffer_ptr) +
		buff_ptr->m_using.m_begin + offset),	
		success_count);

	DO_ONE_LOOP_END
	return success_count;
}

static SR_INLINE usize__t __copy_block_to_block(
	block_buffinfo_t* PARAM_INOUT dest_ptr,
	uindex_t dest_offset, 
	const block_buffinfo_t* PARAM_IN src_ptr,
	uindex_t src_offset,
	uindex_t copy_size)
{
	usize__t success_count;
	DO_ONE_LOOP_BEGIN

	if (null == src_ptr || null == dest_ptr)
	{
		success_count = 0;
		break;
	}

	if (null == src_ptr ||
		0 == copy_size  ||
		src_offset >= src_ptr->m_using.m_size||
		dest_offset >= dest_ptr->m_using.m_size)
	{
		success_count = 0;
		break;
	}
	success_count = src_offset + copy_size;
	if (success_count > src_ptr->m_using.m_size)
	{
		success_count = src_ptr->m_using.m_size - src_offset;
	}
	else
	{
		success_count = copy_size;
	}
	copy_size = success_count;
	
	success_count = dest_offset + copy_size;

	if (success_count > dest_ptr->m_using.m_size)
	{
		success_count = dest_ptr->m_using.m_size - dest_offset;
	}
	else
	{
		success_count = copy_size;
	}

	sr_memory_move_s(
		ADDRESS_2_VOID_PTR(
		POINTER_2_ADDRESS(dest_ptr->m_pool.m_blockbuffer_ptr) +
		dest_ptr->m_using.m_begin + dest_offset),
		success_count,
		ADDRESS_2_VOID_PTR(
		POINTER_2_ADDRESS(src_ptr->m_pool.m_blockbuffer_ptr) +
		src_ptr->m_using.m_begin + src_offset),
		success_count);


	DO_ONE_LOOP_END
	return success_count;
}



#endif	//SUNRED_LIB_BLOCK_HEADER










