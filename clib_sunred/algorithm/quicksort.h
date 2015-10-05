//////////////////////////////////////
// quicksort.h
// Created on: 2015-7-24
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef SUNRED_LIB_QUICKSORT_H_
#define SUNRED_LIB_QUICKSORT_H_

#include "../include/type.h"
#include "../util/object_type.h"
#include "../data/iterator.h"

typedef void* (*get_at_func)(void* PARAM_IN array_ptr,
	const void* PARAM_IN itr_ptr);
typedef int (*value_swap_func)(void* PARAM_IN array_ptr,
	const void* PARAM_IN first_itr_ptr,
	const void* PARAM_IN second_itr_ptr);
typedef int(*compare_two_array_item_func)(
	const void* PARAM_OUT first_item,
	const void* PARAM_IN second_item);
typedef void* (*select_keyitem_func)(void* PARAM_IN array_ptr,
	const void* PARAM_IN first_itr_ptr,
	const void* PARAM_IN second_itr_ptr);

typedef struct st_sort_array
{
	void*              array_ptr;

	iterator_method_t* itr_method;
	get_at_func        at;
	value_swap_func	   swap;

	compare_two_array_item_func cmp;
}sort_array_t;

//////////////////////////////////////////////////////////////////////////
typedef struct st_int_buf
{
	int* m_buf;
	int  m_size;
}INT_BUF_t;

typedef int (*quick_sort_int_array_func)(INT_BUF_t* PARAM_INOUT array,
	int PARAM_IN iterator_low_,
	int PARAM_IN iterator_high_);

typedef int (*quick_sort_func)(sort_array_t* PARAM_INOUT array,
	const void* PARAM_IN iterator_low_,
	const void* PARAM_IN iterator_high_);

#endif	 //SUNRED_LIB_QUICKSORT_H_
