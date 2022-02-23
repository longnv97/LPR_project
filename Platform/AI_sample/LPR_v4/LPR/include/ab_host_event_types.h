#ifndef _AB_HOST_EVENT_TYPES_H_
#define _AB_HOST_EVENT_TYPES_H_

#define CAMERA_HOST_EVENT_MESSAGE_AI_GROUP        0x05000000
#define CAMERA_HOST_EVENT_MESSAGE_WIFI2SYS        0x00020000
#define CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES    (CAMERA_HOST_EVENT_MESSAGE_AI_GROUP + CAMERA_HOST_EVENT_MESSAGE_WIFI2SYS  + 0x0000)

#define CAMERA_HOST_EVENT_AI_TEST_BUF_LEN         1024

typedef enum  {  
  CAMERA_HOST_EVENT_AI_PERSON_REGISTER                              = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F06),
  CAMERA_HOST_EVENT_AI_PERSON_UNREGISTER                            = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F07),
  CAMERA_HOST_EVENT_AI_REGISTER_STATUS_POLLING                      = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F08),
  CAMERA_HOST_EVENT_AI_DATABASE_GET                                 = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F09),
  CAMERA_HOST_EVENT_AI_ALL_PERSON_UNREGISTER                        = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F10),
  CAMERA_HOST_EVENT_AI_FACE_REGISTER_IMAGE_PATH_GET                 = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F11),
  CAMERA_HOST_EVENT_AI_FACE_REGISTER                                = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F12),
  CAMERA_HOST_EVENT_AI_FACE_UNREGISTER                              = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F13),
  CAMERA_HOST_EVENT_AI_FENCE_CONFIG_GET                             = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F14),
  CAMERA_HOST_EVENT_AI_FENCE_CONFIG_SET                             = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F15),
  CAMERA_HOST_EVENT_AI_FACE_INFO_UPDATE                             = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F16),
  CAMERA_HOST_EVENT_AI_DATABASE_IMPORT                              = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F17),
  CAMERA_HOST_EVENT_AI_DATABASE_EXPORT                              = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F18),
  CAMERA_HOST_EVENT_AI_HCT_AREA_CONFIG_GET                          = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F19),
  CAMERA_HOST_EVENT_AI_HCT_AREA_CONFIG_SET                          = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F1A),
  //VEUNQJ0
  CAMERA_HOST_EVENT_AI_UPDATE_CAMERA_MODE                           = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F20),
  CAMERA_HOST_EVENT_AI_UPDATE_CAMERA_MODE_DONE                      = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F21),
  CAMERA_HOST_EVENT_AI_UPDATE_RECOG_FACE_NUM                        = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0F22),
  CAMERA_HOST_EVENT_AI_TEST                                         = (CAMERA_HOST_EVENT_MSGGROUP_AI_MESSAGES      + 0x0FF0),
  CAMERA_HOST_EVENT_TYPE_DUMMY 										= 0xFFFFFFFF,
}Camera_Host_Event_Type;

typedef struct _Camera_Host_AI_Register_ReqParaStruct_  {
  char   Label[32];
} Camera_Host_Register_ReqParaStruct, *pCamera_Host_Register_ReqParaStruct;

typedef struct _Camera_Host_AI_UnRegister_ReqParaStruct_  {
  char Label[32];
} Camera_Host_AI_UnRegister_ReqParaStruct, *pCamera_Host_AI_UnRegister_ReqParaStruct;

typedef struct _Camera_Host_AI_Register_ResParaStruct_  {
  int32_t   Result; 
} Camera_Host_AI_Register_ResParaStruct, *pCamera_Host_AI_Register_ResParaStruct;

typedef struct _Camera_Host_AI_RegisterStatusPolling_ResParaStruct_  {
  int32_t   Result; 
} Camera_Host_AI_RegisterStatusPolling_ResParaStruct, *pCamera_Host_AI_RegisterStatusPolling_ResParaStruct;

typedef struct _Camera_Host_AI_DataBase_ResParaStruct_  {
  char FilePath[256];
  char FileName[64];
} Camera_Host_AI_DataBase_ResParaStruct, *pCamera_Host_AI_DataBase_ResParaStruct;

typedef struct _Camera_Host_AI_FaceRegister_ImagePath_ResParaStruct_  {
  char ImagePath[256];
} Camera_Host_AI_FaceRegister_ImagePath_ResParaStruct, *pCamera_Host_AI_FaceRegister_ImagePath_ResParaStruct;

typedef struct _Camera_Host_AI_FaceRegister_ReqParaStruct_  {
  char Label[32];
  char Remark[128];
  uint32_t ImageWidth;
  uint32_t ImageHeight;
} Camera_Host_AI_FaceRegister_ReqParaStruct, *pCamera_Host_AI_FaceRegister_ReqParaStruct;

