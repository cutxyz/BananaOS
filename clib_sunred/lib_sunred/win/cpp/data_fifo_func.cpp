//////////////////////////////////////
// dlllib_sunred.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "clib_sunred.h"
#include < Windows.h >
#define _STR_(X) X

int load_data_fifo_funcs(HMODULE dlllib)
{
	int status;
	if (NULL == dlllib)
	{
		return STATUS_INVALID_PARAMS;
	}

	status = STATUS_ERROR_;
	DO_ONE_LOOP_BEGIN

	status = STATUS_OK;
	DO_ONE_LOOP_END
	return status;
}

void clean_data_fifo_funcs()
{
	;
}

