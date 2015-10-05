/*
 * fifo_ring_header.h
 *
 *  Created on: 2015年4月27日
 *      Author: hehe
 */

#ifndef  SUNRED_CLIB_FIFO_RING_HEADER_H_
#define SUNRED_CLIB_FIFO_RING_HEADER_H_

#include "../include/type.h"
typedef struct st_ring_fifo_header
{
	volatile unsigned int m_begin_index;
	volatile unsigned int m_end_index;

#if defined(__BIG_ENDIAN_BITFIELD)
	unsigned int          m_is_full   : 1;
	unsigned int          m_fifo_size : 31;
#else  //defined(__LITTLE_ENDIAN_BITFIELD)        
	unsigned int          m_fifo_size : 31;
	unsigned int          m_is_full   : 1;
#endif

	unsigned char*    m_fifo_buffer;
}ring_fifo_header_t;


static SR_FORCE_INLINE void __init_fifo_header(ring_fifo_header_t* PARAM_IN fifo_ptr)
{
	fifo_ptr->m_begin_index = 0;
	fifo_ptr->m_end_index   = 0;
	fifo_ptr->m_is_full     = 0;
	fifo_ptr->m_fifo_size   = 0;
	fifo_ptr->m_fifo_buffer = null;
}

static SR_FORCE_INLINE void __reset_fifo_index (ring_fifo_header_t* PARAM_IN fifo_ptr)
{
	fifo_ptr->m_begin_index = 0;
	fifo_ptr->m_end_index   = 0;
	fifo_ptr->m_is_full     = 0;
}
static SR_FORCE_INLINE void __clean_fifo_index (ring_fifo_header_t* PARAM_IN fifo_ptr)
{
	fifo_ptr->m_begin_index = fifo_ptr->m_end_index;
	fifo_ptr->m_is_full     = 0;
}

static SR_FORCE_INLINE unsigned int __check_fifo_full(const ring_fifo_header_t* PARAM_IN fifo_ptr)
{
	return fifo_ptr->m_is_full;
}

static SR_FORCE_INLINE int __bind_buffer_to_fifo_header (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	unsigned char* PARAM_IN buffer, unsigned int buffer_size)
{

	if (null == buffer || 0 == buffer_size)
	{
		return STATUS_INVALID_PARAMS;
	}
	else
	{
		__reset_fifo_index(fifo_ptr);
		fifo_ptr->m_fifo_buffer = buffer;
		fifo_ptr->m_fifo_size   = buffer_size;
		return STATUS_OK;
	}
}

static SR_FORCE_INLINE int __get_fifo_data_length(const ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	int length = (int)fifo_ptr->m_end_index - (int)fifo_ptr->m_begin_index;
	if (length < 0)
	{
		length += (int)fifo_ptr->m_fifo_size;
	}
	else if (fifo_ptr->m_is_full)
	{
		length = (int)fifo_ptr->m_fifo_size;
	}
	return length;
}

static SR_FORCE_INLINE int __remain_fifo_size (const ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	int __size = __get_fifo_data_length(fifo_ptr);
	if (__size >= 0)
	{
		__size =  (int)fifo_ptr->m_fifo_size - __size;
	}
	return __size;
}

static SR_FORCE_INLINE int __get_fifobuffer_size (const ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return fifo_ptr->m_fifo_size;
}

static SR_FORCE_INLINE unsigned char* __get_fifobuffer (ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return fifo_ptr->m_fifo_buffer;
}

static SR_FORCE_INLINE const unsigned char* __get_fifobuffer_const (const ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return fifo_ptr->m_fifo_buffer;
}

static SR_FORCE_INLINE unsigned char* __get_fifo_beginbuffer (ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return fifo_ptr->m_fifo_buffer + fifo_ptr->m_begin_index;
}

static SR_FORCE_INLINE unsigned char* __get_fifo_endbuffer (ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return fifo_ptr->m_fifo_buffer + fifo_ptr->m_end_index;
}

static SR_FORCE_INLINE unsigned char* __internal_get_fifo_value_at(ring_fifo_header_t* PARAM_INOUT fifo_ptr, 
	int index)
{
	int val_index;
	val_index = fifo_ptr->m_begin_index + index;
	if (val_index >= (int)fifo_ptr->m_fifo_size)
	{
		val_index -= fifo_ptr->m_fifo_size;
	}
	return fifo_ptr->m_fifo_buffer + val_index;
}

static SR_FORCE_INLINE unsigned char* __get_fifo_value_at(ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	int index)
{
	if (index >= 0 && index < __get_fifo_data_length(fifo_ptr))
	{
		return __internal_get_fifo_value_at(fifo_ptr, index);
	}
	else
	{
		return null;
	}
}

#endif // SUNRED_CLIB_FIFO_RING_HEADER_H_ 
