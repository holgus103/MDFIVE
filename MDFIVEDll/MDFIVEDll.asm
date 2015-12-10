include /masm32/include/masm32rt.inc

.data
szLoading       BYTE    "Dll is loading", 0
szUnloading     BYTE    "Dll is un-loading", 0
szOrdinal       BYTE    "Look ma, I was called by ordinal!", 0

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

TestProc1 proc lpString:DWORD
    
    invoke  MessageBox, NULL, lpString, NULL, NULL
    ret

TestProc1 endp

ProcByOrdinal proc
    invoke  MessageBox, NULL, offset szOrdinal, NULL, NULL
    ret
ProcByOrdinal endp
end SuperDuperEntryPoint
