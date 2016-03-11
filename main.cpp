#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "LineSegment.h"
#include "LinePainter.h"
#include "LineOverlayPainter.h"
#include "WindowedHoughTransform.h"
#include "PowerLineDetection.h"


const int slider_max = 200;
int slider;

cv::Mat image_src;

void on_trackbar(int pos, void *)
{
	int thresh = pos + 20;

	cv::Mat image_mask;
	//PowerLineDetection(image_src, image_mask, 0.7971, 15.9820, thresh);
	PowerLineDetection(image_src, image_mask, 0.5, 10, 200);

	cv::Mat image_des;
	cv::addWeighted(image_src, 0.8, image_mask, 0.2, 0, image_des);

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

	on_trackbar(0, (void *)0);
	slider = 0;

	cv::createTrackbar("Hough Threshold = Position + 20", "Display Image", &slider, slider_max, on_trackbar);
	while(char(cv::waitKey(1)) != 'q'){}

	return 0;
}
