//////////////////////////////////////
// type.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef SUNRED_TYPE_H_
#define SUNRED_TYPE_H_

#include "lib_config.h"
#include "export_config.h"
// 常用定义
#define SR_INLINE       __inline
#define SR_CODE_LINE    __inline
#define SR_FORCE_INLINE __forceinline

#define _SR_STR(str) #str
#define SR_STR(str) _SR_STR(str) 

#define _DEFINE_DEFINENAME_1PART(namepart1)                     __##namepart1##_
#define _DEFINE_DEFINENAME_2PART(namepart1,namepart2)           __##namepart1##_##namepart2##_
#define _DEFINE_DEFINENAME_3PART(namepart1,namepart2,namepart3) __##namepart1##_##namepart2##_##namepart3##_

#define DEFINE_DEFINENAME_1PART(namepart1)                     _DEFINE_DEFINENAME_1PART(namepart1)                    
#define DEFINE_DEFINENAME_2PART(namepart1,namepart2)           _DEFINE_DEFINENAME_2PART(namepart1,namepart2)          
#define DEFINE_DEFINENAME_3PART(namepart1,namepart2,namepart3) _DEFINE_DEFINENAME_3PART(namepart1,namepart2,namepart3)

#ifdef __cplusplus
#define SR_EXTERN_C_BEGIN extern "C"{
#define SR_EXTERN_C_END };
#else
#define SR_EXTERN_C_BEGIN 
#define SR_EXTERN_C_END 
#endif//__cplusplus



// 微软 MSVC编译器
#ifdef _MSC_VER
#define ALIGNED_TYPE_ATTRIBUTE(ALIGNED_BYTE_COUNT, DEFINES)     __declspec(align(ALIGNED_BYTE_COUNT)) DEFINES
#define ALIGNED_VARIABLE_ATTRIBUTE(ALIGNED_BYTE_COUNT, DEFINES) __declspec(align(ALIGNED_BYTE_COUNT)) DEFINES
#endif

// GNU GCC编译器
#ifdef __GNUC__
#define ALIGNED_TYPE_ATTRIBUTE(ALIGNED_BYTE_COUNT, DEFINES)     DEFINES  __attribute__ ((aligned (ALIGNED_BYTE_COUNT)))
#define ALIGNED_VARIABLE_ATTRIBUTE(ALIGNED_BYTE_COUNT, DEFINES) DEFINES  __attribute__ ((aligned (ALIGNED_BYTE_COUNT)))
#endif

// ARM ARMCC编译器
#ifdef __ARMCC_VERSION
#define ALIGNED_TYPE_ATTRIBUTE(ALIGNED_BYTE_COUNT, DEFINES)     DEFINES  __attribute__ ((aligned (ALIGNED_BYTE_COUNT)))
#define ALIGNED_VARIABLE_ATTRIBUTE(ALIGNED_BYTE_COUNT, DEFINES) __align(ALIGNED_BYTE_COUNT) DEFINES 
#endif


#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifdef null
#if null != 0
#undef null
#define null (0)
#endif
#else
#define null (0)
#endif
#define INVALID_VALUE	(-1)
#define MAX_UNSIGNED_VALUE (-1)
#define PECKER_PI (3.141592653)
#define PECKER_TWO_PI (6.283185306)
#define DEGREE_TO_RAD(X) ((double_t)(X)/180.0*PECKER_PI)


#ifdef __cplusplus
#define	PFX_C_EXTERN_BEGIN extern "C" {
#else // __cplusplus
#define	PFX_C_EXTERN_BEGIN
#endif // __cplusplus

#ifdef __cplusplus
#define	PFX_C_EXTERN_END  };
#else// __cplusplus
#define	PFX_C_EXTERN_END
#endif // __cplusplus

#define DO_ONE_LOOP_BEGIN do{
#define DO_ONE_LOOP_END ;break;}while(1);
#define BREAK_LOOP(STATUS_PARAM,ERROR_CODE) {STATUS_PARAM = ERROR_CODE; break;}
#define BREAK_LOOP_CONDITION(condition_)if (condition_){break;}
#define BREAK_LOOP_CONDITION_ACT(condition_,ACT)if (condition_){{ACT;}break;}
#define BREAK_LOOP_CONDITION_SETS(condition_,STATUS_PARAM,ERROR_CODE)if (condition_){STATUS_PARAM = ERROR_CODE;break;}

