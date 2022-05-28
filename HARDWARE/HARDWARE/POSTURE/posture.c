#include "posture.h"
#include "pid.h"

int i = 1500;
int j = 1500;
int swim_flag=0;
int speed=16;


void Rswim()
{
	swim_flag = 1;
}

void Rstop()
{
	swim_flag = 0;
}

void Rleft()
{
	swim_flag = 2;
}

void Rright()
{
	swim_flag = 3;
}
void PID()
{
	swim_flag = 4;
}

void speedup()
{
	speed++;
}

void speeddown()
{
	speed--;
}


void lets_swim(int A, int B, int speed)
{
	OS_ERR err;
	while(i<1500+A)
	{
		i+=speed;
		TIM_SetCompare2(TIM4,i);
		OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_PERIODIC,&err);
	}
	while(j<1500+B)
	{
		j+=speed;
		TIM_SetCompare1(TIM4,j);
		OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_PERIODIC,&err);
	}
	while(i>1500-A)
	{
		i-=speed;
		TIM_SetCompare2(TIM4,i);
		OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_PERIODIC,&err);
	}
	while(j>1500-B)
	{
		j-=speed;
		TIM_SetCompare1(TIM4,j);
		OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_PERIODIC,&err);
	}
}
void lets_turn(int A, int B, int offset, int speed)
{
	OS_ERR err;
	while(i<1500+offset+A)
	{
		i+=speed;
		TIM_SetCompare2(TIM4,i);
		OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_PERIODIC,&err);
	}
	while(j<1500+offset+B)
	{
		j+=speed;
		TIM_SetCompare1(TIM4,j);
		OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_PERIODIC,&err);
	}
	while(i>1500+offset-A)
	{
		i-=speed;
		TIM_SetCompare2(TIM4,i);
		OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_PERIODIC,&err);
	}
	while(j>1500+offset-B)
	{
		j-=speed;
		TIM_SetCompare1(TIM4,j);
		OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_PERIODIC,&err);
	}
}

void my_pid()
{
	lets_turn(180,300,a_m,speed);
}
