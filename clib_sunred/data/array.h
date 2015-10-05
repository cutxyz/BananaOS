//////////////////////////////////////
// array.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef SUNRED_LIB_ARRAY_H_
#define SUNRED_LIB_ARRAY_H_

#include "bst_method.h"
#include "iterator.h"



typedef struct st_array_header 
{

	const iterator_method_t*     itr;
}array_header_t;





#endif	 //SUNRED_LIB_ARRAY_H_
