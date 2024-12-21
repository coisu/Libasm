section .text
    global ft_strcmp

ft_strcmp:
                            ; rdi = str1, rsi = str2
    cld
    xor rax, rax            ; initailize rax = 0

.loop:
    movzx rcx, byte [rdi]   ; Move with Zero-Extend"
                            ; unsigned char c = 0xF0;
                            ; uint64_t extended = (uint64_t)c;
    movzx rdx, byte [rsi]
    cmp rcx, rdx
    jne .diff
    
    test rcx, rcx
    je .end

    inc rdi
    inc rsi
    jmp .loop

.diff:
    sub rcx, rdx            ; rcx = rcx - rdx (ASCII)
    ;mov rax, rcx           ; return sub value, issue with -fsanitize=address

    test rcx, rcx
    jg .positive
    mov rax, -1
    ret

.positive:
    mov rax, 1               ; Set return value to 1
    ret

.end:
    xor rax, rax            ; if equal rax = 0
    ret



; movzx
; copy small value to bigger value, filled with '0'
; mov al, 0xF5              ; al = 11110101
; movzx rax, al             ; rax = 00000000_00000000_00000000_00000000_00000000_00000000_00000000_11110101 (64비트)

; movsx (Move with Sign-Extend):
; mov al, 0xF0         ; al = 11110000 (8, -16)
; movsx rax, al        ; rax = 0xFFFFFFFFFFFFFFF0 (64, -16)

; sub dest, cur        ; dest = str1, cur = str2
                       ; dest = dest* - cur*
                       ; result save in dest, 
; ZF val == 0
; SF val < SF
; OF overflow
