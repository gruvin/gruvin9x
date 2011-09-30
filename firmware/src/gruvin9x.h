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
#ifndef gruvin9x_h
#define gruvin9x_h

#define VERS 1
#define SUB_VERS 2

#include <inttypes.h>
#include <string.h>

///opt/cross/avr/include/avr/pgmspace.h
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

//#define eeprom_write_block eeWriteBlockCmp

#include "file.h"
//
//                  elev                        thr
//                   LV                         RV
//                 2 ^                        4 ^
//                   1                          2
//                   |     rudd                 |     aile
//              <----X--3-> LH             <----X--0-> RH
//              6    |    7                1    |    0
//                   |                          |
//                 3 v                        5 v
//


//PORTA  7      6       5       4       3       2       1       0
//       O      O       O       O       O       O       O       O
//       ------------------------ LCD_DAT -----------------------
//
//PORTB  7      6       5       4       3       2       1       0
//       O      i       i       i       i       i       i       O
//       light  KEY_LFT KEY_RGT KEY_UP  KEY_DWN KEY_EXT KEY_MEN  PPM
//
//PORTC  7      6       5       4       3       2       1       0
//       -      -       O       O       O       O       O       -
//       NC     NC    LCD_E   LCD_RNW  LCD_A0  LCD_RES LCD_CS1  NC
//
//PORTD  7      6       5       4       3       2       1       0
//       i      i       i       i       i       i       i       i
//     TRM_D_DWN _UP  TRM_C_DWN _UP   TRM_B_DWN _UP   TRM_A_DWN _UP
//
//PORTE  7      6       5       4       3       2       1       0
//       i      i       i       i       O       i       i       i
//     PPM_IN  ID2    Trainer  Gear   Buzzer   ElevDR  AileDR  THRCT
//
//PORTF  7      6       5       4       3       2       1       0
//       ai     ai      ai      ai      ai      ai      ai      ai
// ANA_ BAT   PITT_TRM HOV_THR HOV_PIT  STCK_LH STCK_RV STCK_LV STCK_RH
//                                      rud    thro   elev   aile
//PORTG  7      6       5       4       3       2       1       0
//       -      -       -       O       i               i       i
//                            SIM_CTL  ID1      NC      RF_POW RuddDR

#define PORTA_LCD_DAT  PORTA
#define OUT_B_LIGHT   7
#define INP_B_KEY_LFT 6
#define INP_B_KEY_RGT 5
#define INP_B_KEY_UP  4
#define INP_B_KEY_DWN 3
#define INP_B_KEY_EXT 2
#define INP_B_KEY_MEN 1
#define OUT_B_PPM 0
#define PORTC_LCD_CTRL PORTC
#define OUT_C_LCD_E     5
#define OUT_C_LCD_RnW   4
#define OUT_C_LCD_A0    3
#define OUT_C_LCD_RES   2
#define OUT_C_LCD_CS1   1

#define INP_D_TRM_LH_UP   7
#define INP_D_TRM_LH_DWN  6
#define INP_D_TRM_RV_DWN  5
#define INP_D_TRM_RV_UP   4
#define INP_D_TRM_LV_DWN  3
#define INP_D_TRM_LV_UP   2
#define INP_D_TRM_RH_DWN  1
#define INP_D_TRM_RH_UP   0

// Legacy support for USART1 hardware mod [DEPRECATED]
#if defined(USART1FREED)
// do not undef the original INP_D_TRM_LV_DWN/UP as we need them later
  #define INP_C_TRM_LV_UP 0
  #define INP_G_TRM_LV_DWN 2
#endif

#define INP_E_PPM_IN  7
#define INP_E_ID2     6
#define INP_E_Trainer 5
#define INP_E_Gear    4
#define OUT_E_BUZZER  3
#define INP_E_ElevDR  2


#define INP_E_AileDR  1
#define INP_E_ThrCt   0

#if (defined(JETI) || defined(FRSKY))
  #undef INP_E_ThrCt
  #undef INP_E_AileDR
  #define INP_C_ThrCt   6
  #define INP_C_AileDR  7
#endif

#ifdef BEEPSPKR
#define BEEP_KEY_TIME 5
#define BEEP_DEFAULT_FREQ 50
#define BEEP_KEY_UP_FREQ 55
#define BEEP_KEY_DOWN_FREQ 45
#endif

