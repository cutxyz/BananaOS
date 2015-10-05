//////////////////////////////////////
// array_method.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef SUNRED_LIB_ARRAY_METHOD_H_
#define SUNRED_LIB_ARRAY_METHOD_H_

#include "compareto.h"
#include "../util/object_type.h"
#include "iterator.h"

typedef void* (get_array_at_func)(void* PARAM_INOUT array_ptr, const iterator_method_t* PARAM_IN itr_ptr);

#endif	 //SUNRED_LIB_ARRAY_METHOD_H_
