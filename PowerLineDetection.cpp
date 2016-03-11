/*
 * PowerLineDetection.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: steven
 */

#include "cv.h"
#include "highgui.h"

#include "PowerLineDetection.h"
#include "WindowedHoughTransform.h"
#include "LinePainter.h"

void PowerLineDetection(cv::Mat input, cv::Mat& output, double p1_m, double p1_b, double p2)
{
	cv::Size image_size = input.size();
	cv::Mat image_src = input.clone();

	cv::Mat image_mask = cv::Mat::zeros(image_size, CV_8UC3);
	cv::Mat image_des = cv::Mat::zeros(image_size, CV_8UC3);

	cv::Mat image_can = cv::Mat::zeros(image_size, CV_8UC3);
	cv::Canny(image_src, image_can, 50, 90, 3);
	cv::imshow("Canny", image_can);

	WindowedHoughLine(image_can, image_mask, 4, 4, 1, CV_PI/180, 0, p1_m, p1_b);
	cv::imshow("hough", image_mask);

	cv::Mat temp;
	std::vector<cv::Vec2f> lines_temp;

	cvtColor(image_mask, temp, CV_BGR2GRAY);
	temp.copyTo(image_mask);

	cv::HoughLines(image_mask, lines_temp, 1, CV_PI/180, p2, 0, 0);

	image_mask = cv::Mat::zeros(image_mask.size(), CV_8UC3);

	LinePainter painter;
	painter.SetImage(&image_mask);
	painter.SetThickness(2);
	painter.SetColor(cv::Scalar(255,255,255));
	painter.SetLines(lines_temp);
	painter.DrawLines();
	painter.RstLines();

	output = image_mask.clone();
}
