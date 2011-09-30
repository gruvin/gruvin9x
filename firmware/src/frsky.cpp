/*
 *
 * gruvin9x Author Bryan J.Rentoul (Gruvin) <gruvin@gmail.com>
 *
 * frsky.cpp original author - Philip Moss Adapted from jeti.cpp code by Karl
 * Szmutny <shadow@privy.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */

#include "gruvin9x.h"
#include "frsky.h"

uint8_t frskyRxBuffer[19];   // Receive buffer. 9 bytes (full packet), worst case 18 bytes with byte-stuffing (+1)
uint8_t frskyTxBuffer[19]; // Ditto for transmit buffer
uint8_t frskyTxBufferCount = 0;
uint8_t FrskyRxBufferReady = 0;
uint8_t frskyStreaming = 0;

uint8_t frskyA1;
uint8_t frskyA2;
uint8_t frskyRSSI; // RSSI (virtual 10 slot) running average

struct FrskyAlarm frskyAlarms[4];

/*
   Called from somewhere in the main loop or a low prioirty interrupt
   routine perhaps. This funtcion processes Fr-Sky telemetry data packets
   assembled byt he USART0_RX_vect) ISR function (below) and stores
   extracted data in global variables for use by other parts of the program.

   Packets can be any of the following:

    - A1/A2/RSSI telemtry data
    - Alarm level/mode/threshold settings for Ch1A, Ch1B, Ch2A, Ch2B
    - User Data packets

   User Data packets are not yet implementedi (they are simply ignored), 
   but will likely one day contain the likes of GPS long/lat/alt/speed, 
   AoA, airspeed, etc.
*/
void processFrskyPacket(uint8_t *packet)
{
  static uint8_t lastRSSI = 0; // for running average calculation

  // What type of packet?
  switch (packet[0])
  {
    case 0xf9:
    case 0xfa:
    case 0xfb:
    case 0xfc:
      frskyAlarms[(packet[0]-0xf9)].value = packet[1];
      frskyAlarms[(packet[0]-0xf9)].greater = packet[2] & 0x01;
      frskyAlarms[(packet[0]-0xf9)].level = packet[3] & 0x03;
      break;
    case 0xfe: // A1/A2/RSSI values
      frskyA1 = packet[1];
      frskyA2 = packet[2];

      if (lastRSSI == 0)
        frskyRSSI = packet[3];
      else
        frskyRSSI = ((uint16_t)packet[3] + ((uint16_t)lastRSSI * 15)) >> 4; // >>4 = divide by 16 the fast way
      lastRSSI = frskyRSSI;
      break;

    case 0xfd: // User Data packet -- not yet implemented
      break;

  }

  FrskyRxBufferReady = 0;
  frskyStreaming = FRSKY_TIMEOUT10ms; // reset counter only if valid frsky packets are being detected
}

