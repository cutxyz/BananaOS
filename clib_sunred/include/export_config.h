//////////////////////////////////////
// export_config.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef SUNRED_EXPORT_CONFIG_H_
#define SUNRED_EXPORT_CONFIG_H_

// 微软 MSVC编译器
#ifdef _MSC_VER
#if defined(SUNLIB_DLL_EXPORT)
#define SUNRED_API  _declspec(dllexport)
#else
#define SUNRED_API  _declspec(dllimport)
#endif

#endif

// GNU GCC编译器
#ifdef __GNUC__
#define SUNRED_API
#endif

// ARM ARMCC编译器
#ifdef __ARMCC_VERSION
#define SUNRED_API
#endif


#endif	 //SUNRED_EXPORT_CONFIG_H_
