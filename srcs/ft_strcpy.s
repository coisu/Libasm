section .text
    global ft_strcpy

ft_strcpy:
                        ; rdi = dest, rsi = src
    cld                 ; DF를 0으로 설정 (기본 증가 동작)  
    mov rax, rdi        ; rax에 dest 주소 저장 (반환값 준비)

.loop:
                        ; rdi, rsi 는 메모리 주소 저장, al은 그 주소에서 읽어온 실제 값을 저장하는 하위 8비트로(1바이트)저장
                        ; (char al) al == p (char *p)
    lodsb               ; al = *rsi, rsi++, 
                        ; 특별한 연산없이 rsi가 가리키는 메모리에서 1바이트 값을 읽어 al에 저장 한 수, rsi다음 값으로 자동 증가
    stosb               ; rdi[0] = p, sdi++,
                        ; al의 값을 rdi가 가리키는 위치에 저장하고 rdi 증가
    cmp al, 0           ; if al == '\0', set Zero Flag,
                        ; test doesn't change al value itself
    jne .loop           ; if not Zero Flag, loop

    ret                 ; rax(dest 주소) 반환

section .note.GNU-stack noalloc noexec nowrite progbits


; cmp al, 0 + jne .loop   	    if ZF unset(al != 0), loop.
; cmp al, 0 + jnz .loop         if ZF unset(al != 0), loop.
; test al, al + jnz .loop	    if ZF unset(al != 0), loop.
; test al, al + jne .loop = test al, al + jnz .loop