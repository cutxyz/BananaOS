//////////////////////////////////////
// inorder_bst_iterator_template.h
// Created on: 2015-5-9
// Author: 李镇城  （ cut / cutxyz） 
// e-mail: cut-12345@hotmail.com / 501931049@qq.com
/////////////////////////////////////
// 二叉树中序遍历规则的迭代器

#ifndef BST_INORDER_ITEARATOR_
#define BST_INORDER_ITEARATOR_

typedef struct st_bst_inorder_iterator
{
	void*  m_tree_root_ref;
	void*  m_this_node_ptr;
}st_bst_inorder_iterator_t;

typedef struct st_const_bst_inorder_iterator
{
	const void*  m_tree_root_ref;
	const void*  m_this_node_ptr;
}st_bst_const_inorder_iterator_t;

typedef union un_bst_inorder_iterator
{
	st_bst_inorder_iterator_t         itr;
	st_bst_const_inorder_iterator_t	  const_itr;
}bst_inorder_iterator_t;

#endif //BST_INORDER_ITEARATOR_


// 二叉树后序遍历规则的迭代器
#ifndef BST_POSORDER_ITEARATOR_
#define BST_POSORDER_ITEARATOR_

typedef struct st_bst_posorder_iterator
{
	void*  m_tree_root_ref;
	void*  m_this_node_ptr;
}st_bst_posorder_iterator_t;

typedef struct st_const_bst_posorder_iterator
{
	const void*  m_tree_root_ref;
	const void*  m_this_node_ptr;
}st_bst_const_posorder_iterator_t;

typedef union un_bst_posorder_iterator
{
	st_bst_posorder_iterator_t         itr;
	st_bst_const_posorder_iterator_t   const_itr;
}bst_posorder_iterator_t;

#endif //BST_POSORDER_ITEARATOR_

// 二叉树前序遍历规则的迭代器
#ifndef BST_PREORDER_ITEARATOR_
#define BST_PREORDER_ITEARATOR_	 	

typedef enum enum_PREODER_ITERATOR_NEXT_FLAG
{
	PREORDER_NEXT_SUB_ROOT_RIGHT = 0,
	PREORDER_NEXT_SUB_ROOT_LEFT,
	PREORDER_NEXT_LEFT,
	PREORDER_NEXT_RIGHT,
	PREORDER_NEXT_BEGIN,
	PREORDER_NEXT_END,
	PREORDER_FIN,

	PREODER_ITERATOR_NEXT_FLAG_COUNT
}PREODER_ITERATOR_NEXT_FLAG_t;

typedef struct st_bst_preorder_iterator
{
	void*  m_tree_root_ref;
	void*  m_this_node_ptr;

	PREODER_ITERATOR_NEXT_FLAG_t m_next_step;
	result_t m_last_result;
}st_bst_preorder_iterator_t;

typedef struct st_const_bst_preorder_iterator
{
	const void* m_tree_root_ref;
	const void* m_this_node_ptr;

	PREODER_ITERATOR_NEXT_FLAG_t m_next_node_type;
	result_t m_last_result;
}st_bst_const_preorder_iterator_t;

typedef union un_bst_preorder_iterator
{
	st_bst_preorder_iterator_t         itr;
	st_bst_const_preorder_iterator_t   const_itr;
}bst_preorder_iterator_t;

#endif //BST_PREORDER_ITEARATOR_

#ifndef get_bst_itr_this_traits
#define get_bst_itr_this_traits(NODE_PTR_TYPE,ITR)        ((NODE_PTR_TYPE)((ITR).m_this_node_ptr))
#endif//get_bst_itr_this_traits

#ifndef get_bst_itr_root_ref_traits
#define get_bst_itr_root_ref_traits(NODE_PTR_TYPE,ITR)    ((NODE_PTR_TYPE*)((ITR).m_tree_root_ref))
#endif//get_bst_itr_root_ref_traits

#ifndef get_bst_itrptr_this_traits
#define get_bst_itrptr_this_traits(NODE_PTR_TYPE,ITR)     ((NODE_PTR_TYPE)((ITR)->m_this_node_ptr))
#endif//get_bst_itrptr_this_traits

#ifndef get_bst_itrptr_root_traits
#define get_bst_itrptr_root_traits(NODE_PTR_TYPE,ITR)     ((NODE_PTR_TYPE*)((ITR)->m_tree_root_ref))
#endif//get_bst_itrptr_root_traits









