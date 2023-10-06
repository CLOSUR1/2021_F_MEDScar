#ifndef  _SYSLIB_H
#define  _SYSLIB_H

#include "math.h"
#include "string.h"
#include "stdio.h"
#include "string.h"
#include "stm32f4xx.h"

#include "sys.h"
#include "delay.h"


#include "usart.h"
#include "usart2.h"
#include "usart6.h"
#include "uart_parse.h"

#include "hcsr.h"
#include "adc.h"
#include "led.h"
#include "moto2.h"
#include "encoder.h"
#include "wifi.h"
#include "sevo.h"

#include "timer.h"
#include "func.h"
#include "pid.h"
#include "mission.h"

#define SYSCLK 100

#define MOTO2_ENCODER_DIR 1
#define MOTO4_ENCODER_DIR -1

#define MOTO2_PWM_DIR 1
#define MOTO4_PWM_DIR 0


#endif