// Receive buffer state machine state defs
#define frskyDataIdle    0
#define frskyDataStart   1
#define frskyDataInFrame 2
#define frskyDataXOR     3
/*
   Receive serial (RS-232) characters, detecting and storing each Fr-Sky 
   0x7e-framed packet as it arrives.  When a complete packet has been 
   received, process its data into storage variables.  NOTE: This is an 
   interrupt routine and should not get too lengthy. I originally had
   the buffer being checked in the perMain function (because per10ms
   isn't quite often enough for data streaming at 9600baud) but alas
   that scheme lost packets also. So each packet is parsed as it arrives,
   directly at the ISR function (through a call to frskyProcessPacket).
   
   If this proves a problem in the future, then I'll just have to implement
   a second buffer to receive data while one buffer is being processed (slowly).
*/
ISR(USART0_RX_vect)
{
  uint8_t stat;
  uint8_t data;
  
  static uint8_t numPktBytes = 0;
  static uint8_t dataState = frskyDataIdle;

  stat = UCSR0A; // USART control and Status Register 0 A

    /*
              bit      7      6      5      4      3      2      1      0
                      RxC0  TxC0  UDRE0    FE0   DOR0   UPE0   U2X0  MPCM0
             
              RxC0:   Receive complete
              TXC0:   Transmit Complete
              UDRE0:  USART Data Register Empty
              FE0:    Frame Error
              DOR0:   Data OverRun
              UPE0:   USART Parity Error
              U2X0:   Double Tx Speed
              PCM0:   MultiProcessor Comms Mode
    */
    // rh = UCSR0B; //USART control and Status Register 0 B

    /*
              bit      7      6      5      4      3      2      1      0
                   RXCIE0 TxCIE0 UDRIE0  RXEN0  TXEN0 UCSZ02  RXB80  TXB80
             
              RxCIE0:   Receive Complete int enable
              TXCIE0:   Transmit Complete int enable
              UDRIE0:   USART Data Register Empty int enable
              RXEN0:    Rx Enable
              TXEN0:    Tx Enable
              UCSZ02:   Character Size bit 2
              RXB80:    Rx data bit 8
              TXB80:    Tx data bit 8
    */

  data = UDR0; // USART data register 0

  if (stat & ((1 << FE0) | (1 << DOR0) | (1 << UPE0)))
  { // discard buffer and start fresh on any comms error
    FrskyRxBufferReady = 0;
    numPktBytes = 0;
  } 
  else
  {
    if (FrskyRxBufferReady == 0) // can't get more data if the buffer hasn't been cleared
    {
      switch (dataState) 
      {
        case frskyDataStart:
          if (data == 0x7e) break; // Remain in userDataStart if possible 0x7e,0x7e doublet found. 

          if (numPktBytes < 19)
            frskyRxBuffer[numPktBytes++] = data;
          dataState = frskyDataInFrame;
          break;

        case frskyDataInFrame:
          if (data == 0x7d) 
          { 
              dataState = frskyDataXOR; // XOR next byte
              break; 
          }
          if (data == 0x7e) // end of frame detected
          {
            processFrskyPacket(frskyRxBuffer); // FrskyRxBufferReady = 1;
            dataState = frskyDataIdle;
            break;
          }
          frskyRxBuffer[numPktBytes++] = data;
          break;

        case frskyDataXOR:
          if (numPktBytes < 19)
            frskyRxBuffer[numPktBytes++] = data ^ 0x20;
          dataState = frskyDataInFrame;
          break;

        case frskyDataIdle:
          if (data == 0x7e)
          {
            numPktBytes = 0;
            dataState = frskyDataStart;
          }
          break;

      } // switch
    } // if (FrskyRxBufferReady == 0)
  }
}

/*
   USART0 (transmit) Data Register Emtpy ISR
   Usef to transmit FrSky data packets, which are buffered in frskyTXBuffer. 
*/
uint8_t frskyTxISRIndex = 0;
ISR(USART0_UDRE_vect)
{
  if (frskyTxBufferCount > 0) 
  {
    UDR0 = frskyTxBuffer[frskyTxISRIndex++];
    frskyTxBufferCount--;
  } else
    UCSR0B &= ~(1 << UDRIE0); // disable UDRE0 interrupt
}

/******************************************/


void frskyTransmitBuffer()
{
  frskyTxISRIndex = 0;
  UCSR0B |= (1 << UDRIE0); // enable  UDRE0 interrupt
}

