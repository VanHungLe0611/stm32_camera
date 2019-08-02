#include "user_main.h"
#include "stm32f4xx_hal_sram.h"
#include "stm32f4xx_ll_fmc.h"
#include "stm32f407xx.h"

SRAM_HandleTypeDef hsram;
FMC_NORSRAM_TimingTypeDef Timing;

void user_code1() {

}

void user_code2() {
	HAL_DMA_Init(&hdma_dcmi);
	BSP_CAMERA_Init(CAMERA_R320x240);
	ov2640_Config(0x60, CAMERA_BLACK_WHITE, CAMERA_BLACK_WHITE_BW_NEGATIVE, CAMERA_BRIGHTNESS_LEVEL0);

}

void user_code3() {
}

void user_code_inf_while() {


}
