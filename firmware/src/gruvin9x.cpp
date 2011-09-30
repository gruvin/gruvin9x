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
#include "s9xsplash.lbm"

/*
mode1 rud ele thr ail
mode2 rud thr ele ail
mode3 ail ele thr rud
mode4 ail thr ele rud
*/



EEGeneral  g_eeGeneral;
ModelData  g_model;
#ifdef FRSKY
EEFrskyData g_eeFrsky;
#endif

#ifdef BEEPSPKR
// gruvin: Tone Generator Globals
uint8_t toneFreq = BEEP_DEFAULT_FREQ;
uint8_t toneOn = false;
#endif

bool warble = false;

const prog_char APM modi12x3[]=
  "RUD ELE THR AIL "
  "RUD THR ELE AIL "
  "AIL ELE THR RUD "
  "AIL THR ELE RUD ";


void putsTime(uint8_t x,uint8_t y,int16_t tme,uint8_t att,uint8_t att2)
{
  //uint8_t fw=FWNUM; //FW-1;
  //if(att&DBLSIZE) fw+=fw;

  lcd_putcAtt(   x,   y, tme<0 ?'-':' ',att);
  x += (att&DBLSIZE) ? FWNUM*5 : FWNUM*3+2;
  lcd_putcAtt(   x+3, y, ':',att & ~INVERS);
  lcd_outdezNAtt(x,   y, abs(tme)/60,LEADING0|att,2);
  x += (att&DBLSIZE) ? FWNUM*5-1 : FWNUM*4-2;
  lcd_outdezNAtt(x,   y, abs(tme)%60,LEADING0|att2,2);
}
void putsVBat(uint8_t x,uint8_t y,uint8_t hideV,uint8_t att)
{
  //att |= g_vbat100mV < g_eeGeneral.vBatWarn ? BLINK : 0;
  if(!hideV) lcd_putcAtt(   x+ 4*FW,   y,    'V',att);
  lcd_outdezAtt( x+ 4*FW,   y,   g_vbat100mV,att);
}
void putsChnRaw(uint8_t x,uint8_t y,uint8_t idx1,uint8_t att)
{
  if(!idx1)
    lcd_putsnAtt(x,y,PSTR("----"),4,att);
  else if((idx1>=1) && (idx1 <=4))
    lcd_putsnAtt(x,y,modi12x3+g_eeGeneral.stickMode*16+4*(idx1-1),4,att);
  else                  // 4   5   6   7   8   9
    lcd_putsnAtt(x,y,PSTR("P1  P2  P3  MAX FULLPPM1PPM2PPM3PPM4PPM5PPM6PPM7PPM8CH1 CH2 CH3 CH4 CH5 CH6 CH7 CH8 CH9 CH10CH11CH12CH13CH14CH15CH16"
                          "CH17CH18CH19CH20CH21CH22CH23CH24CH25CH26CH27CH28CH29CH30")+4*(idx1-5),4,att);
}
void putsChn(uint8_t x,uint8_t y,uint8_t idx1,uint8_t att)
{
  // !! todo NUM_CHN !!
  lcd_putsnAtt(x,y,PSTR("--- CH1 CH2 CH3 CH4 CH5 CH6 CH7 CH8 CH9 CH10CH11CH12CH13CH14CH15CH16"
                        "CH17CH18CH19CH20CH21CH22CH23CH24CH25CH26CH27CH28CH29CH30")+4*idx1,4,att);
}

void putsDrSwitches(uint8_t x,uint8_t y,int8_t idx1,uint8_t att)//, bool nc)
{
  switch(idx1){
    case  0:            lcd_putsAtt(x+FW,y,PSTR("---"),att);return;
    case  MAX_DRSWITCH: lcd_putsAtt(x+FW,y,PSTR("ON "),att);return;
    case -MAX_DRSWITCH: lcd_putsAtt(x+FW,y,PSTR("OFF"),att);return;
  }
  lcd_putcAtt(x,y, idx1<0 ? '!' : ' ',att);
  lcd_putsnAtt(x+FW,y,PSTR(SWITCHES_STR)+3*(abs(idx1)-1),3,att);
}

void putsTmrMode(uint8_t x, uint8_t y, uint8_t attr)
{
  int8_t tm = g_model.tmrMode;
  if(abs(tm)<TMR_VAROFS) {
    lcd_putsnAtt(  x, y, PSTR("OFFABSRUsRU%ELsEL%THsTH%ALsAL%P1 P1%P2 P2%P3 P3%")+3*abs(tm),3,attr);
    if(tm<(-TMRMODE_ABS)) lcd_putcAtt(x-1*FW,  y,'!',attr);
    return;
  }

  if(abs(tm)<(TMR_VAROFS+MAX_DRSWITCH-1)) { //normal on-off
    putsDrSwitches( x-1*FW,y,tm>0 ? tm-(TMR_VAROFS-1) : tm+(TMR_VAROFS-1),attr);
    return;
  }

  putsDrSwitches( x-1*FW,y,tm>0 ? tm-(TMR_VAROFS+MAX_DRSWITCH-1-1) : tm+(TMR_VAROFS+MAX_DRSWITCH-1-1),attr);//momentary on-off
  lcd_putcAtt(x+3*FW,  y,'m',attr);
}

