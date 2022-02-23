/**
    @brief Header file of ability stream get interface function definition.

    @file ab_stream_get_api.h

    @note Nothing.
*/
#ifndef __AB_STREAM_GET_API_H
#define __AB_STREAM_GET_API_H
#include<stdint.h>

typedef struct _CameraStreamGetAPI{
  uint8_t*   DataPtr;
  int32_t  DataLength;
  uint64_t PTS;
}CameraStreamGetAPI, *pCameraStreamGetAPI;

int32_t ab_stream_get_interface_init(void);
int32_t ab_stream_get_aistream_video_data(pCameraStreamGetAPI ps);

#endif