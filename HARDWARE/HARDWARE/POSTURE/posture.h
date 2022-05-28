#ifndef __POSTURE_H
#define __POSTURE_H
#include "sys.h"
#include "delay.h"
#include "includes.h"

void lets_swim(int A, int B, int speed);
void lets_turn(int A, int B, int offset, int speed);

void Rswim(void);
void Rstop(void);
void Rleft(void);
void Rright(void);
void PID(void);
void speedup(void);
void speeddown(void);
void my_pid(void);
char set_pid(int x , u16 *para1);
	
extern int swim_flag;
extern int speed;
#endif