#define RETURN_RESULT(condition,return_status) {if (condition) {return (return_status);} };
#define RETURN_BY_ACT_RESULT(condition,action_,return_status) {if (condition) {{action_;};return (return_status);} };
#define RETURN_INVALID_RESULT(condition,return_status) {if (condition) {return (return_status);} };
#define RETURN_INVALID_BY_ACT_RESULT(condition,action_,return_status) {if (condition) {{action_;};return (return_status);} };
#define SET_POINTER_VALUE(ptr_,val_){if (ptr_){*(ptr_) = (val_);};};

#define PARAM_IN
#define PARAM_OUT
#define PARAM_INOUT

// 类型定义
typedef unsigned char		u8_t;
typedef unsigned short		u16_t;
typedef unsigned int		u32_t;
typedef unsigned long long	u64_t;

typedef signed char			s8_t;
typedef signed short		s16_t;
typedef signed int			s32_t;
typedef signed long long	s64_t;

typedef float				f32_t;
typedef double				f64_t;

typedef signed long			long_t;
typedef unsigned long		ulong_t;

typedef s32_t				sint_t;
typedef u32_t				uint_t;
typedef s16_t				short_t;
typedef u16_t				ushort_t;

typedef unsigned long		enum_t;
typedef unsigned int		enum_int_t;
typedef int					coord_t;
typedef int					nsize__t;
typedef unsigned int		usize__t;
typedef int					index_t;
typedef unsigned int		uindex_t;
typedef unsigned char		byte_t;
typedef unsigned int		bitfield_t;
typedef unsigned int		boolean_t;
typedef char				bool_t;
typedef long                result_t;

#define MAX_16BIT_INT (0x7fff)
#define MIN_16BIT_INT (0x8000)

#define MAX_32BIT_INT (0x7fffffff)
#define MIN_32BIT_INT (0x80000000)

#define MAX_64BIT_INT (9223372036854775807)
#define MIN_64BIT_INT (-9223372036854775808)


typedef struct st_bit8_field
{
#if (ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
	unsigned char m_bit0 : 1;
	unsigned char m_bit1 : 1;
	unsigned char m_bit2 : 1;
	unsigned char m_bit3 : 1;
	unsigned char m_bit4 : 1;
	unsigned char m_bit5 : 1;
	unsigned char m_bit6 : 1;
	unsigned char m_bit7 : 1;
#else  //(ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
	unsigned char m_bit7 : 1;
	unsigned char m_bit6 : 1;
	unsigned char m_bit5 : 1;
	unsigned char m_bit4 : 1;
	unsigned char m_bit3 : 1;
	unsigned char m_bit2 : 1;
	unsigned char m_bit1 : 1;
	unsigned char m_bit0 : 1;
#endif //(ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
}bit8_field_t;

typedef struct st_bit16_field
{
#if (ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
	unsigned short m_bit0  : 1;
	unsigned short m_bit1  : 1;
	unsigned short m_bit2  : 1;
	unsigned short m_bit3  : 1;
	unsigned short m_bit4  : 1;
	unsigned short m_bit5  : 1;
	unsigned short m_bit6  : 1;
	unsigned short m_bit7  : 1;
	unsigned short m_bit8  : 1;
	unsigned short m_bit9  : 1;
	unsigned short m_bit10 : 1;
	unsigned short m_bit11 : 1;
	unsigned short m_bit12 : 1;
	unsigned short m_bit13 : 1;
	unsigned short m_bit14 : 1;
	unsigned short m_bit15 : 1;
#else  //(ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
	unsigned short m_bit15 : 1;
	unsigned short m_bit14 : 1;
	unsigned short m_bit13 : 1;
	unsigned short m_bit12 : 1;
	unsigned short m_bit11 : 1;
	unsigned short m_bit10 : 1;
	unsigned short m_bit9  : 1;
	unsigned short m_bit8  : 1;
	unsigned short m_bit7  : 1;
	unsigned short m_bit6  : 1;
	unsigned short m_bit5  : 1;
	unsigned short m_bit4  : 1;
	unsigned short m_bit3  : 1;
	unsigned short m_bit2  : 1;
	unsigned short m_bit1  : 1;
	unsigned short m_bit0  : 1;
#endif //(ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
}bit16_field_t;

