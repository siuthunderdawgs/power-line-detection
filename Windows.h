/*
 * Windows.h
 *
 *  Created on: Feb 12, 2016
 *      Author: steven
 */

#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <vector>

#include "cv.h"
#include "highgui.h"

std::vector< std::vector<cv::Mat> > CreateWindows(cv::Mat input, int horz, int vert);
cv::Mat ComputeWindowsStatistics(std::vector< std::vector<cv::Mat> > windows);
void PrintWindowsStatistics(std::vector< std::vector<cv::Mat> > windows);

#endif /* WINDOWS_H_ */
