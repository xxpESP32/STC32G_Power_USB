#ifndef __SYSTEM_H
#define __SYSTEM_H
#include <STC32G.H>


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
//typedef unsigned long u64;

#define NMOS P16
#define Sysclk  35000000L
void GPIO_Init(void);
void Delay_ms(u32 x);
#endif
