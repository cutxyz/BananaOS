//////////////////////////////////////
// sr_mem.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef CLIB_SUNRED_MEM_H_
#define CLIB_SUNRED_MEM_H_

#include "../type.h"

typedef void* (*sr_memcpy_func)(void* PARAM_OUT dest,
	const void* PARAM_IN src,
	usize__t count);

typedef void* (*sr_memset_func)(void* PARAM_OUT dest,
	u32_t    val,
	usize__t count);

#ifdef STATIC_LIB_OR_SHADOW_DLL_IMPORT

SR_EXTERN_C_BEGIN

void* sr_memcpy_c(void* PARAM_OUT dest,
const void* PARAM_IN src,
usize__t count);

void* sr_memset_c(void* PARAM_OUT dest,
	u32_t    val,
	usize__t count);

SR_EXTERN_C_END

#else

extern sr_memcpy_func sr_memcpy_c;
extern sr_memset_func sr_memset_c;

#endif //STATIC_LIB_OR_SHADOW_DLL_IMPORT


#include "../../util/memcopy.h"

#endif	 //CLIB_SUNRED_MEM_H_
