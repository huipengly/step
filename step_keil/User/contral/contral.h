#ifndef __CONTRAL_H
#define __CONTRAL_H
#include <include.h>
#define ARM_A                   132    // upper arm
#define ARM_B                   137    // lower arm
#define ARM_2AB                 36168  // 2*A*B
#define ARM_A2                  17424  // A^2
#define ARM_B2                  18769  // B^2
#define ARM_A2B2                36193  // A^2 + B^2
#define ARM_STRETCH_MIN         0      //前后大小限位
#define ARM_STRETCH_MAX         195    
#define ARM_HEIGHT_MIN          -150   //上下大小限位
#define ARM_HEIGHT_MAX          160
#define ARM_ROTATION_MIN        -90    //底座角度限位
#define ARM_ROTATION_MAX        90
#define HAND_ROTATION_MIN       -90	   //抓手左右限位
#define HAND_ROTATION_MAX       90
#define HAND_ANGLE_OPEN         25		//抓手张开角度
#define HAND_ANGLE_CLOSE        70      //抓手闭合角度
#define HEIGHT_OFFSET           80	    // 高度校准
#define LENGTH_OFFSET           15		// 长度校准
#define Y_OFFSET				100		// Y轴校准
#define PI                      3.141592653
#define ANGLE_INIT1             34
#define ANGLE_INIT2             -2
#define ANGLE_INIT3             0
struct Arm_Stretch
{
	int Stretch_X;
	int Height;
	int Stretch_Y;
	double Stretch;
	
};
struct Arm_Angle
{
	double Motor1_angle;
	double Motor2_angle;
	double Motor3_angle;
	
};
struct Arm_Step
{
	double Motor1_step;
	double Motor2_step;
	double Motor3_step;
	double Hand_servo;	
};

void Arm_run(struct Arm_Stretch Stretch_run);
void Arm_Angle_init(void);

#endif