typedef struct st_bit32_field
{
#if (ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
	unsigned int m_bit0  : 1;
	unsigned int m_bit1  : 1;
	unsigned int m_bit2  : 1;
	unsigned int m_bit3  : 1;
	unsigned int m_bit4  : 1;
	unsigned int m_bit5  : 1;
	unsigned int m_bit6  : 1;
	unsigned int m_bit7  : 1;
	unsigned int m_bit8  : 1;
	unsigned int m_bit9  : 1;
	unsigned int m_bit10 : 1;
	unsigned int m_bit11 : 1;
	unsigned int m_bit12 : 1;
	unsigned int m_bit13 : 1;
	unsigned int m_bit14 : 1;
	unsigned int m_bit15 : 1;
	unsigned int m_bit16 : 1;
	unsigned int m_bit17 : 1;
	unsigned int m_bit18 : 1;
	unsigned int m_bit19 : 1;
	unsigned int m_bit20 : 1;
	unsigned int m_bit21 : 1;
	unsigned int m_bit22 : 1;
	unsigned int m_bit23 : 1;
	unsigned int m_bit24 : 1;
	unsigned int m_bit25 : 1;
	unsigned int m_bit26 : 1;
	unsigned int m_bit27 : 1;
	unsigned int m_bit28 : 1;
	unsigned int m_bit29 : 1;
	unsigned int m_bit30 : 1;
	unsigned int m_bit31 : 1;
#else  //(ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
	unsigned int m_bit31 : 1;
	unsigned int m_bit30 : 1;
	unsigned int m_bit29 : 1;
	unsigned int m_bit28 : 1;
	unsigned int m_bit27 : 1;
	unsigned int m_bit26 : 1;
	unsigned int m_bit25 : 1;
	unsigned int m_bit24 : 1;
	unsigned int m_bit23 : 1;
	unsigned int m_bit22 : 1;
	unsigned int m_bit21 : 1;
	unsigned int m_bit20 : 1;
	unsigned int m_bit19 : 1;
	unsigned int m_bit18 : 1;
	unsigned int m_bit17 : 1;
	unsigned int m_bit16 : 1;
	unsigned int m_bit15 : 1;
	unsigned int m_bit14 : 1;
	unsigned int m_bit13 : 1;
	unsigned int m_bit12 : 1;
	unsigned int m_bit11 : 1;
	unsigned int m_bit10 : 1;
	unsigned int m_bit9  : 1;
	unsigned int m_bit8  : 1;
	unsigned int m_bit7  : 1;
	unsigned int m_bit6  : 1;
	unsigned int m_bit5  : 1;
	unsigned int m_bit4  : 1;
	unsigned int m_bit3  : 1;
	unsigned int m_bit2  : 1;
	unsigned int m_bit1  : 1;
	unsigned int m_bit0  : 1;
#endif //(ENDIAN_BITFIELD == __BIG_ENDIAN_BITFIELD__)
}bit32_field_t;

typedef union _8bit_DataType
{
	s8_t         m_s8;
	u8_t         m_u8;
	bit8_field_t m_bit8;
}bit8_t;

typedef union _16bit_DataType
{
	s16_t         m_s16;
	u16_t         m_u16;
	s8_t          m_s8[2];
	u8_t          m_u8[2];
	bit8_t		  m_b8[2];
	bit8_field_t  m_bit8[2];
	bit16_field_t m_bit16;
}bit16_t;

typedef union _32bit_DataType
{
	s32_t         m_s32;
	u32_t         m_u32;
	f32_t         m_f32;
	s16_t         m_s16[2];
	u16_t         m_u16[2];
	s8_t          m_s8[4];
	u8_t          m_u8[4];
	bit8_t		  m_b8[4];
	bit16_t       m_b16[2];
	bit8_field_t  m_bit8[4];
	bit16_field_t m_bit16[2];
	bit32_field_t m_bit32;
}bit32_t;

typedef union _64bit_DataType
{
	s64_t         m_s64;
	u64_t         m_u64;
	f64_t         m_f64;
	f32_t         m_f32[2];
	s32_t         m_s32[2];
	u32_t         m_u32[2];
	s16_t         m_s16[4];
	u16_t         m_u16[4];
	s8_t          m_s8[8];
	u8_t          m_u8[8];
	bit8_t		  m_b8[8];
	bit16_t       m_b16[4];
	bit32_t       m_b32[2];
	bit8_field_t  m_bit8[8];
	bit16_field_t m_bit16[4];
	bit32_field_t m_bit32[2];

}bit64_t;

typedef union _128bit_DataType
{
	bit64_t       m_bit64[2];

	s64_t         m_s64[2];
	u64_t         m_u64[2];
	f64_t         m_f64[2];
	f32_t         m_f32[4];
	s32_t         m_s32[4];
	u32_t         m_u32[4];
	s16_t         m_s16[8];
	u16_t         m_u16[8];
	s8_t          m_s8[16];
	u8_t          m_u8[16];
	bit8_t		  m_b8[16];
	bit16_t       m_b16[8];
	bit32_t       m_b32[4];
	bit8_field_t  m_bit8[16];
	bit16_field_t m_bit16[8];
	bit32_field_t m_bit32[4];
	 
}bit128_t;

typedef union _256bit_DataType
{
	bit128_t      m_bit128[2];
	bit32_t       m_bit32[8];
	bit64_t       m_bit64[4];
	
}bit256_t;

