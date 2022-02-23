/**
    @mainpage Ability Host APIs
    
    @section Description
    This document explains common API in Ability's MiddleWare Layer.
*/

/**
    @brief Header file of ability OS API definition.

    @file ab_host_api.h

    @note Nothing.
*/

#ifndef _AB_HOST_API_H_
#define _AB_HOST_API_H_

//*******************************************************************************
//                              I N C L U D E   F I L E
//*******************************************************************************
#include "ab_host_types.h"

//*******************************************************************************
//                              C O N S T A N T S
//*******************************************************************************
#ifndef CAMERA_HOST_VERSION
#define CAMERA_HOST_VERSION    0x000001 ///< Ver 0x000001
#endif

#define CAMERA_HOST_GET_FRAME_INFO_WITH_IPC 1

/********************************************************************
    TYPE DEFINITION
********************************************************************/

#define STREAM_OUT_ITEMS_MAX_SIZE           2000
#define STREAM_OUT_DISPLAY_TEXT_LEN         32
#define STREAM_OUT_DISPLAY_SHORT_TEXT_LEN   16
#define STREAM_OUT_DISPLAY_LONG_TEXT_LEN    64

#define CUSTOMZIED_SETTING_VALUE_MAX_SIZE   1024
#define APP_NAME_MAX_STR_LENGTH             128

typedef struct _CameraHostAPI_General_Res_{
    Camera_Host_Result_Type Result;
}CameraHostAPI_General_Res,*pCameraHostAPI_General_Res;

/********************************************************************
    STREAM IN STRUCTURE DEFINITIONS
********************************************************************/
typedef struct _CameraHostAPI_StreamInit_Config_Struc_ {
    uint8_t FrameType; // regerence Camera_Host_Stream_Frame_Format_Type
    uint8_t FPS;
	uint8_t Reserved[2];
    uint32_t ResolutionWidth;
    uint32_t ResolutionHeight;
    uint16_t ROI_X;
	uint16_t ROI_Y;
	uint16_t ROI_Width;
	uint16_t ROI_Height;
    uint8_t Reserved2[8];
} CameraHostAPI_StreamInit_Config_Struc,*pCameraHostAPI_StreamInit_Config_Struc;

typedef struct _CameraHostAPI_SubStream_Config_Struc_ {
    uint8_t FrameType; // regerence Camera_Host_Stream_Frame_Format_Type
	uint8_t Reserved[3];
    uint32_t ResolutionWidth;
    uint32_t ResolutionHeight;
    uint8_t Reserved2[8];
} CameraHostAPI_SubStream_Config_Struc,*pCameraHostAPI_SubStream_Config_Struc;

typedef struct _CameraHostAPI_ToFStream_Config_Struc_ {
  uint8_t FrameType; // regerence Camera_Host_Stream_Frame_Format_Type
  uint8_t Reserved[3];
  uint32_t ResolutionWidth;
  uint32_t ResolutionHeight;
  uint16_t ROI_X;
  uint16_t ROI_Y;
  uint16_t ROI_Width;
  uint16_t ROI_Height;
    uint8_t Reserved2[8];
} CameraHostAPI_ToFStream_Config_Struc,*pCameraHostAPI_ToFStream_Config_Struc;

typedef struct _CameraHostAPI_StreamIn_Init_Req_ {
    uint8_t Mode;
    uint8_t StreamNum;
    uint8_t ToFMode;
	uint8_t Reserved[5];
	CameraHostAPI_StreamInit_Config_Struc MainStreamConfig;
	CameraHostAPI_SubStream_Config_Struc SubStreamConfig;
    CameraHostAPI_ToFStream_Config_Struc ToFStreamConfig;
} CameraHostAPI_StreamIn_Init_Req,*pCameraHostAPI_StreamIn_Init_Req;

