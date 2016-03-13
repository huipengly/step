/************************************************************
  Copyright (C), 2015 - 2015, ZhA.
  FileName: main.c
  Author: NaTel   Version : 0.0      Date: 2015/08/04
  Description: ����ģ���������     // ģ������     
  Version:   // �汾��Ϣ
  Function List:   // ��Ҫ�������书��
    1. 
  History:         // ��ʷ�޸ļ�¼
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/
  
#include "stm32f10x.h"
#include "contral.h"
#include "stepping_motor.h"


/*************************************************
  Function:main       // ��������
  Description:������    // �������ܡ����ܵȵ�����
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Input:          // �������˵��������ÿ����������
                  // �á�ȡֵ˵�����������ϵ��
  Output:         // �����������˵����
  Return:         // ��������ֵ��˵��
  Others:         // ����˵��
*************************************************/
int main(void)
{
	
	struct Arm_Stretch Stretch_run;
	Arm_Angle_init();
	stepping_motor_Init();
	Stretch_run.Stretch_X = 5;
	Stretch_run.Stretch_Y = 5;
	Stretch_run.Height = 5;
	
	Arm_run(Stretch_run);
	
	while(1);
}

/*********************************************END OF FILE**********************/