typedef union _512bit_DataType
{
	bit256_t      m_bit256[2];
	bit32_t       m_bit32[16];
	bit64_t       m_bit64[8];
	bit128_t      m_bit128[4];
	
}bit512_t;


typedef struct st_api_version
{
	u32_t version_code[4];
}api_version_t;

typedef struct st_ins_ver
{
	u16_t   m_sub_version[4];
}ins_ver_t;

typedef union un_instance_version
{
	ins_ver_t	m_sub_ver;
	u64_t		m_version;
}instance_version_t;

typedef struct st_u8_buffer
{
	uint_t m_buffer_size;
	u8_t*  m_buffer;
}u8_buffer_t;

typedef struct st_void_buffer
{
	uint_t m_buffer_size;
	u8_t*  m_buffer;
}void_buffer_t;

typedef struct st_const_u8_buffer
{
	uint_t       m_buffer_size;
	const u8_t*  m_buffer;
}const_u8_buffer_t;

typedef union un_buffer
{
	u8_buffer_t        u8;
	const_u8_buffer_t  const_u8;
	void_buffer_t      __void;
}buffer_t;

typedef struct st_buffer_offsetinfo
{
	uindex_t m_begin;
	usize__t m_size;
}buffer_offsetinfo_t;

typedef struct st_object
{
	uint_t   m_mask;
	buffer_t m_data;
}object_t;

// 状态
enum OS_STATUS_CODE
{
	STATUS_ERROR_CODE = -65535,

	STATUS_FULL,
	STATUS_EMPTY,

	STATUS_OVERRANGE,

	STATUS_DENIED,
	STATUS_NOT_EXISTS,

	STATUS_DIFF_TYPE,

	STATUS_REFERENCED,

	STATUS_UNIQUE,
	STATUS_UNINIT,

	STATUS_TIME_OUT,
	STATUS_NULLITEM,

	STATUS_OPENED,
	STATUS_CLOSED,

	STATUS_MEM_ERR,
	STATUS_MEM_LOW,
	STATUS_DATA_ERROR,
	STATUS_STREAM_ERROR,
	STATUS_BUFFER_ERROR,
	STATUS_OUT_OF_MEMORY,
	STATUS_STACKOVERFLOW,

	STATUS_WAITRESULT,
	STATUS_FIN,

	STATUS_VERSION_ERROR,

	STATUS_INVALID_PARAMS,
	STATUS_INVALID_VERSION,
	STATUS_INVALID_LEVEL,
	STATUS_INVALID_SIZE,
	STATUS_INVALID_OPERATION,
	STATUS_INVALID_VALUE,
	STATUS_INVALID_ENUM,
	STATUS_INVALID_FORMAT,

	STATUS_MISSING,
	STATUS_INCOMPLETE,
	STATUS_NOT_SUPPORTED,

	STATUS_NOT_ENOUGH_NODE,

	STATUS_FAIL = -2,
	STATUS_ERROR_ = -1,

	STATUS_OK = 0,
	STATUS_SUCCESS,

	STATUS_OK_COUNT,
};


//计算
#define FIRST_BITINDEX_0(X,Y) (Y)
#define FIRST_BITINDEX_1(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_0((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_2(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_1((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_3(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_2((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_4(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_3((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_5(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_4((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_6(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_5((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_7(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_6((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_8(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_7((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_9(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_8((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_10(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_9((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_11(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_10((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_12(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_11((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_13(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_12((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_14(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_13((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_15(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_14((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_16(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_15((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_17(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_16((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_18(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_17((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_19(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_18((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_20(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_19((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_21(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_20((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_22(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_21((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_23(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_22((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_24(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_23((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_25(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_24((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_26(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_25((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_27(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_26((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_28(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_27((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_29(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_28((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_30(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_29((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_31(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_30((X)>>1,((Y)+1))):(Y))


#define MIP_BUFFER_SIZE_00(X,Y,F) (Y)
#define MIP_BUFFER_SIZE_01(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_00( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_02(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_01( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_03(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_02( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_04(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_03( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_05(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_04( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_06(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_05( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_07(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_06( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_08(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_07( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_09(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_08( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_10(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_09( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_11(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_10( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_12(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_11( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_13(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_12( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_14(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_13( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_15(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_14( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_16(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_15( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_17(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_16( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_18(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_17( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_19(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_18( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_20(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_19( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_21(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_20( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_22(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_21( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_23(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_22( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_24(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_23( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_26(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_24( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_27(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_26( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_28(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_27( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_29(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_28( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_30(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_29( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_31(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_30( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))

#endif	 //SUNRED_TYPE_H_
