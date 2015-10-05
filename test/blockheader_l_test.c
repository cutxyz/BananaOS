//#undef EXPORT_SUNRED_LIB
#include "../clib_sunred/data/block_header.h"
#include "../clib_sunred/include/util.h"

#define LOG_BUFFER_SIZE	 (32)

void print_blockbuffinfo(const block_buffinfo_t* blk_ptr)
{
	if (blk_ptr)
	{
		printf("(BLOCK)<\nm_using.m_begin=%d;\nm_using.m_size=%d;\nm_pool.m_blockbuffer_ptr=%d\nm_pool.m_size=%d;\n>\n",
			blk_ptr->m_using.m_begin,
			blk_ptr->m_using.m_size,
			blk_ptr->m_pool.m_blockbuffer_ptr,
			blk_ptr->m_pool.m_size);
	}
	else
	{
		printf("null block\n");
	}
}

void block_test()
{
	block_buffinfo_t blk_buf;
	const char* _out_chr_ptr;
	unsigned char* _buffer_ptr = (unsigned char*)malloc(LOG_BUFFER_SIZE);
	if (null == _buffer_ptr)
	{
		return;
	}
	init_block_buffinfo_unsafe(&blk_buf, _buffer_ptr, LOG_BUFFER_SIZE, 0, 0);
	print_blockbuffinfo(&blk_buf);
	sr_memset(_buffer_ptr, 0, LOG_BUFFER_SIZE);
	sr_memcpy(_buffer_ptr, "hehe,you are a sb!", 18);
	set_block_usingbuff_size_unsafe(&blk_buf, 18, TRUE);
	print_blockbuffinfo(&blk_buf);
	_out_chr_ptr = get_block_usingbuff_ptr_unsafe(&blk_buf);
	printf("using_str = %s\n", _out_chr_ptr);
	set_block_usingbuff_beginindex_unsafe(&blk_buf, 17);
	print_blockbuffinfo(&blk_buf);
	_out_chr_ptr = get_block_usingbuff_ptr_unsafe(&blk_buf);
	printf("using_str = %s\n", _out_chr_ptr);
	set_block_usingbuff_beginindex_unsafe(&blk_buf, 20);
	print_blockbuffinfo(&blk_buf);
	_out_chr_ptr = get_block_usingbuff_ptr_unsafe(&blk_buf);
	printf("using_str = %s\n", _out_chr_ptr);
}

