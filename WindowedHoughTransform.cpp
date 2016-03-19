/*
 * WindowedHoughTransform.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: steven
 */

#include <vector>
#include <utility>
#include <cmath>

#include "cv.h"
#include "highgui.h"

#include "Windows.h"
#include "WindowedHoughTransform.h"
#include "LinePainter.h"
#include "LineClipping.h"

void WindowedHoughLine(cv:: Mat image_src, cv::Mat image_can, std::vector<LineSegment>& lines, int horz, int vert, double rho, double theta, double m, double b)
{
	std::vector<LineSegment> lines_local;

	std::vector< std::vector <cv::Mat> > windows_src, windows_can;
	windows_src = CreateWindows(image_src, horz, vert);
	windows_can = CreateWindows(image_can, horz, vert);

	for(unsigned int i = 0; i < windows_can.size(); i++)
	{
		for(unsigned int j = 0; j < windows_can[i].size(); j++)
		{
			cv::Mat win_src = windows_src[i][j];
			cv::Mat win_can = windows_can[i][j];

			double clutter = ComputeWindowClutter(win_src, 4, 4);
			double cthresh = m*clutter + b;

			std::vector<cv::Vec2f> lines;
			cv::HoughLines(win_can, lines, rho, theta, cthresh, 0, 0);

			cv::Size size; cv::Point ofs;
			win_src.locateROI(size, ofs);
			int x = ofs.x;
			int y = ofs.y;
			int img_rows = size.height;
			int img_cols = size.width;
			int win_rows = win_can.rows;
			int win_cols = win_can.cols;

			cv::Rect roi = cv::Rect(x, y, win_cols, win_rows);

			// Debugging Information
			// printf("(%d,%d,%d,%d,%d,%d)\n", x, y, win_cols, win_rows, img_cols, img_rows);

			for(std::vector<cv::Vec2f>::iterator it = lines.begin(); it != lines.end(); ++it)
			{
				LineSegment line;
				line.SetPts(float((*it)[0]), float((*it)[1]));
				line.AddOffset(cv::Point(x,y));

				if(ClipLine(line, roi))	lines_local.push_back(line);
			}
		}
	}

	lines = lines_local;
}