#define OUT_G_SIM_CTL  4 //1 : phone-jack=ppm_in
#define INP_G_ID1      3
#define INP_G_RF_POW   1
#define INP_G_RuddDR   0

const uint8_t modn12x3[4][4]= {
  {1, 2, 3, 4},
  {1, 3, 2, 4},
  {4, 2, 3, 1},
  {4, 3, 2, 1} };

//R=1
//E=2
//T=3
//A=4

const uint8_t chout_ar[24][4] = { //First number is 0..23 -> template setup,  Second is relevant channel out
{1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},
{2,1,3,4},{2,1,4,3},{2,3,1,4},{2,3,4,1},{2,4,1,3},{2,4,3,1},
{3,1,2,4},{3,1,4,2},{3,2,1,4},{3,2,4,1},{3,4,1,2},{3,4,2,1},
{4,1,2,3},{4,1,3,2},{4,2,1,3},{4,2,3,1},{4,3,1,2},{4,3,2,1}    };

//convert from mode 1 to mode g_eeGeneral.stickMode
//NOTICE!  =>  1..4 -> 1..4
#define CONVERT_MODE(x)  (((x)<=4) ? modn12x3[g_eeGeneral.stickMode][((x)-1)] : (x))
#define CHANNEL_ORDER(x) (chout_ar[g_eeGeneral.templateSetup][(x)-1])


enum EnumKeys {
  KEY_MENU ,
  KEY_EXIT ,
  KEY_DOWN ,
  KEY_UP  ,
  KEY_RIGHT ,
  KEY_LEFT ,
  TRM_LH_DWN  ,
  TRM_LH_UP   ,
  TRM_LV_DWN  ,
  TRM_LV_UP   ,
  TRM_RV_DWN  ,
  TRM_RV_UP   ,
  TRM_RH_DWN  ,
  TRM_RH_UP   ,
  //SW_NC     ,
  //SW_ON     ,
  SW_ThrCt  ,
  SW_RuddDR ,
  SW_ElevDR ,
  SW_ID0    ,
  SW_ID1    ,
  SW_ID2    ,
  SW_AileDR ,
  SW_Gear   ,
  SW_Trainer
};

#define SWITCHES_STR "THR""RUD""ELE""ID0""ID1""ID2""AIL""GEA""TRN""SW1""SW2""SW3""SW4""SW5""SW6"
#define NUM_CSW  6 //number of custom switches

#define CURV_STR "---x>0x<0|x|f>0f<0|f|c1 c2 c3 c4 c5 c6 c7 c8 c9 c10c11c12c13c14c15c16"
#define CURVE_BASE 7

#define CSWITCH_STR  "----   v>ofs  v<ofs  |v|>ofs|v|<ofsAND    OR     XOR    ""v1==v2 ""v1!=v2 ""v1>v2  ""v1<v2  ""v1>=v2 ""v1<=v2 "
#define CSW_LEN_FUNC 7

#define CS_OFF       0
#define CS_VPOS      1  //v>offset
#define CS_VNEG      2  //v<offset
#define CS_APOS      3  //|v|>offset
#define CS_ANEG      4  //|v|<offset
#define CS_AND       5
#define CS_OR        6
#define CS_XOR       7
#define CS_EQUAL     8
#define CS_NEQUAL    9
#define CS_GREATER   10
#define CS_LESS      11
#define CS_EGREATER  12
#define CS_ELESS     13
#define CS_MAXF      13  //max function

#define CS_VOFS       0
#define CS_VBOOL      1
#define CS_VCOMP      2
#define CS_STATE(x)   ((x)<CS_AND ? CS_VOFS : ((x)<CS_EQUAL ? CS_VBOOL : CS_VCOMP))



//#define SW_BASE      SW_NC
#define SW_BASE      SW_ThrCt
#define SW_BASE_DIAG SW_ThrCt
//#define SWITCHES_STR "  NC  ON THR RUD ELE ID0 ID1 ID2 AILGEARTRNR"
#define MAX_DRSWITCH (1+SW_Trainer-SW_ThrCt+1+NUM_CSW)

#define MIX_P1    5
#define MIX_P2    6
#define MIX_P3    7
#define MIX_MAX   8
#define MIX_FULL  9

#define PPM_BASE   (MIX_FULL)
#define CHOUT_BASE (MIX_FULL+NUM_PPM)

