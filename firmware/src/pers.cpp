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
#include "templates.h"


EFile theFile;  //used for any file operation
EFile theFile2; //sometimes we need two files

#define FILE_TYP_GENERAL 1
#define FILE_TYP_MODEL   2

#ifdef FRSKY
#define FILE_TYP_FRSKY   3
#endif

#define partCopy(sizeDst,sizeSrc)                         \
      pSrc -= (sizeSrc);                                  \
      pDst -= (sizeDst);                                  \
      memmove(pDst, pSrc, (sizeSrc));                     \
      memset (pDst+(sizeSrc), 0,  (sizeDst)-(sizeSrc));
#define fullCopy(size) partCopy(size,size)
void generalDefault()
{
  memset(&g_eeGeneral,0,sizeof(g_eeGeneral));
  g_eeGeneral.myVers   =  GENERAL_MYVER;
  g_eeGeneral.currModel=  0;
  g_eeGeneral.contrast = 25;
  g_eeGeneral.vBatWarn = 90;
#ifdef DEFAULTMODE1
  g_eeGeneral.stickMode=  0; // default to mode 1
#else
  g_eeGeneral.stickMode=  2; // default to mode 2
#endif
  for (int i = 0; i < 7; ++i) {
    g_eeGeneral.calibMid[i]     = 0x200;
    g_eeGeneral.calibSpanNeg[i] = 0x180;
    g_eeGeneral.calibSpanPos[i] = 0x180;
  }
  int16_t sum=0;
  for(int i=0; i<12;i++) sum+=g_eeGeneral.calibMid[i];
  g_eeGeneral.chkSum = sum;
}
bool eeLoadGeneral()
{
  theFile.openRd(FILE_GENERAL);
  uint8_t sz = theFile.readRlc((uint8_t*)&g_eeGeneral, sizeof(EEGeneral));
  uint16_t sum=0;
  if(sz == sizeof(EEGeneral)  && g_eeGeneral.myVers==GENERAL_MYVER){
    for(int i=0; i<12;i++) sum+=g_eeGeneral.calibMid[i];
    return g_eeGeneral.chkSum == sum;
  }
  return false;
}

#ifdef FRSKY
void frskyDefault()
{
  memset(&g_eeFrsky, 0, sizeof(g_eeFrsky));
  g_eeFrsky.myVers = FRSKY_MYVER;
  g_eeFrsky.rxVoltsChannel  = 1;
  g_eeFrsky.rxVoltsMax      = 66;   // 6.6V
  g_eeFrsky.rxVoltsOfs      = -1;   // -0.1V
  g_eeFrsky.rxVoltsBarMin   = 40;   // 4.0V
  g_eeFrsky.rxVoltsBarMax   = 66;   // 6.6V
  g_eeFrsky.noDataAlarm = 0; // no
}
bool eeLoadFrsky()
{
  theFile.openRd(FILE_FRSKY);
  uint8_t sz = theFile.readRlc((uint8_t*)&g_eeFrsky, sizeof(EEFrskyData));
  return(sz == sizeof(EEFrskyData)  && g_eeFrsky.myVers==FRSKY_MYVER);
}
#endif

void modelDefault(uint8_t id)
{
  memset(&g_model, 0, sizeof(g_model));
  strcpy_P(g_model.name,PSTR("MODEL     "));
  g_model.name[5]='0'+(id+1)/10;
  g_model.name[6]='0'+(id+1)%10;
  g_model.mdVers = MDVERS;

  //for(uint8_t i= 0; i<4; i++){
  //  g_model.mixData[i].destCh = i+1;
  //  g_model.mixData[i].srcRaw = i+1;
  //  g_model.mixData[i].weight = 100;
  //}
  applyTemplate(0); //default 4 channel template
}
void eeLoadModelName(uint8_t id,char*buf,uint8_t len)
{
  if(id<MAX_MODELS)
  {
    //eeprom_read_block(buf,(void*)modelEeOfs(id),sizeof(g_model.name));
    theFile.openRd(FILE_MODEL(id));
    memset(buf,' ',len);
    if(theFile.readRlc((uint8_t*)buf,sizeof(g_model.name)) == sizeof(g_model.name) )
    {
      uint16_t sz=theFile.size();
      buf+=len;
      while(sz){ --buf; *buf='0'+sz%10; sz/=10;}
    }
  }
}

uint16_t eeFileSize(uint8_t id)
{
    theFile.openRd(FILE_MODEL(id));
    return theFile.size();
}

void eeLoadModel(uint8_t id)
{
  if(id<MAX_MODELS)
  {
    theFile.openRd(FILE_MODEL(id));
    uint16_t sz = theFile.readRlc((uint8_t*)&g_model, sizeof(g_model));

    switch (g_model.mdVers){
      default:
        if(sz != sizeof(ModelData)) {
          //alert("Error Loading Model");
          modelDefault(id);
        }
        break;
    }
  }
}

