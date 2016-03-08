/*
 * PowerLineDetection.h
 *
 *  Created on: Mar 7, 2016
 *      Author: steven
 */

#ifndef POWERLINEDETECTION_H_
#define POWERLINEDETECTION_H_

#include "cv.h"
#include "highgui.h"

void PowerLineDetection(cv::Mat input, cv::Mat& output, double p1_m, double p1_b, double p2);

#endif /* POWERLINEDETECTION_H_ */
