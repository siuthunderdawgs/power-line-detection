/*
 * LineClipping.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: steven
 */

#include "LineSegment.h"
#include "LineClipping.h"

bool ClipLine(LineSegment& line_inout, cv::Rect rect)
{
	LineSegment line_in = line_inout;
	return ClipLine(line_in, line_inout, rect);
}

bool ClipLine(LineSegment line_in, LineSegment& line_out, cv::Rect rect)
{
	double L = rect.x;
	double R = rect.x + rect.width;
	double T = rect.y;
	double B = rect.y + rect.height;

	double x1 = line_in.GetPt1().x;
	double y1 = line_in.GetPt1().y;
	double x2 = line_in.GetPt2().x;
	double y2 = line_in.GetPt2().y;
	double x1c, y1c, x2c, y2c;

	bool should_draw = LiangBarsky (L,R,T,B,
									x1,y1,x2,y2,
									x1c,y1c,x2c,y2c);

	if(should_draw)
	{
		line_out = LineSegment(cv::Point(x1c,y1c),cv::Point(x2c,y2c));
		return true;
	}
	else
	{
		line_out = LineSegment(cv::Point(-1,-1),cv::Point(-1,-1));
		return false;
	}
}


// Original Name: N/A
// Original Author: Daniel White
// Source: http://www.skytopia.com/project/articles/compsci/clipping.html

bool LiangBarsky (double edgeLeft, double edgeRight, double edgeBottom, double edgeTop,   // Define the x/y clipping values for the border.
					double x0src, double y0src, double x1src, double y1src,                 // Define the start and end points of the line.
					double &x0clip, double &y0clip, double &x1clip, double &y1clip)         // The output values, so declare these outside.
{
	double t0 = 0.0;
	double t1 = 1.0;
	double xdelta = x1src-x0src;
	double ydelta = y1src-y0src;
	double p,q,r;

	// Traverse through left, right, bottom, top edges.
	for(int edge=0; edge<4; edge++)
	{
		if (edge==0)
		{
			p = -xdelta;
			q = -(edgeLeft-x0src);
		}
		if (edge==1)
		{
			p = xdelta;
			q = (edgeRight-x0src);
		}
		if (edge==2)
		{
			p = -ydelta;
			q = -(edgeBottom-y0src);
		}
		if (edge==3)
		{
			p = ydelta;
			q = (edgeTop-y0src);
		}

		r = q/p;

		if(p==0 && q<0)
		{
			return false;				// Don't draw line at all.
										// (parallel line outside)
		}
		if(p<0)
		{
			if(r>t1) return false;		// Don't draw line at all.
			else if(r>t0) t0=r;			// Line is clipped!
		}
		else if(p>0)
		{
			if(r<t0) return false;		// Don't draw line at all.
			else if(r<t1) t1=r;			// Line is clipped!
		}
    }

	x0clip = x0src + t0*xdelta;
	y0clip = y0src + t0*ydelta;
	x1clip = x0src + t1*xdelta;
	y1clip = y0src + t1*ydelta;

	return true;        // (clipped) line is drawn
}