inline int16_t getValue(uint8_t i)
{
    if(i<MIX_MAX) return calibratedStick[i];//-512..512
    else if(i<=MIX_FULL) return 1024; //FULL/MAX
    else if(i<MIX_FULL+NUM_PPM) return (g_ppmIns[i-MIX_FULL] - g_eeGeneral.ppmInCalib[i-MIX_FULL])*2;
    else return ex_chans[i-MIX_FULL-NUM_PPM];
    return 0;
}

bool getSwitch(int8_t swtch, bool nc, uint8_t level)
{
  if(level>5) return false; //prevent recursive loop going too deep

  switch(swtch){
    case  0:            return  nc;
    case  MAX_DRSWITCH: return  true;
    case -MAX_DRSWITCH: return  false;
  }

  uint8_t dir = swtch>0;
  if(abs(swtch)<(MAX_DRSWITCH-NUM_CSW)) {
    if(!dir) return ! keyState((EnumKeys)(SW_BASE-swtch-1));
    return            keyState((EnumKeys)(SW_BASE+swtch-1));
  }

  //custom switch, Issue 78
  //use putsChnRaw
  //input -> 1..4 -> sticks,  5..8 pots
  //MAX,FULL - disregard
  //ppm
  CSwData &cs = g_model.customSw[abs(swtch)-(MAX_DRSWITCH-NUM_CSW)];
  if(!cs.func) return false;


  int8_t a = cs.v1;
  int8_t b = cs.v2;
  int16_t x = 0;
  int16_t y = 0;

  // init values only if needed
  uint8_t s = CS_STATE(cs.func);
  if(s == CS_VOFS)
  {
      x = getValue(cs.v1-1);
      y = calc100toRESX(cs.v2);
  }
  else if(s == CS_VCOMP)
  {
      x = getValue(cs.v1-1);
      y = getValue(cs.v2-1);
  }

  switch (cs.func) {
  case (CS_VPOS):
      return swtch>0 ? (x>y) : !(x>y);
      break;
  case (CS_VNEG):
      return swtch>0 ? (x<y) : !(x<y);
      break;
  case (CS_APOS):
      return swtch>0 ? (abs(x)>y) : !(abs(x)>y);
      break;
  case (CS_ANEG):
      return swtch>0 ? (abs(x)<y) : !(abs(x)<y);
      break;

  case (CS_AND):
      return (getSwitch(a,0,level+1) && getSwitch(b,0,level+1));
      break;
  case (CS_OR):
      return (getSwitch(a,0,level+1) || getSwitch(b,0,level+1));
      break;
  case (CS_XOR):
      return (getSwitch(a,0,level+1) ^ getSwitch(b,0,level+1));
      break;

  case (CS_EQUAL):
      return (x==y);
      break;
  case (CS_NEQUAL):
      return (x!=y);
      break;
  case (CS_GREATER):
      return (x>y);
      break;
  case (CS_LESS):
      return (x<y);
      break;
  case (CS_EGREATER):
      return (x>=y);
      break;
  case (CS_ELESS):
      return (x<=y);
      break;
  default:
      return false;
      break;
  }

}


//#define CS_EQUAL     8
//#define CS_NEQUAL    9
//#define CS_GREATER   10
//#define CS_LESS      11
//#define CS_EGREATER  12
//#define CS_ELESS     13

void doSplash()
{
    if(!g_eeGeneral.disableSplashScreen)
    {
        lcd_clear();
        lcd_img(0, 0, s9xsplash,0,0);
        refreshDiplay();
        lcdSetRefVolt(g_eeGeneral.contrast);

        uint16_t tgtime = g_tmr10ms + 200;  //2sec splash screen
        while(tgtime != g_tmr10ms)
        {
            if(IS_KEY_BREAK(getEvent()))   return;  //wait for key release

            if(getSwitch(g_eeGeneral.lightSw,0) || g_eeGeneral.lightAutoOff)
                BACKLIGHT_ON;
            else
                BACKLIGHT_OFF;
        }
    }
}

void checkMem()
{
  if(g_eeGeneral.disableMemoryWarning) return;
  if(EeFsGetFree() < 200)
  {
    alert(PSTR("EEPROM low mem"));
  }

}
void checkTHR()
{
  if(g_eeGeneral.disableThrottleWarning) return;

  while(g_tmr10ms<20){} //wait for some ana in

  int thrchn=(2-(g_eeGeneral.stickMode&1));//stickMode=0123 -> thr=2121
  //int16_t v      = g_anaIns[thrchn];
  int16_t v      = anaIn(thrchn);

  int16_t lowLim = g_eeGeneral.calibMid[thrchn] - g_eeGeneral.calibSpanNeg[thrchn] +
    g_eeGeneral.calibSpanNeg[thrchn]/8;

  int16_t highLim = g_eeGeneral.calibMid[thrchn] + g_eeGeneral.calibSpanPos[thrchn] -
    g_eeGeneral.calibSpanPos[thrchn]/8;
  //  v -= g_eeGeneral.calibMid[thrchn];
  //v  = v * (512/8) / (max(40,g_eeGeneral.calibSpan[thrchn]/8));
  if(((v>lowLim) && !g_eeGeneral.throttleReversed) || ((v<highLim) && g_eeGeneral.throttleReversed))
  {
    alert(PSTR("THR not idle"));
  }
}

