#include "stm32f10x.h"
#include "stepping_motor.h"
uint16_t steps_counter = 0;			//脉冲计数
uint16_t steps_change[3] = {0, 0, 0};//记录脉冲应改变数目
uint8_t steps_change_finish = 1;//记录脉冲改变是否完成
uint8_t motor1_change_finish = 0;//记录第1个步进电机是否改变完成
uint8_t motor2_change_finish = 0;//记录第2个步进电机是否改变完成
uint8_t motor3_change_finish = 0;//记录第3个步进电机是否改变完成
void stepping_motor_pwm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef Base_InitStructure;
	TIM_OCInitTypeDef PWM_InitSturcture;
	NVIC_InitTypeDef PWM_NVICStructure;
	
	/*******************RCC********************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	/************************************************/
	
	
	/*******************GPIO********************/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	/************************************************/


	/*******************NVIC********************/
	PWM_NVICStructure.NVIC_IRQChannel = TIM3_IRQn;
	PWM_NVICStructure.NVIC_IRQChannelCmd = ENABLE;
	PWM_NVICStructure.NVIC_IRQChannelSubPriority = 1;
	PWM_NVICStructure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_Init(&PWM_NVICStructure);
	/************************************************/
	
	/*******************TIM3 BASE********************/
	Base_InitStructure.TIM_ClockDivision = 0;
	Base_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Base_InitStructure.TIM_Period = 999;
	Base_InitStructure.TIM_Prescaler = 71;
	Base_InitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&Base_InitStructure);
	/************************************************/
	
	
	TIM_ITConfig(TIM3,TIM_IT_CC2,ENABLE);


	/*******************TIM3 PWM********************/
	PWM_InitSturcture.TIM_OCMode = TIM_OCMode_PWM1;
	PWM_InitSturcture.TIM_OCPolarity = TIM_OCPolarity_High;
	PWM_InitSturcture.TIM_OutputState= TIM_OutputState_Enable;
	PWM_InitSturcture.TIM_Pulse = 500;
	
	TIM_OC1Init(TIM3,&PWM_InitSturcture);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	PWM_InitSturcture.TIM_OutputState = TIM_OutputState_Enable;
	PWM_InitSturcture.TIM_Pulse = 500;
	
	TIM_OC2Init(TIM3,&PWM_InitSturcture);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);

	PWM_InitSturcture.TIM_OutputState = TIM_OutputState_Enable;
	PWM_InitSturcture.TIM_Pulse = 500;
	
	TIM_OC3Init(TIM3,&PWM_InitSturcture);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	PWM_InitSturcture.TIM_OutputState = TIM_OutputState_Enable;
	PWM_InitSturcture.TIM_Pulse = 500;
	
 	TIM_OC4Init(TIM3,&PWM_InitSturcture);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	/************************************************/
	
	
	TIM3->CCMR1 = 0x0808;
	TIM3->CCMR2 = 0x0808;
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

void stepping_motor_GPIO_Init(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIO的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
 
	/*选择要控制的GPIOB引脚*/				   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化GPIOB0*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOB, GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}

void stepping_motor_Init(void)
{
	stepping_motor_pwm_Init();
	stepping_motor_GPIO_Init();
}

void TIM3_IRQHandler(void)
{
//	extern u8 steps_counter;
	if (TIM_GetITStatus(TIM3,TIM_IT_CC2) != RESET)
	{
		steps_counter++;
		if (steps_counter >= steps_change[0])
		{
			TIM3->CCMR1 &= 0xFF0F;
			motor1_change_finish = 1;
		}
		if (steps_counter >= steps_change[1])
		{
			TIM3->CCMR2 &= 0xFF0F;
			motor2_change_finish = 1;
		}
		if (steps_counter >= steps_change[2])
		{
			TIM3->CCMR2 &= 0x0FFF;
			motor3_change_finish = 1;
		}
		if ( (1 == motor1_change_finish) & (1 == motor2_change_finish) & (1 == motor3_change_finish) )
		{
			steps_change_finish = 1;
			motor1_change_finish = 0;
			motor2_change_finish = 0;
			motor3_change_finish = 0;
			TIM3->CCMR1 = 0x0808;
			TIM3->CCMR2 = 0x0808;
			steps_counter = 0;
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC2);
	}
}

void stepping_motor_step_change( float motor1_step, int8_t motor1_direction, float motor2_step, int8_t motor2_direction, float motor3_step, int8_t motor3_direction )
{
	if( 1 == steps_change_finish )
	{
		//判断步进电机转动方向
		GPIO_SetBits(GPIOB, GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);//默认所有方向设置为正转，若标志量为负则将方向反转
		if( 0 > motor1_direction )
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		}
		if( 0 > motor2_direction )
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		}
		if( 0 > motor3_direction )
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		}
		//计算输出给步进电机的脉冲数
		steps_change[0] = motor1_step;
		steps_change[1] = motor2_step;
		steps_change[2] = motor3_step;
		TIM3->CCMR1 = 0x6868;
		TIM3->CCMR2 = 0x6868;
		//判断是否有不需要脉冲的电机
		if ( 0 == steps_change[0] )
			TIM3->CCMR1 &= 0xFF0F;
		if ( 0 == steps_change[1] )
			TIM3->CCMR2 &= 0xFF0F;
		if ( 0 == steps_change[2] )
			TIM3->CCMR2 &= 0x0FFF;
		steps_change_finish = 0;//开始发生脉冲
	}
}


