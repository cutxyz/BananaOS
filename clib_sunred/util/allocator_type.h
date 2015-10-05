//////////////////////////////////////
// allocator_type.h
// Created on: 2015-5-25
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////

#ifndef SUNRED_LIB_ALLOCATOR_H_
#define SUNRED_LIB_ALLOCATOR_H_

#include "../include/type.h"

typedef void* (*allocate_func)   (usize__t bytes_count);
typedef void* (*reallocate_func) (void* PARAM_INOUT reallocate_ptr, usize__t bytes_count);
typedef void  (*deallocate_func) (void* PARAM_INOUT del_ptr);

// 获取当前内存的大小
// 参数1：分配器对象指针
// 参数2：内存指针
// 返回值：内存块的大小
typedef usize__t (*local_get_memsize_func)   (void* PARAM_IN alloc_obj_ptr, const void* PARAM_IN mem_ptr);
// 分配一块内存
// 参数1：分配器对象指针
// 参数2：内存块的大小
// 返回值：分配的内存指针
typedef void* (*local_allocate_func)   (void* PARAM_IN alloc_obj_ptr, usize__t bytes_count);
// 重新对一内存再分配
// 参数1：分配器对象指针
// 参数2：需重新分配内存指针
// 参数3：新内存块的大小
// 返回值：再分配的内存指针(当内存不够的时候返回null,当再分配的内存小于原内存的时候100%成功)
typedef void* (*local_reallocate_func) (void* PARAM_IN alloc_obj_ptr, 
	void* PARAM_INOUT reallocate_ptr, usize__t bytes_count);
// 释放内存
// 参数1：分配器对象指针
// 参数2：需释放的内存指针
typedef void  (*local_deallocate_func) (void* PARAM_IN alloc_obj_ptr, void* PARAM_INOUT del_ptr);
// 复位分配器
// 参数1：分配器对象指针
typedef result_t(*local_reset_func) (void* PARAM_IN alloc_obj_ptr);

typedef struct st_memory_allocator
{
	void*                  lo_alloc_object_ptr;
	local_allocate_func	   lo_new_memory;
	local_deallocate_func  lo_delete_memory;
	local_reallocate_func  lo_renew_memory;
	local_get_memsize_func lo_getmemsize;
	local_reset_func       lo_reset;
}memory_allocator_t;

static SR_FORCE_INLINE usize__t memory_size(memory_allocator_t* PARAM_IN alloc_ptr,
	const void* PARAM_IN mem_ptr)
{
	if (alloc_ptr && alloc_ptr->lo_getmemsize)
	{
		return 	alloc_ptr->lo_getmemsize(alloc_ptr->lo_alloc_object_ptr, mem_ptr);
	}
	return 0;
}

static SR_FORCE_INLINE void* memory_new(memory_allocator_t* PARAM_IN alloc_ptr,
	usize__t bytes_count)
{
	if (alloc_ptr && alloc_ptr->lo_new_memory)
	{
		return 	alloc_ptr->lo_new_memory(alloc_ptr->lo_alloc_object_ptr, bytes_count);
	}
	return null;
}

static SR_FORCE_INLINE void* memory_renew(memory_allocator_t* PARAM_IN alloc_ptr,
	void* PARAM_INOUT reallocate_ptr,
	usize__t bytes_count)
{
	if (alloc_ptr && alloc_ptr->lo_renew_memory)
	{
		return 	alloc_ptr->lo_renew_memory(alloc_ptr->lo_alloc_object_ptr, 
					reallocate_ptr, bytes_count);
	}

	return null;
}

static SR_FORCE_INLINE void memory_delete(memory_allocator_t* PARAM_IN alloc_ptr,
	void* PARAM_INOUT del_ptr)
{
	if (alloc_ptr && alloc_ptr->lo_delete_memory)
	{
		alloc_ptr->lo_delete_memory(alloc_ptr->lo_alloc_object_ptr, del_ptr);
		return;
	}
	return;
}

