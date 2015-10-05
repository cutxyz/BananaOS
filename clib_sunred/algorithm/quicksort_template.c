//////////////////////////////////////
// quicksort_template.c
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

#ifndef QUICKSORT_FUNC
#define QUICKSORT_FUNC
// 升序排列
static SR_INLINE int __order_partition(SORTARRAY PARAM_INOUT array,
	SORTARRAY_ITERATOR_ITR PARAM_INOUT iterator_low,
	SORTARRAY_ITERATOR_ITR PARAM_INOUT iterator_high,
	SORTARRAY_ITERATOR_REF PARAM_OUT iterator_out)
{
	int   cmp_result;
	SORTARRAY_ITEM_PTR pitem_high;
	SORTARRAY_ITEM_PTR pitem_low;

	// 取选取枢轴，并将iterator_low里面元素的值替换成枢轴的值
	SORTARRAY_SET_PRIVOT_ITEM_TO_LOW(array, iterator_low, iterator_high);

	pitem_high = GET_SORTARRAY_AT(array, iterator_high);
	pitem_low  = GET_SORTARRAY_AT(array, iterator_low);

	cmp_result = SORTARRAY_ITR_EQUELS(array, iterator_low, iterator_high);
	while (0 != cmp_result)
	{
		// 先看左边
		while (0 != cmp_result &&
			SORTARRAY_ITR_CMPITEM(array, pitem_high, pitem_low) >= 0)
		{
			SORTARRAY_ITR_DEC(array, iterator_high);
			pitem_high = GET_SORTARRAY_AT(array, iterator_high);
			cmp_result = SORTARRAY_ITR_EQUELS(array, iterator_low, iterator_high);
		}

		if (cmp_result)
		{
			if (STATUS_OK != SORTARRAY_SWAP_ITEM_BY_ITR(array, iterator_low, iterator_high))
			{
				return STATUS_ERROR_;
			}
		}

		// 再看右边
		while (0 != cmp_result &&
			SORTARRAY_ITR_CMPITEM(array, pitem_high, pitem_low) >= 0)
		{
			SORTARRAY_ITR_INC(array, iterator_low);
			pitem_low = GET_SORTARRAY_AT(array, iterator_low);
			cmp_result = SORTARRAY_ITR_EQUELS(array, iterator_low, iterator_high);
		}

		if (cmp_result)
		{
			if (STATUS_OK != SORTARRAY_SWAP_ITEM_BY_ITR(array, iterator_low, iterator_high))
			{
				return STATUS_ERROR_;
			}
		}

	}
	SORTARRAY_ITR_COPY_TO_REF(array, iterator_out, iterator_low);
	return STATUS_OK;
}

static SR_INLINE int __quick_sort(SORTARRAY PARAM_INOUT array,
	const SORTARRAY_ITERATOR_ITR PARAM_IN iterator_low_,
	const SORTARRAY_ITERATOR_ITR PARAM_IN iterator_high_)
{
	SORTARRAY_ITERATOR_INSTANCE  iterator_low;
	SORTARRAY_ITERATOR_INSTANCE  iterator_high;
	SORTARRAY_ITERATOR_INSTANCE  iterator_clip;
	int status;

	// 排序的数量很少，使用插入排序优化
	if (CHECK_ENTER_INSERT_SORT(array, iterator_low, iterator_high))
	{
		return QUICKSORT_INSERT_SORT(array, iterator_low, iterator_high);
	}
	
	// 开始快速排序（递归法）
	SORTARRAY_ITR_COPY(array, 
		               GET_ITERATOR_INSTANCE_ADDR(iterator_high), 
					   iterator_high_);
	SORTARRAY_ITR_COPY(array, 
		               GET_ITERATOR_INSTANCE_ADDR(iterator_low), 
					   iterator_low_);

	status = __order_partition(array, 
		                       GET_ITERATOR_INSTANCE_ADDR(iterator_low), 
							   GET_ITERATOR_INSTANCE_ADDR(iterator_high), 
							   GET_ITERATOR_INSTANCE_ADDR_REF(iterator_clip));
	if (status < STATUS_OK)
	{
		return status;
	}

	SORTARRAY_ITR_COPY(array, 
		               GET_ITERATOR_INSTANCE_ADDR(iterator_high), 
					   iterator_high_);
	SORTARRAY_ITR_COPY(array, 
		               GET_ITERATOR_INSTANCE_ADDR(iterator_low), 
					   iterator_low_);

	if (0 != SORTARRAY_ITR_EQUELS(array, 
		               GET_ITERATOR_INSTANCE_ADDR(iterator_clip), 
					   GET_ITERATOR_INSTANCE_ADDR(iterator_low)))
	{
		SORTARRAY_ITERATOR_INSTANCE itmp_pre;
		SORTARRAY_ITR_COPY(array, 
			               GET_ITERATOR_INSTANCE_ADDR(itmp_pre), 
						   GET_ITERATOR_INSTANCE_ADDR(iterator_clip));
		SORTARRAY_ITR_DEC(array, 
			              GET_ITERATOR_INSTANCE_ADDR(itmp_pre));
		status = __quick_sort(array, 
			                  GET_ITERATOR_INSTANCE_ADDR(iterator_low), 
							  GET_ITERATOR_INSTANCE_ADDR(itmp_pre));
		if (status < STATUS_OK)
		{
			return status;
		}
	}

	if (0 != SORTARRAY_ITR_EQUELS(array, 
		                          GET_ITERATOR_INSTANCE_ADDR(iterator_clip), 
								  GET_ITERATOR_INSTANCE_ADDR(iterator_high)))
	{
		SORTARRAY_ITERATOR_INSTANCE itmp_next;
		SORTARRAY_ITR_COPY(array, 
			               GET_ITERATOR_INSTANCE_ADDR(itmp_next), 
			               GET_ITERATOR_INSTANCE_ADDR(iterator_clip));
		SORTARRAY_ITR_INC(array, 
			               GET_ITERATOR_INSTANCE_ADDR(itmp_next));

		status = __quick_sort(array, 
			                  GET_ITERATOR_INSTANCE_ADDR(itmp_next), 
							  GET_ITERATOR_INSTANCE_ADDR(iterator_high));
		if (status < STATUS_OK)
		{
			return status;
		}
	}

	return STATUS_OK;
}
#endif//QUICKSORT_FUNC



