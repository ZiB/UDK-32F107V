/*
 * File: lcd.c
 * Date: 24.11.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#include "main.h"

struct register_data
{
	uint8_t address;
	uint16_t value;
};

const struct register_data init_value_ssd1289[] = { { 0x00, 0x0001 }, { 0x03, 0xA8A4 }, { 0x0C, 0x0000 }, { 0x0D, 0x080C }, { 0x0E, 0x2B00 }, { 0x1E, 0x00B0 },
		{ 0x01, 0x2B3F }, { 0x02, 0x0600 }, { 0x10, 0x0000 }, { 0x11, 0x6070 }, { 0x05, 0x0000 }, { 0x06, 0x0000 }, { 0x16, 0xEF1C }, { 0x17, 0x0003 }, { 0x07,
				0x0133 }, { 0x0B, 0x0000 }, { 0x0F, 0x0000 }, { 0x41, 0x0000 }, { 0x42, 0x0000 }, { 0x48, 0x0000 }, { 0x49, 0x013F }, { 0x4A, 0x0000 }, { 0x4B,
				0x0000 }, { 0x44, 0xEF00 }, { 0x45, 0x0000 }, { 0x46, 0x013F }, { 0x30, 0x0707 }, { 0x31, 0x0204 }, { 0x32, 0x0204 }, { 0x33, 0x0502 }, { 0x34,
				0x0507 }, { 0x35, 0x0204 }, { 0x36, 0x0204 }, { 0x37, 0x0502 }, { 0x3A, 0x0302 }, { 0x3B, 0x0302 }, { 0x23, 0x0000 }, { 0x24, 0x0000 }, { 0x25,
				0x8000 }, { 0x4f, 0x0000 }, { 0x4e, 0x0000 } };

static inline void write(uint16_t value)
{
	GPIOE->ODR = value;

	PIN_ON(PIN_LCD_HY32D_WR);
	PIN_OFF(PIN_LCD_HY32D_WR);
}

static inline uint16_t read(void)
{
	return GPIOE->IDR;
}

static void register_write(uint8_t address, uint16_t value)
{
	PIN_ON(PIN_LCD_HY32D_CS);

	// выбор адреса регистра
	PIN_OFF(PIN_LCD_HY32D_RS);
	PIN_OFF(PIN_LCD_HY32D_RD);
	write(address);

	// запись данных в выбранный регистр
	PIN_ON(PIN_LCD_HY32D_RS);
	write(value);

	PIN_OFF(PIN_LCD_HY32D_CS);
}

static uint16_t register_read(uint8_t address)
{
	PIN_ON(PIN_LCD_HY32D_CS);

	// выбор адреса регистра
	PIN_OFF(PIN_LCD_HY32D_RS);
	PIN_OFF(PIN_LCD_HY32D_RD);
	write(address);

	// переводим порт на ввод данных
	GPIOE->ODR = 0xFFFF;
	GPIOE->CRL = 0x88888888;
	GPIOE->CRH = 0x88888888;

	// чтение данных из выбранного регистра
	PIN_ON(PIN_LCD_HY32D_RS);
	PIN_ON(PIN_LCD_HY32D_RD);
	uint16_t value = read();
	PIN_OFF(PIN_LCD_HY32D_RD);

	PIN_OFF(PIN_LCD_HY32D_CS);

	// переводим порт на вывод данных
	GPIOE->CRL = 0x22222222;
	GPIOE->CRH = 0x22222222;

	return value;
}

void lcd_fill_screen(uint16_t color)
{
	register_write(0x4E, 0);
	register_write(0x4F, 0);

	PIN_ON(PIN_LCD_HY32D_CS);

	// выбор адреса регистра
	PIN_OFF(PIN_LCD_HY32D_RS);
	PIN_OFF(PIN_LCD_HY32D_RD);
	write(0x22);

	// запись данных в выбранный регистр
	PIN_ON(PIN_LCD_HY32D_RS);
	write(color);
	for (uint32_t i = 1; i < 320 * 240; i++)
	{
		PIN_ON(PIN_LCD_HY32D_WR);
		PIN_OFF(PIN_LCD_HY32D_WR);
	}

	PIN_OFF(PIN_LCD_HY32D_CS);
}

void lcd_fill_pixel(uint8_t x, uint8_t y, uint16_t color)
{
	register_write(0x4E, x);
	register_write(0x4F, y);

	PIN_ON(PIN_LCD_HY32D_CS);

	// выбор адреса регистра
	PIN_OFF(PIN_LCD_HY32D_RS);
	PIN_OFF(PIN_LCD_HY32D_RD);
	write(0x22);

	// запись данных в выбранный регистр
	PIN_ON(PIN_LCD_HY32D_RS);
	write(color);

	PIN_OFF(PIN_LCD_HY32D_CS);
}

void lcd_init(void)
{
	// проверка модели контроллера
	if (register_read(0x00) == 0x8989)
	{
		// инициализация
		for (uint8_t i = 0; i < ARRAY_LENGHT(init_value_ssd1289); i++)
		{
			register_write(init_value_ssd1289[i].address, init_value_ssd1289[i].value);
		}

		// вкл. подсветку
		PIN_ON(PIN_LCD_HY32D_BL);
	}
}
