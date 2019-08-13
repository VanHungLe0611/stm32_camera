#include "hdmi_driver.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_sram.h"
#include "stm32f4xx_ll_fmc.h"

extern const int IMG_SIZE_IN_BYTES;

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_dcmi;
extern DCMI_HandleTypeDef hdcmi;
extern SRAM_HandleTypeDef hsram;
extern UART_HandleTypeDef huart4;

extern uint8_t image_data[];
