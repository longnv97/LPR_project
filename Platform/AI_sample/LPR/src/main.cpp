#include "config.hpp"


int main()
{
    int retryCount = 0;

    if(ab_host_init() != CAMERA_HOST_OK){
        printf("ab_host_init fail\n");
    }

    if(CameraHost_StreamIn_Init() != CAMERA_HOST_OK){
        printf("CameraHost_StreamIn_Init fail\n");
    }
    if(CameraHost_StreamOut_Start() != CAMERA_HOST_OK){
        printf("CameraHost_StreamOut_Init fail\n");
    }
    
    printf("Init CameraCV\n");
    camera_cv_api_init();

    while(true)
    {
        if (InferenceStart() == 0) {
            break;
        }
        retryCount++;
        printf("Xlink error and retryCount = %d\n",retryCount);
    }

    CameraHost_StreamIn_Deinit();
    CameraHost_StreamOut_Stop();
    camera_cv_api_deinit();
    ab_host_deinit();
    return 1;
}


//Test git