void checkAlarm() // added by Gohst
{
    if(g_eeGeneral.disableAlarmWarning) return;
  if(!g_eeGeneral.beeperVal) alert(PSTR("Alarms Disabled"));
}

void checkSwitches()
{
  if(g_eeGeneral.disableSwitchWarning) return; // if warning is on

  // first - display warning
  lcd_clear();
  lcd_putsAtt(64-5*FW,0*FH,PSTR("ALERT"),DBLSIZE);
  lcd_puts_P(0,4*FH,PSTR("Switches not off"));
  lcd_puts_P(0,7*FH,PSTR("Please reset them"));
  refreshDiplay();
  lcdSetRefVolt(g_eeGeneral.contrast);

  //loop until all switches are reset
  while (1)
  {
    uint8_t i;
    for(i=SW_BASE; i<SW_Trainer; i++)
    {
        if(i==SW_ID0) continue;
        if(getSwitch(i-SW_BASE+1,0)) break;
    }
    if(i==SW_Trainer) return;
  }
}

MenuFuncP g_menuStack[5];

uint8_t  g_menuStackPtr = 0;
uint8_t  g_beepCnt;
uint8_t  g_beepVal[5];

void message(const prog_char * s)
{
  lcd_clear();
  lcd_putsAtt(64-5*FW,0*FH,PSTR("MESSAGE"),DBLSIZE);
  lcd_puts_P(0,4*FW,s);
  refreshDiplay();
  lcdSetRefVolt(g_eeGeneral.contrast);
}

void alert(const prog_char * s, bool defaults)
{
  lcd_clear();
  lcd_putsAtt(64-5*FW,0*FH,PSTR("ALERT"),DBLSIZE);
  lcd_puts_P(0,4*FW,s);
  lcd_puts_P(64-6*FW,7*FH,PSTR("press any Key"));
  refreshDiplay();
  lcdSetRefVolt(defaults ? 25 : g_eeGeneral.contrast);
  beepErr();
  while(1)
  {
    if(IS_KEY_BREAK(getEvent()))   return;  //wait for key release

    if(getSwitch(g_eeGeneral.lightSw,0) || g_eeGeneral.lightAutoOff || defaults)
        BACKLIGHT_ON;
      else
        BACKLIGHT_OFF;
  }
}

uint8_t checkTrim(uint8_t event)
{
  int8_t  k = (event & EVT_KEY_MASK) - TRM_BASE;
  int8_t  s = g_model.trimInc;
  if (s>1) s = 1 << (s-1);  // 1=>1  2=>2  3=>4  4=>8

  if((k>=0) && (k<8))// && (event & _MSK_KEY_REPT))
  {
    //LH_DWN LH_UP LV_DWN LV_UP RV_DWN RV_UP RH_DWN RH_UP
    uint8_t idx = k/2;
    int8_t  v = (s==0) ? (abs(g_model.trim[idx])/4)+1 : s;
    bool thro = (((2-(g_eeGeneral.stickMode&1)) == idx) && (g_model.thrTrim));
    if (thro) v = 4; // if throttle trim and trim trottle then step=4
    int16_t x = (k&1) ? g_model.trim[idx] + v : g_model.trim[idx] - v;   // positive = k&1

    if(((x==0)  ||  ((x>=0) != (g_model.trim[idx]>=0))) && (!thro) && (g_model.trim[idx]!=0))
    {
      g_model.trim[idx]=0;
      killEvents(event);
      warble = false;
#ifdef BEEPSPKR
      beepWarn2Spkr(60);
#else
      beepWarn2();
#endif
    }
    else if(x>-125 && x<125){
      g_model.trim[idx] = (int8_t)x;
      STORE_MODELVARS;
      if(event & _MSK_KEY_REPT) warble = true;
#ifdef BEEPSPKR
      // toneFreq higher/lower according to trim position
      // beepTrimSpkr((x/3)+60);  // Range -125 to 125 = toneFreq: 19 to 101
      beepTrimSpkr((x/4)+60);  // Divide by 4 more efficient. Range -125 to 125 = toneFreq: 28 to 91
#else
      beepKey();
#endif
    }
    else
    {
      g_model.trim[idx] = (x>0) ? 125 : -125;
      STORE_MODELVARS;
      warble = false;
#ifdef BEEPSPKR
      beepWarn2Spkr((x/4)+60);
#else
      beepWarn2();
#endif
    }

    return 0;
  }
  return event;
}

//global helper vars
bool    checkIncDec_Ret;
int16_t p1val;
int16_t p1valdiff;