bool eeDuplicateModel(uint8_t id)
{
  uint8_t i;
  for( i=id+1; i<MAX_MODELS; i++)
  {
    if(! EFile::exists(FILE_MODEL(i))) break;
  }
  if(i==MAX_MODELS) return false; //no free space in directory left

  theFile.openRd(FILE_MODEL(id));
  theFile2.create(FILE_MODEL(i),FILE_TYP_MODEL,600);
  uint8_t buf[15];
  uint8_t l;
  while((l=theFile.read(buf,15)))
  {
    theFile2.write(buf,l);
//    if(theFile.errno()==ERR_TMO)
//    {
//        //wait for 10ms and try again
//        uint16_t tgtime = g_tmr10ms + 100;
//        while (g_tmr10ms!=tgtime);
//        theFile2.write(buf,l);
//    }
    wdt_reset();
  }
  theFile2.closeTrunc();
  //XXX: todo error handling
  return true;
}
void eeReadAll()
{
  if(!EeFsOpen()  ||
     EeFsck() < 0 ||
     !eeLoadGeneral()
  )
  {
    alert(PSTR("Bad EEprom Data"), true);
    message(PSTR("EEPROM Formatting"));
    EeFsFormat();
    //alert(PSTR("format ok"));
    generalDefault();
    // alert(PSTR("default ok"));

    uint16_t sz = theFile.writeRlc(FILE_GENERAL,FILE_TYP_GENERAL,(uint8_t*)&g_eeGeneral,sizeof(EEGeneral),200);
    if(sz!=sizeof(EEGeneral)) alert(PSTR("genwrite error"));

    modelDefault(0);
    //alert(PSTR("modef ok"));
    theFile.writeRlc(FILE_MODEL(0),FILE_TYP_MODEL,(uint8_t*)&g_model,sizeof(g_model),200);
    //alert(PSTR("modwrite ok"));
  }

#ifdef FRSKY
  if(!eeLoadFrsky()){
    frskyDefault();
    // alert(PSTR("FrSky Default OK"));
    theFile.writeRlc(FILE_FRSKY, FILE_TYP_FRSKY,(uint8_t *)&g_eeFrsky,sizeof(g_eeFrsky), 100);
    // alert(PSTR("FrSky write OK"));
  }
#endif
  eeLoadModel(g_eeGeneral.currModel);
}


static uint8_t  s_eeDirtyMsk;
static uint16_t s_eeDirtyTime10ms;
void eeDirty(uint8_t msk)
{
  if(!msk) return;
  s_eeDirtyMsk      |= msk;
  s_eeDirtyTime10ms  = g_tmr10ms;
}
#define WRITE_DELAY_10MS 100
void eeCheck(bool immediately)
{
  uint8_t msk  = s_eeDirtyMsk;
  if(!msk) return;
  if( !immediately && ((g_tmr10ms - s_eeDirtyTime10ms) < WRITE_DELAY_10MS)) return;
  s_eeDirtyMsk = 0;
  if(msk & EE_GENERAL){
    if(theFile.writeRlc(FILE_TMP, FILE_TYP_GENERAL, (uint8_t*)&g_eeGeneral,
                        sizeof(EEGeneral),20) == sizeof(EEGeneral))
    {
      EFile::swap(FILE_GENERAL,FILE_TMP);
    }else{
      if(theFile.errno()==ERR_TMO){
        s_eeDirtyMsk |= EE_GENERAL; //try again
        s_eeDirtyTime10ms = g_tmr10ms - WRITE_DELAY_10MS;
      }else{
        alert(PSTR("EEPROM overflow"));
      }
    }
    //first finish GENERAL, then MODEL !!avoid Toggle effect
  }
#ifdef FRSKY
    // G: ... or then FRSKY. What's Toggle Effect? Hmmm. :/
  else if (msk & EE_FRSKY){
// ref: uint16_t EFile::writeRlc(uint8_t i_fileId, uint8_t typ,uint8_t*buf,uint16_t i_len, uint8_t maxTme10ms){
    if(theFile.writeRlc(FILE_TMP, FILE_TYP_FRSKY, (uint8_t*)&g_eeFrsky,
                        sizeof(g_eeFrsky),10) == sizeof(g_eeFrsky))
    {
      EFile::swap(FILE_FRSKY,FILE_TMP);
    }else{
      if(theFile.errno()==ERR_TMO){
        s_eeDirtyMsk |= EE_MODEL; //try again
        s_eeDirtyTime10ms = g_tmr10ms - WRITE_DELAY_10MS;
      }else{
        alert(PSTR("EEPROM overflow"));
      }
    }
  }
#endif
  else if(msk & EE_MODEL){
    if(theFile.writeRlc(FILE_TMP, FILE_TYP_MODEL, (uint8_t*)&g_model,
                        sizeof(g_model),20) == sizeof(g_model))
    {
      EFile::swap(FILE_MODEL(g_eeGeneral.currModel),FILE_TMP);
    }else{
      if(theFile.errno()==ERR_TMO){
        s_eeDirtyMsk |= EE_MODEL; //try again
        s_eeDirtyTime10ms = g_tmr10ms - WRITE_DELAY_10MS;
      }else{
        alert(PSTR("EEPROM overflow"));
      }
    }
  }
  //beepWarn1();
}
