#include <ros/ros.h>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.h>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;

cv_bridge::CvImagePtr cv_ptr;
using namespace cv;


int main(int argc , char ** argv)
{
    ros::init(argc , argv , "publisher");

    ros::NodeHandle n;    //初始化节点
    VideoCapture cap;
    
    std::string  path;
    n.param<std::string>("/path",path,"/home/wzr/2022-05-11 21-47-05.mkv"); //视频路径
    
    cap.open(path);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,1980);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,1080); //设置图像分辨率
    cap.set(CV_CAP_PROP_FPS, 30); //读取频率
    Mat frame;
    ROS_INFO("SUCCESS, publishing images.");

    ros::Publisher vedio_pub = n.advertise<cv_bridge::CvImage>("/image_raw", 1000); //定义发布图像的topic
    ros::Rate loop_rate(30);  //设置发布频率

    


    while (ros::ok())
    {
        cap >> frame;
        if (frame.empty()) 
        {   
            ROS_INFO("Finsh publishing.");
            return 0;
        }
        //cv::imshow("source",frame);
        sensor_msgs::ImagePtr raw_image = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        vedio_pub.publish(raw_image);
        loop_rate.sleep();
        //cv::waitKey(10);
    }
    ros::spin();
    return 0;
}
