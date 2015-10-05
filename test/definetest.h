#include "../sunredos/include/type.h"
#include <stdio.h>

#ifndef define_name
#define define_name DEFINE_DEFINENAME_1PART(hehe123)
#endif

#if define_name == DEFINE_DEFINENAME_1PART(hehe123)
//#error ("hhehehe");
#endif



typedef struct st_aaa
{
	int a;
}st_aaa_t;
#define aaa_type st_aaa_t
#define aaa_ptr st_aaa_t*
#define bbb_ptr aaa_ptr

static SR_FORCE_INLINE void DEFINE_DEFINENAME_1PART(hehe_aaa)(bbb_ptr a)
{
	printf("%s: %s=%d\n", __FUNCTION__, SR_STR(aaa_type), a->a);
}

static SR_FORCE_INLINE void DEFINE_DEFINENAME_2PART(hehe_aaa, aaa_type)(bbb_ptr a)
{
	printf("%s: %s=%d\n", __FUNCTION__, SR_STR(aaa_type), a->a);
}

//#ifdef DEFINE_DEFINENAME_3PART(111,hehe_aaa, aaa_type)
//#error ("DEFINE_DEFINENAME_3PART(111,hehe_aaa, aaa_type)");
//#endif


