/* Name: main.c
 * Project: USBaspLoader
 * Author: Christian Starkjohann
 * Creation Date: 2007-12-08
 * Tabsize: 4
 * Copyright: (c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt)
 * This Revision: $Id: main.c 786 2010-05-30 20:41:40Z cs $
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/boot.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <string.h>

static void leaveBootloader() __attribute__((__noreturn__));

#include "bootloaderconfig.h"
#include "usbdrv/usbdrv.c"

#include "pgmtypes.h"
#include "lcd.h"

/* ------------------------------------------------------------------------ */

/* Request constants used by USBasp */
#define USBASP_FUNC_CONNECT         1
#define USBASP_FUNC_DISCONNECT      2
#define USBASP_FUNC_TRANSMIT        3
#define USBASP_FUNC_READFLASH       4
#define USBASP_FUNC_ENABLEPROG      5
#define USBASP_FUNC_WRITEFLASH      6
#define USBASP_FUNC_READEEPROM      7
#define USBASP_FUNC_WRITEEEPROM     8
#define USBASP_FUNC_SETLONGADDRESS  9

/* ------------------------------------------------------------------------ */

#ifndef ulong
#   define ulong    unsigned long
#endif
#ifndef uint
#   define uint     unsigned int
#endif

/* defaults if not in config file: */
#ifndef HAVE_EEPROM_PAGED_ACCESS
#   define HAVE_EEPROM_PAGED_ACCESS 0
#endif
#ifndef HAVE_EEPROM_BYTE_ACCESS
#   define HAVE_EEPROM_BYTE_ACCESS  0
#endif
#ifndef BOOTLOADER_CAN_EXIT
#   define  BOOTLOADER_CAN_EXIT     0
#endif

/* allow compatibility with avrusbboot's bootloaderconfig.h: */
#ifdef BOOTLOADER_INIT
#   define bootLoaderInit()         BOOTLOADER_INIT
#   define bootLoaderExit()
#endif
#ifdef BOOTLOADER_CONDITION
#   define bootLoaderCondition()    BOOTLOADER_CONDITION
#endif

/* device compatibility: */
#ifndef GICR    /* ATMega*8 don't have GICR, use MCUCR instead */
#   define GICR     MCUCR
#endif

/* ------------------------------------------------------------------------ */

#if (FLASHEND) > 0xffff /* we need long addressing */
#   define CURRENT_ADDRESS  currentAddress.l
#   define addr_t           ulong
#else
#   define CURRENT_ADDRESS  currentAddress.w[0]
#   define addr_t           uint
#endif

typedef union longConverter{
    addr_t  l;
    uint    w[sizeof(addr_t)/2];
    uchar   b[sizeof(addr_t)];
}longConverter_t;

static uchar            requestBootLoaderExit;
static longConverter_t  currentAddress; /* in bytes */
static uchar            bytesRemaining;
static uchar            isLastPage;
#if HAVE_EEPROM_PAGED_ACCESS
static uchar            currentRequest;
#else
static const uchar      currentRequest = 0;
#endif

static const uchar  signatureBytes[4] = {
#ifdef SIGNATURE_BYTES
    SIGNATURE_BYTES
#elif defined (__AVR_ATmega8__) || defined (__AVR_ATmega8HVA__)
    0x1e, 0x93, 0x07, 0
#elif defined (__AVR_ATmega48__) || defined (__AVR_ATmega48P__)
    0x1e, 0x92, 0x05, 0
#elif defined (__AVR_ATmega88__) || defined (__AVR_ATmega88P__)
    0x1e, 0x93, 0x0a, 0
#elif defined (__AVR_ATmega168__) || defined (__AVR_ATmega168P__)
    0x1e, 0x94, 0x06, 0
#elif defined (__AVR_ATmega328P__)
    0x1e, 0x95, 0x0f, 0
#elif defined (__AVR_ATmega2560__)
    0x1e, 0x98, 0x01, 0
#else
#   error "Device signature is not known, please edit bootloader.cpp!"
#endif
};

/* ------------------------------------------------------------------------ */

//static void (*nullVector)(void) __attribute__((__noreturn__));
// G: This doesn't work. It doesn't seem to generate a 32-bit (or 24-bit) address
//    as is requried. Use asm(jmp 0x00000) instead. *shrug* 

static void leaveBootloader()
{
    DBG1(0x01, 0, 0);
    bootLoaderExit();
    cli();
    USB_INTR_ENABLE = 0;
    USB_INTR_CFG = 0;       /* also reset config bits */
    GICR = (1 << IVCE);     /* enable change of interrupt vectors */
    GICR = (0 << IVSEL);    /* move interrupts to application flash section */
/* We must go through a global function pointer variable instead of writing
 *  ((void (*)(void))0)();
 * because the compiler optimizes a constant 0 to "rcall 0" which is not
 * handled correctly by the assembler.
 */
    RAMPZ=0; MCUSR = 0x01; MCUSR = 0x00;
    asm volatile ("jmp 0x00000\n\t" ::);
    for(;;);

    // nullVector(); // G: See my note above.
}

