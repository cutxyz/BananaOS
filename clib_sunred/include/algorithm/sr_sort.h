//////////////////////////////////////
// sr_sort.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef CLIB_SUNRED_SORT_H_
#define CLIB_SUNRED_SORT_H_

#include "../../algorithm/quicksort.h"

#ifdef STATIC_LIB_OR_SHADOW_DLL_IMPORT

SR_EXTERN_C_BEGIN
///////////////////////////////////////////////////////////////////
int quick_sort(sort_array_t* PARAM_INOUT array,
const void* PARAM_IN iterator_low_,
const void* PARAM_IN iterator_high_);
//////////////////////////////////////////////////////////////////////////
int quick_sort_int_array(INT_BUF_t* PARAM_INOUT array,
	int PARAM_IN iterator_low_,
	int PARAM_IN iterator_high_);

SR_EXTERN_C_END

#else

extern quick_sort_func quick_sort;
extern quick_sort_int_array_func quick_sort_int_array;

#endif //STATIC_LIB_OR_SHADOW_DLL_IMPORT


#endif	 //CLIB_SUNRED_SORT_H_
