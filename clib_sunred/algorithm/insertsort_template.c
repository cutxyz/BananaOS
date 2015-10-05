//////////////////////////////////////
// insertsort_template.c
// Created on: 2015-7-24
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "quicksort.h"

#ifndef MAX_BASE_ITERATOR_SIZE
#define MAX_BASE_ITERATOR_SIZE (5)
#endif//MAX_BASE_ITERATOR_SIZE

#ifndef SORTARRAY_ITERATOR_ITR 
#define SORTARRAY_ITERATOR_ITR void*
#endif//SORTARRAY_ITERATOR

#ifndef SORTARRAY_ITERATOR_REF 
#define SORTARRAY_ITERATOR_REF void*
#endif//SORTARRAY_ITERATOR_REF

#ifndef SORTARRAY_ITERATOR_INSTANCE
#define SORTARRAY_ITERATOR_INSTANCE iterator_instance_t
typedef struct st_iterator_instance
{
	reg_t m_itr_ins[MAX_BASE_ITERATOR_SIZE];
}iterator_instance_t;

#endif // ITERATOR_INSTANCE

#ifndef GET_ITERATOR_INSTANCE_ADDR 
#define GET_ITERATOR_INSTANCE_ADDR(ins) &(ins) 
#endif//GET_ITERATOR_INSTANCE_ADDR

#ifndef GET_ITERATOR_INSTANCE_ADDR_REF 
#define GET_ITERATOR_INSTANCE_ADDR_REF(ins) &(ins) 
#endif//GET_ITERATOR_INSTANCE_ADDR_REF

#ifndef SORTARRAY
#define SORTARRAY void*
#endif//SORTARRAY

#ifndef SORTARRAY_ITEM_PTR
#define SORTARRAY_ITEM_PTR	void*
#endif//SORTARRAY_ITEM_PTR


#ifndef GET_SORTARRAY_AT
#define GET_SORTARRAY_AT(arr,_at) (((sort_array_t*)(arr))->at(((sort_array_t*)(arr))->array_ptr,(_at)))
#endif// GET_ARRAY_AT

#ifndef SORTARRAY_ITR_EQUELS
#define SORTARRAY_ITR_EQUELS(arr,itr1_ptr,itr2_ptr) (((sort_array_t*)(arr))->itr_method->equals((itr1_ptr), (itr2_ptr)))
#endif//SORTARRAY_ITR_EQUELS

#ifndef SORTARRAY_ITR_CMPITEM
#define SORTARRAY_ITR_CMPITEM(arr,itm1,itm2) (((sort_array_t*)(arr))->cmp((itm1), (itm2)))
#endif//SORTARRAY_ITR_CMPITEM

#ifndef SORTARRAY_ITR_INC
#define SORTARRAY_ITR_INC(arr,itr_ptr)	(((sort_array_t*)(arr))->itr_method->increase(itr_ptr))
#endif//SORTARRAY_ITR_INC

#ifndef SORTARRAY_ITR_DEC
#define SORTARRAY_ITR_DEC(arr,itr_ptr)	(((sort_array_t*)(arr))->itr_method->decrease(itr_ptr))
#endif//SORTARRAY_ITR_DEC

#ifndef SORTARRAY_ITR_COPY
#define SORTARRAY_ITR_COPY(arr,des,src)	  (((sort_array_t*)(arr))->itr_method->copy(des, src))
#endif//SORTARRAY_ITR_COPY

#ifndef SORTARRAY_ITR_COPY_TO_REF
#define SORTARRAY_ITR_COPY_TO_REF  SORTARRAY_ITR_COPY
#endif//SORTARRAY_ITR_COPY_TO_REF

#ifndef SORTARRAY_SWAP_ITEM_BY_ITR
#define SORTARRAY_SWAP_ITEM_BY_ITR(arr,itr1_ptr,itr2_ptr) (((sort_array_t*)(arr))->swap(((sort_array_t*)(arr))->array_ptr, itr1_ptr, itr2_ptr))
#endif//SORTARRAY_SWAP_ITEM_BY_ITR

