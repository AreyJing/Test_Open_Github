//使用arduino IDE自带的Stepper.h库文件
#include <Stepper.h>
#define Forward 1
#define Turn_right 2
#define Turn_left 3
#define Backward 4
#define Stop 5


// 这设置步进电机旋转一圈是多少步，依据步距角计算，及走一圈需要多少脉冲
#define STEPS 180

//设置步进电机的步数和引脚
Stepper stepperR_L(STEPS, 8, 9,10,11);
Stepper stepperR(STEPS, 8, 9);
Stepper stepperL(STEPS, 10, 11);
//设置超声波传感器引脚
int ECHO = 2;
int TRIG = 3;


void setup()
{
  // 设置电机的转速：每分钟为90步
  stepperR_L.setSpeed(500);
  stepperR.setSpeed(500);
  stepperL.setSpeed(500);
  // 初始化串口，用于调试输出信息
  Serial.begin(9600);
  //循迹模块、超声波模块引脚初始化
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(ECHO,INPUT);
  pinMode(TRIG,OUTPUT);
   
}

void loop()
{
//  int a;
//  a = getLength();
//  if(a>=35)
//  {
   Tracing();
//  }
//  else if (a<35)
//  {
//   Motor_Run(Stop,0);
//    }
}

//测距函数
int getLength()
{
  digitalWrite(TRIG,LOW);
  delayMicroseconds(1);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  int distance = pulseIn(ECHO,HIGH);
  distance /= 58;
  return distance;
}
//移动函数
void Motor_Run(int cmd,int value)
{
//  analogWrite(stepperR_L,value); //设置步数 即设置速度
//  analogWrite(stepperR,value);
//  analogWrite(stepperL,value);
  switch (cmd)
  {
    case Forward:
    Serial.println("Forward"); //端口监视输出状态
    stepperR_L.step(400); 
    break;
    
    case Turn_right:
    Serial.println("Right"); //端口监视输出状态
    stepperL.step(400);
    break;

    case Turn_left:
    Serial.println("left"); //端口监视输出状态
    stepperR.step(400);
    break;

    case Backward:
    Serial.println("Backward"); //端口监视输出状态
    stepperR_L.step(-400); 
    break;

    case Stop:
    Serial.println("Stop"); //端口监视输出状态
    stepperR_L.step(0); 
    break;

  }
  
}

void Tracing()
{
  int data[5];
  data[0]=analogRead(A1);
  data[1]=analogRead(A2);
  data[2]=analogRead(A3);
  data[3]=analogRead(A4);
  data[4]=analogRead(A5);

if((data[2]<(20))&&(data[1]>(600))&&(data[3]>(600))&&(data[0]>(600))&&(data[4]>(600)))
  {
    Motor_Run(Forward,400);
    }
  if(((data[2]>(600))&&(data[1]>(600))&&(data[3]<(20))&&(data[0]>(600))&&(data[4]<(20)))||((data[2]>(600))&&(data[1]>(600))&&(data[3]>(600))&&(data[0]>(600))&&(data[4]<(20)))||((data[2]>(600))&&(data[1]>(600))&&(data[3]<(20))&&(data[0]>(600))&&(data[4]>(600))))
   {
    Motor_Run(Turn_left,400);
    }
  if(((data[2]>(600))&&(data[1]>(600))&&(data[3]>(600))&&(data[0]<(20))&&(data[4]>(600)))||((data[2]>(600))&&(data[1]<(20))&&(data[3]>(600))&&(data[0]<(20))&&(data[4]>(600)))||((data[2]>(600))&&(data[1]<(20))&&(data[3]>(600))&&(data[0]>(600))&&(data[4]>(600))))
   {
    Motor_Run(Turn_right,400);
    }
  if((data[2]>(600))&&(data[1]>(600))&&(data[3]>(600))&&(data[0]>(600))&&(data[4]>(600)))
   {
    Motor_Run(Backward,400);
    }
  if((data[2]<(20))&&(data[1]<(20))&&(data[3]<(20))&&(data[0]<(20))&&(data[4]<(20)))
   {
    Motor_Run(Stop,0);
   }
  
  
  
}
