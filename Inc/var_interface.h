#include "hdmi_driver.h"
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Image mem size in bytes */
#define CAMERA_R160x120_COLOR_MEMSIZE 0x9600
#define CAMERA_R320x240_COLOR_MEMSIZE 0x25800
#define CAMERA_R480x272_COLOR_MEMSIZE 0x3FC00
#define CAMERA_R640x480_COLOR_MEMSIZE 0x96000
#define CAMERA_R160x120_MONOC_MEMSIZE 0x4B00
#define CAMERA_R320x240_MONOC_MEMSIZE 0x12C00
#define CAMERA_R480x272_MONOC_MEMSIZE 0x1FE00
#define CAMERA_R640x480_MONOC_MEMSIZE 0x4B000

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_dcmi;
extern DCMI_HandleTypeDef hdcmi;
extern UART_HandleTypeDef huart4;

extern uint8_t image_data[];

/* CAMERA GLOBAL SETTING */
#define IMAGE_RESOLUTION CAMERA_R160x120
#define IMAGE_SIZE CAMERA_R160x120_COLOR_MEMSIZE

/*RTT debug activation*/
#define CAMERA_DEBUG_RTT_EN 1

#ifdef __cplusplus
}
#endif