#define DR_HIGH   0
#define DR_MID    1
#define DR_LOW    2
#define DR_EXPO   0
#define DR_WEIGHT 1
#define DR_RIGHT  0
#define DR_LEFT   1
#define DR_DRSW1  99
#define DR_DRSW2  98

#define DSW_THR  1
#define DSW_RUD  2
#define DSW_ELE  3
#define DSW_ID0  4
#define DSW_ID1  5
#define DSW_ID2  6
#define DSW_AIL  7
#define DSW_GEA  8
#define DSW_TRN  9
#define DSW_SW1  10
#define DSW_SW2  11
#define DSW_SW3  12
#define DSW_SW4  13
#define DSW_SW5  14
#define DSW_SW6  15



#define NUM_KEYS TRM_RH_UP+1
#define TRM_BASE TRM_LH_DWN

//#define _MSK_KEY_FIRST (_MSK_KEY_REPT|0x20)
//#define EVT_KEY_GEN_BREAK(key) ((key)|0x20)
#define _MSK_KEY_REPT    0x40
#define _MSK_KEY_DBL     0x10
#define IS_KEY_BREAK(key)  (((key)&0xf0)        ==  0x20)
#define EVT_KEY_BREAK(key) ((key)|                  0x20)
#define EVT_KEY_FIRST(key) ((key)|    _MSK_KEY_REPT|0x20)
#define EVT_KEY_REPT(key)  ((key)|    _MSK_KEY_REPT     )
#define EVT_KEY_LONG(key)  ((key)|0x80)
#define EVT_KEY_DBL(key)   ((key)|_MSK_KEY_DBL)
//#define EVT_KEY_DBL(key)   ((key)|0x10)
#define EVT_ENTRY               (0xff - _MSK_KEY_REPT)
#define EVT_ENTRY_UP            (0xfe - _MSK_KEY_REPT)
#define EVT_KEY_MASK             0x0f


#define TMRMODE_NONE     0
#define TMRMODE_ABS      1
#define TMRMODE_THR      2
#define TMRMODE_THR_REL  3
#define MAX_ALERT_TIME   60

#define PROTO_PPM        0
#define PROTO_SILV_A     1
#define PROTO_SILV_B     2
#define PROTO_SILV_C     3
#define PROTO_TRACER_CTP1009 4
#define PROT_MAX         4
#define PROT_STR "PPM   SILV_ASILV_BSILV_CTRAC09"
#define PROT_STR_LEN     6

typedef void (*MenuFuncP)(uint8_t event);
typedef void (*getADCp)();

/// stoppt alle events von dieser taste bis eine kurze Zeit abgelaufen ist
void pauseEvents(uint8_t enuk);
/// liefert die Zahl der schnellen Wiederholungen dieser Taste
uint8_t getEventDbl(uint8_t event);
/// stoppt alle events von dieser taste bis diese wieder losgelassen wird
void    killEvents(uint8_t enuk);
/// liefert den Wert einer beliebigen Taste KEY_MENU..SW_Trainer
bool    keyState(EnumKeys enuk);
/// Liefert das naechste Tasten-Event, auch trim-Tasten.
/// Das Ergebnis hat die Form:
/// EVT_KEY_BREAK(key), EVT_KEY_FIRST(key), EVT_KEY_REPT(key) oder EVT_KEY_LONG(key)
uint8_t getEvent();

