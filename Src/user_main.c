#include "user_main.h"
#include "stm32f4xx_hal_sram.h"
#include "stm32f4xx_ll_fmc.h"
#include "stm32f407xx.h"
#include "../SEGGER/RTT/SEGGER_RTT.h"
#include "camera_irq_handler.h"

SRAM_HandleTypeDef hsram;
FMC_NORSRAM_TimingTypeDef Timing;

void user_code1() {

}

void user_code2() {
	// init camera
	BSP_CAMERA_Init(CAMERA_R160x120);

//	ov2640_Config(0x60, CAMERA_COLOR_EFFECT, 0x00, CAMERA_BRIGHTNESS_LEVEL0);
//	uint8_t i = CAMERA_IO_Read(0x60, OV2640_DSP_IMAGE_MODE);
//	SEGGER_RTT_printf(0,"REG: 0x%x VAL: 0x%x\n", OV2640_DSP_IMAGE_MODE, CAMERA_readRegValue(OV2640_DSP_IMAGE_MODE));
//	SEGGER_RTT_printf(0,"REG: 0x%x VAL: 0x%x\n", OV2640_DSP_RA_DLMT, CAMERA_readRegValue(OV2640_DSP_RA_DLMT));
//	CAMERA_writeRegValue(SENSOR_CTRL_REG, OV2640_SENSOR_COM7, 0x08);
//	SEGGER_RTT_printf(0,"REG: 0x%x VAL: 0x%x\n", OV2640_DSP_IMAGE_MODE, CAMERA_readRegValue(OV2640_DSP_IMAGE_MODE));
	CAMERA_writeRegValue(DSP_CTRL_REG, OV2640_DSP_IMAGE_MODE, 0x00); // use for YCBCR-Format
	CAMERA_writeRegValue(DSP_CTRL_REG, OV2640_DSP_IMAGE_MODE, 0x01); // enable YCBCR-format

//	SEGGER_RTT_printf(0,"REG: 0x%x VAL: 0x%x\n", OV2640_DSP_IMAGE_MODE, CAMERA_readRegValue(OV2640_DSP_IMAGE_MODE));
//	DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
//	DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
}

void user_code3() {
}

void user_code_inf_while() {

}
