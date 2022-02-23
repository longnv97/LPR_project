#ifndef _AB_CAMERA_CV_SAMPLE_H_
#define _AB_CAMERA_CV_SAMPLE_H_
#include <stdint.h>
int CameraCvSampleWarpAffine(void);
int CameraCvSampleInit(void);
void CameraCvSampleTestCommand(int i_test_id, uint8_t *puc_parameter);

#endif // _AB_IEINTERFACE_MAIN_H_