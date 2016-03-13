/************************************************************
  Copyright (C), 2015 - 2015, ZhA.
  FileName: main.c
  Author: NaTel   Version : 0.0      Date: 2015/08/04
  Description: 工程模版的主函数     // 模块描述     
  Version:   // 版本信息
  Function List:   // 主要函数及其功能
    1. 
  History:         // 历史修改记录
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/
  
#include "stm32f10x.h"
#include "include.h"

#define X_change = 0;
#define Y_change = 1;
#define H_change = 2;

/*************************************************
  Function:main       // 函数名称
  Description:主函数    // 函数功能、性能等的描述
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Input:          // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Output:         // 对输出参数的说明。
  Return:         // 函数返回值的说明
  Others:         // 其它说明
*************************************************/
int main(void)
{
	int KEY;
	int state = 0;
	
	struct Arm_Stretch Stretch_run;
	Arm_Angle_init();
	stepping_motor_Init();
	
	Key_GPIO_Init();
	delay_init(72);
	
	Stretch_run.Stretch_X = 5;
	Stretch_run.Stretch_Y = 5;
	Stretch_run.Height = 5;
	
	Arm_run(Stretch_run);
	
	while(1)
	{
		KEY = Key_Scan();
		if ( KEY_OK == KEY )//状态切换
		{
			state++;
			if ( 3 == state)
			{
				state = 0;
			}
		}
		switch( state )//state 0改变x,1改变Y,2改变H
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
	}
}

/*********************************************END OF FILE**********************/

