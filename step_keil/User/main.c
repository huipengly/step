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
#include "include.h"

#define X_change = 0;
#define Y_change = 1;
#define H_change = 2;

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
	int KEY;
	int state = 0;
	char X_string[3];
	char Y_string[3];
	char H_string[3];
	
	struct Arm_Stretch Stretch_run;
	Arm_Angle_init();
	stepping_motor_Init();
	
	Key_GPIO_Init();
	delay_init(72);
	
	LCD_init();
	
	Stretch_run.Stretch_X = 100;
	Stretch_run.Stretch_Y = 0;
	Stretch_run.Height = 0;
	
	Arm_run(Stretch_run);
	
	LCD_write_english_string(0, 0, "X:");
	LCD_write_english_string(0, 1, "Y:");
	LCD_write_english_string(0, 2, "H:");
	LCD_write_english_string(12, 0, my_itoa(Stretch_run.Stretch_X, X_string, 10));
	LCD_write_english_string(12, 1, my_itoa(Stretch_run.Stretch_Y, Y_string, 10));
	LCD_write_english_string(12, 2, my_itoa(Stretch_run.Height,		 H_string, 10));
	while(1)
	{
		KEY = Key_Scan();
		if ( KEY_OK == KEY )//״̬�л�
		{
			state++;
			if ( 3 == state)
			{
				state = 0;
			}
		}
		switch( state )//state 0�ı�x,1�ı�Y,2�ı�H
		{
			case 0 :
				if( KEY_UP == KEY )
				{
					Stretch_run.Stretch_X++;
					Arm_run(Stretch_run);
				}
				if( KEY_DOWN == KEY )
				{
					Stretch_run.Stretch_X--;
					Arm_run(Stretch_run);
				}
				break;
			case 1 :
				if( KEY_UP == KEY )
				{
					Stretch_run.Stretch_Y++;
					Arm_run(Stretch_run);
				}
				if( KEY_DOWN == KEY )
				{
					Stretch_run.Stretch_Y--;
					Arm_run(Stretch_run);
				}
				break;
			case 2 :
				if( KEY_UP == KEY )
				{
					Stretch_run.Height++;
					Arm_run(Stretch_run);
				}
				if( KEY_DOWN == KEY )
				{
					Stretch_run.Height--;
					Arm_run(Stretch_run);
				}
				break;
		}
		if( ( KEY_UP == KEY ) || ( KEY_DOWN == KEY ) || ( KEY_OK == KEY ))
		{
			LCD_write_english_string(12, 0, "   ");
			LCD_write_english_string(12, 1, "   ");
			LCD_write_english_string(12, 2, "   ");
			LCD_write_english_string(12, 0, my_itoa(Stretch_run.Stretch_X, X_string, 10));
			LCD_write_english_string(12, 1, my_itoa(Stretch_run.Stretch_Y, Y_string, 10));
			LCD_write_english_string(12, 2, my_itoa(Stretch_run.Height, 		H_string, 10));
		}
	}
}

/*********************************************END OF FILE**********************/

