#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <vector>
#include <math.h>
#include <assert.h>

#include "LineSegment.h"
#include "LinePainter.h"
#include "LineOverlayPainter.h"
#include "WindowedHoughTransform.h"
#include "Windows.h"

const int slider_max = 200;
int slider;

cv::Size image_size;
cv::Mat image_src;
cv::Mat image_mask;
cv::Mat image_des;
cv::Mat image_can;

cv::Mat window;
cv::Mat window_src;
cv::Mat window_mask;
cv::Mat window_des;

void on_trackbar(int pos, void *)
{
	int thresh = pos + 20;

	window_mask = cv::Scalar(0,0,0);
	window_des = cv::Scalar(0,0,0);

	std::vector<cv::Vec2f> lines;
	cv::HoughLines(window, lines, 1, CV_PI/180, thresh, 0, 0);

	LinePainter painter;
	painter.SetImage(&window_mask);
	painter.SetLines(lines);
	painter.DrawLines();

	LineOverlayPainter opainter;
	opainter.SetImageSrc(&window_src);
	opainter.SetMask(&window_mask);
	opainter.SetImageDes(&window_des);
	opainter.DrawOverlay();

	cv::imshow( "Display Image", window_des );
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
	cv::createTrackbar(" ", "Display Image", &slider, slider_max, on_trackbar);

	std::vector< std::vector<cv::Mat> > windows, windows_src, windows_mask;
	windows = CreateWindows(image_can, 4, 4);
	windows_src = CreateWindows(image_src, 4, 4);
	windows_mask = CreateWindows(image_mask, 4, 4);

	for(unsigned int i = 0; i < windows.size(); i++)
	{
		for(unsigned int j = 0; j < windows[i].size(); j++)
		{
			slider = 0;

			window = windows[i][j].clone();
			window_src = windows_src[i][j].clone();
			window_des = cv::Mat::zeros(window.size(), CV_8UC3);
			window_mask = cv::Mat::zeros(window.size(), CV_8UC3);

			double clutter_win = ComputeWindowClutter(window, 4,4);
			std::cout << "Window [" << i << "][" << j << "]: ";
			std::cout << "Clutter: " << clutter_win << "\n";

			imshow("Display Image", window);
			while(char(cv::waitKey(1)) != ' '){}
		}
	}

	std::cout << "Done!";
	while(char(cv::waitKey(1)) != 'q'){}

	return 0;
}
