#ifndef DISPLAY_H_
#define DISPLAY_H_

//#include "gpio.h"
#include "font.h"
#include "color.h"
// TODO remove
#include "usb_configuration.h"

#define DISPLAY_WIDTH		320
#define DISPLAY_HEIGHT		240

void display_SetFont(font_t f);
void display_SetForeground(color_t c);
color_t display_GetForeground(void);
void display_SetBackground(color_t c);
color_t display_GetBackground(void);
void display_Clear();
void display_Pixel(uint16_t x, uint16_t y, uint16_t color);
void display_HorizontalLine(uint16_t x, uint16_t y, uint16_t length);
void display_VerticalLine(uint16_t x, uint16_t y, uint16_t length);
void display_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void display_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void display_RectangleFull(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void display_Char(uint16_t x, uint16_t y, uint8_t c);
void display_String(uint16_t x, uint16_t y, char *s);

#endif