typedef struct _Camera_Host_AI_FaceInfoUpdate_ReqParaStruct_  {
  char LabelCurr[32];
  char LabelNew[32];
  char Remark[128];
} Camera_Host_AI_FaceInfoUpdate_ReqParaStruct, *pCamera_Host_AI_FaceInfoUpdate_ReqParaStruct;

typedef struct _Camera_Host_AI_FaceInfoUpdate_ResParaStruct_  {
  int32_t   Result; 
} Camera_Host_AI_FaceInfoUpdate_ResParaStruct, *pCamera_Host_AI_FaceInfoUpdate_ResParaStruct;

typedef struct _Camera_Host_AI_DataBaseImport_ReqParaStruct_  {
  char FilePath[256];
} Camera_Host_AI_DataBaseImport_ReqParaStruct, *pCamera_Host_AI_DataBaseImport_ReqParaStruct;

typedef struct _Camera_Host_AI_DataBaseExport_ResParaStruct_  {
  char FilePath[256];
  char FileName[64];
} Camera_Host_AI_DataBaseExport_ResParaStruct, *pCamera_Host_AI_DataBaseExport_ResParaStruct;

typedef struct _Camera_Host_AI_FaceRegister_ResParaStruct_  {
  int32_t   Result; 
} Camera_Host_AI_FaceRegister_ResParaStruct, *pCamera_Host_AI_FaceRegister_ResParaStruct;

typedef struct _Camera_Host_AI_FaceUnRegister_ReqParaStruct_  {
  uint32_t  Index;
} Camera_Host_AI_FaceUnRegister_ReqParaStruct, *pCamera_Host_AI_FaceUnRegister_ReqParaStruct;

typedef struct _Camera_Host_AI_FaceUnRegister_ResParaStruct_  {
  int32_t   Result; 
} Camera_Host_AI_FaceUnRegister_ResParaStruct, *pCamera_Host_AI_FaceUnRegister_ResParaStruct;

typedef struct _Camera_Host_AI_Test_ReqParaStruct_  {
  int32_t  TestID;
  uint8_t  Parameters[CAMERA_HOST_EVENT_AI_TEST_BUF_LEN];
} Camera_Host_AI_Test_ReqParaStruct, *pCamera_Host_AI_Test_ReqParaStruct;

//VEUNQJ0
typedef enum {
    CAMERA_HOST_CUSTOM_CAMERA_MODE             = 0,
    CAMERA_HOST_CUSTOM_MAX_RECOG_FACE_NUM      = 1,
} Camera_Host_Customized_Setting_ID;

typedef struct _Camera_Host_AI_UpdateCameraMode_ReqParaStruct_  {
  /*
    CAMERA_MODE_TYPE_STITCH  = 0,
    CAMERA_MODE_TYPE_TELE    = 1,
    CAMERA_MODE_TYPE_WIDE    = 2,
    CAMERA_MODE_TYPE_ERROR   = -1,
  */
  uint8_t  cameraMode; 
} Camera_Host_AI_UpdateCameraMode_ReqParaStruct, *pCamera_Host_AI_UpdateCameraMode_ReqParaStruct;

typedef struct _Camera_Host_AI_UpdateRecogFaceNum_ReqParaStruct_  {
  uint8_t maxFaceNum;
} Camera_Host_AI_UpdateRecogFaceNum_ReqParaStruct, *pCamera_Host_AI_UpdateRecogFaceNum_ReqParaStruct;

typedef struct _Camera_Host_AI_PointPosition_Struc_ {
  uint16_t    X;
  uint16_t    Y;
}Camera_Host_AI_PointPosition_Struc, *pCamera_Host_AI_PointPosition_Struc;

typedef struct _Camera_Host_AI_Display_Polygon_Struc_ {
  uint8_t                               PointNumber;
  uint8_t                               Reserved[3];
  char                                  Labal[16];
  char                                  Color[16];
  Camera_Host_AI_PointPosition_Struc    Points[16];
} Camera_Host_AI_Display_Polygon_Struc, *pCamera_Host_AI_Display_Polygon_Struc;

typedef struct _Camera_Host_AI_FenceArea_ParaStruct_  {
  Camera_Host_AI_Display_Polygon_Struc Areas[3];
} Camera_Host_AI_FenceArea_ParaStruct, *pCamera_Host_AI_FenceArea_ParaStruct;

typedef struct _Camera_Host_AI_HCT_AreaPara_Struc_ {
    uint8_t                             Enable;
    uint8_t                             EntryPointIndex[2];
    uint8_t                             Reserved[1];
    Camera_Host_AI_PointPosition_Struc  Points[4];
} Camera_Host_AI_HCT_AreaPara_Struc, *pCamera_Host_AI_HCT_AreaPara_Struc;
#endif
