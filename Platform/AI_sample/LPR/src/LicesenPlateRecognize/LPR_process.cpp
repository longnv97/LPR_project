#include "LPR_process.hpp"


int TextDetection::InitTextDetection(Core &ie, std::string path_to_model)
{
    std::string inputConfigPath= "";

    /** Set graph path **/
    std::string graphPath = fileNameNoExt(path_to_model) + ".abgrp";
    std::cout << "Graph path: " << graphPath << std::endl;
    ie.SetConfig({ {VPU_CONFIG_KEY(AB_GRAPH_PATH), graphPath} });

    ExecutableNetwork executable_network = ie.ImportNetwork(graphPath, PLUGIN_TYPE_STRING, configure(inputConfigPath));
    const InferenceEngine::ConstInputsDataMap info(executable_network.GetInputsInfo());
    const InferenceEngine::ConstOutputsDataMap outputInfos(executable_network.GetOutputsInfo());
    
    for (const ConstInputsDataMap::value_type& item : info) {
        if (item.second->getTensorDesc().getDims().size() == 4) {
            this->input_name_td = item.first;
        }
    }
    
    for(const ConstOutputsDataMap::value_type& item : outputInfos) {
        std::cout << item.first << std::endl;
        this->output_names_td.emplace_back(item.first);
    }  

    std::string abgraph_ver = executable_network.GetMetric(METRIC_KEY(AB_CONFIG_ABGRAPH_VER)).as<std::string>();
    std::cout << "AB_CONFIG_ABGRAPH_VER: " << abgraph_ver.c_str() << std::endl;
    // ------------ Create infer request ------------
    this->infer_request_td = executable_network.CreateInferRequest();
    return 0;
}

InferenceEngine::BlobMap TextDetection::InferTextDetect(const cv::Mat &frame)
{
    // Blob::Ptr imageInput = this->infer_request_td.GetBlob(this->input_name_td);
    // auto input_data_td = imageInput->buffer().as<PrecisionTrait<Precision::U8>::value_type *>();

    InferenceEngine::LockedMemory<void> inputMapped = InferenceEngine::as<InferenceEngine::MemoryBlob>(this->infer_request_td.GetBlob(this->input_name_td))->wmap();
    uint8_t* input_data_td = inputMapped.as<uint8_t *>();

    cv::Mat image;
    image = frame.clone();

    image.convertTo(image, CV_8UC3);

    cv::Size input_size_ = cv::Size(128, 96);//704, 704 //1280, 768
    cv::resize(image, image, input_size_);

    int image_size = input_size_.area();

    int channels_ = 3;
    if (channels_ == 3) {
        for (int pid = 0; pid < image_size; ++pid) {
            for (int ch = 0; ch < channels_; ++ch) {
                input_data_td[ch * image_size + pid] = image.at<cv::Vec3b>(pid)[ch];
            }
        }
    }
    // std::cout << "infer_request_td.Infer();" << std::endl;
    this->infer_request_td.Infer();
    // std::cout << "infer_request_td.Infer()_1" << std::endl;

    // --------------------------- Processing output -----------------------------------------------------

    InferenceEngine::BlobMap blobs;
    for (const auto &output_name : output_names_td) {
        blobs[output_name] = infer_request_td.GetBlob(output_name);
    }

    return blobs;
}



int TextRecognition::InitTextRecognition(Core &ie, std::string path_to_model)
{
    std::string inputConfigPath= "";

    /** Set graph path **/
    std::string graphPath = fileNameNoExt(path_to_model) + ".abgrp";
    std::cout << "Graph path: " << graphPath << std::endl;
    ie.SetConfig({ {VPU_CONFIG_KEY(AB_GRAPH_PATH), graphPath} });

    ExecutableNetwork executable_network = ie.ImportNetwork(graphPath, PLUGIN_TYPE_STRING, configure(inputConfigPath));
    const InferenceEngine::ConstInputsDataMap info(executable_network.GetInputsInfo());
    const InferenceEngine::ConstOutputsDataMap outputInfos(executable_network.GetOutputsInfo());
    
    for (const ConstInputsDataMap::value_type& item : info) {
        if (item.second->getTensorDesc().getDims().size() == 4) {
            this->input_name_tr = item.first;
        }
    }
    
    for(const ConstOutputsDataMap::value_type& item : outputInfos) {
        std::cout << item.first << std::endl;
        this->output_names_tr.emplace_back(item.first);
    }  

    std::string abgraph_ver = executable_network.GetMetric(METRIC_KEY(AB_CONFIG_ABGRAPH_VER)).as<std::string>();
    std::cout << "AB_CONFIG_ABGRAPH_VER: " << abgraph_ver.c_str() << std::endl;
    // ------------ Create infer request ------------
    this->infer_request_tr = executable_network.CreateInferRequest();
    return 0;
}