bool checkIncDecGen2(uint8_t event, void *i_pval, int16_t i_min, int16_t i_max, uint8_t i_flags)
{
  int16_t val;
  
  if (i_flags & _FL_UNSIGNED8)
    val = i_flags & _FL_SIZE2 ? *(uint16_t*)i_pval : *(uint8_t*)i_pval ;
  else
    val = i_flags & _FL_SIZE2 ? *(int16_t*)i_pval : *(int8_t*)i_pval ;

  int16_t newval = val;
  uint8_t kpl=KEY_RIGHT, kmi=KEY_LEFT, kother = -1;

  if(i_flags&_FL_VERT){
    kpl=KEY_UP; kmi=KEY_DOWN;
  }
  if(event & _MSK_KEY_DBL){
    uint8_t hlp=kpl;
    kpl=kmi;
    kmi=hlp;
    event=EVT_KEY_FIRST(EVT_KEY_MASK & event);
  }
  if(event==EVT_KEY_FIRST(kpl) || event== EVT_KEY_REPT(kpl) || (s_editMode && (event==EVT_KEY_FIRST(KEY_UP) || event== EVT_KEY_REPT(KEY_UP))) ) {
    newval++;
#ifdef BEEPSPKR
    beepKeySpkr(BEEP_KEY_UP_FREQ);
#else
    beepKey();
#endif
    kother=kmi;
  }else if(event==EVT_KEY_FIRST(kmi) || event== EVT_KEY_REPT(kmi) || (s_editMode && (event==EVT_KEY_FIRST(KEY_DOWN) || event== EVT_KEY_REPT(KEY_DOWN))) ) {
    newval--;
#ifdef BEEPSPKR
    beepKeySpkr(BEEP_KEY_DOWN_FREQ);
#else
    beepKey();
#endif
    kother=kpl;
  }
  if((kother != (uint8_t)-1) && keyState((EnumKeys)kother)){
    newval=-val;
    killEvents(kmi);
    killEvents(kpl);
  }

  //change values based on P1
  newval -= p1valdiff;

  if(newval>i_max)
  {
    newval = i_max;
    killEvents(event);
#ifdef BEEPSPKR
    beepWarn2Spkr(BEEP_KEY_UP_FREQ);
#else
    beepWarn2();
#endif
  }
  if(newval < i_min)
  {
    newval = i_min;
    killEvents(event);
#ifdef BEEPSPKR
    beepWarn2Spkr(BEEP_KEY_DOWN_FREQ);
#else
    beepWarn2();
#endif
  }
  if(newval != val){
    if(newval==0) {
      pauseEvents(event); // delay before auto-repeat continues
#ifdef BEEPSPKR
      if (newval>val)
        beepWarn2Spkr(BEEP_KEY_UP_FREQ);
      else
        beepWarn2Spkr(BEEP_KEY_DOWN_FREQ);
#else
      beepWarn2();
#endif
    }
    // gruvin: added support for unsigned values to be returned
    if(i_flags & _FL_SIZE2)
      if (i_flags & _FL_UNSIGNED8) *(uint16_t*)i_pval = newval;
      else                        *( int16_t*)i_pval = newval;
    else
      if (i_flags & _FL_UNSIGNED8) *(uint8_t*)i_pval = newval;
      else                        *( int8_t*)i_pval = newval;
#ifdef FRSKY
    eeDirty(i_flags & (EE_GENERAL|EE_MODEL|EE_FRSKY));
#else
    eeDirty(i_flags & (EE_GENERAL|EE_MODEL));
#endif
    return checkIncDec_Ret=true;
  }
  return checkIncDec_Ret=false;
}

int8_t checkIncDec_hm(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max)
{
  checkIncDecGen2(event,&i_val,i_min,i_max,EE_MODEL);
  return i_val;
}
int8_t checkIncDec_vm(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max)
{
  checkIncDecGen2(event,&i_val,i_min,i_max,_FL_VERT|EE_MODEL);
  return i_val;
}
int8_t checkIncDec_hg(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max)
{
  checkIncDecGen2(event,&i_val,i_min,i_max,EE_GENERAL);
  return i_val;
}
int8_t checkIncDec_vg(uint8_t event, int8_t i_val, int8_t i_min, int8_t i_max)
{
  checkIncDecGen2(event,&i_val,i_min,i_max,_FL_VERT|EE_GENERAL);
  return i_val;
}
MenuFuncP lastPopMenu()
{
  return  g_menuStack[g_menuStackPtr+1];
}

void popMenu(bool uppermost)
{
  if(g_menuStackPtr>0){
    g_menuStackPtr = uppermost ? 0 : g_menuStackPtr-1;
    beepKey();
    (*g_menuStack[g_menuStackPtr])(EVT_ENTRY_UP);
  }else{
    alert(PSTR("menuStack underflow"));
  }
}

