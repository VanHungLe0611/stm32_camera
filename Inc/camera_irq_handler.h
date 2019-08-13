#include "hdmi_driver.h"
#include "var_interface.h"

void BSP_CAMERA_LineEventCallback(void);
void BSP_CAMERA_VsyncEventCallback(void);
void BSP_CAMERA_FrameEventCallback(void);
void BSP_CAMERA_ErrorCallback(void);
void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState);
FlagStatus DCMI_GetFlagStatus(uint16_t DCMI_FLAG);
void DCMI_ClearFlag(uint16_t DCMI_FLAG);
ITStatus DCMI_GetITStatus(uint16_t DCMI_IT);
