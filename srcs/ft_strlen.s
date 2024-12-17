; ft_strlen.s

section .text
    global ft_strlen

ft_strlen:
    mov rax, 0                  ; Initialize length counter to 0 (rax will hold the result)

.loop:
    cmp byte [rdi + rax], 0     ; cmp rbx byte and 0 , Check if the current byte is NULL
    je .done                    ; if cmp = true jump to .done If NULL, jump to done
    inc rax                     ; rax++
    jmp .loop

.done:
    ret                         ; Return (rax already contains the length)

section .note.GNU-stack noalloc noexec nowrite progbits
