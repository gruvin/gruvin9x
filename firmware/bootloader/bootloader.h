#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stddef.h>
#include <avr/io.h>
#define assert(x)
#include <avr/pgmspace.h>
#include "pgmtypes.h"
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



