include /masm32/include/masm32rt.inc

.data?
hInst           DWORD   ?

.code
SuperDuperEntryPoint proc hInstDLL:DWORD, reason:DWORD, lpvReserved:DWORD
    
    .if reason == DLL_PROCESS_ATTACH
      mov eax, TRUE

    .elseif reason == DLL_PROCESS_DETACH
      ; ---------------------------------------
      ; perform any exit code you require here
      ; ---------------------------------------

    .elseif reason == DLL_THREAD_ATTACH

    .elseif reason == DLL_THREAD_DETACH

    .endif

    ret 

    ret
SuperDuperEntryPoint endp

Init proc
    
    mov     eax, hInst
    ret

Init endp

;F := D xor (B and (C xor D))
FFunc proc	Bval: DWORD,
			Cval: DWORD,
			Dval: DWORD
	mov eax, Dval
	xor eax, Cval
	and eax, Bval
	xor eax, Dval
	ret
FFunc endp
;F := C xor (D and (B xor C))
GFunc proc	Bval: DWORD,
			Cval: DWORD,
			Dval: DWORD
	mov eax, Cval
	xor eax, Bval
	and eax, Dval
	xor eax, Cval
	ret
GFunc endp
;F := B xor C xor D
HFunc proc	Bval: DWORD,
			Cval: DWORD,
			Dval: DWORD	
	mov eax, Dval
	xor eax, Cval
	xor eax, Bval
	ret
HFunc endp
;F := C xor (B or (not D))
IFunc proc Bval: DWORD,
			Cval: DWORD,
			Dval: DWORD
	mov eax, Dval
	not eax
	or eax, Bval
	xor eax, Cval
	ret
IFunc endp
end SuperDuperEntryPoint
