/*
 * Filters.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: steven
 */

#include "cv.h"
#include "highgui.h"

#include <vector>
#include <algorithm>

#include "Filters.h"
#include "LineSegment.h"
#include "LinePainter.h"

void FilterBackgroundContinuity(std::vector<LineSegment> input, std::vector<LineSegment>& output, cv::Mat image_src, double offset_mult, double thresh_mult)
{
	std::vector<LineSegment> output_local;

	for(std::vector<LineSegment>::iterator it = input.begin(); it != input.end(); ++it)
	{
		double rho, theta;
		LineSegment lineo = *it;
		lineo.GetHesseNormalForm(rho, theta);

		double vx = 1; double vy = vx*tan(theta);
		double vm = sqrt(pow(vx,2)+pow(vy,2));

		vx = vx/vm; vx = fabs(offset_mult*vx);
		vy = vy/vm; vy = fabs(offset_mult*vy);

		LineSegment lines[3] = {lineo, lineo, lineo};
		if(theta <= M_PI/2)
		{
			lines[0].AddOffset(cv::Point(-vx,-vy));
			lines[2].AddOffset(cv::Point( vx, vy));
		}
		else
		{
			lines[0].AddOffset(cv::Point( vx,-vy));
			lines[2].AddOffset(cv::Point(-vx, vy));
		}

		double vmean[3], vstddev[3];
		for(int i = 0; i < 3; i++)
		{
			cv::Mat maskC1, maskC3;
			maskC3 = cv::Mat::zeros(image_src.size(), CV_8UC3);

			LinePainter painter;
			painter.SetImage(&maskC3);
			painter.SetColor(cv::Scalar(255,255,255));
			painter.SetThickness(1);
			painter.AddLines(lines[i]);
			painter.DrawLines();
			painter.RstLines();

			cv::cvtColor(maskC3, maskC1, CV_BGR2GRAY);
			cv::threshold(maskC1, maskC1, 200, 255, cv::THRESH_BINARY);

			cv::Mat mmean, mstddev;
			cv::meanStdDev(image_src, mmean, mstddev, maskC1);

			vmean[i] = mmean.at<double>(0,0);
			vstddev[i] = mstddev.at<double>(0,0);
		}

		float fthresh = (vstddev[0] >= vstddev[2]) ? vstddev[0] : vstddev[2];

		if(fabs(vmean[0] - vmean[2]) <= thresh_mult*fthresh)
			output_local.push_back(*it);

		// Debugging Code
		// DebugFilterBackgroundContinuity(image_src, lines, vmean, vstddev);
	}

	output = output_local;
}

void FilterKnownAngle(std::vector<LineSegment> input, std::vector<LineSegment>& output, double angle, double angle_thresh)
{
	std::vector<LineSegment> output_local;

	for(std::vector<LineSegment>::iterator it = input.begin(); it != input.end(); ++it)
	{
		double rho, theta;
		LineSegment lineo = *it;
		lineo.GetHesseNormalForm(rho, theta);

		if(angle - angle_thresh < theta && theta < angle + angle_thresh)
		{
			output_local.push_back(*it);
		}
	}

	output = output_local;
}

void FilterMedianAngle(std::vector<LineSegment> input, std::vector<LineSegment>& output, double angle_thresh)
{
	std::vector<LineSegment> output_local;

	std::vector<double> angles;
	for(std::vector<LineSegment>::iterator it = input.begin(); it != input.end(); ++it)
	{
		double rho, theta;
		it->GetHesseNormalForm(rho, theta);

		angles.push_back(theta);
	}
	double median = GetMedian(angles);

	for(std::vector<LineSegment>::iterator it = input.begin(); it != input.end(); ++it)
	{
		double rho, theta;
		it->GetHesseNormalForm(rho, theta);

		if(median - angle_thresh < theta && theta < median + angle_thresh)
		{
			output_local.push_back(*it);
		}
	}

	output = output_local;
}

void DebugFilterBackgroundContinuity(cv::Mat image_src, LineSegment* lines, double* vmean, double* vstddev)
{
	cv::Mat mask;
	mask = cv::Mat::zeros(image_src.size(), CV_8UC3);

	LinePainter painter;
	painter.SetImage(&mask);

	painter.SetColor(cv::Scalar(255,255,255));
	painter.AddLines(lines[1]);
	painter.DrawLines();
	painter.RstLines();

	painter.SetColor(cv::Scalar(255,0,0));
	painter.AddLines(lines[0]);
	painter.DrawLines();
	painter.RstLines();

	painter.SetColor(cv::Scalar(0,0,255));
	painter.AddLines(lines[2]);
	painter.DrawLines();
	painter.RstLines();

	for(int k = 0; k < 3; k++)
	{
		printf("vmean[%d] = %g\n", k, vmean[k]);
		printf("vstddev[%d] = %g\n", k, vstddev[k]);
	}

	cv::imshow("Lines", mask);
	cv::waitKey();
}

double GetMedian(std::vector<double> input)
{
	double median;
	unsigned int size = input.size();

	std::sort(input.begin(), input.end());

	if (size  % 2 == 0)
	{
		median = (input[size / 2 - 1] + input[size / 2]) / 2;
	}
	else
	{
		median = input[size / 2];
	}

	return median;
}
