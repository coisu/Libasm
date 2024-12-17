section .text
    global ft_strdup
    extern malloc
    extern ft_strlen
    extern ft_strcpy

ft_strdup:
    test rdi, rdi               ; Check if input string is NULL
    jz .null_input              ; Handle NULL input

    push rdi                    ; Save input string (s1) on the stack
    call ft_strlen              ; Calculate the length of the string
    inc rax                     ; Add 1 for null terminator
    mov rdi, rax                ; Pass size to malloc
    call malloc                 ; Allocate memory
    test rax, rax               ; Check if malloc returned NULL
    jz .malloc_failed           ; Handle malloc failure

    cld
    mov rdi, rax                ; Set destination pointer
    pop rsi                     ; Restore source string
    call ft_strcpy                 ; Copy the string
    ret                         ; Return the allocated memory pointer

.malloc_failed:
    xor rax, rax                ; Return NULL
    ret

.null_input:
    xor rax, rax                ; Return NULL
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
