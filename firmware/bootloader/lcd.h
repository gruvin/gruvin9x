/*
 * Authors (alphabetical order)
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 *
 * gruvin9x is based on code named er9x by
 * Author - Erez Raviv <erezraviv@gmail.com>, which is in turn
 * was based on the original (and ongoing) project by Thomas Husterer,
 * th9x -- http://code.google.com/p/th9x/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef lcd_h
#define lcd_h

#define PORTA_LCD_DAT  PORTA
#define PORTC_LCD_CTRL PORTC
#define OUT_C_LCD_E     5
#define OUT_C_LCD_RnW   4
#define OUT_C_LCD_A0    3
#define OUT_C_LCD_RES   2
#define OUT_C_LCD_CS1   1

#define DISPLAY_W 128
#define DISPLAY_H  64
#define FW          6
#define FWNUM       5
#define FWDP        2 /* DP=decimal point */
#define FH          8

/* lcd common flags */
#define BLINK         0x01

/* lcd text flags */
#define INVERS        0x02
#define DBLSIZE       0x04

/* lcd putc flags */
#define CONDENSED     0x08

/* lcd puts flags */
#define BSS           0x10
#define ZCHAR         0x20

/* lcd outdez flags */
#define UNSIGN        0x08
#define LEADING0      0x10
#define SPARE1        0x20
#define SPARE2        0x30
#define SPARE3        0x40
#define PREC1         0x50
#define PREC2         0x60
#define PREC3         0x70
#define MODE(flags)   (-4 + ((int8_t)(flags & 0x70) >> 4))
#define LEFT          0x80 /* align left */

/* line, rect, square flags */
#define BLACK         0x02
#define WHITE         0x04

/* time & telemetry flags */
#define NO_UNIT       UNSIGN

extern uint8_t displayBuf[DISPLAY_W*DISPLAY_H/8];
extern uint8_t lcd_lastPos;

extern void lcd_putc(unsigned char x,unsigned char y,const char c);
extern void lcd_putcAtt(unsigned char x,unsigned char y,const char c,uint8_t mode);

extern void lcd_putsAtt(unsigned char x,unsigned char y,const pm_char * s,uint8_t mode);
extern void lcd_putsnAtt(unsigned char x,unsigned char y,const pm_char * s,unsigned char len,uint8_t mode);
extern void lcd_puts_P(unsigned char x,unsigned char y,const pm_char * s);
extern void lcd_putsn_P(unsigned char x,unsigned char y,const pm_char * s,unsigned char len);

extern void lcd_outhex4(unsigned char x,unsigned char y,uint16_t val);
extern void lcd_outhex5(uint8_t x,uint8_t y,uint32_t val);

extern void lcd_init();
extern void lcd_clear();
extern void lcdSetRefVolt(uint8_t val);
extern void refreshDisplay();

#endif
/*eof*/
