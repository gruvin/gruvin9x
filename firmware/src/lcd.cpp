/*
 * gruvin9x Author Bryan J.Rentoul (Gruvin) <gruvin@gmail.com>
 *
 * gruvin9x is based on code named er9x by
 * Author - Erez Raviv <erezraviv@gmail.com>, which is in turn
 * based on th9x -> http://code.google.com/p/th9x/
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

#include "gruvin9x.h"


uint8_t displayBuf[DISPLAY_W*DISPLAY_H/8];
#define DISPLAY_END (displayBuf+sizeof(displayBuf))
#include "font.lbm"
#define font_5x8_x20_x7f (font+3)

#include "font_dblsize.lbm"
#define font_10x16_x20_x7f (font_dblsize+3)

#define BITMASK(bit) (1<<(bit))
void lcd_clear()
{
  //for(unsigned i=0; i<sizeof(displayBuf); i++) displayBuf[i]=0;
  memset(displayBuf, 0, sizeof(displayBuf));
}


void lcd_img(uint8_t i_x,uint8_t i_y,const prog_uchar * imgdat,uint8_t idx,uint8_t mode)
{
  const prog_uchar  *q = imgdat;
  uint8_t w    = pgm_read_byte(q++);
  uint8_t hb   = (pgm_read_byte(q++)+7)/8;
  uint8_t sze1 = pgm_read_byte(q++);
  q += idx*sze1;
  bool    inv  = (mode & INVERS) ? true : (mode & BLINK ? BLINK_ON_PHASE : false);
  for(uint8_t yb = 0; yb < hb; yb++){
    uint8_t   *p = &displayBuf[ (i_y / 8 + yb) * DISPLAY_W + i_x ];
    for(uint8_t x=0; x < w; x++){
      uint8_t b = pgm_read_byte(q++);
      *p++ = inv ? ~b : b;
    }
  }
}

/// invers: 0 no 1=yes 2=blink
void lcd_putcAtt(uint8_t x,uint8_t y,const char c,uint8_t mode)
{
  uint8_t *p    = &displayBuf[ y / 8 * DISPLAY_W + x ];
  //uint8_t *pmax = &displayBuf[ DISPLAY_H/8 * DISPLAY_W ];

  prog_uchar    *q = &font_5x8_x20_x7f[ + (c-0x20)*5];
  bool         inv = (mode & INVERS) ? true : (mode & BLINK ? BLINK_ON_PHASE : false);
  if(mode&DBLSIZE)
  {
    /* each letter consists of ten top bytes followed by
     * five bottom by ten bottom bytes (20 bytes per 
     * char) */
    q = &font_10x16_x20_x7f[(c-0x20)*10 + ((c-0x20)/16)*160];
    for(char i=5; i>=0; i--){
      /*top byte*/
      uint8_t b1 = i>0 ? pgm_read_byte(q) : 0;
      /*bottom byte*/
      uint8_t b3 = i>0 ? pgm_read_byte(160+q) : 0;
      /*top byte*/
      uint8_t b2 = i>0 ? pgm_read_byte(++q) : 0;
      /*bottom byte*/
      uint8_t b4 = i>0 ? pgm_read_byte(160+q) : 0;
      q++;
      if(inv) {
        b1=~b1;
        b2=~b2;
        b3=~b3;
        b4=~b4;
      }   

      if(&p[DISPLAY_W+1] < DISPLAY_END){
        p[0]=b1;
        p[1]=b2;
        p[DISPLAY_W] = b3; 
        p[DISPLAY_W+1] = b4; 
        p+=2;
      }   
    }   

