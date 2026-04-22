
#ifndef std
#define std

typedef short unsigned int u16;  
typedef long unsigned int u32; 
typedef long long unsigned int u64;  
typedef short signed int s16;  
typedef long signed int s32; 
typedef long long signed int s64; 
typedef signed char s8; 
typedef unsigned char u8;  
typedef float f32;
typedef double d64; 
typedef long double d128;

typedef enum{ LOW=(0u) , HIGH=(1u) } LOGICAL_VALUE;
typedef enum{ F=(0u) , T=(1u) } Bool_t;


#define NULL_PTR ((void*)0)

#endif