void chainMenu(MenuFuncP newMenu)
{
  g_menuStack[g_menuStackPtr] = newMenu;
  (*newMenu)(EVT_ENTRY);
  beepKey();
}
void pushMenu(MenuFuncP newMenu)
{

  g_menuStackPtr++;
  if(g_menuStackPtr >= DIM(g_menuStack))
  {
    g_menuStackPtr--;
    alert(PSTR("menuStack overflow"));
    return;
  }
  beepKey();
  g_menuStack[g_menuStackPtr] = newMenu;
  (*newMenu)(EVT_ENTRY);
}

uint8_t  g_vbat100mV;
volatile uint8_t tick10ms = 0;
uint16_t g_LightOffCounter;
void evalCaptures();

void perMain()
{
  static uint16_t lastTMR;
  tick10ms = (g_tmr10ms != lastTMR);
  lastTMR = g_tmr10ms;

  perOut(g_chans512, false);
  if(!tick10ms) return; //make sure the rest happen only every 10ms.

  eeCheck();

  lcd_clear();
  uint8_t evt=getEvent();
  evt = checkTrim(evt);

  if(g_LightOffCounter) g_LightOffCounter--;
  if(evt) g_LightOffCounter = g_eeGeneral.lightAutoOff*500; // on keypress turn the light on 5*100

  if( getSwitch(g_eeGeneral.lightSw,0) || g_LightOffCounter)
      BACKLIGHT_ON;
  else
      BACKLIGHT_OFF;

  static int16_t p1valprev;
  p1valdiff = (p1val-calibratedStick[6])/32;
  if(p1valdiff) {
      p1valdiff = (p1valprev-calibratedStick[6])/2;
      p1val = calibratedStick[6];
  }
  p1valprev = calibratedStick[6];

  g_menuStack[g_menuStackPtr](evt);
  refreshDiplay();

  // PPM signal on phono-jack. In or out? ...
  if(PING & (1<<INP_G_RF_POW)) { //no power -> only phone jack = slave mode
    PORTG &= ~(1<<OUT_G_SIM_CTL); // 0=ppm out
  }else{
    PORTG |=  (1<<OUT_G_SIM_CTL); // 1=ppm-in
//    evalCaptures();
  }

  switch( g_tmr10ms & 0x1f ) { //alle 10ms*32
//    case 1:
      //check light switch and timer
//      if( getSwitch(g_eeGeneral.lightSw,0) || g_LightOffCounter)
//        BACKLIGHT_ON;
//      else
//        BACKLIGHT_OFF;
//      break;

    case 2:
      {
        //check v-bat
        //14.2246465682983   -> 10.7 V  ((2.65+5.07)/2.65*5/1024)*1000  mV
        //0.142246465682983   -> 10.7 V  ((2.65+5.07)/2.65*5/1024)*10    1/10 V
        //0.137176291331963    k=((2.65+5.07)/2.65*5/1024)*10*9.74/10.1
        // g_vbat100mV=g_anaIns[7]*35/256; //34/239;
        // g_vbat100mV += g_vbat100mV*g_eeGeneral.vBatCalib/256;
        //g_vbat100mV = (g_anaIns[7]*35+g_anaIns[7]/4*g_eeGeneral.vBatCalib) / 256;
        uint16_t ab = anaIn(7);

/* 
Gruvin:
  Interesting fault with new unit. Sample is reading 0x06D0 (around 12.3V) but
  we're only seeing around 0.2V displayed! (Calibrate = 0)

  Long story short, the higher voltage of the new 8-pack of AA alkaline cells I put in the stock
  '9X, plus just a tiny bit of calibration applied, were causing an overflow in the 16-bit math,
  causing a wrap-around to a very small voltage.

  See the wiki (VoltageAveraging) if you're interested in my long-winded analysis.
*/

        // G: Running average (virtual 7 stored plus current sample) for batt volts to stablise display
        static uint8_t vbatRunningAvg = 0;
#ifdef THBATVOLTS
        g_vbat100mV = (ab*35 + ab / 4 * g_eeGeneral.vBatCalib) / 512; // G: Hmmm. See above.
#else
        g_vbat100mV = (ab + 4 * g_eeGeneral.vBatCalib) * 36 / 512; // G: Similar still, but no overflow now.
#endif
        // initialize to first sample if on first averaging cycle
        if (vbatRunningAvg==0) vbatRunningAvg = g_vbat100mV;
        vbatRunningAvg = ( (uint16_t)((uint16_t)vbatRunningAvg * 7) + g_vbat100mV) / 8;
        g_vbat100mV = vbatRunningAvg;

        static uint8_t s_batCheck;
        s_batCheck+=32;
        if(s_batCheck==0 && g_vbat100mV < g_eeGeneral.vBatWarn){
          beepErr();
          if (g_eeGeneral.flashBeep) g_LightOffCounter = FLASH_DURATION;
        }
      }
      break;
    case 3:
      {
        // The various "beep" tone lengths
        static prog_uint8_t APM beepTab[]= {
       // 0   1   2   3    4
          0,  0,  0,  0,   0, //quiet
          0,  1,  8, 30, 100, //silent
          1,  1,  8, 30, 100, //normal
          1,  1, 15, 50, 150, //for motor
         10, 10, 30, 50, 150, //for motor
        };
        memcpy_P(g_beepVal,beepTab+5*g_eeGeneral.beeperVal,5);
          //g_beepVal = BEEP_VAL;
      }
      break;
  }

#ifdef FRSKY
//  if (FrskyRxBufferReady)
//    processFrskyPacket(frskyRxBuffer);
#endif
}
int16_t g_ppmIns[8];
uint8_t ppmInState = 0; //0=unsync 1..8= wait for value i-1

