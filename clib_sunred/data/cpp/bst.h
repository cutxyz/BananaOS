//////////////////////////////////////
// bst.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
#ifndef CPP_SUNRED_BST_H_
#define CPP_SUNRED_BST_H_

#include "clib_sunred.h"

#include "bst_iterator.h"

template < class tree_method_traits,
	       class key_type,
		   class key_compare_method,
		   class node_alloc >
class cbinary_search_tree
{
public:
	typedef tree_method_traits   tree_method_t;
	typedef key_type             key_t;
	typedef key_compare_method   cmp_t;
	typedef node_alloc           node_alloc_t;
	
	typedef tree_method_t::link_type_t  linked_t;

	//typedef node_alloc_t::obj_alloc_t obj_allocate_t;

	typedef enum  enumREMOVE_ITERATOR_NEXT_OPERATE
	{
		SET_ITR_NOTHING = 0,
		SET_ITR_INCREASE,
		SET_ITR_DECREASE,
		SET_ITR_TRY_NOTNULL,

		REMOVE_ITERATOR_NEXT_OPERATE_COUNT
	}REMOVE_ITERATOR_NEXT_OPERATE_t;
	
	typedef struct st_node_pair
	{
		linked_t  m_linked;
		key_t     m_key;
	}node_pair_t;

	typedef cbinary_search_tree< tree_method_t, key_t, cmp_t, node_alloc_t > bstree_t;


	class const_bstree_node;
	class bstree_node;
	class bstree_inorder_iterator;
	
private:
	linked_t*            m_root_ptr;
	usize__t             m_size;
	bst_node_allocator_t m_node_allocator;
public:
	const linked_t* const& root_linked_ref() const
	{
		return m_root_ptr;
	}
	const linked_t* root_linked() const
	{
		return m_root_ptr;
	}
	const node_pair_t* root() const
	{
		return (node_pair_t*)m_root_ptr;
	}
	usize__t size() const
	{
		return m_size;
	}

public:
	cbinary_search_tree(obj_allocate_t* PARAM_INOUT alloc_ptr = null) :
		m_size(0), m_root_ptr(null)
	{
		node_alloc_t::init_alloc(m_node_allocator, alloc_ptr);
	}

	cbinary_search_tree(const bstree_t& PARAM_IN other_tree)
	{
		if (&other_tree != this)
		{
			m_size = 0;
			m_root_ptr = null;
			m_node_allocator = other_tree.m_node_allocator;
			clone(other_tree);
		}
	}

	cbinary_search_tree(const bstree_t& PARAM_IN other_tree, 
		obj_allocate_t& PARAM_INOUT alloc)
	{
		if (&other_tree != this)
		{
			m_size = 0;
			m_root_ptr = null;
			node_alloc_t::init_alloc(m_node_allocator, alloc);
			clone(other_tree);
		}
	}

	virtual ~cbinary_search_tree()
	{
		_clear();
	}
protected:
	static SR_INLINE int __compare_two_node(const void* PARAM_OUT first,
		const void* PARAM_IN second)
	{
		const node_pair_t* first_pair_ptr  = (const node_pair_t*)first;
		const node_pair_t* second_pair_ptr = (const node_pair_t*)second;
		return cmp_t::compare(first_pair_ptr->m_key, second_pair_ptr->m_key);
	}
	static SR_INLINE int __compare_value_node(const void* PARAM_OUT first,
		const void* PARAM_IN second)
	{
		const key_t* first_value_ptr = (const key_t*)first;
		const node_pair_t* second_pair_ptr = (const node_pair_t*)second;
		return cmp_t::compare(*first_value_ptr, second_pair_ptr->m_key);
	}
	SR_INLINE void swap(bstree_t& PARAM_INOUT other)
	{
		linked_t*            tmp_root_ptr;
		usize__t             tmp_size;
		bst_node_allocator_t tmp_node_allocator;

		tmp_root_ptr = m_root_ptr;
		tmp_size = m_size;
		tmp_node_allocator = m_node_allocator;

		m_node_allocator = other.m_node_allocator;
		m_root_ptr = other.m_root_ptr;
		m_size = other.m_size;

		other.m_node_allocator = tmp_node_allocator;
		other.m_root_ptr = tmp_root_ptr;
		other.m_size = tmp_size;
	}
public:
	// 创建新的节点
	// 返回节点的值
	SR_INLINE bstree_node new_node()
	{
		node_pair_t* new_pair_ptr = (node_pair_t*)m_node_allocator->new_node(&m_node_allocator.m_alloc_inst, null);
		return bstree_node(null, new_pair_ptr, m_node_allocator);
	}
	SR_INLINE bstree_node new_node(const key_t& val)
	{
		node_pair_t* new_pair_ptr = (node_pair_t*)m_node_allocator->new_node(&m_node_allocator.m_alloc_inst, null);

		if (new_pair_ptr)
		{
			new_pair_ptr->m_key = val;
		}

		return bstree_node(null, new_pair_ptr, m_node_allocator);
	}
	// 释放节点
	SR_INLINE result_t release_node(bstree_node& PARAM_IN node)
	{
		result_t status = STATUS_OK;
		if ( (
			 (node.owner() == this) ||
			 (node.owner() == null && node.alloc() == m_node_allocator)
			 )
			&& node.valid())
		{
			status = m_node_allocator->release_node(&m_node_allocator.m_alloc_inst, node.m_pair_ptr);
			if (STATUS_OK == status)
			{
				node.reset(null, null, null);
			}
		}
		return status;
	}

