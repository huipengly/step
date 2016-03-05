/*************************************************
  Copyright (C), 2015 - 2016, ZhA.
  FileName: include.h
  Author: NaTel  Version: 1.0     Date: 2016/01/18
  Description: ����
  Others: 
  Function List:   // ��Ҫ�������书��
    1. void Key_GPIO_Init(void); //����GPIO��ʼ��
	2. uint8_t Key_Scan(void);//����ɨ��,���ؼ�ֵ
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
