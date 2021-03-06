#include "contral.h"
#include "stepping_motor.h"
struct Arm_Angle Arm_angle_old;
struct Arm_Stretch  Offset_Length(struct Arm_Stretch Arm_run)//增加补偿
{
	Arm_run.Stretch_Y = Arm_run.Stretch_Y + Y_OFFSET;
	Arm_run.Stretch = sqrt(Arm_run.Stretch_X * Arm_run.Stretch_X + Arm_run.Stretch_Y * Arm_run.Stretch_Y)-HEIGHT_OFST;
	Arm_run.Stretch =Arm_run.Stretch + LENGTH_OFFSET;
	Arm_run.Height = Arm_run.Height - HEIGHT_OFFSET;
	return (Arm_run);
}
void Arm_Angle_init(void) //初始化角度
{
	Arm_angle_old.Motor1_angle = ANGLE_INIT1;
	Arm_angle_old.Motor2_angle = ANGLE_INIT2;
	Arm_angle_old.Motor3_angle = ANGLE_INIT3;
	
}
struct Arm_Angle Length_To_Angle(struct Arm_Stretch Arm_run)//从长度到角度 cos a = (b^2+c^2-a^2)/2ab
{
	double angle_a;
	double angle_b;
	double angle_c = 0;
	//double angle_d;
	//double
	double Height2_Stretch2;
	struct Arm_Angle Angle_one;
	Height2_Stretch2 = Arm_run.Stretch * Arm_run.Stretch + Arm_run.Height * Arm_run.Height;
	angle_a = acos((ARM_A2 + Height2_Stretch2 - ARM_B2)/(2 * ARM_A * sqrt(Height2_Stretch2))) * 180 / PI;
	angle_b = acos((ARM_A2B2 - Height2_Stretch2) / ( ARM_2AB)) * 180 / PI;
	angle_c = (double)atan((double)Arm_run.Height / (double)Arm_run.Stretch) * 180 / PI;
	Angle_one.Motor1_angle = angle_a + angle_c;
	Angle_one.Motor2_angle = 180 - angle_b - Angle_one.Motor1_angle;
	Angle_one.Motor3_angle = (double)atan((double)Arm_run.Stretch_X / (double)Arm_run.Stretch_Y) * 180 / PI;
	return (Angle_one);
}
struct Arm_Step Angle_To_step(struct Arm_Angle Arm_run) //从角度到步进电机步数
{
	struct Arm_Step Step_one;
	Step_one.Motor1_step = Arm_run.Motor1_angle * 13.7 * 16.0 / 1.8;//步进电机每步1.8度，1:19减速
	Step_one.Motor2_step = Arm_run.Motor2_angle * 13.7 * 16.0 / 1.8;
	Step_one.Motor3_step = Arm_run.Motor3_angle * 13.7 * 16.0 / 1.8;
	return (Step_one);
};
struct Arm_Angle Add_Angle (struct Arm_Angle Arm_run_new ,struct Arm_Angle Arm_run_old)//变为增加的角度
{
	Arm_run_new.Motor1_angle = Arm_run_new.Motor1_angle - Arm_run_old.Motor1_angle;
	Arm_run_new.Motor2_angle = Arm_run_new.Motor2_angle - Arm_run_old.Motor2_angle;
	Arm_run_new.Motor3_angle = Arm_run_new.Motor3_angle - Arm_run_old.Motor3_angle;
	return (Arm_run_new);
}

void Arm_run(struct Arm_Stretch Stretch_run)
{
	struct Arm_Angle Arm_angle_new;
	//static struct Arm_Angle Arm_angle_old;
	struct Arm_Angle Arm_angle_send;
	struct Arm_Stretch Stretch_one;
	static struct Arm_Step Step_one_err_zheng;
	static struct Arm_Step Step_one_err_fu;
	struct Arm_Step Step_one;
	unsigned char PAN_Motor1 = 0;               //positive and negative going motion；
	unsigned char PAN_Motor2 = 0;               //motor1、2、3为0顺时针，为1逆时针；
	unsigned char PAN_Motor3 = 0;
	Stretch_one = Offset_Length(Stretch_run);
	Arm_angle_new = Length_To_Angle(Stretch_one);
	Arm_angle_send = Add_Angle(Arm_angle_new,Arm_angle_old);
	Arm_angle_old.Motor1_angle = Arm_angle_new.Motor1_angle;
	Arm_angle_old.Motor2_angle = Arm_angle_new.Motor2_angle;
	Arm_angle_old.Motor3_angle = Arm_angle_new.Motor3_angle;
	if(Arm_angle_send.Motor1_angle < 0)       //判断正负
	{
		PAN_Motor1 = 1;
		Arm_angle_send.Motor1_angle = -Arm_angle_send.Motor1_angle;
		
	}
	else
	{
		PAN_Motor1 = 0;
		
	}
	if(Arm_angle_send.Motor2_angle < 0)
	{
		PAN_Motor2 = 1;
		Arm_angle_send.Motor2_angle = - Arm_angle_send.Motor2_angle;
		
	}
	else
	{
		PAN_Motor2 = 0;
		
	}
	if(Arm_angle_send.Motor3_angle < 0)
	{
		PAN_Motor3 = 1;
		Arm_angle_send.Motor3_angle = -Arm_angle_send.Motor3_angle;
		
	}
	else
	{
		PAN_Motor3 = 0;
	}
	Step_one = Angle_To_step(Arm_angle_send);
	if(PAN_Motor1 == 0)                //判断正负方向，然后分别累加误差
	{
		Step_one.Motor1_step += Step_one_err_zheng.Motor1_step;
		Step_one_err_zheng.Motor1_step = Step_one.Motor1_step - (int)Step_one.Motor1_step;
	}
	else 
	{
		Step_one.Motor1_step += Step_one_err_fu.Motor1_step;
		Step_one_err_fu.Motor1_step = Step_one.Motor1_step - (int)Step_one.Motor1_step;
	}
	if(PAN_Motor2 == 0)
	{
		Step_one.Motor2_step += Step_one_err_zheng.Motor2_step;
		Step_one_err_zheng.Motor2_step = Step_one.Motor2_step - (int)Step_one.Motor2_step;
	}
	else 
	{
		Step_one.Motor2_step += Step_one_err_fu.Motor2_step;
		Step_one_err_fu.Motor2_step = Step_one.Motor2_step - (int)Step_one.Motor2_step;
	}
	if(PAN_Motor3 == 0)
	{
		Step_one.Motor3_step += Step_one_err_zheng.Motor3_step;
		Step_one_err_zheng.Motor3_step = Step_one.Motor3_step - (int)Step_one.Motor3_step;
	}
	else 
	{
		Step_one.Motor3_step += Step_one_err_fu.Motor3_step;
		Step_one_err_fu.Motor3_step = Step_one.Motor3_step - (int)Step_one.Motor3_step;
	}
	
	
	
	stepping_motor_step_change( (int)Step_one.Motor1_step, !PAN_Motor1, (int)Step_one.Motor2_step, PAN_Motor2, (int)Step_one.Motor3_step, PAN_Motor3 );//motor1方向取反
}
