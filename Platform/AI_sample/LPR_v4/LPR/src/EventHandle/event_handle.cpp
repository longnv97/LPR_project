#include <time.h>
#include <chrono>
#include "event_handle.hpp"

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d%h%s", &tstruct);
    return buf;
}

static std::string getCmdResult(std::string cmd)
{
    // std::cout << "cmd: " << cmd.c_str() << std::endl;
    std::string data;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    FILE* f = popen(cmd.c_str(), "r");
    if (f)
    {
        while (!feof(f))
            if (fgets(buffer, max_buffer, f) != NULL) {
                data.append(buffer);
            }
        pclose(f);
    }
    data.pop_back();
    return data;
}

void pad_rectangle(cv::Mat image, cv::Rect &rect, int paddingPercent)
{
    float padding = (float)(paddingPercent) / 100;
    rect.x = rect.x - (rect.width * padding) / 2;
    rect.y = rect.y -  (rect.height * padding) / 2;
    rect.width = rect.width + (rect.width * padding);
    rect.height = rect.height + (rect.height * padding);

    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0; 
    if ((rect.x + rect.width) > image.cols) rect.width = image.cols - rect.x;
    if ((rect.y + rect.height) > image.rows) rect.height = image.rows - rect.y;
}

void pad_rectangle_from_size(cv::Size size, cv::Rect &rect, int paddingPercent)
{
    float padding = (float)(paddingPercent) / 100;
    rect.x = rect.x - (rect.width * padding) / 2;
    rect.y = rect.y -  (rect.height * padding) / 2;
    rect.width = rect.width + (rect.width * padding);
    rect.height = rect.height + (rect.height * padding);

    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0; 
    if ((rect.x + rect.width) > size.width) rect.width = size.width - rect.x;
    if ((rect.y + rect.height) > size.height) rect.height = size.height - rect.y;
}


void OpenCvOutputHandle(cv::Mat image, std::string path)
{
   
    static int count = 1;
    std::string path_out = path + std::to_string(count) + ".jpg";
    std::cout << "path_out : " << path_out << std::endl;
    char path_image_event_mask[80];
    
    sprintf(path_image_event_mask, path_out.c_str()); 
    cv::imwrite(path_image_event_mask, image); 
    count++;
}



void OpenCvSaveJpeg(CameraHostAPI_StreamIn_GetVideoFrame_Res frameData)
{
    CAMERA_CV_API_MAT_ST src;

    src.pv_data = frameData.Frame[0].DataPtr;
    src.i_data_type = CAMERA_CV_DATA_TYPE_8UC3;
    src.s_size.i_width = MAIN_STREAM_FRAME_WIDTH;
    src.s_size.i_height = MAIN_STREAM_FRAME_HEIGHT;
    src.i_step = CAMERA_CV_API_AUTO_STEP;

    CAMERA_CV_API_MAT_ST dst;
    int32_t result = camera_cv_api_cvt_color(&src, &dst, CAMERA_CV_CONVERT_RGB888Planar_2_RGB888Packed);

    cv::Mat cv_frame(MAIN_STREAM_FRAME_HEIGHT, MAIN_STREAM_FRAME_WIDTH, CV_8UC3, (char*)dst.pv_data);
    camera_cv_api_mem_free(&dst.pv_data);
    // cv::Mat Bands[3], merged;
    // cv::split(cv_frame, Bands);
    // std::vector<cv::Mat> channels = {Bands[0],Bands[2],Bands[1]};
    // cv::merge(channels, merged);
    // cv::rectangle(merged, point_1, point_2, cv::Scalar(255, 0, 0), 2);

    char path_image_event_mask[80];
    sprintf(path_image_event_mask, "/mnt/sd/TestData/output_images/OpenCvSaveJpeg/");
    OpenCvOutputHandle(cv_frame, path_image_event_mask);
    // cv::imwrite(path_image_event_mask, cv_frame);
    std::cout << ">>>>>>>>>>>>>>>>>>>OpenCvSaveJpeg" << std::endl;

}


