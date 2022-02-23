/**
    @brief Header file of ability OS basic type definition.

    @file ab_ipc_types.h

    @note Nothing.
*/

#ifndef _AB_HOST_TYPES_H_
#define _AB_HOST_TYPES_H_

/********************************************************************
    INCLUDE FILES
*********************************************************************/
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/epoll.h> 
#include <string.h>
#include <sys/timeb.h>  
#include <sys/time.h>
#include <math.h>

#include "ab_host_event_types.h"

/********************************************************************
    MACRO CONSTANT DEFINITIONS
*********************************************************************/
#define CAMERA_HOST_DUMMY_VALUE             0xFFFFFFFF
#define MESSAGE_GROUP_AI                    0x05000000
#define MESSAGE_DIRECTION_TO_SYS            0x00020000
#define CAMERA_HOST_MESSAGE_BASE            (MESSAGE_GROUP_AI + MESSAGE_DIRECTION_TO_SYS + 0x0000)
#define CAMERA_NAME_LENGTH                  64
#define NTPSERVER_MAX_STRLEN                64
#define CAMERA_NETWORK_PARAMETER_LENGTH     16
#define CAMERA_SSH_PUBLIC_KEY_FILE_NAME_MAX_STR_LEN 128
#define CAMERA_SSH_PASSWORD_MAX_STR_LEN     32
/********************************************************************
    TYPE DEFINITION
*********************************************************************/
typedef enum {
    CAMERA_HOST_OK                              = 0,
    CAMERA_HOST_EXCUTING                        = 1,
    ///< general error
    CAMERA_HOST_ERR_GENERAL                     = 0xFFFFFFFF,   // -1
    CAMERA_HOST_ERR_NOT_SUPPORT                 = 0xFFFFFFFE,   // -2     ///< not support
    CAMERA_HOST_ERR_PARAM_ERR                   = 0xFFFFFFFD,   // -3
    CAMERA_HOST_ERR_BUSY                        = 0xFFFFFFFC,   // -4
} Camera_Host_Result_Type; ///< ability error code type

typedef enum  {
    CAMERA_HOST_MSGGROUP_STREAM_IN      = 0x0000,
    CAMERA_HOST_MSGGROUP_STREAM_OUT     = 0x0100,
    CAMERA_HOST_MSGGROUP_GET_SETTING    = 0x0200,
    CAMERA_HOST_MSGGROUP_SET_SETTING    = 0x0300,
    CAMERA_HOST_MSGGROUP_COMMAND        = 0x0400,
    CAMERA_HOST_MSGGROUP_MYX            = 0x0500,
}Camera_Host_MsgGroup_Type;

