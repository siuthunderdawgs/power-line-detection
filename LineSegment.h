/*
 * LineSegment.h
 *
 *  Created on: Jan 23, 2016
 *      Author: steven
 */

#ifndef LINESEGMENT_H_
#define LINESEGMENT_H_

#include "cv.h"
#include "highgui.h"

class LineSegment {
public:
	LineSegment();
	LineSegment(cv::Point pt1, cv::Point pt2);
	LineSegment(float rho, float theta);
	virtual ~LineSegment();

	void SetPt1(cv::Point pt1);
	void SetPt2(cv::Point pt2);
	void SetPts(cv::Point pt1, cv::Point pt2);
	void SetPts(float rho, float theta);

	cv::Point GetPt1();
	cv::Point GetPt2();

private:
	cv::Point pt1_;
	cv::Point pt2_;
};

#endif /* LINESEGMENT_H_ */
