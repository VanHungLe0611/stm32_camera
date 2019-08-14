#include "hdmi_driver.h"
#include "var_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

void BSP_CAMERA_LineEventCallback(void);
void BSP_CAMERA_VsyncEventCallback(void);
void BSP_CAMERA_FrameEventCallback(void);
void BSP_CAMERA_ErrorCallback(void);
void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState);
