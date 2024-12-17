; ft_strlen.s

section .text
    global ft_strlen          ; 외부에서 호출 가능하도록 ft_strlen을 글로벌 심볼로 설정

ft_strlen:
    mov rax, 0                  ; 레지스터 반환값(문자열 길이) 초기화 Initialize length counter to 0 (rax will hold the result)

.loop:                          ; 루프 시작점
    cmp byte [rdi + rax], 0     ; rbx바이트와 0(문자열끝, \0) 비교, Check if the current byte is NULL
    je .done                    ; 조건부점프, 만약 cmp참 이면 .done으로 점프 If NULL, jump to done
    inc rax                     ; rax값 1증가 Otherwise, increment the length counter
    jmp .loop                   ; .loop로 점프 Repeat the loop

.done:
    ret                         ; Return (rax already contains the length)


section .note.GNU-stack noalloc noexec nowrite progbits
