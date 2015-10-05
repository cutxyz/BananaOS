//////////////////////////////////////
// quicksort.c
// Created on: 2015-7-24
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////


#define SORTARRAY_ITERATOR_ITR              int	
#define SORTARRAY_ITERATOR_REF              int*
#define SORTARRAY_ITERATOR_INSTANCE         int
#define GET_ITERATOR_INSTANCE_ADDR(ins)     (ins)
#define GET_ITERATOR_INSTANCE_ADDR_REF(ins) &(ins)
#define SORTARRAY                           INT_BUF_t*
#define SORTARRAY_ITEM_PTR	                int*

#define GET_SORTARRAY_AT(arr,_at)                   ((arr)->m_buf + (_at))
#define SORTARRAY_ITR_EQUELS(arr,itr1_ptr,itr2_ptr) ((itr1_ptr)-(itr2_ptr))
#define SORTARRAY_ITR_CMPITEM(arr,itm1,itm2)        (*(itm1)-*(itm2))
#define SORTARRAY_ITR_INC(arr,itr_ptr)	            (++(itr_ptr))
#define SORTARRAY_ITR_DEC(arr,itr_ptr)	            (--(itr_ptr))
#define SORTARRAY_ITR_COPY(arr,des,src)	            ((des) = (src))
#define SORTARRAY_ITR_COPY_TO_REF(arr,des,src)      (*(des) = (src))
#define SORTARRAY_SWAP_ITEM_BY_ITR  int_value_swap


#include "quicksort.h"
#include "quicksort_template.c"
#include "../include/algorithm/sr_sort.h"

static SR_INLINE int int_value_swap(SORTARRAY PARAM_INOUT arr, SORTARRAY_ITERATOR_ITR itr1, SORTARRAY_ITERATOR_ITR itr2)
{
	int tmp = *GET_SORTARRAY_AT(arr, itr1);
	*GET_SORTARRAY_AT(arr, itr1) = *GET_SORTARRAY_AT(arr, itr2);
	*GET_SORTARRAY_AT(arr, itr2) = tmp;
	return STATUS_OK;
}

int quick_sort_int_array(INT_BUF_t* PARAM_INOUT array,
	int PARAM_IN iterator_low_,
	int PARAM_IN iterator_high_)
{
	if (null == array ||											  
		null == array->m_buf ||
		0 >= array->m_size ||
		iterator_low_ < 0 ||
		iterator_high_ >= array->m_size)
	{
		return STATUS_INVALID_PARAMS;
	}
	return __quick_sort(array, iterator_low_, iterator_high_);
}

//#include "../clib_sunred_interal.h"
//void __init_sunred_lib_quick_sort_int_array(clib_sunred_funcions_t* PARAM_INOUT lib_ptr)
//{
//	lib_ptr->quick_sort_int = quick_sort_int_array;
//}