#include <avr/interrupt.h>
//#include <avr/wdt.h>
#define HEART_TIMER2Mhz 1;
#define HEART_TIMER10ms 2;

uint8_t heartbeat;

extern uint16_t g_tmr1Latency_max;
extern uint16_t g_tmr1Latency_min;

//ISR(TIMER1_OVF_vect)
ISR(TIMER1_COMPA_vect) //2MHz pulse generation
{
  static uint8_t   pulsePol;
  static uint16_t *pulsePtr = pulses2MHz;

  uint8_t i = 0;
  while((TCNT1L < 10) && (++i < 50))  // Timer does not read too fast, so i
    ;
  uint16_t dt=TCNT1;//-OCR1A;

  if(pulsePol)
  {
    PORTB |=  (1<<OUT_B_PPM);
    pulsePol = 0;
  }else{
    PORTB &= ~(1<<OUT_B_PPM);
    pulsePol = 1;
  }
  g_tmr1Latency_max = max(dt,g_tmr1Latency_max);    // max has leap, therefore vary in length
  g_tmr1Latency_min = min(dt,g_tmr1Latency_min);    // min has leap, therefore vary in length

  OCR1A  = *pulsePtr++;

  if( *pulsePtr == 0) {
    //currpulse=0;
    pulsePtr = pulses2MHz;
    pulsePol = g_model.pulsePol;//0;

    TIMSK &= ~(1<<OCIE1A); //stop reentrance
    sei();
    setupPulses();
    cli();
    TIMSK |= (1<<OCIE1A);
  }
  heartbeat |= HEART_TIMER2Mhz;
}

class AutoLock
{
  uint8_t m_saveFlags;
public:
  AutoLock(){
    m_saveFlags = SREG;
    cli();
  };
  ~AutoLock(){
    if(m_saveFlags & (1<<SREG_I)) sei();
    //SREG = m_saveFlags;// & (1<<SREG_I)) sei();
  };
};

#define STARTADCONV (ADCSRA  = (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) | (1<<ADSC) | (1 << ADIE))
static uint16_t s_anaFilt[8];
uint16_t anaIn(uint8_t chan)
{
  //                     ana-in:   3 1 2 0 4 5 6 7
  //static prog_char APM crossAna[]={4,2,3,1,5,6,7,0}; // wenn schon Tabelle, dann muss sich auch lohnen
  static prog_char APM crossAna[]={3,1,2,0,4,5,6,7};
  volatile uint16_t *p = &s_anaFilt[pgm_read_byte(crossAna+chan)];
  AutoLock autoLock;
  return *p;
}




#define ADC_VREF_TYPE 0x40
void getADC_filt()
{
  static uint16_t t_ana[3][8];
  for (uint8_t adc_input=0;adc_input<8;adc_input++){
      ADMUX=adc_input|ADC_VREF_TYPE;
      // Start the AD conversion
      ADCSRA|=0x40;
      // Wait for the AD conversion to complete
      while ((ADCSRA & 0x10)==0);
      ADCSRA|=0x10;

      s_anaFilt[adc_input] = (s_anaFilt[adc_input]/2 + t_ana[1][adc_input]) & 0xFFFE; //gain of 2 on last conversion - clear last bit
      //t_ana[2][adc_input]  =  (t_ana[2][adc_input]  + t_ana[1][adc_input]) >> 1;
      t_ana[1][adc_input]  = (t_ana[1][adc_input]  + t_ana[0][adc_input]) >> 1;
      t_ana[0][adc_input]  = (t_ana[0][adc_input]  + ADCW               ) >> 1;
    }
}
/*
  s_anaFilt[chan] = (s_anaFilt[chan] + sss_ana[chan]) >> 1;
  sss_ana[chan] = (sss_ana[chan] + ss_ana[chan]) >> 1;
  ss_ana[chan] = (ss_ana[chan] + s_ana[chan]) >> 1;
  s_ana[chan] = (ADC + s_ana[chan]) >> 1;
  */

void getADC_osmp()
{
  uint16_t temp_ana[8] = {0};
  for (uint8_t adc_input=0;adc_input<8;adc_input++){
    for (uint8_t i=0; i<4;i++) {  // Going from 10bits to 11 bits.  Addition = n.  Loop 4^n times
      ADMUX=adc_input|ADC_VREF_TYPE;
      // Start the AD conversion
      ADCSRA|=0x40;
      // Wait for the AD conversion to complete
      while ((ADCSRA & 0x10)==0);
      ADCSRA|=0x10;
      temp_ana[adc_input] += ADCW;
    }
    s_anaFilt[adc_input] = temp_ana[adc_input] / 2; // divide by 2^n to normalize result.
  }
}



