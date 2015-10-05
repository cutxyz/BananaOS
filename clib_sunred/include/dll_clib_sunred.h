//////////////////////////////////////
// dlllib_sunred.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef DLLLIB_SUNRED_H_
#define DLLLIB_SUNRED_H_

#include "type.h"

#ifndef STATIC_LIB_OR_SHADOW_DLL_IMPORT
SR_EXTERN_C_BEGIN
int load_sunred_clib(const char* strPath, int param);
int release_sunred_clib();
SR_EXTERN_C_END
#endif//STATIC_LIB_OR_SHADOW_DLL_IMPORT

#endif	 //DLLLIB_SUNRED_H_
