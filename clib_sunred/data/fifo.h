/*
 * fifo.h
 *
 *  Created on: 2015年4月27日
 *      Author: hehe
 */

#ifndef   SUNRED_CLIB_FIFO_H_
#define SUNRED_CLIB_FIFO_H_

// fifo ring
#include "fifo_ring_header.h"

 // char

// int
typedef int (*__bind_int_buffer_to_vfifo_header_func) (ring_fifo_header_t* PARAM_INOUT fifo_ptr,
	int* PARAM_IN buffer, unsigned int count);
typedef int (*__get_vfifo_int_data_length_func)(const ring_fifo_header_t* PARAM_INOUT fifo_ptr);
typedef  int (*__remain_vfifo_int_size_func) (const ring_fifo_header_t* PARAM_INOUT fifo_ptr);
typedef int (*__get_vfifo_intbuffer_size_func) (const ring_fifo_header_t* PARAM_INOUT fifo_ptr);


 //

#endif // SUNRED_CLIB_FIFO_H_ 
