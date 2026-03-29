#pragma once
/*
  dt:-----------------------------
  Default: All API: Types & Macros
  dt:-------------------------
*/

/*
  te:---------------------
  vTypes: Signed Integers
  te:-----------------
*/

//type: Signed 8-Bits
typedef signed char i8;

//type: Signed 16-Bits
typedef signed short i16;

//type: Signed 32-Bits
typedef signed int i32;

//type: Signed 64-Bits
typedef signed long long int i64;


//type: Signed 8-Bits Pointer
typedef signed char *i8_pointer;

//type: Signed 16-Bits Pointer
typedef signed short *i16_pointer;

//type: Signed 32-Bits Pointer
typedef signed int *i32_pointer;

//type: Signed 64-Bits Pointer
typedef signed long long int *i64_pointer;



/*
  te:----------------------
  vTypes: Unsigned Integers
  te:------------------
*/

//type: Unsigned 8-Bits
typedef unsigned char u8;

//type: Unsigned 16-Bits
typedef unsigned short u16;

//type: Unsigned 32-Bits
typedef unsigned int u32;

//type: Unsigned 64-Bits
typedef unsigned long long int u64;


//type: Unsigned 8-Bits Pointer
typedef unsigned char *u8_pointer;

//type: Unsigned 16-Bits Pointer
typedef unsigned short *u16_pointer;

//type: Unsigned 32-Bits Pointer
typedef unsigned int *u32_pointer;

//type: Unsigned 64-Bits Pointer
typedef unsigned long long int *u64_pointer;



/*
  te:-----------
  vTypes: Floats
  te:-------
*/

//type: Unsigned 32-Bits
typedef float f32;

//type: Unsigned 64-Bits
typedef double f64;


//type: 32-Bits Float Pointer
typedef float *f32_pointer;

//type: 64-Bits Double Pointer
typedef double *f64_pointer;

/*
  ea:----------------
  vTypes: Other Types
  Extra: Bool
  ea:------------
*/

typedef signed char chr;
typedef signed char *chr_pointer;


typedef void vd;
typedef void non_return;
typedef void *generic_pointer;

#ifndef __bool_true_false_are_defined

typedef enum : u8 {
  false = 0,
  true = 1
} bool;

#endif