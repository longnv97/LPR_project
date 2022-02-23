/**
    @brief Header file of ability OS basic type definition.

    @file ab_cv_types.h

    @note Nothing.
*/

#ifndef _AB_CV_TYPES_H_
#define _AB_CV_TYPES_H_

/********************************************************************
    INCLUDE FILES
*********************************************************************/
#include <stdint.h>

/********************************************************************
    MACRO CONSTANT DEFINITIONS
*********************************************************************/
#ifndef IN
#define IN  // INPUT
#endif
#ifndef OUT
#define OUT // OUTPUT
#endif

#define CAMERA_CV_VERSION "v0.01.02 20191030"

#define CAMERA_CV_ALGORITHM_API_ENABLE  1
#define CAMERA_CV_FEATURE_API_ENABLE    1
#define CAMERA_CV_FORMAT_API_ENABLE     1
#define CAMERA_CV_IMAGE_API_ENABLE      1
#define CAMERA_CV_MATH_API_ENABLE       1

#define CAMERA_CV_API_MERGE_MAX_COUNT   4
#define CAMERA_CV_API_SPLIT_MAX_COUNT   4
#define CAMERA_CV_API_AUTO_STEP         0

/********************************************************************
    TYPE DEFINITION
*********************************************************************/
typedef enum {
    CAMERA_CV_API_RES_UNKNOWN               = 0x0000,

    //ALGORITHM
    CAMERA_CV_API_RES_WARP_AFFINE           = 0x1001,
    CAMERA_CV_API_RES_RESIZE                = 0x1002,
    // CAMERA_CV_API_RES_PYR_DOWN
    // CAMERA_CV_API_RES_PYR_UP
    // CAMERA_CV_API_RES_LAPLACIAN
    // CAMERA_CV_API_RES_CANNY
    // CAMERA_CV_API_RES_CORNER_MIN_EIGEN
    // CAMERA_CV_API_RES_HARRIS

    //FORMAT
    CAMERA_CV_API_RES_CVT_COLOR             = 0x3001,
    CAMERA_CV_API_RES_MERGE                 = 0x3002,
    CAMERA_CV_API_RES_CONVERT_TO            = 0x3003,

    //IMAGE
    CAMERA_CV_API_RES_MEDIAN_BLUR           = 0x4002,
    CAMERA_CV_API_RES_BOX_FILTER            = 0x4003,
    CAMERA_CV_API_RES_DILATE                = 0x4004,
    CAMERA_CV_API_RES_ERODE                 = 0x4005,
    CAMERA_CV_API_RES_SOBEL                 = 0x4006,
    // CAMERA_CV_API_RES_INTEGRAL
    // CAMERA_CV_API_RES_BLUR
    // CAMERA_CV_API_RES_FILTER_2D
    // CAMERA_CV_API_RES_MIN_MAX_IDX           = 0x4001,

    //MATH
    CAMERA_CV_API_RES_ABS                   = 0x5001,
    CAMERA_CV_API_RES_ABS_DIFF              = 0x5002,
    CAMERA_CV_API_RES_ADD                   = 0x5003,
    CAMERA_CV_API_RES_ADD_WEIGHTED          = 0x5004,
    CAMERA_CV_API_RES_BITWISE_AND           = 0x5005,
    CAMERA_CV_API_RES_BITWISE_NOT           = 0x5006,
    CAMERA_CV_API_RES_BITWISE_OR            = 0x5007,
    CAMERA_CV_API_RES_BITWISE_XOR           = 0x5008,
    CAMERA_CV_API_RES_COUNT_NON_ZERO        = 0x5009,
    CAMERA_CV_API_RES_EXP                   = 0x500A,
    CAMERA_CV_API_RES_MEAN_STD_DEV          = 0x500B,
    CAMERA_CV_API_RES_LUT                   = 0x500C,
    CAMERA_CV_API_RES_MAGNITUDE             = 0x500D,
    CAMERA_CV_API_RES_MAX                   = 0x500E,
    CAMERA_CV_API_RES_MIN                   = 0x500F,
    CAMERA_CV_API_RES_MIN_MAX_LOC           = 0x5010,
    CAMERA_CV_API_RES_MULTIPLY              = 0x5011,
    CAMERA_CV_API_RES_PHASE                 = 0x5012,
    CAMERA_CV_API_RES_SCALE_ADD             = 0x5013,
    CAMERA_CV_API_RES_SORT                  = 0x5014,
    CAMERA_CV_API_RES_SUBTRACT              = 0x5015,
    CAMERA_CV_API_RES_SUM                   = 0x5016,
    CAMERA_CV_API_RES_ACCUMULATE            = 0x5017,
    CAMERA_CV_API_RES_ACCUMULATE_SQUARE     = 0x5018,
    CAMERA_CV_API_RES_ACCUMULATE_WEIGHTED   = 0x5019,
    // CAMERA_CV_API_RES_DCT
    // CAMERA_CV_API_RES_MUL
} CAMERA_CV_API_RESPONSE_ET;

