#include "camera_irq_handler.h"

void    BSP_CAMERA_LineEventCallback(void){
	SEGGER_RTT_printf(0,"line event\n");
}
void    BSP_CAMERA_VsyncEventCallback(void){
	SEGGER_RTT_printf(0,"Vsync event\n");
}
void    BSP_CAMERA_FrameEventCallback(void){
	SEGGER_RTT_printf(0,"Frame event\n");
}
void    BSP_CAMERA_ErrorCallback(void){
	SEGGER_RTT_printf(0,"Error event\n");
}