/// goto given Menu, but substitute current menu in menuStack
void    chainMenu(MenuFuncP newMenu);
/// goto given Menu, store current menu in menuStack
void    pushMenu(MenuFuncP newMenu);
///deliver address of last menu which was popped from
MenuFuncP lastPopMenu();
/// return to last menu in menustack
/// if uppermost is set true, thenmenu return to uppermost menu in menustack
void    popMenu(bool uppermost=false);
/// Gibt Alarm Maske auf lcd aus.
/// Die Maske wird so lange angezeigt bis eine beliebige Taste gedrueckt wird.
void alert(const prog_char * s, bool defaults=false);
void message(const prog_char * s);
/// periodisches Hauptprogramm
void    perMain();
/// Bearbeitet alle zeitkritischen Jobs.
/// wie z.B. einlesen aller Eingaenge, Entprellung, Key-Repeat..
void    per10ms();
/// Erzeugt periodisch alle Outputs ausser Bildschirmausgaben.
void zeroVariables();
void perOut(int16_t *chanOut, uint8_t zeroInput);
///   Liefert den Zustand des Switches 'swtch'. Die Numerierung erfolgt ab 1
///   (1=SW_ON, 2=SW_ThrCt, 10=SW_Trainer). 0 Bedeutet not conected.
///   Negative Werte  erzeugen invertierte Ergebnisse.
///   Die Funktion putsDrSwitches(..) erzeugt den passenden Ausdruck.
///
///   \param swtch
///     0                : not connected. Liefert den Wert 'nc'
///     1.. MAX_DRSWITCH : SW_ON .. SW_Trainer
///    -1..-MAX_DRSWITCH : negierte Werte
///   \param nc Wert, der bei swtch==0 geliefert wird.
bool    getSwitch(int8_t swtch, bool nc, uint8_t level=0);
/// Zeigt den Namen des Switches 'swtch' im display an
///   \param x     x-koordinate 0..127
///   \param y     y-koordinate 0..63 (nur durch 8 teilbar)
///   \param swtch -MAX_DRSWITCH ..  MAX_DRSWITCH
///   \param att   NO_INV,INVERS,BLINK
///
void putsDrSwitches(uint8_t x,uint8_t y,int8_t swtch,uint8_t att);
void putsTmrMode(uint8_t x, uint8_t y, uint8_t attr);

uint16_t getTmr16KHz();


void checkMem();
void checkTHR();
///   Pr�ft beim Einschalten ob alle Switches 'off' sind.
void    checkSwitches();

/// Bearbeite alle events die zum gewaehlten mode passen.
/// KEY_LEFT u. KEY_RIGHT
/// oder KEY_UP u. KEY_DOWN falls _FL_VERT in i_flags gesetzt ist.
/// Dabei wird der Wert der Variablen i_pval unter Beachtung der Grenzen
/// i_min und i_max veraendet.
/// i_pval hat die Groesse 1Byte oder 2Bytes falls _FL_SIZE2  in i_flags gesetzt ist
/// falls EE_GENERAL oder EE_MODEL in i_flags gesetzt ist wird bei Aenderung
/// der Variablen zusaetzlich eeDirty() aufgerufen.
/// Als Bestaetigung wird beep() aufgerufen bzw. beepWarn() wenn die Stellgrenze erreicht wird.
bool checkIncDecGen2(uint8_t event, void *i_pval, int16_t i_min, int16_t i_max, uint8_t i_flags);

///Hilfs-template zum Speichersparenden Aufruf von checkIncDecGen2
template<int16_t min,int16_t max>
bool checkIncDecModVar(uint8_t event, void*p, uint8_t flags)
{
  return checkIncDecGen2(event, p, min, max, flags);
}

//void getADC_filt();
//void getADC_osmp();
//void getADC_single();
#define GETADC_SING = 0
#define GETADC_OSMP = 1
#define GETADC_FILT = 2



///Hilfs-funktion zum Aufruf von checkIncDecGen2 fuer bitfield Variablen
int8_t checkIncDec_hm(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max);
///Hilfs-funktion zum Aufruf von checkIncDecGen2 fuer bitfield Variablen
int8_t checkIncDec_vm(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max);
///Hilfs-funktion zum Aufruf von checkIncDecGen2 fuer bitfield Variablen
int8_t checkIncDec_hg(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max);
///Hilfs-funktion zum Aufruf von checkIncDecGen2 fuer bitfield Variablen
int8_t checkIncDec_vg(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max);

#ifdef FRSKY
// Gruvin: This uses a new _FL_UNSIGNED flag to allow for unsigned values, so 0-255 works in an 8bit var. 
int8_t checkIncDec_Frsky(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max);
#endif

extern bool    checkIncDec_Ret;//global helper vars
extern uint8_t s_editMode;     //global editmode

#define _FL_SIZE2      4
#define _FL_VERT       8
#define _FL_UNSIGNED8 16

#define CHECK_INCDEC_H_GENVAR( event, var, min, max)     \
  checkIncDecModVar<min,max>(event,&var,(sizeof(var)==2 ? _FL_SIZE2 : 0)|EE_GENERAL) \

#define CHECK_INCDEC_H_MODELVAR( event, var, min, max)     \
  checkIncDecModVar<min,max>(event,&var,(sizeof(var)==2 ? _FL_SIZE2 : 0)|EE_MODEL) \

