#include "user_main.h"
#include "../SEGGER/RTT/SEGGER_RTT.h"
#include "camera_irq_handler.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal_sram.h"
#include "stm32f4xx_ll_fmc.h"

SRAM_HandleTypeDef hsram;
FMC_NORSRAM_TimingTypeDef Timing;

void user_code1() {}

void user_code2() {
  // init camera
  BSP_CAMERA_Init(IMAGE_RESOLUTION);

  BSP_CAMERA_SnapshotStart(image_data);
}

void user_code3() {}

void loop() { HAL_Delay(1000); }