cv::Mat CameraCvToCVMat(CameraHostAPI_StreamIn_GetVideoFrame_Res frameData)
{
    // CAMERA_CV_API_MAT_ST src;
    // CAMERA_CV_API_MAT_ST dst;	
    
    // /*Src Parm Setting*/
    // src.pv_data = frameData.Frame[0].DataPtr;
    // src.i_data_type = CAMERA_CV_DATA_TYPE_8UC3;
    // src.s_size.i_width = MAIN_STREAM_FRAME_WIDTH;
    // src.s_size.i_height = MAIN_STREAM_FRAME_HEIGHT;
    // src.i_step = CAMERA_CV_API_AUTO_STEP;
    // int32_t result = camera_cv_api_cvt_color(&src, &dst, CAMERA_CV_CONVERT_RGB888Planar_2_NV12);
    // camera_cv_api_mem_free(&dst.pv_data);

    // cv::Mat mat_src = cv::Mat(1080*1.5, 1920, CV_8UC1, frameData.Frame[0].DataPtr);
    // cv::Mat mat_dst(1080, 1920, CV_8UC3);
    // cv::cvtColor(mat_src, mat_dst, cv::COLOR_YUV2BGR_NV12);
    // cv::Mat ROI(mat_dst, cv::Rect(0, 0, 1920, 1080));
    
    // return ROI;

    CAMERA_CV_API_MAT_ST src;

    src.pv_data = frameData.Frame[0].DataPtr;
    src.i_data_type = CAMERA_CV_DATA_TYPE_8UC3;
    src.s_size.i_width = MAIN_STREAM_FRAME_WIDTH;
    src.s_size.i_height = MAIN_STREAM_FRAME_HEIGHT;
    src.i_step = CAMERA_CV_API_AUTO_STEP;

    CAMERA_CV_API_MAT_ST dst;
    int32_t result = camera_cv_api_cvt_color(&src, &dst, CAMERA_CV_CONVERT_RGB888Planar_2_BGR888Packed);

    cv::Mat cv_frame(MAIN_STREAM_FRAME_HEIGHT, MAIN_STREAM_FRAME_WIDTH, CV_8UC3, (char*)dst.pv_data);
    camera_cv_api_mem_free(&dst.pv_data);

    return cv_frame;
    
}





// cv::Mat CameraCvToCVMat(CameraHostAPI_StreamIn_GetVideoFrame_Res frameData, cv::Rect rect)
// {
//     CAMERA_CV_API_MAT_ST src;
//     CAMERA_CV_API_JPEG_RESULT_ST dst;	
//     CAMERA_CV_API_ROI_ST roi;
//     CAMERA_CV_API_SIZE_ST dsize;
//     /*ROI Setting*/
//     roi.i_x = 0;
//     roi.i_y = 0;
//     roi.i_width = MAIN_STREAM_FRAME_WIDTH;
//     roi.i_height = MAIN_STREAM_FRAME_HEIGHT;
//     /*Dst Size Setting*/
//     dsize.i_width = MAIN_STREAM_FRAME_WIDTH;
//     dsize.i_height = MAIN_STREAM_FRAME_HEIGHT;
//     /*Src Parm Setting*/
//     src.pv_data = frameData.Frame[0].DataPtr;
//     src.i_data_type = CAMERA_CV_DATA_TYPE_8UC3;
//     src.s_size.i_width = MAIN_STREAM_FRAME_WIDTH;
//     src.s_size.i_height = MAIN_STREAM_FRAME_HEIGHT;
//     src.i_step = CAMERA_CV_API_AUTO_STEP;
    
//     // cv::Mat mat_src = cv::Mat(1080*1.5, 1920, CV_8UC1, src.pv_data);
//     // cv::Mat mat_dst(1080, 1920, CV_8UC3);
//     // cv::cvtColor(mat_src, mat_dst, cv::COLOR_YUV2BGR_NV12);
//     // cv::Mat ROI(mat_dst, cv::Rect(0, 0, 1920, 1080));

