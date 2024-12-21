section .text
    global ft_strcpy

; rdi 1st, rsi 2nd
ft_strcpy:
    push rbx
    mov rax, rdi                ; save dest address into rax
    xor rcx, rcx                ; i = 0

.loop:
    mov bl, byte [rsi + rcx]
    mov byte [rdi + rcx], bl    ; bl(rbx) = rsi[i], byte(8bits) bl(8bits)
    inc rcx
    test bl, bl
    jnz .loop

    pop rbx
    ret

; rbx register, and sub register
; rbx	64 bits
; ebx	32 bits	lower 32 bits
; bx	16 bits	lower 16 bits
; bl	8 bits	lower 8 bits
; bh	8 bits	upper 8 bits (upper among 16 bits)

; byte   8 bits
; word  16 bits
; dword 32 bits
; qword 64 bits

; mov rbx, byte [rsi + rcx] => 'error: mismatch in operand sizes'
; rbx(64), byte(8)
; 1. movzx rbx, byte [rsi + rcx] : movzx (Move with Zero-Extend)
; 2. mov bl, byte [rsi + rcx]