section .text
    global ft_strcpy

ft_strcpy:
    mov rax, rdi             ; rax에 dest 주소 저장 (복사 시작 주소)
    xor rcx, rcx             ; i = 0으로 초기화

.loop:
    mov dh, byte [rsi + rcx] ; src[i]의 값을 dh에 저장
    mov byte [rdi + rcx], dh ; dh의 값을 dst[i]에 저장
    inc rcx                  ; i++
    test dh, dh              ; dh == '\0'인지 확인
    jnz .loop                ; 널이 아니면 루프 반복

    ret                      ; dest 주소 반환


; dh = independent 16bit register, used for store read value from the memory