//     uint8_t *ptr = (uint8_t*)src.pv_data;
//     for (int i = 0; i < 10; i++)
//     {
//         std::cout << (int)ptr[i] << std::endl;
//     }
//     // std::cout << "size : " << dst.i_data_size << std::endl;
//     // /*Convert Jpeg*/
//     int32_t result = camera_cv_api_sub_img_cvt_jpeg_and_resize(&src, &dst, CAMERA_CV_CONVERT_JPEG_RGB888Planar_2_JPEG, CAMERA_CV_JPEG_QUALITY_MEDIAN, &roi, &dsize, 1);
//     if(!result)
// 		{
//             int x = rect.x, y = rect.y, w = rect.width, h = rect.height;
//             int index = 0;
            
            
// 			/*Save File*/
// 			FILE * pFile = fopen ( "/mnt/sd/TestData/output_images/CameraCvsave_1.jpg" , "wb");
// 			if(pFile)
// 			{
// 				fwrite(dst.pv_data, sizeof(uint8_t), dst.i_data_size, pFile);
// 				fclose (pFile);
// 			}
// 			/*Free output*/
// 			camera_cv_api_mem_free(&dst.pv_data);
// 		}
//     cv::Mat event_image = cv::imread("/mnt/sd/TestData/output_images/CameraCvsave_1.jpg");


//     // cv::Mat raw_image = cv::Mat(cv::Size(MAIN_STREAM_FRAME_WIDTH, MAIN_STREAM_FRAME_HEIGHT), CV_8UC3, (uint8_t*)dst.pv_data);

    
    
//     // uint8_t *buffer = new uint8_t[w*h*3];
//     // for (int i = 0; i < h; i++)
//     // {
//     //     for (int j = 0; j < w; j++)
//     //     {
//     //         buffer[index++] = ptr[(i + x) * MAIN_STREAM_FRAME_WIDTH * 3 + (j + y) * 3];
//     //         buffer[index++] = ptr[(i + x) * MAIN_STREAM_FRAME_WIDTH * 3 + (j + y) * 3 + 1];
//     //         buffer[index++] = ptr[(i + x) * MAIN_STREAM_FRAME_WIDTH * 3 + (j + y) * 3 + 2];
//     //     }
//     // }
//     // cv::Mat event_image(h,w,CV_8UC3,buffer);

//     // cv::Mat raw_data(1, MAIN_STREAM_FRAME_WIDTH * MAIN_STREAM_FRAME_HEIGHT * 3, CV_8UC3, dst.pv_data);
//     // cv::Mat event_image= cv::imdecode(raw_data, CV_LOAD_IMAGE_IGNORE_ORIENTATION);
//     // cv::imwrite("/mnt/sd/TestData/output_images/mat_dst.jpg", mat_dst);
//     camera_cv_api_mem_free(&dst.pv_data);
//     return event_image;
// }

