#include "Sweep.h"
#include "geometry_msgs/Twist.h"

bool isObstacleInFront = false;

Sweep::Sweep() {
    keepMoving = true;

// Advertise a new publisher for the robot's velocity command topic
    commandPub = node.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
// Subscribe to the simulated robot's laser scan topic
    laserSub = node.subscribe("/scan", 1, &Sweep::scanCallback, this);
}

// Send a velocity command
void Sweep::moveForward() {
    geometry_msgs::Twist msg; // The default constructor will set all commands to 0
    msg.linear.x = FORWARD_SPEED;
    msg.angular.z = 0;
    commandPub.publish(msg);
}

// 转向
void Sweep::moveTurn() {
    geometry_msgs::Twist msg;
    msg.linear.x = 0;
    msg.angular.z = 2.36;
    commandPub.publish(msg);
}

// Process the incoming laser scan message
void Sweep::scanCallback(const sensor_msgs::LaserScan::ConstPtr &scan) {

// Find the closest range between the defined minimum and maximum angles
    int minIndex = ceil((MIN_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);
    int maxIndex = floor((MAX_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);
    for (int currIndex = minIndex + 1; currIndex <= maxIndex; currIndex++) {
        if (scan->ranges[currIndex] < MIN_DIST_FROM_OBSTACLE) {
            isObstacleInFront = true;
            break;
        }
    }


}

void Sweep::startMoving() {
    ros::Rate rate(10);
    ROS_INFO("Start moving");
// Keep spinning loop until user presses Ctrl+C or the robot got too close to an obstacle
    while (ros::ok() && keepMoving) {
        moveForward();
        if (isObstacleInFront) {
            ROS_INFO("Turn!");
            moveTurn();
        }
        moveForward();
// Need to call this function often to allow ROS to process incoming messages
        ros::spinOnce();
        rate.sleep();
    }
}