//#undef EXPORT_SUNRED_LIB
#define SR_MEM_DEBUG_INFO
#include "../clib_sunred/include/clib_sunred.h"
#include "../clib_sunred/data/fifo_ring.h"

typedef struct st_BUF
{
	unsigned char* m_buf;
	int            m_buf_size;
}st_BUF_t;

typedef struct st_BUF_CONST
{
	const unsigned char* m_buf;
	int            m_buf_size;
}st_BUF_CONST_t;

typedef union un_BUF
{
	st_BUF_t       m_buf;
	st_BUF_CONST_t m_buf_const;
	unsigned char  m_ptr_buf[sizeof(st_BUF_t)];
}BUF_t;

typedef struct st_SPDU_BUF
{
	int            index;
	BUF_t          m_spdu;
}st_SPDU_BUF_t;

typedef union un_SPDU_BUF
{
	st_SPDU_BUF_t       m_buf;
	unsigned char       m_ptr_buf[sizeof(st_SPDU_BUF_t)];
}SPDU_BUF_t;


#ifndef FIFO_RING_VAL
#define FIFO_RING_VAL  SPDU_BUF_t
#endif//FIFO_RING_VAL

#ifndef FIFO_RING_VAL_SIZE 
#define FIFO_RING_VAL_SIZE sizeof(SPDU_BUF_t)
#endif//FIFO_RING_VAL_SIZE
#include "../clib_sunred/data/fifo_ring_template.c"

#define SORTARRAY_ITERATOR_ITR              int	
#define SORTARRAY_ITERATOR_REF              int*
#define SORTARRAY_ITERATOR_INSTANCE         int
#define GET_ITERATOR_INSTANCE_ADDR(ins)     (ins)
#define GET_ITERATOR_INSTANCE_ADDR_REF(ins) &(ins)
#define SORTARRAY                           ring_fifo_header_t*
#define SORTARRAY_ITEM_PTR	                SPDU_BUF_t*

#define GET_SORTARRAY_AT(arr,_at)                   _get_vfifo_value_at((arr),(_at))
#define SORTARRAY_ITR_EQUELS(arr,itr1_ptr,itr2_ptr) ((itr1_ptr)-(itr2_ptr))
#define SORTARRAY_ITR_CMPITEM(arr,itm1,itm2)        ((itm1)->m_buf.index-(itm2)->m_buf.index)
#define SORTARRAY_ITR_INC(arr,itr_ptr)	            (++(itr_ptr))
#define SORTARRAY_ITR_DEC(arr,itr_ptr)	            (--(itr_ptr))
#define SORTARRAY_ITR_COPY(arr,des,src)	            ((des) = (src))
#define SORTARRAY_ITR_COPY_TO_REF(arr,des,src)      (*(des) = (src))

static SR_INLINE int sbuf_value_swap(SORTARRAY PARAM_INOUT arr, SORTARRAY_ITERATOR_ITR itr1, SORTARRAY_ITERATOR_ITR itr2)
{
	SPDU_BUF_t tmp = *GET_SORTARRAY_AT(arr, itr1);
	*GET_SORTARRAY_AT(arr, itr1) = *GET_SORTARRAY_AT(arr, itr2);
	*GET_SORTARRAY_AT(arr, itr2) = tmp;
	return STATUS_OK;
}

#define SORTARRAY_SWAP_ITEM_BY_ITR  sbuf_value_swap
#include "../clib_sunred/algorithm/quicksort_template.c"

#ifndef SEQUENCE_ARRAY
#define SEQUENCE_ARRAY ring_fifo_header_t*
#endif//SEQUENCE_ARRAY

#ifndef SEQUENCE_ARRAY_ITR
#define SEQUENCE_ARRAY_ITR int
#endif//SEQUENCE_ARRAY_ITR

#ifndef SEQUENCE_ARRAY_ITEM_PTR
#define SEQUENCE_ARRAY_ITEM_PTR	SPDU_BUF_t*
#endif//SEQUENCE_ARRAY_ITEM_PTR

#ifndef GET_SEQUENCE_ARRAY_AT
#define GET_SEQUENCE_ARRAY_AT(arr,_at)                       _get_vfifo_value_at((arr),(_at))
#endif//GET_SEQUENCE_ARRAY_AT

