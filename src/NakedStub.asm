.CODE
EXTERN ProcessPacketLogic : PROC

; This tells the assembler that originalQueuePacket is a QWORD pointer
; defined in another file (our C++ file).
EXTERN originalQueuePacket : QWORD

hookQueuePacket_Naked PROC
    ; --- Prologue: Save the original state ---
    ; This part is correct and preserves the registers.
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    sub rsp, 28h

    ; --- Call our C++ Logic ---
    call ProcessPacketLogic

    ; --- Epilogue: Restore the original state ---
    add rsp, 28h
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; --- Jump to the original game function ---
    ; This is the corrected instruction. It tells the assembler
    ; to treat originalQueuePacket as a memory location and to
    ; jump to the 64-bit address stored AT that location.
    jmp qword ptr [originalQueuePacket]

hookQueuePacket_Naked ENDP

END