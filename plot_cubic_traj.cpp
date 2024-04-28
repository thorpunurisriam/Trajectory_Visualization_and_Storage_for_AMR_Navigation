#include "ros/ros.h"
#include "AR_week5_test/cubic_traj_coeffs.h"
#include "AR_week5_test/position_trajectory.h"
#include "AR_week5_test/velocity_trajectory.h"
#include "AR_week5_test/acceleration_trajectory.h"
#include <cmath>

void callback(const AR_week5_test::cubic_traj_coeffs::ConstPtr& data)
{
    // Publishing initialised
    ros::NodeHandle nh;
    ros::Publisher pub1 = nh.advertise
    <AR_week5_test::position_trajectory>("position_trajectory", 0);
    ros::Publisher pub2 = nh.advertise
    <AR_week5_test::position_trajectory>("position_trajectory", 0);
    ros::Publisher pub2 = nh.advertise
    <AR_week5_test::acceleration_trajectory>("acceleration_trajectory", 0);

    // Initialise messages
    AR_week5_test::position_trajectory msg1;
    AR_week5_test::velocity_trajectory msg2;
    AR_week5_test::acceleration_trajectory msg3;

    // Calculate trajectories
    msg1.trj = data->a0 + data->a1 * data->tf + data->a2 * std::pow(data->tf, 2) + data->a3 * std::pow(data->tf, 3);
    msg2.trj = data->a1 + 2 * data->a2 * data->tf + 3 * data->a3 * std::pow(data->tf, 2);
    msg3.trj = 2 * data->a2 + 6 * data->a3 * data->tf;

    // Publish messages
    ROS_INFO("Publishing trajectories %f, %f, %f", msg1.trj, msg2.trj, msg3.trj);
    pub1.publish(msg1);
    pub2.publish(msg2);
    pub3.publish(msg3);
}

int main(int argc, char **argv)
{
    // Initialize new node
    ros::init(argc, argv, "plot_cubic_traj");
    ros::NodeHandle nh;

    // Subscribe to cubic_traj_coeffs and send data to callback
    ros::Subscriber sub = nh.subscribe("coeffs", 0, callback);

    // Prevent from dying
    ros::spin();

    return 0;
}
