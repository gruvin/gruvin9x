#ifndef LOGS_H
#define LOGS_H

#include "gruvin9x.h"
#include "ff.h"

#define TELEM_LOG_PATH "/G9XLOGS" // no trailing slash = important

extern char g_logFilename[13]; // 8+dot+3+null=13 (was "/G9XLOGS/M00_000.TXT\0" max required length = 21)
extern char g_logErrorStr[22]; // 21 char screen width plus null.
extern int8_t g_telemLogState; // 0=closed, >0 = opened, <0 is error
extern FATFS g_FATFS_Obj;
extern FIL g_oLogFile;

extern void initTelemLog();
extern void doTelemLog();

#endif

