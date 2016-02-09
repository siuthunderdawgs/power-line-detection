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
#include "WindowedHoughTransform.h"

void WindowedHoughLine(cv::Mat input, cv::Mat& output, int horz, int vert, double rho, double theta, int thresh)
{
	cv::Mat mask = cv::Mat::zeros(input.size(), CV_8UC3);

	int input_height = input.size().height;
	int input_width = input.size().width;

	std::pair<int,int> range;
	std::vector< std::pair<int, int> > horz_range, vert_range;

	int incr_vert = input_height / vert;
	int incr_horz = input_width / horz;

	for(int i = 0; i < input_height; i += incr_vert)
	{
		range.first = i;

		if(i+incr_vert < input_height)
			range.second = i + incr_vert;
		else
			range.second = input_height;

		vert_range.push_back(range);
	}

	for(int i = 0; i < input_width; i += incr_horz)
	{
		range.first = i;

		if(i+incr_horz < input_width)
			range.second = i + incr_horz;
		else
			range.second = input_width;

		horz_range.push_back(range);
	}

	int N = vert_range.size() * horz_range.size();

	for(int i = 0; i < horz_range.size(); i++)
	{
		for (int j = 0; j < vert_range.size(); j++)
		{
			cv::Point topleft(horz_range[i].first, vert_range[j].first);
			cv::Point bottomright(horz_range[i].second, vert_range[j].second);
			cv::Rect roi(topleft, bottomright);

			cv::Mat win_in = input(roi);
			cv::Mat win_out = mask(roi);

			std::vector<cv::Vec2f> lines;
			cv::HoughLines(win_in, lines, rho, theta, thresh, 0, 0);

			LinePainter painter;
			painter.SetImage(&win_out);
			painter.SetLines(lines);
			painter.DrawLines();
			painter.RstLines();
		}
	}

	output = mask.clone();
}
