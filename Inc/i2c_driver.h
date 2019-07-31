#ifndef __I2C_DRIVER_H
#define __I2C_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "camera.h"

/**
 * @brief  Define for STM324x9I_EVAL board
 */
#if !defined (USE_STM324x9I_EVAL)
#define USE_STM324x9I_EVAL
#endif

/* Exported constant IO ------------------------------------------------------*/
#define IO_I2C_ADDRESS                   0x84
#define TS_I2C_ADDRESS                   0x82
#define TS3510_I2C_ADDRESS               0x80
#define EXC7200_I2C_ADDRESS              0x08
#define CAMERA_I2C_ADDRESS               0x60
#define AUDIO_I2C_ADDRESS                0x34
#define EEPROM_I2C_ADDRESS_A01           0xA0
#define EEPROM_I2C_ADDRESS_A02           0xA6
/* I2C clock speed configuration (in Hz)
 WARNING:
 Make sure that this define is not already declared in other files (ie.
 stm324x9I_eval.h file). It can be used in parallel by other modules. */
#ifndef BSP_I2C_SPEED
#define BSP_I2C_SPEED                        100000
#endif /* BSP_I2C_SPEED */

/* User can use this section to tailor I2Cx/I2Cx instance used and associated
 resources */
/* Definition for I2Cx clock resources */
#define EVAL_I2Cx                             I2C1
#define EVAL_I2Cx_CLK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define EVAL_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()

#define EVAL_I2Cx_FORCE_RESET()               __HAL_RCC_I2C1_FORCE_RESET()
#define EVAL_I2Cx_RELEASE_RESET()             __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define EVAL_I2Cx_SCL_PIN                     GPIO_PIN_6
#define EVAL_I2Cx_SCL_SDA_GPIO_PORT           GPIOB
#define EVAL_I2Cx_SCL_SDA_AF                  GPIO_AF4_I2C1
#define EVAL_I2Cx_SDA_PIN                     GPIO_PIN_9

/* I2C interrupt requests */
#define EVAL_I2Cx_EV_IRQn                     I2C1_EV_IRQn
#define EVAL_I2Cx_ER_IRQn                     I2C1_ER_IRQn

void I2Cx_MspInit(void);
void I2Cx_Init();
void I2Cx_ITConfig(void);
void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg);
HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
void I2Cx_Error(uint8_t Addr);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