static SR_FORCE_INLINE result_t memory_reset(memory_allocator_t* PARAM_IN alloc_ptr)
{
	if (alloc_ptr && alloc_ptr->lo_reset)
	{
		return alloc_ptr->lo_reset(alloc_ptr->lo_alloc_object_ptr);
	}
	return STATUS_INVALID_PARAMS;
}

static SR_FORCE_INLINE bool_t memory_can_reset(memory_allocator_t* PARAM_IN alloc_ptr)
{
	return (alloc_ptr && alloc_ptr->lo_reset);
}


#include "object_type.h"

typedef struct st_object_allocator
{
	memory_allocator_t* m_memory_allocator_ptr;
	object_info_t*      m_object_info_ptr;
}object_allocator_t;

static SR_INLINE void* allocate_object(
	const object_allocator_t* PARAM_IN ins_ptr, 
	usize__t object_count)
{
	void* mem_ptr;
	ptr_t mem_addr;
	//usize__t i;

	if (null == ins_ptr || 0 == object_count ||
		null == ins_ptr->m_memory_allocator_ptr)
	{
		return null;
	}
	
	if (null == ins_ptr->m_object_info_ptr)
	{
		// 对于非指定类型的对象，按简单的内存块进行处理
		return memory_new(ins_ptr->m_memory_allocator_ptr, object_count);
	}

	if (0 == ins_ptr->m_object_info_ptr->m_memsize)
	{
		return null;
	}

	mem_ptr = memory_new(ins_ptr->m_memory_allocator_ptr, 
		ins_ptr->m_object_info_ptr->m_memsize * object_count);

	if (null == mem_ptr)
	{
		return mem_ptr;
	}

	mem_addr = POINTER_2_ADDRESS(mem_ptr);
	//for (i = 0; i < object_count; ++i)
	while (0 != object_count)
	{
		void* object_ptr = ADDRESS_2_VOID_PTR(mem_addr);
		init_object(ins_ptr->m_object_info_ptr, object_ptr);
		mem_addr += ins_ptr->m_object_info_ptr->m_memsize;
		--object_count;
	}

	return mem_ptr;
}

static SR_INLINE void* allocate_object_withparam(
	const object_allocator_t* PARAM_IN ins_ptr,
	usize__t object_count,
	enum_int_t cmd_type,
	void* PARAM_IN params,
	usize__t param_count)
{
	void* mem_ptr;
	ptr_t mem_addr;
	
	if (null == ins_ptr || 0 == object_count ||
		null == ins_ptr->m_memory_allocator_ptr)
	{
		return null;
	}

	if (null == ins_ptr->m_object_info_ptr)
	{
		// 对于非指定类型的对象，按简单的内存块进行处理
		return memory_new(ins_ptr->m_memory_allocator_ptr, object_count);
	}

	if (0 == ins_ptr->m_object_info_ptr->m_memsize)
	{
		return null;
	}

	mem_ptr = memory_new(ins_ptr->m_memory_allocator_ptr,
		ins_ptr->m_object_info_ptr->m_memsize * object_count);

	if (null == mem_ptr)
	{
		return mem_ptr;
	}

	mem_addr = POINTER_2_ADDRESS(mem_ptr);
	//for (i = 0; i < object_count; ++i)
	while (0 != object_count)
	{
		void* object_ptr = ADDRESS_2_VOID_PTR(mem_addr);
		init_object_with_param(ins_ptr->m_object_info_ptr, 
			object_ptr,
			cmd_type,
			params, param_count);
		mem_addr += ins_ptr->m_object_info_ptr->m_memsize;
		--object_count;
	}

	return mem_ptr;
}

