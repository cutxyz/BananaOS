//////////////////////////////////////
// dlllib_sunred.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "clib_sunred.h"
#include < Windows.h >
static HMODULE gdll_sunred_lib = NULL;

// data
// bst
extern int load_data_bst_funcs(HMODULE dlllib);
extern void clean_data_bst_funcs();
// fifo
extern int load_data_fifo_funcs(HMODULE dlllib);
extern void clean_data_fifo_funcs();
// algorithm
extern int load_algorithm_qsort_funcs(HMODULE dlllib);
extern void clean_algorithm_qsort_funcs();
//util
extern int load_util_men_funcs(HMODULE dlllib);
extern void clean_util_men_funcs();

int load_sunred_clib(const char* strPath, int param)
{
	int status;
	if (NULL == gdll_sunred_lib)
	{
		gdll_sunred_lib = LoadLibraryA(strPath);
	}
	if (NULL == gdll_sunred_lib)
	{
		return STATUS_FAIL;
	}
	status = STATUS_ERROR_;
	DO_ONE_LOOP_BEGIN
	//data
	status = load_data_bst_funcs(gdll_sunred_lib);
	BREAK_LOOP_CONDITION(STATUS_OK != status);
	
	status = load_data_fifo_funcs(gdll_sunred_lib);
	BREAK_LOOP_CONDITION(STATUS_OK != status);

	//algorithm
	status = load_algorithm_qsort_funcs(gdll_sunred_lib);
	BREAK_LOOP_CONDITION(STATUS_OK != status);

	//util
	status = load_util_men_funcs(gdll_sunred_lib);
	BREAK_LOOP_CONDITION(STATUS_OK != status);

	DO_ONE_LOOP_END

	if (STATUS_OK != status)
	{
		release_sunred_clib();
	}
	return status;
	
}
int release_sunred_clib()
{
	if (gdll_sunred_lib)
	{
		BOOL res = FreeLibrary(gdll_sunred_lib);
		if (!res)
		{
			return STATUS_FAIL;
		}
	}
	clean_data_bst_funcs();
	clean_data_fifo_funcs();
	clean_algorithm_qsort_funcs();
	clean_util_men_funcs();
	return STATUS_OK;
}


