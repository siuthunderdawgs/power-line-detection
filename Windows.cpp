/*
 * Windows.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: steven
 */

#include <vector>
#include <iostream>
#include "assert.h"

#include "cv.h"
#include "highgui.h"

#include "Windows.h"

std::vector< std::vector<cv::Mat> > CreateWindows(cv::Mat input, int horz, int vert)
{
	std::vector<cv::Mat> row;
	std::vector< std::vector<cv::Mat> > windows;

	int input_height = input.size().height;
	int input_width = input.size().width;

	std::vector< std::pair<int, int> > horz_range, vert_range;

	int incr_vert = input_height / vert;
	int incr_horz = input_width / horz;

	for(int i = 0; i < vert; i++)
	{
		std::pair<int,int> range;
		range.first = i*incr_vert;

		if((i+2)*incr_vert <= input_height)
			range.second = (i+1)*incr_vert;
		else
			range.second = input_height;

		vert_range.push_back(range);
	}

	for(int i = 0; i < horz; i++)
	{
		std::pair<int,int> range;
		range.first = i*incr_horz;

		if((i+2)*incr_horz <= input_width)
			range.second = (i+1)*incr_horz;
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

cv::Mat ComputeWindowsStatistics(std::vector< std::vector<cv::Mat> > windows)
{
	cv::Mat stats = cv::Mat::zeros(windows[0].size(), windows.size(), CV_8UC2);

	for(int i = 0; i < windows.size(); i++)
	{
		for(int j = 0; j < windows[i].size(); j++)
		{
			cv::Mat mean;
			cv::Mat stddev;

			cv::meanStdDev(windows[i][j], mean, stddev);

			int meanval = int(mean.at<double>(0,0));
			int stddevval = int(stddev.at<double>(0,0));

			stats.at<cv::Vec2b>(i,j)[0] = meanval;
			stats.at<cv::Vec2b>(i,j)[1] = stddevval;
		}
	}

	return stats;
}

void PrintWindowsStatistics(std::vector< std::vector<cv::Mat> > windows)
{
	cv::Mat stats = ComputeWindowsStatistics(windows);

	for(unsigned int i = 0; i < windows.size(); i++)
	{
		for(unsigned int j = 0; j < windows[i].size(); j++)
		{
			double mean = stats.at<cv::Vec2b>(i,j)[0];
			double stddev = stats.at<cv::Vec2b>(i,j)[1];

			std::cout << "Window [" << i << "][" << j << "]: ";
			std::cout << "Mean: " << mean << " ";
			std::cout << "Std Dev: " << stddev << "\n";
		}
	}
}