//   Write out an alarm settings programming packet for given alarm slot (0-4)
void frskyWriteAlarm(uint8_t slot)
{
  uint8_t i = 0;
  uint8_t buf;

  if (frskyTxBufferCount) return; // we only have one buffer. If it's in use, then we can't send. Sorry.

  frskyTxBuffer[i++] = 0x7e; // Start of packet
  frskyTxBuffer[i++] = (0xf9+slot); // Analog 1 alarm 1
  buf = frskyAlarms[slot].value;

  // byte stuff the only byte than might need it
  if (buf == 0x7e) {
    frskyTxBuffer[i++] = 0x7d;
    frskyTxBuffer[i++] = 0x5e;
  } else if (buf == 0x7d) {
    frskyTxBuffer[i++] = 0x7d;
    frskyTxBuffer[i++] = 0x5d;
  } else
    frskyTxBuffer[i++] = buf;

  frskyTxBuffer[i++] = frskyAlarms[slot].greater;
  frskyTxBuffer[i++] = frskyAlarms[slot].level;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x7e; // End of packet

  frskyTxBufferCount = i;
  frskyTransmitBuffer(); 
}

// Send packet requesting all alarm settings be sent back to us
void frskyAlarmsRefresh()
{
  uint8_t i = 0;

  if (frskyTxBufferCount) return; // we only have one buffer. If it's in use, then we can't send. Sorry.

  frskyTxBuffer[i++] = 0x7e; // Start of packet
  frskyTxBuffer[i++] = 0xf8;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x00;
  frskyTxBuffer[i++] = 0x7e; // End of packet

  frskyTxBufferCount = i;
  frskyTransmitBuffer();
}

void FRSKY_Init(void)
{
  // clear alarm variables
  memset(frskyAlarms, 0, sizeof(frskyAlarms));

  DDRE &= ~(1 << DDE0);    // set RXD0 pin as input
  PORTE &= ~(1 << PORTE0); // disable pullup on RXD0 pin

#undef BAUD
#define BAUD 9600
#include <util/setbaud.h>

  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0A &= ~(1 << U2X0); // disable double speed operation.

  // set 8 N1
  UCSR0B = 0 | (0 << RXCIE0) | (0 << TXCIE0) | (0 << UDRIE0) | (0 << RXEN0) | (0 << TXEN0) | (0 << UCSZ02);
  UCSR0C = 0 | (1 << UCSZ01) | (1 << UCSZ00);

  
  while (UCSR0A & (1 << RXC0)) UDR0; // flush receive buffer

  // These should be running right from power up on a FrSky enabled '9X.
  FRSKY_EnableTXD(); // enable FrSky-Telemetry reception
  FRSKY_EnableRXD(); // enable FrSky-Telemetry reception
}


void FRSKY_DisableTXD(void)
{
  UCSR0B &= ~((1 << TXEN0) | (1 << UDRIE0)); // disable TX pin and interrupt
}


void FRSKY_EnableTXD(void)
{
  frskyTxBufferCount = 0;
  UCSR0B |= (1 << TXEN0) | (1 << UDRIE0); // enable TX and TX interrupt
}


void FRSKY_DisableRXD(void)
{
  UCSR0B &= ~(1 << RXEN0);  // disable RX
  UCSR0B &= ~(1 << RXCIE0); // disable Interrupt
}


void FRSKY_EnableRXD(void)
{

  UCSR0B |= (1 << RXEN0);  // enable RX
  UCSR0B |= (1 << RXCIE0); // enable Interrupt
}

/*
   FRSKY MENUS BEGIN HERE
   FRSKY MENUS BEGIN HERE
   FRSKY MENUS BEGIN HERE
*/

/*
uint8_t hex2dec(uint16_t number, uint8_t multiplier)
{
	uint16_t value = 0;
	
	switch (multiplier)
	{
		case 1:
			value = number%100;
			value = value%10;
			break;
			
		case 10:
			value = number%100;
			value = value /10;
			break;
			
		case 100:
			value = number/100;
			break;
			
		default:
			
			break;
	}
	
	value += 48; // convert to ASCII digit
	return value;
	
}
*/
MenuFuncP_PROGMEM APM menuTabFrsky[] = {
  menuProcFrsky,
  menuProcFrskySettings,
  menuProcFrskyAlarms
};

