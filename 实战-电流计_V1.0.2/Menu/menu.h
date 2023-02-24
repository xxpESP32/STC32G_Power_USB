#ifndef __menu_H
#define __menu_H
#include <STC32G.H>
#include "lcd_init.h"
#include "lcd.h"
#include "system.h"


typedef struct { 
	u8 index;
	u8 next;
	u8 enter;
	u8 back;
	void (*current_operation)(void);	
}Menu_Creat;
extern Menu_Creat M_G[25];
extern u8 index_cp;
extern void (*current_operation_func)(void);
void Menu_Loop(void);
#endif