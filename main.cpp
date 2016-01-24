#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <math.h>

#include "LineSegment.h"
#include "LinePainter.h"
#include "LineOverlayPainter.h"

int main(int argc, char** argv)
{
	const char* filename;

	if(argc >= 2)
		filename = argv[1];
	else
		filename = "image.jpg";

	cv::Mat image_src = cv::imread(filename);

	if(image_src.empty())
	{
	 std::cout << "ERROR: Cannot open " << filename << std::endl;
	 return -1;
	}


	cv::Size image_size = image_src.size();

	cv::Mat image_mask = cv::Mat::zeros(image_size, CV_8UC3);
	cv::Mat image_des = cv::Mat::zeros(image_size, CV_8UC3);

	LineSegment line1;
	line1.SetPt1(cv::Point(0,0));
	line1.SetPt2(cv::Point(250,250));

	LineSegment line2;
	line2.SetPts(float(125),float(45*M_PI/180));

	LinePainter painter;
	painter.SetImage(&image_mask);
	painter.AddLines(line1);
	painter.AddLines(line2);
	painter.DrawLines();

	LineOverlayPainter opainter;
	opainter.SetImageSrc(&image_src);
	opainter.SetMask(&image_mask);
	opainter.SetImageDes(&image_des);
	opainter.DrawOverlay();


	cv::namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Display Image", image_des );

	cv::waitKey(0);

	return 0;
}

