#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "delay.h"

#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

void LED_shan(void);
void LED_Init(void);//≥ı ºªØ
void LED_shan1(u8 led);
			    
#endif