	// 插入节点
	SR_INLINE bstree_node insert(bstree_node& PARAM_OUT node, result_t& PARAM_OUT insert_result)
	{
		if (!node.valid() ||
			(node.owner() != this && node.owner() != null) ||
			node.alloc() != this->m_node_allocator)
		{
			insert_result = STATUS_INVALID_PARAMS;
			return bstree_node(null, null, null);
		}

		linked_t* added_ptr = null;
		insert_result = tree_method_t::add(
			&m_root_ptr,
			(linked_t*)node.m_pair_ptr,
			__compare_two_node,
			&added_ptr);

		if (STATUS_OK == insert_result)
		{
			++m_size;
		}

		return bstree_node(this, added_ptr, m_node_allocator);
	}
	// 移除节点
	SR_INLINE result_t remove(bstree_node& PARAM_INOUT node, bool is_release = true)
	{
		result_t status;
		
		if (node.valid())
		{
			status = STATUS_NULLITEM;
			return status;
		}

		if (node.owner() != this ||
			node.alloc() != this->m_node_allocator)
		{
			status = STATUS_INVALID_PARAMS;
			return status;
		}


		status = tree_method_t::remove(
			&m_root_ptr,
			(linked_t*)node.m_pair_ptr);
		
		if (STATUS_OK == status)
		{
			if (m_size > 0)
			{
				--m_size;
			}

			if (is_release)
			{
				release_node(node);
			}
		}

		return status;
	}
	// 清除整棵树
	SR_INLINE result_t _clear()
	{
		result_t status;
		if (node_alloc_t::can_reset(m_node_allocator))
		{
			status = node_alloc_t::reset(m_node_allocator);

			if (STATUS_OK == status || STATUS_MEM_ERR == status)
			{
				m_root_ptr = null;
				m_size = 0;
			}
		}
		else
		{
			status = tree_method_t::clear(m_node_allocator, &m_root_ptr);
			if (STATUS_OK == status || STATUS_MEM_ERR == status)
			{
				m_root_ptr = null;
				m_size = 0;
			}
		}
		return status;
	}
	SR_INLINE void clear()
	{
		bstree_t clr_tree;
		swap(clr_tree);
		this->m_node_allocator = clr_tree.m_node_allocator;
	}
	// 克隆一棵树
	SR_INLINE result_t clone(const bstree_t& PARAM_IN other, bool is_try = true)
	{
		result_t status;
		if (&other == this)
		{
			return STATUS_OK;
		}
		if (!is_try)
		{
			status = _clear();
			if (STATUS_OK != status)
			{
				return status;
			}
		}
		linked_t* try_clone_ptr = m_root_ptr;

		status = bst_clone(&m_node_allocator,
			&try_clone_ptr,
			other.m_root_ptr);

		if (STATUS_OK == status)
		{
			if (is_try)
			{
				clear();
			}
			m_root_ptr = try_clone_ptr;
			m_size = other.m_size;
		}

		return status;
	}

	// 查找结点
	SR_INLINE bstree_node find(const key_t& PARAM_IN val)
	{
		const linked_t* find_linked_ptr = 
			tree_method_t::find(m_root_ptr, &val, __compare_value_node);
		return bstree_node(this, find_linked_ptr, m_node_allocator);
	}
	SR_INLINE const_bstree_node find(const key_t& PARAM_IN val) const
	{
		const linked_t* find_linked_ptr =
			tree_method_t::find(m_root_ptr, &val, __compare_value_node);
		return const_bstree_node(this, find_linked_ptr, m_node_allocator);
	}
	