static SR_INLINE result_t delocate_objects(const object_allocator_t* PARAM_IN ins_ptr,
	void* PARAM_INOUT obj_ptr)
{
	void* mem_ptr;
	ptr_t mem_addr;
	int status;
	usize__t object_count;

	if (null == ins_ptr || 0 == object_count ||
		null == ins_ptr->m_memory_allocator_ptr)
	{
		return STATUS_INVALID_PARAMS;
	}

	if (null == ins_ptr->m_object_info_ptr)
	{
		// 对于非指定类型的对象，按简单的内存块进行处理
		memory_delete(ins_ptr->m_memory_allocator_ptr, obj_ptr);
		return STATUS_OK;
	}

	if (0 == ins_ptr->m_object_info_ptr->m_memsize)
	{
		return STATUS_INVALID_PARAMS;
	}

	if (null == ins_ptr || 0 == object_count ||
		null == ins_ptr->m_memory_allocator_ptr ||
		null == ins_ptr->m_object_info_ptr ||
		0 == ins_ptr->m_object_info_ptr->m_memsize)
	{
		return STATUS_INVALID_PARAMS;
	}


	if (null == obj_ptr)
	{
		return STATUS_OK;
	}

	object_count = memory_size(ins_ptr->m_memory_allocator_ptr, obj_ptr);
	object_count /= ins_ptr->m_object_info_ptr->m_memsize;
	if (0 == object_count)
	{
		return STATUS_OK;
	}


	status = STATUS_OK;
	mem_ptr =  obj_ptr;
	mem_addr = POINTER_2_ADDRESS(mem_ptr);
	//for (i = 0; i < object_count; ++i)
	while (0 != object_count)
	{
		void* object_ptr = ADDRESS_2_VOID_PTR(mem_addr);
		int tmp_status = dispose_object(ins_ptr->m_object_info_ptr, object_ptr);
		mem_addr += ins_ptr->m_object_info_ptr->m_memsize;
		if (STATUS_OK != tmp_status)
		{
			status = tmp_status;
		}
		--object_count;
	}
	memory_delete(ins_ptr->m_memory_allocator_ptr, obj_ptr);

	return status;

}

static SR_INLINE void* reallocate_object(
	const object_allocator_t* PARAM_IN ins_ptr,
	void* PARAM_INOUT realloc_objs_ptr,
	usize__t object_count)
{
	void* mem_ptr;
	ptr_t mem_addr;
	usize__t old_mem_size;
	usize__t new_mem_size;

	if (null == ins_ptr || 0 == object_count ||
		null == ins_ptr->m_memory_allocator_ptr)
	{
		return null;
	}

	if (null == ins_ptr->m_object_info_ptr)
	{
		// 对于非指定类型的对象，按简单的内存块进行处理
		return memory_renew(ins_ptr->m_memory_allocator_ptr,
			realloc_objs_ptr,
			object_count);
	}

	if (0 == ins_ptr->m_object_info_ptr->m_memsize)
	{
		return null;
	}

	old_mem_size = memory_size(ins_ptr->m_memory_allocator_ptr, realloc_objs_ptr);
	new_mem_size = ins_ptr->m_object_info_ptr->m_memsize * object_count;

	if (old_mem_size == new_mem_size)
	{
		return realloc_objs_ptr;
	}

	if (old_mem_size > new_mem_size)
	{
		mem_addr = POINTER_2_ADDRESS(realloc_objs_ptr);
		mem_addr += new_mem_size;
		object_count = old_mem_size / ins_ptr->m_object_info_ptr->m_memsize - object_count;
		while (0 != object_count)
		{
			void* object_ptr = ADDRESS_2_VOID_PTR(mem_addr);
			dispose_object(ins_ptr->m_object_info_ptr, object_ptr);
			mem_addr += ins_ptr->m_object_info_ptr->m_memsize;
			--object_count;
		}
	}

	mem_ptr = memory_renew(ins_ptr->m_memory_allocator_ptr,
		realloc_objs_ptr,
		new_mem_size);

	if (null == mem_ptr)
	{
		return mem_ptr;
	}

	if (old_mem_size < new_mem_size)
	{
		mem_addr = POINTER_2_ADDRESS(mem_ptr);
		mem_addr += old_mem_size;
		object_count -= old_mem_size / ins_ptr->m_object_info_ptr->m_memsize;
		while (0 != object_count)
		{
			void* object_ptr = ADDRESS_2_VOID_PTR(mem_addr);
			init_object(ins_ptr->m_object_info_ptr, object_ptr);
			mem_addr += ins_ptr->m_object_info_ptr->m_memsize;
			--object_count;
		}
	}

	return mem_ptr;
}





#endif	 //SUNRED_LIB_ALLOCATOR_H_
