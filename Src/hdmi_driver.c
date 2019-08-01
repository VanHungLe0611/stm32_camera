/*
 * hdmi_driver.c
 *
 *  Created on: 01.08.2019
 *      Author: hungv
 */

#include "hdmi_driver.h"
#include "stm32f4xx_hal.h"
#include "i2c_driver.h"
#include "io.h"
#include "ov2640.h"
#include "io_pin_driver.h"

DCMI_HandleTypeDef hdcmi;
CAMERA_DrvTypeDef *camera;

uint32_t current_resolution;
uint32_t GetSize(uint32_t resolution);
void BSP_CAMERA_MsInit(void);

/**
 * @brief  Initializes the camera.
 * @param  Resolution: Camera Resolution
 * @retval Camera status
 */
uint8_t BSP_CAMERA_Init(uint32_t Resolution) {
	uint8_t ret = CAMERA_ERROR;

	hdcmi.Instance = DCMI;
	hdcmi.Init.SynchroMode = DCMI_SYNCHRO_HARDWARE;
	hdcmi.Init.PCKPolarity = DCMI_PCKPOLARITY_FALLING;
	hdcmi.Init.VSPolarity = DCMI_VSPOLARITY_LOW;
	hdcmi.Init.HSPolarity = DCMI_HSPOLARITY_LOW;
	hdcmi.Init.CaptureRate = DCMI_CR_ALL_FRAME;
	hdcmi.Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
	hdcmi.Init.JPEGMode = DCMI_JPEG_DISABLE;

	/* Configure IO functionalities for camera detect pin */
	BSP_IO_Init();

	/* Set the camera STANDBY pin */
	BSP_IO_ConfigPin(GPIO_PIN_0, IO_MODE_OUTPUT);
	BSP_IO_WritePin(GPIO_PIN_0, SET);

	/* Check if the camera is plugged */
	if (BSP_IO_ReadPin(GPIO_PIN_3)) {
		return CAMERA_ERROR;
	}

	/* DCMI Initialization */
	BSP_CAMERA_MsInit();
	HAL_DCMI_Init(&hdcmi);

	if (ov2640_ReadID(CAMERA_I2C_ADDRESS) == OV2640_ID) {
		/* Initialize the camera driver structure */
		camera = &ov2640_drv;

		/* Camera Init */
		camera->Init(CAMERA_I2C_ADDRESS, Resolution);

		/* Return CAMERA_OK status */
		ret = CAMERA_OK;
	}

	current_resolution = Resolution;

	return ret;
}
void BSP_CAMERA_MsInit(void) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/*** Enable peripherals and GPIO clocks ***/
	/* Enable DCMI clock */
	__HAL_RCC_DCMI_CLK_ENABLE();

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* Configure DCMI GPIO as alternate function */
	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/**
 * @brief  Starts the camera capture in continuous mode.
 * @param  buff: pointer to the camera output buffer
 */
void BSP_CAMERA_ContinuousStart(uint8_t *buff) {
	/* Start the camera capture */
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t) buff,
			GetSize(current_resolution));
}

/**
 * @brief  Starts the camera capture in snapshot mode.
 * @param  buff: pointer to the camera output buffer
 */
void BSP_CAMERA_SnapshotStart(uint8_t *buff) {
	/* Start the camera capture */
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT, (uint32_t) buff,
			GetSize(current_resolution));
}

/**
 * @brief Suspend the CAMERA capture
 */
void BSP_CAMERA_Suspend(void) {
	/* Suspend the Camera Capture */
	HAL_DCMI_Suspend(&hdcmi);
}

/**
 * @brief Resume the CAMERA capture
 */
void BSP_CAMERA_Resume(void) {
	/* Start the Camera Capture */
	HAL_DCMI_Resume(&hdcmi);
}

/**
 * @brief  Stop the CAMERA capture
 * @retval Camera status
 */
uint8_t BSP_CAMERA_Stop(void) {
	DCMI_HandleTypeDef *phdcmi;

	uint8_t ret = CAMERA_ERROR;

	/* Get the DCMI handle structure */
	phdcmi = &hdcmi;

	if (HAL_DCMI_Stop(phdcmi) == HAL_OK) {
		ret = CAMERA_OK;
	}

	/* Initialize IO */
	BSP_IO_Init();

	/* Reset the camera STANDBY pin */
	BSP_IO_ConfigPin(0x0001, IO_MODE_OUTPUT);
	BSP_IO_WritePin(0x0001, RESET);

	return ret;
}