/* ------------------------------------------------------------------------ */

uchar   usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;
uchar           len = 0;
static uchar    replyBuffer[4];

    usbMsgPtr = replyBuffer;
    if(rq->bRequest == USBASP_FUNC_TRANSMIT){   /* emulate parts of ISP protocol */
        uchar rval = 0;
        usbWord_t address;
        address.bytes[1] = rq->wValue.bytes[1];
        address.bytes[0] = rq->wIndex.bytes[0];
        if(rq->wValue.bytes[0] == 0x30){        /* read signature */
            rval = rq->wIndex.bytes[0] & 3;
            rval = signatureBytes[rval];
#if HAVE_EEPROM_BYTE_ACCESS
        }else if(rq->wValue.bytes[0] == 0xa0){  /* read EEPROM byte */
            rval = eeprom_read_byte((void *)address.word);
        }else if(rq->wValue.bytes[0] == 0xc0){  /* write EEPROM byte */
            eeprom_write_byte((void *)address.word, rq->wIndex.bytes[1]);
#endif
#if HAVE_CHIP_ERASE
        }else if(rq->wValue.bytes[0] == 0xac && rq->wValue.bytes[1] == 0x80){  /* chip erase */
            addr_t addr;
            // XXX TODO: The following assumes only 2K bootloader. ATmega2560 has 4K(words?)
            //           We don't allow chip erase, so it doesn't matter for now.
            for(addr = 0; addr < FLASHEND + 1 - 2048; addr += SPM_PAGESIZE) {
                /* wait and erase page */
                DBG1(0x33, 0, 0);
#   ifndef NO_FLASH_WRITE
                boot_spm_busy_wait();
                cli();
                boot_page_erase(addr);
                sei();
#   endif
            }
#endif
        }else{
            /* ignore all others, return default value == 0 */
        }
        replyBuffer[3] = rval;
        len = 4;
    }else if(rq->bRequest == USBASP_FUNC_ENABLEPROG){
        /* replyBuffer[0] = 0; is never touched and thus always 0 which means success */
        len = 1;
    }else if(rq->bRequest >= USBASP_FUNC_READFLASH && rq->bRequest <= USBASP_FUNC_SETLONGADDRESS){
        currentAddress.w[0] = rq->wValue.word;
        if(rq->bRequest == USBASP_FUNC_SETLONGADDRESS){
#if (FLASHEND) > 0xffff
            currentAddress.w[1] = rq->wIndex.word;
#endif
        }else{
            bytesRemaining = rq->wLength.bytes[0];
            /* if(rq->bRequest == USBASP_FUNC_WRITEFLASH) only evaluated during writeFlash anyway */
            isLastPage = rq->wIndex.bytes[1] & 0x02;
#if HAVE_EEPROM_PAGED_ACCESS
            currentRequest = rq->bRequest;
#endif
            len = 0xff; /* hand over to usbFunctionRead() / usbFunctionWrite() */
        }
#if BOOTLOADER_CAN_EXIT
    }else if(rq->bRequest == USBASP_FUNC_DISCONNECT){
        requestBootLoaderExit = 1;      /* allow proper shutdown/close of connection */
#endif
    }else{
        /* ignore: USBASP_FUNC_CONNECT */
    }
    return len;
}

uchar usbFunctionWrite(uchar *data, uchar len)
{
uchar   isLast;

    DBG1(0x31, (void *)&currentAddress.l, 4);
    if(len > bytesRemaining)
        len = bytesRemaining;
    bytesRemaining -= len;
    isLast = bytesRemaining == 0;
    if(currentRequest >= USBASP_FUNC_READEEPROM){
        uchar i;
        for(i = 0; i < len; i++){
            eeprom_write_byte((void *)(currentAddress.w[0]++), *data++);
        }
    }else{
        uchar i;
        for(i = 0; i < len;){
#if !HAVE_CHIP_ERASE
            if((currentAddress.w[0] & (SPM_PAGESIZE - 1)) == 0){    /* if page start: erase */
                DBG1(0x33, 0, 0);
#   ifndef NO_FLASH_WRITE
                cli();
                boot_page_erase(CURRENT_ADDRESS);   /* erase page */
                sei();
                boot_spm_busy_wait();               /* wait until page is erased */
#   endif
            }
#endif
            i += 2;
            DBG1(0x32, 0, 0);
            cli();
            boot_page_fill(CURRENT_ADDRESS, *(short *)data);
            sei();
            CURRENT_ADDRESS += 2;
            data += 2;
            /* write page when we cross page boundary or we have the last partial page */
            if((currentAddress.w[0] & (SPM_PAGESIZE - 1)) == 0 || (isLast && i >= len && isLastPage)){
                DBG1(0x34, 0, 0);
#ifndef NO_FLASH_WRITE
                cli();
                boot_page_write(CURRENT_ADDRESS - 2);
                sei();
                boot_spm_busy_wait();
                cli();
                boot_rww_enable();
                sei();
#endif
            }
        }
        DBG1(0x35, (void *)&currentAddress.l, 4);
    }
    return isLast;
}

