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
}

void main(void)
{
	gpio_init();

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
