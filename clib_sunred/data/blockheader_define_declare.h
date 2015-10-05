//////////////////////////////////////
// blockheader_define_begin.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#include "block_header.h"

#ifndef blockinfo_ptr
#define blockinfo_ptr  block_buffinfo_t*
#endif//blockinfo_ptr

#ifndef init_blockinfo
#define init_blockinfo 	init_block_buffinfo_unsafe
#endif//init_blockinfo

#ifndef get_blockinfo_poolsize
#define get_blockinfo_poolsize 	get_block_poolbuff_size_unsafe
#endif//get_blockinfo_poolsize

#ifndef get_blockinfo_poolptr
#define get_blockinfo_poolptr   get_block_poolbuff_ptr_unsafe
#endif//get_blockinfo_poolptr

#ifndef get_blockinfo_using_size
#define get_blockinfo_using_size get_block_usingbuff_size_unsafe
#endif//get_blockinfo_using_size

#ifndef set_blockinfo_using_size
#define set_blockinfo_using_size set_block_usingbuff_size_unsafe
#endif//set_blockinfo_using_size

#ifndef get_blockinfo_using_ptr
#define get_blockinfo_using_ptr  get_block_usingbuff_ptr_unsafe
#endif//get_blockinfo_using_ptr

#ifndef get_blockinfo_using_begin_index
#define get_blockinfo_using_begin_index  get_block_usingbuff_beginindex_unsafe
#endif//get_blockinfo_using_begin_index

#ifndef set_blockinfo_using_begin_index
#define set_blockinfo_using_begin_index  set_block_usingbuff_beginindex_unsafe
#endif//set_blockinfo_using_begin_index

#ifndef set_blockinfo_usingbuf
#define set_blockinfo_usingbuf  set_buffer_to_block_buffinfo_unsafe
#endif//set_blockinfo_usingbuf

#ifndef copy_blockinfo_usingbuf
#define copy_blockinfo_usingbuf  copy_buffer_from_block_buffinfo_unsafe
#endif//copy_blockinfo_usingbuf















