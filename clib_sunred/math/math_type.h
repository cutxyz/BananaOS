//////////////////////////////////////
// math_type.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef MATH_TYPE_H_
#define MATH_TYPE_H_

#include "type.h"

#define VEC_IDX_X (0)
#define VEC_IDX_Y (1)
#define VEC_IDX_Z (2)
#define VEC_IDX_W (3)


#ifdef _MSC_VER
typedef struct __declspec(intrin_type) __declspec(align(16)) st_vector4i
{
	s32_t vec[4];
}vector4i_t;
typedef struct __declspec(intrin_type) __declspec(align(16)) st_vector4f
{
	f32_t vec[4];
}vector4f_t;

typedef union __declspec(intrin_type) __declspec(align(16)) un_vector4
{
	vector4i_t vec4i;
	vector4f_t vec4f;
	bit128_t   __128bit;
}vector4_t;
#endif

// GNU GCC编译器
#ifdef __GNUC__
typedef struct  st_vector4i
{
	s32_t vec[4];
}vector4i_t __attribute__ ((__vector_size__(16), __may_alias__)) __attribute__ (aligned (16));
typedef struct st_vector4i
{
	f32_t vec[4];
}vector4f_t __attribute__ ((__vector_size__(16), __may_alias__)) __attribute__ (aligned (16));

typedef union un_vector4
{
	vector4i_t vec4i;
	vector4f_t vec4f;
	bit128_t   __128bit;
}vector4_t __attribute__ ((__vector_size__(16), __may_alias__)) __attribute__ (aligned (16));
#endif

// ARM ARMCC编译器
#ifdef __ARMCC_VERSION
//typedef struct  st_vector4i
//{
//	s32_t vec[4];
//}vector4i_t __attribute__((__vector_size__(16), __may_alias__)) __attribute__(aligned(16));
//typedef struct st_vector4i
//{
//	f32_t vec[4];
//}vector4f_t __attribute__((__vector_size__(16), __may_alias__)) __attribute__(aligned(16));
//
//typedef union un_vector4
//{
//	vector4i_t vec4i;
//	vector4f_t vec4f;
//  bit128_t   __128bit;
//}vector4_t __attribute__((__vector_size__(16), __may_alias__)) __attribute__(aligned(16));
#endif


//neon_vector_type

#endif//MATH_TYPE_H_