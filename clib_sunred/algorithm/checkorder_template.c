//////////////////////////////////////
// checkorder_template.c
// Created on: 2015-7-28
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "../include/type.h"

#ifndef SEQUENCE_ARRAY
#define SEQUENCE_ARRAY int*
#endif//SEQUENCE_ARRAY

#ifndef SEQUENCE_ARRAY_ITR
#define SEQUENCE_ARRAY_ITR int
#endif//SEQUENCE_ARRAY_ITR

#ifndef SEQUENCE_ARRAY_ITEM_PTR
#define SEQUENCE_ARRAY_ITEM_PTR	int*
#endif//SEQUENCE_ARRAY_ITEM_PTR

#ifndef GET_SEQUENCE_ARRAY_AT
#define GET_SEQUENCE_ARRAY_AT(arr,_at)                       ((int*)(arr) + (_at))
#endif//GET_SEQUENCE_ARRAY_AT
					  
#ifndef SEQUENCE_ARRAY_VALUE_CMP
#define SEQUENCE_ARRAY_VALUE_CMP(itm1_ptr, itm2_ptr)         (*(itm1_ptr)-*(itm2_ptr))
#endif//SEQUENCE_ARRAY_VALUE_CMP

#ifndef SEQUENCE_ARRAY_ITR_EQUELS
#define SEQUENCE_ARRAY_ITR_EQUELS(arr,itr1_ptr,itr2_ptr)     ((itr1_ptr)-(itr2_ptr))
#endif//SEQUENCE_ARRAY_ITR_EQUELS

#ifndef SEQUENCE_ARRAY_ITR_INC
#define SEQUENCE_ARRAY_ITR_INC(arr,itr_ptr)	                 (++(itr_ptr))
#endif//SEQUENCE_ARRAY_ITR_INC

#ifndef SEQUENCE_ARRAY_ITR_DEC
#define SEQUENCE_ARRAY_ITR_DEC(arr,itr_ptr)	                 (--(itr_ptr))
#endif//SEQUENCE_ARRAY_ITR_DEC


static SR_INLINE int __get_order_first_inc_count(const SEQUENCE_ARRAY PARAM_IN arr,
	SEQUENCE_ARRAY_ITR PARAM_IN itr1,
	SEQUENCE_ARRAY_ITR PARAM_IN itr2)
{
	SEQUENCE_ARRAY_ITEM_PTR itm1;
	SEQUENCE_ARRAY_ITEM_PTR itm2;
	int res = 1;
	if (0 == SEQUENCE_ARRAY_ITR_EQUELS(arr, itr1, itr2))
	{
		return 1;
	}

	itm1 = GET_SEQUENCE_ARRAY_AT(arr, itr1);

	do
	{
		SEQUENCE_ARRAY_ITR_INC(arr, itr1);
		itm2 = GET_SEQUENCE_ARRAY_AT(arr, itr1);
		if (SEQUENCE_ARRAY_VALUE_CMP(itm1, itm2) > 0)
		{
			break;
		}
		itm1 = itm2;
		++res;
	} while (0 != SEQUENCE_ARRAY_ITR_EQUELS(arr, itr1, itr2));

	return res;
}

static SR_INLINE int __get_order_fisrt_dec_count(const SEQUENCE_ARRAY PARAM_IN arr,
	SEQUENCE_ARRAY_ITR PARAM_IN itr1,
	SEQUENCE_ARRAY_ITR PARAM_IN itr2)
{
	SEQUENCE_ARRAY_ITEM_PTR itm1;
	SEQUENCE_ARRAY_ITEM_PTR itm2;
	int res = 0;
	if (0 == SEQUENCE_ARRAY_ITR_EQUELS(arr, itr1, itr2))
	{
		return 1;
	}

	itm1 = GET_SEQUENCE_ARRAY_AT(arr, itr1);

	do
	{
		SEQUENCE_ARRAY_ITR_INC(arr, itr1);
		itm2 = GET_SEQUENCE_ARRAY_AT(arr, itr1);
		if (SEQUENCE_ARRAY_VALUE_CMP(itm1, itm2) < 0)
		{
			break;
		}
		itm1 = itm2;
		++res;
	} while (0 != SEQUENCE_ARRAY_ITR_EQUELS(arr, itr1, itr2));

	return res;
}

static SR_INLINE int __check_order_inc(const SEQUENCE_ARRAY PARAM_IN arr,
	SEQUENCE_ARRAY_ITR PARAM_IN itr1,
	SEQUENCE_ARRAY_ITR PARAM_IN itr2)
{
	SEQUENCE_ARRAY_ITEM_PTR itm1;
	SEQUENCE_ARRAY_ITEM_PTR itm2;
	int res = TRUE;
	if (0 == SEQUENCE_ARRAY_ITR_EQUELS(arr, itr1, itr2))
	{
		return TRUE;
	}

	itm1 = GET_SEQUENCE_ARRAY_AT(arr, itr1);

	do
	{
		SEQUENCE_ARRAY_ITR_INC(arr, itr1);
		itm2 = GET_SEQUENCE_ARRAY_AT(arr, itr1);
		if (SEQUENCE_ARRAY_VALUE_CMP(itm1, itm2) > 0)
		{
			res = FALSE;
			break;
		}
		itm1 = itm2;
	} while (0 != SEQUENCE_ARRAY_ITR_EQUELS(arr, itr1, itr2));

	return res;
}

static SR_INLINE int __check_order_dec(const SEQUENCE_ARRAY PARAM_IN arr,
	SEQUENCE_ARRAY_ITR PARAM_IN itr1,
	SEQUENCE_ARRAY_ITR PARAM_IN itr2)
{
	SEQUENCE_ARRAY_ITEM_PTR itm1;
	SEQUENCE_ARRAY_ITEM_PTR itm2;
	int res = TRUE;
	if (0 == SEQUENCE_ARRAY_ITR_EQUELS(arr, itr1, itr2))
	{
		return TRUE;
	}

	itm1 = GET_SEQUENCE_ARRAY_AT(arr, itr1);

	do
	{
		SEQUENCE_ARRAY_ITR_INC(arr, itr1);
		itm2 = GET_SEQUENCE_ARRAY_AT(arr, itr1);
		if (SEQUENCE_ARRAY_VALUE_CMP(itm1, itm2) < 0)
		{
			res = FALSE;
			break;
		}
		itm1 = itm2;
	} while (0 != SEQUENCE_ARRAY_ITR_EQUELS(arr, itr1, itr2));

	return res;
}




