;12MHz
;1ms - 12Mhz/1000 = 12 000
;65 536 = 0xffff
;65536-12000=53536  0xd120 
;65536-60000=5536	0x15a0  

;T0L         EQU 0x8A      ; Mlodszy bajt rejestru T0
;T0H         EQU 0x8C      ; Starszy bajt rejestru T0

; Program glówny
ljmp start
ORG 0100h
	
end_t0:
	setb p1.0
	clr TR0
	ret
	
end_t1:
	setb p1.1
	clr TR1
	ret
	
start:
	mov p1, #0
	
    MOV TMOD, #00010001b 	; pierwsze 4b odnosza sie do T0, kolejne do T1 - ustawienie obu T w tryb timera 16b
;	MOV TH0, #0d1h			; ustawienie wartosci ktore spowoduja przepelnienie po 1ms
;	MOV TL0, #20h
;	MOV TH1, #15h			; ustawienie wartosci ktore spowoduja przepelnienie po 5ms
;	MOV TL1, #0a0h
 	mov TH0, #0ffh			; testowe odliczenie 16 cykli
 	mov TL0, #0f0h
	mov TH1, #0ffh			; testowe odliczenie 32 cykli
 	mov TL1, #0e0h
		
    SETB TR0            	; Wlacz timer T0
	setb TR1				; Wlacz timer T1
	
	loop:
		jnb TR0, cont_t0
		jnb TF0, cont_t0		; jesli timer przekroczy wartosc to wykonaj skok
		acall end_t0
		cont_t0:
		jnb TR1, cont_t1
		jnb TF1, cont_t1		; jesli timer przekroczy wartosc to wykonaj skok
		acall end_t1
		cont_t1:
		
		mov c, TF0				; zakoncz petle gdy oba liczniki odlicza zadane czasy
		anl c, TF1
		jnc loop
		
	nop
	jmp $
END start