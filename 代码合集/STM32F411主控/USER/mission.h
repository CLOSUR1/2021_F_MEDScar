#ifndef __MISSION_H
#define __MISSION_H
#include "sys.h"


extern int STEP;
extern int target_step;

void host(void);
void slave(void);
int END(void);

void OS(void);
extern int MODE;

void map2(void);

#define HOST 0
#define SLAVE 1

#endif

