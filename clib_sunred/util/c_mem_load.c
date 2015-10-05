//////////////////////////////////////
// c_math_load.c
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "../include/type.h"
#undef 	MEM_SMID_OPTION
#define MEM_SMID_OPTION NO_SMID
#include "../include/util/sr_mem.h"
//#include "memcopy.h"

void* sr_memcpy_c(void* PARAM_OUT dest,
	const void* PARAM_IN src,
	usize__t count)
{
	return sr_memcpy_inline(dest, src, count);
}

void* sr_memset_c(void* PARAM_OUT dest,
	u32_t    val,
	usize__t count)
{
	return sr_memset_inline(dest, val, count);
}

//#include "../clib_sunred_interal.h"
//void __init_sunred_lib_mem(clib_sunred_funcions_t* PARAM_INOUT lib_ptr)
//{
//	lib_ptr->sr_memcpy_c = sr_memcpy_c;
//	lib_ptr->sr_memset_c  = sr_memset_c;
//}
