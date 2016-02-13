/*
 * WindowedHoughTransform.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: steven
 */

#include <vector>
#include <utility>

#include "cv.h"
#include "highgui.h"

#include "LinePainter.h"
#include "Windows.h"
#include "WindowedHoughTransform.h"

void WindowedHoughLine(cv::Mat input, cv::Mat& output, int horz, int vert, double rho, double theta, int thresh)
{
	cv::Mat mask = cv::Mat::zeros(input.size(), CV_8UC3);

	std::vector< std::vector <cv::Mat> > windows_input, windows_mask;
	windows_input = CreateWindows(input, horz, vert);
	windows_mask = CreateWindows(mask, horz, vert);


	for(unsigned int i = 0; i < windows_input.size(); i++)
	{
		for(unsigned int j = 0; j < windows_input[i].size(); j++)
		{
			cv::Mat win_in = windows_input[i][j];
			cv::Mat win_mask = windows_mask[i][j];

			std::vector<cv::Vec2f> lines;
			cv::HoughLines(win_in, lines, rho, theta, thresh, 0, 0);

			LinePainter painter;
			painter.SetImage(&win_mask);
			painter.SetLines(lines);
			painter.DrawLines();
			painter.RstLines();
		}
	}

	output = mask.clone();
}