typedef enum {
    CAMERA_CV_CONVERT_YM16_2_YM16   				= 0x0101,
	CAMERA_CV_CONVERT_YM16_2_RGB888Packed  			= 0x0105,
    CAMERA_CV_CONVERT_YM16_2_UYVY   				= 0x0106,
    CAMERA_CV_CONVERT_YM16_2_YUYV    				= 0x0108,
    CAMERA_CV_CONVERT_YM16_2_GRAY    				= 0x010C,
	CAMERA_CV_CONVERT_YM12_2_YM12					= 0x0202,
    CAMERA_CV_CONVERT_YM12_2_NV12    				= 0x0203,
    CAMERA_CV_CONVERT_YM12_2_NV21    				= 0x0204,    
    CAMERA_CV_CONVERT_YM12_2_RGB888Packed  			= 0x0205,
    CAMERA_CV_CONVERT_YM12_2_YM24    				= 0x0207,
    CAMERA_CV_CONVERT_YM12_2_GRAY    				= 0x020C,
    CAMERA_CV_CONVERT_NV12_2_YM16    				= 0x0301,
    CAMERA_CV_CONVERT_NV12_2_YM12    				= 0x0302,
    CAMERA_CV_CONVERT_NV12_2_NV12    				= 0x0303,
    CAMERA_CV_CONVERT_NV12_2_RGB888Packed  			= 0x0305,
	CAMERA_CV_CONVERT_NV12_2_YM24    				= 0x0307,
	CAMERA_CV_CONVERT_NV12_2_BGR888Packed			= 0x0309,
    CAMERA_CV_CONVERT_NV12_2_GRAY			        = 0x030C,
	CAMERA_CV_CONVERT_NV12_2_RGB888Planar			= 0x0315,
	CAMERA_CV_CONVERT_NV12_2_BGR888Planar			= 0x0319,
	CAMERA_CV_CONVERT_NV21_2_YM16    				= 0x0401,
	CAMERA_CV_CONVERT_NV21_2_YM12    				= 0x0402,
	CAMERA_CV_CONVERT_NV21_2_NV21    				= 0x0404,
	CAMERA_CV_CONVERT_NV21_2_RGB888Packed  			= 0x0405,
	CAMERA_CV_CONVERT_NV21_2_YM24    				= 0x0407,
    CAMERA_CV_CONVERT_NV21_2_GRAY    				= 0x040C,
	CAMERA_CV_CONVERT_RGB888Packed_2_YM16  			= 0x0501,
	CAMERA_CV_CONVERT_RGB888Packed_2_YM12  			= 0x0502,
	CAMERA_CV_CONVERT_RGB888Packed_2_NV12  			= 0x0503,
	CAMERA_CV_CONVERT_RGB888Packed_2_RGB888Packed	= 0x0505,
	CAMERA_CV_CONVERT_RGB888Packed_2_YM24  			= 0x0507,
    CAMERA_CV_CONVERT_RGB888Packed_2_GRAY  			= 0x050C,
	CAMERA_CV_CONVERT_RGB888Packed_2_RGB888Planar  	= 0x0515,
	CAMERA_CV_CONVERT_RGB888Packed_2_BGR888Planar  	= 0x0519,
	CAMERA_CV_CONVERT_UYVY_2_YM16	  				= 0x0601,
	CAMERA_CV_CONVERT_UYVY_2_YM12   				= 0x0602,
	CAMERA_CV_CONVERT_UYVY_2_NV12	  				= 0x0603,
	CAMERA_CV_CONVERT_UYVY_2_RGB888Packed			= 0x0605,
	CAMERA_CV_CONVERT_UYVY_2_UYVY		  			= 0x0606,
	CAMERA_CV_CONVERT_UYVY_2_YM24					= 0x0607,
	CAMERA_CV_CONVERT_YM24_2_YM24	  				= 0x0707,
	CAMERA_CV_CONVERT_YUYV_2_YM16   				= 0x0801,
	CAMERA_CV_CONVERT_YUYV_2_YM12   				= 0x0802,
	CAMERA_CV_CONVERT_YUYV_2_NV12   				= 0x0803,
	CAMERA_CV_CONVERT_YUYV_2_RGB888Packed  			= 0x0805,
	CAMERA_CV_CONVERT_YUYV_2_YM24   				= 0x0807,
	CAMERA_CV_CONVERT_YUYV_2_YUYV   				= 0x0808,
	CAMERA_CV_CONVERT_BGR888Packed_2_BGR888Packed   = 0x0909,
	CAMERA_CV_CONVERT_BGR888Packed_2_RGB888Planar   = 0x0915,
	CAMERA_CV_CONVERT_BGR888Packed_2_BGR888Planar   = 0x0919,
	CAMERA_CV_CONVERT_GRAY_2_GRAY    				= 0x0C0C,
    CAMERA_CV_CONVERT_RGB888Planar_2_NV12           = 0x1503,
	CAMERA_CV_CONVERT_RGB888Planar_2_RGB888Packed   = 0x1505,
	CAMERA_CV_CONVERT_RGB888Planar_2_BGR888Packed   = 0x1509,
    CAMERA_CV_CONVERT_RGB888Planar_2_GRAY           = 0x150C,
	CAMERA_CV_CONVERT_RGB888Planar_2_RGB888Planar   = 0x1515,
    CAMERA_CV_CONVERT_BGR888Planar_2_NV12           = 0x1903,
	CAMERA_CV_CONVERT_BGR888Planar_2_RGB888Packed   = 0x1905,
	CAMERA_CV_CONVERT_BGR888Planar_2_BGR888Packed   = 0x1909,
    CAMERA_CV_CONVERT_BGR888Planar_2_GRAY           = 0x190C,
	CAMERA_CV_CONVERT_BGR888Planar_2_BGR888Planar   = 0x1919,

} CAMERA_CV_API_CONVERT_CODE_ET;

