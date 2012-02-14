/*
 * Authors (alphabetical order)
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 *
 * Original contributors
 * - Philip Moss Adapted first frsky functions from jeti.cpp code by
 * - Karl Szmutny <shadow@privy.de>

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

#include "logs.h"

char g_logFilename[13]; // 8+dot+3+null
char g_logErrorStr[22] = { 0 };
int8_t g_telemLogState = 0;
FATFS g_FATFS_Obj;
FIL g_oLogFile;
char logFullPath[21]; 

// initTelemLog: Determine and set telemetry log filename
void initTelemLog() // pers.cpp -- after loading model data
{
  FRESULT result;

  // close any file left open. E.G. Changing models with log switch still on.
  if (g_oLogFile.fs) f_close(&g_oLogFile);
  g_telemLogState = 0;

  strcpy_P(g_logFilename, PSTR("M00_000.TXT")); // filename only.

  // Set log file model number
  uint8_t num = g_eeGeneral.currModel + 1;
  char *n = &g_logFilename[2];
  *n = (char)((num % 10) + '0');
  *(--n) = (char)((num / 10) + '0');

  // Loop, skipping over any existing log files ... _000, _001, etc. until we have a unique file name
  result = f_mount(0, &g_FATFS_Obj);
  if (result!=FR_OK)
  {
    strcpy_P(g_logErrorStr, PSTR("SDCARD F/S ERROR"));
    g_telemLogState = -result;
    return;
  }
  while (1)
  {
    strcpy(logFullPath, TELEM_LOG_PATH);
    strcat(logFullPath, "/");
    strcat(logFullPath, g_logFilename);

    result = f_open(&g_oLogFile, logFullPath, FA_OPEN_EXISTING | FA_READ);
    if (result == FR_OK)
    {
      f_close(&g_oLogFile);

      // bump log file counter (file extension)
      n = &g_logFilename[6];
      if (++*n > '9')
      {
        *n='0';
        n--;
        if (++*n > '9')
        {
          *n='0';
          n--;
          if (++*n > '9')
          {
            *n='0';
            break; // Wow. We looped back around past 999 to 000! abort loop
          }
        }
      }
    }
    else if (result == FR_NO_FILE /*TODO check this code. What should happen here? */)
    {
      break;
    }
    else if (result == FR_NO_PATH)
    {
      if (f_mkdir(TELEM_LOG_PATH) != FR_OK)
      {
        strcpy_P(g_logErrorStr, PSTR("Check "));
        strcat(g_logErrorStr, TELEM_LOG_PATH);
        strcat(g_logErrorStr, PSTR(" folder"));
        g_telemLogState = -result;
        return;
      }
    }
    else
    {
      g_telemLogState = -result;
      if (result == FR_NOT_READY)
        strcpy_P(g_logErrorStr, PSTR("NO DATA CARD"));
      else
        strcpy_P(g_logErrorStr, PSTR("CARD ERROR"));
      return;
    }
  } // while
  g_telemLogState = result;

  // g_logFilename should now be set appropriately.
}

// doTelemLog: Append current telemtry and switch status data to log file
// Called every perMain (gruvin9x.cpp) TODO -- NOT GOOD.
// Should be maximum once a second. This either needs to be configurable or
// be called from the Fr-Sky telemetry decode routines, in event-driven fashion.

// Would be best in-lined as well -- but G++ won't allow that to happen with code that's split across files.
// If we really want it inlined, then we'll need to stick it in its own file (log_inc.cpp) and include it 
// where it's wanted. *shrug*
void doTelemLog()
{
  FRESULT result;

  if (isFunctionActive(FUNC_TELEMLOG)) // if FUNC SWITCH for 'Write log data' is on ...
  {
    // Only appeand/create the log file if it's not already open ...
    if (g_telemLogState<=0)
    {
      result = f_mount(0, &g_FATFS_Obj);
      if (result != FR_OK)
      {
        g_telemLogState = -result;
        beepAgain = result - 1;  // DEBUG -- count out error_number beeps
        beepKey();
      }
      else
      {
        // create new log file using filename set up in initTelemLog()
        result = f_open(&g_oLogFile, logFullPath, FA_OPEN_ALWAYS | FA_WRITE);
        if (result != FR_OK)
        {
          g_telemLogState = -result;
          beepAgain = result - 1; // DEBUG -- count out error_number beeps
          beepKey();
        }
        else
        {
          f_lseek(&g_oLogFile, g_oLogFile.fsize); // append
          g_telemLogState = 1;
          beepWarn2(); // DEBUG -- tell user the log is open
        }
      }
    }

    if (g_telemLogState>0)
    {
      // TODO here we write logs
      // For now, append 'anything' as a test
      f_printf(&g_oLogFile, "Appended log line test 100ms=%u\n", g_ms100);

      // Don't close the log file here. We have 'soft off' available on the v4.1 board. Once
      // that is implemented, it can take care of closing the file, should the radio be
      // powered off before the FUNC SWITCH is turned off.
    }
  }
  else if (g_telemLogState > 0)
  {
    f_close(&g_oLogFile);
    beepWarn2();
    g_telemLogState = 0;
  }
}



