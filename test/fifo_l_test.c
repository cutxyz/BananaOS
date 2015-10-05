//#undef EXPORT_SUNRED_LIB
#define SR_MEM_DEBUG_INFO
#include "../clib_sunred/include/clib_sunred.h"


#include "../clib_sunred/data/fifo_ring.h"
#include "../clib_sunred/data/fifo_ring_template.c"




#define LOG_BUFFER_SIZE	 (32)
static void print_fifoinfo(const ring_fifo_header_t* fifo_ptr)
{
	if (fifo_ptr)
	{
		printf("(FIFO)<\nm_begin_index=%d;\nm_end_index=%d;\nm_is_full=%d\nm_fifo_size=%d;\nm_fifo_buffer=%08X\n>\n",
			fifo_ptr->m_begin_index,
			fifo_ptr->m_end_index,
			fifo_ptr->m_is_full,
			fifo_ptr->m_fifo_size,
			fifo_ptr->m_fifo_buffer);
	}
	else
	{
		printf("null fifo\n");
	}
}
static void print_vfifobuff(const ring_fifo_header_t* fifo_ptr)
{
	if (fifo_ptr)
	{
		int i;
		int size;
		int linecount = 0;

		size = _get_vfifo_data_length(fifo_ptr);

		printf("vfifo size = %d \n {\n", size);
		for (i = 0; i < size; ++i)
		{
			int val;
			val = *_get_vfifo_value_at(fifo_ptr, i);
			val &= 0xFF;
			printf("%d ", val);
			++linecount;
			if (16 <= linecount)
			{
				linecount = 0;
				printf("\n");
			}
		}
		printf("}\n");
	}
	else
	{
		printf("null vfifo\n");
	}
}

static void print_int_buf(const int* arr_ptr, unsigned int size)
{
	if (null == arr_ptr || size <= 0)
	{
		printf("empty size array!\n");
	}
	else
	{
		int i;
		int linecount = 0;
		printf("array size = %d \n {\n", size);
		for (i = 0; i < size; ++i)
		{
			printf("%d ", arr_ptr[i]);
			++linecount;
			if (16 <= linecount)
			{
				linecount = 0;
				printf("\n");
			}
		}
		printf("}\n");
	}
}

static void chr_fifo_test()
{

	ring_fifo_header_t fifo_header;
	unsigned char  pop_buf[64];

	unsigned char  staticfifobuffer[16];
	unsigned char* fifo_buffer = (unsigned char*)malloc(LOG_BUFFER_SIZE);
	int result;
	int str_buf_size;
	const char* str_ptr;

	if (null == fifo_buffer)
	{
		__bind_buffer_to_fifo_header(&fifo_header, staticfifobuffer, sizeof(staticfifobuffer));
	}
	else
	{
		__bind_buffer_to_fifo_header(&fifo_header, fifo_buffer, LOG_BUFFER_SIZE);
	}
	printf("0\n");
	print_fifoinfo(&fifo_header);

	str_ptr = "hehe123";
	result = __push_back_fifo(&fifo_header, str_ptr, strlen(str_ptr));
	
	printf("1\n");
	print_fifoinfo(&fifo_header);
	str_buf_size = __pop_front_fifo_to_buff(&fifo_header,
		8, pop_buf);

	pop_buf[str_buf_size] = 0;
	printf("%s\n", pop_buf);

	printf("2\n");
	print_fifoinfo(&fifo_header);

	result = __push_back_fifo(&fifo_header, str_ptr, strlen(str_ptr));

	printf("3\n");
	print_fifoinfo(&fifo_header);

	str_ptr = "hehe1234567890";
	result = __push_back_fifo(&fifo_header, str_ptr, strlen(str_ptr));

	printf("4\n");
	print_fifoinfo(&fifo_header);

	str_buf_size = __pop_front_fifo_to_buff(&fifo_header,
		16, pop_buf);
	pop_buf[str_buf_size] = 0;

	printf("5\n");
	print_fifoinfo(&fifo_header);
	printf("%s\n", pop_buf);

	str_ptr = "heheasdfghjkl123456789012345678901234567890123456789012";
	//result = __push_back_fifo(&fifo_header, str_ptr, strlen(str_ptr));
	result = __force_push_back_fifo(&fifo_header, str_ptr, strlen(str_ptr));

	printf("6\n");
	print_fifoinfo(&fifo_header);

	str_buf_size = __pop_front_fifo_to_buff(&fifo_header,
		32, pop_buf);
	printf("7\n");
	print_fifoinfo(&fifo_header);
	pop_buf[str_buf_size] = 0;
	printf("%s\n", pop_buf);


	return;

}

static void int_fifo_test()
{

	ring_fifo_header_t fifo_header;
	unsigned int  pop_buf[64];

	unsigned int  staticfifobuffer[16];
	unsigned int* fifo_buffer = (unsigned int*)malloc(LOG_BUFFER_SIZE*sizeof(int));
	int result;
	int str_buf_size;
	
	int str_ptr[100];
	int i;

	if (null == fifo_buffer)
	{
		_bind_buffer_to_vfifo_header(&fifo_header, staticfifobuffer, sizeof(staticfifobuffer)/sizeof(int));
	}
	else
	{
		_bind_buffer_to_vfifo_header(&fifo_header, fifo_buffer, LOG_BUFFER_SIZE);
	}
	printf("0\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);
	for (i = 0; i < 100; ++i)
	{
		str_ptr[i] = i;
	}
	result = _push_back_vfifo(&fifo_header, str_ptr, 8);

	printf("1\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);
	str_buf_size = _pop_front_vfifo_to_buff(&fifo_header,
		8, pop_buf);

	pop_buf[str_buf_size] = 0;
	print_int_buf(pop_buf, str_buf_size);

	printf("2\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);

	result = _push_back_vfifo(&fifo_header, str_ptr, 8);

	printf("3\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);

	result = _push_back_vfifo(&fifo_header, str_ptr, 14);

	printf("4\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);

	str_buf_size = _pop_front_vfifo_to_buff(&fifo_header,
		16, pop_buf);
	pop_buf[str_buf_size] = 0;

	printf("5\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);
	print_int_buf(pop_buf, str_buf_size);


	//result = __push_back_fifo(&fifo_header, str_ptr, strlen(str_ptr));
	result = _force_push_back_vfifo(&fifo_header, str_ptr, 20);

	printf("6\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);

	str_buf_size = _pop_front_vfifo_to_buff(&fifo_header,
		32, pop_buf);
	printf("7\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);
	pop_buf[str_buf_size] = 0;
	print_int_buf(pop_buf, str_buf_size);


	return;

}

void fifo_test()
{
	printf("chr_fifo_test\n");
	chr_fifo_test();
    
	printf("int_fifo_test\n");
	int_fifo_test();
}