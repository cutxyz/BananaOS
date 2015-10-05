#include <string>
#include <fstream>


#define SR_GET_EXTERN_FUC
#include "../clib_sunred/include/data/sr_data.h"
#include "../clib_sunred/data/avlbst_node.h"

#include "../clib_sunred/include/clib_sunred.h"


#define bst_init                bstnode_init
#define avlbst_add         bst_avltree_add_node
#define avlbst_remove      bst_avltree_remove
//#define bst_clone           lib.m_call->bst_clone
//#define bst_clear            lib.m_call->bst_clear
//#define bst_find_const lib.m_call->bst_find_const
//#define get_inorder_iterator_method() (lib.m_call->bst_inorder_iterator_method)
//#define get_posorder_iterator_method() (lib.m_call->bst_posorder_iterator_method)
//#define get_preorder_iterator_method() (lib.m_call->bst_preorder_iterator_method)

using namespace std;
struct avl_str_node
{
	avlbst_node m_node;
	string      m_string;
};

void avl_str_node_printf(const avl_str_node* PARAM_IN node_ptr)
{
	if (node_ptr)
	{
		printf("node str = %s\n", node_ptr->m_string.c_str());
	}
	else
	{
		printf("node is null\n");
	}
	
}

int compare_two_avlnode(const void* PARAM_OUT first,
	const void* PARAM_IN second)
{
	if (null == first || null == second)
	{
		if (null == first)
		{
			printf("cmp first node is null\n");
		}

		if (null == second)
		{
			printf("cmp second node is null\n");
		}

		return ((int)first - (int)second);
	}
	string& str1 = ((avl_str_node*)first)->m_string;
	string& str2 = ((avl_str_node*)second)->m_string;

	int cmp_rs = strcmp(str1.c_str(), str2.c_str());
	return cmp_rs;

}

void* new_a_simple_avlbst_node(object_allocator_t* PARAM_INOUT ins_ptr,
	const void* PARAM_IN copy_ptr)
{
	return new avl_str_node;
}

result_t release_a_simple_avlbst_node(object_allocator_t* PARAM_INOUT ins_ptr,
	void* PARAM_INOUT del_ptr)
{
	if (del_ptr)
	{
		delete (avl_str_node*)del_ptr;
	}

	return STATUS_OK;
}

void avl_bst_node_alloc_init(bst_node_allocator_t* PARAM_INOUT alloc)
{
	if (null == alloc)
	{
		printf("%s param error\n", __FUNCTION__);
	}
	memset(alloc, 0, sizeof(bst_node_allocator_t));
	alloc->new_node     = new_a_simple_avlbst_node;
	alloc->release_node = release_a_simple_avlbst_node;
}

void avl_bst_init(bstree_header_t* tree_ptr)
{
	if (null == tree_ptr)
	{
		printf("%s param error\n", __FUNCTION__);
	}
	memset(tree_ptr, 0, sizeof(bstree_header_t));

	tree_ptr->m_cmp  = compare_two_avlnode;
	tree_ptr->add    = avlbst_add;
	tree_ptr->remove = avlbst_remove;
	tree_ptr->clean  = bst_clear;
	tree_ptr->clone  = bst_clone;
	tree_ptr->itr    = get_inorder_iterator_method();

	avl_bst_node_alloc_init(&tree_ptr->m_alloc);
}

void avl_bst_load(bstree_header_t* tree_ptr, const char* strfilepath)
{
	if (null == tree_ptr || null == strfilepath)
	{
		printf("param error!\n");
		return;
	}
	clean_bsttree_node(tree_ptr);

	fstream fin;
	fin.open(strfilepath);
	if (fin.good())
	{
		while (!fin.eof())
		{
			avl_str_node* node_ptr = (avl_str_node*)new_bsttree_node(tree_ptr, null);
			if (null == node_ptr)
			{
				printf("mem alloc error!\n");
				break;
			}
			fin >> node_ptr->m_string;
			bst_node_ptr bstnode_ptr = bst_init((bst_node_ptr)&node_ptr->m_node, null, null, null);
			avl_str_node* added_node_ptr = null;

			if ("enable" == node_ptr->m_string)
			{
				int a = 0;
			}
			result_t status = add_bsttree_node(tree_ptr, bstnode_ptr, (bst_node_ptr*)&bstnode_ptr);

			if (STATUS_OK != status)
			{
				if (STATUS_UNIQUE == status)
				{
					printf("add same value node!(str=%s)\n", node_ptr->m_string.c_str());
				}
				else
				{
					printf("add str=%s error\n", node_ptr->m_string.c_str());
					break;
				}
			}
		}
	}
}

