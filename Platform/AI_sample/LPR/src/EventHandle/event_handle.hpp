#ifndef _EVENT_HANDLE_H_
#define _EVENT_HANDLE_H_

#include "../AbilityInit/ability_init.hpp"
#include "../config.hpp"
extern "C" {
    #include <ab_host_api.h>
    #include <ab_cv_api.h>
}

void OpenCvSaveJpeg(CameraHostAPI_StreamIn_GetVideoFrame_Res frameData);
void CameraCvSaveJpeg(std::vector<cv::Rect> location, std::vector<std::string> text, CameraHostAPI_StreamIn_GetVideoFrame_Res frameData);
void OpenCvOutputHandle(cv::Mat image, std::string path);
int CameraCvResize( CameraHostAPI_StreamIn_GetVideoFrame_Res &data,  
                    int resize_width, 
                    int resize_height);
cv::Mat CameraCvToCVMat(CameraHostAPI_StreamIn_GetVideoFrame_Res frameData);
void pad_rectangle(cv::Mat image, cv::Rect &rect, int paddingPercent);
void pad_rectangle_from_size(cv::Size size, cv::Rect &rect, int paddingPercent);
void setLabel(cv::Mat& im, const std::string& label, const cv::Point & p);

#endif  /* _EVENT_HANDLE_H_ */