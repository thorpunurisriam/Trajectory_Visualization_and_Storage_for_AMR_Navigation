#include "ros/ros.h"
#include "AR_week5_test/ComputeCubicTraj.h"
#include "AR_week5_test/cubic_traj_params.h"
#include "AR_week5_test/cubic_traj_coeffs.h"

void callback(const AR_week5_test::cubic_traj_params::ConstPtr& data)
{
    // Publishing initialized
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise
    <AR_week5_test::cubic_traj_coeffs>("coeffs", 0);

    try {
        // Try to connect to service
        ros::ServiceClient compute_client = nh.serviceClient
        <AR_week5_test::ComputeCubicTraj>("compute_service");

        // Compute trajectories using data obtained from the subscriber
        AR_week5_test::compute_cubic_traj srv;
        srv.request.params = *data;

        if (compute_client.call(srv))
        {
            // Construct a message
            AR_week5_test::cubic_traj_coeffs msg;
            msg.a0 = srv.response.a0;
            msg.a1 = srv.response.a1;
            msg.a2 = srv.response.a2;
            msg.a3 = srv.response.a3;
            msg.t0 = data->t0;
            msg.tf = data->tf;

            // Publish obtained data
            ROS_INFO("%f %f %f %f %f %f", msg.a0, msg.a1, msg.a2, msg.a3, msg.t0, msg.tf);
            pub.publish(msg);
        }
        else
        {
            ROS_ERROR("Failed to call service compute_service");
        }
    }
    catch (ros::Exception &e)
    {
        ROS_ERROR("Service call failed: %s", e.what());
    }
}

void cubic_traj_planner()
{
    // Initialize new node
    ros::init(argc, argv, "cubic_traj_planner");
    ros::NodeHandle nh;

    // Subscribe to cubic_traj_params and send data to callback
    ros::Subscriber sub = nh.subscribe("points", 0, callback);

    // Prevent from dying
    ros::spin();
}

int main(int argc, char **argv)
{
    cubic_traj_planner();
    return 0;
}
