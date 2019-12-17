#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

class Sweep {
public:
// Tunable parameters
    const double FORWARD_SPEED = 0.5;
    const double MIN_SCAN_ANGLE = -30.0 / 180 * M_PI;
    const double MAX_SCAN_ANGLE = +30.0 / 180 * M_PI;
// Should be smaller than sensor_msgs::LaserScan::range_max
    const float MIN_DIST_FROM_OBSTACLE = 0.5;

    Sweep();

    void startMoving();

private:
    ros::NodeHandle node;
    ros::Publisher commandPub; // Publisher to the robot's velocity command topic
    ros::Subscriber laserSub; // Subscriber to the robot's laser scan topic
    bool keepMoving; // Indicates whether the robot should continue moving
    void moveForward();
    void moveTurn();
    void scanCallback(const sensor_msgs::LaserScan::ConstPtr &scan);
};