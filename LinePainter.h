/*
 * LinePainter.h
 *
 *  Created on: Jan 23, 2016
 *      Author: steven
 */

#ifndef LINEPAINTER_H_
#define LINEPAINTER_H_

#include <vector>

#include "cv.h"
#include "highgui.h"

#include "LineSegment.h"

class LinePainter {
public:
	LinePainter();
	virtual ~LinePainter();

	cv::Scalar GetColor() const;
	void SetColor(cv::Scalar color);

	std::vector<LineSegment> GetLines() const;
	void SetLines(std::vector<LineSegment> lines);
	void SetLines(std::vector<cv::Vec2f> lines);
	void SetLines(std::vector<cv::Vec4i> lines);
	void AddLines(LineSegment line);
	void RstLines();

	cv::Mat* GetImage() const;
	void SetImage(cv::Mat* srcImage);

	int GetThickness() const;
	void SetThickness(int thickness);

	void DrawLines();

private:
	cv::Mat* image_ = 0;

	std::vector<LineSegment> lines_;

	cv::Scalar color_ = cv::Scalar(0,0,255);
	int thickness_ = 1;
};

#endif /* LINEPAINTER_H_ */
