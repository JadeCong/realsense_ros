#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

#include <iostream>
#include <pcl/common/common_headers.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/console/parse.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>


using namespace std;

void pointCloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
    // Container for original & filtered data
    pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
    pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
    pcl::PCLPointCloud2 cloud_filtered;
    
    // Save the point cloud to pcd file
    pcl::io::savePCDFile("./realsense_view.pcd", *msg);
    cout<< "publish point_cloud height = " << msg->height << endl;
    cout<< "publish point_cloud width = " << msg->width << endl;
}

int main(int argc, char** argv)
{
    // Initialize ROS node
    ros::init (argc, argv, "Realsense_Save_PCD", ros::init_options::AnonymousName);
    ros::NodeHandle nh;
    
    // Create a ROS subscriber for the point cloud input
    ros::Subscriber sub_point_cloud = nh.subscribe<sensor_msgs::PointCloud2>("/realsense/camera/depth/color/points", 1, pointCloudCallback, ros::TransportHints().reliable().tcpNoDelay());
    
    // Spin simply keeps main function from exiting until this node is stopped
    ros::spin();
}
