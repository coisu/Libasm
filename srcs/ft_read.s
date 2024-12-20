section .text
    global ft_read

ft_read:
    mov rax, 0
;   mov rdi, rdi
;   mov rsi, rsi
;   mov rdx, rdx
    syscall
    ret

