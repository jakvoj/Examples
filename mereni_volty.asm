;
; mereni volty.asm
;
; Created: 29.3.2020 16:31:51
; Author : jakub
;


; Replace with your application code
.include "./m328Pdef.inc"
.org 0x0000             
rjmp Reset
             
.org 0x002A ;preruseni vyvolano, kdyz je konvertovani hotove
rjmp ADC_int

Reset:     ;konfigurace
 ;ADC nastaveni
 lds r16, PRR
 andi r16, 0b11111110
 sts PRR, r16
 ldi r16, 0b01100000
 sts ADMUX,r16
 lds r16, DIDR0         
 ori r16, 0b00000001    
 sts DIDR0, r16
 ldi r16, 0b00000011
 sts EICRA, r16
 ldi r16, 0b00000000
 out EIMSK, r16
 ldi r16, 0b11101111 ;0b10101111
 sts ADCSRA, r16
 ldi r16, 0b00000010
 sts ADCSRB, r16       
 ;ADC nastaveni    
 sei                   
 ser r16
 out DDRB, r16
 clr r16

 Start: ;main loop
 
 rjmp Start ;main loop

ADC_int:	;cteni hodnoty napeti a vypis hodnoty na LED segmentovku
ldi r16, 0b00111111 ;default, 0V segment
lds r20, ADCH ;precteni vysledku konverze
subi r20, 51
brmi End
ldi r16, 0b00000110 ;1V segment
subi r20, 51
brmi End
ldi r16, 0b01011011 ;2V segment
subi r20, 51
brmi End
ldi r16, 0b01001111 ;3V segment
subi r20, 51
brmi End
ldi r16, 0b01100110 ;4V segment
subi r20, 44
brmi End
ldi r16, 0b01101101 ;5V segment, Max value - ref voltage for ADC 5 volts
End:
out PortB, r16
lds r16, ADCSRA
ori r16, 0b01000000 ;starting ADC again
sts ADCSRA, r16
reti


