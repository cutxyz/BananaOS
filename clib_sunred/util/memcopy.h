//////////////////////////////////////
// memcopy.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef SR_MEMCOPY_H_
#define SR_MEMCOPY_H_

#include "c_mem_load.h"


#define MAX_LOAD_ALIGNED_MASK ALIGNED512BIT_MASK
#define MAX_LOAD_ALIGNED8BIT   (0x3F)
#define MAX_LOAD_ALIGNED16BIT  (0x3E)
#define MAX_LOAD_ALIGNED32BIT  (0x3C)
#define MAX_LOAD_ALIGNED64BIT  (0x38)
#define MAX_LOAD_ALIGNED128BIT (0x30)
#define MAX_LOAD_ALIGNED256BIT (0x20)
#define MAX_LOAD_ALIGNED512BIT (0)

#if (!defined(MEM_SMID_OPTION) || (MEM_SMID_OPTION == NO_SMID))

#define __sr_loadu8_memory   __sr_loadu8_memory_c  
#define __sr_loadu16_memory  __sr_loadu16_memory_c 
#define __sr_loadu32_memory  __sr_loadu32_memory_c 
#define __sr_loadu64_memory  __sr_loadu64_memory_c 
#define __sr_loadu128_memory __sr_loadu128_memory_c
#define __sr_loadu256_memory __sr_loadu256_memory_c
#define __sr_loadu512_memory __sr_loadu512_memory_c

#define __sr_setu8_memory   __sr_setu8_memory_c  
#define __sr_setu16_memory  __sr_setu16_memory_c 
#define __sr_setu32_memory  __sr_setu32_memory_c 
#define __sr_setu64_memory  __sr_setu64_memory_c 
#define __sr_setu128_memory __sr_setu128_memory_c
#define __sr_setu256_memory __sr_setu256_memory_c
#define __sr_setu512_memory __sr_setu512_memory_c

//void* sr_memcpy_c(void* PARAM_OUT dest,
//	const void* PARAM_IN src,
//	usize__t count);
//
//void* sr_memset_c(void* PARAM_OUT dest,
//	u32_t    val,
//	usize__t count);

#ifndef sr_memset_c_
#define sr_memset_c_  sr_memset_c
#endif//sr_memset_c_
#ifndef sr_memcpy_c_
#define sr_memcpy_c_  sr_memcpy_c
#endif//sr_memcpy_c_

#ifndef sr_memcpy
#define sr_memcpy sr_memcpy_c_
#endif//sr_memcpy

#ifndef sr_memset
#define sr_memset sr_memset_c_
#endif//sr_memset

#endif //(!defined(MEM_SMID_OPTION) || (MEM_SMID_OPTION == NO_SMID))

#if (defined(MEM_SMID_OPTION) && (MEM_SMID_OPTION == X86_SSE_OPTION))

#endif //(defined(MEM_SMID_OPTION) && (MEM_SMID_OPTION == X86_SSE_OPTION))

#if (defined(MEM_SMID_OPTION) && (MEM_SMID_OPTION == ARM_NEON_OPTION))

#endif //(defined(MEM_SMID_OPTION) && (MEM_SMID_OPTION == ARM_NEON_OPTION))


static SR_FORCE_INLINE u8_t* __sr_memu8cpy(u8_t* PARAM_OUT dest,
	const u8_t* PARAM_IN src,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_loadu8_memory(dest + count, src + count);
	}
	return dest;
}

static SR_FORCE_INLINE u16_t* __sr_memu16cpy(u16_t* PARAM_OUT dest,
	const u16_t* PARAM_IN src,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_loadu16_memory(dest + count, src + count);
	}
	return dest;
}

static SR_FORCE_INLINE u32_t* __sr_memu32cpy(u32_t* PARAM_OUT dest,
	const u32_t* PARAM_IN src,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_loadu32_memory(dest + count, src + count);
	}
	return dest;
}

static SR_FORCE_INLINE u64_t* __sr_memu64cpy(u64_t* PARAM_OUT dest,
	const u64_t* PARAM_IN src,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_loadu64_memory(dest + count, src + count);
	}
	return dest;
}

static SR_FORCE_INLINE bit128_t* __sr_memu128cpy(bit128_t* PARAM_OUT dest,
	const bit128_t* PARAM_IN src,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_loadu128_memory(dest + count, src + count);
	}
	return dest;
}

