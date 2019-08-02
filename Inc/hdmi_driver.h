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

typedef enum {
	CAMERA_OK = 0x00, CAMERA_ERROR = 0x01, CAMERA_TIMEOUT = 0x02
} Camera_StatusTypeDef;

uint8_t BSP_CAMERA_Init(uint32_t Resolution);
void BSP_CAMERA_ContinuousStart(uint32_t *buff);
void BSP_CAMERA_SnapshotStart(uint32_t *buff);
void BSP_CAMERA_Suspend(void);
void BSP_CAMERA_Resume(void);
uint8_t BSP_CAMERA_Stop(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_HDMI_DRIVER_H_ */