void CameraCvSaveJpeg(std::vector<cv::Rect> location, std::vector<std::string> text, CameraHostAPI_StreamIn_GetVideoFrame_Res frameData)
{
	// CameraHostAPI_StreamIn_GetVideoFrame_Res frameData      = {0};
	// if(CameraHost_StreamIn_FramePop(&frameData) == CAMERA_HOST_OK) {
		CAMERA_CV_API_MAT_ST src;
		CAMERA_CV_API_JPEG_RESULT_ST dst;	
		CAMERA_CV_API_ROI_ST roi;
		CAMERA_CV_API_SIZE_ST dsize;
		/*ROI Setting*/
		roi.i_x = 0;
		roi.i_y = 0;
		roi.i_width = MAIN_STREAM_FRAME_WIDTH;
		roi.i_height = MAIN_STREAM_FRAME_HEIGHT;
		/*Dst Size Setting*/
		dsize.i_width = MAIN_STREAM_FRAME_WIDTH;
		dsize.i_height = MAIN_STREAM_FRAME_HEIGHT;
		/*Src Parm Setting*/
		src.pv_data = frameData.Frame[0].DataPtr;
		src.i_data_type = CAMERA_CV_DATA_TYPE_8UC3;
		src.s_size.i_width = MAIN_STREAM_FRAME_WIDTH;
		src.s_size.i_height = MAIN_STREAM_FRAME_HEIGHT;
		src.i_step = CAMERA_CV_API_AUTO_STEP;
		
		/*Convert Jpeg*/
		int32_t result = camera_cv_api_sub_img_cvt_jpeg_and_resize(&src, &dst, CAMERA_CV_CONVERT_JPEG_BGR888Planar_2_JPEG, CAMERA_CV_JPEG_QUALITY_MEDIAN, &roi, &dsize, 1);
		
		printf("Convert Result = %d\n", result);	

		if(!result)
		{
			/*Save File*/
			FILE * pFile = fopen ( "/mnt/sd/TestData/output_images/CameraCvsave.jpg" , "wb");
			if(pFile)
			{
				fwrite(dst.pv_data, sizeof(uint8_t), dst.i_data_size, pFile);
				fclose (pFile);
			}
			/*Free output*/
			camera_cv_api_mem_free(&dst.pv_data);
		}
	// } 
    cv::Mat event_image = cv::imread("/mnt/sd/TestData/output_images/CameraCvsave.jpg");
    cv::Mat license_plate_image;
                    
    for (int i = 0; i < location.size(); i++)
    {
        // event_image.clone()(location[i]).copyTo(license_plate_image);

        cv::rectangle(event_image, location[i], cv::Scalar(0, 255, 0), 2);
        cv::putText(event_image, text[i], cv::Point(location[i].x, location[i].y - 10), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    }
    std::string path_to_LPD_event = "/mnt/sd/TestData/output_images/LPD_event_images/";
    std::string path_to_LPR_event = "/mnt/sd/TestData/output_images/LPR_event_images/";
    OpenCvOutputHandle(event_image, path_to_LPR_event);
    // OpenCvOutputHandle(license_plate_image, path_to_LPD_event);
}


int CameraCvResize( CameraHostAPI_StreamIn_GetVideoFrame_Res &data, int resize_width, int resize_height)
{
    CAMERA_CV_API_MAT_ST src;
    CAMERA_CV_API_MAT_ST dst;
    CAMERA_CV_API_SIZE_ST dsize;

    src.pv_data = data.Frame[0].DataPtr;
    src.s_size.i_width = MAIN_STREAM_FRAME_WIDTH;
    src.s_size.i_height = MAIN_STREAM_FRAME_HEIGHT;
    src.i_data_type = CAMERA_CV_DATA_TYPE_8UC3;
    src.i_step = CAMERA_CV_API_AUTO_STEP;

    dsize.i_width = resize_width;
    dsize.i_height = resize_height;
    int32_t result = camera_cv_api_resize(&src, &dst, &dsize);

    data.Frame[0].DataPtr = (uint8_t*) dst.pv_data;
    data.Frame[0].DataLen = resize_width*resize_height*3;

    camera_cv_api_mem_free(&dst.pv_data);
    return result;
}

void setLabel(cv::Mat& im, const std::string& label, const cv::Point & p) 
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.7;
    int thickness = 1;
    int baseline = 0;

    cv::Size text_size = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    auto text_position = p;
    text_position.x = std::max(0, p.x);
    text_position.y = std::max(text_size.height, p.y);

    cv::rectangle(im, text_position + cv::Point(0, baseline), text_position + cv::Point(text_size.width, -text_size.height), CV_RGB(50, 205, 50), cv::FILLED);
    cv::putText(im, label, text_position, fontface, scale, CV_RGB(255, 255, 255), thickness, 8);
}