typedef struct _CameraHostAPI_StreamIn_GetVideoFrame_Req_ {
  uint8_t Reserved[8];
} CameraHostAPI_StreamIn_GetVideoFrame_Req,*pCameraHostAPI_StreamIn_GetVideoFrame_Req;

typedef struct _CameraHostAPI_FrameData_Param_ {
    uint8_t *DataPtr;
	uint32_t DataLen;
	uint8_t Reserved[8];
} CameraHostAPI_FrameData_Param,*pCameraHostAPI_FrameData_Param;

typedef struct _CameraHostAPI_StreamIn_GetVideoFrame_Res_ {
  uint8_t PoolIndex;
  uint8_t Reserved[3];
  uint64_t PTS;
  CameraHostAPI_FrameData_Param Frame[2];
} CameraHostAPI_StreamIn_GetVideoFrame_Res,*pCameraHostAPI_StreamIn_GetVideoFrame_Res;

typedef struct _CameraHostAPI_StreamIn_GetToFFrame_Req_ {
  uint8_t Reserved[8];
} CameraHostAPI_StreamIn_GetToFFrame_Req,*pCameraHostAPI_StreamIn_GetToFFrame_Req;

typedef struct _CameraHostAPI_StreamIn_GetToFFrame_Res_ {
  uint8_t PoolIndex;
  uint8_t Reserved[3];
  uint64_t PTS;
  CameraHostAPI_FrameData_Param Frame[2];
} CameraHostAPI_StreamIn_GetToFFrame_Res,*pCameraHostAPI_StreamIn_GetToFFrame_Res;

/********************************************************************
    STREAM OUT STRUCTURE DEFINITIONS
********************************************************************/
typedef struct _CameraHostAPI_Display_Text_Struc_ {
    uint8_t     GroupID;
    uint8_t     FontSize;
    uint8_t     Reserved[2];
    uint32_t    TextColor;       //ARGB8888
    uint32_t    BackgroundColor; //ARGB8888
    uint16_t    PositionX;
    uint16_t    PositionY;
    uint8_t     Content[STREAM_OUT_DISPLAY_TEXT_LEN];
} CameraHostAPI_Display_Text_Struc,*pCameraHostAPI_Display_Text_Struc;

typedef struct _CameraHostAPI_Display_ShortText_Struc_ {
    uint8_t     GroupID;
    uint8_t     FontSize;
    uint8_t     Reserved[2];
    uint32_t    TextColor;       //ARGB8888
    uint32_t    BackgroundColor; //ARGB8888
    uint16_t    PositionX;
    uint16_t    PositionY;
    uint8_t     Content[STREAM_OUT_DISPLAY_SHORT_TEXT_LEN];
} CameraHostAPI_Display_ShortText_Struc,*pCameraHostAPI_Display_ShortText_Struc;

typedef struct _CameraHostAPI_Display_LongText_Struc_ {
    uint8_t     GroupID;
    uint8_t     FontSize;
    uint8_t     Reserved[2];
    uint32_t    TextColor;       //ARGB8888
    uint32_t    BackgroundColor; //ARGB8888
    uint16_t    PositionX;
    uint16_t    PositionY;
    uint8_t     Content[STREAM_OUT_DISPLAY_LONG_TEXT_LEN];
} CameraHostAPI_Display_LongText_Struc,*pCameraHostAPI_Display_LongText_Struc;

typedef struct _CameraHostAPI_Display_Line_Struc_ {
    uint8_t     GroupID;
    uint8_t     LineWidth;
    uint8_t     Reserved[2];
    uint32_t    Color;       //ARGB8888
    uint16_t    StartX;
    uint16_t    StartY;
    uint16_t    EndX;
    uint16_t    EndY;
} CameraHostAPI_Display_Line_Struc,*pCameraHostAPI_Display_Line_Struc;