// FRSKY menu
void menuProcFrsky(uint8_t event)
{
  static uint8_t blinkCount = 0; // let's blink the data on and off if there's no data stream
  static MState2 mstate2;
  TITLE("FRSKY");
  MSTATE_CHECK_V(1,menuTabFrsky,1); // curr,menuTab,numRows(including the page counter [1/2] etc)
  // int8_t  sub    = mstate2.m_posVert; // alias sub to m_posvert. Clever Mr. TH :-D

  if (!frskyStreaming)
  {
    lcd_putsAtt(32, 0, PSTR("NO"), DBLSIZE);
    lcd_putsAtt(62, 0, PSTR("DATA"), DBLSIZE);

  }


  uint8_t y = 2*FH;

  // Data labels
  lcd_puts_P(2*FW, y, PSTR("A1:"));
  lcd_puts_P(11*FW, y, PSTR("A2:"));

  y+=FH; lcd_puts_P(2*FW, y, PSTR("Rx RSSI:   dB"));

  // Display RX Batt Volts only if a valid channel (A1/A2) has been selected
  if (g_eeFrsky.rxVoltsChannel >0)
  {
    y+=FH; lcd_puts_P(2*FW, y, PSTR("Rx Batt:"));
    // Rx batt voltage bar frame

    // Minimum voltage
    lcd_vline(3, 58, 6);  // marker

    y = 6*FH;
    uint8_t t = 1+NUM_OFSP1(g_eeFrsky.rxVoltsBarMin);
    lcd_outdezAtt(t, y, g_eeFrsky.rxVoltsBarMin, 0|PREC1);
    lcd_putc(t, y, 'v');

    uint8_t middleVolts = g_eeFrsky.rxVoltsBarMin+(g_eeFrsky.rxVoltsBarMax - g_eeFrsky.rxVoltsBarMin)/2;
    t = 64+((FW+NUM_OFS(middleVolts))>>1);
    lcd_outdezAtt(t, y, middleVolts, 0|PREC1);
    lcd_putc(t, y, 'v');
    lcd_vline(64, 58, 6);  // marker

    lcd_outdezAtt(128-FW, y, g_eeFrsky.rxVoltsBarMax, 0|PREC1);
    lcd_putc(128-FW, y, 'v');
    lcd_vline(125, 58, 6); // marker
  }

  // blinking if no data stream
  if (frskyStreaming || ((blinkCount++ % 128) > 25)) // 50:255 off:on ratio at double speed
  {

    // A1 raw value, zero padded
    lcd_outdezAtt(8*FW, 2*FH, frskyA1, 0);

    // A2 raw value, zero padded
    lcd_outdezAtt(17*FW, 2*FH, frskyA2, 0);

    // RSSI value 
    lcd_outdezAtt(13*FW, 3*FH, frskyRSSI, 0);

    uint8_t voltsVal = 0;
    switch (g_eeFrsky.rxVoltsChannel) {
      case 1:
        voltsVal = frskyA1;
        break;
      case 2:
        voltsVal = frskyA2;
    }

    if (g_eeFrsky.rxVoltsChannel > 0)
    {
      // Rx Batt: volts (255 == g_eefrsky.rxVoltsMax) 
      uint16_t centaVolts = (voltsVal > 0) ? (10 * (uint16_t)g_eeFrsky.rxVoltsMax * (uint32_t)(voltsVal) / 255) + g_eeFrsky.rxVoltsOfs : 0;
      lcd_outdezAtt(13*FW, 4*FH, centaVolts, 0|PREC2);
      lcd_putc(13*FW, 4*FH, 'v');
      
      // draw the actual voltage bar
      uint16_t centaVoltsMin = 10 * g_eeFrsky.rxVoltsBarMin;
      if (centaVolts >= centaVoltsMin)
      {
        uint8_t vbarLen = (centaVolts - (10 * (uint16_t)g_eeFrsky.rxVoltsBarMin))  * 12 
                            / (g_eeFrsky.rxVoltsBarMax - g_eeFrsky.rxVoltsBarMin);
        for (uint8_t i = 59; i < 63; i++) // Bar 4 pixels thick (high)
          lcd_hline(4, i, (vbarLen > 120) ? 120 : vbarLen);
      }
    }
  } // if data streaming / blink choice
    
}