	// 查找最后一个相近节点
	SR_INLINE bstree_node find_near(const key_t& PARAM_IN val, int& PARAM_OUT last_cmp_result)
	{
		const linked_t* find_linked_ptr =
			tree_method_t::find_near(m_root_ptr, &val, __compare_value_node, last_cmp_result);
		return bstree_node(this, find_linked_ptr, m_node_allocator);
	}
	SR_INLINE const_bstree_node find_near(const key_t& PARAM_IN val, int& PARAM_OUT last_cmp_result) const
	{
		const linked_t* find_linked_ptr =
			tree_method_t::find_near(m_root_ptr, &val, __compare_value_node, last_cmp_result);
		return const_bstree_node(this, find_linked_ptr, m_node_allocator);
	}
	//
	SR_INLINE bstree_inorder_iterator* find(const key_t& PARAM_IN val, bstree_inorder_iterator& PARAM_OUT itr)
	{
		const linked_t* find_linked_ptr =
			tree_method_t::find(m_root_ptr, &val, __compare_value_node);
		
		itr.init(m_root_ptr, find_linked_ptr);
		return &itr;
	}
	SR_INLINE bstree_inorder_iterator* find_near(const key_t& PARAM_IN val, 
		bstree_inorder_iterator& PARAM_OUT itr, int& PARAM_OUT last_cmp_result)
	{
		const linked_t* find_linked_ptr =
			tree_method_t::find_near(m_root_ptr, &val, __compare_value_node, last_cmp_result);

		itr.init(m_root_ptr, find_linked_ptr);
		return &itr;
	}
	SR_INLINE bst_inorder_iterator_t* upper_bound(const key_t& PARAM_IN val, bstree_inorder_iterator& PARAM_OUT itr)
	{
		int last_cmp_result;
		bstree_inorder_iterator* itr_ptr;
		itr_ptr = find_near(val, itr, last_cmp_result);
		if (last_cmp_result > 0)
		{
			itr_ptr = itr.increase();
			while (itr_ptr)
			{
				int cmp_res = __compare_value_node(&val, itr_ptr->m_iter.itr.m_this_node_ptr);
				if (cmp_res <= 0)
				{
					break;
				}
			}
		}
		return itr_ptr;
	}
	SR_INLINE bst_inorder_iterator_t* lower_bound(const key_t& PARAM_IN val, bstree_inorder_iterator& PARAM_OUT itr)
	{
		int last_cmp_result;
		bstree_inorder_iterator* itr_ptr;
		itr_ptr = find_near(val, itr, last_cmp_result);
		if (last_cmp_result < 0)
		{
			itr_ptr = itr.increase();
			while (itr_ptr)
			{
				int cmp_res = __compare_value_node(&val, itr_ptr->m_iter.itr.m_this_node_ptr);
				if (cmp_res >= 0)
				{
					break;
				}
			}
		}
		return itr_ptr;
	}


	SR_INLINE bstree_inorder_iterator* begin(bstree_inorder_iterator& PARAM_OUT itr) const
	{
		 itr = bstree_inorder_iterator(m_root_ptr, m_root_ptr);
		 return itr.begin();
	}
	SR_INLINE bstree_inorder_iterator* end(bstree_inorder_iterator& PARAM_OUT itr) const
	{
		itr = bstree_inorder_iterator(m_root_ptr, m_root_ptr);
		return itr.end();
	}
	
	SR_INLINE bstree_node at(bstree_inorder_iterator& PARAM_IN itr)
	{
		if (itr.ref().itr.m_tree_root_ref == &m_root_ptr)
		{
			return bstree_node(this, (node_pair_t*)itr.ref().itr.m_this_node_ptr, &m_node_allocator);
		}
		else
		{
			return bstree_node(null, null, null);
		}
	}
	