static SR_FORCE_INLINE bit256_t* __sr_memu256cpy(bit256_t* PARAM_OUT dest,
	const bit256_t* PARAM_IN src,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_loadu256_memory(dest + count, src + count);
	}
	return dest;
}

static SR_FORCE_INLINE bit512_t* __sr_memu512cpy(bit512_t* PARAM_OUT dest,
	const bit512_t* PARAM_IN src,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_loadu512_memory(dest + count, src + count);
	}
	return dest;
}

//////////////////////////////////////////////////////////////////////////
static SR_FORCE_INLINE u8_t* __sr_memu8set(u8_t* PARAM_OUT dest,
	u8_t val,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_setu8_memory(dest + count, val);
	}
	return dest;
}

static SR_FORCE_INLINE u16_t* __sr_memu16set(u16_t* PARAM_OUT dest,
	u16_t val,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_setu16_memory(dest + count, val);
	}
	return dest;
}

static SR_FORCE_INLINE u32_t* __sr_memu32set(u32_t* PARAM_OUT dest,
	u32_t val,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_setu32_memory(dest + count, val);
	}
	return dest;
}

static SR_FORCE_INLINE u64_t* __sr_memu64set(u64_t* PARAM_OUT dest,
	u32_t val,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_setu64_memory(dest + count, val);
	}
	return dest;
}

static SR_FORCE_INLINE bit128_t* __sr_memu128set(bit128_t* PARAM_OUT dest,
	u32_t val,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_setu128_memory(dest + count, val);
	}
	return dest;
}

static SR_FORCE_INLINE bit256_t* __sr_memu256set(bit256_t* PARAM_OUT dest,
	u32_t val,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_setu256_memory(dest + count, val);
	}
	return dest;
}

static SR_FORCE_INLINE bit512_t* __sr_memu512set(bit512_t* PARAM_OUT dest,
	u32_t val,
	usize__t count)
{
	while (count)
	{
		--count;
		__sr_setu512_memory(dest + count, val);
	}
	return dest;
	}

