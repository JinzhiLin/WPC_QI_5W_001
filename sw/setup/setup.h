

#ifndef __SETUP_H__
#define __SETUP_H__
#include "includes.h"

//�������ݵ���ʱ
//Ϊ�˼���дFLASH����,ÿ���޸Ĳ�����,��ʱһ��ʱ����д��FLASH,
//���⽫���ٵ��ڲ���ʱ���м�ֵд��FLASH
//��λΪ 1/SYSTEM_TICK
#define SAVE_SETUP_DLY           200      

#define IAP_USER_CONFIG_ADDR     0x4400
//===================================================================

//===================================================================
//ÿ�����ݿ�8�ֽ�,����8bytes�Ĳ������Է��������Ķ��,������Խ��ҳ�߽�
//ÿ��ҳ 128B = 8 * 16 
//���� 8ҳ �洢��������  8 * 16 = 128��������
typedef enum
{
  SETUP_INDEX_CONFIG = 0,     			//����ģʽ  
}enumSetupIndex;

//����һ��������
//len->max==8
#define SetupSavePara_Chip(index, p, len) SetupSavePara_Chip_Addr(IAP_USER_CONFIG_ADDR + (((u16)index) << 3), p, len)

//��ȡһ��������
//len->max==8
#define SetupReadPara_Chip(index, p, len) SetupReadPara_Chip_Addr(IAP_USER_CONFIG_ADDR + (((u16)index) << 3), p, len)

//addr->
//p   ->
//len ->  max=8
void SetupSavePara_Chip_Addr(u16 addr, void * p, u8 len);
void SetupReadPara_Chip_Addr(u16 addr, void * p, u8 len);


//===================================================================
#endif  //__SETUP_H__

//===================================================================

//end files