#ifndef SEQUENCE_ARRAY_VALUE_CMP
#define SEQUENCE_ARRAY_VALUE_CMP(itm1_ptr, itm2_ptr)         ((itm1)->m_buf.index-(itm2)->m_buf.index)
#endif//SEQUENCE_ARRAY_VALUE_CMP

#ifndef SEQUENCE_ARRAY_ITR_EQUELS
#define SEQUENCE_ARRAY_ITR_EQUELS(arr,itr1_ptr,itr2_ptr)     ((itr1_ptr)-(itr2_ptr))
#endif//SEQUENCE_ARRAY_ITR_EQUELS

#ifndef SEQUENCE_ARRAY_ITR_INC
#define SEQUENCE_ARRAY_ITR_INC(arr,itr_ptr)	                 (++(itr_ptr))
#endif//SEQUENCE_ARRAY_ITR_INC

#ifndef SEQUENCE_ARRAY_ITR_DEC
#define SEQUENCE_ARRAY_ITR_DEC(arr,itr_ptr)	                 (--(itr_ptr))
#endif//SEQUENCE_ARRAY_ITR_DEC
#include "../clib_sunred/algorithm/checkorder_template.c"


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
			SPDU_BUF_t* val;
			val = _get_vfifo_value_at(fifo_ptr, i);
		
			printf("%d ", val->m_buf.index);
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

static void print_int_buf(const SPDU_BUF_t* arr_ptr, unsigned int size)
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
			printf("%d ", arr_ptr[i].m_buf.index);
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


static void int_fifo_test()
{

	ring_fifo_header_t fifo_header;
	SPDU_BUF_t  pop_buf[64];

	SPDU_BUF_t  staticfifobuffer[16];
	SPDU_BUF_t* fifo_buffer = (SPDU_BUF_t*)malloc(LOG_BUFFER_SIZE*sizeof(SPDU_BUF_t));
	int result;
	int str_buf_size;
	int       order_count;
	int       is_order;
	
	SPDU_BUF_t str_ptr[100];
	int i;

	if (null == fifo_buffer)
	{
		_bind_buffer_to_vfifo_header(&fifo_header, staticfifobuffer, sizeof(staticfifobuffer) / sizeof(SPDU_BUF_t));
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
		str_ptr[i].m_buf.index = i;
		str_ptr[i].m_buf.m_spdu.m_buf.m_buf = null;
		str_ptr[i].m_buf.m_spdu.m_buf.m_buf_size = 0;
	}
	result = _push_back_vfifo(&fifo_header, str_ptr, 8);

	printf("1\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);
	str_buf_size = _pop_front_vfifo_to_buff(&fifo_header,
		8, pop_buf);

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

	printf("5\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);
	print_int_buf(pop_buf, str_buf_size);


	//result = __push_back_fifo(&fifo_header, str_ptr, strlen(str_ptr));
	result = _force_push_back_vfifo(&fifo_header, str_ptr, 20);

	printf("6\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);

	order_count = __get_order_first_inc_count(&fifo_header, 0, _get_vfifo_data_length(&fifo_header) - 1);
	is_order = __check_order_inc(&fifo_header, 0, _get_vfifo_data_length(&fifo_header) - 1);
	printf("\norder count=%d, is order?=%d\n", order_count, is_order);

	printf("\nfifo quicksort!\n");
	__quick_sort(&fifo_header, 0, _get_vfifo_data_length(&fifo_header) - 1);


	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);

	order_count = __get_order_first_inc_count(&fifo_header, 0, _get_vfifo_data_length(&fifo_header) - 1);
	is_order = __check_order_inc(&fifo_header, 0, _get_vfifo_data_length(&fifo_header) - 1);
	printf("\norder count=%d, is order?=%d\n", order_count, is_order);

	str_buf_size = _pop_front_vfifo_to_buff(&fifo_header,
		32, pop_buf);
	printf("7\n");
	print_fifoinfo(&fifo_header);
	print_vfifobuff(&fifo_header);
	print_int_buf(pop_buf, str_buf_size);



	return;

}

void sort_fifo_test()
{
	printf("int_fifo_test\n");
	int_fifo_test();
}