	SR_INLINE result_t remove(bstree_inorder_iterator& PARAM_IN itr, 
		REMOVE_ITERATOR_NEXT_OPERATE_t increase_next = SET_ITR_TRY_NOTNULL,
		bool is_release = true)
	{
		if (itr.ref().itr.m_tree_root_ref != &m_root_ptr)
		{
			return STATUS_INVALID_PARAMS;
		}
		
		linked_t* remove_node_ptr = (linked_t*)itr.m_iter.itr.m_this_node_ptr;
		if (null == remove_node_ptr)
		{
			return STATUS_NULLITEM;
		}
		
		// 选取迭代器在删除元素后的动作处理
		bstree_inorder_iterator* next_itr;
		switch (increase_next)
		{
		case SET_ITR_TRY_NOTNULL: // 在前后选取一个非空的索引值
			next_itr = itr.increase();
			if (null == next_itr)
			{
				next_itr = itr.decrease();
			}
			if (null == next_itr)
			{
				itr.init(m_root_ptr, null);
			}
			break;
		case SET_ITR_INCREASE: // 设置后面的一个索引值
			next_itr = itr.increase();
			if (null == next_itr)
			{
				itr.init(m_root_ptr, null);
			}
			break;
		case SET_ITR_DECREASE: // 设置前面的一个索引值
			next_itr = itr.decrease();
			if (null == next_itr)
			{
				itr.init(m_root_ptr, null);
			}
			break;
		case  SET_ITR_NOTHING:// 不设置
		default:
			itr.init(m_root_ptr, null);
			break;
		}

		status = tree_method_t::remove(
			&m_root_ptr,
			remove_node_ptr);

		if (STATUS_OK == status)
		{
			if (m_size > 0)
			{
				--m_size;
			}

			// 释放节点
			if (is_release)
			{
				m_node_allocator->release_node(&m_node_allocator.m_alloc_inst, 
					remove_node_ptr);
			}
		}

		return status;

	}
 

	// nest class
	class const_bstree_node
	{
		friend class cbinary_search_tree< tree_method_t, key_t, cmp_t, node_alloc_t >;
	public:
		typedef node_pair_t            pair_type_t;
		typedef bst_node_allocator_t   alloc_type_t;
		typedef bstree_t               tree_type;
	private:
		const node_pair_t*          m_pair_ptr;
		const bst_node_allocator_t* m_allocate_ptr;
		const bstree_t*             m_owner;
	public:
		const_bstree_node() :m_owner(null), m_allocate_ptr(null), m_allocate_ptr(null)
		{
			;
		}
	protected:
		const_bstree_node(
			const bstree_t* PARAM_IN owner,
			const node_pair_t* PARAM_INOUT pair_ptr,
			const bst_node_allocator_t* PARAM_IN allocate_ptr) :
			m_owner(owner),
			m_pair_ptr(pair_ptr),
			m_allocate_ptr(allocate_ptr)
		{
			;
		}
	protected:
		SR_INLINE void reset(const bstree_t* PARAM_IN owner,
			const node_pair_t* PARAM_INOUT pair_ptr,
			const bst_node_allocator_t* PARAM_IN allocate_ptr)
		{
			m_owner = owner;
			m_pair_ptr = pair_ptr;
			m_allocate_ptr = allocate_ptr;
		}
		SR_INLINE const bst_node_allocator_t* alloc() const
		{
			return m_allocate_ptr;
		}
	public:
		SR_INLINE const linked_t* link() const
		{
			if (m_pair_ptr)
			{
				return m_pair_ptr->m_linked;
			}
			else
			{
				return null;
			}

		}
		SR_INLINE const key_t*  value() const
		{
			if (m_pair_ptr)
			{
				return m_pair_ptr->m_key;
			}
			else
			{
				return null;
			}
		}
		SR_INLINE bool valid() const
		{
			return (bool)(m_pair_ptr);
		}
		SR_INLINE const bstree_t* owner() const
		{
			return m_owner;
		}

		SR_INLINE bool equal(const bstree_node& other) const
		{
			return (this->link() == other->link());
		}

		SR_INLINE bool equal(const const_bstree_node& other) const
		{
			return (this->link() == other->link());
		}
	};

