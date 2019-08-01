/*
 * io_pin_driver.c
 *
 *  Created on: 01.08.2019
 *      Author: hungv
 */

#include "io_pin_driver.h"
#include "stm32f4xx_hal.h"
#include "stmpe1600.h"
#include "io.h"

#define IO_I2C_ADDRESS                   0x84

IO_DrvTypeDef *io_driver;


/**
  * @brief  Initializes and configures the IO functionalities and configures all
  *         necessary hardware resources (GPIOs, clocks..).
  * @note   BSP_IO_Init() is using HAL_Delay() function to ensure that stmpe1600
  *         IO Expander is correctly reset. HAL_Delay() function provides accurate
  *         delay (in milliseconds) based on variable incremented in SysTick ISR.
  *         This implies that if BSP_IO_Init() is called from a peripheral ISR process,
  *         then the SysTick interrupt must have higher priority (numerically lower)
  *         than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  * @retval IO_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_IO_Init(void)
{
  uint8_t ret = 1; // IO_ERROR

  /* Read ID and verify the IO expander is ready */
  if(stmpe1600_io_drv.ReadID(IO_I2C_ADDRESS) == STMPE1600_ID)
  {
    /* Initialize the IO driver structure */
    io_driver = &stmpe1600_io_drv;
    ret = 0; // IO_OK
  }

  if(ret == 0) // IO_OK
  {
    io_driver->Init(IO_I2C_ADDRESS);
    io_driver->Start(IO_I2C_ADDRESS, IO_PIN_ALL);
  }
  return ret;
}

/**
  * @brief  Gets the selected pins IT status.
  * @param  IO_Pin: Selected pins to check the status.
  *          This parameter can be any combination of the IO pins.
  * @retval IO_OK if read status OK. Other value if error.
  */
uint8_t BSP_IO_ITGetStatus(uint16_t IO_Pin)
{
  /* Return the IO Pin IT status */
  return (io_driver->ITStatus(IO_I2C_ADDRESS, IO_Pin));
}

/**
  * @brief  Clears all the IO IT pending bits.
  */
void BSP_IO_ITClear(void)
{
  /* Clear all IO IT pending bits */
  io_driver->ClearIT(IO_I2C_ADDRESS, STMPE1600_PIN_ALL);
}

/**
  * @brief  Configures the IO pin(s) according to IO mode structure value.
  * @param  IO_Pin: IO pin(s) to be configured.
  *          This parameter can be one of the following values:
  *            @arg  STMPE1600_PIN_x: where x can be from 0 to 15.
  * @param  IO_Mode: IO pin mode to configure
  *          This parameter can be one of the following values:
  *            @arg  IO_MODE_INPUT
  *            @arg  IO_MODE_OUTPUT
  *            @arg  IO_MODE_IT_RISING_EDGE
  *            @arg  IO_MODE_IT_FALLING_EDGE
  * @retval IO_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_IO_ConfigPin(uint16_t IO_Pin, IO_ModeTypedef IO_Mode)
{
  /* Configure the selected IO pin(s) mode */
  io_driver->Config(IO_I2C_ADDRESS, (uint16_t )IO_Pin, IO_Mode);

  return 0;
}

/**
  * @brief  Sets the selected pins state.
  * @param  IO_Pin: Selected pins to write.
  *          This parameter can be any combination of the IO pins.
  * @param  PinState: New pins state to write
  */
void BSP_IO_WritePin(uint16_t IO_Pin, uint8_t PinState)
{
  /* Set the Pin state */
  io_driver->WritePin(IO_I2C_ADDRESS, IO_Pin, PinState);
}

/**
  * @brief  Gets the selected pins current state.
  * @param  IO_Pin: Selected pins to read.
  *          This parameter can be any combination of the IO pins.
  * @retval The current pins state
  */
uint16_t BSP_IO_ReadPin(uint16_t IO_Pin)
{
 return(io_driver->ReadPin(IO_I2C_ADDRESS, IO_Pin));
}

/**
  * @brief  Toggles the selected pins state.
  * @param  IO_Pin: Selected pins to toggle.
  *          This parameter can be any combination of the IO pins.
  */
void BSP_IO_TogglePin(uint16_t IO_Pin)
{
  /* Toggle the current pin state */
  if(io_driver->ReadPin(IO_I2C_ADDRESS, IO_Pin) == 1) /* Set */
  {
    io_driver->WritePin(IO_I2C_ADDRESS, IO_Pin, 0); /* Reset */
  }
  else
  {
    io_driver->WritePin(IO_I2C_ADDRESS, IO_Pin, 1); /* Set */
  }
}






