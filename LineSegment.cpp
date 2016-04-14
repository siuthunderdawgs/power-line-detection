/*
 * LineSegment.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: steven
 */

#include "LineSegment.h"

#include <cstdlib>

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

void LineSegment::AddOffset(cv::Point pt0)
{
	pt1_.x = pt0.x + pt1_.x;
	pt1_.y = pt0.y + pt1_.y;
	pt2_.x = pt0.x + pt2_.x;
	pt2_.y = pt0.y + pt2_.y;
}

cv::Point LineSegment::GetPt1()
{
	return pt1_;
}

cv::Point LineSegment::GetPt2()
{
	return pt2_;
}

void LineSegment::GetHesseNormalForm(double& rho, double& theta)
{
	double rise = pt2_.y - pt1_.y;
	double run = pt2_.x - pt1_.x;
	double slope = rise/run;

	double phi = atan(fabs(slope));

	if(slope >= 0)
	{
		theta = M_PI/2 - phi;
	}
	else
	{
		theta = M_PI - (M_PI/2-phi);
	}

	rho = pt2_.x*cos(theta) + pt2_.y*sin(theta);
}
