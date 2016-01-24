/*
 * LineSegment.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: steven
 */

#include "LineSegment.h"

#include "cv.h"
#include "highgui.h"

LineSegment::LineSegment()
{
	pt1_ = cv::Point(0,0);
	pt2_ = cv::Point(0,0);
}

LineSegment::LineSegment(cv::Point pt1, cv::Point pt2)
{
	SetPts(pt1, pt2);
}

LineSegment::LineSegment(float rho, float theta)
{
	SetPts(rho,theta);
}

LineSegment::~LineSegment() {
	// TODO Auto-generated destructor stub
}

void LineSegment::SetPt1(cv::Point pt1)
{
	pt1_ = pt1;
}

void LineSegment::SetPt2(cv::Point pt2)
{
	pt2_ = pt2;
}

void LineSegment::SetPts(cv::Point pt1, cv::Point pt2)
{
	pt1_ = pt1;
	pt2_ = pt2;
}

void LineSegment::SetPts(float rho, float theta)
{
    double a = cos(theta);
    double b = sin(theta);
    double x0 = a*rho;
    double y0 = b*rho;

    pt1_.x = cvRound(x0 + 1000*(-b));
    pt1_.y = cvRound(y0 + 1000*(a));
    pt2_.x = cvRound(x0 - 1000*(-b));
    pt2_.y = cvRound(y0 - 1000*(a));
}

cv::Point LineSegment::GetPt1()
{
	return pt1_;
}

cv::Point LineSegment::GetPt2()
{
	return pt2_;
}
