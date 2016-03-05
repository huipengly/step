void stepping_motor_pwm_Init(void);
void TIM3_IRQHandler(void);
void stepping_motor_step_change( float motor1_step, int8_t motor1_direction, float motor2_step, int8_t motor2_direction, float motor3_step, int8_t motor3_direction );
void stepping_motor_GPIO_Init(void);
void stepping_motor_Init(void);
