/*************************************************
  Copyright (C), 2015 - 2016, ZhA.
  FileName: include.h
  Author: NaTel  Version: 1.0     Date: 2016/01/18
  Description: 按键
  Others: 
  Function List:   // 主要函数及其功能
    1. void Key_GPIO_Init(void); //按键GPIO初始化
	2. uint8_t Key_Scan(void);//按键扫描,返回键值
*************************************************/
#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"
#define KEY_CANCLE 0xC0
#define KEY_NEXT 0xA0
#define KEY_OK 0x60
void Key_GPIO_Init(void);
uint8_t Key_Scan(void);
void Key_Function(void);
#endif/*__KEY_H*/
