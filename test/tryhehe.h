#include "trytest.h"
#ifdef B_hehe_config
#define heheprint printB
#else
#define heheprint printA
#endif

#ifndef __printhehe__def
#define __printhehe__def
static __inline void  printhehe()
{
	heheprint();
}
#endif