typedef struct _CameraHostAPI_Display_Rectangle_Struc_ {
    uint8_t     GroupID;
    uint8_t     LineWidth;
    uint8_t     Reserved[2];
    uint32_t    Color;       //ARGB8888
    uint16_t    PositionX;
    uint16_t    PositionY;
    uint16_t    Width;
    uint16_t    Height;
} CameraHostAPI_Display_Rectangle_Struc,*pCameraHostAPI_Display_Rectangle_Struc;

typedef struct _CameraHostAPI_Display_Circle_Struc_ {
    uint8_t     GroupID;
    uint8_t     Enable;
    uint8_t     Reserved[2];
    uint32_t    Color;       //ARGB8888
    uint16_t    CenterPositionX;
    uint16_t    CenterPositionY;
    uint16_t    InnerRadius;
    uint16_t    OuterRadius;
} CameraHostAPI_Display_Circle_Struc,*pCameraHostAPI_Display_Circle_Struc;

typedef struct _CameraHostAPI_Display_BasicHumanBody_Struc_ {
    CameraHostAPI_Display_Circle_Struc  Head;
    CameraHostAPI_Display_Circle_Struc  Neck;
    CameraHostAPI_Display_Circle_Struc  LeftShoulder;
    CameraHostAPI_Display_Circle_Struc  RightShoulder;
    CameraHostAPI_Display_Circle_Struc  LeftElbow;
    CameraHostAPI_Display_Circle_Struc  RightElbow;
    CameraHostAPI_Display_Circle_Struc  LeftWrist;
    CameraHostAPI_Display_Circle_Struc  RightWrist;
    CameraHostAPI_Display_Circle_Struc  LeftThigh;
    CameraHostAPI_Display_Circle_Struc  RightThigh;
    CameraHostAPI_Display_Circle_Struc  LeftKnee;
    CameraHostAPI_Display_Circle_Struc  RightKnee;
    CameraHostAPI_Display_Circle_Struc  LeftFoot;
    CameraHostAPI_Display_Circle_Struc  RightFoot;
    CameraHostAPI_Display_Circle_Struc  Pelvis;
} CameraHostAPI_Display_BasicHumanBody_Struc,*pCameraHostAPI_Display_BasicHumanBody_Struc;

typedef struct _CameraHostAPI_Display_SimpleFDFR_Struc_ {
    uint16_t    Left;
    uint16_t    Top;
    uint16_t    Right;
    uint16_t    Bottom;
    uint32_t    Color;
    uint8_t     Label[32];
} CameraHostAPI_Display_SimpleFDFR_Struc,*pCameraHostAPI_Display_SimpleFDFR_Struc;

typedef struct _CameraHostAPI_PointPosition_Struc_ {
    uint16_t    X;
    uint16_t    Y;
} CameraHostAPI_PointPosition_Struc,*pCameraHostAPI_PointPosition_Struc;

typedef struct _CameraHostAPI_Display_Polygon_Struc_ {
    uint8_t                             PointNumber;
    uint8_t                             Reserved[3];
    uint32_t                            Color;
    CameraHostAPI_PointPosition_Struc   Points[16];
} CameraHostAPI_Display_Polygon_Struc,*pCameraHostAPI_Display_Polygon_Struc;

typedef struct _CameraHostInterface_StreamOut_Start_Req_ {
    Camera_Host_Stream_Out_SyncMode_Type SyncMode;
} CameraHostInterface_StreamOut_Start_Req,*pCameraHostInterface_StreamOut_Start_Req;

typedef struct _CameraHostAPI_StreamOut_FrameUpdate_Req_ {
    uint32_t TargetWidth;
    uint32_t TargetHeight;
    uint16_t ItemsLength;
    uint8_t  ItemNumber;
    uint8_t  Reserved[1];
    uint8_t  Items[STREAM_OUT_ITEMS_MAX_SIZE]; 
} CameraHostAPI_StreamOut_FrameUpdate_Req,*pCameraHostAPI_StreamOut_FrameUpdate_Req;

