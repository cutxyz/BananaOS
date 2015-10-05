//////////////////////////////////////
// container.h
// Created on: 2015-5-30
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef SUNRED_LIB_CONTAINER_H_
#define SUNRED_LIB_CONTAINER_H_

#include "type.h"
#include "iterator.h"


typedef void* (*container_init_defualt_func) (void* PARAM_OUT contain_ptr);
typedef void* (*container_add_func)          (void* PARAM_IN contain_ptr);
typedef void* (*container_remove_func)       (void* PARAM_IN contain_ptr);
typedef void* (*container_pushback_func)     (void* PARAM_IN contain_ptr);
typedef void* (*container_popback_func)      (void* PARAM_IN contain_ptr);
typedef void* (*container_pushfront_func)    (void* PARAM_IN contain_ptr);
typedef void* (*container_popfront_func)     (void* PARAM_IN contain_ptr);
typedef void* (*container_find_func)         (void* PARAM_IN contain_ptr,
	                                          void* PARAM_OUT iterator_ptr,
	                                          void* PARAM_IN PARAMs, 
	                                          usize__t PARAMBUFF_count, 
	                                          usize__t PARAMBUFF_size);
typedef void* (*container_findnear_func)     (void* PARAM_IN contain_ptr,
	                                          void* PARAM_OUT iterator_ptr,
	                                          void* PARAM_IN PARAMs, 
	                                          usize__t PARAMBUFF_count, 
	                                          usize__t PARAMBUFF_size);

typedef struct st_container_method
{
	iterator_method_t*          itr;
	container_init_defualt_func init;
	container_add_func          add;
	container_remove_func       remove;
	container_pushback_func     pushback;
	container_popback_func	    popback;
	container_pushfront_func    pushfront;
	container_popfront_func		popfront;
	container_find_func			find;
	container_findnear_func		findnear;
}container_method_t;


#endif	 //SUNRED_LIB_CONTAINER_H_