InferenceEngine::BlobMap TextRecognition::InferTextRecognition(const cv::Mat &frame)
{
    Blob::Ptr imageInput = infer_request_tr.GetBlob(this->input_name_tr);
    auto input_data_tr = imageInput->buffer().as<PrecisionTrait<Precision::U8>::value_type *>();

    cv::Mat image;
    cv::cvtColor(frame, image, cv::COLOR_BGR2GRAY);

    image.convertTo(image, CV_8UC3);

    cv::Size input_size_ = cv::Size(120, 32);
    cv::resize(image, image, input_size_);

    int image_size = input_size_.area();

    int channels_ = 1;
    if (channels_ == 1) {
        for (int pid = 0; pid < image_size; ++pid) {
            input_data_tr[pid] = image.at<uint8_t>(pid);
        }
    }

    this->infer_request_tr.Infer();

    // --------------------------- Processing output -----------------------------------------------------

    InferenceEngine::BlobMap blobs;
    for (const auto &output_name : output_names_tr) {
        blobs[output_name] = infer_request_tr.GetBlob(output_name);
    }

    return blobs;
}

int LicesenPlateDetect::InitLicesenPlateDetect(Core &ie, std::string path_to_model)
{
    std::string inputConfigPath= "";

    /** Set graph path **/
    std::string graphPath = fileNameNoExt(path_to_model) + ".abgrp";
    std::cout << "Graph path: " << graphPath << std::endl;
    ie.SetConfig({ {VPU_CONFIG_KEY(AB_GRAPH_PATH), graphPath} });

    ExecutableNetwork executable_network = ie.ImportNetwork(graphPath, PLUGIN_TYPE_STRING, configure(inputConfigPath));
    const InferenceEngine::ConstInputsDataMap info(executable_network.GetInputsInfo());
    const InferenceEngine::ConstOutputsDataMap outputInfos(executable_network.GetOutputsInfo());
    
    
    for (const ConstInputsDataMap::value_type& item : info) {
        if (item.second->getTensorDesc().getDims().size() == 4) {
            imageInputName = item.first;
        } else if (item.second->getInputData()->getTensorDesc().getDims().size() == 2) {
            imInfoInputName = item.first;
        }
    }
    

    for (const ConstOutputsDataMap::value_type& item : outputInfos) {
        if (item.first == "detector/yolo-v3-tiny/Conv_12/BiasAdd/YoloRegion" || item.first == "DetectionOutput") {
                outputName_1 = item.first;
                outputInfo_1 = item.second;
            }
            if (item.first == "detector/yolo-v3-tiny/Conv_9/BiasAdd/YoloRegion" || item.first == "DetectionOutput") {
                outputName_2 = item.first;
                outputInfo_2 = item.second;
            }
    }

    std::string abgraph_ver = executable_network.GetMetric(METRIC_KEY(AB_CONFIG_ABGRAPH_VER)).as<std::string>();
    std::cout << "AB_CONFIG_ABGRAPH_VER: " << abgraph_ver.c_str() << std::endl;
    // ------------ Create infer request ------------
    this->infer_request_lpd = executable_network.CreateInferRequest();
    return 0;
}

