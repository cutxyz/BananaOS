//////////////////////////////////////
// object_type.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef SUNRED_OBJECT_TYPE_H_
#define SUNRED_OBJECT_TYPE_H_

#include "../include/type.h"

typedef result_t(*defualt_init_object_func)(void* PARAM_INOUT object_ptr);

typedef enum enumOBJECT_INIT_CMD
{
	OBJECT_INIT_DEFAULT = 0,
	OBJECT_INIT_COPY,
	OBJECT_INIT_COPYE,
	OBJECT_INIT_USER
}OBJECT_INIT_CMD_t;

typedef result_t(*init_object_func)(void* PARAM_INOUT object_ptr,
	enum_int_t cmd_type,
	void* PARAM_IN params, 
	usize__t param_count);

typedef result_t (*dispose_object_func)
   (void* PARAM_INOUT object_ptr);

typedef void(*call_exception_func)
   (void* PARAM_INOUT object_ptr, 
   result_t status);

typedef struct st_obejct_info
{
	struct st_obejct_info*   m_inherit_info_ptr;

	usize__t m_memsize;

	defualt_init_object_func defualt_init;
	init_object_func         init;
	dispose_object_func	     dispose;
	call_exception_func      init_exception_handle;
	call_exception_func      dispose_exception_handle;
}object_info_t;

static SR_INLINE result_t init_object(const object_info_t* PARAM_INOUT object_info_ptr,
	void* PARAM_INOUT obj_ptr)
{
	result_t status = STATUS_OK;

	if (null == object_info_ptr)
	{
		return STATUS_OK;
	}

	if (object_info_ptr->m_inherit_info_ptr)
	{
		status = init_object (object_info_ptr->m_inherit_info_ptr,
			obj_ptr);
	}

	if (STATUS_OK != status)
	{
		return status;
	}
	
	if (object_info_ptr->defualt_init)
	{
		status = object_info_ptr->defualt_init(obj_ptr);
		if (STATUS_OK != status && object_info_ptr->init_exception_handle)
		{
			object_info_ptr->init_exception_handle(obj_ptr, status);
		}
		return status;
	}
	else
	{
		return STATUS_OK;
	}
	
}

static SR_INLINE result_t init_object_with_param(const object_info_t* PARAM_INOUT object_info_ptr,
	void* PARAM_INOUT obj_ptr,
	enum_int_t cmd_type,
	void* PARAM_IN params,
	usize__t param_count)
{
	result_t status = init_object(object_info_ptr->m_inherit_info_ptr,
		obj_ptr);
	if (STATUS_OK != status)
	{
		return status;
	}

	if (object_info_ptr->init)
	{
		status = object_info_ptr->init(obj_ptr,
			cmd_type,
			params,
			param_count);

		if (STATUS_OK != status && object_info_ptr->init_exception_handle)
		{
			object_info_ptr->init_exception_handle(obj_ptr, status);
		}
		return status;
	}
	else
	{
		return STATUS_OK;
	}
}

static SR_INLINE result_t dispose_object(object_info_t* PARAM_INOUT object_info_ptr,
	void* PARAM_INOUT obj_ptr)
{
	result_t status = STATUS_OK;

	while (object_info_ptr)
	{
		if (object_info_ptr->dispose)
		{
			status = object_info_ptr->dispose(obj_ptr);

			if (STATUS_OK != status && object_info_ptr->dispose_exception_handle)
			{
				object_info_ptr->dispose_exception_handle(obj_ptr, status);
				break;
			}
		}

		object_info_ptr = object_info_ptr->m_inherit_info_ptr;
	}
	return status;
}

static SR_INLINE result_t dispose_objects(object_info_t* PARAM_INOUT obj_info_ptr,
	void* PARAM_INOUT objs_ptr,
	usize__t objs_count)
{
	result_t status   = STATUS_OK;
	reg_t    mem_addr = POINTER_2_ADDRESS(objs_ptr);
	while (0 != objs_count)
	{
		void*    object_ptr = ADDRESS_2_VOID_PTR(mem_addr);
		result_t tmp_status = dispose_object(obj_info_ptr, objs_ptr);
		if (STATUS_OK != tmp_status)
		{
			status = tmp_status;
		}
		mem_addr += obj_info_ptr->m_memsize;
		--objs_count;
	}
	return status;
}







#endif	 //SUNRED_OBJECT_TYPE_H_
