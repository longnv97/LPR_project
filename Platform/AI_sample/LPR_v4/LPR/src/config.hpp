#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#include <time.h>
#include <fstream>
#include <sys/types.h>
#include <signal.h>
#include <iomanip>
#include <iostream>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <vpu_tools_common.hpp>
#include <vpu/vpu_plugin_config.hpp>
#include <inference_engine.hpp>
#include "ab_camera_cv_sample.h"
#include "json.hpp"

#include "AbilityInit/ability_init.hpp"
#include "LicesenPlateRecognize/LPR_process.hpp"
#include "LicesenPlateRecognize/LPD_process.hpp"
#include "EventHandle/event_handle.hpp"

#include "ObjectTracker.hpp"
#include "TrackerManager.hpp"

extern "C" {
    #include <ab_host_api.h>
    #include <ab_cv_api.h>
}
using namespace cv;
using std::cout;




#define  DISABLE_ABGRP_IMPROVEMENT   0 //If 1, would not use .abgrp to improve the flow

#define  PLUGIN_TYPE_STRING         "MYRIAD"
#define  MAIN_STREAM_FRAME_WIDTH    1920
#define  MAIN_STREAM_FRAME_HEIGHT   1080
#define  SUB_STREAM_FRAME_WIDTH     300
#define  SUB_STREAM_FRAME_HEIGHT    300
#define  STREAM_FRAME_TO_AI_WIDTH   608
#define  STREAM_FRAME_TO_AI_HEIGHT  608
#define  POP_FRAME_INTERVAL         10000 //us
#define  MAX_FDFR_RESULT            10
#define  ENABLE_XLINK_PIPELINE      0
#define  ENABLE_RTP_META_UPDATE     0
#define  MAX_RTP_PACKET_SIZE        (64*1024)

#define  THRESHOLD_LPD              0.5
#define  THRESHOLD_TR               0.2
using namespace InferenceEngine;
using json = nlohmann::json;



#endif /* _CONFIG_H_ */