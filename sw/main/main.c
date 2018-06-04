/* MAIN.C file
 * 
	by:sqqdfny 2017-11-26 QQ:792739069  e-mail:sqqdfny@163.com
	ϵͳ10ms����һ��,���еļ�ʱ�����������н���
	10ms�ж�ֻ����ʱ����
	4��Ĵ�������: main->page0   Wkt_ISR->page1  TimerCapture_ISR(QIЭ�����)->page2  page3->not used
	N76E003AT20 ��WDT����ѡ�������ÿ�����,����Ҫ�����ʼ��,Ŀǰ��֪��ʲôԭ�������к�,WDT�޷���ʱ��λϵͳ
	WKT->10ms�ж�
	Timer2->QI(capture) ң��������         
*/
 
 /*
           b7        b6        b5        b4        b3        b2         b1         b0
 config0   CBS       Reserved  OCDPWM    OCDEN     Reserved  RPD        LOCK       Reserved     0xd9/0xe9   RST_PIN->P2.0  LOCK_EN
 config1   Reserved  Reserved  Reserved  Reserved  Reserved  LDSIZE[2]  LDSIZE[1]  LDSIZE[0]    0xff
 config2   CBODEN    Reserved  CBOV[1]   CBOV[0]   BOIAP     CBORST     Reserved   Reserved     0xff   2.2V
 config3   Reserved  Reserved  Reserved  Reserved  Reserved  Reserved   Reserved   Reserved     0xff
 config4   WDTEN[3]  WDTEN[2]  WDTEN[1]  WDTEN[0]  Reserved  Reserved   Reserved   Reserved     0x5f   ��ʱ��λ,���в�����
 */

#include "includes.h"
#include "adc.h"
#include "qi.h"
#include "led.h"

bit BIT_TMP;

static bool tick_flag;
//=============================================================================
void SystemInit(void)
{
	CKDIV = 0;  //fosc = 16M  fCPU = 16M													
	tick_flag = true;
}
/************************************************************************************************************
*    WKT interrupt subroutine
************************************************************************************************************/
void Wkt_ISR(void) interrupt 17  using 1 //interrupt address is 008BH
{  
	clr_WKTF;
  tick_flag=true;
	QiTimeTickHook();
}

static void WKT_Init(void)
{
	RWK   = 156;    //10MS
  WKCON = 0x08;   //1��Ƶ  
	set_EWKT;       //ʹ��wkt�ж�
}
//==========================================================
//==========================================================
#if(1)   //#ifndef   DEBUG
	#define IWDG_Feed()   set_WDCLR

	static void Iwdg_Init(void)
	{	
		//Setting WDT prescale 
		TA=0xAA;TA=0x55;WDCON=0x07;						//Setting WDT prescale 
		set_WDCLR;														//Clear WDT timer
		while((WDCON|~SET_BIT6)==0xFF);				//confirm WDT clear is ok before into power down mode	
	}
#else
	#define IWDG_Feed()   
	#define Iwdg_Init()
#endif
//=============================================================================
void main(void)
{
	clr_WDTRF;
	clr_BORF;
	Iwdg_Init();
	Delayms(1);
	SystemInit();
	
	InitAdc();
	WKT_Init();
	LedInit();
	QiInit();
	
	EA = 1;

	while(1)
	{
		IWDG_Feed();
		WPC_Qi();
		if(tick_flag)
		{
			tick_flag = false;
		  LedFunction();
		}
	}
}
//===================================================================
//end files
