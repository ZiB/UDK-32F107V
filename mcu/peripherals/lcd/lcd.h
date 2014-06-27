/*
 * File: lcd.h
 * Date: 24.11.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#ifndef LCD_H_
#define LCD_H_

enum lcd_colors
{
	LCD_COLOR_BLACK = 0x0000,
	LCD_COLOR_WHITE = 0xFFFF,
	LCD_COLOR_GRAY = 0xE79C,
	LCD_COLOR_GREEN = 0x07E0,
	LCD_COLOR_BLUE = 0x001F,
	LCD_COLOR_RED = 0xF800,
	LCD_COLOR_SKY = 0x5D1C,
	LCD_COLOR_YELLOW = 0xFFE0,
	LCD_COLOR_MAGENTA = 0xF81F,
	LCD_COLOR_CYAN = 0x07FF,
	LCD_COLOR_ORANGE = 0xFCA0,
	LCD_COLOR_PINK = 0xF97F,
	LCD_COLOR_BROWN = 0x8200,
	LCD_COLOR_VIOLET = 0x9199,
	LCD_COLOR_SILVER = 0xA510,
	LCD_COLOR_GOLD = 0xA508,
	LCD_COLOR_BEGH = 0xF77B,
	LCD_COLOR_NAVY = 0x000F,
	LCD_COLOR_DARK_GREEN = 0x03E0,
	LCD_COLOR_DARK_CYAN = 0x03EF,
	LCD_COLOR_MAROON = 0x7800,
	LCD_COLOR_PURPLE = 0x780F,
	LCD_COLOR_OLIVE = 0x7BE0,
	LCD_COLOR_LIGHT_GREY = 0xC618,
	LCD_COLOR_DARK_GREY = 0x7BEF
};

void lcd_init(void);
void lcd_fill_pixel(uint8_t x, uint8_t y, uint16_t color);
void lcd_fill_screen(uint16_t color);

#endif /* LCD_H_ */
