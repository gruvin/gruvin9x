#ifndef BOOTLOADER_H
#define BOOTLOADER_H


#define __AVR_ENHANCED__    1 //used by pgmspace.h to activate advanced fnc's

#include <stddef.h>
#include <avr/io.h>
#define assert(x)
//disable whole pgmspace functionality for all avr-gcc because
//avr-gcc > 4.2.1 does not work anyway
//http://www.mail-archive.com/gcc-bugs@gcc.gnu.org/msg239240.html
//http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34734
//
//Workarounds:
//
//PSTR is fixed below
//all prog_xx definitions must use APM explicitely

//#define __ATTR_PROGMEM__
#include <avr/pgmspace.h>
#ifdef __cplusplus
#define APM __attribute__(( section(".progmem.data") ))
#undef PSTR
#define PSTR(s) (__extension__({static prog_char APM __c[] = (s);&__c[0];}))
#endif

#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#define pgm_read_adr(address_short) pgm_read_word(address_short)
#include <avr/wdt.h>

#include <inttypes.h>
#include <string.h>

#define BITMASK(bit) (1<<(bit))

#endif



