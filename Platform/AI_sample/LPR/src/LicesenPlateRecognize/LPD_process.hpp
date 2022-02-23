#ifndef _LPD_PROCESS_H_
#define _LPD_PROCESS_H_

#include "../AbilityInit/ability_init.hpp"
#include "../EventHandle/event_handle.hpp"
#include "../config.hpp"
#include "../LicesenPlateRecognize/LPR_process.hpp"

#include "../LicesenPlateRecognize/text_detection.hpp"
#include "../LicesenPlateRecognize/text_recognition.hpp"

// using namespace InferenceEngine;




int InferenceStart();
std::vector<cv::Point2f> floatPointsFromRotatedRect(const cv::RotatedRect &rect);
cv::Point topLeftPoint(const std::vector<cv::Point2f> & points, int *idx);
cv::Mat cropImage(const cv::Mat &image, const std::vector<cv::Point2f> &points, const cv::Size& target_size, int top_left_point_idx);

#endif  /* _LPD_PROCESS_H_ */