#include "bootloader.h"
#include "lcd.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/boot.h>

// Assume we're running on an ATmega2560/1 and that this file is only compiled if that is the case
// Application Flash space available = 256K(x2) bytes total Flash minus 4096 bytes (x2) of bootloader Flash
//#define _B4096
//#define APP_PAGES ((2*(unsigned long)0x3FFFF / PAGESIZE)- (2*4096 / PAGESIZE ))
//#define APP_END (APP_PAGES * PAGESIZE)


int main(void)
{

  // Set up I/O port data directions and initial states
  DDRA = 0xff;  PORTA = 0x00; // LCD data
  DDRC = 0x3f;  PORTC = 0xc0; // 7:N/A, 6:N/A, LCD[5,4,3,2,1], 0:N/A
  DDRL = 0x00;  PORTL = 0xff; // 7-6:Spare6/5 (inputs), 5-0: User Button inputs
  DDRE = 0x04;  PORTE = 0x04; // Bit 3=BUZZER

  uint8_t buttons = 0;
  for (uint16_t x=0; x<5000; x++) // Need this to give time for power supply to stabalise, apparently. *shrug*
  {
    buttons = ~PINL;
    if ((buttons & 3) != 3) // If not [UP] and [DOWN] held down
    {
      RAMPZ=0; MCUSR = 0x01; MCUSR = 0x00;
      asm volatile ("jmp 0x00000\n\t" ::);
    }
  } 

  // BOOT LOADER BEGINS

  for (int x = 0; x < 3; x++)
  {
    PORTE |= 1<<3; PORTC |= 1;
    _delay_us(70000);
    PORTE &= ~(1<<3); PORTC &= 0xfe;
    _delay_us(100000);
  }
  PORTE |= 1<<3; PORTC |= 1;
  _delay_us(200000);
  PORTE &= ~(1<<3); PORTC &= 0xfe;

  lcd_init();
  lcd_puts_P(2*FW, 3*FH, PSTR("BOOTLOADER!"));
  refreshDisplay();

  while (1);
  return 0;
}


