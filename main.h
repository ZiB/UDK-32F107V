/*
 * File: main.h
 * Date: 09.11.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#ifndef MAIN_H_
#define MAIN_H_

#define PIN_BUTTON_WAKEUP		A,  0, HIGH, MODE_INPUT_PULL_UP, SPEED_2MHZ
#define PIN_BUTTON_TAMPER		C, 13,  LOW, MODE_INPUT_PULL_UP, SPEED_2MHZ

#define PIN_USB_PWR_EN			B, 15,  LOW, MODE_OUTPUT_PUSH_PULL, SPEED_2MHZ

#define PIN_USER_LED			B, 10, HIGH, MODE_OUTPUT_PUSH_PULL, SPEED_2MHZ

#if defined STM32F107VCT6

#define STM32F10X_CL
#define HSE_VALUE       25000000UL

#include "macros_stm32f10x.h"

#include "stm32f10x.h"

#endif

#include "macros_stm32f10x.h"

#endif /* MAIN_H_ */
