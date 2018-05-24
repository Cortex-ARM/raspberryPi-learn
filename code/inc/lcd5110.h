#ifndef LCD5110_H_
#define LCD5110_H_


#define RASPBERRY

#ifdef  RASPBERRY

#include <wiringPi.h>
#define LCD_CE_ON	digitalWrite(10,HIGH)
#define LCD_CE_OFF	digitalWrite(10,LOW)   
#define LCD_RST_ON	digitalWrite(2,HIGH)    
#define LCD_RST_OFF	digitalWrite(2,LOW)  
#define LCD_DC_ON	digitalWrite(3,HIGH)   
#define LCD_DC_OFF 	digitalWrite(3,LOW)
#define SDIN_ON		digitalWrite(12,HIGH)
#define SDIN_OFF	digitalWrite(12,LOW)
#define SCLK_ON		digitalWrite(14,HIGH)
#define SCLK_OFF	digitalWrite(14,LOW)
#define LCD_BL_ON 	digitalWrite(23,LOW)
#define LCD_BL_OFF 	digitalWrite(23,HIGH)

#else

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libfahw.h"
#define LCD_CE_ON	setGPIOValue(GPIO_PIN(11),1)
#define LCD_CE_OFF	setGPIOValue(GPIO_PIN(11),0)
#define LCD_RST_ON	setGPIOValue(GPIO_PIN(12),1)
#define LCD_RST_OFF	setGPIOValue(GPIO_PIN(12),0)
#define LCD_DC_ON	setGPIOValue(GPIO_PIN(10),1)
#define LCD_DC_OFF	setGPIOValue(GPIO_PIN(10),0)
#define SDIN_ON		setGPIOValue(GPIO_PIN(8),1)
#define SDIN_OFF	setGPIOValue(GPIO_PIN(8),0)
#define SCLK_ON		setGPIOValue(GPIO_PIN(7),1)
#define SCLK_OFF	setGPIOValue(GPIO_PIN(7),0)
#define LCD_BL_ON 	//digitalWrite(23,LOW)
#define LCD_BL_OFF //digitalWrite(23,HIGH)

#endif


extern void LCD_clear(void);
extern void LCD_init(void);
extern void LCD_write_char(unsigned char c);
extern void LCD_write_english_string(unsigned char X,unsigned char Y,char *s);
extern void LCD_write_chinese_string(unsigned char X, unsigned char Y, 
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row);
extern void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y);
extern void int_clk(void);


#endif 