typedef enum  {
    CAMERA_HOST_API_STREAM_IN_INIT                              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_IN + 0x0000,
    CAMERA_HOST_API_STREAM_IN_DEINIT                            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_IN + 0x0001,
    CAMERA_HOST_API_STREAM_IN_GET_VIDEO_FRAME                   = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_IN + 0x0002,
    CAMERA_HOST_API_STREAM_IN_GET_TOF_FRAME                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_IN + 0x0003,

  	CAMERA_HOST_API_STREAM_OUT_START                            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_OUT + 0x0000,
  	CAMERA_HOST_API_STREAM_OUT_STOP                             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_OUT + 0x0001,
  	CAMERA_HOST_API_STREAM_OUT_FRAME_UPDATE                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_OUT + 0x0002,
    CAMERA_HOST_API_STREAM_OUT_RTP_DATA_UPDATE                  = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_OUT + 0x0010,
    CAMERA_HOST_API_STREAM_OUT_RTP_FIFO_RESET                   = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_OUT + 0x0011,
    CAMERA_HOST_API_STREAM_OUT_CUSTOMIZED_DATA_UPDATE           = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_STREAM_OUT + 0x001F,
                
  	CAMERA_HOST_API_GET_IMAGE_PARAMETER_ALL                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0000,       
  	CAMERA_HOST_API_GET_SETTING_MAIN_STREAM_ALL                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0010,                      
  	CAMERA_HOST_API_GET_SETTING_SECOND_STREAM_ALL               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0020,   
  	CAMERA_HOST_API_GET_SETTING_OVERLAY_TEXT_ALL                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0030,
  	CAMERA_HOST_API_GET_SETTING_OVERLAY_TIME_ALL                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0031,
  	CAMERA_HOST_API_GET_SETTING_OVERLAY_IMAGE_ALL               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0032,
  	CAMERA_HOST_API_GET_SETTING_AUDIO_ALL                       = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0033,
  	CAMERA_HOST_API_GET_IMAGE_CONFIG_ALL                        = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0034,
  	CAMERA_HOST_API_GET_NETWORK_BASIC_CONFIG_ALL                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0035,
    CAMERA_HOST_API_GET_ZOOM_LEVEL                              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0036,
    CAMERA_HOST_API_GET_CONTINUOS_AUTO_FOCUS                    = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0038,
    CAMERA_HOST_API_GET_AUTO_IRIS                               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0039,
    CAMERA_HOST_API_GET_MANUAL_IRIS                             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x003A,
    CAMERA_HOST_API_GET_MANUAL_MFSPEED                          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x003B,
    CAMERA_HOST_API_GET_AEMODE                                  = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x003C,
    CAMERA_HOST_API_GET_DIGITAL_IO_CONFIG_ALL                   = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x003D,
    CAMERA_HOST_API_GET_CAMERA_GENERAL_INFO                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x003E,
    CAMERA_HOST_API_GET_DATETIME_CONFIG_ALL                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x003F,
    CAMERA_HOST_API_GET_NETWORK_DISCOVERY_CONFIG_ALL            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0040,
    CAMERA_HOST_API_GET_NETWORK_SSH_CONFIG_ALL                  = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0041,
    CAMERA_HOST_API_GET_RECORDING_CONFIG                        = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0042,
    CAMERA_HOST_API_GET_EXPOSURE_MODE_ALL                       = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0043,
    CAMERA_HOST_API_GET_IMAGE_ADVANCED_ALL                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0044,
    CAMERA_HOST_API_GET_LOG_SETTING_ALL                         = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0045,
    CAMERA_HOST_API_GET_TRIGGER_SOURCE_ALL                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0046,
    CAMERA_HOST_API_GET_MEDIA_SNAPSHOT_ALL                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0047,
    CAMERA_HOST_API_GET_MEDIA_VIDEO_ALL                         = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0048,
    CAMERA_HOST_API_GET_WEB_ACCOUNT                             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x0049,
    CAMERA_HOST_API_GET_SETTING_CUSTOMIZED                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_GET_SETTING + 0x00F0,

    CAMERA_HOST_API_SET_IMAGE_PARAMETER_BRIGHTNESS               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0000,
    CAMERA_HOST_API_SET_IMAGE_PARAMETER_CONTRAST                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0001,    
    CAMERA_HOST_API_SET_IMAGE_PARAMETER_COLOR_DESATURATION       = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0002,                
    CAMERA_HOST_API_SET_IMAGE_PARAMETER_SHARPNESS                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0003,                    
    CAMERA_HOST_API_SET_IMAGE_PARAMETER_WHITEBALANCE_TYPE        = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0004,                
    CAMERA_HOST_API_SET_IMAGE_PARAMETER_WHITEBALANCE_COLOR_LEVEL = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0005,                    
    CAMERA_HOST_API_SET_IMAGE_PARAMETER_GAMMA                    = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0006,                           
    CAMERA_HOST_API_SET_IMAGE_PARAMETER_ALL                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0007,
    CAMERA_HOST_API_SET_SETTING_AE_MODE                          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x000A,

    CAMERA_HOST_API_SET_SETTING_MAIN_STREAM_FORMAT              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0010,    
    CAMERA_HOST_API_SET_SETTING_MAIN_STREAM_RESOLUTION          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0011,            
    CAMERA_HOST_API_SET_SETTING_MAIN_STREAM_FPS                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0012,    
    CAMERA_HOST_API_SET_SETTING_MAIN_STREAM_GOV                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0013,    
    CAMERA_HOST_API_SET_SETTING_MAIN_STREAM_RATECONTROL_MODE    = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0014,                    
    CAMERA_HOST_API_SET_SETTING_MAIN_STREAM_TARGET_BITRATE      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0015,                
    CAMERA_HOST_API_SET_SETTING_MAIN_STREAM_QUALITY             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0016,      
    CAMERA_HOST_API_SET_SETTING_MAIN_STREAM_ALL                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x001F,    
    
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_FORMAT            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0020,            
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_RESOLUTION        = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0021,                
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_FPS               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0022,        
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_GOV               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0023,        
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_RATECONTROL_MODE  = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0024,                    
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_TARGET_BITRATE    = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0025,                    
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_QUALITY           = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0026,
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_AUDIO_TYPE        = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0027,            
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_ENABLED           = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0028,            
    CAMERA_HOST_API_SET_SETTING_SECOND_STREAM_ALL               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x002F,        

    CAMERA_HOST_API_SET_SETTING_OVERLAY_TEXT_ENABLED            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0030,               
    CAMERA_HOST_API_SET_SETTING_OVERLAY_TEXT_FONT_SIZE          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0031,            
    CAMERA_HOST_API_SET_SETTING_OVERLAY_TEXT_COLOR              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0032,        
    CAMERA_HOST_API_SET_SETTING_OVERLAY_TEXT_POSITION           = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0033,            
    CAMERA_HOST_API_SET_SETTING_OVERLAY_TEXT_CONTENT            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0034,            
    CAMERA_HOST_API_SET_SETTING_OVERLAY_TEXT_ALL                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0035,        
    CAMERA_HOST_API_SET_SETTING_OVERLAY_TIME_ENABLED            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0036,                   
    CAMERA_HOST_API_SET_SETTING_OVERLAY_TIME_POSITION           = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0037,            
    CAMERA_HOST_API_SET_SETTING_OVERLAY_TIME_ALL                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0038,        
    CAMERA_HOST_API_SET_SETTING_OVERLAY_IMAGE_ENABLED           = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x003B,            
    CAMERA_HOST_API_SET_SETTING_OVERLAY_IMAGE_POSITION          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x003C,        
    CAMERA_HOST_API_SET_SETTING_OVERLAY_IMAGE_ALL               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x003D,

    CAMERA_HOST_API_SET_SETTING_AUDIO_SPEAKER_ENABLE            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0040,               
    CAMERA_HOST_API_SET_SETTING_AUDIO_SPEAKER_GAIN              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0041,            
    CAMERA_HOST_API_SET_SETTING_AUDIO_MIC_ENABLE                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0042,        
    CAMERA_HOST_API_SET_SETTING_AUDIO_MIC_GAIN                  = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0043,            
    CAMERA_HOST_API_SET_SETTING_AUDIO_ALL                       = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0044,

    CAMERA_HOST_API_SET_IMAGE_CONFIG_FLIP                       = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0045,        
    CAMERA_HOST_API_SET_IMAGE_CONFIG_ROTATION                   = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0046,
    CAMERA_HOST_API_SET_IMAGE_CONFIG_LDC_ENABLE                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0047,                    
    CAMERA_HOST_API_SET_IMAGE_CONFIG_CAPTURE_FREQUENCY          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0048,    
    CAMERA_HOST_API_SET_IMAGE_CONFIG_ALL                        = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0049,
    CAMERA_HOST_API_SET_RECORDING_CONFIG                        = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x004F,

    CAMERA_HOST_API_SET_DIGITAL_IO_CONFIG_ALL                   = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0050,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_DATEFORMAT              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0051,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_TIMEFORMAT              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0052,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_SYNCSOURCE              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0053,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_DAYLIGHT                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0054,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_TIMEZONE                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0055,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_NTP                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0056,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_DATETIME                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0057,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_IEEE_ROLE               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0058,
    CAMERA_HOST_API_SET_DATETIME_CONFIG_ALL                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0059,
    
    CAMERA_HOST_API_SET_WEB_ACCOUNT                             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x005E,
    CAMERA_HOST_API_SET_WEB_ACCOUNT_PASSWORD                    = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x005F,

    CAMERA_HOST_API_SET_NETWORK_BASIC_CONFIG_IPV4_ADDR          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0060,
    CAMERA_HOST_API_SET_NETWORK_BASIC_CONFIG_IPV4_MASK          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0061,
    CAMERA_HOST_API_SET_NETWORK_BASIC_CONFIG_IPV4_GATEWAY       = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0062,
    CAMERA_HOST_API_SET_NETWORK_BASIC_CONFIG_IPV4_DNS           = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0063,
    CAMERA_HOST_API_SET_NETWORK_BASIC_CONFIG_TYPE               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0064,
    CAMERA_HOST_API_SET_NETWORK_BASIC_DHCP_FALLBACKIP_TYPE      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0065,
    CAMERA_HOST_API_SET_NETWORK_BASIC_CONFIG_ALL                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0066,
    CAMERA_HOST_API_SET_NETWORK_DISCOVERY_CONFIG_WSD            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0068,
    CAMERA_HOST_API_SET_NETWORK_DISCOVERY_CONFIG_MDNS           = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0069,
    CAMERA_HOST_API_SET_NETWORK_DISCOVERY_CONFIG_ALL            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x006A,
    CAMERA_HOST_API_SET_NETWORK_SSH_CONFIG_PORT                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x006B,
    CAMERA_HOST_API_SET_NETWORK_SSH_CONFIG_PASSWORD             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x006C,
    CAMERA_HOST_API_SET_NETWORK_SSH_CONFIG_TYPE                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x006D,
    CAMERA_HOST_API_SET_NETWORK_SSH_CONFIG_ENABLE               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x006E,
    CAMERA_HOST_API_SET_NETWORK_SSH_CONFIG_ALL                  = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x006F,

    CAMERA_HOST_API_SET_ZOOM_LEVEL                              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0070,
    CAMERA_HOST_API_SET_AUTO_FOCUS                              = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0071,
    CAMERA_HOST_API_SET_CONTINUOS_AUTO_FOCUS                    = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0072,
    CAMERA_HOST_API_SET_AUTO_IRIS                               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0073,
    CAMERA_HOST_API_SET_MANUAL_IRIS                             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0074,
    CAMERA_HOST_API_SET_MANUAL_MFSPEED                          = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0075,
    CAMERA_HOST_API_SET_MANUAL_FOUCS                            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0076,

    CAMERA_HOST_API_SET_EXPOSURE_MODE_TYPE                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0080,
    CAMERA_HOST_API_SET_EXPOSURE_MODE_AESPEED                   = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0081,
    CAMERA_HOST_API_SET_EXPOSURE_MODE_AESENSITIVITY             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0082,
    CAMERA_HOST_API_SET_EXPOSURE_MODE_ROI                       = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0083,
    CAMERA_HOST_API_SET_EXPOSURE_MODE_ALL                       = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0084,

    CAMERA_HOST_API_SET_MEDIA_SNAPSHOT_ALL                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x008C,
    CAMERA_HOST_API_SET_MEDIA_VIDEO_ALL                         = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x008D,
    CAMERA_HOST_API_SET_TRIGGER_SOURCE_ALL                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x008E,
    CAMERA_HOST_API_SET_LOG_SETTING_ALL                         = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x008F,
    
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_HDR                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0090,
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_WDR                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0091,
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_DNR                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0092,
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_FOCUS_MODE               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0093,
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_MF_FOCUS                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0094,
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_MF_SPEED                 = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0095,
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_IRCUT_FILTER             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0096,
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_EXPOSURE_MODE            = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0097,
    CAMERA_HOST_API_SET_IMAGE_ADVANCED_ALL                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_SET_SETTING + 0x0098,
    

    CAMERA_HOST_API_COMMAND_STREAM_SETTING_START                = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_COMMAND + 0x0000,
    CAMERA_HOST_API_COMMAND_STREAM_SETTING_FINISH               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_COMMAND + 0x0001, 
    CAMERA_HOST_API_COMMAND_OVERLAY_SETTING_TRIGGER             = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_COMMAND + 0x0002,
    CAMERA_HOST_API_COMMAND_NETWORK_RESTART                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_COMMAND + 0x0003,
    CAMERA_HOST_API_COMMAND_AI_EVENT_NOTIFY                     = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_COMMAND + 0x0004,
    CAMERA_HOST_API_COMMAND_PROFILE_LOCK                        = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_COMMAND + 0x0005,
    CAMERA_HOST_API_COMMAND_PROFILE_UNLOCK                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_COMMAND + 0x0006,
    CAMERA_HOST_API_COMMAND_PROFILE_UPDATE                      = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_COMMAND + 0x0007,
    CAMERA_HOST_API_MYRIADX_RESET                               = CAMERA_HOST_MESSAGE_BASE + CAMERA_HOST_MSGGROUP_MYX + 0x0000,
    CAMERA_HOST_API_MSGID_DUMMY                                 = CAMERA_HOST_DUMMY_VALUE,
}Camera_Host_MsgID_Type;