#define CHECK_INCDEC_V_MODELVAR( event, var, min, max)     \
  checkIncDecModVar<min,max>(event,&var,(sizeof(var)==2 ? _FL_SIZE2 : 0)|_FL_VERT|EE_MODEL) \

//for bitfields
#define CHECK_INCDEC_H_GENVAR_BF( event, var, min, max)               \
  ( var=checkIncDec_hg(event,var,min,max),                              \
    checkIncDec_Ret                                                     \
  )
#define CHECK_INCDEC_H_MODELVAR_BF( event, var, min, max)               \
  ( var=checkIncDec_hm(event,var,min,max),                              \
    checkIncDec_Ret                                                     \
  )
#define CHECK_INCDEC_V_MODELVAR_BF( event, var, min, max)               \
  ( var=checkIncDec_vm(event,var,min,max),                              \
    checkIncDec_Ret                                                     \
  )



#define STORE_MODELVARS eeDirty(EE_MODEL)
#define BACKLIGHT_ON    PORTB |=  (1<<OUT_B_LIGHT)
#define BACKLIGHT_OFF   PORTB &= ~(1<<OUT_B_LIGHT)




/// liefert Dimension eines Arrays
#define DIM(arr) (sizeof((arr))/sizeof((arr)[0]))

/// liefert Betrag des Arguments
template<class t> inline t abs(t a){ return a>0?a:-a; }
/// liefert das Minimum der Argumente
template<class t> inline t min(t a, t b){ return a<b?a:b; }
/// liefert das Maximum der Argumente
template<class t> inline t max(t a, t b){ return a>b?a:b; }
template<class t> inline int8_t sgn(t a){ return a>0 ? 1 : (a < 0 ? -1 : 0); }


#define EE_GENERAL 1
#define EE_MODEL   2
#ifdef FRSKY
#define EE_FRSKY  32
#endif

/// Markiert einen EEPROM-Bereich als dirty. der Bereich wird dann in
/// eeCheck ins EEPROM zurueckgeschrieben.
void eeWriteBlockCmp(const void *i_pointer_ram, void *i_pointer_eeprom, size_t size);
void eeDirty(uint8_t msk);
void eeCheck(bool immediately=false);
//void eeWriteGeneral();
void eeReadAll();
void eeLoadModelName(uint8_t id,char*buf,uint8_t len);
uint16_t eeFileSize(uint8_t id);
void eeLoadModel(uint8_t id);
//void eeSaveModel(uint8_t id);
bool eeDuplicateModel(uint8_t id);

#define NUM_PPM     8
//number of real outputchannels CH1-CH8
#define NUM_CHNOUT   16
///number of real input channels (1-9) plus virtual input channels X1-X4
#define NUM_XCHNRAW (NUM_CHNOUT+9+NUM_PPM) // NUMCH + P1P2P3+ AIL/RUD/ELE/THR + MAX/FULL
///number of real output channels (CH1-CH8) plus virtual output channels X1-X4
#define NUM_XCHNOUT (NUM_CHNOUT) //(NUM_CHNOUT)//+NUM_VIRT)

//#define MAX_CHNRAW 8
/// Schreibt [RUD ELE THR AIL P1 P2 P3 MAX] aufs lcd
void putsChnRaw(uint8_t x,uint8_t y,uint8_t idx1,uint8_t att);
//#define MAX_CHN 8

/// Schreibt [CH1 CH2 CH3 CH4 CH5 CH6 CH7 CH8] aufs lcd
void putsChn(uint8_t x,uint8_t y,uint8_t idx1,uint8_t att);
/// Schreibt die Batteriespannung aufs lcd
void putsVBat(uint8_t x,uint8_t y,uint8_t hideV,uint8_t att);
void putsTime(uint8_t x,uint8_t y,int16_t tme,uint8_t att,uint8_t att2);

extern inline int16_t calc100toRESX(int8_t x)
{
  return (int16_t)x*10 + x/4 - x/64;
}

extern inline int16_t calc1000toRESX(int16_t x)
{
  return x + x/32 - x/128 + x/512;
}



#define TMR_VAROFS  16

#define SUB_MODE_V     1
#define SUB_MODE_H     2
#define SUB_MODE_H_DBL 3
//uint8_t checkSubGen(uint8_t event,uint8_t num, uint8_t sub, uint8_t mode);

