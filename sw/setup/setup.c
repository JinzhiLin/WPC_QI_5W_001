/*
	by:sqqdfny 2017-09-30 QQ:792739069  e-mail:sqqdfny@163.com
	�������ݱ��浽APROM ����� 1K 
	��ʼ��ַ: 0x4400
	FALSH�ṹ: 128bytes Ϊ1ҳ, ��ҳ���� ��8ҳ
	�������ݷ���: 8bytes Ϊ1��, ÿҳ16�� ��128��(���ɱ���128������)
	����8bytes�Ĳ������Է��������Ķ��,������Խ��ҳ�߽�
*/


#include "setup.h"
#include "string.h"


static u8 xdata setup_buf[128];
//===================================================================
//***********************************************************************************************************
#define     CID_READ            0x0B
#define     DID_READ            0x0C

/*
	Since the DATAFLASH is in the APROM. Program command is same as program APROM
*/
#define     PAGE_ERASE_AP       0x22
#define     BYTE_READ_AP        0x00
#define     BYTE_PROGRAM_AP     0x21
#define     PAGE_SIZE           128


#define     ERASE_FAIL          0x70
#define     PROGRAM_FAIL        0x71
#define     IAPFF_FAIL          0x72
#define     IAP_PASS            0x00

static void IapEraseFlashPage(u16 pageAddr)
{
	set_IAPEN;													// Enable IAP function
	IAPFD = 0xFF;												// IMPORTANT !! To erase function must setting IAPFD = 0xFF 
	IAPCN = PAGE_ERASE_AP;
	set_APUEN;													//  APROM modify Enable
 
	IAPAL = pageAddr & 0xFF;
	IAPAH = (pageAddr >> 8) & 0xFF;
	set_IAPGO;	 
  //if((CHPCON&SET_BIT6)==SET_BIT6)
	//{}
	clr_APUEN;
	clr_IAPEN;
}

static void IapWriteDataToFlashPage(u16 addr, u8 * pbuf)
{
	u8 i;
	set_IAPEN;
	set_APUEN;    
	
	IAPCN = BYTE_PROGRAM_AP;
	
	for(i = 0; i < 128; i++)
	{   
		IAPAL = addr & 0xFF;
		IAPAH = (addr >> 8) & 0xFF;
		IAPFD = *pbuf;     
		set_IAPGO;	 
  //if((CHPCON&SET_BIT6)==SET_BIT6)
	//{}
		addr ++;
		pbuf ++;
	} 
		
	clr_APUEN;
	clr_IAPEN;
}

static void IapReadDataFromFlash(u16 addr, u8 * pbuf, u8 len)
{
	u8 i;
	set_IAPEN;
	set_APUEN;    
	
	IAPCN = BYTE_READ_AP;
	
	for(i = 0; i < len; i++)
	{   
		IAPAL = addr & 0xFF;
		IAPAH = (addr >> 8) & 0xFF;    
		set_IAPGO;	 
  //if((CHPCON&SET_BIT6)==SET_BIT6)
	//{}
		*pbuf = IAPFD;
		addr ++;
		pbuf ++;
	} 
		
	clr_APUEN;
	clr_IAPEN;
}
//===================================================================
void SetupSavePara_Chip_Addr(u16 addr, void * p, u8 len)
{
	u8 index;
	index = addr & 0x7F;
	addr &= ~0x007F;
	
	IapReadDataFromFlash(addr, setup_buf, 128);
	if(memcmp(p, setup_buf + index, len))
	{//�¾ɲ�����ͬ��д���²�����FLASH
		memcpy(setup_buf + index, p, len);
		
		IapEraseFlashPage(addr);
		IapWriteDataToFlashPage(addr, setup_buf);
	}
}

void SetupReadPara_Chip_Addr(u16 addr, void * p, u8 len)
{
	IapReadDataFromFlash(addr, p, len);
}
//===================================================================

//end files

