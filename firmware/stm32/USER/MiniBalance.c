#include "stm32f10x.h"
#include "control.h"
#include "sys.h"
#include "math.h"

/**************************************************************************

**************************************************************************/
u8 Flag_Way=0,Flag_Show=0;                 //停止标志位和 显示标志位 默认停止 显示打开
int Servo1,Servo2,Servo3,Servo4,Servo5;     //电机PWM变量
float Velocity1,Velocity2,Velocity3,Velocity4,Velocity5,Velocity6;     //电机PWM变量
float Position1=750,Position2=750,Position3=750,Position4=750,Position5=750,Position6=750;    
float Speed=3;                   //运动速度设置
int Voltage;                      //电池电压采样相关的变量
#define Pi 3.1416
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send; //延时和调参等变量
float Balance_Kp=350,Balance_Kd=0,Velocity_Kp=70,Velocity_Ki=0.7;//PID参数
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash相关数组 
float Target_X=750,Target_Y=750	,Target_Z=750;                     
//float Target1=680,Target2=730,Target3=770,Target4=730,Target5=450,Target6=800;     //电机初始值
float Target1=732,Target2=765,Target3=545,Target4=490,Target5=750,Target6=3000;     //电机初始值
float TargetX,TargetY,TargetZ,Target_Beta=0,Target_Alpha=0,Target_Gamma=0;     					//电机目标值
float	Position_KP=6,Position_KI=0,Position_KD=3;  //位置控制PID参数
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;

u8 zhua_flag=0;
u8 testcmd[]={0xFD,0x00,0x0B ,0x01 ,0x01, 0xD3, 0xD0 ,0xBA ,0xA6 ,0xC0, 0xAC, 0xBB ,0xF8, 0xC6};


int main(void)
  { 
			int i=0,J=0,K=0;
			//	u8 temp1;
			MY_NVIC_PriorityGroupConfig(2); //=====中断分组
			delay_init();	    	            //=====延时函数初始化	
			uart_init(9600);	   //  
			uart3_init(9600);  //接收OPENMV 
			Time2_pwm_init();
			car_stop();
			//=====串口3初始化
			JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试

			delay_ms(1000);                  //=====延时等待

			delay_ms(100);                  //=====延时等待

			tail_trail_init();
			head_trail_init();
		//	bizhang_init();	
		
			delay_ms(1000);  
			TIM2_Int_Init(99,7199);         //=====定时器10ms中断
	  	
    while(1)
	   {
					// printf("111111111");
					delay_flag=1;	
					delay_50=0;
			 /*
			 if(M ==1)
			 {
				printf("MMM");
			 
			 
			 }
			  if(L ==1)
			 {
				printf("LLL");
			 
			 
			 }
			  if(R ==1)
			 {
				printf("RRR");
			 
			 
			 }
			 */
					//head_xunji();	
					//	 turn(right,0.5);
				//	 move(qian ,0.5);
				//	tail_xunji(); 
					// bizhangAction();
					// uart4_sendchar(0XFF);
					//	move(hou,0.5);
					// test(1800,1800,1800,1800);
					//	 car_stop();
					while(delay_flag);	     				
	   } 
}

