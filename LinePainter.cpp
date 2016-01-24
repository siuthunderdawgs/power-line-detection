/*
 * LinePainter.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: steven
 */

#include "LinePainter.h"
#include "LineSegment.h"

#include "cv.h"
#include "highgui.h"

LinePainter::LinePainter() {
	// TODO Auto-generated constructor stub
}

LinePainter::~LinePainter() {
	// TODO Auto-generated destructor stub
}

cv::Scalar LinePainter::GetColor() const
{
	return color_;
}

void LinePainter::SetColor(cv::Scalar color)
{
	color_ = color;
}

std::vector<LineSegment> LinePainter::GetLines() const
{
	return lines_;
}

void LinePainter::SetLines(std::vector<LineSegment> lines)
{
	lines_ = lines;
}

void LinePainter::SetLines(std::vector<cv::Vec2f> lines)
{
	LineSegment line;

	std::vector<cv::Vec2f>::iterator it;
	for(it = lines.begin(); it != lines.end(); ++it)
	{
		line.SetPts(float((*it)[0]), float((*it)[1]));
		AddLines(line);
	}
}

void LinePainter::AddLines(LineSegment line)
{
	lines_.push_back(line);
}

void LinePainter::RstLines()
{
	lines_.clear();
}

cv::Mat* LinePainter::GetImage() const
{
	return image_;
}

void LinePainter::SetImage(cv::Mat* srcImage)
{
	image_ = srcImage;
}

int LinePainter::GetThickness() const
{
	return thickness_;
}

void LinePainter::SetThickness(int thickness)
{
	thickness_ = thickness;
}

void LinePainter::DrawLines()
{
	cv::Point temp_pt1, temp_pt2;
	std::vector<LineSegment>::iterator it;

	if(image_ == 0)
		return;

	for(it = lines_.begin(); it != lines_.end(); ++it)
	{
		temp_pt1 = it->GetPt1();
		temp_pt2 = it->GetPt2();

		cv::line(*image_, temp_pt1, temp_pt2, color_, thickness_);
	}
}


