#include "../clib_sunred/include/clib_sunred.h"
#include "../clib_sunred/algorithm/quicksort.h"
#include "../clib_sunred/algorithm/checkorder_template.c"

typedef struct st_int_array
{
	int*  m_data_ptr;
	int   m_size;
}int_array_t;
typedef struct st_int_array_itr
{
	int           m_index;
	int_array_t*  m_arr_ptr;
}int_array_itr_t;

static void* __init_int_arr_iterator(void* PARAM_OUT itr_ptr,
	void* PARAM_IN  contain_ptr)
{
	int_array_itr_t*  _itr_ptr = (int_array_itr_t*)itr_ptr;
	_itr_ptr->m_index   = 0;
	_itr_ptr->m_arr_ptr = (int_array_t*)contain_ptr;
	return itr_ptr;
}
static void* __copy_int_arr_iterator(void* PARAM_OUT des_itr_ptr,
	const void* PARAM_IN src_itr_ptr)
{
	sr_memcpy(des_itr_ptr, src_itr_ptr, sizeof(int_array_itr_t));
	return des_itr_ptr;
}

static void* __begin_int_arr_iterator(void* PARAM_OUT itr_ptr)
{
	int_array_itr_t*  _itr_ptr = (int_array_itr_t*)itr_ptr;
	_itr_ptr->m_index = (_itr_ptr->m_arr_ptr->m_size > 0)?(0):(-1);
	return _itr_ptr;
}
static void* __end_int_arr_iterator(void* PARAM_OUT itr_ptr)
{
	int_array_itr_t*  _itr_ptr = (int_array_itr_t*)itr_ptr;
	_itr_ptr->m_index = (_itr_ptr->m_arr_ptr->m_size > 0) ? (_itr_ptr->m_arr_ptr->m_size-1):(-1);
	return _itr_ptr;
}
static void* __increase_int_arr_iterator(void* PARAM_OUT itr_ptr)
{
	int_array_itr_t*  _itr_ptr = (int_array_itr_t*)itr_ptr;
	if (_itr_ptr->m_index >= 0)
	{
		++(_itr_ptr->m_index);
		if (_itr_ptr->m_index >= _itr_ptr->m_arr_ptr->m_size)
		{
			_itr_ptr->m_index = -1;
		}
	}
	return _itr_ptr;
}
static void* __decrease_int_arr_iterator(void* PARAM_OUT itr_ptr)
{
	int_array_itr_t*  _itr_ptr = (int_array_itr_t*)itr_ptr;
	if (_itr_ptr->m_index >= 0)
	{
		--(_itr_ptr->m_index);
	}
	return _itr_ptr;
}

static int __equals_int_arr_iterator(const void* PARAM_IN first_itr_ptr, const void* PARAM_IN second_itr_ptr)
{
	int_array_itr_t*  first_ptr  = (int_array_itr_t*)first_itr_ptr;
	int_array_itr_t*  second_ptr = (int_array_itr_t*)second_itr_ptr;
	return first_ptr->m_index - second_ptr->m_index;
}

static void* __int_arr_get_at(void* PARAM_IN array_ptr,
	const void* PARAM_IN itr_ptr)
{
	if (itr_ptr)
	{
		int_array_t*     arr_ptr     = (int_array_t*)array_ptr;
		int_array_itr_t* arr_itr_ptr = (int_array_itr_t*)itr_ptr;
		if (arr_itr_ptr->m_index >= 0 && arr_itr_ptr->m_index <arr_ptr->m_size)
		{
			return (arr_ptr->m_data_ptr + arr_itr_ptr->m_index);
		}
		else
		{
			return null;
		}
	}

	return null;	
}

static int __int_arr_value_swap(void* PARAM_IN array_ptr,
	const void* PARAM_IN first_itr_ptr,
	const void* PARAM_IN second_itr_ptr)
{
	int* first_ptr  = (int*)__int_arr_get_at(array_ptr,first_itr_ptr);
	int* second_ptr = (int*)__int_arr_get_at(array_ptr, second_itr_ptr);
	int tmp;
	if (first_ptr && second_ptr)
	{
		tmp = *first_ptr;
		*first_ptr = *second_ptr;
		*second_ptr = tmp;
		return STATUS_OK;
	}
	else
	{
		return STATUS_INVALID_PARAMS;
	}
}
static int __int_arr_compare_two_array_item(
	//void* PARAM_IN array_ptr,
	const void* PARAM_OUT first,
	const void* PARAM_IN second)
{
	int* first_ptr  = (int*)first;//__int_arr_get_at(array_ptr, first);
	int* second_ptr = (int*)second;//__int_arr_get_at(array_ptr, second);
	return *first_ptr - *second_ptr;
}

