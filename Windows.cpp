/*
 * Windows.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: steven
 */

#include <vector>

#include "cv.h"
#include "highgui.h"

#include "Windows.h"

std::vector< std::vector<cv::Mat> > CreateWindows(cv::Mat input, int horz, int vert)
{
	std::vector<cv::Mat> row;
	std::vector< std::vector<cv::Mat> > windows;

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

	for(unsigned int i = 0; i < horz_range.size(); i++)
	{
		for(unsigned int j = 0; j < vert_range.size(); j++)
		{
			cv::Point topleft(horz_range[i].first, vert_range[j].first);
			cv::Point bottomright(horz_range[i].second, vert_range[j].second);
			cv::Rect roi(topleft, bottomright);

			cv::Mat win = input(roi);
			row.push_back(win);
		}
		windows.push_back(row);
		row.clear();
	}

	return windows;
}


