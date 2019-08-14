#include "user_main.h"
#include "../SEGGER/RTT/SEGGER_RTT.h"
#include "camera_irq_handler.h"
#include "stm32f407xx.h"

void user_code1() {}

void user_code2() {
  // init camera
  BSP_CAMERA_Init(IMAGE_RESOLUTION);

  BSP_CAMERA_SnapshotStart(image_data);
}

void user_code3() {}

void loop() { HAL_Delay(1000); }
