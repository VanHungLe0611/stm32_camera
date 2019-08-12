#include "camera_irq_handler.h"


void BSP_CAMERA_LineEventCallback(void) {
	DCMI_ClearFlag(DCMI_IT_LINE);
	lineNum++;
	SEGGER_RTT_printf(0, "line %d event \n", lineNum);

}
void BSP_CAMERA_VsyncEventCallback(void) {
	DCMI_ClearFlag(DCMI_IT_VSYNC);
	SEGGER_RTT_printf(0, "Vsync event\n");
	SEGGER_RTT_printf(0, "current num of line: %d\n", lineNum);
	lineNum = 0;
	//TODO: send image over UART for preview in pc
}
void BSP_CAMERA_FrameEventCallback(void) {
	DCMI_ClearFlag(DCMI_IT_FRAME);
	SEGGER_RTT_printf(0, "Frame event\n");
}
void BSP_CAMERA_ErrorCallback(void) {
	SEGGER_RTT_printf(0, "Error event\n");
}

/**
 * @brief  Enables or disables the DCMI interface interrupts.
 * @param  DCMI_IT: specifies the DCMI interrupt sources to be enabled or disabled.
 *          This parameter can be any combination of the following values:
 *            @arg DCMI_IT_FRAME: Frame capture complete interrupt mask
 *            @arg DCMI_IT_OVF: Overflow interrupt mask
 *            @arg DCMI_IT_ERR: Synchronization error interrupt mask
 *            @arg DCMI_IT_VSYNC: VSYNC interrupt mask
 *            @arg DCMI_IT_LINE: Line interrupt mask
 * @param  NewState: new state of the specified DCMI interrupts.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState) {
	/* Check the parameters */
	assert_param(IS_DCMI_CONFIG_IT(DCMI_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {
		/* Enable the Interrupt sources */
		DCMI->IER |= DCMI_IT;
	} else {
		/* Disable the Interrupt sources */
		DCMI->IER &= (uint16_t) (~DCMI_IT);
	}
}

/**
 * @brief  Checks whether the  DCMI interface flag is set or not.
 * @param  DCMI_FLAG: specifies the flag to check.
 *          This parameter can be one of the following values:
 *            @arg DCMI_FLAG_FRAMERI: Frame capture complete Raw flag mask
 *            @arg DCMI_FLAG_OVFRI: Overflow Raw flag mask
 *            @arg DCMI_FLAG_ERRRI: Synchronization error Raw flag mask
 *            @arg DCMI_FLAG_VSYNCRI: VSYNC Raw flag mask
 *            @arg DCMI_FLAG_LINERI: Line Raw flag mask
 *            @arg DCMI_FLAG_FRAMEMI: Frame capture complete Masked flag mask
 *            @arg DCMI_FLAG_OVFMI: Overflow Masked flag mask
 *            @arg DCMI_FLAG_ERRMI: Synchronization error Masked flag mask
 *            @arg DCMI_FLAG_VSYNCMI: VSYNC Masked flag mask
 *            @arg DCMI_FLAG_LINEMI: Line Masked flag mask
 *            @arg DCMI_FLAG_HSYNC: HSYNC flag mask
 *            @arg DCMI_FLAG_VSYNC: VSYNC flag mask
 *            @arg DCMI_FLAG_FNE: Fifo not empty flag mask
 * @retval The new state of DCMI_FLAG (SET or RESET).
 */
FlagStatus DCMI_GetFlagStatus(uint16_t DCMI_FLAG) {
	FlagStatus bitstatus = RESET;
	uint32_t dcmireg, tempreg = 0;

	/* Check the parameters */
	assert_param(IS_DCMI_GET_FLAG(DCMI_FLAG));

	/* Get the DCMI register index */
	dcmireg = (((uint16_t) DCMI_FLAG) >> 12);

	if (dcmireg == 0x00) /* The FLAG is in RISR register */
	{
		tempreg = DCMI->RISR;
	} else if (dcmireg == 0x02) /* The FLAG is in SR register */
	{
		tempreg = DCMI->SR;
	} else /* The FLAG is in MISR register */
	{
		tempreg = DCMI->MISR;
	}

	if ((tempreg & DCMI_FLAG) != (uint16_t) RESET) {
		bitstatus = SET;
	} else {
		bitstatus = RESET;
	}
	/* Return the DCMI_FLAG status */
	return bitstatus;
}

/**
 * @brief  Clears the DCMI's pending flags.
 * @param  DCMI_FLAG: specifies the flag to clear.
 *          This parameter can be any combination of the following values:
 *            @arg DCMI_FLAG_FRAMERI: Frame capture complete Raw flag mask
 *            @arg DCMI_FLAG_OVFRI: Overflow Raw flag mask
 *            @arg DCMI_FLAG_ERRRI: Synchronization error Raw flag mask
 *            @arg DCMI_FLAG_VSYNCRI: VSYNC Raw flag mask
 *            @arg DCMI_FLAG_LINERI: Line Raw flag mask
 * @retval None
 */
void DCMI_ClearFlag(uint16_t DCMI_FLAG) {
	/* Check the parameters */
	assert_param(IS_DCMI_CLEAR_FLAG(DCMI_FLAG));

	/* Clear the flag by writing in the ICR register 1 in the corresponding
	 Flag position*/

	DCMI->ICR = DCMI_FLAG;
}

/**
 * @brief  Checks whether the DCMI interrupt has occurred or not.
 * @param  DCMI_IT: specifies the DCMI interrupt source to check.
 *          This parameter can be one of the following values:
 *            @arg DCMI_IT_FRAME: Frame capture complete interrupt mask
 *            @arg DCMI_IT_OVF: Overflow interrupt mask
 *            @arg DCMI_IT_ERR: Synchronization error interrupt mask
 *            @arg DCMI_IT_VSYNC: VSYNC interrupt mask
 *            @arg DCMI_IT_LINE: Line interrupt mask
 * @retval The new state of DCMI_IT (SET or RESET).
 */

ITStatus DCMI_GetITStatus(uint16_t DCMI_IT) {
	ITStatus bitstatus = RESET;
	uint32_t itstatus = 0;

	/* Check the parameters */
	assert_param(IS_DCMI_GET_IT(DCMI_IT));

	itstatus = DCMI->MISR & DCMI_IT; /* Only masked interrupts are checked */

	if ((itstatus != (uint16_t) RESET)) {
		bitstatus = SET;
	} else {
		bitstatus = RESET;
	}
	return bitstatus;
}

