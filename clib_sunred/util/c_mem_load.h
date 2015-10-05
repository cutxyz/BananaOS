//////////////////////////////////////
// c_math_load.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef C_MEM_LOAD_H_
#define C_MEM_LOAD_H_

#include "../include/type.h"

#define ALIGNED16BIT_MASK  (0x1)
#define ALIGNED32BIT_MASK  (0x3)
#define ALIGNED64BIT_MASK  (0x7)
#define ALIGNED128BIT_MASK (0xF)
#define ALIGNED256BIT_MASK (0x1F)
#define ALIGNED512BIT_MASK (0x3F)




#define CHECK_16BIT_ALIGNED(addr)  (!(addr & ALIGNED16BIT_MASK))
#define CHECK_32BIT_ALIGNED(addr)  (!(addr & ALIGNED32BIT_MASK))
#define CHECK_64BIT_ALIGNED(addr)  (!(addr & ALIGNED64BIT_MASK))
#define CHECK_128BIT_ALIGNED(addr) (!(addr & ALIGNED128BIT_MASK))
#define CHECK_256BIT_ALIGNED(addr) (!(addr & ALIGNED256BIT_MASK))
#define CHECK_512BIT_ALIGNED(addr) (!(addr & ALIGNED512BIT_MASK))

#define __sr_load_memory_c(dest, src)  \
	*(dest) = *(src)


#define __sr_loadu8_memory_c(dest, src)   __sr_load_memory_c((u8_t*)    (dest),   (u8_t*)    (src))
#define __sr_loadu16_memory_c(dest, src)  __sr_load_memory_c((u16_t*)   (dest),   (u16_t*)   (src))
#define __sr_loadu32_memory_c(dest, src)  __sr_load_memory_c((u32_t*)   (dest),   (u32_t*)   (src))
#define __sr_loadu64_memory_c(dest, src)  __sr_load_memory_c((u64_t*)   (dest),   (u64_t*)   (src))
#define __sr_loadu128_memory_c(dest, src) __sr_load_memory_c((bit128_t*)(dest),   (bit128_t*)(src))
#define __sr_loadu256_memory_c(dest, src) __sr_load_memory_c((bit256_t*)(dest),   (bit256_t*)(src))
#define __sr_loadu512_memory_c(dest, src) __sr_load_memory_c((bit512_t*)(dest),   (bit512_t*)(src))

#define __sr_set_memory_c(dest, val)  \
	*(dest) = (val)


#define __sr_setu8_memory_c(dest, val)   __sr_set_memory_c(((u8_t*)dest), val);
#define __sr_setu16_memory_c(dest, val)  __sr_set_memory_c(((u16_t*)dest), val);
#define __sr_setu32_memory_c(dest, val)  __sr_set_memory_c(((u32_t*)dest), val);

#define __sr_setu64_memory_c(dest, val)   __sr_setu32_memory_c(((u32_t*)dest)+0, val);	\
	                                      __sr_setu32_memory_c(((u32_t*)dest)+1, val);

#define __sr_setu128_memory_c(dest, val)  __sr_setu32_memory_c(((u32_t*)dest)+0, val);	\
	                                      __sr_setu32_memory_c(((u32_t*)dest)+1, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+2, val);	\
										  __sr_setu32_memory_c(((u32_t*)dest)+3, val);

#define __sr_setu256_memory_c(dest, val)  __sr_setu32_memory_c(((u32_t*)dest)+0, val);	\
	                                      __sr_setu32_memory_c(((u32_t*)dest)+1, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+2, val);	\
										  __sr_setu32_memory_c(((u32_t*)dest)+3, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+4, val);	\
										  __sr_setu32_memory_c(((u32_t*)dest)+5, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+6, val);	\
										  __sr_setu32_memory_c(((u32_t*)dest)+7, val); 

#define __sr_setu512_memory_c(dest, val)  __sr_setu32_memory_c(((u32_t*)dest)+0 , val);	\
	                                      __sr_setu32_memory_c(((u32_t*)dest)+1 , val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+2 , val);	\
										  __sr_setu32_memory_c(((u32_t*)dest)+3 , val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+4 , val);	\
										  __sr_setu32_memory_c(((u32_t*)dest)+5 , val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+6 , val);	\
										  __sr_setu32_memory_c(((u32_t*)dest)+7 , val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+8 , val);	\
										  __sr_setu32_memory_c(((u32_t*)dest)+9 , val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+10, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+11, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+12, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+13, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+14, val); \
										  __sr_setu32_memory_c(((u32_t*)dest)+15, val);






#endif //C_MEM_LOAD_H_