typedef enum {
    Camera_Host_Stream_Rotation_0   = 0x00,
    Camera_Host_Stream_Rotation_90  = 0x01,
    Camera_Host_Stream_Rotation_180 = 0x02,
    Camera_Host_Stream_Rotation_270 = 0x03,
    Camera_Host_Stream_Rotation_Dummy = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Stream_Rotation_Type; 

typedef enum {
    Camera_Host_Stream_Type_Default = 0x00,
} Camera_Host_Stream_Type; 

typedef enum {
    Camera_Host_Stream_Frame_Format_YM16 			= 0x01,
    Camera_Host_Stream_Frame_Format_YM12 			= 0x02,
    Camera_Host_Stream_Frame_Format_NV12 			= 0x03,
    Camera_Host_Stream_Frame_Format_RGB888Packed  	= 0x05,
    Camera_Host_Stream_Frame_Format_YM24 			= 0x07,
    Camera_Host_Stream_Frame_Format_BGR888Packed  	= 0x09,
    Camera_Host_Stream_Frame_Format_Gray  			= 0x0C,
    Camera_Host_Stream_Frame_Format_RGB888Planar 	= 0x15,
    Camera_Host_Stream_Frame_Format_BGR888Planar 	= 0x19,
} Camera_Host_Stream_Frame_Format_Type;

typedef enum {
    Camera_Host_Stream_Frame_ToF_Depth_IR 			= 0x01,
} Camera_Host_Stream_Frame_ToF_Type;

typedef enum {
    Camera_Host_Stream_Out_SyncMode_Async  = 0x00,
    Camera_Host_Stream_Out_SyncMode_Sync   = 0x01,
} Camera_Host_Stream_Out_SyncMode_Type;

typedef enum {
    Camera_Host_Stream_Out_Display_Text             = 0x00,
    Camera_Host_Stream_Out_Display_ShortText        = 0x01,
    Camera_Host_Stream_Out_Display_LongText         = 0x02,
    Camera_Host_Stream_Out_Display_Line             = 0x03,
    Camera_Host_Stream_Out_Display_Rectangle        = 0x04,
    Camera_Host_Stream_Out_Display_Circle           = 0x05,
    Camera_Host_Stream_Out_Display_BasicHumanBody   = 0x0101,
    Camera_Host_Stream_Out_Display_Polygon          = 0x0102,
    Camera_Host_Stream_Out_Display_SimpleFDFR       = 0x0A00,
    Camera_Host_Stream_Out_Display_UnknownItem      = 0xFFFF,
} Camera_Host_Stream_Out_Display_Type;

/********************************************************************
    GENERAL SETTING DEFINITION
*********************************************************************/
typedef enum {
    Camera_Host_Switch_Off             = 0x00,
    Camera_Host_Switch_On              = 0x01,
    Camera_Host_Switch_Dummy = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Switch_Type;


/********************************************************************
    SENSOR SETTING DEFINITION
*********************************************************************/
typedef enum {
    Camera_Host_AE_Mode_Auto             = 0x00,
    Camera_Host_AE_Mode_ROI              = 0x01,
    Camera_Host_AE_Mode_Dummy = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_AE_Mode_Type;

typedef enum {
    Camera_Host_Capture_Freq_60Hz             = 0x00,
    Camera_Host_Capture_Freq_50Hz             = 0x01,
    Camera_Host_Capture_Freq_Auto,
    Camera_Host_Capture_Freq_Dummy = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Capture_Freq_Type;

typedef enum {
    Camera_Host_WB_Auto                 = 0x00,
    Camera_Host_WB_Manual               = 0x01,
    Camera_Host_WB_Dummy = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_WB_Type;

typedef enum {
    Camera_Host_Exp_Auto                 = 0x00,
    Camera_Host_Exp_Manual               = 0x01,
    Camera_Host_Exp_Dummy = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Exp_Type;

typedef enum {
  Camera_Host_ExpTime_1_8000_S         = 0x00,
  Camera_Host_ExpTime_1_4000_S         = 0x01,
  Camera_Host_ExpTime_1_2000_S         = 0x02,
  Camera_Host_ExpTime_1_1000_S         = 0x03,
  Camera_Host_ExpTime_1_500_S          = 0x04,
  Camera_Host_ExpTime_1_250_S          = 0x05,
  Camera_Host_ExpTime_1_120_S          = 0x06,
  Camera_Host_ExpTime_1_100_S          = 0x07,
  Camera_Host_ExpTime_1_60_S           = 0x08,
  Camera_Host_ExpTime_1_50_S           = 0x09,
  Camera_Host_ExpTime_1_30_S           = 0x0A,
  Camera_Host_ExpTime_1_25_S           = 0x0B,
  Camera_Host_ExpTime_1_15_S           = 0x0C,
  Camera_Host_ExpTime_1_8_S            = 0x0D,
  Camera_Host_ExpTime_1_4_S            = 0x0E,
  Camera_Host_ExpTime_1_2_S            = 0x0F,
  Camera_Host_ExpTime_1_S              = 0x10,
  Camera_Host_ExpTime_Dummy = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_ExpTime_Type;

typedef enum {
  Camera_Host_DNR_2D         = 0x00,
  Camera_Host_DNR_3D         = 0x01,
  Camera_Host_DNR_Dummy      = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_DNR_Type;

/********************************************************************
    STREAM SETTING DEFINITION
*********************************************************************/
typedef enum {
  Camera_Host_StreamResolution_3840x2160         = 0x00,
  Camera_Host_StreamResolution_2560x1440,
  Camera_Host_StreamResolution_1920x1080,
  Camera_Host_StreamResolution_1280x720,
  Camera_Host_StreamResolution_640x360,
  Camera_Host_StreamResolution_2560x1920,
  Camera_Host_StreamResolution_2048x1536,
  Camera_Host_StreamResolution_1600x1200,
  Camera_Host_StreamResolution_1280x960,
  Camera_Host_StreamResolution_1024x768,
  Camera_Host_StreamResolution_640x480,
} Camera_Host_StreamResolution_Type;

typedef enum {
  Camera_Host_StreamFormat_H264= 0x00,
  Camera_Host_StreamFormat_MJPEG,
  Camera_Host_StreamFormat_H265,
} Camera_Host_StreamFormat_Type;

typedef enum {
  Camera_Host_StreamMode_VBR= 0x00,
  Camera_Host_StreamMode_CBR,
} Camera_Host_StreamMode_Type;

typedef enum {
  Camera_Host_StreamQuality_VaryLow= 0x00,
  Camera_Host_StreamQuality_Low,
  Camera_Host_StreamQuality_Normal,
  Camera_Host_StreamQuality_High,
  Camera_Host_StreamQuality_VaryHigh,
} Camera_Host_StreamQuality_Type;

typedef enum {
  Camera_Host_StreamAudio_AAC= 0x00,
  Camera_Host_StreamAudio_G711_PCMU,
  Camera_Host_StreamAudio_G711_PCMA,
} Camera_Host_StreamAudio_Type;

/********************************************************************
    OVERLAY SETTING DEFINITION
*********************************************************************/
typedef enum {
  Camera_Host_Overlay_FontSize_Large= 0x00,
  Camera_Host_Overlay_FontSize_Medium,
  Camera_Host_Overlay_FontSize_Small,
} Camera_Host_Overlay_FontSize_Type;

typedef enum {
  Camera_Host_Overlay_Position_TopLeft= 0x00,
  Camera_Host_Overlay_Position_TopRight,
  Camera_Host_Overlay_Position_BottomLeft,
  Camera_Host_Overlay_Position_BottomRight,
} Camera_Host_Overlay_Position_Type;

typedef struct _CameraHostAPI_OverlayColor_Param_ {
  uint8_t               Color_R;
  uint8_t               Color_G;
  uint8_t               Color_B;
  uint8_t               Alpha;
} CameraHostAPI_OverlayColor_Param,*pCameraHostAPI_OverlayColor_Param;

/********************************************************************
    APPEARRANCE SETTING DEFINITION
*********************************************************************/
typedef enum {
  Camera_Host_Flip_Off= 0x00,
  Camera_Host_Flip_Horizontal,
  Camera_Host_Flip_Vertical,
} Camera_Host_Flip_Type;

typedef enum {
  Camera_Host_Rotation_0= 0x00,
  Camera_Host_Rotation_90,
  Camera_Host_Rotation_180,
  Camera_Host_Rotation_270,
} Camera_Host_Rotation_Type;
/********************************************************************
    NETWORK SETTING DEFINITION
*********************************************************************/
typedef enum {
  Camera_Host_Network_DHCP_IPV4= 0x00,
  Camera_Host_Network_DHCP_IPV6,
  Camera_Host_Network_IPV6,
  Camera_Host_Network_STatic_IPV4,
  Camera_Host_Network_STatic_IPV6,
  Camera_Host_Network_Type_Dummy     = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Network_Type;

typedef enum {
  Camera_Host_DHCP_FallbackIP_IPV4_Static         = 0x00,  
  Camera_Host_DHCP_FallbackIP_IPV4_DHCP           = 0x01,  
  Camera_Host_DHCP_FallbackIP_Dummy               = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_DHCP_FallbackIP_Type;

/********************************************************************
    ADVANCED SETTING DEFINITION
*********************************************************************/
typedef enum {
  Camera_Host_Zoom_Level_0= 0x00,
  Camera_Host_Zoom_Level_1,
  Camera_Host_Zoom_Level_2,
  Camera_Host_Zoom_Level_3,
  Camera_Host_Zoom_Level_4,
  Camera_Host_Zoom_Level_5,
  Camera_Host_Zoom_Level_6,
  Camera_Host_Zoom_Level_7,
  Camera_Host_Zoom_Level_8,
  Camera_Host_Zoom_Level_9,
  Camera_Host_Zoom_Level_Dummy     = CAMERA_HOST_DUMMY_VALUE
}Camera_Host_Zoom_Level;

typedef enum {
  Camera_Host_MFSpeed_Level_1         = 0x01,  
  Camera_Host_MFSpeed_Level_2         = 0x02,  
  Camera_Host_MFSpeed_Level_3         = 0x03,  
  Camera_Host_MFSpeed_Level_4         = 0x04,  
  Camera_Host_MFSpeed_Level_Dummy     = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_MFSpeed_Type;

typedef enum {
  Camera_Host_Iris_Level_0             = 0x00,  
  Camera_Host_Iris_Level_1             = 0x01,  
  Camera_Host_Iris_Level_2             = 0x02,  
  Camera_Host_Iris_Level_3             = 0x03,  
  Camera_Host_Iris_Level_4             = 0x04,  
  Camera_Host_Iris_Level_5             = 0x05, 
  Camera_Host_Iris_Level_6             = 0x06, 
  Camera_Host_Iris_Level_7             = 0x07, 
  Camera_Host_Iris_Level_8             = 0x08,     
  Camera_Host_Iris_Level_Dummy         = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Iris_Type;

/********************************************************************
    RECORDING SETTING DEFINITION
*********************************************************************/
typedef enum {
  Camera_Host_Recording_OverWrite= 0x00,
  Camera_Host_Recording_ToFull,
  Camera_Host_Recording_Type_Dummy              = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Recording_Type;

typedef enum {
  Camera_Host_Recording_FileSize_Type_Min     = 0x00,  
  Camera_Host_Recording_FileSize_Type_MB      = 0x01,
  Camera_Host_Recording_FileSize_Type_Dummy   = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Recording_FileSize_Type;

/********************************************************************
    DIGITAL IO SETTING DEFINITION
*********************************************************************/
typedef enum {
  Camera_Host_DIDO_GroundedCircuit= 0x00,
  Camera_Host_DIDO_OpenCircuit,
  Camera_Host_DIDO_Type_Dummy                 = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_DIDO_Type;

typedef enum {
  Camera_Host_BaseOn_Type_None                  = 0x00,  
  Camera_Host_BaseOn_Type_DI                    = 0x01,
  Camera_Host_BaseOn_Type_Event                 = 0x02,
  Camera_Host_BaseOn_Type_ICR                   = 0x03,
  Camera_Host_BaseOn_Type_Dummy                 = CAMERA_HOST_DUMMY_VALUE
}Camera_Host_BaseOn_Type;

/********************************************************************
    DATE TIME SETTING DEFINITION
*********************************************************************/
typedef enum {
  Camera_Host_DATE_FORMAT_TYPE_YEAR_MONTH_DAY          = 0x00,  //YYYY/MM/DD
  Camera_Host_DATE_FORMAT_TYPE_DAY_MONTH_YEAR          = 0x01,  //DD/MM/YYYY 
  Camera_Host_DATE_FORMAT_TYPE_MONTH_DAY_YEAR          = 0x02,  //MM/DD/YYYY
  Camera_Host_DATE_FORMAT_TYPE_DUMMY                   = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_DateFormat_Type;

typedef enum {
  Camera_Host_TIME_FORMAT_TYPE_24HR          = 0x00,  
  Camera_Host_TIME_FORMAT_TYPE_12HR          = 0x01,
  Camera_Host_TIME_FORMAT_TYPE_DUMMY         = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_TimeFormat_Type;

typedef enum {
  Camera_Host_TimeSyncSource_PC          = 0x00,  
  Camera_Host_TimeSyncSource_NTP         = 0x01,
  Camera_Host_TimeSyncSource_Manual      = 0x02,
  Camera_Host_TimeSyncSource_IEEE        = 0x03,
  Camera_Host_TimeSyncSource_DUMMY       = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_TimeSyncSource_Type;

typedef enum {
  Camera_Host_IEEE1588_Role_Type_None          = 0x00,
  Camera_Host_IEEE1588_Role_Type_Auto          = 0x01,  
  Camera_Host_IEEE1588_Role_Type_Master        = 0x02, 
  Camera_Host_IEEE1588_Role_Type_Slave         = 0x03, 
  Camera_Host_IEEE1588_Role_Type_Dummy         = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_IEEE1588_Role_Type;

typedef enum {
  Camera_Host_TimeZone_International_Date_Line_West = 0x00,  
  Camera_Host_TimeZone_Midway_Island,
  Camera_Host_TimeZone_Samoa,
  Camera_Host_TimeZone_Hawaii,
  Camera_Host_TimeZone_Alaska,
  Camera_Host_TimeZone_Pacific_Time_US,
  Camera_Host_TimeZone_Tijuana_Baja_California,
  Camera_Host_TimeZone_Mountain_Time_US,
  Camera_Host_TimeZone_Arizona,
  Camera_Host_TimeZone_Chihuahua_LaPaz_Mazatlan,
  Camera_Host_TimeZone_Central_Time_US,
  Camera_Host_TimeZone_Central_America,
  Camera_Host_TimeZone_Guadalajara_MexicoCity_Monterrey,
  Camera_Host_TimeZone_Saskatchewan,
  Camera_Host_TimeZone_Eastern_Time_US,
  Camera_Host_TimeZone_Indiana_East,
  Camera_Host_TimeZone_Bogota_Lima_Quito,
  Camera_Host_TimeZone_Caracas,
  Camera_Host_TimeZone_AtlanticTime_Canada,
  Camera_Host_TimeZone_Cuiaba,
  Camera_Host_TimeZone_Georgetown_LaPaz_ManausSanJuan,
  Camera_Host_TimeZone_Asuncion,
  Camera_Host_TimeZone_Santiago,
  Camera_Host_TimeZone_Newfoundland,
  Camera_Host_TimeZone_Brasilia,
  Camera_Host_TimeZone_BuenosAires,
  Camera_Host_TimeZone_Greenland,
  Camera_Host_TimeZone_Cayenne_Fortaleza,
  Camera_Host_TimeZone_Montevideo,
  Camera_Host_TimeZone_Mid_Atlantic,
  Camera_Host_TimeZone_Coordinated_UniversalTime_02,
  Camera_Host_TimeZone_Azores,
  Camera_Host_TimeZone_CapeVerdeIs,
  Camera_Host_TimeZone_Casablanca,
  Camera_Host_TimeZone_Coordinated_UniversalTime,
  Camera_Host_TimeZone_Dublin_Edinburgh_Lisbon_London,
  Camera_Host_TimeZone_Monrovia_Reykjavik,
  Camera_Host_TimeZone_West_Central_Africa,
  Camera_Host_TimeZone_Brussels_Copenhagen_Madrid_Paris,
  Camera_Host_TimeZone_Belgrade_Bratislava_Budapest_Ljubljana,
  Camera_Host_TimeZone_Amsterdam_Berlin_Bern_Rome_Stockholm_Vienna,
  Camera_Host_TimeZone_Sarajevo_Skopje_Warsaw_Zagreb,
  Camera_Host_TimeZone_Windhoek,
  Camera_Host_TimeZone_Damascus,
  Camera_Host_TimeZone_Amman,
  Camera_Host_TimeZone_Beirut,
  Camera_Host_TimeZone_Harare_Pretoria,
  Camera_Host_TimeZone_Jerusalem,
  Camera_Host_TimeZone_Cairo,
  Camera_Host_TimeZone_Athens_Bucharest_Istanbul,
  Camera_Host_TimeZone_Helsinki_Kyiv_Riga_Sofia_Tallinn_Vilnius,
  Camera_Host_TimeZone_Minsk,
  Camera_Host_TimeZone_Baghdad,
  Camera_Host_TimeZone_Nairobi,
  Camera_Host_TimeZone_Kuwait_Riyadh,
  Camera_Host_TimeZone_Moscow_StPetersburg_Volgograd,
  Camera_Host_TimeZone_Tehran,
  Camera_Host_TimeZone_Baku,
  Camera_Host_TimeZone_AbuDhabi_Muscat,
  Camera_Host_TimeZone_Tbilisi,
  Camera_Host_TimeZone_Yerevan,
  Camera_Host_TimeZone_PortLouis,
  Camera_Host_TimeZone_Kabul,
  Camera_Host_TimeZone_Ekaterinburg,
  Camera_Host_TimeZone_Islamabad_Karachi,
  Camera_Host_TimeZone_Tashkent,
  Camera_Host_TimeZone_Chennai_Kolkata_Mumbai_NewDelhi,
  Camera_Host_TimeZone_SriJayawardenepura,
  Camera_Host_TimeZone_Kathmandu,
  Camera_Host_TimeZone_Astana,
  Camera_Host_TimeZone_Dhaka,
  Camera_Host_TimeZone_Yangon,
  Camera_Host_TimeZone_Novosibirsk,
  Camera_Host_TimeZone_Krasnoyarsk,
  Camera_Host_TimeZone_Bangkok_Hanoi_Jakarta,
  Camera_Host_TimeZone_Beijing_Chongqing_HongKong_Urumqi,
  Camera_Host_TimeZone_Taiwan,
  Camera_Host_TimeZone_Irkutsk,
  Camera_Host_TimeZone_KualaLumpur_Singapores,
  Camera_Host_TimeZone_Perth,
  Camera_Host_TimeZone_Ulaanbaatar,
  Camera_Host_TimeZone_Osaka_Sapporo_Tokyo,
  Camera_Host_TimeZone_Yakutsk,
  Camera_Host_TimeZone_Seoul,
  Camera_Host_TimeZone_Adelaide,
  Camera_Host_TimeZone_Darwin,
  Camera_Host_TimeZone_Brisbane,
  Camera_Host_TimeZone_Canberra_Melbourne_Sydney,
  Camera_Host_TimeZone_Vladivostok,
  Camera_Host_TimeZone_Hobart,
  Camera_Host_TimeZone_Guam_PortMoresby,
  Camera_Host_TimeZone_SolomonIs_NewCaledonia,
  Camera_Host_TimeZone_Magadan,
  Camera_Host_TimeZone_Petropavlovsk_Kamchatsky,
  Camera_Host_TimeZone_Coordinated_Universal_Time_12,
  Camera_Host_TimeZone_Fiji,
  Camera_Host_TimeZone_Auckland_Wellington,
  Camera_Host_TimeZone_Nuku_alofa,
  Camera_Host_TimeZone_DUMMY       = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_TimeZone_Type;

typedef enum {
  Camera_Host_SSH_Type_Password                 = 0x00,
  Camera_Host_SSH_Type_Pubkey                   = 0x01,
  Camera_Host_SSH_Type_Dummy                    = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_SSH_Type;

typedef enum {
  Camera_Host_Exposure_Mode_Type_Multi_Metering   = 0x00,
  Camera_Host_Exposure_Mode_Type_Center_Metering  = 0x01,
  Camera_Host_Exposure_Mode_Type_ROI_Metering     = 0x02,
  Camera_Host_Exposure_Mode_Type_Dummy            = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_Exposure_Mode_Type;

typedef enum {
  Camera_Host_AE_Speed_Type_Slow    = 0x00,
  Camera_Host_AE_Speed_Type_Noraml  = 0x01,
  Camera_Host_AE_Speed_Type_Fast    = 0x02,
  Camera_Host_AE_Speed_Type_Dummy   = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_AE_Speed_Type;

typedef enum {
  Camera_Host_AE_Sensitivity_Type_Level1    = 0x00,
  Camera_Host_AE_Sensitivity_Type_Level2    = 0x01,
  Camera_Host_AE_Sensitivity_Type_Level3    = 0x02,
  Camera_Host_AE_Sensitivity_Type_Dummy     = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_AE_Sensitivity_Type;

typedef enum {
  Camera_Host_ICR_Filter_Mode_Auto      = 0x00,
  Camera_Host_ICR_Filter_Mode_Color     = 0x01,
  Camera_Host_ICR_Filter_Mode_Mono      = 0x02,
  Camera_Host_ICR_Filter_Mode_Dummy     = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_ICR_Filter_Mode;

typedef enum {
  Camera_Host_ICR_Type_Color   = 0x00,
  Camera_Host_ICR_Type_Mono    = 0x01,
  Camera_Host_ICR_Type_General = 0x02,
  Camera_Host_ICR_Type_Dummy   = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_ICR_Type;

typedef enum {
  Camera_Host_ICR_BaseOn_Type_LightSensor = 0x00,
  Camera_Host_ICR_BaseOn_Type_DI          = 0x01,
  Camera_Host_ICR_BaseOn_Type_Dummy       = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_ICR_BaseOn_Type;

typedef enum {
  Camera_Host_Advanced_ICR_LightLevel1    = 0x00,
  Camera_Host_Advanced_ICR_LightLevel2    = 0x01,
  Camera_Host_Advanced_ICR_LightLevel3    = 0x02,
  Camera_Host_Advanced_ICR_LightLevel4    = 0x03,
  Camera_Host_Advanced_ICR_LightLevel5    = 0x04,
  Camera_Host_Advanced_ICR_LightLevel_Dummy     = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_Advanced_ICR_LightLevel;

typedef enum {
  Camera_Host_ICR_BaseOn_Condition_OpenCircuit      = 0x00,
  Camera_Host_ICR_BaseOn_Condition_GroundedCircuit  = 0x01,
  Camera_Host_ICR_BaseOn_Condition_Dummy     = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_ICR_BaseOn_Condition;

typedef enum {
  Camera_Host_Advanced_Exposure_Mode_Auto               = 0x00,
  Camera_Host_Advanced_Exposure_Mode_Manual             = 0x01,
  Camera_Host_Advanced_Exposure_Mode_Priority           = 0x02,
  Camera_Host_Advanced_Exposure_Mode_Dummy              = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_Advanced_Exposure_Mode;

typedef enum {
  Camera_Host_Advanced_Exposure_Time_1_25                  = 0x00,           
  Camera_Host_Advanced_Exposure_Time_1_32                  = 0x01,
  Camera_Host_Advanced_Exposure_Time_1_40                  = 0x02,
  Camera_Host_Advanced_Exposure_Time_1_30                  = 0x03,  
  Camera_Host_Advanced_Exposure_Time_1_38                  = 0x04,   
  Camera_Host_Advanced_Exposure_Time_1_48                  = 0x05,
  Camera_Host_Advanced_Exposure_Time_1_50                  = 0x06,  
  Camera_Host_Advanced_Exposure_Time_1_60                  = 0x07,   
  Camera_Host_Advanced_Exposure_Time_1_64                  = 0x08,
  Camera_Host_Advanced_Exposure_Time_1_76                  = 0x09,  
  Camera_Host_Advanced_Exposure_Time_1_80                  = 0x0A,   
  Camera_Host_Advanced_Exposure_Time_1_95                  = 0x0B,
  Camera_Host_Advanced_Exposure_Time_1_100                 = 0x0C,
  Camera_Host_Advanced_Exposure_Time_1_120                 = 0x0D,  
  Camera_Host_Advanced_Exposure_Time_1_125                 = 0x0E,   
  Camera_Host_Advanced_Exposure_Time_1_150                 = 0x0F,
  Camera_Host_Advanced_Exposure_Time_1_160                 = 0x10,  
  Camera_Host_Advanced_Exposure_Time_1_200                 = 0x11,   
  Camera_Host_Advanced_Exposure_Time_1_250                 = 0x12,
  Camera_Host_Advanced_Exposure_Time_1_320                 = 0x13,  
  Camera_Host_Advanced_Exposure_Time_1_400                 = 0x14,   
  Camera_Host_Advanced_Exposure_Time_1_500                 = 0x15,
  Camera_Host_Advanced_Exposure_Time_1_640                 = 0x16,
  Camera_Host_Advanced_Exposure_Time_1_800                 = 0x17,  
  Camera_Host_Advanced_Exposure_Time_1_1000                = 0x18,   
  Camera_Host_Advanced_Exposure_Time_1_1250                = 0x19,
  Camera_Host_Advanced_Exposure_Time_1_1600                = 0x1A,  
  Camera_Host_Advanced_Exposure_Time_1_2000                = 0x1B,   
  Camera_Host_Advanced_Exposure_Time_1_2500                = 0x1C,
  Camera_Host_Advanced_Exposure_Time_1_3200                = 0x1D,  
  Camera_Host_Advanced_Exposure_Time_1_4000                = 0x1E,   
  Camera_Host_Advanced_Exposure_Time_1_5000                = 0x1F,
  Camera_Host_Advanced_Exposure_Time_1_6400                = 0x20,
  Camera_Host_Advanced_Exposure_Time_1_8000                = 0x21,  
  Camera_Host_Advanced_Exposure_Time_Dummy       = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_Advanced_Exposure_Time;

typedef enum {
  Camera_Host_Advanced_HDR_Level1    = 0x00,
  Camera_Host_Advanced_HDR_Level2    = 0x01,
  Camera_Host_Advanced_HDR_Level3    = 0x02,
  Camera_Host_Advanced_HDR_Level_Dummy     = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_Advanced_HDR_Level;

typedef enum {
  Camera_Host_Advanced_WDR_Level1    = 0x00,
  Camera_Host_Advanced_WDR_Level2    = 0x01,
  Camera_Host_Advanced_WDR_Level3    = 0x02,
  Camera_Host_Advanced_WDR_Level_Dummy     = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_Advanced_WDR_Level;

typedef enum {
  Camera_Host_Advanced_DNR_Level1    = 0x00,
  Camera_Host_Advanced_DNR_Level2    = 0x01,
  Camera_Host_Advanced_DNR_Level3    = 0x02,
  Camera_Host_Advanced_DNR_Level_Dummy     = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_Advanced_DNR_Level;

typedef enum {
  Camera_Host_Advanced_Focus_Mode_ContinuosAF   = 0x00,
  Camera_Host_Advanced_Focus_Mode_PushAF        = 0x01,
  Camera_Host_Advanced_Focus_Mode_Manual        = 0x02,
  Camera_Host_Advanced_Focus_Mode_Dummy         = CAMERA_HOST_DUMMY_VALUE,
} Camera_Host_Advanced_Focus_Mode;

typedef enum {
  CAMERA_HOST_NOTIFICATION_LEVEL_INFO      = 0x00,
  CAMERA_HOST_NOTIFICATION_LEVEL_WARNING   = 0x01,  
  CAMERA_HOST_NOTIFICATION_LEVEL_ERROR     = 0x02, 
  CAMERA_HOST_NOTIFICATION_LEVEL_DUMMY     = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Notification_Log_Level;

typedef enum {
  Camera_Host_Photo_Quality_VeryLow     = 0x00,  
  Camera_Host_Photo_Quality_Low         = 0x01,  
  Camera_Host_Photo_Quality_Normal      = 0x02,  
  Camera_Host_Photo_Quality_High        = 0x03,  
  Camera_Host_Photo_Quality_VeryHigh    = 0x04,
  Camera_Host_Photo_Quality_Dummy       = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Photo_Quality_Type;

typedef enum {
  Camera_Host_Stream_Resolution_Type_3840x2160    = 0x01,  
  Camera_Host_Stream_Resolution_Type_2560x1440    = 0x02,
  Camera_Host_Stream_Resolution_Type_1920x1080    = 0x04,
  Camera_Host_Stream_Resolution_Type_1280x720     = 0x08,
  Camera_Host_Stream_Resolution_Type_640x360      = 0x10,
  Camera_Host_Stream_Resolution_Type_2560x1920    = 0x20,
  Camera_Host_Stream_Resolution_Type_2048x1536    = 0x40,
  Camera_Host_Stream_Resolution_Type_1600x1200    = 0x80,
  Camera_Host_Stream_Resolution_Type_1280x960     = 0x100,
  Camera_Host_Stream_Resolution_Type_1024x768     = 0x200,
  Camera_Host_Stream_Resolution_Type_640x480      = 0x400,
  Camera_Host_Stream_Resolution_Type_320x240      = 0x800,
  Camera_Host_Stream_Resolution_Type_Dummy  = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Stream_Resolution_InputType;

typedef enum {
  Camera_Host_Web_Account_Default = 0x00,
  Camera_Host_Web_Account_Updated = 0x01,
  Camera_Host_Web_Account_Dummy   = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Web_Account_Type; 

typedef enum  {
  Camera_Host_Account_Level_Type_Admin      = 0x01,
  Camera_Host_Account_Level_Type_Operator   = 0x02,
  Camera_Host_Account_Level_Type_User       = 0x03,
  Camera_Host_Account_Level_Type_Dummy      = CAMERA_HOST_DUMMY_VALUE
} Camera_Host_Web_User_Level_Type;
/********************************************************************
    API INTERFACE RELATED TYPE DEFINITION
*********************************************************************/

typedef struct _Host_Remote_ReqMsg_Struct_  {
  Camera_Host_Event_Type    MessageID;
  uint32_t                  ReqParaLen;
  void*                     ReqParaPtr;
} Host_Remote_ReqMsg_Struct;

typedef struct _Host_Remote_ResMsg_Struct_  {
  Camera_Host_Result_Type   ResResult;
  uint32_t                  ResParaMaxLen;
  uint32_t                  ResParaLen;
  void*                     ResParaPtr;
} Host_Remote_ResMsg_Struct;

typedef struct _Host_Request_Message_ {
    Camera_Host_MsgID_Type  MessageID;
    uint32_t                DataLength;
    void*                   DataPtr;
} Host_Request_Message,*pHost_Request_Message;

extern void CameraHostAPI_EventCallback(Host_Remote_ReqMsg_Struct* ReqMessagePtr, Host_Remote_ResMsg_Struct* ResMessagePtr);
#endif  /* _AB_HOST_TYPES_H_ */