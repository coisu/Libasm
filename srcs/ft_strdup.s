section .text
    global ft_strdup
    extern malloc
    extern ft_strlen
    extern ft_strcpy
    extern __errno_location

ft_strdup:
    test rdi, rdi               ; Check if input string is NULL
    jz .null_input              ; If NULL, set errno and return NULL

    push rdi                    ; Save input string (s1) on the stack
    call ft_strlen              ; Calculate the length of the string
    inc rax                     ; Add 1 for null terminator
    mov rdi, rax                ; Pass size to malloc
    call malloc                 ; Allocate memory
    test rax, rax               ; Check if malloc returned NULL
    jz .malloc_failed           ; Handle malloc failure

    mov rdi, rax                ; Set destination pointer
    pop rsi                     ; Restore source string
    call ft_strcpy              ; Copy the string
    ret                         ; Return the allocated memory pointer

.malloc_failed:
    neg rax                     ; Negate rax (errno from malloc is returned negatively)
    mov rdi, rax                ; Temporarily store errno in rdi
    call __errno_location       ; Get address of errno
    mov [rax], rdi              ; Set errno with the value in rdi
    mov rax, -1                 ; Set return value to -1
    ret                         ; Return rax

.null_input:
    mov rdi, 22                 ; Set errno to EINVAL (22)
    call __errno_location       ; Get address of errno
    mov [rax], rdi              ; Set errno with the value in rdi
    xor rax, rax                ; Return NULL
    ret                         ; Return rax

section .note.GNU-stack noalloc noexec nowrite progbits