static void print_arr(const int_array_t* arr_ptr)
{
	if (null == arr_ptr || null == arr_ptr->m_data_ptr || arr_ptr->m_size <= 0)
	{
		printf("empty size array!\n");
	}
	else
	{
		int i;
		int linecount = 0;
		printf("array size = %d \n {\n", arr_ptr->m_size);
		for (i = 0; i < arr_ptr->m_size; ++i)
		{
			printf("%d ", arr_ptr->m_data_ptr[i]);
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

#define TEST_ARR_DATA \
{ 1, 3, 5, 2, 4, 6, 20, 19, 18, 17, 16, 15, 7, 8, 9, 10, 14, 13, 12, 11 }
//{ 1111, 3, 5, 2, 4, 116, 20, 19, 18, 171, 16, 15, 71, 8, 9, 10, 14, 13, 12, 11 }
//{ 1, 3, 5, 2, 4, 6, 20, 19, 18, 17, 16, 15, 7, 8, 9, 10, 14, 13, 12, 11 }
//{ 1111, 3, 5, 2, 4, 116, 20, 19, 18, 171, 16, 15, 71, 8, 9, 10, 14, 13, 12, 11 }
//{ 1, 4, 6, 7, 6, 6, 7, 6, 8, 6 }

void quick_sort_comm_array_test()
{
	sort_array_t qs_arr;
	iterator_method_t itr_method;
	int_array_t       int_arr;
	int_array_itr_t   begin_itr, end_itr;
	int               arr[] = TEST_ARR_DATA;
		//= { 1, 3, 5, 2, 4, 6, 20, 19, 18, 17, 16, 15, 7, 8, 9, 10, 14, 13, 12, 11 };
		//= { 1111, 3, 5, 2, 4, 116, 20, 19, 18, 171, 16, 15, 71, 8, 9, 10, 14, 13, 12, 11 };
		//= { 1, 4, 6, 7, 6, 6, 7, 6, 8, 6 };
	int               status;

	int_arr.m_data_ptr = arr;
	int_arr.m_size     = sizeof(arr)/sizeof(int);

	itr_method.init     = __init_int_arr_iterator;
	itr_method.equals   = __equals_int_arr_iterator;
	itr_method.copy     = __copy_int_arr_iterator;
	itr_method.begin    = __begin_int_arr_iterator;
	itr_method.end      = __end_int_arr_iterator;
	itr_method.increase = __increase_int_arr_iterator;
	itr_method.decrease = __decrease_int_arr_iterator;

	itr_method.init(&begin_itr, &int_arr);
	itr_method.begin(&begin_itr);

	itr_method.init(&end_itr, &int_arr);
	itr_method.end(&end_itr);

	qs_arr.array_ptr  = &int_arr;
	qs_arr.itr_method = &itr_method;
	qs_arr.at         = __int_arr_get_at;
	qs_arr.swap       = __int_arr_value_swap;
	qs_arr.cmp        = __int_arr_compare_two_array_item;

	print_arr(&int_arr);

	printf("begin quicksort!\n");
	status = quick_sort(&qs_arr, &begin_itr, &end_itr);
	printf("end quicksort!\n");
	print_arr(&int_arr);

}

static void print_int_arr(const INT_BUF_t* arr_ptr)
{
	if (null == arr_ptr || null == arr_ptr->m_buf || arr_ptr->m_size <= 0)
	{
		printf("empty size array!\n");
	}
	else
	{
		int i;
		int linecount = 0;
		printf("array size = %d \n {\n", arr_ptr->m_size);
		for (i = 0; i < arr_ptr->m_size; ++i)
		{
			printf("%d ", arr_ptr->m_buf[i]);
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

void quick_sort_int_array_test()
{
	INT_BUF_t qs_arr;

	int  arr[] = TEST_ARR_DATA;
		//= { 1, 3, 5, 2, 4, 6, 20, 19, 18, 17, 16, 15, 7, 8, 9, 10, 14, 13, 12, 11 };
		//= { 1111, 3, 5, 2, 4, 116, 20, 19, 18, 171, 16, 15, 71, 8, 9, 10, 14, 13, 12, 11 };
		//= { 1, 4, 6, 7, 6, 6, 7, 6, 8, 6 };

	int       status;
	int       begin_itr, end_itr;
	int       order_count;
	int       is_order;


	qs_arr.m_buf = arr;
	qs_arr.m_size = sizeof(arr) / sizeof(int);

	begin_itr = 0;
	end_itr = (qs_arr.m_size>0) ? (qs_arr.m_size-1):(0);
	print_int_arr(&qs_arr);

	order_count = __get_order_first_inc_count(qs_arr.m_buf, begin_itr, end_itr);
	is_order = __check_order_inc(qs_arr.m_buf, begin_itr, end_itr);
	printf("order count=%d, is order?=%d\n", order_count, is_order);

	printf("begin quicksort!\n");
	status = quick_sort_int_array(&qs_arr, begin_itr, end_itr);
	printf("end quicksort!\n");
	print_int_arr(&qs_arr);

	order_count = __get_order_first_inc_count(qs_arr.m_buf, begin_itr, end_itr);
	is_order = __check_order_inc(qs_arr.m_buf, begin_itr, end_itr);
	printf("order count=%d, is order?=%d\n", order_count, is_order);

}

void quick_sort_test()
{
	printf("common array quicksort!\n");
	quick_sort_comm_array_test();

	printf("\nint array quicksort!\n");
	quick_sort_int_array_test();
}