void getADC_single()
{
    for (uint8_t adc_input=0;adc_input<8;adc_input++){
      ADMUX=adc_input|ADC_VREF_TYPE;
      // Start the AD conversion
      ADCSRA|=0x40;
      // Wait for the AD conversion to complete
      while ((ADCSRA & 0x10)==0);
      ADCSRA|=0x10;
      s_anaFilt[adc_input]= ADCW * 2; // use 11 bit numbers
    }
}

getADCp getADC[3] = {
  getADC_single,
  getADC_osmp,
  getADC_filt
  };

volatile uint8_t g_tmr16KHz;
ISR(TIMER0_OVF_vect) //continuous timer 16ms (16MHz/1024/256) -- 8-bit counter overflow
{
  g_tmr16KHz++; // gruvin: Not. It's about 62.5Hz (1/256th pf 16KHz) to give 16ms intervals.
                // However, g_tmr16KHz appears to be used to software-construct a 16-bit timer
                // from TIMER-0 (8-bit). See getTmr16KHz, below.
}

uint16_t getTmr16KHz()
{
  while(1){
    uint8_t hb  = g_tmr16KHz;
    uint8_t lb  = TCNT0;
    if(hb-g_tmr16KHz==0) return (hb<<8)|lb;
  }
}

uint8_t beepAgain = 0;
uint8_t beepAgainOrig = 0;
uint8_t beepOn = false;
extern uint16_t g_time_per10; // instantiated in menus.cpp

ISR(TIMER0_COMP_vect, ISR_NOBLOCK) //10ms timer
{
  cli();
  TIMSK &= ~(1<<OCIE0); //stop reentrance
  sei();
#ifdef BEEPSPKR
  OCR0 += 2;
#else  
  OCR0 = OCR0 + 156;
#endif

#ifdef BEEPSPKR
  // gruvin: Begin Tone Generator
  static uint8_t toneCounter;

  if (toneOn)
  {
    toneCounter += toneFreq;
    if ((toneCounter & 0x80) == 0x80)
      PORTE |=  (1<<OUT_E_BUZZER); // speaker output 'high'
    else
      PORTE &=  ~(1<<OUT_E_BUZZER); // speaker output 'low'
  } 
  else
      PORTE &=  ~(1<<OUT_E_BUZZER); // speaker output 'low'
  // gruvin: END Tone Generator

  static uint8_t cnt10ms = 77; // execute 10ms code once every 78 ISRs
  if (cnt10ms-- == 0) // BEGIN { ... every 10ms ... }
  {
    // Begin 10ms event
    cnt10ms = 77; 
    
/*
    // DEBUG: gruvin: crude test to time if I have in fact still got 10ms
    // Test confirms 1 second bips. Too accurate to count error offset over 6 full minutes. (Good.)
    static uint8_t test10ms = 100;
    if (test10ms-- == 0)
    {
      test10ms = 100;
      g_beepCnt = 5;
      beepOn = true; // beep each second (beepOn function turns beep off)
    }
*/

#endif
    
    // Record start time from TCNT1 to record excution time
    uint16_t dt=TCNT1;// TCNT1 (used for PPM out pulse generation) is running at 2MHz

    //cnt >/=0
    //beepon/off
    //beepagain y/n
    if(g_beepCnt) {
        if(!beepAgainOrig) {
            beepAgainOrig = g_beepCnt;
            beepOn = true;
        }
        g_beepCnt--;
    }
    else 
    {
        if(beepAgain && beepAgainOrig) {
            beepOn = !beepOn;
            g_beepCnt = beepOn ? beepAgainOrig : 8;
            if(beepOn) beepAgain--;
        }
        else {
            beepAgainOrig = 0;
            beepOn = false;
            warble = false;
        }
    }

#ifdef BEEPSPKR
    // G: use new tone generator for beeps
    if(beepOn)
    {
      static bool warbleC;
      warbleC = warble && !warbleC;
      if(warbleC)
        toneOn = false;
      else
        toneOn = true;
    }else{
      toneOn = false;
    }

#else
    // G: use original external buzzer for beeps
    if(beepOn){
    static bool warbleC;
    warbleC = warble && !warbleC;
    if(warbleC)
      PORTE &= ~(1<<OUT_E_BUZZER);//buzzer off
    else
      PORTE |=  (1<<OUT_E_BUZZER);//buzzer on
    }else{
      PORTE &= ~(1<<OUT_E_BUZZER);
    }
#endif

    per10ms();
    heartbeat |= HEART_TIMER10ms;

    // Record per10ms code execution time, in us(x2) for STAT2 page
    uint16_t dt2 = TCNT1; // capture end time
    g_time_per10 = dt2 - dt; 

#ifdef BEEPSPKR
  } // end 10ms event
#endif

  cli();
  TIMSK |= (1<<OCIE0);
  sei();
}