typedef struct _CameraHostAPI_StreamOut_Data_Req_ {
    uint64_t PTS;
    uint32_t Length;
    uint8_t  OnvifWrapperEnable;//0:Disable/1:Enable the ONVIF metadata header/tailer
    uint8_t  Reserved[3];
	uint8_t* DataPtr;
} CameraHostAPI_StreamOut_Data_Req,*pCameraHostAPI_StreamOut_Data_Req;

typedef struct _CameraHostAPI_GetSetting_CustomziedReq_ {
    uint32_t ID;
    uint8_t  Reserved[8];
} CameraHostAPI_GetSetting_CustomziedReq,*pCameraHostAPI_GetSetting_CustomziedReq;

/********************************************************************
    SETTING STRUCTURE DEFINITIONS
********************************************************************/
typedef struct _CameraHostAPI_ImageParameter_Para_ {
    Camera_Host_Result_Type         Result;
    uint32_t                        Brightness;
    uint32_t                        Contrast;
    uint32_t                        ColorDesaturation;
    uint32_t                        Sharpness;
    Camera_Host_WB_Type             WBType;
    uint32_t                        WBColorLevel;
    uint32_t                        Gamma;
} CameraHostAPI_ImageParameter_Para,*pCameraHostAPI_ImageParameter_Para;

typedef struct _CameraHostAPI_Stream_Param_ {
    Camera_Host_Result_Type             Result;
    Camera_Host_Switch_Type             Enable;
    Camera_Host_StreamFormat_Type       Format;
    Camera_Host_StreamResolution_Type   Resolution;
    uint8_t                             Fps;
    uint8_t                             GOP;
    uint16_t                            TargetBitrate;
    Camera_Host_StreamMode_Type         Mode;
    Camera_Host_StreamQuality_Type      Quality;
    Camera_Host_StreamAudio_Type        AudioFormat;
} CameraHostAPI_Stream_Param,*pCameraHostAPI_Stream_Param;

typedef struct _CameraHostAPI_OverlayText_Param_ {
	Camera_Host_Result_Type 			Result;
	Camera_Host_Switch_Type 	 		Enable;
	char 								Text[CAMERA_NAME_LENGTH];
	Camera_Host_Overlay_FontSize_Type 	FontSize;
	Camera_Host_Overlay_Position_Type 	Position;
    CameraHostAPI_OverlayColor_Param    Color;
} CameraHostAPI_OverlayText_Param,*pCameraHostAPI_OverlayText_Param;

typedef struct _CameraHostAPI_OverlayTime_Param_ {
	Camera_Host_Result_Type 			Result;
	Camera_Host_Switch_Type 	 		Enable;
	Camera_Host_Overlay_FontSize_Type 	FontSize;
	CameraHostAPI_OverlayColor_Param 	Color;
	Camera_Host_Overlay_Position_Type 	Position;
} CameraHostAPI_OverlayTime_Param,*pCameraHostAPI_OverlayTime_Param;

typedef struct _CameraHostAPI_OverlayImage_Param_ {
    Camera_Host_Result_Type             Result;
    Camera_Host_Switch_Type             Enable;
    Camera_Host_Overlay_Position_Type   Position;
} CameraHostAPI_OverlayImage_Param,*pCameraHostAPI_OverlayImage_Param;

typedef struct _CameraHostAPI_Audio_Param_ {
	Camera_Host_Result_Type 			Result;
	Camera_Host_Switch_Type 			SpeakerEnable;
	uint8_t       						SpeakerGain;
	Camera_Host_Switch_Type 			MicEnable;
	uint8_t       						MicGain;
} CameraHostAPI_Audio_Param,*pCameraHostAPI_Audio_Param;

typedef struct _CameraHostAPI_ImageConfig_Para_ {
	Camera_Host_Result_Type 		Result;
	Camera_Host_Flip_Type 			Flip;
	Camera_Host_Rotation_Type 		Rotation;
    Camera_Host_Switch_Type         LDCEnable;
    Camera_Host_Capture_Freq_Type   CaptureFreq;
} CameraHostAPI_ImageConfig_Para,*pCameraHostAPI_ImageConfig_Para;