#ifndef SORTARRAY_SET_PRIVOT_ITEM_TO_LOW
#define SORTARRAY_SET_PRIVOT_ITEM_TO_LOW(arr,itrlow,itrhigh)
#endif//SORTARRAY_SET_PRIVOT_ITEM_TO_LOW

#ifndef CHECK_ENTER_INSERT_SORT
#define CHECK_ENTER_INSERT_SORT(arr,itrlow,itrhigh)	(0)
#endif//CHECK_ENTER_INSERT_SORT

#ifndef QUICKSORT_INSERT_SORT
#define QUICKSORT_INSERT_SORT(arr,itrlow,itrhigh)	(0)
#endif//QUICKSORT_INSERT_SORT

#ifndef INSERTSORT_FUNC
#define INSERTSORT_FUNC

static SR_INLINE int __insert_sort(SORTARRAY PARAM_INOUT array,
	const SORTARRAY_ITERATOR_ITR PARAM_IN iterator_low_,
	const SORTARRAY_ITERATOR_ITR PARAM_IN iterator_high_)
{
	SORTARRAY_ITERATOR_INSTANCE  iterator_up;
	SORTARRAY_ITERATOR_INSTANCE  iterator_down;
	SORTARRAY_ITERATOR_INSTANCE  iterator_tmp;
	//int status;
	int   itrcmp_result;

	itrcmp_result = SORTARRAY_ITR_EQUELS(array, iterator_low_, iterator_high_);
	if (0 == itrcmp_result)
	{
		return STATUS_OK;
	}
	
	SORTARRAY_ITR_COPY(array,
		               GET_ITERATOR_INSTANCE_ADDR(iterator_up),
					   iterator_low_);

	SORTARRAY_ITR_INC(array, GET_ITERATOR_INSTANCE_ADDR(iterator_up));

	itrcmp_result = SORTARRAY_ITR_EQUELS(array,
		GET_ITERATOR_INSTANCE_ADDR(iterator_up),
		iterator_high_);
	while (itrcmp_result)
	{ 
		SORTARRAY_ITEM_PTR key;

		key = GET_SORTARRAY_AT(array, GET_ITERATOR_INSTANCE_ADDR(iterator_up));

		SORTARRAY_ITR_COPY(array,
			GET_ITERATOR_INSTANCE_ADDR(iterator_down),
			GET_ITERATOR_INSTANCE_ADDR(iterator_up));

		itrcmp_result = SORTARRAY_ITR_EQUELS(array,
			                                 GET_ITERATOR_INSTANCE_ADDR(iterator_down),
			                                 iterator_low_);

		while (itrcmp_result)
		{
			SORTARRAY_ITEM_PTR item_ptr;
			int cmp_result;

			SORTARRAY_ITR_COPY(array,
				GET_ITERATOR_INSTANCE_ADDR(iterator_tmp),
				GET_ITERATOR_INSTANCE_ADDR(iterator_down));

			SORTARRAY_ITR_DEC(array, GET_ITERATOR_INSTANCE_ADDR(iterator_down));
			
			item_ptr = GET_SORTARRAY_AT(array, GET_ITERATOR_INSTANCE_ADDR(iterator_down));
			cmp_result = SORTARRAY_ITR_CMPITEM(array, key, item_ptr);
			if (cmp_result < 0)
			{
				SORTARRAY_SWAP_ITEM_BY_ITR(array, 
					GET_ITERATOR_INSTANCE_ADDR(iterator_tmp), 
					GET_ITERATOR_INSTANCE_ADDR(iterator_down));
				key = GET_SORTARRAY_AT(array, GET_ITERATOR_INSTANCE_ADDR(iterator_tmp));
			}
			else
			{
				break;
			}


			itrcmp_result = SORTARRAY_ITR_EQUELS(array,
			                                 GET_ITERATOR_INSTANCE_ADDR(iterator_down),
			                                 iterator_low_);
		}

		SORTARRAY_ITR_INC(array, GET_ITERATOR_INSTANCE_ADDR(iterator_up));
		itrcmp_result = SORTARRAY_ITR_EQUELS(array,
			GET_ITERATOR_INSTANCE_ADDR(iterator_up),
			iterator_high_);
	}
	return STATUS_OK;
}
#endif//INSERTSORT_FUNC



