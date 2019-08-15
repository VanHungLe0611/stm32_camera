/*
 * dcmi_driver.h
 *
 *  Created on: Aug 15, 2019
 *      Author: duyanhpham
 */

#ifndef INC_DCMI_DRIVER_H_
#define INC_DCMI_DRIVER_H_

#include "i2c_driver.h"
#include "ov2640.h"
#include "stm32f4xx_hal.h"
#include "var_interface.h"

#define DSP_CTRL_REG 0x00
#define SENSOR_CTRL_REG 0x01

/* Macro for CAMERA_read-/writeRegVal functions */
#define CAMERA_OUTPUT_FORMAT_YUV422 0x00
#define CAMERA_OUTPUT_FORMAT_RAW10 0x01
#define CAMERA_OUTPUT_FORMAT_RBG565 0x02
#define CAMERA_OUTPUT_FORMAT_JPEG 0x03

//typedef enum {
//CAMERA_OK = 0x00,
//CAMERA_ERROR = 0x01,
//CAMERA_TIMEOUT = 0x02
//} Camera_StatusTypeDef;

class DCMI_Driver {
 private:
  DCMI_Driver() {}
  DCMI_Driver(const DCMI_Driver&);
  DCMI_Driver& operator=(const DCMI_Driver&);

 public:
  static uint32_t lineNum;
  static DCMI_Driver& instance() {
    static DCMI_Driver _instance;
    return _instance;
  }
  ~DCMI_Driver() {}
  void someMethode();
  void BSP_CAMERA_MsInit(void);
  uint8_t BSP_CAMERA_Init(uint32_t Resolution);
  void BSP_CAMERA_ContinuousStart(uint8_t* buff);
  void BSP_CAMERA_SnapshotStart(uint8_t* buff);
  void BSP_CAMERA_Suspend(void);
  void BSP_CAMERA_Resume(void);
  uint8_t BSP_CAMERA_Stop(void);
  /* Camera features functions prototype */
  void BSP_CAMERA_ContrastBrightnessConfig(uint32_t contrast_level,
                                           uint32_t brightness_level);
  void BSP_CAMERA_BlackWhiteConfig(uint32_t Mode);
  void BSP_CAMERA_ColorEffectConfig(uint32_t Effect);
  void CAMERA_factoryReset(void);
  void CAMERA_setOutputFormat(uint8_t format);
  /* Camera interrupts and callbacks functions */
  void BSP_CAMERA_LineEventCallback(void);
  void BSP_CAMERA_VsyncEventCallback(void);
  void BSP_CAMERA_FrameEventCallback(void);
  void BSP_CAMERA_ErrorCallback(void);

  /* To be called in DCMI_IRQHandler function */
  void BSP_CAMERA_IRQHandler(void);
  /* To be called in DMA2_Stream1_IRQHandler function */
  void BSP_CAMERA_DMA_IRQHandler(void);

  /* utilities function */
  uint32_t GetSize(uint32_t resolution);
  uint8_t CAMERA_readRegValue(uint8_t REG_ADDRESS);
  void CAMERA_writeRegValue(bool REG_BANK_SEL, uint8_t REG_ADDRESS,
                            uint8_t VALUE);
};

#endif /* INC_DCMI_DRIVER_H_ */
