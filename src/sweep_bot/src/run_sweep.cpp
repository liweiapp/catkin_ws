#include "Sweep.h"

int main(int argc, char **argv) {
// Initiate new ROS node named "sweep"
    ros::init(argc, argv, "sweep");
// Create new sweep object
    Sweep sweep;
// Start the movement
    sweep.startMoving();
    return 0;
};