//////////////////////////////////////
// dlllib_sunred.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "clib_sunred.h"
#include < Windows.h >

#define _STR_(X) X

quick_sort_func           quick_sort = NULL;
quick_sort_int_array_func quick_sort_int_array = NULL;

int load_algorithm_qsort_funcs(HMODULE dlllib)
{
	int status;
	if (NULL == dlllib)
	{
		return STATUS_INVALID_PARAMS;
	}

	status = STATUS_ERROR_;
	DO_ONE_LOOP_BEGIN

	quick_sort = (quick_sort_func)GetProcAddress(dlllib, _STR_("quick_sort"));
	BREAK_LOOP_CONDITION(NULL == quick_sort);

	quick_sort_int_array = (quick_sort_int_array_func)GetProcAddress(dlllib, _STR_("quick_sort_int_array"));
	BREAK_LOOP_CONDITION(NULL == quick_sort_int_array);

	status = STATUS_OK;
	DO_ONE_LOOP_END
	return status;
}

void clean_algorithm_qsort_funcs()
{
	quick_sort = NULL;
	quick_sort_int_array = NULL;
}

