//////////////////////////////////////
// lib_config.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef LIB_SUNRED_CONFIG_H_
#define LIB_SUNRED_CONFIG_H_

//ENDIAN_BIT 
#define __LITTLE_ENDIAN_BITFIELD__ (0)
#define __BIG_ENDIAN_BITFIELD__    (1)

// SMID OPTION
#define NO_SMID                 (0)
#define X86_SSE_OPTION          (1)
#define ARM_NEON_OPTION         (2)

// OS_PLATFORM
#define FOR_SUNRED_OS (0)
#define FOR_WINDOW_OS (1)
#define FOR_LINUX_OS  (2) 


#include "build_config.h"

#if (defined (ENDIAN_BITFIELD) && (__BIG_ENDIAN_BITFIELD__ == ENDIAN_BITFIELD) )
#define __BIG_ENDIAN_BITFIELD
#else
#define __LITTLE_ENDIAN_BITFIELD
#endif

#if (!(defined (COMPILER_TYPE)))
#include "defualt_compiler32bit_type.h"
#else
// to add
#endif



#endif	 //LIB_SUNRED_CONFIG_H_
