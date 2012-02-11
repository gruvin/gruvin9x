#include "gruvin9x.h"
#include "stamp-gruvin9x.h"

#define STR2(s) #s
#define DEFNUMSTR(s)  STR2(s)

const pm_char stamp1[] PROGMEM = "VERS: V" DEFNUMSTR(VERS) "." DEFNUMSTR(TAG_VERS);
const pm_char stamp2[] PROGMEM = "DATE: " DATE_STR;
const pm_char stamp3[] PROGMEM = "TIME: " TIME_STR;
const pm_char stamp4[] PROGMEM = " SVN: " SVN_VERS;
const pm_char stamp5[] PROGMEM = " MOD: " MOD_VERS;
const pm_char stamp6[] PROGMEM = " BLD: " DEFNUMSTR(BUILD_NUM);



