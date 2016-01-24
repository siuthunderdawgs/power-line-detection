/*
 * LineOverlayPainter.h
 *
 *  Created on: Jan 24, 2016
 *      Author: steven
 */

#ifndef LINEOVERLAYPAINTER_H_
#define LINEOVERLAYPAINTER_H_

#include "cv.h"
#include "highgui.h"

class LineOverlayPainter {
public:
	LineOverlayPainter();
	virtual ~LineOverlayPainter();

	cv::Mat* GetImageDes() const;
	void SetImageDes(cv::Mat* imageDes);

	cv::Mat* GetImageSrc() const;
	void SetImageSrc(cv::Mat* imageSrc);

	cv::Mat* GetMask() const;
	void SetMask(cv::Mat* mask);

	void DrawOverlay();

private:
	cv::Mat* image_src_;
	cv::Mat* image_des_;
	cv::Mat* mask_;
};

#endif /* LINEOVERLAYPAINTER_H_ */
