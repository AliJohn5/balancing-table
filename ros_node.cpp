#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "math.h"

float x,x2;
float y,y2;
float k1,k2,k3,k4,k5,k6,kall,alss;
float a,b,c,c1,ka1,ka2,ka3,ka4,ka5,ka,a1,b1;

void chatterCallback(const geometry_msgs::Twist msg)
{
  x=msg.linear.x;
  y=msg.linear.y;
  
  
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("chatter", 1000);
  ros::Subscriber sub = n.subscribe("chatter1", 1000, chatterCallback);

  ros::Rate loop_rate(10);
  //ros::spin();
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    geometry_msgs::Twist msg1;
    /*
write the publishing
*/
//x=phay
//y=theta

///first equ
x=x*(M_PI/180);
y=y*(M_PI/180);

     k1 =(12*(sin(x)*cos(y))-10*(cos(x)*cos(y))-10);
     k2 =(12*(cos(x))+10*(sin(x))-12);
     k3 = (2*sin(y)*5*cos(x)-2*sin(y)*6*sin(x));
     b=20* k1;
     a=20* k3;
     kall = pow(k1,2)+pow(k2,2)+pow(k3,2)-500+100;
     c =-kall;
     alss = sqrt(pow(a,2)+pow(b,2)-pow(c,2));
     x2= atan2(c,alss)-atan2(a,b);
     x2 =x2 *(180/M_PI);

///second eq
ka1 = (10*cos(x)*sin(y)-12*cos(y)+12)*(10*cos(x)*sin(y)-12*cos(y)+12);
ka2 = (12*sin(y)+10*cos(x)*cos(y)+10);//
ka4 = 100*sin(x);
ka5 = 500;
ka =( ka1+(ka2*ka2)-ka5+100+(ka4*ka4))/2;//
a1 = ka4;//
b1 = -10*ka2;//
c1 = -ka;//
float g = +sqrt ((a1*a1)+(b1*b1)-(c1*c1));//
y2 = atan2(c1,g)-atan2(a1,b1);//
    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
     y2=y2*(180/M_PI);
 if (x2>0)
 x2=x2-180;
 else
 x2=x2+180    ;
  if (y2>0)
 y2=y2-180;
 else
 y2=y2+180    ;
     msg1.linear.x=x2;
     msg1.linear.y=y2;
     x=x*(180/M_PI);
     y=y*(180/M_PI);
     ROS_INFO("theta = [ %f ]",x);
     ROS_INFO("alpha = [ %f ]",y);
     ROS_INFO("thetaM = [ %f ]",x2);
     ROS_INFO("alphaM = [ %f ]\n",y2);
     chatter_pub.publish(msg1);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
