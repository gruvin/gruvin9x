#include "avr/io.h"

      .text

      .extern _Z25simplec_frskyRxParser_putc
      .globl _G_USART0_RX_vect

_G_USART0_RX_vect:
      ;; We're told that r18-r27 are free to use without interfering with compiler generated code
;      lds     r18 ,UCSR0B   ; disable RX int
;      andi    r18, 0x7f
;      sts     UCSR0B, r18
;      sei                  ; enable global ints

      push    r1
      push    r0
      in      r0, _SFR_IO_ADDR(SREG)
      push    r0
      in      r0, _SFR_IO_ADDR(RAMPZ)
      push    r0
      eor     r1, r1 ; reset flags
      push    r25
      push    r24

      lds     r24, UDR0
      ;  char data = UDR0;  // USART0 received byte register

;  // Ignore this byte if (frame | overrun | partiy) error
;  if ((UCSR0A & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))) == 0)

   ;  frskyRxParser.put(data);
      ldi     r25, 0
      call    _Z25simplec_frskyRxParser_putc

;//  UCSR0B |= (1 << RXCIE0); // enable (ONLY) USART RX interrupt
        
      pop     r24
      pop     r25
      pop     r0
      out     _SFR_IO_ADDR(RAMPZ), r0
      pop     r0
      out     _SFR_IO_ADDR(SREG), r0
      pop     r0
      pop     r1

;      cli
;      lds     r18, UCSR0B   ; enable RX int
;      ori     r18, 0x80
;      sts     UCSR0B, r18

      ;;      sei ;; done automatically by reti
      reti

      .end
