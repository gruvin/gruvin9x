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

#include "gruvin9x.h"
#include "ff.h"

// "/G9XLOGS/M00_000.TXT\0" max required length = 21
char g_logFilename[22];
// These global so we can close any open file from anywhere
FATFS FATFS_Obj;
FIL g_oLogFile;

void startLogs()
{
  // Determine and set log file filename

  FRESULT result;

  // close any file left open. E.G. Changing models with log switch still on.
  if (g_oLogFile.fs) f_close(&g_oLogFile);

  strcpy(g_logFilename, "/G9XLOGS/M00_000.TXT");

  uint8_t num = g_eeGeneral.currModel + 1;
  char *n = &g_logFilename[11];
  *n = (char)((num % 10) + '0');
  *(--n) = (char)((num / 10) + '0');

  result = f_mount(0, &FATFS_Obj);
  if (result!=FR_OK)
  {
    strcpy(g_logFilename, "FILE SYSTEM ERROR");
  }
  else
  {
    // Skip over any existing log files ... _000, _001, etc. (or find first gap in numbering)
    while (1)
    {
      result = f_open(&g_oLogFile, g_logFilename, FA_OPEN_EXISTING | FA_READ);

      if (result == FR_OK)
      {
        f_close(&g_oLogFile);

        // bump log file counter (file extension)
        n = &g_logFilename[15];
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
      else if (result == FR_NO_PATH)
      {
        if (f_mkdir("/G9XLOGS") != FR_OK)
        {
          result = FR_NO_PATH;
          break;
        }
        else
          continue;
      }
      else
        break;
    }

    switch (result)
    {
      case FR_NO_PATH:
        strcpy(g_logFilename, "Check /G9XLOGS folder");
        break;
      case FR_NOT_READY:
        strcpy(g_logFilename, "DATA CARD NOT PRESENT");
        break;

      default:
        break;
    }
  }

  // g_logFilename should now be set appropriately.

}