const avl_str_node* avl_bst_search(const bstree_header_t* tree_ptr, string str)
{
	if (null == tree_ptr)
	{
		return null;
	}
	avl_str_node key_node;
	key_node.m_string = str;
	bst_init((bst_node_ptr)&key_node.m_node, null, null, null);

	const bst_node_ptr node_ptr = bst_find_const
		(tree_ptr->m_root_node_ptr, 
		 (bst_node_ptr)&key_node,
		 tree_ptr->m_cmp);

	return (const avl_str_node*)node_ptr;
}

void inorder_traval(const bstree_header_t* tree_ptr)
{
	printf("\n\n%s begin\n\n", __FUNCTION__);
	const iterator_method_t* itr_method_ptr = get_inorder_iterator_method();
	bst_inorder_iterator_t itr;
	bst_inorder_iterator_t* itr_ptr = (bst_inorder_iterator_t*)itr_method_ptr->init(&itr, (avlbst_node**)&(tree_ptr->m_root_node_ptr));
	int icount = 0;
	if (itr_ptr)
	{
		itr_ptr = (bst_inorder_iterator_t*)
			itr_method_ptr->begin(&itr);

		while (itr_ptr)
		{
			avl_str_node_printf((const avl_str_node*)itr_ptr->const_itr.m_this_node_ptr);
			itr_ptr = (bst_inorder_iterator_t*)itr_method_ptr->increase(itr_ptr);
			++icount;
		}
	}
	else
	{
		printf("empty tree!\n");
	}
	printf("\n%d\n", icount);

	printf("\n\n%s end\n\n", __FUNCTION__);
}

void preorder_traval(const bstree_header_t* tree_ptr)
{
	printf("\n\n%s begin\n\n", __FUNCTION__);
	const iterator_method_t* itr_method_ptr = get_preorder_iterator_method();
	bst_preorder_iterator_t itr;
	bst_preorder_iterator_t* itr_ptr = (bst_preorder_iterator_t*)itr_method_ptr->init(&itr, tree_ptr->m_root_node_ptr);
	
	if (itr_ptr)
	{
		itr_ptr = (bst_preorder_iterator_t*)
			itr_method_ptr->begin(&itr);

		while (itr_ptr)
		{
			avl_str_node_printf((const avl_str_node*)itr_ptr->const_itr.m_this_node_ptr);
			itr_ptr = (bst_preorder_iterator_t*)itr_method_ptr->increase(itr_ptr);
		}
	}
	else
	{
		printf("empty tree!\n");
	}


	printf("\n\n%s end\n\n", __FUNCTION__);
}

void posorder_traval(const bstree_header_t* tree_ptr)
{
	printf("\n\n%s begin\n\n", __FUNCTION__);
	const iterator_method_t* itr_method_ptr = get_posorder_iterator_method();
	bst_posorder_iterator_t itr;
	bst_posorder_iterator_t* itr_ptr = (bst_posorder_iterator_t*)itr_method_ptr->init(&itr, tree_ptr->m_root_node_ptr);

	if (itr_ptr)
	{
		itr_ptr = (bst_posorder_iterator_t*)
			itr_method_ptr->begin(&itr);

		while (itr_ptr)
		{
			avl_str_node_printf((const avl_str_node*)itr_ptr->const_itr.m_this_node_ptr);
			itr_ptr = (bst_posorder_iterator_t*)itr_method_ptr->increase(itr_ptr);
		}
	}
	else
	{
		printf("empty tree!\n");
	}


	printf("\n\n%s end\n\n", __FUNCTION__);
}


void avl_bst_test()
{
	bstree_header_t bstree;
	avl_bst_init(&bstree);
	avl_bst_load(&bstree, "bst_data1.txt");


	inorder_traval(&bstree);

	string str = "ad";
	const avl_str_node* str_node_ptr =
		avl_bst_search(&bstree, str);

	avl_str_node_printf(str_node_ptr);
}
