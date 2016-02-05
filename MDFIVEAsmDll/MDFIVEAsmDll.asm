include /masm32/include/masm32rt.inc
.xmm
.data?
hInst           DWORD   ?
.data 
shifts  db  7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22 ;0-15
	    db  5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20 ; 16-31
	    db  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23 ; 32-47
	    db  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 ;48- 63
sines   DWORD  0d76aa478h, 0e8c7b756h, 0242070dbh, 0c1bdceeeh ;0-3
		DWORD	0f57c0fafh, 04787c62ah, 0a8304613h, 0fd469501h ;4-7
		DWORD	0698098d8h, 08b44f7afh, 0ffff5bb1h, 0895cd7beh ;8-11
		DWORD	06b901122h, 0fd987193h, 0a679438eh, 049b40821h ;12-15
		DWORD	0f61e2562h, 0c040b340h, 0265e5a51h, 0e9b6c7aah ;16-19
		DWORD	0d62f105dh, 002441453h, 0d8a1e681h, 0e7d3fbc8h ;20-23
		DWORD	021e1cde6h, 0c33707d6h, 0f4d50d87h, 0455a14edh ;24-27
		DWORD	0a9e3e905h, 0fcefa3f8h, 0676f02d9h, 08d2a4c8ah ;28-31
		DWORD	0fffa3942h, 08771f681h, 06d9d6122h, 0fde5380ch ;32-35
		DWORD	0a4beea44h, 04bdecfa9h, 0f6bb4b60h, 0bebfbc70h ;36-39
		DWORD	0289b7ec6h, 0eaa127fah, 0d4ef3085h, 004881d05h ;40-43
		DWORD	0d9d4d039h, 0e6db99e5h, 01fa27cf8h, 0c4ac5665h ;44-47
		DWORD	0f4292244h, 0432aff97h, 0ab9423a7h, 0fc93a039h ;48-51
		DWORD	0655b59c3h, 08f0ccc92h, 0ffeff47dh, 085845dd1h ;52-55
		DWORD	06fa87e4fh, 0fe2ce6e0h, 0a3014314h, 04e0811a1h ;56-59
		DWORD	0f7537e82h, 0bd3af235h, 02ad7d2bbh, 0eb86d391h  ;60-63
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
UpdateHash proc current: PTR DWORD,
				results: PTR DWORD
	mov eax, results
	movups xmm1,[eax]
	mov eax, current
	movups xmm0,[eax]
	paddb xmm0,xmm1
	movups [eax],xmm0
	ret
UpdateHash endp	
end SuperDuperEntryPoint
