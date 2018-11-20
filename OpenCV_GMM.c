//  基于混合高斯模型的运动目标检测  

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>


int main(int argc, char** argv)
{
	std::string videoFile = "../test.avi";

	cv::VideoCapture capture;
	capture.open(videoFile);

	if (!capture.isOpened())
	{
		std::cout<<"read video failure"<<std::endl;
		return -1;
	}


	cv::BackgroundSubtractorMOG2 mog;

	cv::Mat foreground;
	cv::Mat background;

	cv::Mat frame;
	long frameNo = 0;
	while (capture.read(frame))
	{
		++frameNo;

		std::cout<<frameNo<<std::endl;

		// 运动前景检测，并更新背景
		mog(frame, foreground, 0.001);       
		
		// 腐蚀
		cv::erode(foreground, foreground, cv::Mat());
		
		// 膨胀
		cv::dilate(foreground, foreground, cv::Mat());

		mog.getBackgroundImage(background);   // 返回当前背景图像

		cv::imshow("video", foreground);
		cv::imshow("background", background);


		if (cv::waitKey(25) > 0)
		{
			break;
		}
	}
	


	return 0;
}