uchar usbFunctionRead(uchar *data, uchar len)
{
uchar   i;

    if(len > bytesRemaining)
        len = bytesRemaining;
    bytesRemaining -= len;
    for(i = 0; i < len; i++){
        if(currentRequest >= USBASP_FUNC_READEEPROM){
            *data = eeprom_read_byte((void *)currentAddress.w[0]);
        }else{
#if (FLASHEND) > 0xffff /* we need long addressing */
          *data = pgm_read_byte_far(CURRENT_ADDRESS);
#else
          *data = pgm_read_byte((void *)(unsigned)CURRENT_ADDRESS);
#endif
        }
        data++;
        CURRENT_ADDRESS++;
    }
    return len;
}

/* ------------------------------------------------------------------------ */

static void initForUsbConnectivity(void)
{
uchar   i = 0;

    usbInit();
    /* enforce USB re-enumerate: */
    usbDeviceDisconnect();  /* do this while interrupts are disabled */
    while(--i){         /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
    sei();
}

uint8_t contrast = 28;

int __attribute__((noreturn)) main(void)
{
    /* initialize  */
    wdt_disable();      /* main app may have enabled watchdog */
    bootLoaderInit();
    odDebugInit();
    DBG1(0x00, 0, 0);
#ifndef NO_FLASH_WRITE
    GICR = (1 << IVCE);  /* enable change of interrupt vectors */
    GICR = (1 << IVSEL); /* move interrupts to boot flash section */
#endif

    if(bootLoaderCondition()){

        /////////////////////////////////////////////////////////////////////
        // MAKE SOME NOISE ... (sound beeper _... (Morse 'B' for 'boot' )
        // PORTE |= 1<<3; 
        PORTC |= 1;
        _delay_us(300000);
        // PORTE &= ~(1<<3); 
        PORTC &= 0xfe;

        int x;
        for (x = 0; x < 3; x++)
        {
          _delay_us(100000);
          // PORTE |= 1<<3; 
          PORTC |= 1;
          _delay_us(100000);
          // PORTE &= ~(1<<3); 
          PORTC &= 0xfe;
        }
        /////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////
        // Write somthing semi-useful on the LCD screen ...
        lcd_init();
        lcdSetRefVolt(contrast);
        lcd_clear();
        lcd_puts_P(3*FW+3, 3*FH, PSTR("USBasp Online"));
        lcd_puts_P(0*FW, 0*FH, PSTR("+cntrst"));
        lcd_puts_P(0*FW, 7*FH, PSTR("-cntrst"));
        lcd_puts_P(14*FW+2, 0*FH, PSTR("bklight"));
        lcd_puts_P(17*FW+2, 7*FH, PSTR("exit"));
        refreshDisplay();
        /////////////////////////////////////////////////////

        ///////////////////////////////////
        // Original V_USB code starts here
        ///////////////////////////////////
        uchar i = 0, j = 0;
        initForUsbConnectivity();
        do{
            usbPoll();
            if ((PINL & (1<<5)) == 0) // if [EXIT] key pressed
            {
                if(--i == 0){
                    if(--j == 0)
                    {
                      lcd_clear();
                      lcd_puts_P(2*FW, 3*FH, PSTR("REBOOT!"));
                      refreshDisplay();
                      break;
                    }
                }
            }
            
            static uint16_t r = 0;
            if (r-- == 0)
            {
              r = 0x700;
              lcd_putsnAtt(4*FW+3, 4*FH, 
                  PSTR(
                    "IDLE     "
                    "CONNECT  "
                    "DISCONN  "
                    "TRANSMIT "
                    "RD FLASH "
                    "EN PROG  "
                    "WR FLASH "
                    "RD EEPROM"
                    "WR EEPROM"
                    "SET LADDR"
                  )+9*currentRequest, 9, 0
              );
              lcd_outhex5(15*FW, 4*FH, CURRENT_ADDRESS);
              refreshDisplay();
            }

            // LCD contrast up/down control
            static uint8_t db0, db1, db2, click0, click1, click2 = 0;
            if ((click0 == 0) && ((~PINL & 1) == 1) && (--db0 == 0)) { click0 = 1; lcdSetRefVolt(--contrast); }
            else if ((~PINL & 1) == 0) { db0 = 0; click0 = 0; }

            if ((click1 == 0) && ((~PINL & 2) == 2) && (--db1 == 0)) { click1 = 1; lcdSetRefVolt(++contrast); }
            else if ((~PINL & 2) == 0) { db1 = 0; click1 = 0; }

            // toggle backlight
            if ((click2 == 0) && ((~PINL & 16) == 16) && (--db2 == 0)) { click2 = 1; (PORTC = PINC ^ 1); }
            else if ((~PINL & 16) == 0) { db2 = 0; click2 = 0; }


#if BOOTLOADER_CAN_EXIT
            if(requestBootLoaderExit) 
                if(--i == 0){
                    if(--j == 0)
                        break;
                }
            }
#endif
        } while(1); // we want to remain in loop until [EXIT] is pressed
    }
    leaveBootloader();
    for(;;);
}

/* ------------------------------------------------------------------------ */
