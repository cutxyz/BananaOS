#ifndef TRY_TEST_H_
#define TRY_TEST_H_

#include <stdio.h>
#define hehe(...) printf(__VA_ARGS__)
__forceinline void printA()
{
	hehe("12345\n");
}
__forceinline void printB()
{
	hehe("ABCDE\n");
}
#endif //TRY_TEST_H_

