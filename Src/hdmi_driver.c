/*
 * hdmi_driver.c
 *
 *  Created on: 01.08.2019
 *      Author: hungv
 */

#include "hdmi_driver.h"
#include "stm32f4xx_hal.h"
#include "i2c_driver.h"
#include "ov2640.h"
#include "var_interface.h"


//DCMI_HandleTypeDef hdcmi; // temperary not need deed because it is already defined
CAMERA_DrvTypeDef *camera;


static uint32_t current_resolution;
uint32_t GetSize(uint32_t resolution);
void BSP_CAMERA_MsInit(void);

/**
 * @brief  Initializes the camera.
 * @param  Resolution: Camera Resolution
 * @retval Camera status
 */
uint8_t BSP_CAMERA_Init(uint32_t Resolution) {
	uint8_t ret = CAMERA_ERROR;

	/* our code */
	//hdcmi_x = &hdcmi;

	/* DCMI Initialization */
	BSP_CAMERA_MsInit();
	HAL_DCMI_Init(&hdcmi);

	if (ov2640_ReadID(CAMERA_OV2640_I2C_ADDRESS) == OV2640_ID) {
		/* Initialize the camera driver structure */
		camera = &ov2640_drv;

		/* Camera Init */
		camera->Init(CAMERA_OV2640_I2C_ADDRESS, Resolution);

		/* Return CAMERA_OK status */
		ret = CAMERA_OK;
	}

	current_resolution = Resolution;

	return ret;
}

void BSP_CAMERA_MsInit(void) {
/* example code */
//	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
//
//	/*** Enable peripherals and GPIO clocks ***/
//	/* Enable DCMI clock */
//	__HAL_RCC_DCMI_CLK_ENABLE();
//
//	/* GPIO Ports Clock Enable */
//	__HAL_RCC_GPIOE_CLK_ENABLE();
//	__HAL_RCC_GPIOA_CLK_ENABLE();
//	__HAL_RCC_GPIOC_CLK_ENABLE();
//	__HAL_RCC_GPIOB_CLK_ENABLE();
//
//	/* Configure DCMI GPIO as alternate function */
//	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
//	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
//
//	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_6;
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
//	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//
//	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*our code*/
	HAL_DCMI_MspInit(&hdcmi);
}

/**
 * @brief  Starts the camera capture in continuous mode.
 * @param  buff: pointer to the camera output buffer
 */
void BSP_CAMERA_ContinuousStart(uint8_t *buff) {
	/* Start the camera capture */
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)buff,
			GetSize(current_resolution));
}

/**
 * @brief  Starts the camera capture in snapshot mode.
 * @param  buff: pointer to the camera output buffer
 */
void BSP_CAMERA_SnapshotStart(uint8_t *buff) {
	/* Start the camera capture */
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT, (uint32_t)buff,
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

	// TODO: make a camera on/off switch

	return ret;
}

uint32_t GetSize(uint32_t resolution)
{
  uint32_t size = 0;

  /* Get capture size */
  switch (resolution)
  {
  case CAMERA_R160x120:
    {
      size =  0x2580;
    }
    break;
  case CAMERA_R320x240:
    {
      size =  0x9600;
    }
    break;
  case CAMERA_R480x272:
    {
      size =  0xFF00;
    }
    break;
  case CAMERA_R640x480:
    {
      size =  0x25800;
    }
    break;
  default:
    {
      break;
    }
  }

  return size;
}

/**
  * @brief  Configures the camera contrast and brightness.
  * @param  contrast_level: Contrast level
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_CONTRAST_LEVEL4: for contrast +2
  *            @arg  CAMERA_CONTRAST_LEVEL3: for contrast +1
  *            @arg  CAMERA_CONTRAST_LEVEL2: for contrast  0
  *            @arg  CAMERA_CONTRAST_LEVEL1: for contrast -1
  *            @arg  CAMERA_CONTRAST_LEVEL0: for contrast -2
  * @param  brightness_level: Contrast level
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_BRIGHTNESS_LEVEL4: for brightness +2
  *            @arg  CAMERA_BRIGHTNESS_LEVEL3: for brightness +1
  *            @arg  CAMERA_BRIGHTNESS_LEVEL2: for brightness  0
  *            @arg  CAMERA_BRIGHTNESS_LEVEL1: for brightness -1
  *            @arg  CAMERA_BRIGHTNESS_LEVEL0: for brightness -2
  */
void BSP_CAMERA_ContrastBrightnessConfig(uint32_t contrast_level, uint32_t brightness_level)
{
  if(camera->Config != NULL)
  {
    camera->Config(CAMERA_OV2640_I2C_ADDRESS, CAMERA_CONTRAST_BRIGHTNESS, contrast_level, brightness_level);
  }
}

/**
  * @brief  Configures the camera white balance.
  * @param  Mode: black_white mode
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_BLACK_WHITE_BW
  *            @arg  CAMERA_BLACK_WHITE_NEGATIVE
  *            @arg  CAMERA_BLACK_WHITE_BW_NEGATIVE
  *            @arg  CAMERA_BLACK_WHITE_NORMAL
  */
void BSP_CAMERA_BlackWhiteConfig(uint32_t Mode)
{
  if(camera->Config != NULL)
  {
    camera->Config(CAMERA_OV2640_I2C_ADDRESS, CAMERA_BLACK_WHITE, Mode, 0);
  }
}

/**
  * @brief  Configures the camera color effect.
  * @param  Effect: Color effect
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_COLOR_EFFECT_ANTIQUE
  *            @arg  CAMERA_COLOR_EFFECT_BLUE
  *            @arg  CAMERA_COLOR_EFFECT_GREEN
  *            @arg  CAMERA_COLOR_EFFECT_RED
  */
void BSP_CAMERA_ColorEffectConfig(uint32_t Effect)
{
  if(camera->Config != NULL)
  {
    camera->Config(CAMERA_OV2640_I2C_ADDRESS, CAMERA_COLOR_EFFECT, Effect, 0);
  }
}

/**
  * @brief  Line event callback
  * @param  hdcmi: pointer to the DCMI handle
  */
void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi)
{
  BSP_CAMERA_LineEventCallback();
}

/**
  * @brief  Line Event callback.
  */
__weak void BSP_CAMERA_LineEventCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_LineEventCallback could be implemented in the user file
   */
}

/**
  * @brief  VSYNC event callback
  * @param  hdcmi: pointer to the DCMI handle
  */
void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi)
{
  BSP_CAMERA_VsyncEventCallback();
}

/**
  * @brief  VSYNC Event callback.
  */
__weak void BSP_CAMERA_VsyncEventCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_VsyncEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Frame event callback
  * @param  hdcmi: pointer to the DCMI handle
  */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
  BSP_CAMERA_FrameEventCallback();
}

/**
  * @brief  Frame Event callback.
  */
__weak void BSP_CAMERA_FrameEventCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_FrameEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Error callback
  * @param  hdcmi: pointer to the DCMI handle
  */
void HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi)
{
  BSP_CAMERA_ErrorCallback();
}

/**
  * @brief  Error callback.
  */
__weak void BSP_CAMERA_ErrorCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_ErrorCallback could be implemented in the user file
   */
}

/**
  * @brief  Handles DCMI interrupt request.
  */
void BSP_CAMERA_IRQHandler(void)
{
  HAL_DCMI_IRQHandler(&hdcmi);
}

/**
  * @brief  Handles DMA interrupt request.
  */
void BSP_CAMERA_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hdcmi.DMA_Handle);
}

