//////////////////////////////////////
// fifo_ring_template.c
//
//  Created on: 2015年7月28日
//      Author:李镇城  （ cut / cutxyz）
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "fifo_ring.h"

#ifndef FIFO_RING_VAL
#define FIFO_RING_VAL  int
#endif//FIFO_RING_VAL

#ifndef FIFO_RING_VAL_SIZE 
#define FIFO_RING_VAL_SIZE sizeof(int)
#endif//FIFO_RING_VAL_SIZE

#ifndef _bind_buffer_to_vfifo_header
#define _bind_buffer_to_vfifo_header   __bind_buffer_to_vfifo_header
static SR_FORCE_INLINE int __bind_buffer_to_vfifo_header (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	FIFO_RING_VAL* PARAM_IN buffer, unsigned int count)
{
	return __bind_buffer_to_fifo_header(fifo_ptr, 
		(unsigned char*)buffer, 
		(FIFO_RING_VAL_SIZE  * count));
}
#endif//_bind_buffer_to_vfifo_header

#ifndef _get_vfifo_data_length
#define _get_vfifo_data_length  __get_vfifo_data_length
static SR_FORCE_INLINE int __get_vfifo_data_length(const ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	int length = __get_fifo_data_length(fifo_ptr);
	return (length / FIFO_RING_VAL_SIZE);
}								  
#endif//_get_vfifo_data_length

#ifndef _remain_vfifo_size
#define _remain_vfifo_size  __remain_vfifo_size
static SR_FORCE_INLINE int __remain_vfifo_size (const ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	int __size = __remain_fifo_size(fifo_ptr);
	return (__size / FIFO_RING_VAL_SIZE);
}
#endif//_remain_vfifo_size

#ifndef _get_vfifobuffer_size
#define _get_vfifobuffer_size  __get_vfifobuffer_size
static SR_FORCE_INLINE int __get_vfifobuffer_size (const ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return (__get_fifobuffer_size(fifo_ptr) / FIFO_RING_VAL_SIZE);
}
#endif//_get_vfifobuffer_size

#ifndef _get_vfifobuffer
#define _get_vfifobuffer  __get_vfifobuffer
static SR_FORCE_INLINE FIFO_RING_VAL* __get_vfifobuffer(ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return (FIFO_RING_VAL*)__get_fifobuffer(fifo_ptr);
}
#endif//_get_vfifobuffer

#ifndef _get_vfifobuffer_const
#define _get_vfifobuffer_const __get_vfifobuffer_const
static SR_FORCE_INLINE const FIFO_RING_VAL* __get_vfifobuffer_const(const ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return (const FIFO_RING_VAL*)__get_fifobuffer_const(fifo_ptr);
}
#endif//_get_vfifobuffer_const

#ifndef _get_vfifo_beginbuffer
#define _get_vfifo_beginbuffer __get_vfifo_beginbuffer
static SR_FORCE_INLINE FIFO_RING_VAL* __get_vfifo_beginbuffer(ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return (FIFO_RING_VAL*)__get_vfifo_beginbuffer(fifo_ptr);
}
#endif//_get_vfifo_beginbuffer


#ifndef _get_vfifo_endbuffer
#define _get_vfifo_endbuffer __get_vfifo_endbuffer
static SR_FORCE_INLINE FIFO_RING_VAL* __get_vfifo_endbuffer(ring_fifo_header_t* PARAM_INOUT fifo_ptr)
{
	return (FIFO_RING_VAL*)__get_fifo_endbuffer(fifo_ptr); 
}
#endif//_get_vfifo_endbuffer

#ifndef _internal_get_vfifo_value_at
#define _internal_get_vfifo_value_at   __internal_get_vfifo_value_at
static SR_FORCE_INLINE FIFO_RING_VAL* __internal_get_vfifo_value_at(ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	int index)
{
	return (FIFO_RING_VAL*)__internal_get_fifo_value_at(fifo_ptr, (index * FIFO_RING_VAL_SIZE));
}
#endif// _internal_get_vfifo_value_at

#ifndef _get_vfifo_value_at
#define _get_vfifo_value_at  __get_vfifo_value_at
static SR_FORCE_INLINE FIFO_RING_VAL* __get_vfifo_value_at(ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	int index)
{
	return (FIFO_RING_VAL*)__get_fifo_value_at(fifo_ptr, (index * FIFO_RING_VAL_SIZE));
}
#endif//_get_vfifo_value_at

#ifndef _push_back_vfifo
#define _push_back_vfifo  __push_back_vfifo
static SR_FORCE_INLINE int __push_back_vfifo (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	const FIFO_RING_VAL* PARAM_IN buffer,
	unsigned int count)
{
	int success_count;
	success_count = __push_back_fifo(fifo_ptr, 
		                             (const unsigned char*)buffer, 
		                             (count * FIFO_RING_VAL_SIZE));
	if (success_count <= 0)
	{
		return success_count;
	}
	else
	{
		return (success_count / FIFO_RING_VAL_SIZE);
	}
}
#endif//_push_back_vfifo

#ifndef _pop_front_vfifo
#define _pop_front_vfifo __pop_front_vfifo
static SR_FORCE_INLINE int __pop_front_vfifo (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
		unsigned int pop_size)
{
	int success_count;
	success_count = __pop_front_vfifo(fifo_ptr, (pop_size*FIFO_RING_VAL_SIZE));
	if (success_count <= 0)
	{
		return success_count;
	}
	else
	{
		return (success_count / FIFO_RING_VAL_SIZE);
	}
}
#endif//_pop_front_vfifo


#ifndef _force_push_back_vfifo
#define _force_push_back_vfifo  __force_push_back_vfifo
static SR_FORCE_INLINE int __force_push_back_vfifo(ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	const FIFO_RING_VAL* PARAM_IN buffer,
	unsigned int count)
{
	int success_count;
	success_count = __force_push_back_fifo(fifo_ptr, 
		             (const unsigned char*)buffer,
					 (count * FIFO_RING_VAL_SIZE));

	if (success_count <= 0)
	{
		return success_count;
	}
	else
	{
		return (success_count / FIFO_RING_VAL_SIZE);
	}
}
#endif//_force_push_back_vfifo


#ifndef _pop_front_vfifo_to_buff
#define _pop_front_vfifo_to_buff  __pop_front_vfifo_to_buff
static SR_FORCE_INLINE int __pop_front_vfifo_to_buff (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
		unsigned int   count,
		FIFO_RING_VAL* buffer)
{
	int success_count;
	success_count = __pop_front_fifo_to_buff(fifo_ptr,
		(count * FIFO_RING_VAL_SIZE),
		(unsigned char*)buffer);

	if (success_count <= 0)
	{
		return success_count;
	}
	else
	{
		return (success_count / FIFO_RING_VAL_SIZE);
	}
}
#endif//_pop_front_vfifo_to_buff


