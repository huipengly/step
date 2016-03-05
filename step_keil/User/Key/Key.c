/************************************************************
  Copyright (C), 2015 - 2015, ZhA.
  FileName: KEY.c
  Author: NaTel   Version : 0.1      Date: 2015/08/12
  Description: �������     // ģ������
  Version:0.1   // �汾��Ϣ
  Function List:   // ��Ҫ�������书��
    1. void Key_GPIO_Init(void); //����GPIO��ʼ��
		2. uint8_t Key_Scan(void);//����ɨ��,���ؼ�ֵ
  History:         // ��ʷ�޸ļ�¼
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/

#include "Key.h"
#include "delay.h"

/*************************************************
  Function:Key_GPIO_Init       // ��������
  Description:����GPIO��ʼ��
					PB13~15�ֱ��Ӧ1,2,3�ż�
					�ֱ𷵻�0xC0 0xA0 0x30
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Input:          // �������˵��������ÿ����������
                  // �á�ȡֵ˵�����������ϵ��
  Output:         // �����������˵����
  Return:         // ��������ֵ��˵��
  Others:         // ����˵��
*************************************************/
void Key_GPIO_Init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����LED������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
 
	/*ѡ��Ҫ���Ƶ�GPIOB����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;

	/*��������ģʽΪ��������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	/*���ÿ⺯������ʼ��GPIOB 13~15*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_Write(GPIOB, 0XFFFF);
	
}
/*************************************************
  Function:Key_Scan       // ��������
  Description:����ɨ�����
									// �������ܡ����ܵȵ�����
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Input:          // �������˵��������ÿ����������
                  // �á�ȡֵ˵�����������ϵ��
  Output:         // �����������˵����
  Return:
					PB13~15�ֱ��Ӧ1,2,3�ż�
					�ֱ𷵻�0xC0 0xA0 0x30
									// ��������ֵ��˵��
  Others:         // ����˵��
*************************************************/
uint8_t Key_Scan(void)
{
	uint16_t KEY_tmp;//��¼����İ���GPIO(16λ)
	uint8_t KEY;//ת��Ϊ8λ�İ���ֵ
	KEY_tmp = GPIO_ReadInputData(GPIOB);
	if ( (GPIO_ReadInputData(GPIOB) & 0xE000) != 0xE000 )//�����ֵ,�ж��Ƿ��°���
	{
		delay_ms(10);//����
		if ( (GPIO_ReadInputData(GPIOB) & 0xE000) != 0xE000 )//�����ֵ,�ж��Ƿ��°���
		{
			KEY_tmp = GPIO_ReadInputData(GPIOB);//�����ֵ
			KEY_tmp = KEY_tmp & 0xE000;//ȥ�����ò���
			KEY = KEY_tmp >> 8;//ת��Ϊ8λ
			while( (GPIO_ReadInputData(GPIOB) & 0xE000) != 0xE000 );//���ּ��
			return KEY;
		}
	}
	return 0;
}
/***********END OF FILE******************/
