#include "hehetry.h"
#include "definetest.h"

// 搜索二叉树节点实体初始化
#define BST_NODE_INSTANCE_INIT_FUNC_NAME(node_type)	instance_init##node_type
#define BST_NODE_INSTANCE_INIT_FUNC(node_type) \
	typedef _##node_type##ptr(*BST_NODE_INSTANCE_INIT_FUNC_NAME(node_type))(_##node_type##ptr dst);

// 搜索二叉树节点深拷贝
#define BST_NODE_DEEPCOPY_FUNC_NAME(node_type)	deepcopy##node_type
#define BST_NODE_DEEPCOPY_FUNC(node_type) \
	typedef _##node_type##ptr (*BST_NODE_DEEPCOPY_FUNC_NAME(node_type))(_##node_type##ptr dst, \
	const##node_type##ptr  src);

// 搜索二叉树结点比较
#define BST_NODE_CMP_FUNC_NAME(node_type) cmp##node_type
#define BST_NODE_CMP_FUNC(node_type) \
	typedef int(*BST_NODE_CMP_FUNC_NAME(node_type))( const##node_type##ptr  first, \
	const##node_type##ptr  second);

#define MYINT int 
#define constintptr const int*
#define _intptr int*

int __cmpint(const int *  first,
	const int *  second)
{
	printf("%08X %08X\n", first, second);
	return 0;
}
int* __copyint(int *  first,
	const int *  second)
{
	printf("%08X %08X\n", first, second);
	return 0;
}
int* __initint(int *  first)
{
	printf("%08X\n", first);
	return 0;
}

BST_NODE_CMP_FUNC(int)
BST_NODE_DEEPCOPY_FUNC(int)
BST_NODE_INSTANCE_INIT_FUNC(int)


//#ifdef _DEBUG
//#pragma comment(lib, "../sln/Debug/clib_sunred.lib")
//
//#else
//#pragma comment(lib, "../sln/Release/clib_sunred.lib")
//#endif


//BST_NODE_CMP_FUNC(MYINT)
extern void load_dll();
extern void fifo_test();
//extern void block_test();
extern void quick_sort_test();
extern void sort_fifo_test();
int main()
{
	load_dll();
	//BST_NODE_CMP_FUNC_NAME(int) funcA = __cmpint;
	//BST_NODE_DEEPCOPY_FUNC_NAME(int) funcB = __copyint;
	//BST_NODE_INSTANCE_INIT_FUNC_NAME(int) funcC = __initint;
	//funcA(1, 2);
	//funcB(3, 4);
	//funcC(5);
	//printheheB();
	//printheheA();



	//st_aaa_t aa;
	//aa.a = 10;
	//DEFINE_DEFINENAME_1PART(hehe_aaa)(&aa);
	//DEFINE_DEFINENAME_2PART(hehe_aaa, aaa_type)(&aa);

	sort_fifo_test();
	fifo_test();
	//block_test();
	quick_sort_test();
	return 0;
}