typedef struct _CameraHostAPI_Network_Param_ {
  Camera_Host_Result_Type       Result;
  Camera_Host_Network_Type      Type;
  Camera_Host_DHCP_FallbackIP_Type    FallbackIPType;
  char                    IPAddress[CAMERA_NETWORK_PARAMETER_LENGTH];
  char                    SubnetMask[CAMERA_NETWORK_PARAMETER_LENGTH];
  char                    Gateway[CAMERA_NETWORK_PARAMETER_LENGTH];
  char                    PrimaryDNS[CAMERA_NETWORK_PARAMETER_LENGTH];
  char                    SecondDNS[CAMERA_NETWORK_PARAMETER_LENGTH];
} CameraHostAPI_Network_Para,*pCameraHostAPI_Network_Para;

typedef struct _CameraHostAPI_Zoom_Param_ {
    Camera_Host_Result_Type             Result;
    Camera_Host_Zoom_Level ZoomLevel;
} CameraHostAPI_Zoom_Param,*pCameraHostAPI_Zoom_Param;

typedef struct _CameraHostAPI_ContinuosAF_Param_ {
    Camera_Host_Result_Type             Result;
    Camera_Host_Switch_Type Enable;
} CameraHostAPI_ContinuosAF_Param,*pCameraHostAPI_ContinuosAF_Param;

typedef struct _CameraHostAPI_AutoFocus_Param_ {
    Camera_Host_Result_Type             Result;
    Camera_Host_Switch_Type Enable;
} CameraHostAPI_AutoFocus_Param,*pCameraHostAPI_AutoFocus_Param;

typedef struct _CameraHostAPI_ManualFocus_Param_ {
    Camera_Host_Result_Type             Result;
    int8_t FocusLevel;
} CameraHostAPI_ManualFocus_Param,*pCameraHostAPI_ManualFocus_Param;

typedef struct _CameraHostAPI_AutoIris_Param_ {
    Camera_Host_Result_Type             Result;
    Camera_Host_Switch_Type Enable;
} CameraHostAPI_AutoIris_Param,*pCameraHostAPI_AutoIris_Param;

typedef struct _CameraHostAPI_ManualIris_Param_ {
    Camera_Host_Result_Type  Result;
    int8_t IrisLevel;
} CameraHostAPI_ManualIris_Param,*pCameraHostAPI_ManualIris_Param;

typedef struct _CameraHostAPI_MFSpeed_Param_ {
    Camera_Host_Result_Type  Result;
    Camera_Host_MFSpeed_Type MFSpeedLevel;
} CameraHostAPI_MFSpeed_Param,*pCameraHostAPI_MFSpeed_Param;

typedef struct _CameraHostAPI_Recording_Param_ {
  Camera_Host_Result_Type             Result;
  Camera_Host_Switch_Type             Enable;
  Camera_Host_Recording_Type          RecordingType;
  Camera_Host_Recording_FileSize_Type RecordingFileSizeType;
  uint32_t                            FilesizeValue;
  uint64_t                            RecordingLimitMB;
  uint64_t                            RecordedSizeMB;
} CameraHostAPI_Recording_Param,*pCameraHostAPI_Recording_Param;

typedef struct _CameraHostAPI_AE_Mode_Para_ {
    Camera_Host_Result_Type     Result;
    Camera_Host_AE_Mode_Type    Mode;
    unsigned int                ROIX;
    unsigned int                ROIY;
    unsigned int                ROIWidth;
    unsigned int                ROIHeight;
    unsigned int                StreamWidth;
    unsigned int                StreamHeight;
} CameraHostAPI_AE_Mode_Para,*pCameraHostAPI_AE_Mode_Para;

