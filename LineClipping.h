/*
 * LineClipping.h
 *
 *  Created on: Mar 13, 2016
 *      Author: steven
 */

#ifndef LINECLIPPING_H_
#define LINECLIPPING_H_

#include "cv.h"
#include "highgui.h"

#include "LineSegment.h"

bool ClipLine(LineSegment& line_inout, cv::Rect rect);
bool ClipLine(LineSegment line_in, LineSegment& line_out, cv::Rect rect);
bool ClipReject(double C, double q, double& u1, double& u2);


// Original Name: N/A
// Original Author: Daniel White
// Source: http://www.skytopia.com/project/articles/compsci/clipping.html

bool LiangBarsky (double edgeLeft, double edgeRight, double edgeBottom, double edgeTop,
					double x0src, double y0src, double x1src, double y1src,
					double &x0clip, double &y0clip, double &x1clip, double &y1clip);

#endif /* LINECLIPPING_H_ */