typedef enum {
    CAMERA_CV_CONVERT_JPEG_YM12_2_JPEG   				= 0x02FF,
	CAMERA_CV_CONVERT_JPEG_NV12_2_JPEG  				= 0x03FF,
    CAMERA_CV_CONVERT_JPEG_RGB888Packed_2_JPEG   		= 0x05FF,
    CAMERA_CV_CONVERT_JPEG_UYVY_2_JPEG    				= 0x06FF,
	CAMERA_CV_CONVERT_JPEG_YUYV_2_JPEG					= 0x08FF,
    CAMERA_CV_CONVERT_JPEG_RGB888Planar_2_JPEG			= 0x15FF,
    CAMERA_CV_CONVERT_JPEG_BGR888Planar_2_JPEG			= 0x19FF
} CAMERA_CV_API_CONVERT_JPEG_CODE_ET;

typedef enum {
    CAMERA_CV_JPEG_QUALITY_LOW   		= 0x00,
	CAMERA_CV_JPEG_QUALITY_MEDIAN  		= 0x01,
    CAMERA_CV_JPEG_QUALITY_HIGH   		= 0x02,
    CAMERA_CV_JPEG_QUALITY_MAX    		= 0x03
} CAMERA_CV_API_JPEG_QUALITY_ET;

typedef enum {
    CAMERA_CV_BITDEPTH_8U   = 0x00,
    CAMERA_CV_BITDEPTH_8S   = 0x01,
    CAMERA_CV_BITDEPTH_16U  = 0x02,
    CAMERA_CV_BITDEPTH_16S  = 0x03,
    CAMERA_CV_BITDEPTH_32U  = 0x04,
    CAMERA_CV_BITDEPTH_32F  = 0x05,
    CAMERA_CV_BITDEPTH_64F  = 0x06,
    CAMERA_CV_BITDEPTH_32S  = 0x07,
} CAMERA_CV_API_BIT_DEPTH_ET;

