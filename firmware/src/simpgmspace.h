/*
 * Author - Erez Raviv <erezraviv@gmail.com>
 *
 * Based on th9x -> http://code.google.com/p/th9x/
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

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

typedef unsigned char prog_uchar;
typedef const char prog_char;
typedef const uint16_t prog_uint16_t;
typedef const uint8_t prog_uint8_t;
typedef const int16_t prog_int16_t;
typedef const int8_t prog_int8_t;



#define PROGMEM
#define pgm_read_byte(address_short) (*(uint8_t*)(address_short))
#define pgm_read_word(address_short) (*(uint16_t*)(address_short))
#define pgm_read_adr(address_short) (*(int*)(address_short))
#define pgm_read_stringP(adr) ((adr))
#define PSTR(adr) adr
#define _delay_us(a)
#define cli()
#define sei()
#define strcpy_P strcpy
#define memcpy_P memcpy

#define PORTA dummyport
#define PORTB portb
#define PORTC dummyport
#define PORTG dummyport
#define DDRA   dummyport
#define DDRB   dummyport
#define DDRC   dummyport
#define PINB  ~pinb
#define PIND  ~pind
#define PINE  ~pine
#define PING  ~ping
#define EEMEM

extern unsigned char pinb,pind,pine,ping,portb;
extern unsigned char dummyport;
//extern uint16_t anaIn(uint8_t chan);
//void eeprom_write_block (const void *pointer_ram,
//                    void *pointer_eeprom,
//                         size_t size);
void eeprom_read_block (void *pointer_ram,
                   const void *pointer_eeprom,
                        size_t size);
#define offsetof(st, m) ((size_t) ( (char *)&((st *)(0))->m - (char *)0 ))
#define wdt_reset()
