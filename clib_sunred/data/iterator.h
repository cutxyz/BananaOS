//////////////////////////////////////
// iterator.h
// Created on: 2015-5-30
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef SUNRED_LIB_ITERATOR_H_
#define SUNRED_LIB_ITERATOR_H_

#include "../include/type.h"

typedef void* (*init_iterator_func)    (void* PARAM_OUT itr_ptr, 
	                                    void* PARAM_IN  contain_ptr);
typedef void* (*copy_iterator_func)    (void* PARAM_OUT des_itr_ptr, const void* PARAM_IN src_itr_ptr);

typedef int   (*equals_iterator_func)  (const void* PARAM_IN first_itr_ptr, const void* PARAM_IN second_itr_ptr);

typedef void* (*begin_iterator_func)   (void* PARAM_OUT itr_ptr);
typedef void* (*end_iterator_func)     (void* PARAM_OUT itr_ptr);
typedef void* (*increase_iterator_func)(void* PARAM_OUT itr_ptr);
typedef void* (*decrease_iterator_func)(void* PARAM_OUT itr_ptr);

typedef struct st_iterator_method
{
	init_iterator_func       init;
	copy_iterator_func       copy;
	equals_iterator_func     equals;
	begin_iterator_func	     begin;
	end_iterator_func        end;
	increase_iterator_func	 increase;
	decrease_iterator_func   decrease;
}iterator_method_t;

typedef const iterator_method_t* (*get_iterator_method_func)();


#endif	 //SUNRED_LIB_ITERATOR_H_