typedef enum {
    CAMERA_CV_DATA_TYPE_8UC1  = 0x00,
    CAMERA_CV_DATA_TYPE_8UC2  = 0x08,
    CAMERA_CV_DATA_TYPE_8UC3  = 0x10,
    CAMERA_CV_DATA_TYPE_8UC4  = 0x18,
    CAMERA_CV_DATA_TYPE_8SC1  = 0x01,
    CAMERA_CV_DATA_TYPE_8SC2  = 0x09,
    CAMERA_CV_DATA_TYPE_8SC3  = 0x11,
    CAMERA_CV_DATA_TYPE_8SC4  = 0x19,
    CAMERA_CV_DATA_TYPE_16UC1 = 0x02,
    CAMERA_CV_DATA_TYPE_16UC2 = 0x0A,
    CAMERA_CV_DATA_TYPE_16UC3 = 0x12,
    CAMERA_CV_DATA_TYPE_16UC4 = 0x1A,
    CAMERA_CV_DATA_TYPE_16SC1 = 0x03,
    CAMERA_CV_DATA_TYPE_16SC2 = 0x0B,
    CAMERA_CV_DATA_TYPE_16SC3 = 0x13,
    CAMERA_CV_DATA_TYPE_16SC4 = 0x1B,
    CAMERA_CV_DATA_TYPE_32UC1 = 0x04,
    CAMERA_CV_DATA_TYPE_32UC2 = 0x0C,
    CAMERA_CV_DATA_TYPE_32UC3 = 0x14,
    CAMERA_CV_DATA_TYPE_32UC4 = 0x1C,
    CAMERA_CV_DATA_TYPE_32FC1 = 0x05,
    CAMERA_CV_DATA_TYPE_32FC2 = 0x0D,
    CAMERA_CV_DATA_TYPE_32FC3 = 0x15,
    CAMERA_CV_DATA_TYPE_32FC4 = 0x1D,
    CAMERA_CV_DATA_TYPE_64FC1 = 0x06,
    CAMERA_CV_DATA_TYPE_64FC2 = 0x0E,
    CAMERA_CV_DATA_TYPE_64FC3 = 0x16,
    CAMERA_CV_DATA_TYPE_64FC4 = 0x1E,
} CAMERA_CV_API_DATA_ET;

typedef struct {
    int i_width;
    int i_height;
} CAMERA_CV_API_SIZE_ST;

typedef struct {
    void* pv_data;
    CAMERA_CV_API_SIZE_ST s_size;
    int   i_data_type;
    int   i_step;
} CAMERA_CV_API_MAT_ST;

typedef struct {
    void* pv_data;
    CAMERA_CV_API_SIZE_ST s_size;
    int   i_data_size; 
} CAMERA_CV_API_JPEG_RESULT_ST;

typedef struct {
    int i_x;
	int i_y;
	int i_width;
	int i_height;
} CAMERA_CV_API_ROI_ST;

typedef struct {
    //generate by camera_cv_api_fast_create, ab_cv_api_gftt_create, or ab_cv_api_orb_create
    //do not modify the value of it
    unsigned int ui_type; 
} CAMERA_CV_API_FEATURE_2D_ST;

typedef struct {
    float f_x;
    float f_y;
    int score;
}  CAMERA_CV_API_KEY_POINT_ST;

typedef struct {
    CAMERA_CV_API_KEY_POINT_ST* ps_key_point;
    size_t count;
}  CAMERA_CV_API_KEY_POINT_VECTOR_ST;

typedef struct {
	int i_query_idx;
	int i_train_idx;
    float   f_distance;
}  CAMERA_CV_API_MATCH_ST;

typedef struct {
    CAMERA_CV_API_MATCH_ST* ps_matches;
    size_t count;
}  CAMERA_CV_API_MATCH_VECTOR_ST;

typedef enum {
    CAMERA_CV_API_OK                              = 0,
    CAMERA_CV_API_EXCUTING                        = 1,
    ///< general error
    CAMERA_CV_API_ERR_GENERAL                     = 0xFFFFFFFF,
    CAMERA_CV_API_ERR_NOT_SUPPORT                 = 0xFFFFFFFE,     ///< not support
    CAMERA_CV_API_ERR_PARAM_ERR                   = 0xFFFFFFFD,
    CAMERA_CV_API_ERR_MEM_NOT_ENOUGH              = 0xFFFFFFFC,
    CAMERA_CV_API_ERR_HW_ENGINE_BUSY              = 0xFFFFFFFB,

} CAMERA_CV_API_RESULT_ET; ///< ability error code type

typedef enum {
    CAMERA_CV_API_ORB_FAST_SCORE                  = 0,
    CAMERA_CV_API_ORB_HARRIS_SCORE                = 1,
} CAMERA_CV_API_ORB_SCORE_TYPE_ET; ///< ability error code type

#endif  /* _AB_CV_TYPES_H_ */