// FRSKY Settings menu
void menuProcFrskySettings(uint8_t event)
{
#define COUNT_ITEMS 5
#define PARAM_OFS   17*FW

  static MState2 mstate2;
  TITLE("FRSKY SETTINGS");
  MSTATE_CHECK_V(2,menuTabFrsky,7); // current page=2, 7 rows of settings including page counter top/right

  int8_t  sub    = mstate2.m_posVert; // 0 = page/pages at top right
  
  EEFrskyData *fs = &g_eeFrsky;
  switch(event)
  {
    case EVT_ENTRY:
      s_editMode = false;
      break;
    case EVT_KEY_FIRST(KEY_MENU):
      if(sub>=0) s_editMode = !s_editMode;
      break;
  }

  uint8_t y = 2*FH;
  uint8_t subN = 1;
  lcd_puts_P(0, y,PSTR("Rx Volts Channel"));
  lcd_putsnAtt(PARAM_OFS, y, PSTR("--""A1""A2")+2*fs->rxVoltsChannel,2,(sub==subN ? INVERS:0));
  if(sub==subN) checkIncDecGen2( event, &fs->rxVoltsChannel, 0, 2, EE_FRSKY); 

  y+=FH; subN++;
  lcd_puts_P(0, y, PSTR("Rx Max Volts"));
  uint8_t t = PARAM_OFS + NUM_OFSP1(fs->rxVoltsMax);
  lcd_outdezAtt(t, y, fs->rxVoltsMax,(sub==subN ? INVERS:0)|PREC1);
  lcd_putcAtt(  t, y, 'v', 0);
  if(sub==subN) checkIncDecGen2( event, &fs->rxVoltsMax, 0, 255, _FL_UNSIGNED8 | EE_FRSKY); 

  y+=FH; subN++;
  lcd_puts_P(0, y, PSTR("Volts Calibrate"));
  t = PARAM_OFS + NUM_OFSP1(fs->rxVoltsOfs);
  lcd_outdezAtt(t, y, fs->rxVoltsOfs,(sub==subN ? INVERS:0)|PREC1);
  lcd_putcAtt(  t, y, 'v', 0);
  if(sub==subN) checkIncDecGen2( event, &fs->rxVoltsOfs, -127, 127, EE_FRSKY); 

  y+=FH; subN++;
  lcd_puts_P(0, y, PSTR("VBar Min Volts"));
  t = PARAM_OFS + NUM_OFSP1(fs->rxVoltsBarMin);
  lcd_outdezAtt(t, y, fs->rxVoltsBarMin,(sub==subN ? INVERS:0)|PREC1);
  lcd_putcAtt(  t, y, 'v', 0);
  if(sub==subN) checkIncDecGen2( event, &fs->rxVoltsBarMin, 0, 255, _FL_UNSIGNED8 | EE_FRSKY); 

  y+=FH; subN++;
  lcd_puts_P(0, y, PSTR("VBar Max Volts"));
  t = PARAM_OFS + NUM_OFSP1(fs->rxVoltsBarMax);
  lcd_outdezAtt(t, y, fs->rxVoltsBarMax,(sub==subN ? INVERS:0)|PREC1);
  lcd_putcAtt(  t, y, 'v', 0);
  if(sub==subN) checkIncDecGen2( event, &fs->rxVoltsBarMax, 0, 255, _FL_UNSIGNED8 | EE_FRSKY); 

  y+=FH; subN++;
  lcd_puts_P(0, y, PSTR("No Data Alarm"));
  lcd_putsnAtt(PARAM_OFS, y, PSTR("No ""Yes")+3*(fs->noDataAlarm&1),3,(sub==subN ? INVERS:0));
  if(sub==subN) checkIncDecGen2( event, &fs->noDataAlarm, 0, 1, EE_FRSKY); 

}