std::vector<DetectionObject> LicesenPlateDetect::InferLicesenPlateDetect(CameraHostAPI_StreamIn_GetVideoFrame_Res frameData)
{
    Blob::Ptr imageInput = infer_request_lpd.GetBlob(imageInputName);
    auto input_data = imageInput->buffer().as<PrecisionTrait<Precision::U8>::value_type *>();

    CameraHostAPI_StreamIn_GetVideoFrame_Res frameDataToAI  = {0};

    frameDataToAI.Frame[0].DataPtr = frameData.Frame[0].DataPtr;
    frameDataToAI.Frame[0].DataLen = frameData.Frame[0].DataLen;

    if (CameraCvResize(frameDataToAI, STREAM_FRAME_TO_AI_WIDTH, STREAM_FRAME_TO_AI_HEIGHT) != CAMERA_HOST_OK)
    {
        printf("CameraCvResize Fail!!\n");
    }
    memcpy(input_data, frameDataToAI.Frame[0].DataPtr, frameDataToAI.Frame[0].DataLen);

    infer_request_lpd.Infer();

    const Blob::Ptr output_blob_1 = infer_request_lpd.GetBlob(outputName_1);
    const Blob::Ptr output_blob_2 = infer_request_lpd.GetBlob(outputName_2);

    const float* detection_1 = static_cast<PrecisionTrait<Precision::FP32>::value_type*>(output_blob_1->buffer());
    const float* detection_2 = static_cast<PrecisionTrait<Precision::FP32>::value_type*>(output_blob_2->buffer());

    unsigned long resized_im_h = STREAM_FRAME_TO_AI_HEIGHT;
    unsigned long resized_im_w = STREAM_FRAME_TO_AI_WIDTH;
    std::vector<DetectionObject> objects;
    objects.clear();

    std::vector<float> anchors_1 = {10, 14, 23, 27, 37, 58};
    const double threshold = 0.5;
    ParseYOLOV3Output(output_blob_1, detection_1, anchors_1, resized_im_h, resized_im_w, STREAM_FRAME_TO_AI_HEIGHT, STREAM_FRAME_TO_AI_WIDTH, threshold, objects);

    std::vector<float> anchors_2 = {81, 82, 135, 169, 344, 319};
    ParseYOLOV3Output(output_blob_2, detection_2, anchors_2, resized_im_h, resized_im_w, STREAM_FRAME_TO_AI_HEIGHT, STREAM_FRAME_TO_AI_WIDTH, threshold, objects);
    return objects;
}

static int EntryIndex(int side, int lcoords, int lclasses, int location, int entry) {
    int n = location / (side * side);
    int loc = location % (side * side);
    return n * side * side * (lcoords + lclasses + 1) + entry * side * side + loc;
}

void ParseYOLOV3Output(const Blob::Ptr blob,
                       const float* output_blob, 
                       std::vector<float> anchors,
                       const unsigned long resized_im_h, const unsigned long resized_im_w, 
                       const unsigned long original_im_h, const unsigned long original_im_w,
                       const double threshold, std::vector<DetectionObject> &objects)
{
    const int out_blob_h = static_cast<int>(blob->getTensorDesc().getDims()[2]);
    const int out_blob_w = static_cast<int>(blob->getTensorDesc().getDims()[3]);
    if (out_blob_h != out_blob_w)
        throw std::runtime_error("Invalid size of output. It should be in NCHW layout and H should be equal to W. Current H = " + std::to_string(out_blob_h) +
        ", current W = " + std::to_string(out_blob_h));
    
    int num = 3;
    int coords = 4;
    int classes = 2;
    
    auto side = out_blob_h;
    auto side_square = side * side;

    for(int i=0; i<side_square; ++i) {
        int row = i / side;
        int col = i % side;
        for(int n=0; n<num; ++n) {
            int obj_index = EntryIndex(side, coords, classes, n * side * side + i, coords);
            int box_index = EntryIndex(side, coords, classes, n * side * side + i, 0);
            float scale = output_blob[obj_index];
            if(scale < threshold) {
                continue;
            }
            double x = (col + output_blob[box_index + 0 * side_square]) / side * resized_im_w;
            double y = (row + output_blob[box_index + 1 * side_square]) / side * resized_im_h;
            double height = std::exp(output_blob[box_index + 3 * side_square]) * anchors[2 * n + 1];
            double width = std::exp(output_blob[box_index + 2 * side_square]) * anchors[2 * n];
            for(int j=0; j<classes; ++j) {
                int class_index = EntryIndex(side, coords, classes, n * side_square + i, coords + 1 + j);
                float prob = scale * output_blob[class_index];
                if(prob < threshold)
                    continue;
                DetectionObject obj(x, y, height, width, j, prob,
                                static_cast<float>(original_im_h) / static_cast<float>(resized_im_h),
                                static_cast<float>(original_im_w) / static_cast<float>(resized_im_w));
                objects.push_back(obj);
            }
        }
    }
}