/************************************************************
  Copyright (C), 2015 - 2015, ZhA.
  FileName: KEY.c
  Author: NaTel   Version : 0.1      Date: 2015/08/12
  Description: 按键检测     // 模块描述
  Version:0.1   // 版本信息
  Function List:   // 主要函数及其功能
    1. void Key_GPIO_Init(void); //按键GPIO初始化
		2. uint8_t Key_Scan(void);//按键扫描,返回键值
  History:         // 历史修改记录
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/

#include "Key.h"
#include "delay.h"

/*************************************************
  Function:Key_GPIO_Init       // 函数名称
  Description:按键GPIO初始化
					PB13~15分别对应1,2,3号键
					分别返回0xC0 0xA0 0x30
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Input:          // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Output:         // 对输出参数的说明。
  Return:         // 函数返回值的说明
  Others:         // 其它说明
*************************************************/
void Key_GPIO_Init(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启LED的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
 
	/*选择要控制的GPIOB引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;

	/*设置引脚模式为上拉输入*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	/*调用库函数，初始化GPIOB 13~15*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_Write(GPIOB, 0XFFFF);
	
}
/*************************************************
  Function:Key_Scan       // 函数名称
  Description:按键扫描程序
									// 函数功能、性能等的描述
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Input:          // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Output:         // 对输出参数的说明。
  Return:
					PB13~15分别对应1,2,3号键
					分别返回0xC0 0xA0 0x30
									// 函数返回值的说明
  Others:         // 其它说明
*************************************************/
uint8_t Key_Scan(void)
{
	uint16_t KEY_tmp;//记录读入的按键GPIO(16位)
	uint8_t KEY;//转换为8位的按键值
	KEY_tmp = GPIO_ReadInputData(GPIOB);
	if ( (GPIO_ReadInputData(GPIOB) & 0xE000) != 0xE000 )//读入键值,判断是否按下按键
	{
		delay_ms(10);//消抖
		if ( (GPIO_ReadInputData(GPIOB) & 0xE000) != 0xE000 )//读入键值,判断是否按下按键
		{
			KEY_tmp = GPIO_ReadInputData(GPIOB);//读入键值
			KEY_tmp = KEY_tmp & 0xE000;//去除无用部分
			KEY = KEY_tmp >> 8;//转换为8位
			while( (GPIO_ReadInputData(GPIOB) & 0xE000) != 0xE000 );//松手检测
			return KEY;
		}
	}
	return 0;
}
/***********END OF FILE******************/