//    for(char i=5; i>=0; i--){
//      uint8_t b = i ? pgm_read_byte(q++) : 0;
//      if(inv) b=~b;
//      static uint8_t dbl[]={0x00,0x03,0x0c,0x0f, 0x30,0x33,0x3c,0x3f,
//                            0xc0,0xc3,0xcc,0xcf, 0xf0,0xf3,0xfc,0xff};
//      if(&p[DISPLAY_W+1] < DISPLAY_END){
//        p[0] = p[1] = dbl[b&0xf];
//        p[DISPLAY_W]=p[DISPLAY_W+1] = dbl[b>>4];
//        p+=2;
//      }
//    }
  }else{
    for(char i=5; i!=0; i--){
      uint8_t b = pgm_read_byte(q++);
      if(p<DISPLAY_END) *p++ = inv ? ~b : b;
    }
    if(p<DISPLAY_END) *p++ = inv ? ~0 : 0;
  }
}
void lcd_putc(uint8_t x,uint8_t y,const char c)
{
  lcd_putcAtt(x,y,c,false);
}
void lcd_putsnAtt(uint8_t x,uint8_t y,const prog_char * s,uint8_t len,uint8_t mode)
{
  while(len!=0) {
    char c = (mode & BSS_NO_INV) ? *s++ : pgm_read_byte(s++);
    lcd_putcAtt(x,y,c,mode);
    x+=FW;
    len--;
  }
}
void lcd_putsn_P(uint8_t x,uint8_t y,const prog_char * s,uint8_t len)
{
  lcd_putsnAtt( x,y,s,len,false);
}
uint8_t lcd_putsAtt(uint8_t x,uint8_t y,const prog_char * s,uint8_t mode)
{
  //while(char c=pgm_read_byte(s++)) {
  while(1) {
    char c = (mode & BSS_NO_INV) ? *s++ : pgm_read_byte(s++);
    if(!c) break;
    lcd_putcAtt(x,y,c,mode);
    x+=FW;
    if(mode&DBLSIZE) x+=FW;
  }
  return x;
}
void lcd_puts_P(uint8_t x,uint8_t y,const prog_char * s)
{
  lcd_putsAtt( x, y, s, 0);
}
void lcd_outhex4(uint8_t x,uint8_t y,uint16_t val)
{
  x+=FW; // was FWNUM*4;
  for(int i=0; i<4; i++)
  {
    x-=FW; // was FWNUM;
    char c = val & 0xf;
    c = c>9 ? c+'A'-10 : c+'0';
    lcd_putc(x,y,c);
    val>>=4;
  }
}
void lcd_outdez(uint8_t x,uint8_t y,int16_t val)
{
  lcd_outdezAtt(x,y,val,0);
}
void lcd_outdezAtt(uint8_t x,uint8_t y,int16_t val,uint8_t mode)
{
  lcd_outdezNAtt( x,y,val,mode,5);
}
void lcd_outdezNAtt(uint8_t x,uint8_t y,int16_t val,uint8_t mode,uint8_t len)
{
  uint8_t fw=FWNUM; //FW-1;
  if(mode&DBLSIZE) fw+=fw;
  uint8_t prec=PREC(mode);
  bool neg=val<0;
  if(neg) val=-val;
  //x+=fw*len;
  x-=FW;
  for(uint8_t i=0;i<len;i++)
  {
    if( prec && prec==i){
      x-=1;
      lcd_putcAtt(x,y,(val % 10)+'0',mode);
      lcd_plot( x+5, y+6); // period
      prec=0;
    }else{
      lcd_putcAtt(x,y,(val % 10)+'0',mode);
    }
    val /= 10;
    if(!(mode & LEADING0) && !val && !prec) break;
    x-=fw;
  }
  if(neg) lcd_putcAtt(x-fw,y,'-',mode);
  else  if((mode & SIGN)) lcd_putcAtt(x-fw,y,'+',mode);
}

void lcd_plot(uint8_t x,uint8_t y)
{
  //  if(y>=64)  return;
  //  if(x>=128) return;
  //  displayBuf[ y / 8 * DISPLAY_W + x ] ^= BITMASK(y%8);
  uint8_t *p   = &displayBuf[ y / 8 * DISPLAY_W + x ];
  if(p<DISPLAY_END) *p ^= BITMASK(y%8);
}
void lcd_hlineStip(unsigned char x,unsigned char y, signed char w,uint8_t pat)
{
  if(w<0) {x+=w; w=-w;}
  uint8_t *p  = &displayBuf[ y / 8 * DISPLAY_W + x ];
  uint8_t msk = BITMASK(y%8);
  while(w){
    if(pat&1) {
      //lcd_plot(x,y);
      *p ^= msk;
      pat = (pat >> 1) | 0x80;
    }else{
      pat = pat >> 1;
    }
    w--;
    p++;
  }
}

void lcd_hline(uint8_t x,uint8_t y, int8_t w)
{
  lcd_hlineStip(x,y,w,0xff);
}
void lcd_vline(uint8_t x,uint8_t y, int8_t h)
{
  uint8_t *p  = &displayBuf[ y / 8 * DISPLAY_W + x ];
  y = y % 8;
  if (y) {
    assert(p < DISPLAY_END);
    *p ^= ~(BITMASK(y)-1);
    p += DISPLAY_W;
    h -= 8-y;
  }
  while (h>0) {
    assert(p < DISPLAY_END);
    *p ^= 0xff;
    p += DISPLAY_W;
    h -= 8;
  }
  h = (h+8) % 8;
  if (h) {
    p -= DISPLAY_W;
    assert(p < DISPLAY_END);
    *p ^= ~(BITMASK(h)-1);
  }
}

