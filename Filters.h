/*
 * Filters.h
 *
 *  Created on: Mar 18, 2016
 *      Author: steven
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "cv.h"
#include "highgui.h"

#include <vector>

#include "LineSegment.h"

void FilterBackgroundContinuity(std::vector<LineSegment> input, std::vector<LineSegment>& output, cv::Mat image_src, double offset_mult, double thresh_mult);
void FilterKnownAngle(std::vector<LineSegment> input, std::vector<LineSegment>& output, double angle, double angle_thresh);
void FilterMedianAngle(std::vector<LineSegment> input, std::vector<LineSegment>& output, double angle_thresh);

void DebugFilterBackgroundContinuity(cv::Mat image_src, LineSegment* lines, double* vmean, double* vstddev);

double GetMedian(std::vector<double> input);

#endif /* FILTERS_H_ */
