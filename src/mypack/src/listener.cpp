#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include <sstream>



turtlesim::Pose::ConstPtr message;


void chatterCallback(const turtlesim::Pose::ConstPtr& msg)
{
  ROS_INFO("I heard: [%f],[%f],[%f],[%f],[%f] \n", msg->x, msg->y, msg->theta, msg->linear_velocity, msg->angular_velocity);

  message->x=msg->x;
  message->y=msg->y;

}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");

  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("turtle1/pose", 1000,chatterCallback);


//  ros::spin();


  //ros::init(argc, argv, "talker");

  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    geometry_msgs::Twist msg;
    msg.linear.x=message->x;
    msg.angular.y=message->y;
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
