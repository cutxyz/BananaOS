//////////////////////////////////////
// sr_memcopy.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////

#ifndef SUNRED_MEMCOPY_H_
#define SUNRED_MEMCOPY_H_

#include "memcopy.h"
#include "object_type.h"


static SR_INLINE void* __sr_objects_copy(
	const object_info_t* PARAM_IN obj_info_ptr,
	void*       PARAM_OUT dest,
	const void* PARAM_IN  src,
	usize__t object_count,
	OBJECT_INIT_CMD_t init_type)
{
	reg_t mem_addr = POINTER_2_ADDRESS(dest);
	while (0 != object_count)
	{
		void* object_ptr = ADDRESS_2_VOID_PTR(mem_addr);
		init_object_with_param(obj_info_ptr,
			object_ptr,
			init_type,
			(void*)src, 1);
		mem_addr += obj_info_ptr->m_memsize;
		--object_count;
	}
	return dest;
}

static SR_INLINE void* __sr_objects_ncopy(
	const object_info_t* PARAM_IN obj_info_ptr,
	void*       PARAM_OUT dest,
	usize__t    dest_count,
	const void* PARAM_IN  src,
	usize__t    src_count,
	OBJECT_INIT_CMD_t init_type)
{
	usize__t copy_count;
	copy_count = (dest_count > src_count) ? src_count : dest_count;
	return 	__sr_objects_copy(obj_info_ptr, dest, src, copy_count, init_type);
}

// 只对初始化过的对象有效
static SR_INLINE void* __sr_objects_move(
	const object_info_t* PARAM_IN obj_info_ptr,
	void* PARAM_IN dest_objs_ptr, usize__t dest_object_count,
	void* PARAM_IN src_objs_ptr, usize__t src_object_count)
{
	same_memory_block_info_t same_info;

	DO_ONE_LOOP_BEGIN

	if (null == obj_info_ptr   || 0 == obj_info_ptr->m_memsize	||
		0 == dest_object_count || dest_objs_ptr == src_objs_ptr ||
		null == dest_objs_ptr || null == src_objs_ptr)
	{
		break;
	}

	__get_same_memoryblock(dest_objs_ptr, 
		dest_object_count * obj_info_ptr->m_memsize, 
		src_objs_ptr, 
		src_object_count * obj_info_ptr->m_memsize,
		&same_info);

	if (0 == same_info.m_samesize)
	{
		__sr_objects_ncopy(obj_info_ptr, dest_objs_ptr, dest_object_count, 
			src_objs_ptr, src_object_count, OBJECT_INIT_COPYE);
		break;
	}
	else
	{
		reg_t dest_addr = POINTER_2_ADDRESS(dest_objs_ptr);
		reg_t src_addr = POINTER_2_ADDRESS(src_objs_ptr);

		if (src_addr >= same_info.m_sameblock_addr)
		{
			__sr_objects_ncopy(obj_info_ptr, dest_objs_ptr, dest_object_count,
				src_objs_ptr, src_object_count, OBJECT_INIT_COPYE);
			break;
		}
		else
		{
			usize__t dest_offset;
			usize__t same_obj_count = same_info.m_samesize / obj_info_ptr->m_memsize;
			dest_offset = src_object_count - same_obj_count;
			if (dest_offset >= dest_object_count)
			{
				__sr_objects_ncopy(obj_info_ptr, dest_objs_ptr, dest_object_count,
					src_objs_ptr, src_object_count, OBJECT_INIT_COPYE);
				break;
			}
			else
			{
				__sr_objects_copy(
					obj_info_ptr,
					ADDRESS_2_VOID_PTR(dest_addr + dest_offset * obj_info_ptr->m_memsize),
					ADDRESS_2_VOID_PTR(same_info.m_sameblock_addr),
					same_obj_count,
					OBJECT_INIT_COPYE);

				__sr_objects_copy(
					obj_info_ptr, 
					dest_objs_ptr, 
					src_objs_ptr, 
					dest_offset, 
					OBJECT_INIT_COPYE);
				break;

			}
		}

	}
	DO_ONE_LOOP_END
	return dest_objs_ptr;
}




//////////////////////////////////////////////////////////////////////////


static SR_FORCE_INLINE void* sr_objects_init(
	const object_info_t* PARAM_IN obj_info_ptr,
	void*       PARAM_OUT dest,
	const void* PARAM_IN  src,
	usize__t object_count)
{
	if (dest && src && object_count)
	{
		if (obj_info_ptr)
		{
			return  __sr_objects_copy(obj_info_ptr, dest, src, object_count, OBJECT_INIT_COPY);
		}
		else
		{
			return sr_memcpy(dest, src, object_count);
		}
	}
	else
	{
		return null;
	}
}

static SR_FORCE_INLINE void* sr_objects_copy(
	const object_info_t* PARAM_IN obj_info_ptr,
	void*       PARAM_OUT dest,
	const void* PARAM_IN  src,
	usize__t object_count)
{
	if (dest && src && object_count)
	{
		if (obj_info_ptr)
		{
			return __sr_objects_copy(obj_info_ptr, dest, src, object_count, OBJECT_INIT_COPYE);
		}
		else
		{
			return sr_memcpy(dest, src, object_count);
		}
	}
	else
	{
		return null;
	}
}

static SR_FORCE_INLINE void* sr_object_ninit(
	const object_info_t* PARAM_IN obj_info_ptr,
	void*       PARAM_OUT dest,
	usize__t    dest_count,
	const void* PARAM_IN  src,
	usize__t    src_count)
{
	if (dest && src &&
		dest_count && src_count)
	{
		if (obj_info_ptr)
		{
			return  __sr_objects_ncopy(obj_info_ptr, dest, dest_count, src, src_count, OBJECT_INIT_COPY);
		}
		else
		{
			return 	sr_memncpy(dest, dest_count, src, src_count);
		}
		
	}
	else
	{
		return null;
	}
}

static SR_FORCE_INLINE void* sr_object_ncopy(
	const object_info_t* PARAM_IN obj_info_ptr,
	void*       PARAM_OUT dest,
	usize__t    dest_count,
	const void* PARAM_IN  src,
	usize__t    src_count)
{
	if (dest && src  && 
		dest_count && src_count)
	{
		if (obj_info_ptr)
		{
			return  __sr_objects_ncopy(obj_info_ptr, dest, dest_count, src, src_count, OBJECT_INIT_COPYE);
		}
		else
		{
			return 	sr_memncpy(dest, dest_count, src, src_count);
		}
		
	}
	else
	{
		return null;
	}
}

#endif//SUNRED_MEMCOPY_H_