typedef struct _CameraHostAPI_Digital_IO_Info_ {
    Camera_Host_Switch_Type     SwitchType;
    Camera_Host_DIDO_Type       NormalState;
    Camera_Host_DIDO_Type       CurrentState;
    Camera_Host_BaseOn_Type     BaseOnType;
} CameraHostAPI_Digital_IO_Info,*pCameraHostAPI_Digital_IO_Info;

typedef struct _CameraHostAPI_Digital_IO_Para_ {
    Camera_Host_Result_Type             Result;
    CameraHostAPI_Digital_IO_Info       InputInfo;
    CameraHostAPI_Digital_IO_Info       OutputInfo;
} CameraHostAPI_Digital_IO_Para,*pCameraHostAPI_Digital_IO_Para;

typedef struct _CameraHostAPI_GeneralInfo_Para_ {
    Camera_Host_Result_Type             Result;
    char       Manufacturer[CAMERA_NAME_LENGTH];
    char       Model[CAMERA_NAME_LENGTH];
    char       SerialNumber[CAMERA_NAME_LENGTH];
    char       HardwareVersion[CAMERA_NAME_LENGTH];
    char       FirmwareVersion[CAMERA_NAME_LENGTH];
} CameraHostAPI_GeneralInfo_Para,*pCameraHostAPI_GeneralInfo_Para;

typedef struct _CameraHostAPI_DateTime_Para_  {
    int32_t TimeHour;
    int32_t TimeMin;
    int32_t TimeSec;
    int32_t DateYear;
    int32_t DateMonth;
    int32_t DateDay;
} CameraHostAPI_DateTime_Para, *pCameraHostAPI_DateTime_Para;

typedef struct _CameraHostAPI_DateTimeConfig_Para_  {
    Camera_Host_Result_Type           Result;
    Camera_Host_TimeSyncSource_Type   TimeSyncSourceType;
    Camera_Host_IEEE1588_Role_Type    RoleType;
    Camera_Host_Switch_Type           DaylightSavingSwitchType;
    Camera_Host_TimeZone_Type         TimeZoneType;
    Camera_Host_DateFormat_Type       DateFormatType;
    Camera_Host_TimeFormat_Type       TimeFormatType;
    CameraHostAPI_DateTime_Para       DateTime;
    char                              NTPAddress[NTPSERVER_MAX_STRLEN];
} CameraHostAPI_DateTimeConfig_Para, *pCameraHostAPI_DateTimeConfig_Para;

typedef struct _CameraHostAPI_SSHService_Para_  {
    Camera_Host_Result_Type      Result;
    Camera_Host_Switch_Type      Enable;
    Camera_Host_SSH_Type         Type;
    uint32_t                     Port;
    char                         Password[CAMERA_SSH_PASSWORD_MAX_STR_LEN];
    char                         PubkeyFilePath[CAMERA_SSH_PUBLIC_KEY_FILE_NAME_MAX_STR_LEN];
} CameraHostAPI_SSHService_Para, *pCameraHostAPI_SSHService_Para;

typedef struct _CameraHostAPI_Network_Discovery_Para_  {
    Camera_Host_Result_Type           Result;
    Camera_Host_Switch_Type           WSDSwitchType;
    Camera_Host_Switch_Type           MDNSSwitchType;
} CameraHostAPI_Network_Discovery_Para, *pCameraHostAPI_Network_Discovery_Para;

typedef struct _CameraHostAPI_Exposure_Mode_Para_ {
    Camera_Host_Result_Type         Result;
    Camera_Host_Exposure_Mode_Type  Mode;
    unsigned int                    AESpeed;
    unsigned int                    Sensitivity;
    unsigned int                    ROIX;
    unsigned int                    ROIY;
    unsigned int                    ROIWidth;
    unsigned int                    ROIHeight;
} CameraHostAPI_Exposure_Mode_Para,*pCameraHostAPI_Exposure_Mode_Para;

