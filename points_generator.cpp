#include "ros/ros.h"
#include "AR_week5_test/cubic_traj_params.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv)
{
    // Initialize ROS node
    ros::init(argc, argv, "points_generator");
    ros::NodeHandle nh;

    // Initialize publisher for cubic_traj_params topic
    ros::Publisher pub = nh.advertise
    <AR_week5_test::cubic_traj_params>("points", 0);

    // Seed random number generator
    srand(time(0));

    // Set loop rate
    ros::Rate rate(0.05); // 0.05Hz or once every 20 seconds

    while (ros::ok())
    {
        // Generate random numbers
        AR_week5_test::cubic_traj_params msg;
        msg.p0 = (double)rand() / RAND_MAX * 20 - 10;
        msg.pf = (double)rand() / RAND_MAX * 20 - 10;
        msg.v0 = (double)rand() / RAND_MAX * 20 - 10;
        msg.vf = (double)rand() / RAND_MAX * 20 - 10;
        msg.t0 = 0;
        msg.tf = msg.t0 + round((double)rand() / RAND_MAX * 5 + 5);

        // Publish message
        ROS_INFO_STREAM(msg);
        pub.publish(msg);

        // Sleep according to loop rate
        rate.sleep();
    }

    return 0;
}
