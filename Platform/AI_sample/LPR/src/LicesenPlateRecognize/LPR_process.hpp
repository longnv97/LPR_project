#ifndef _LPR_PROCESS_H_
#define _LPR_PROCESS_H_

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// #include <gflags/gflags.h>
#include <opencv2/opencv.hpp>

#include <inference_engine.hpp>

#include <vpu_tools_common.hpp>
#include <vpu/vpu_plugin_config.hpp>
#include "../AbilityInit/ability_init.hpp"
#include "../EventHandle/event_handle.hpp"
#include "../config.hpp"

extern "C" {
    #include <ab_host_api.h>
    #include <ab_cv_api.h>
}

using namespace InferenceEngine;

struct DetectionObject {
    int xmin, ymin, xmax, ymax, class_id;
    float confidence;

    DetectionObject(double x, double y, double h, double w, int class_id, float confidence, float h_scale, float w_scale) :
        xmin{static_cast<int>((x - w / 2) * w_scale)},
        ymin{static_cast<int>((y - h / 2) * h_scale)},
        xmax{static_cast<int>(this->xmin + w * w_scale)},
        ymax{static_cast<int>(this->ymin + h * h_scale)},
        class_id{class_id},
        confidence{confidence} {}

    bool operator <(const DetectionObject &s2) const {
        return this->confidence < s2.confidence;
    }
    bool operator >(const DetectionObject &s2) const {
        return this->confidence > s2.confidence;
    }
};


class TextDetection
{
    public:
        int InitTextDetection(Core &ie, std::string path_to_model);
        InferenceEngine::BlobMap InferTextDetect(const cv::Mat &frame);
    private:
        InferRequest infer_request_td;
        std::string input_name_td;
        std::vector<std::string> output_names_td;
};


class TextRecognition
{
    public:
        int InitTextRecognition(Core &ie, std::string path_to_model);
        InferenceEngine::BlobMap InferTextRecognition(const cv::Mat &frame);
    private:
        InferRequest infer_request_tr;
        std::string input_name_tr;
        std::vector<std::string> output_names_tr;
};


class LicesenPlateDetect
{
    public:
        int InitLicesenPlateDetect(Core &ie, std::string path_to_model);
        std::vector<DetectionObject> InferLicesenPlateDetect(CameraHostAPI_StreamIn_GetVideoFrame_Res frameData);
    private:
        InferRequest infer_request_lpd;
        std::string imageInputName, imInfoInputName;
        std::string outputName_1;
        CDataPtr outputInfo_1;
        std::string outputName_2;
        CDataPtr outputInfo_2;
};



void ParseYOLOV3Output(const Blob::Ptr blob,
                       const float* output_blob, 
                       std::vector<float> anchors,
                       const unsigned long resized_im_h, const unsigned long resized_im_w, 
                       const unsigned long original_im_h, const unsigned long original_im_w,
                       const double threshold, std::vector<DetectionObject> &objects);

#endif  /* _LPR_PROCESS_H_ */