typedef struct _CameraHostAPI_Advanced_ICR_Para_ {
    Camera_Host_ICR_Filter_Mode         Mode;
    Camera_Host_ICR_BaseOn_Type         BaseOnType;
    Camera_Host_Switch_Type             ICRSync;
    Camera_Host_Advanced_ICR_LightLevel LightLevel;
    Camera_Host_ICR_BaseOn_Condition    BaseOnCondition;
    Camera_Host_Switch_Type             ICRIntensityEnable;
    uint32_t                            ICRIntensityValue;
    uint8_t                             DetectionInterval;
} CameraHostAPI_Advanced_ICR_Para,*pCameraHostAPI_Advanced_ICR_Para;

typedef struct _CameraHostAPI_Advanced_Exposure_Para_ {
    Camera_Host_Advanced_Exposure_Mode  Mode;
    Camera_Host_Switch_Type             GainAuto;
    unsigned int                        MaxGain;
    unsigned int                        MinGain;
    unsigned int                        GainValue;
    int                                 EVValue;
    Camera_Host_Advanced_Exposure_Time  ExpTime;
    Camera_Host_Advanced_Exposure_Time  MaxExpTime;
    Camera_Host_Advanced_Exposure_Time  MinExpTime;
    Camera_Host_Iris_Type               IrisLevel;
    Camera_Host_Iris_Type               MaxIrisLevel;
    Camera_Host_Iris_Type               MinIrisLevel;
    Camera_Host_Switch_Type             ExpAuto;
    Camera_Host_Switch_Type             IrisAuto;
} CameraHostAPI_Advanced_Exposure_Para,*pCameraHostAPI_Advanced_Exposure_Para;

typedef struct _CameraHostAPI_Advanced_HDR_Para_ {
    Camera_Host_Switch_Type             Enable;
    Camera_Host_Advanced_HDR_Level      Level;
} CameraHostAPI_Advanced_HDR_Para,*pCameraHostAPI_Advanced_HDR_Para;

typedef struct _CameraHostAPI_Advanced_WDR_Para_ {
    Camera_Host_Switch_Type             Enable;
    Camera_Host_Advanced_WDR_Level      Level;
} CameraHostAPI_Advanced_WDR_Para,*pCameraHostAPI_Advanced_WDR_Para;

typedef struct _CameraHostAPI_Advanced_DNR_Para_ {
    Camera_Host_DNR_Type                Type;
    Camera_Host_Advanced_DNR_Level      Level;
} CameraHostAPI_Advanced_DNR_Para,*pCameraHostAPI_Advanced_DNR_Para;

typedef struct _CameraHostAPI_Image_Advanced_Para_ {
  Camera_Host_Result_Type                 Result;
  CameraHostAPI_Advanced_ICR_Para         ICRPara;
  CameraHostAPI_Advanced_Exposure_Para    ExposurePara;
  CameraHostAPI_Advanced_HDR_Para         HDRPara;
  CameraHostAPI_Advanced_WDR_Para         WDRPara;
  CameraHostAPI_Advanced_DNR_Para         DNRPara;
  Camera_Host_Advanced_Focus_Mode         FocusMode;
  Camera_Host_MFSpeed_Type                MFSpeed;
  Camera_Host_ICR_Type                    ICRType;
} CameraHostAPI_Image_Advanced_Para,*pCameraHostAPI_Image_Advanced_Para;

typedef struct _CameraHostAPI_Notify_AI_Event_Para_  {
  Camera_Host_Result_Type             Result;
  Camera_Host_Notification_Log_Level  Level;
  char                                UnixTime[64];
  char                                Title[32];
  char                                Body[64];
  char                                FilePath[128];
} CameraHostAPI_Notify_AI_Event_Para, *pCameraHostAPI_Notify_AI_Event_Para;

