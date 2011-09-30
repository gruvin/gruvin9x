/*
 * Author - Philip Moss
 * Adapted from jeti.h code by Karl Szmutny <shadow@privy.de>
 * 
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

#ifndef frsky_h
#define frsky_h


#include "menus.h"

// .20 seconds
#define FRSKY_TIMEOUT10ms 20

extern uint8_t frskyRxBuffer[19];   // Receive buffer. 9 bytes (full packet), worst case 18 bytes with byte-stuffing (+1)
extern uint8_t frskyTxBuffer[19]; // Ditto for transmit buffer
extern uint8_t FrskyRxBufferReady;  // 1 = received frsky packet (in frskyRxBuffer) is ready for parsing
extern uint8_t frskyTxBufferCount;   // Number of remaining bytes to transmit. Check if zero before loading a new packet.

// Global Fr-Sky telemetry data variables
extern uint8_t frskyA1;
extern uint8_t frskyA2;
extern uint8_t frskyRSSI; // RSSI (virtual 10 slot) running average
struct FrskyAlarm {
  uint8_t level;    // The alarm's 'urgency' level. 0=disabled, 1=yellow, 2=orange, 3=red
  uint8_t greater;  // 1 = 'if greater than'. 0 = 'if less than'
  uint8_t value;    // The threshold above or below which the alarm will sound
};
extern struct FrskyAlarm frskyAlarms[4];
extern uint8_t frskyStreaming; // >0 (true) == data is streaming in. 0 = nodata detected for some time


void processFrskyPacket(uint8_t *packet);
void frskyWriteAlarm(uint8_t slot);
void frskyAlarmsRefresh(void);

void FRSKY_Init(void);
void FRSKY_DisableTXD (void);
void FRSKY_EnableTXD (void);
void FRSKY_DisableRXD (void);
void FRSKY_EnableRXD (void);

// Menus
void menuProcFrsky(uint8_t event);
void menuProcFrskySettings(uint8_t event);
void menuProcFrskyAlarms(uint8_t event);

extern MenuFuncP_PROGMEM APM menuTabFrsky[3];



#endif

