#include <ros.h>
#include "MPU9250.h"
#include <Arduino.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>
Servo myservo1;

Servo myservo2;

MPU9250 mpu;
int h=90;
int k1=90;
int k2=90;
float x,y;
int pos=0;
int pos1=0;
int pos2=0;
ros::NodeHandle nh;
void aaa(const geometry_msgs::Twist& msg1)
{
  x=msg1.linear.x;
  y=msg1.linear.y;
 // if (x>0){
 // for ( int i=h;i<= (h+x);i++ )
  //{
//  if(y<5)
     {myservo2.write(h-x);
    myservo1.write(h+y);}

   // delay(20);
  //}
  //}
  //else 
  //{
   // for ( int i=h;i>= (h+x);i-- )
  //{
   
   // delay(20);
  //}
  //}
  /*if (y>0){
  for ( int i=h;i<= (h+y);i++ )
  {
    myservo1.write(i);
    delay(20);
  }
  }
  else 
  {
    for ( int i=h;i>= (h+y);i-- )
  {
    myservo1.write(i);
    delay(20);
  }
  }*/
 /* myservo1.write(x+90);
  delay(20);
  
  
 // for (pos2 =0; pos2 <= y; pos2 += 1) {
  myservo2.write(y);
  delay(20);
//  }*/
  
}

ros::Subscriber<geometry_msgs::Twist> GO("chatter",aaa);
geometry_msgs::Twist msg;
ros::Publisher m("chatter1",& msg);

void reset1()
{int c=0;
  while(c<3){
    for (pos = 0; pos <=90; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);
    }
      for (pos = 90; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15 ms for the servo to reach the position
  }
    c++;
    }// waits 15 ms for the servo to reach the position
  }

void reset2()
{int c=0;
  while(c<3){
    for (pos = 0; pos <=90; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);
    }
      for (pos = 90; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15 ms for the servo to reach the position
  }
    c++;
    }// waits 15 ms for the servo to reach the position
  }


  
  
  
  
void setup() {
/*
 * pinMode(,);
 */
 myservo1.attach(2);
 myservo2.attach(3);
 myservo1.write(90);
 myservo2.write(90);
 //reset1();
// reset2();
 Wire.begin();
 delay(2000);
 if (!mpu.setup(0x68)) {while (1){}}
  nh.initNode();
  nh.advertise(m);
  nh.subscribe(GO);
}
void loop() {
  
   nh.subscribe(GO);
            mpu.update();
            msg.linear.x=mpu.getPitch();
            msg.linear.y=mpu.getRoll(); 
            m.publish( &msg);
            nh.spinOnce();
            delay(10);
    }
