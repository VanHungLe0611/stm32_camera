#include "camera_irq_handler.h"

void BSP_CAMERA_LineEventCallback(void) {
  __HAL_DCMI_CLEAR_FLAG(&hdcmi, DCMI_IT_LINE);
  lineNum++;
  SEGGER_RTT_printf(CAMERA_DEBUG_RTT_EN, "End of line %d event \n", lineNum);
}
void BSP_CAMERA_VsyncEventCallback(void) {
  __HAL_DCMI_CLEAR_FLAG(&hdcmi, DCMI_IT_VSYNC);
  SEGGER_RTT_printf(CAMERA_DEBUG_RTT_EN,
                    "Vsync event - sychronization frame\n");
  SEGGER_RTT_printf(CAMERA_DEBUG_RTT_EN, "--current num of line: %d\n",
                    lineNum);
  lineNum = CAMERA_DEBUG_RTT_EN;
  // TODO: send image over UART for preview in pc
}
void BSP_CAMERA_FrameEventCallback(void) {
  __HAL_DCMI_CLEAR_FLAG(&hdcmi, DCMI_IT_FRAME);
  HAL_UART_Transmit_DMA(&huart4, image_data, IMAGE_SIZE);
  SEGGER_RTT_printf(CAMERA_DEBUG_RTT_EN, "Frame captured event\n");
}
void BSP_CAMERA_ErrorCallback(void) {
  SEGGER_RTT_printf(CAMERA_DEBUG_RTT_EN, "Frame synchonization error event\n");
}