	class bstree_node
	{
		friend class cbinary_search_tree< tree_method_t, key_t, cmp_t, node_alloc_t >;
	public:
		typedef node_pair_t            pair_type_t;
		typedef bst_node_allocator_t   alloc_type_t;
		typedef bstree_t               tree_type;
	private:
		node_pair_t*          m_pair_ptr;
		bst_node_allocator_t* m_allocate_ptr;
		bstree_t*             m_owner;
	public:
		bstree_node() :m_owner(null), m_allocate_ptr(null), m_allocate_ptr(null)
		{
			;
		}
	protected:
		bstree_node(
			bstree_t* PARAM_IN owner,
			node_pair_t* PARAM_INOUT pair_ptr,
			bst_node_allocator_t* PARAM_IN allocate_ptr) :
			m_owner(owner),
			m_pair_ptr(pair_ptr),
			m_allocate_ptr(allocate_ptr)
		{
			;
		}
	protected:
		SR_INLINE void reset(bstree_t* PARAM_IN owner,
			node_pair_t* PARAM_INOUT pair_ptr,
			bst_node_allocator_t* PARAM_IN allocate_ptr)
		{
			m_owner = owner;
			m_pair_ptr = pair_ptr;
			m_allocate_ptr = allocate_ptr;
		}
		SR_INLINE linked_t* ref_link()
		{
			if (m_pair_ptr)
			{
				return m_pair_ptr->m_linked;
			}
			else
			{
				return null;
			}

		}
		SR_INLINE key_t* ref_value()
		{
			if (m_pair_ptr)
			{
				return m_pair_ptr->m_key;
			}
			else
			{
				return null;
			}
		}
		SR_INLINE const bst_node_allocator_t* alloc() const
		{
			return m_allocate_ptr;
		}
	public:
		SR_INLINE const linked_t* link() const
		{
			if (m_pair_ptr)
			{
				return m_pair_ptr->m_linked;
			}
			else
			{
				return null;
			}

		}
		SR_INLINE const key_t*  value() const
		{
			if (m_pair_ptr)
			{
				return m_pair_ptr->m_key;
			}
			else
			{
				return null;
			}
		}
		SR_INLINE bool valid() const
		{
			return (bool)(m_pair_ptr);
		}
		SR_INLINE const bstree_t* owner() const
		{
			return m_owner;
		}

		SR_INLINE bool equal(const bstree_node& other) const
		{
			return (this->link() == other->link());
		}

		SR_INLINE bool equal(const const_bstree_node& other) const
		{
			return (this->link() == other->link());
		}
	};

	// 
	class bstree_inorder_iterator
	{
		friend class cbinary_search_tree< tree_method_t, key_t, cmp_t, node_alloc_t >;
	public:
		typedef tree_method_t::inorder_method_t   iterator_method_t;
		typedef iterator_method_t::link_t         link_t;
		typedef bstree_inorder_iterator           bstree_inorder_t;
	private:
		bst_inorder_iterator_t m_iter;
	public:
		const bst_inorder_iterator_t& ref() const
		{
			return m_iter;
		}
		bool valid() const
		{
			return (m_iter.const_itr.m_this_node_ptr && m_iter.const_itr.m_this_node_ptr);
		}
	protected:
		bstree_inorder_iterator(const link_t* const& PARAM_IN root_ptr,
			const link_t* PARAM_IN cur_ptr)
		{
			iterator_method_t::init(m_iter, root_ptr, cur_ptr);
		}

		result_t init(const link_t* const& PARAM_IN root_ptr,
			const link_t* PARAM_IN cur_ptr)
		{
			return iterator_method_t::init(m_iter, root_ptr, cur_ptr);
		}

	public:
		bstree_inorder_iterator()
		{
			iterator_method_t::init(m_iter, null, null);
		}


		SR_INLINE bstree_inorder_t* begin()
		{
			bst_inorder_iterator_t* itr_ptr = iterator_method_t::begin(&m_iter);
			if (null == itr_ptr)
			{
				return null;
			}
			else
			{
				return this;
			}
		}

		SR_INLINE bstree_inorder_t* end()
		{
			bst_inorder_iterator_t* itr_ptr = iterator_method_t::end(&m_iter);
			if (null == itr_ptr)
			{
				return null;
			}
			else
			{
				return this;
			}
		}

		SR_INLINE bstree_inorder_t* increase()
		{
			bst_inorder_iterator_t* itr_ptr = iterator_method_t::increase(&m_iter);
			if (null == itr_ptr)
			{
				return null;
			}
			else
			{
				return this;
			}
		}

		SR_INLINE bstree_inorder_t* decrease()
		{
			bst_inorder_iterator_t* itr_ptr = iterator_method_t::decrease(&m_iter);
			if (null == itr_ptr)
			{
				return null;
			}
			else
			{
				return this;
			}
		}

		SR_INLINE const bstree_inorder_t* invalid_iterator() const
		{
			return null;
		}

	};
};


#endif	 //CPP_SUNRED_BST_H_
