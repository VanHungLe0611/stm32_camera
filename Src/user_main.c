#include "user_main.h"
#include "stm32f4xx_hal_sram.h"
#include "stm32f4xx_ll_fmc.h"
#include "stm32f407xx.h"
#include "../SEGGER/RTT/SEGGER_RTT.h"

SRAM_HandleTypeDef hsram;
FMC_NORSRAM_TimingTypeDef Timing;

void user_code1() {

}

void user_code2() {
	//HAL_DMA_Init(&hdma_dcmi);
	BSP_CAMERA_Init(CAMERA_R160x120);
//	ov2640_Config(0x60, CAMERA_BLACK_WHITE, CAMERA_BLACK_WHITE_BW_NEGATIVE, CAMERA_BRIGHTNESS_LEVEL0);
//	uint8_t i = CAMERA_IO_Read(0x60, OV2640_DSP_IMAGE_MODE);
//	SEGGER_RTT_printf(0,"REG: 0x%x VAL: 0x%x\n", OV2640_DSP_IMAGE_MODE, CAMERA_readRegValue(OV2640_DSP_IMAGE_MODE));
//	SEGGER_RTT_printf(0,"REG: 0x%x VAL: 0x%x\n", OV2640_DSP_RA_DLMT, CAMERA_readRegValue(OV2640_DSP_RA_DLMT));
//	CAMERA_writeRegValue(SENSOR_CTRL_REG, OV2640_SENSOR_COM7, 0x08);
//	SEGGER_RTT_printf(0,"REG: 0x%x VAL: 0x%x\n", OV2640_DSP_IMAGE_MODE, CAMERA_readRegValue(OV2640_DSP_IMAGE_MODE));
//	CAMERA_writeRegValue(DSP_CTRL_REG, OV2640_DSP_IMAGE_MODE, 0x10);
//	SEGGER_RTT_printf(0,"REG: 0x%x VAL: 0x%x\n", OV2640_DSP_IMAGE_MODE, CAMERA_readRegValue(OV2640_DSP_IMAGE_MODE));
}

void user_code3() {
}

void user_code_inf_while() {


}