typedef struct _CameraHostAPI_Notification_TriggerSource_Para_  {
    Camera_Host_Result_Type             Result;
    Camera_Host_Switch_Type             MotionDetectionEnabled;
    Camera_Host_Switch_Type             TamperingDetectionEnabled;
    Camera_Host_Switch_Type             AIDetectionEnabled;
} CameraHostAPI_Notification_TriggerSource_Para, *pCameraHostAPI_Notification_TriggerSource_Para;

typedef struct _CameraHostAPI_Log_Setting_Para_  {
  Camera_Host_Result_Type             Result;
  Camera_Host_Switch_Type             DeviceLogEnable;
  Camera_Host_Switch_Type             AccessLogEnable;
  Camera_Host_Switch_Type             DetectionLogEnable;
} CameraHostAPI_Log_Setting_Para, *pCameraHostAPI_Log_Setting_Para;

typedef struct _CameraHostAPI_Media_Snapshot_Para_  {
  uint32_t PreEventSnapshot;
  uint32_t PostEventSnapshot;
  Camera_Host_Photo_Quality_Type PhotoQuality;
  Camera_Host_Stream_Resolution_InputType Resolution;
}CameraHostAPI_Media_Snapshot_Para, *pCameraHostAPI_Media_Snapshot_Para;

typedef struct _CameraHostAPI_Media_Video_Para_  {
  uint32_t PreEventRecording;
  uint32_t PostEventRecording;
  Camera_Host_Stream_Resolution_InputType Resolution;
}CameraHostAPI_Media_Video_Para, *pCameraHostAPI_Media_Video_Para;

typedef struct _CameraHostAPI_AccountInfo_ {
  char                          UserName[64];
  char                          Password[64];
  Camera_Host_Web_Account_Type  AccountType;
}CameraHostAPI_AccountInfo,*pCameraHostAPI_AccountInfo;

typedef struct _CameraHostAPI_Web_Account_Para_ {
    CameraHostAPI_AccountInfo Admin;
    CameraHostAPI_AccountInfo Operator;
    CameraHostAPI_AccountInfo User;
} CameraHostAPI_Web_Account_Para,*pCameraHostAPI_Web_Account_Para;

typedef struct _CameraHostAPI_Web_Account_Regsiter_Para_ {
  char                            UserName[36];
  char                            Password[36];
  Camera_Host_Web_User_Level_Type UserLevel;
} CameraHostAPI_Web_Account_Regsiter_Para,*pCameraHostAPI_Web_Account_Regsiter_Para;

typedef struct _CameraHostAPI_Customized_Param_ {
    Camera_Host_Result_Type Result;
    uint32_t                ID;
    uint8_t                 Reserved[4];
    uint8_t                 Value[CUSTOMZIED_SETTING_VALUE_MAX_SIZE];
} CameraHostAPI_Customized_Param,*pCameraHostAPI_Customized_Param;

/********************************************************************
    FUNCTION DEFINITIONS
********************************************************************/
/**
 * @brief Launch Linux others process command via this unified API
 *
 * @param p_command:      [in]  command string
 * @param p_stdout:       [out] catch stdout string, buffer ptr_offset
 * #param ui_stdout_size:     [in]  The stdout_ptr buffer size
 *
 * @return
 *     - @b  AB_OK: Success.
 *     - @b  < 0:   Some error happened.
 *
 * Example:
 * @code
 * {
 *     TBD;
 * }
 * @endcode
**/

extern Camera_Host_Result_Type ab_host_init(void);
extern Camera_Host_Result_Type ab_host_deinit(void);
extern Camera_Host_Result_Type ab_host_watchdog_register(char* pAppNameForRegister);
extern Camera_Host_Result_Type ab_host_watchdog_unregister(char* pAppNameForUnRegister);
extern Camera_Host_Result_Type ab_host_msg_send(pHost_Request_Message RequestPtr,void* ResponsePtr);
#endif /* _AB_HOST_API_H_ */
