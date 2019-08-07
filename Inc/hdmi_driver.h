/*
 * hdmi_driver.h
 *
 *  Created on: 01.08.2019
 *      Author: hungv
 */

#ifndef INC_HDMI_DRIVER_H_
#define INC_HDMI_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define DSP_CTRL_REG 0x00
#define SENSOR_CTRL_REG 0x01

typedef enum {
	CAMERA_OK = 0x00, CAMERA_ERROR = 0x01, CAMERA_TIMEOUT = 0x02
} Camera_StatusTypeDef;

uint8_t BSP_CAMERA_Init(uint32_t Resolution);
void BSP_CAMERA_ContinuousStart(uint8_t *buff);
void BSP_CAMERA_SnapshotStart(uint8_t *buff);
void BSP_CAMERA_Suspend(void);
void BSP_CAMERA_Resume(void);
uint8_t BSP_CAMERA_Stop(void);
/* Camera features functions prototype */
void    BSP_CAMERA_ContrastBrightnessConfig(uint32_t contrast_level, uint32_t brightness_level);
void    BSP_CAMERA_BlackWhiteConfig(uint32_t Mode);
void    BSP_CAMERA_ColorEffectConfig(uint32_t Effect);
/* Camera interrupts and callbacks functions */
void    BSP_CAMERA_LineEventCallback(void);
void    BSP_CAMERA_VsyncEventCallback(void);
void    BSP_CAMERA_FrameEventCallback(void);
void    BSP_CAMERA_ErrorCallback(void);

/* To be called in DCMI_IRQHandler function */
void    BSP_CAMERA_IRQHandler(void);
/* To be called in DMA2_Stream1_IRQHandler function */
void    BSP_CAMERA_DMA_IRQHandler(void);

/* utilities function */
uint8_t CAMERA_readRegValue(uint8_t REG_ADDRESS);
void CAMERA_writeRegValue(_Bool REG_BANK_SEL, uint8_t REG_ADDRESS, uint8_t VALUE);

#ifdef __cplusplus
}
#endif

#endif /* INC_HDMI_DRIVER_H_ */