#define SR_COPY_ONE_512BIT   \
	__sr_loadu512_memory((bit512_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	(const bit512_t*)ADDRESS_2_VOID_PTR(src_addr));					\
	dest_addr += 64;											    \
	src_addr += 64;													\
	count -= 64;													\

#define SR_COPY_ONE_256BIT   \
	__sr_loadu256_memory((bit256_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	(const bit256_t*)ADDRESS_2_VOID_PTR(src_addr));				   \
	dest_addr += 32;											   \
	src_addr += 32;												   \
	count -= 32;												   \

#define SR_COPY_ONE_128BIT   \
	__sr_loadu128_memory((bit128_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	(const bit128_t*)ADDRESS_2_VOID_PTR(src_addr));				   \
	dest_addr += 16;											   \
	src_addr += 16;											   \
	count -= 16;											   \

#define SR_COPY_ONE_64BIT   \
	__sr_loadu64_memory((u64_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	(const u64_t*)ADDRESS_2_VOID_PTR(src_addr));				  \
	dest_addr += 8;												  \
	src_addr += 8;												  \
	count -= 8;													  \

#define SR_COPY_ONE_32BIT   \
	__sr_loadu32_memory((u32_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	(const u32_t*)ADDRESS_2_VOID_PTR(src_addr));				  \
	dest_addr += 4;												  \
	src_addr += 4;												  \
	count -= 4;												  \

#define  SR_COPY_ONE_16BIT   \
	__sr_loadu16_memory((u16_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	(const u16_t*)ADDRESS_2_VOID_PTR(src_addr));					 \
	dest_addr += 2;												 \
	src_addr += 2;												 \
	count -= 2;													 \

#define SR_COPY_ONE_8BIT   \
	__sr_loadu8_memory((u8_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	(const u8_t*)ADDRESS_2_VOID_PTR(src_addr));					 \
	dest_addr++;													 \
	src_addr++;													 \
	--count;														 \

#define SR_TMP_COPYMEM_BLOCK(break_triger,COPY_FUNC)\
	while (count >= break_triger)			   \
	{							   \
		COPY_FUNC; \
	}	\

#if defined(SR_MEM_DEBUG_INFO)
#define SR_MEM_DEBUG_INFO_OUT(FORMAT,...) printf(FORMAT, __VA_ARGS__)
#else
#define SR_MEM_DEBUG_INFO_OUT(FORMAT,...)
#endif

#define SR_ALIGNED_512BITCOPY \
	DO_ONE_LOOP_BEGIN \
	SR_TMP_COPYMEM_BLOCK(64, SR_COPY_ONE_512BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(32, SR_COPY_ONE_256BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(16, SR_COPY_ONE_128BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(8, SR_COPY_ONE_64BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(4, SR_COPY_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(2, SR_COPY_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(1, SR_COPY_ONE_8BIT);\
	DO_ONE_LOOP_END


#define  SR_ALIGNED_256BITCOPY(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_256BITCOPY"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("%d\n",count); \
	  SR_COPY_ONE_256BIT; \
	  same_aligned_mask = (dest_addr | src_addr);\
      if (0 ==(same_aligned_mask & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITCOPY;\
		 break;\
	  }													 \
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(32, SR_COPY_ONE_256BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(16, SR_COPY_ONE_128BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(8, SR_COPY_ONE_64BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(4, SR_COPY_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(2, SR_COPY_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(1, SR_COPY_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_128BITCOPY(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_128BITCOPY"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("copy count = %d\n", count); \
	  SR_COPY_ONE_128BIT; \
	  same_aligned_mask = (dest_addr | src_addr);\
      if (0 ==(same_aligned_mask & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITCOPY;\
		 break;\
	  }													 \
	  else if (0 == (same_aligned_mask & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITCOPY(MINCOUNT);\
		 break;\
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(16, SR_COPY_ONE_128BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(8, SR_COPY_ONE_64BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(4, SR_COPY_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(2, SR_COPY_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(1, SR_COPY_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_64BITCOPY(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_64BITCOPY"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("copy count = %d\n", count); \
	  SR_COPY_ONE_64BIT; \
	  same_aligned_mask = (dest_addr | src_addr);\
      if (0 ==(same_aligned_mask & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITCOPY;\
		 break;\
	  }													 \
	  else if (0 == (same_aligned_mask & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITCOPY(MINCOUNT);\
		 break;\
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED128BIT_MASK))\
	  {\
	     SR_ALIGNED_128BITCOPY(MINCOUNT); \
	     break; \
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(8, SR_COPY_ONE_64BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(4, SR_COPY_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(2, SR_COPY_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(1, SR_COPY_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_32BITCOPY(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_32BITCOPY"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("copy count = %d\n", count); \
	  SR_COPY_ONE_32BIT; \
	  same_aligned_mask = (dest_addr | src_addr);\
      if (0 ==(same_aligned_mask & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITCOPY;\
		 break;\
	  }													 \
	  else if (0 == (same_aligned_mask & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITCOPY(MINCOUNT);\
		 break;\
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED128BIT_MASK))\
	  {\
	     SR_ALIGNED_128BITCOPY(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED64BIT_MASK))\
	  {\
	     SR_ALIGNED_64BITCOPY(MINCOUNT); \
	     break; \
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(4, SR_COPY_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(2, SR_COPY_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(1, SR_COPY_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_16BITCOPY(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_16BITCOPY"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("copy count = %d\n", count); \
	  SR_COPY_ONE_16BIT; \
	  same_aligned_mask = (dest_addr | src_addr);\
      if (0 ==(same_aligned_mask & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITCOPY;\
		 break;\
	  }													 \
	  else if (0 == (same_aligned_mask & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITCOPY(MINCOUNT);\
		 break;\
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED128BIT_MASK))\
	  {\
	     SR_ALIGNED_128BITCOPY(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED64BIT_MASK))\
	  {\
	     SR_ALIGNED_64BITCOPY(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED32BIT_MASK))\
	  {\
	     SR_ALIGNED_32BITCOPY(MINCOUNT); \
	     break; \
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(2, SR_COPY_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(1, SR_COPY_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_8BITCOPY(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_8BITCOPY"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("copy count = %d\n", count); \
	  SR_COPY_ONE_8BIT; \
	  same_aligned_mask = (dest_addr | src_addr);\
      if (0 ==(same_aligned_mask & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITCOPY;\
		 break;\
	  }													 \
	  else if (0 == (same_aligned_mask & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITCOPY(MINCOUNT);\
		 break;\
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED128BIT_MASK))\
	  {\
	     SR_ALIGNED_128BITCOPY(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED64BIT_MASK))\
	  {\
	     SR_ALIGNED_64BITCOPY(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED32BIT_MASK))\
	  {\
	     SR_ALIGNED_32BITCOPY(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (same_aligned_mask & ALIGNED16BIT_MASK))\
	  {\
	     SR_ALIGNED_16BITCOPY(MINCOUNT); \
	     break; \
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_COPYMEM_BLOCK(1, SR_COPY_ONE_8BIT); \
	DO_ONE_LOOP_END


static SR_INLINE void* sr_memcpy_inline(void* PARAM_OUT dest, 
	                                   const void* PARAM_IN src, 
									   usize__t count)
{
	reg_t dest_addr;
	reg_t src_addr;
	reg_t same_aligned_mask;

	if (0 >= count || dest == src || null == dest || null == src)
	{
		return dest;
	}

	dest_addr = POINTER_2_ADDRESS(dest);
	src_addr  = POINTER_2_ADDRESS(src);

	same_aligned_mask = (dest_addr | src_addr);


	if (0 == (same_aligned_mask & ALIGNED512BIT_MASK))
	{
		SR_ALIGNED_512BITCOPY;
	}
	else 
	if (0 == (same_aligned_mask & ALIGNED256BIT_MASK))
	{
		SR_ALIGNED_256BITCOPY(96); 
	}
	else 
	if (0 == (same_aligned_mask & ALIGNED128BIT_MASK))
	{
		SR_ALIGNED_128BITCOPY(48);
	}
	else
	if (0 == (same_aligned_mask & ALIGNED64BIT_MASK))
	{
		SR_ALIGNED_64BITCOPY(32);
	}
	else
	if (0 == (same_aligned_mask & ALIGNED32BIT_MASK))
	{
		SR_ALIGNED_32BITCOPY(16);
	}
	else
	if (0 == (same_aligned_mask & ALIGNED16BIT_MASK))
	{
		SR_ALIGNED_16BITCOPY(8);
	}
	else
	{
		SR_ALIGNED_8BITCOPY(4);
	}

	return dest;
}



static SR_INLINE void* sr_memncpy(void* PARAM_OUT dest,
	usize__t destbuf_size,
	const void* PARAM_IN src,
	usize__t count)
{
	usize__t copysize;
	copysize = (destbuf_size > count) ? count : destbuf_size;
	return sr_memcpy(dest, src, copysize);
}

typedef struct st_same_memory_block_info
{
	reg_t	    m_sameblock_addr;
	usize__t    m_samesize;	
}same_memory_block_info_t;

static SR_INLINE const same_memory_block_info_t* __get_same_memoryblock(
	const void* PARAM_IN block1_ptr, usize__t b1_size,
	const void* PARAM_IN block2_ptr, usize__t b2_size,
	same_memory_block_info_t* PARAM_OUT info_ptr)
{
	reg_t block1_addr = POINTER_2_ADDRESS(block1_ptr);
	reg_t block2_addr = POINTER_2_ADDRESS(block2_ptr);

	if (block1_addr < block2_addr)
	{
		sreg_t tmp_size = block1_addr + b1_size - block2_addr;
		if (tmp_size > 0)
		{
			info_ptr->m_sameblock_addr = block2_addr;
			info_ptr->m_samesize       = ((reg_t)tmp_size > b2_size) ? b2_size : tmp_size;
		}
		else
		{
			info_ptr->m_sameblock_addr = null;
			info_ptr->m_samesize       = 0;
		}
	}
	else
	{
		sreg_t tmp_size = block2_addr + b2_size - block1_addr;
		if (tmp_size > 0)
		{
			info_ptr->m_sameblock_addr = block1_addr;
			info_ptr->m_samesize = ((reg_t)tmp_size > b1_size) ? b1_size : tmp_size;
		}
		else
		{
			info_ptr->m_sameblock_addr = null;
			info_ptr->m_samesize = 0;
		}
	}
	
	return info_ptr;

}

static SR_INLINE void* sr_memory_move_s(void* PARAM_IN dest_ptr, usize__t dest_size,
	const void* PARAM_IN src_ptr, usize__t src_size)
{
	same_memory_block_info_t same_info;

	DO_ONE_LOOP_BEGIN

	if (0 == dest_size || dest_ptr == src_ptr || 
		null == dest_ptr || null == src_ptr)
	{
		break;
	}
	
	__get_same_memoryblock(dest_ptr, dest_size, src_ptr, src_size, &same_info);

	if (0 == same_info.m_samesize)
	{
		 sr_memncpy(dest_ptr, dest_size, src_ptr, src_size);
		 break;
	}
	else
	{
		reg_t dest_addr = POINTER_2_ADDRESS(dest_ptr);
		reg_t src_addr  = POINTER_2_ADDRESS(src_ptr);

		if (src_addr >= same_info.m_sameblock_addr)
		{
			sr_memncpy(dest_ptr, dest_size, src_ptr, src_size);
			break;
		}
		else
		{
			usize__t dest_offset;
			dest_offset = src_size - same_info.m_samesize;
			if (dest_offset >= dest_size)
			{
				sr_memncpy(dest_ptr, dest_size, src_ptr, src_size);
				break;
			}
			else
			{
			    sr_memcpy(ADDRESS_2_VOID_PTR(dest_addr + dest_offset),
						  ADDRESS_2_VOID_PTR(same_info.m_sameblock_addr),
						  same_info.m_samesize);
				sr_memcpy(dest_ptr, src_ptr, dest_offset);
				break;

			}
		}

	}
	DO_ONE_LOOP_END
	return dest_ptr;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define SR_SET_ONE_512BIT   \
	__sr_setu512_memory((bit512_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	val);					\
	dest_addr += 64;											    \
	count -= 64;													\

#define SR_SET_ONE_256BIT   \
	__sr_setu256_memory((bit256_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	val);				   \
	dest_addr += 32;											   \
	count -= 32;												   \

#define SR_SET_ONE_128BIT   \
	__sr_setu128_memory((bit128_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	val);				   \
	dest_addr += 16;											   \
	count -= 16;											   \

#define SR_SET_ONE_64BIT   \
	__sr_setu64_memory((u64_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	val);				  \
	dest_addr += 8;												  \
	count -= 8;													  \

#define SR_SET_ONE_32BIT   \
	__sr_setu32_memory((u32_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	val);				  \
	dest_addr += 4;												  \
	count -= 4;												  \

#define  SR_SET_ONE_16BIT   \
	__sr_setu16_memory((u16_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	val);					 \
	dest_addr += 2;												 \
	count -= 2;													 \

#define SR_SET_ONE_8BIT   \
	__sr_setu8_memory((u8_t*)ADDRESS_2_VOID_PTR(dest_addr), \
	val);					 \
	dest_addr++;													 \
	--count;														 \

#define SR_TMP_SETMEM_BLOCK(break_triger,SET_FUNC)\
	while (count >= break_triger)			   \
	{							   \
	   SET_FUNC; \
	}	\

#define SR_ALIGNED_512BITSET \
	DO_ONE_LOOP_BEGIN \
	SR_TMP_SETMEM_BLOCK(64, SR_SET_ONE_512BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(32, SR_SET_ONE_256BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(16, SR_SET_ONE_128BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(8, SR_SET_ONE_64BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(4, SR_SET_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(2, SR_SET_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(1, SR_SET_ONE_8BIT);\
	DO_ONE_LOOP_END


#define  SR_ALIGNED_256BITSET(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_256BITSET"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("%d\n",count); \
	  SR_SET_ONE_256BIT; \
      if (0 ==(dest_addr & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITSET;\
		 break;\
	  }													 \
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(32, SR_SET_ONE_256BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(16, SR_SET_ONE_128BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(8, SR_SET_ONE_64BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(4, SR_SET_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(2, SR_SET_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(1, SR_SET_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_128BITSET(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_128BITSET"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("SET count = %d\n", count); \
	  SR_SET_ONE_128BIT; \
      if (0 ==(dest_addr & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITSET;\
		 break;\
	  }													 \
	  else if (0 == (dest_addr & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITSET(MINCOUNT);\
		 break;\
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(16, SR_SET_ONE_128BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(8, SR_SET_ONE_64BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(4, SR_SET_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(2, SR_SET_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(1, SR_SET_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_64BITSET(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_64BITSET"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("SET count = %d\n", count); \
	  SR_SET_ONE_64BIT; \
      if (0 ==(dest_addr & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITSET;\
		 break;\
	  }													 \
	  else if (0 == (dest_addr & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITSET(MINCOUNT);\
		 break;\
	  }\
	  else if (0 == (dest_addr & ALIGNED128BIT_MASK))\
	  {\
	     SR_ALIGNED_128BITSET(MINCOUNT); \
	     break; \
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(8, SR_SET_ONE_64BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(4, SR_SET_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(2, SR_SET_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(1, SR_SET_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_32BITSET(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_32BITSET"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("SET count = %d\n", count); \
	  SR_SET_ONE_32BIT; \
      if (0 ==(dest_addr & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITSET;\
		 break;\
	  }													 \
	  else if (0 == (dest_addr & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITSET(MINCOUNT);\
		 break;\
	  }\
	  else if (0 == (dest_addr & ALIGNED128BIT_MASK))\
	  {\
	     SR_ALIGNED_128BITSET(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (dest_addr & ALIGNED64BIT_MASK))\
	  {\
	     SR_ALIGNED_64BITSET(MINCOUNT); \
	     break; \
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(4, SR_SET_ONE_32BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(2, SR_SET_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(1, SR_SET_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_16BITSET(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_16BITSET"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("SET count = %d\n", count); \
	  SR_SET_ONE_16BIT; \
      if (0 ==(dest_addr & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITSET;\
		 break;\
	  }													 \
	  else if (0 == (dest_addr & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITSET(MINCOUNT);\
		 break;\
	  }\
	  else if (0 == (dest_addr & ALIGNED128BIT_MASK))\
	  {\
	     SR_ALIGNED_128BITSET(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (dest_addr & ALIGNED64BIT_MASK))\
	  {\
	     SR_ALIGNED_64BITSET(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (dest_addr & ALIGNED32BIT_MASK))\
	  {\
	     SR_ALIGNED_32BITSET(MINCOUNT); \
	     break; \
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(2, SR_SET_ONE_16BIT); \
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(1, SR_SET_ONE_8BIT); \
	DO_ONE_LOOP_END

#define  SR_ALIGNED_8BITSET(MINCOUNT) \
	SR_MEM_DEBUG_INFO_OUT("%s\n", "SR_ALIGNED_8BITSET"); \
	DO_ONE_LOOP_BEGIN \
    if (count >= MINCOUNT)\
    {\
	  SR_MEM_DEBUG_INFO_OUT("SET count = %d\n", count); \
	  SR_SET_ONE_8BIT; \
      if (0 ==(dest_addr & ALIGNED512BIT_MASK))	\
      {													 \
		 SR_ALIGNED_512BITSET;\
		 break;\
	  }													 \
	  else if (0 == (dest_addr & ALIGNED256BIT_MASK))\
	  {\
	     SR_ALIGNED_256BITSET(MINCOUNT);\
		 break;\
	  }\
	  else if (0 == (dest_addr & ALIGNED128BIT_MASK))\
	  {\
	     SR_ALIGNED_128BITSET(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (dest_addr & ALIGNED64BIT_MASK))\
	  {\
	     SR_ALIGNED_64BITSET(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (dest_addr & ALIGNED32BIT_MASK))\
	  {\
	     SR_ALIGNED_32BITSET(MINCOUNT); \
	     break; \
	  }\
	  else if (0 == (dest_addr & ALIGNED16BIT_MASK))\
	  {\
	     SR_ALIGNED_16BITSET(MINCOUNT); \
	     break; \
	  }\
	}\
	BREAK_LOOP_CONDITION(!count); \
	SR_TMP_SETMEM_BLOCK(1, SR_SET_ONE_8BIT); \
	DO_ONE_LOOP_END



static SR_INLINE void* sr_memset_inline(void* PARAM_OUT dest,
	u32_t    val,
	usize__t count)
{
	reg_t dest_addr;
	//reg_t same_aligned_mask;
	//bool_t aligned_fin;

	if (0 == count || null == dest)
	{
		return dest;
	}

	dest_addr = POINTER_2_ADDRESS(dest);

	if (0 == (dest_addr & ALIGNED512BIT_MASK))
	{
		SR_ALIGNED_512BITSET;
	}
	else
	if (0 == (dest_addr & ALIGNED256BIT_MASK))
	{
		SR_ALIGNED_256BITSET(96);
	}
	else
	if (0 == (dest_addr & ALIGNED128BIT_MASK))
	{
		SR_ALIGNED_128BITSET(48);
	}
	else
	if (0 == (dest_addr & ALIGNED64BIT_MASK))
	{
		SR_ALIGNED_64BITSET(32);
	}
	else
	if (0 == (dest_addr & ALIGNED32BIT_MASK))
	{
		SR_ALIGNED_32BITSET(16);
	}
	else
	if (0 == (dest_addr & ALIGNED16BIT_MASK))
	{
		SR_ALIGNED_16BITSET(8);
	}
	else
	{
		SR_ALIGNED_8BITSET(4);
	}

	return dest;
}

#endif // SR_MEMCOPY_H_

