//////////////////////////////////////
// quicksort.c
// Created on: 2015-7-24
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "quicksort_template.c"
#include "../include/algorithm/sr_sort.h"

int quick_sort(sort_array_t* PARAM_INOUT array,
	const void* PARAM_IN iterator_low_,
	const void* PARAM_IN iterator_high_)
{
	if (null == array ||
		null == iterator_low_ ||
		null == iterator_high_ ||
		null == array->at ||
		null == array->array_ptr ||
		null == array->cmp ||
		null == array->swap ||
		null == array->itr_method ||
		null == array->itr_method->equals ||
		null == array->itr_method->copy ||
		null == array->itr_method->decrease ||
		null == array->itr_method->increase ||
		null == array->at(array->array_ptr, iterator_low_) ||
		null == array->at(array->array_ptr, iterator_high_))
	{
		return STATUS_INVALID_PARAMS;
	}
	return __quick_sort(array, iterator_low_, iterator_high_);
}

//#include "../clib_sunred_interal.h"
//void __init_sunred_lib_quick_sort_array(clib_sunred_funcions_t* PARAM_INOUT lib_ptr)
//{
//	lib_ptr->quick_sort = quick_sort;
//}


