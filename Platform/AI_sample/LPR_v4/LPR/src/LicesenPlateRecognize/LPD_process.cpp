#include "LPD_process.hpp"
#include <chrono>
#include <math.h>
using namespace std::chrono;

std::vector<cv::Point2f> floatPointsFromRotatedRect(const cv::RotatedRect &rect) {
    cv::Point2f vertices[4];
    rect.points(vertices);

    std::vector<cv::Point2f> points;
    for (int i = 0; i < 4; i++) {
        points.emplace_back(vertices[i].x, vertices[i].y);
    }
    return points;
}

cv::Point topLeftPoint(const std::vector<cv::Point2f> & points, int *idx) {
    cv::Point2f most_left(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    cv::Point2f almost_most_left(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

    int most_left_idx = -1;
    int almost_most_left_idx = -1;

    for (size_t i = 0; i < points.size() ; i++) {
        if (most_left.x > points[i].x) {
            if (most_left.x < std::numeric_limits<float>::max()) {
                almost_most_left = most_left;
                almost_most_left_idx = most_left_idx;
            }
            most_left = points[i];
            most_left_idx = static_cast<int>(i);
        }
        if (almost_most_left.x > points[i].x && points[i] != most_left) {
            almost_most_left = points[i];
            almost_most_left_idx = static_cast<int>(i);
        }
    }

    if (almost_most_left.y < most_left.y) {
        most_left = almost_most_left;
        most_left_idx = almost_most_left_idx;
    }

    *idx = most_left_idx;
    return most_left;
}

cv::Mat cropImage(const cv::Mat &image, const std::vector<cv::Point2f> &points, const cv::Size& target_size, int top_left_point_idx) {
    cv::Point2f point0 = points[static_cast<size_t>(top_left_point_idx)];
    cv::Point2f point1 = points[(top_left_point_idx + 1) % 4];
    cv::Point2f point2 = points[(top_left_point_idx + 2) % 4];

    cv::Mat crop(target_size, CV_8UC3, cv::Scalar(0));

    std::vector<cv::Point2f> from{point0, point1, point2};
    std::vector<cv::Point2f> to{cv::Point2f(0.0f, 0.0f), cv::Point2f(static_cast<float>(target_size.width-1), 0.0f),
                                cv::Point2f(static_cast<float>(target_size.width-1), static_cast<float>(target_size.height-1))};

    cv::Mat M = cv::getAffineTransform(from, to);

    cv::warpAffine(image, crop, M, crop.size());

    return crop;
}

int InferenceStart()
{
    // std::string inputModelPathTD = "/mnt/sd/model/intel/text-detection-0004/FP32/text-detection-0004.xml";
    // std::string inputModelPathTD = "/mnt/sd/model/intel/horizontal-text-detection-0001/horizontal-text-detection-0001.xml";
    std::string inputModelPathTD = "/mnt/sd/model/TD_train/text_detection.xml";
    std::string inputModelPathTR = "/mnt/sd/model/intel/text-recognition-0012/FP32/text-recognition-0012.xml";
    std::string inputModelPathLPD = "/mnt/sd/model/license_plate_detect_model.xml";
    std::string s_json_file_path= "/tmp/aiapp/airesult";

    char* cp_jsonData = NULL;
    uint32_t ui_jsonSize = 0 ;
    int loopi, loopch;
    uint32_t itemPointer;
    CameraHostAPI_StreamOut_FrameUpdate_Req  frameUpdateReq = {0};
    Camera_Host_Stream_Out_Display_Type      itemType       = Camera_Host_Stream_Out_Display_SimpleFDFR;
    CameraHostAPI_Display_SimpleFDFR_Struc   fdfr           = {0};
    CameraHostAPI_StreamIn_GetVideoFrame_Res frameData      = {0};
    CameraHostAPI_StreamOut_Data_Req         metaUpdateReq  = {0};

    try
    {
        Core ie;
        TextDetection       TD;
        TextRecognition     TR;
        LicesenPlateDetect  LPD;

        TD.InitTextDetection(ie, inputModelPathTD);
        TR.InitTextRecognition(ie, inputModelPathTR);
        LPD.InitLicesenPlateDetect(ie, inputModelPathLPD);

        // ------------ Prepare input ------------
        std::vector<size_t> imageWidths, imageHeights;
        imageWidths.push_back(STREAM_FRAME_TO_AI_WIDTH);
        imageHeights.push_back(STREAM_FRAME_TO_AI_HEIGHT);
        int image_size = STREAM_FRAME_TO_AI_WIDTH * STREAM_FRAME_TO_AI_HEIGHT;
        frameUpdateReq.TargetWidth  = STREAM_FRAME_TO_AI_WIDTH;
        frameUpdateReq.TargetHeight = STREAM_FRAME_TO_AI_HEIGHT;
        memset(&fdfr, 0, sizeof(CameraHostAPI_Display_SimpleFDFR_Struc));


        std::unique_ptr<ObjectTracker> m_tracker;
        m_tracker = std::make_unique<ObjectTracker>();
        std::vector<TrackingTrace> tracks;
        size_t old_id = 0, new_id = 0;
        std::vector<cv::Rect> location;
        std::vector<std::string> text_result;
        std::string text;

        /** Start inference & calc performance **/
        while(true)
        {
            // ------------ Pop out frame ------------
            if(CameraHost_StreamIn_FramePop(&frameData) == CAMERA_HOST_OK) {
                // OpenCvSaveJpeg(frameData);
                // printf("Pop frame, size:%d (expected %dx%dx3)\n", frameData.Frame[0].DataLen, imageInput->getTensorDesc().getDims()[3], imageInput->getTensorDesc().getDims()[2]);
            } else {
                printf("CameraHost_StreamIn_FramePop Fail!!\n");
                usleep(500000);
                continue;
            }
            std::vector<DetectionObject> objects;
            objects.clear();

            auto start = high_resolution_clock::now();

            objects = LPD.InferLicesenPlateDetect(frameData);

            auto start_1 = high_resolution_clock::now();
            auto duration_1 = duration_cast<microseconds>(start_1 - start);
            std::cout << "Time taken by LicesenPlateDetect: "<< duration_1.count() << " microseconds" << std::endl;

            std::cout << "Object detect number: " << objects.size() << std::endl;

            

            frameUpdateReq.ItemNumber = 0;
            frameUpdateReq.ItemsLength = 0;
            itemPointer = 0;
            memset(frameUpdateReq.Items, 0, STREAM_OUT_ITEMS_MAX_SIZE);

            std::vector<ObjectTrace> detected;
            detected.clear();
            
            for(int i = 0; i < objects.size(); i++) 
            {
                float confidence = objects[i].confidence;
                auto label = objects[i].class_id;
                auto xmin = objects[i].xmin;
                auto ymin = objects[i].ymin;
                auto xmax = objects[i].xmax;
                auto ymax = objects[i].ymax;
                if (xmin < 0) { xmin = 0; }
                if (ymin < 0) { ymin = 0; }
                if (xmax >= 608) { xmax = 608-1; }
                if (ymax >= 608) { ymax = 608-1; }

                cv::Rect rect(xmin, ymin, (xmax - xmin), (ymax - ymin));
                
                if (confidence > THRESHOLD_LPD) //threshold = 0.5
                {

                    ObjectTrace obj;
                    obj.label = "licesen plate";
                    obj.score = objects[i].confidence;
                    obj.rect.x = rect.x;
                    obj.rect.y = rect.y;
                    obj.rect.width = rect.width;
                    obj.rect.height = rect.height;
                    detected.push_back(obj);

                }
            }
            
            

            if (detected.size() != 0)
            {
                m_tracker->update(detected);
                tracks.clear();
                tracks = m_tracker->getTracks();

                std::cout << detected.size() << "  " << tracks.size() << std::endl;

                auto start_6 = high_resolution_clock::now();     
                cv::Mat image = CameraCvToCVMat(frameData);
                auto start_7 = high_resolution_clock::now();
                // cv::imwrite("/mnt/sd/TestData/output_images/CameraCvToCVMat.jpg", image);

                auto duration_7 = duration_cast<microseconds>(start_7 - start_6);
                std::cout << "Time taken by CameraCvToCVMat: "<< duration_7.count() << " microseconds" << std::endl;

                for (auto &track: tracks) 
                {
                    if(!track.isOutOfFrame)
                    {
                        cv::Rect rect_to_liveview(track.m_rect.x, track.m_rect.y, track.m_rect.width, track.m_rect.height);
                        cv::Rect rect_to_server(track.m_rect.x * 1920 / 608, track.m_rect.y * 1080 / 608, track.m_rect.width * 1920 / 608, track.m_rect.height * 1080 / 608);      
                        new_id = track.m_ID;
                        // std::cout << "track.m_ID : " << track.m_ID << std::endl;
                        if (new_id > old_id)
                        {
                            pad_rectangle(image, rect_to_server, 10);
                            cv::Mat license_plate_image;
                            image.clone()(rect_to_server).copyTo(license_plate_image);
                            // cv::imwrite("/mnt/sd/TestData/output_images/license_plate_image.jpg", license_plate_image);

                            auto start_2 = high_resolution_clock::now();
                            InferenceEngine::BlobMap blobs;
                            blobs = TD.InferTextDetect(license_plate_image);
                            std::vector<cv::RotatedRect> rects;
                            rects = postProcess(blobs, license_plate_image.size(), cv::Size(128, 96), 0.8, 0.8); //1280, 768 // 704, 704

                            auto start_3 = high_resolution_clock::now();

                            std::cout << "Text detect number : " << rects.size() << std::endl;
                            auto duration_2 = duration_cast<microseconds>(start_3 - start_2);
                            std::cout << "Time taken by InferTextDetect: "<< duration_2.count() << " microseconds" << std::endl;
                            
                            if(rects.size() != 0) 
                            {
                                std::sort(rects.begin(), rects.end(), [](const cv::RotatedRect & a, const cv::RotatedRect & b) 
                                {
                                    if (abs(a.center.y - b.center.y) < 50) return a.center.x < b.center.x;
                                    else return a.center.y < b.center.y;
                                });

                                text.clear();
                                auto start_4 = high_resolution_clock::now();
                                for(const auto &rect : rects) 
                                {
                                    cv::Mat cropped_text;
                                    std::vector<cv::Point2f> points;
                                    int top_left_point_idx = 0;
                                    points = floatPointsFromRotatedRect(rect);
                                    topLeftPoint(points, &top_left_point_idx);
                                    cropped_text = cropImage(license_plate_image, points, cv::Size(120, 32), top_left_point_idx);
                                    

                                    std::string res = "";
                                    double conf = 1.0;

                                    InferenceEngine::BlobMap blobs_tr;
                                    blobs_tr = TR.InferTextRecognition(cropped_text);

                                    auto out_blob_tr = blobs_tr.begin()->second;
                                    auto output_shape_tr = out_blob_tr->getTensorDesc().getDims();

                                    const char kPadSymbol = '#';
                                    std::string kAlphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                                    kAlphabet = kAlphabet + kPadSymbol;

                                    LockedMemory<const void> blobMapped_tr = as<MemoryBlob>(out_blob_tr)->rmap();
                                    float *output_data_pointer = blobMapped_tr.as<float *>();
                                    std::vector<float> output_data(output_data_pointer, output_data_pointer + output_shape_tr[0] * output_shape_tr[2]);
                                    res = CTCGreedyDecoder(output_data, kAlphabet, kPadSymbol, &conf);
                                    res = conf >= THRESHOLD_TR ? res : "";
                                    text += res;
                                    std::cout << "res : " << res << std::endl;

                                    // for (size_t i = 0; i < points.size() ; i++) {
                                    //     cv::line(license_plate_image, points[i], points[(i+1) % points.size()], cv::Scalar(50, 205, 50), 2);
                                    // }
                                    // setLabel(license_plate_image, res, points[static_cast<size_t>(top_left_point_idx)]);

                                }

                                auto start_5 = high_resolution_clock::now();
                                auto duration = duration_cast<microseconds>(start_5 - start_4);
                                std::cout << "Time taken by InferTextRecognition: "<< duration.count() << " microseconds" << std::endl;
                            }

                            // OpenCvOutputHandle(license_plate_image, "/mnt/sd/TestData/output_images/test/");

                            auto stop = high_resolution_clock::now();
                        
                            auto time = duration_cast<microseconds>(stop - start);
                            
                            std::cout << "Time taken by LicesenPlateRecognize: "<< time.count() << " microseconds" << std::endl;
                            std::cout << "Licesen : " << text << std::endl;
                            // ------------ Process output ------------

                            
                            // cv::Rect rect_to_liveview(xmin, ymin, xmax - xmin, ymax - ymin);
                            location.push_back(rect_to_server);
                            text_result.push_back(text);
                            old_id = new_id;
                        }

                        cv::Size size_main_stream;
                        size_main_stream.width = 1920;
                        size_main_stream.height = 1080;
                        pad_rectangle_from_size(size_main_stream, rect_to_liveview, 10);

                        if (frameUpdateReq.ItemNumber < MAX_FDFR_RESULT) {
                            // fdfr.Left     = xmin;
                            // fdfr.Right    = xmax;
                            // fdfr.Top      = ymin;
                            // fdfr.Bottom   = ymax;
                            fdfr.Left     = (uint16_t)rect_to_liveview.x;
                            fdfr.Right    = (uint16_t)(rect_to_liveview.x + rect_to_liveview.width);
                            fdfr.Top      = (uint16_t)rect_to_liveview.y;
                            fdfr.Bottom   = (uint16_t)(rect_to_liveview.y + rect_to_liveview.height);
                            memset(fdfr.Label, 0, 32);
                            std::copy(text.begin(), text.end(), fdfr.Label);
                            fdfr.Color    = 0xFF009100; //ARGB8888: Green color

                            memcpy(&frameUpdateReq.Items[itemPointer], &itemType, sizeof(Camera_Host_Stream_Out_Display_Type));
                            itemPointer += sizeof(Camera_Host_Stream_Out_Display_Type);
                            memcpy(&frameUpdateReq.Items[itemPointer], &fdfr, sizeof(CameraHostAPI_Display_SimpleFDFR_Struc));
                            itemPointer += sizeof(CameraHostAPI_Display_SimpleFDFR_Struc);
                            frameUpdateReq.ItemNumber++;
                        }
                        if (frameUpdateReq.ItemNumber >= MAX_FDFR_RESULT) {
                            break;
                        }
                    }
                }
                
            }
            if (location.size())
            {
                CameraCvSaveJpeg(location, text_result, frameData);
                location.clear();
                text_result.clear();
            }

            frameUpdateReq.ItemsLength = itemPointer;
            CameraHost_StreamOut_FrameUpdate(&frameUpdateReq);
            json_export(&frameUpdateReq,s_json_file_path);

            usleep(POP_FRAME_INTERVAL);
        }

    }
    catch(const std::exception& error)
    {
        printf("[AB DBG] catch exception\n");
        std::cerr << error.what() << std::endl;
        return -1;
    }
    catch (...) {
        printf("[AB DBG] catch ... unexpected error\n");
        return -1;
    }
    

   return -1;
}
