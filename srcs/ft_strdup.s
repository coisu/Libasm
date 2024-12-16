section .text
    global ft_strdup
    extern ft_strlen
    extern ft_strcpy
    extern malloc
    extern errno_location

; char *ft_strdup(const char *s1);
; s1 == rdi
ft_strdup:
    test  rdi, rdi          ; Check if input string is NULL
    jz    .null_input       ; If NULL, return NULL

    push  rdi               ; Save input string (s1) on the stack
    call  ft_strlen         ; Calculate the length of the string
    inc   rax               ; Add 1 for the null terminator
    mov   rdi, rax          ; Pass size to malloc
    call  [rel malloc]      ; Use RIP-relative addressing to call malloc
    test  rax, rax          ; Check if malloc returned NULL
    jz    .malloc_failed    ; If NULL, handle malloc failure

    mov   rdi, rax          ; Set destination pointer (malloc result)
    pop   rsi               ; Restore source string (s1)
    call  ft_strcpy         ; Copy the string
    ret                     ; Return the allocated memory pointer

.malloc_failed:
    call  [rel errno_location] ; Get the address of errno
    mov   rdi, rax          ; Load errno address into rdi
    mov   dword [rdi], 12   ; Set errno = ENOMEM (12)
    xor   rax, rax          ; Return NULL
    ret

.null_input:
    call  [rel errno_location] ; Get the address of errno
    mov   rdi, rax          ; Load errno address into rdi
    mov   dword [rdi], 22   ; Set errno = EINVAL (22)
    xor   rax, rax          ; Return NULL
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