void menuProcLimits(uint8_t event);
void menuProcMixOne(uint8_t event);
void menuProcMix(uint8_t event);
void menuProcCurve(uint8_t event);
void menuProcTrim(uint8_t event);
void menuProcExpoOne(uint8_t event);
void menuProcExpoAll(uint8_t event);
void menuProcModel(uint8_t event);
void menuProcDiagCalib(uint8_t event);
void menuProcDiagAna(uint8_t event);
void menuProcDiagKeys(uint8_t event);
void menuProcDiagVers(uint8_t event);
void menuProcPPMIn(uint8_t event);
void menuProcSetup(uint8_t event);
void menuProcMain(uint8_t event);
void menuProcModelSelect(uint8_t event);
void menuProcTemplates(uint8_t event);
void menuProcSwitches(uint8_t event);

#ifdef FRSKY
void menuProcFrsky(uint8_t event);
void menuProcFrskyAlarms(uint8_t event);
#endif

void menuProcStatistic2(uint8_t event);
void menuProcStatistic(uint8_t event);
void menuProc0(uint8_t event);

void setupPulses();
void setupPulsesPPM();
void setupPulsesSilver();
void setupPulsesTracerCtp1009();

void initTemplates();

extern int16_t intpol(int16_t, uint8_t);

//extern uint16_t s_ana[8];
extern uint16_t anaIn(uint8_t chan);
extern int16_t calibratedStick[7];
extern int16_t ex_chans[NUM_CHNOUT];

#ifdef JETI
// Jeti-DUPLEX Telemetry
extern uint16_t jeti_keys;
#include "jeti.h"
#endif

#ifdef FRSKY
// FrSky Telemetry
#include "frsky.h"
#endif

//extern TrainerData g_trainer;
//extern uint16_t           g_anaIns[8];
extern uint8_t            g_vbat100mV;
extern volatile uint16_t  g_tmr10ms;
extern volatile uint8_t   g_blinkTmr10ms;
extern uint8_t            g_beepCnt;
extern uint8_t            g_beepVal[5];
extern const PROGMEM char modi12x3[];
//extern uint16_t           pulses2MHz[9];
extern uint16_t           pulses2MHz[120];
extern int16_t            g_ppmIns[8];
extern int16_t            g_chans512[NUM_CHNOUT];
extern volatile uint8_t   tick10ms;

#include "lcd.h"
extern const char stamp1[];
extern const char stamp2[];
extern const char stamp3[];
extern const char stamp4[];
extern const char stamp5[];
#include "myeeprom.h"

#define FLASH_DURATION 50

extern uint8_t  beepAgain;
extern uint16_t g_LightOffCounter;
extern uint8_t mixWarning;

/// Erzeugt einen beep der laenge b
inline void _beep(uint8_t b) {
  g_beepCnt=b;
}

#ifdef BEEPSPKR
extern uint8_t toneFreq;
inline void _beepSpkr(uint8_t d, uint8_t f)
{
  g_beepCnt=d;
  toneFreq=f;
}
#endif

#ifdef BEEPSPKR

#define beepKeySpkr(freq) _beepSpkr(g_beepVal[0],freq)
#define beepTrimSpkr(freq) _beepSpkr(g_beepVal[0],freq)
#define beepWarn1Spkr(freq) _beepSpkr(g_beepVal[1],freq)
#define beepWarn2Spkr(freq) _beepSpkr(g_beepVal[2],freq)
#define beepKey() _beepSpkr(g_beepVal[0],BEEP_DEFAULT_FREQ)
#define beepWarn() _beepSpkr(g_beepVal[3],BEEP_DEFAULT_FREQ)
#define beepWarn1() _beepSpkr(g_beepVal[1],BEEP_DEFAULT_FREQ)
#define beepWarn2() _beepSpkr(g_beepVal[2],BEEP_DEFAULT_FREQ)
#define beepErr()  _beepSpkr(g_beepVal[4],BEEP_DEFAULT_FREQ)

#else

/// Erzeugt einen kurzen beep
#define beepKey()   _beep(g_beepVal[0])
#define beepWarn() _beep(g_beepVal[3])
#define beepWarn1() _beep(g_beepVal[1])
#define beepWarn2() _beep(g_beepVal[2])
#define beepErr()  _beep(g_beepVal[4])

#endif

#endif // gruvin9x_h
/*eof*/