// Timer3 used for PPM_IN pulse width capture. Counter running at 16MHz / 8 = 2MHz
// equating to one count every half millisecond. (2 counts = 1ms). Control channel
// count delta values thus can range from about 1600 to 4400 counts (800us to 2200us),
// corresponding to a PPM signal in the range 0.8ms to 2.2ms (1.5ms at center).
// (The timer is free-running and is thus not reset to zero at each capture interval.)
ISR(TIMER3_CAPT_vect, ISR_NOBLOCK) //capture ppm in 16MHz / 8 = 2MHz
{
  uint16_t capture=ICR3; 
  cli();
  ETIMSK &= ~(1<<TICIE3); // prevent re-entrance
  sei();

  static uint16_t lastCapt;

  uint16_t val = (capture - lastCapt) / 2;
  lastCapt = capture;

  // G: We prcoess g_ppmInsright here to make servo movement as smooth as possible
  //    while under trainee control
  if (val>4000 && val < 16000) { // G: Priorotise reset pulse. (Needed when less than 8 incoming pulses)
    ppmInState = 1; // triggered
  } else {
    if (ppmInState && ppmInState<=8) {
      if (val>800 && val<2200){
        g_ppmIns[ppmInState++ - 1] = 
          (int16_t)(val - 1500)*(g_eeGeneral.PPM_Multiplier+10)/10; //+-500 != 512, but close enough.
      } else 
        ppmInState = 0; // not triggered
    }
  }

  cli();
  ETIMSK |= (1<<TICIE3);
  sei();
}

extern uint16_t g_timeMain;
//void main(void) __attribute__((noreturn));

int main(void)
{
  DDRA = 0xff;  PORTA = 0x00;
  DDRB = 0x81;  PORTB = 0x7e; //pullups keys+nc
  DDRC = 0x3e;  PORTC = 0xc1; //pullups nc
  DDRD = 0x00;  PORTD = 0xff; //pullups keys
  DDRE = 0x08;  PORTE = 0xff-(1<<OUT_E_BUZZER); //pullups + buzzer 0
  DDRF = 0x00;  PORTF = 0xff; //anain
  DDRG = 0x10;  PORTG = 0xff; //pullups + SIM_CTL=1 = phonejack = ppm_in
  lcd_init();

#ifdef JETI
  JETI_Init();
#endif

#ifdef FRSKY
  FRSKY_Init();
#endif

  ADMUX=ADC_VREF_TYPE;
  ADCSRA=0x85;

  // TCNT0         10ms = 16MHz/160000  periodic timer
  //TCCR0  = (1<<WGM01)|(7 << CS00);//  CTC mode, clk/1024
  TCCR0  = (7 << CS00);//  Norm mode, clk/1024
#ifdef BEEPSPKR
  OCR0   = 2;   // gruvin: 7812.5 interrupts / second for tone generator
#else
  OCR0   = 156; // 10ms
#endif
  TIMSK |= (1<<OCIE0) |  (1<<TOIE0);

  // TCNT1 2MHz Pulse generator
  TCCR1A = (0<<WGM10);
  TCCR1B = (1 << WGM12) | (2<<CS10); // CTC OCR1A, 16MHz / 8
  //TIMSK |= (1<<OCIE1A); enable immediately before mainloop

  // Timer 3 used for PPM_IN pulse width capture
  TCCR3A  = 0;
#ifdef PPMIN_MOD1
  TCCR3B  = (1<<ICNC3) | (1<<ICES3) | 2;      // Noise Canceller enabled, pos. edge, clock at 16MHz / 8 (2MHz)
#else
  TCCR3B  = (1<<ICNC3) | 2;      // Noise Canceller enabled, neg. edge, clock at 16MHz / 8 (2MHz)
#endif
  ETIMSK |= (1<<TICIE3);         // Enable capture event interrupt

  sei(); //damit alert in eeReadGeneral() nicht haengt
  g_menuStack[0] =  menuProc0;

  lcdSetRefVolt(25);
  eeReadAll();
  doSplash();
  checkMem();
  //setupAdc(); //before checkTHR
  getADC_single();
  checkTHR();
  checkSwitches();
  checkAlarm();
  setupPulses();
  wdt_enable(WDTO_500MS);
  perOut(g_chans512, false);

  pushMenu(menuProcModelSelect);
  popMenu(true);  // this is so the first instance of [MENU LONG] doesn't freak out!
  //g_menuStack[g_menuStackPtr+1] =

  lcdSetRefVolt(g_eeGeneral.contrast);
  g_LightOffCounter = g_eeGeneral.lightAutoOff*500; //turn on light for x seconds - no need to press key Issue 152
  TIMSK |= (1<<OCIE1A); // Pulse generator enable immediately before mainloop
  while(1){
    //uint16_t old10ms=g_tmr10ms;
    uint16_t t0 = getTmr16KHz();
    getADC[g_eeGeneral.filterInput]();
    perMain();
    //while(g_tmr10ms==old10ms) sleep_mode();
    if(heartbeat == 0x3)
    {
      wdt_reset();
      heartbeat = 0;
    }
    t0 = getTmr16KHz() - t0;
    g_timeMain = max(g_timeMain,t0);
  }
}
