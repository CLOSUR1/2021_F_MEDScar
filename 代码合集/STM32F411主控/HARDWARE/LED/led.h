#ifndef __LED_H
#define __LED_H
#include "sys.h"

//#define GLED PCout(15)	
//#define RLED PCout(14)	 
#define GLED PBout(12)	
#define RLED PBout(13)	

#define LED PCout(13)
#define BEEP PBout(13)
#define YLED(n) {GLED=n;RLED=n;}

void RGBLED_Init(void);		 
void LED_Init(void);	
void BEEP_Init(void);

#endif
