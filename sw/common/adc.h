

#ifndef __ADC_H__
#define __ADC_H__

#include "includes.h"

//ʵ������Ϊ�¶�ֵ +40��
//��Ƭ������������������ת��
#define MIN_TEMP_LIMIT        (-40)               //ϵͳ�ɼ��������¶�ֵ
#define TEMP_2_UINT(temp)     ((u8)((temp) - MIN_TEMP_LIMIT))
// #define UINT_2_TEMP(u_int)    ((s8)(u_int + MIN_TEMP_LIMIT))

#define TEMP_SENSOR_OPEN      ((u8)-1)    //��������·
#define TEMP_SENSOR_SHORT     ((u8)-2)    //��������·
#define TEMP_HIGH_LIMIT       69          //�¶�����,�������¶���Ϊ���¶ȹ���
#define TEMP_LOW_LIMIT        5           //�¶�����,���ڴ��¶���Ϊ���¶ȹ���

#define ADC_CH_REF             0     //�ο�ͨ��
#define ADC_CH_TEMP            1     //�¶�
#define ADC_CH_CURRENT         2		 //����
#define ADC_CH_INPUT_VOLGATE   3     //�����ѹ


//��ȡָ��ͨ����ǰ��ADֵ
u16 GetAd(u8 ch);

//��Ȧ���� mA
u16 GetCoilCurrent(void);

void InitAdc(void);

#endif
