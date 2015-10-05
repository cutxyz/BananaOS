//#ifdef _DEBUG
//#pragma comment(lib, "../sln/Debug/clib_sunred.lib")
//#else
//#pragma comment(lib, "../sln/Relese/clib_sunred.lib")
//#endif
#include "clib_sunred.h"
extern void avl_bst_test();
int main()
{
	load_sunred_clib("clib_sunred.dll", 0);
	avl_bst_test();
	release_sunred_clib();
	return 0;
}