void lcdSendCtl(uint8_t val)
{
  PORTC_LCD_CTRL &= ~(1<<OUT_C_LCD_CS1);
#ifdef LCD_MULTIPLEX
  DDRA = 0xFF; // set LCD_DAT pins to output
#endif
  PORTC_LCD_CTRL &= ~(1<<OUT_C_LCD_A0);
  PORTC_LCD_CTRL &= ~(1<<OUT_C_LCD_RnW);
  PORTA_LCD_DAT = val;
  PORTC_LCD_CTRL |=  (1<<OUT_C_LCD_E);
  PORTC_LCD_CTRL &= ~(1<<OUT_C_LCD_E);
  PORTC_LCD_CTRL |=  (1<<OUT_C_LCD_A0);
#ifdef LCD_MULTIPLEX
  DDRA = 0x00; // set LCD_DAT pins to input
#endif
  PORTC_LCD_CTRL |=  (1<<OUT_C_LCD_CS1);
}

void lcdSendDat(uint8_t val)
{
  PORTC_LCD_CTRL &= ~(1<<OUT_C_LCD_CS1);
#ifdef LCD_MULTIPLEX
  DDRA = 0xFF; // set LCD_DAT pins to output
#endif
  PORTC_LCD_CTRL |=  (1<<OUT_C_LCD_A0);
  PORTC_LCD_CTRL &= ~(1<<OUT_C_LCD_RnW);
  PORTA_LCD_DAT = val;
  PORTC_LCD_CTRL |=  (1<<OUT_C_LCD_E);
  PORTC_LCD_CTRL &= ~(1<<OUT_C_LCD_E);
  PORTC_LCD_CTRL |=  (1<<OUT_C_LCD_A0);
#ifdef LCD_MULTIPLEX
  DDRA = 0x00; // set LCD_DAT pins to input
#endif
  PORTC_LCD_CTRL |=  (1<<OUT_C_LCD_CS1);
}

#define delay_1us() _delay_us(1)
void delay_1_5us(int ms)
{
  for(int i=0; i<ms; i++) delay_1us();
}


void lcd_init()
{
  // /home/thus/txt/datasheets/lcd/KS0713.pdf
  // ~/txt/flieger/ST7565RV17.pdf  from http://www.glyn.de/content.asp?wdid=132&sid=

  PORTC_LCD_CTRL &= ~(1<<OUT_C_LCD_RES);  //LCD_RES
  delay_1us();
  delay_1us();//    f520  call  0xf4ce  delay_1us() ; 0x0xf4ce
  PORTC_LCD_CTRL |= (1<<OUT_C_LCD_RES); //  f524  sbi 0x15, 2 IOADR-PORTC_LCD_CTRL; 21           1
  delay_1_5us(1500);
  lcdSendCtl(0xe2); //Initialize the internal functions
  lcdSendCtl(0xae); //DON = 0: display OFF
  lcdSendCtl(0xa1); //ADC = 1: reverse direction(SEG132->SEG1)
  lcdSendCtl(0xA6); //REV = 0: non-reverse display
  lcdSendCtl(0xA4); //EON = 0: normal display. non-entire
  lcdSendCtl(0xA2); // Select LCD bias=0
  lcdSendCtl(0xC0); //SHL = 0: normal direction (COM1->COM64)
  lcdSendCtl(0x2F); //Control power circuit operation VC=VR=VF=1
  lcdSendCtl(0x25); //Select int resistance ratio R2 R1 R0 =5
  lcdSendCtl(0x81); //Set reference voltage Mode
  lcdSendCtl(0x22); // 24 SV5 SV4 SV3 SV2 SV1 SV0 = 0x18
  lcdSendCtl(0xAF); //DON = 1: display ON
  g_eeGeneral.contrast = 0x22;
}
void lcdSetRefVolt(uint8_t val)
{
  lcdSendCtl(0x81);
  lcdSendCtl(val);
}

void refreshDiplay()
{
  uint8_t *p=displayBuf;
  for(uint8_t y=0; y < 8; y++) {
    lcdSendCtl(0x04);
    lcdSendCtl(0x10); //column addr 0
    lcdSendCtl( y | 0xB0); //page addr y
    for(uint8_t x=0; x<128; x++){
      lcdSendDat(*p);
      p++;
    }
  }
}
