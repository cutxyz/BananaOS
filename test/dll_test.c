#undef STATIC_LIB_OR_SHADOW_DLL_IMPORT
#include "clib_sunred.h"
int load_sunred_clib(const char* strPath, int param);
void load_dll()
{
	load_sunred_clib("clib_sunred.dll", 0);
}

