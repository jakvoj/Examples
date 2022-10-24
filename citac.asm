;
; citac segment.asm
;
; Created: 29.6.2022 16:31:51
; Author : jakub
;


; Replace with your application code
.include "./m328Pdef.inc"
.org 0x0000             
rjmp Reset

.org 0x000A ;Pin change interrupt request 2 - PCINT2 - zm�na stavu u pinu, plat� pro piny 16-23 
rjmp button_stopping
               
.org 0x0020              
rjmp overflow_handler

Reset: ;Konfigurace mikro�adi�e a perif�ri�    
 ldi r16,  0b00000101
 out TCCR0B, r16      
 ldi r16, 0b00000001
 sts TIMSK0, r16
 ldi r16, 0b00010000
 sts PCMSK2, r16 ;nastavuje piny(povoluje tedy p�eru�en� pin�) 16-23 - u n�s nastaven� pin PCINT20 - �ili PD4 podle datasheetu
 ldi r16, 0b00000100
 sts PCICR, r16 ;nastavili jsme bit PCIE2 - �ili mikro�adi� bude p�ij�mat p�eru�en� od pin� 16-23
 ldi r16, 0b11101111
 out DDRD, r16 ;PD4 pro direction register
 clr r16
 out PortD, r16     
 sei                   
 clr r16
 out TCNT0, r16
 ser r16
 out DDRB, r16
 clr r17
 ldi ZL, 0x01
 ldi ZH, 0x02

 Start: ;main loop
 rcall segment
 rcall delay
 rjmp Start ;main loop

 overflow_handler:
 inc r17
 reti

 delay:
 cpi r17, 61 ;zhruba 61 p�ete�en� ��ta�e za sekundu
  brne PC-1 ;podm�n�n� skok - sko�� na adresu v program counteru m�nus jedna
  clr r17
 ret

 button_stopping: ;pokud sepnut� tla��tko, tak pozastaven� ��ta�e
 ldi r23, 0b00010000
 ldi r22,  0b00000000
 out TCCR0B, r22
 continue_stop:
 in r20, PinD
 and r20, r23 ;maska pro neuzemn�n� vstupn� piny
 cpi r20, 0b00010000
 breq continue_stop
 end_stop:
 ldi r22,  0b00000101
 out TCCR0B, r22
 reti

 .org 0x0200
 segment: ;ovl�d�n� segment� pro v�pis ��sel
 ijmp
 ldi r16, 0b00111111 ;0 /dot, g, f, e, d, c, b, a
 rjmp end_segment
 ldi r16, 0b00000110 ;1
 rjmp end_segment
 ldi r16, 0b01011011 ;2
 rjmp end_segment
 ldi r16, 0b01001111 ;3
 rjmp end_segment
 ldi r16, 0b01100110 ;4
 rjmp end_segment
 ldi r16, 0b01101101 ;5
 rjmp end_segment
 ldi r16, 0b01111101 ;6
 rjmp end_segment
 ldi r16, 0b00000111 ;7
 rjmp end_segment
 ldi r16, 0b01111111 ;8
 rjmp end_segment
 ldi r16, 0b01101111 ;9
 ldi ZL, 0x01
 rjmp complete_cyclus
 end_segment:
 adiw Z, 2
 complete_cyclus:
 out PortB, r16
 ret


