#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr &msg) {
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv) {
    // Initiate a new ROS node named "listener"
    ros::init(argc, argv, "listener");
    ros::NodeHandle node;
    // Subscribe to a given top
    ros::Subscriber sub = node.subscribe("chatter", 1000, chatterCallback);
    // Enter a loop, pumping callbac
    ros::spin();
    return 0;
}