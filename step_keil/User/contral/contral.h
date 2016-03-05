#include "include.h"
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
#define HEIGHT_OFFSET           0	    // 高度校准
#define LENGTH_OFFSET           0		// 长度校准
#define PI                      3.141592653
#define ANGLE_INIT1             0
#define ANGLE_INIT2             0
#define ANGLE_INIT3             0
struct Arm_Stretch
{
	unsigned int Stretch_X;
	unsigned int Height;
	unsigned int Stretch_Y;
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
	unsigned int Motor1_step;
	unsigned int Motor2_step;
	unsigned int Motor3_step;
	unsigned int Hand_servo;	
};

