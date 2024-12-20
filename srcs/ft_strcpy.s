section .text
    global ft_strcpy

ft_strcpy:
    mov rax, rdi                ; save dest address into rax
    xor rcx, rcx                ; i = 0

.loop:
    mov dh, byte [rsi + rcx]    ; dh = src[i]
    mov byte [rdi + rcx], dh    ; dst[i] = dh
    inc rcx
    test dh, dh                 ; test dh == '\0'
    jnz .loop                   ; if not null

    ret                         ; dest address return


; dh = independent 16bit register, used for store read value from the memory