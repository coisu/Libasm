section .text
    global ft_strdup
    extern malloc
    extern ft_strlen
    extern ft_strcpy
    extern __errno_location

; rdi 1st, rsi 2nd
ft_strdup:
    push rbx

    test rdi, rdi               ; NULL input
    jz .null_input

    mov rbx, rdi                ; rbx = source str
    call ft_strlen
    inc rax                     ; for \0

    mov rdi, rax
    call malloc WRT ..plt
    test rax, rax
    jz .malloc_failed

    cld                         ; Clear direction flag for string operations
    mov rdi, rax
    mov rsi, rbx
    call ft_strcpy

    pop rbx
    ret

.malloc_failed:
    call __errno_location WRT ..plt
    mov qword [rax], 12             ; ENOMEM (12), dword for constant value(immediate value)
                                    ; no need dword between registers
    xor rax, rax                    ; NULL
    pop rbx
    ret

.null_input:
    xor rax, rax                ; Return NULL
    pop rbx
    ret

; byte   8 bits
; word  16 bits
; dword 32 bits
; qword 64 bits