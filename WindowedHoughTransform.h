/*
 * WindowedHoughTransform.h
 *
 *  Created on: Feb 6, 2016
 *      Author: steven
 */

#ifndef WINDOWEDHOUGHTRANSFORM_H_
#define WINDOWEDHOUGHTRANSFORM_H_

#include "cv.h"
#include "highgui.h"

void WindowedHoughLine(cv::Mat input, cv::Mat& output, int horz, int vert, double rho, double theta, int thresh);

#endif /* WINDOWEDHOUGHTRANSFORM_H_ */
