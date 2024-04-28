#include "ros/ros.h"
#include "AR_week5_test/ComputeCubicTraj.h"
#include <Eigen/Dense> // Eigen library for matrix operations

bool handle_compute_cubic_traj(AR_week5_test::compute_cubic_traj::Request &req,
                               AR_week5_test::compute_cubic_traj::Response &res)
{
    // create 2 matrices
    auto params = req.params;
    ROS_INFO("Accepting Computation Request");
    Eigen::Matrix4d A;
    A << 1, params.t0, std::pow(params.t0, 2), std::pow(params.t0, 3),
         0, 1, 2 * params.t0, 3 * std::pow(params.t0, 2),
         1, params.tf, std::pow(params.tf, 2), std::pow(params.tf, 3),
         0, 1, 2 * params.tf, 3 * std::pow(params.tf, 2);

    Eigen::Vector4d C;
    C << params.p0, params.v0, params.pf, params.vf;

    // compute B = C * A.inverse()
    Eigen::Vector4d result = A.inverse() * C;
    ROS_INFO("Returning [%f, %f, %f, %f]", result[0], result[1], result[2], result[3]);

    res.result.p0 = result[0];
    res.result.v0 = result[1];
    res.result.pf = result[2];
    res.result.vf = result[3];
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "compute_cubic_coeffs");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("compute_service", handle_compute_cubic_traj);
    ROS_INFO("Ready to Compute Cubic Coefficients.");
    ros::spin();

    return 0;
}
