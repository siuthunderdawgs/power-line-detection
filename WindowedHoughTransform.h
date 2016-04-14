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

#include "LineSegment.h"

void WindowedHoughLine(cv:: Mat image_src, cv::Mat image_can, std::vector<LineSegment>& lines, int horz, int vert, double rho, double theta, double m, double b);

#endif /* WINDOWEDHOUGHTRANSFORM_H_ */
