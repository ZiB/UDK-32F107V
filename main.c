/*
 * File: main.c
 * Date: 09.11.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#include "main.h"

inline static void gpio_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPEEN;

	// питание USB порта
	PIN_CONFIGURATION(PIN_USB_PWR_EN);
	PIN_OFF(PIN_USB_PWR_EN);

	// светодиод пользователя
	PIN_CONFIGURATION(PIN_USER_LED);
	PIN_OFF(PIN_USER_LED);

	//
	PIN_CONFIGURATION(PIN_BUTTON_TAMPER);
	PIN_CONFIGURATION(PIN_BUTTON_WAKEUP);

	// ЖКИ модуль
	PIN_CONFIGURATION(PIN_LCD_HY32D_CS);
	PIN_CONFIGURATION(PIN_LCD_HY32D_RD);
	PIN_CONFIGURATION(PIN_LCD_HY32D_RS);
	PIN_CONFIGURATION(PIN_LCD_HY32D_WR);
	PIN_CONFIGURATION(PIN_LCD_HY32D_BL);
}

inline static void rcc_init(void)
{
	// сброс RCC модуля
	RCC->CR |= RCC_CR_HSION;
	RCC->CFGR &= (uint32_t) 0xF0FF0000;
	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON);
	RCC->CR &= ~(RCC_CR_HSEBYP);
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL | RCC_CFGR_OTGFSPRE);
	RCC->CR &= ~(RCC_CR_PLL2ON | RCC_CR_PLL3ON);
	RCC->CIR = 0x00FF0000;
	RCC->CFGR2 = 0x00000000;

	// перенос таблицы прерываний во флеш-память
	SCB->VTOR = FLASH_BASE;
}

void main(void)
{
	gpio_init();

	rcc_init();

	while (1)
	{
		if(PIN_SIGNAL(PIN_BUTTON_TAMPER))
		{
			PIN_ON(PIN_USER_LED);
		}
		else
		{
			PIN_OFF(PIN_USER_LED);
		}
	}
}
