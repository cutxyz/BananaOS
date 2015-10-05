/*
 * fifo_ring.h
 *
 *  Created on: 2015年4月27日
 *      Author: hehe
 */

#ifndef SUNRED_CLIB_FIFO_RING_H_
#define SUNRED_CLIB_FIFO_RING_H_

//#include "../include/util.h"
#include "fifo_ring_header.h"

static SR_FORCE_INLINE int __internal_push_back_fifo (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
		const unsigned char* PARAM_IN buffer,
		unsigned int buffer_size)
{
	int copy_size = buffer_size;
	if (copy_size > 0)
	{
		int endindex = fifo_ptr->m_end_index;
		sr_memcpy(__get_fifo_endbuffer(fifo_ptr), buffer, copy_size);
		endindex += copy_size;
		if (endindex == fifo_ptr->m_fifo_size)
		{
			endindex = 0;
		}
		if (endindex == fifo_ptr->m_begin_index)
		{
			fifo_ptr->m_is_full = 1;
		}
		fifo_ptr->m_end_index = endindex;
	}
	else
	{
		copy_size = STATUS_ERROR_;
	}
	return copy_size;
}

static SR_FORCE_INLINE int __push_back_fifo (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
		const unsigned char* PARAM_IN buffer,
		unsigned int buffer_size)
{
	int copy_size;
	int success_count;
	int copy_block_size;

	if (null == fifo_ptr->m_fifo_buffer ||
		0 == fifo_ptr->m_fifo_size)
	{
		return STATUS_INVALID_PARAMS;
	}

	copy_size = __remain_fifo_size(fifo_ptr);
	if (copy_size > (int)buffer_size)
	{
		copy_size = buffer_size;
	}
	if (0 == copy_size)
	{
		return copy_size;
	}

	success_count   = 0;
	copy_block_size = (int)fifo_ptr->m_fifo_size - (int)fifo_ptr->m_end_index;
	if (copy_block_size < copy_size)
	{

		if (copy_block_size > 0)
		{
			int tmp_success_count;

			tmp_success_count = __internal_push_back_fifo(fifo_ptr, buffer, copy_block_size);
			copy_size         = copy_size - tmp_success_count;
			buffer           += tmp_success_count;
			success_count    += tmp_success_count;
		}
		else
		{
			return STATUS_INVALID_PARAMS;
		}

		if (0 == copy_size)
		{
			return success_count;
		}
	}

	success_count += __internal_push_back_fifo(fifo_ptr, buffer, copy_size);
	return success_count;
}

static SR_FORCE_INLINE int __pop_front_fifo (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
		unsigned int pop_size)
{
	int data_length;
	unsigned int begin_index;

	if (null == fifo_ptr->m_fifo_buffer ||
		0 == fifo_ptr->m_fifo_size || 
		0 == pop_size)
	{
		return 0;
	}

	data_length = __get_fifo_data_length(fifo_ptr);
	if (data_length < (int)pop_size)
	{
		pop_size = data_length;
	}
	begin_index = fifo_ptr->m_begin_index + pop_size;

	if (begin_index >= fifo_ptr->m_fifo_size)
	{
		begin_index -= fifo_ptr->m_fifo_size;
	}
	fifo_ptr->m_is_full = 0;

	fifo_ptr->m_begin_index = begin_index;
	return pop_size;
}

static SR_FORCE_INLINE int __force_push_back_fifo(ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	const unsigned char* PARAM_IN buffer,
	unsigned int buffer_size)
{
	int remain_size = __remain_fifo_size(fifo_ptr);

	if ((int)buffer_size > remain_size)
	{
		int fifo_size = __get_fifobuffer_size(fifo_ptr);
		if ((int)buffer_size > fifo_size)
		{
			__reset_fifo_index(fifo_ptr);
			buffer += (buffer_size - fifo_size);
			buffer_size = fifo_size;
		}
		else if ((int)buffer_size == fifo_size)
		{
			__reset_fifo_index(fifo_ptr);
		}
		else
		{
			int pop_size = buffer_size - remain_size;
			__pop_front_fifo(fifo_ptr, pop_size);
		}
	}
	return 	__push_back_fifo(fifo_ptr, buffer, buffer_size);
}

static SR_FORCE_INLINE int __pop_front_fifo_to_buff (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
		unsigned int   pop_size,
		unsigned char* buffer)
{
	int data_length;
	int remainsize;
	unsigned int begin_index;

	if (null == fifo_ptr->m_fifo_buffer ||
		0 == fifo_ptr->m_fifo_size ||
		0 == pop_size)
	{
		return 0;
	}

	data_length = __get_fifo_data_length(fifo_ptr);
	if (data_length < (int)pop_size)
	{
		pop_size = data_length;
	}

	remainsize = fifo_ptr->m_fifo_size - fifo_ptr->m_begin_index;
	if (remainsize >= (int)pop_size || 0 == remainsize)
	{
		sr_memcpy(buffer, __get_fifo_beginbuffer(fifo_ptr), pop_size);
	}
	else if (remainsize > 0)
	{
		sr_memcpy(buffer, __get_fifo_beginbuffer(fifo_ptr), remainsize);
		sr_memcpy(buffer + remainsize, __get_fifobuffer(fifo_ptr), (pop_size - remainsize));
	}

	begin_index = fifo_ptr->m_begin_index + pop_size;

	if (begin_index >= fifo_ptr->m_fifo_size)
	{
		begin_index -= fifo_ptr->m_fifo_size;
	}

	fifo_ptr->m_is_full = 0;
	fifo_ptr->m_begin_index = begin_index;
	return pop_size;
}


#endif // SUNRED_CLIB_FIFO_RING_H_ 