// FRSKY Alarms menu
void menuProcFrskyAlarms(uint8_t event)
{
  static MState2 mstate2;
  TITLE("FRSKY ALARMS");
  MSTATE_TAB = {1,3}; // horizontal column counts for MSTAT_CHECK_VxH (1 is the page/pages field I think.)
  MSTATE_CHECK_VxH(3,menuTabFrsky,5); // current page=3, 5 rows of settings including page counter top/right

  int8_t  sub    = mstate2.m_posVert - 1; // vertical position (1 = page counter, top/right)
  uint8_t subSub = mstate2.m_posHorz;     // horizontal position

  static uint8_t refreshAlarmsFlag = 0; // The functions is repeatedly called. So this makes our refresh request a one-shot
  if (!refreshAlarmsFlag)
  {
    frskyAlarmsRefresh();
    refreshAlarmsFlag = 1;
  }

  switch(event)
  {
    case EVT_ENTRY:
      s_editMode = false;
      break;
    case EVT_KEY_LONG(KEY_MENU):
        frskyAlarmsRefresh();
        killEvents(event);
      break;
    case EVT_KEY_FIRST(KEY_MENU):
      if(sub>=0) s_editMode = !s_editMode;
      if (!s_editMode) frskyWriteAlarm(sub); // update Fr-Sky module when edit mode exited
      break;
    case EVT_KEY_FIRST(KEY_EXIT):
      if(s_editMode)
      {
        frskyWriteAlarm(sub); // update Fr-Sky module when edit mode exited
        s_editMode = false;
        killEvents(event);
      }
      refreshAlarmsFlag = 0;
      break;
  }

  lcd_puts_P(0, 2*FH,PSTR("Slot Level > < Value"));
  for(uint8_t i=0; i<4; i++) // 4 alarm slots
  {
    uint8_t y=(i+3)*FH;
    FrskyAlarm *ad = &frskyAlarms[i];

    for(uint8_t j=0; j<4;j++) // 4 settings each slot
    {
      uint8_t attr = ((sub==i && (subSub+1)==j) ? (s_editMode ? BLINK : INVERS) : 0);
      switch(j)
      {
        case 0:
          lcd_putsnAtt(0,y,PSTR("A2a""A2b""A1a""A1b")+i*3,3, (sub==i) ? INVERS : 0);
          break;
        case 1:
          lcd_putsnAtt(5*FW,y,PSTR("---""Yel""Org""Red")+ad->level*3,3, attr);
          if(attr && (s_editMode || p1valdiff)) // p1valdiff is analog user input via Pot 1 (rear/left)
            checkIncDecGen2( event, &ad->level, 0, 3, _FL_UNSIGNED8); 
          break;
        case 2:
          lcd_putsnAtt(11*FW,y,PSTR("LT<""GT>")+ad->greater*3,3, attr);
          if(attr && s_editMode)
            checkIncDecGen2( event, &ad->greater, 0, 1, _FL_UNSIGNED8);
          break;
        case 3:
          if ((g_eeFrsky.rxVoltsChannel-1) == ((i>>1)^1)) {
            uint16_t centaVolts = (ad->value > 0) ? 
                (10 * (uint16_t)g_eeFrsky.rxVoltsMax * (uint32_t)(ad->value) / 255) + g_eeFrsky.rxVoltsOfs : 0;
            lcd_outdezAtt(19*FW, y, centaVolts, attr|PREC2);
            lcd_putc(     19*FW, y, 'v');
          } else
            lcd_outdezAtt(19*FW,y, ad->value, attr);
          if(attr && (s_editMode || p1valdiff))
            checkIncDecGen2( event, &ad->value, 0, 255, _FL_UNSIGNED8);
          break;
      }
    }
  }
}

