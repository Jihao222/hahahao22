#include "pid.h"
#include "stmflash.h" 
#include "stdlib.h"

u8 TEXT_Buffer[25];

static float off_err_last=0;
static float off_err=0;
static float off_err_last_last=0;
static float ang_err_last=0;
static float ang_err=0;
static float ang_err_last_last=0;


float off_p=16;//1.5
float off_i=5.4;//0.4
float off_d=0.6;//0.6
 
float ang_p=16;//4
float ang_i=7;//0.5
float ang_d=0.6;//1

static float ang_out;

static float off_cal;
static float ang_cal;
extern int angle,offset,sign; 
int a_m=0;
void pipe_control()
 {	 
	off_err_last_last=off_err_last;
	off_err_last=off_err;
	off_err=0 - offset;
		
	ang_err_last_last=ang_err_last;
	ang_err_last=ang_err;
	ang_err=0 - angle;
	

	
	off_cal=(int)(off_p*(off_err-off_err_last)+off_i*off_err+off_d*(off_err+off_err_last_last-2*off_err_last));
	ang_cal=(int)(ang_p*(ang_err-ang_err_last)+ang_i*ang_err+ang_d*(ang_err+ang_err_last_last-2*ang_err_last));
	a_m+=off_cal*0.9+ang_cal*0.7;

	a_m = a_m<300?a_m:300;
	a_m = a_m>-300?a_m:-300; //ãÐÖµ
 }

int douhao=0;
 

void save_para()
{
	sprintf(TEXT_Buffer,"%d,%d,%d,%d,%d,%d,",(int)(10*off_p),(int)(10*off_i),(int)(10*off_d),(int)(10*ang_p),(int)(10*ang_i),(int)(10*ang_d));
	STMFLASH_Write(FLASH_SAVE_ADDR,(u32*)TEXT_Buffer,SIZE);
}
void read_para()
{
	u8 datatemp[32];
	u8 *para = (u8*)datatemp;
	u8 buf[5];
	int i=0;
	
	
	for(i=0;i<5;i++)
	{
		buf[i]=0;
	}
	STMFLASH_Read(FLASH_SAVE_ADDR,(u32*)datatemp,8);
	i=0;
switch(douhao)
{
	case 0:
		while(1)
		{
			if(*para!=',')
			{
				buf[i] = *para;
				i++;
				para++;
			}
			else 
			{
				off_p=(float)(atoi((char*)buf))/10;
				for(i=0;i<5;i++)
				{
					buf[i]=0;
				}
				i=0;
				douhao++;
				para++;
				break;
			}
		}
	case 1:
		while(1)
		{
			if(*para!=',')
			{
				buf[i] = *para;
				i++;
				para++;
			}
			else 
			{
				off_i=(float)(atoi((char*)buf))/10;
				for(i=0;i<5;i++)
				{
					buf[i]=0;
				}
				i=0;
				douhao++;
				para++;
				break;
			}
		}
	case 2:
		while(1)
		{
			if(*para!=',')
			{
				buf[i] = *para;
				i++;
				para++;
			}
			else 
			{
				off_d=(float)(atoi((char*)buf))/10;
				for(i=0;i<5;i++)
				{
					buf[i]=0;
				}
				i=0;
				douhao++;
				para++;
				break;
			}
		}
		case 3:
		while(1)
		{
			if(*para!=',')
			{
				buf[i] = *para;
				i++;
				para++;
			}
			else 
			{
				ang_p=(float)(atoi((char*)buf))/10;
				for(i=0;i<5;i++)
				{
					buf[i]=0;
				}
				i=0;
				douhao++;
				para++;
				break;
			}
		}
		case 4:
		while(1)
		{
			if(*para!=',')
			{
				buf[i] = *para;
				i++;
				para++;
			}
			else 
			{
				ang_i=(float)(atoi((char*)buf))/10;
				for(i=0;i<5;i++)
				{
					buf[i]=0;
				}
				i=0;
				douhao++;
				para++;
				break;
			}
		}
		case 5:
		while(1)
		{
			if(*para!=',')
			{
				buf[i] = *para;
				i++;
				para++;
			}
			else 
			{
				ang_d=(float)(atoi((char*)buf))/10;
				for(i=0;i<5;i++)
				{
					buf[i]=0;
				}
				i=0;
				douhao++;
				para++;
				break;
			}
		}
		
	
}

}

char set_pid(int x , u16 *para1)
{
	u8 *para=(u8*)para1;
	char a[8]={0};
	int i=0,j =0;
	u8 douhao=0;
	u8 save_para=1;
	if(x!=41)
		return 'X';
	while((*para<='~')&&(*para>=' '))
	{
		if(*para==',')
		{
			douhao++;
			switch(save_para)
			{
				case 1:
					off_p=0.1*atof(a);
					break;
				case 2:
					off_i=0.1*atof(a);
					break;
				case 3:
					off_d=0.1*atof(a);
					break;
				case 4:
					ang_p=0.1*atof(a);
					break;
				case 5:
					ang_i=0.1*atof(a);
					break;
			}
			for(j=0;j<=5;j++)
			{
				a[j]=0;
			}
			para++;
			save_para++;
			i=0;
		}
		else
		{
			a[i]=*para;
			para++;
			i++;
		}
	}
		ang_d=0.1*atof(a);
	if(douhao!=5)
		return 'X';
	return 0;
}


void OP1()
{
	off_p+=0.1;
}
void OI1()
{
	off_i+=0.1;
}
void OD1()
{
	off_d+=0.1;
}
void OP2()
{
	off_p-=0.1;
}
void OI2()
{
	off_i-=0.1;
}
void OD2()
{
	off_d-=0.1;
}

void AP1()
{
	ang_p+=0.1;
}
void AI1()
{
	ang_i+=0.1;
}
void AD1()
{
	ang_d+=0.1;
}
void AP2()
{
	ang_p-=0.1;
}
void AI2()
{
	ang_i-=0.1;
}
void AD2()
{
	ang_d-=0.1;
}