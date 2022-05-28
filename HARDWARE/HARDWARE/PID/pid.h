#ifndef __PID_H
#define __PID_H
#include "sys.h"

extern u8 TEXT_Buffer[25];

#define TEXT_LENTH sizeof(TEXT_Buffer)	 		  	//数组长度	
#define SIZE TEXT_LENTH/4+((TEXT_LENTH%4)?1:0)

#define FLASH_SAVE_ADDR  0X0805C004 	//设置FLASH 保存地址(必须为偶数，且所在扇区,要大于本代码所占用到的扇区.
										//否则,写操作的时候,可能会导致擦除整个扇区,从而引起部分程序丢失.引起死机.

extern int a_m;

extern float off_p;//1.5
extern float off_i;//0.4
extern float off_d;//0.6
 
extern float ang_p;//4
extern float ang_i;//0.5
extern float ang_d;//1

void pipe_control(void);
void save_para(void);
void read_para(void);

void AP1(void);
void AP2(void);
void AI1(void);
void AI2(void);
void AD1(void);
void AD2(void);

void OP1(void);
void OP2(void);
void OI1(void);
void OI2(void);
void OD1(void);
void OD2(void);
	

#endif
