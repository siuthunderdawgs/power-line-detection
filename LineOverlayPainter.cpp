/*
 * LineOverlayPainter.cpp
 *
 *  Created on: Jan 24, 2016
 *      Author: steven
 */

#include "LineOverlayPainter.h"

#include "cv.h"
#include "highgui.h"

LineOverlayPainter::LineOverlayPainter() {
	// TODO Auto-generated constructor stub

}

LineOverlayPainter::~LineOverlayPainter() {
	// TODO Auto-generated destructor stub
}

cv::Mat* LineOverlayPainter::GetImageDes() const {
	return image_des_;
}

void LineOverlayPainter::SetImageDes(cv::Mat* imageDes) {
	image_des_ = imageDes;
}

cv::Mat* LineOverlayPainter::GetImageSrc() const {
	return image_src_;
}

void LineOverlayPainter::SetImageSrc(cv::Mat* imageSrc) {
	image_src_ = imageSrc;
}

cv::Mat* LineOverlayPainter::GetMask() const {
	return mask_;
}

void LineOverlayPainter::SetMask(cv::Mat* mask) {
	mask_ = mask;
}

void LineOverlayPainter::DrawOverlay()
{
	for(int i=0; i<mask_->rows; i++)
	    for(int j=0; j<mask_->cols; j++)
	        if
	        (
	        	cvRound(mask_->at<cv::Vec3b>(i,j)[0]) ||
	        	cvRound(mask_->at<cv::Vec3b>(i,j)[1]) ||
	        	cvRound(mask_->at<cv::Vec3b>(i,j)[2])
	        )
	        {
	        	image_des_->at<cv::Vec3b>(i,j) = mask_->at<cv::Vec3b>(i,j);
	        }
	        else
	        {
	        	image_des_->at<cv::Vec3b>(i,j) = image_src_->at<cv::Vec3b>(i,j);
	        }
}
