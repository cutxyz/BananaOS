//////////////////////////////////////
// dlllib_sunred.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "clib_sunred.h"
#include < Windows.h >
#define _STR_(X) X

sr_memcpy_func sr_memcpy_c = NULL;
sr_memset_func sr_memset_c = NULL;

int load_util_men_funcs(HMODULE dlllib)
{
	int status;
	if (NULL == dlllib)
	{
		return STATUS_INVALID_PARAMS;
	}

	status = STATUS_ERROR_;
	DO_ONE_LOOP_BEGIN
		
	sr_memcpy_c = (sr_memcpy_func)GetProcAddress(dlllib, _STR_("sr_memcpy_c"));
	BREAK_LOOP_CONDITION(NULL == sr_memcpy_c);

	sr_memset_c = (sr_memset_func)GetProcAddress(dlllib, _STR_("sr_memset_c"));
	BREAK_LOOP_CONDITION(NULL == sr_memset_c);

	status = STATUS_OK;
	DO_ONE_LOOP_END
	return status;
}

void clean_util_men_funcs()
{
	sr_memcpy_c = NULL;
	sr_memset_c = NULL;


}