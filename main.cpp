#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "LineSegment.h"
#include "LinePainter.h"
#include "LineOverlayPainter.h"
#include "WindowedHoughTransform.h"


const int slider_max = 200;
int slider;

cv::Size image_size;
cv::Mat image_src;
cv::Mat image_mask;
cv::Mat image_des;
cv::Mat image_can;

void on_trackbar(int pos, void *)
{
	int thresh = pos + 20;

	image_mask = cv::Scalar(0,0,0);
	image_des = cv::Scalar(0,0,0);

	/*
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(image_can, lines, 1, CV_PI/180, thresh, 0, 0);

	LinePainter painter;
	painter.SetImage(&image_mask);
	painter.SetLines(lines);
	painter.DrawLines();
	*/

	WindowedHoughLine(image_can, image_mask, 4, 4, 1, CV_PI/180, 0, 0.7971, 15.9820);

	LineOverlayPainter opainter;
	opainter.SetImageSrc(&image_src);
	opainter.SetMask(&image_mask);
	opainter.SetImageDes(&image_des);
	opainter.DrawOverlay();

	cv::imshow( "Display Image", image_des );
}


int main(int argc, char** argv)
{
	const char* filename;

	if(argc >= 2)
		filename = argv[1];
	else
		filename = "image.jpg";

	image_src = cv::imread(filename);

	if(image_src.empty())
	{
	 std::cout << "ERROR: Cannot open " << filename << std::endl;
	 return -1;
	}

	image_size = image_src.size();

	image_mask = cv::Mat::zeros(image_size, CV_8UC3);
	image_des = cv::Mat::zeros(image_size, CV_8UC3);

	image_can = cv::Mat::zeros(image_size, CV_8UC3);
	cv::Canny(image_src, image_can, 50, 200, 3);

	cv::namedWindow( "Display Image");
	cv::imshow( "Display Image", image_can );

	slider = 0;

	cv::createTrackbar("Hough Threshold = Position + 20", "Display Image", &slider, slider_max, on_trackbar);
	while(char(cv::waitKey(1)) != 'q'){}

	return 0;
}
