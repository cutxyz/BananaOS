#ifndef SUNRED_DEFUALT_COMPILE32BIT_TYPE_H_
#define SUNRED_DEFUALT_COMPILE32BIT_TYPE_H_

typedef unsigned long  ptr_t;
typedef unsigned long  reg_t;
typedef signed long    sreg_t;
typedef volatile void* REG_t;

#define ADDRESS_2_VOID_PTR(ADDR) ((void*)(ADDR))
#define ADDRESS_2_POINTER(ADDR) ((REG_t)(ADDR))
#define POINTER_2_ADDRESS(ADDR_PTR) ((reg_t)(ADDR_PTR))


#endif	 //SUNRED_DEFUALT_COMPILE32BIT_TYPE_H_
