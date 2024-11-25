section .text
    global ft_write

ft_write:
    mov rax, 1            ; syscall number
    mov rdi, rdi          ; 파일 디스크립터 (첫 번째 인자)
    mov rsi, rsi          ; 버퍼 주소 (두 번째 인자)
    mov rdx, rdx          ; 출력할 데이터 길이 (세 번째 인자)
    syscall               ; 시스템 콜 실행
    ret                   ; 결과 반환



; syscall
; grep __NR_write /usr/include/asm-generic/unistd.h
;    #define __NR_write 64
;    __SYSCALL(__NR_write, sys_write)

; generic syscall definitions in the kernel source code (like in unistd.h) 
; are not directly applicable to how user-space programs interact 
; with the kernel through the syscall instruction. Instead, 
; the x86-64 architecture follows a specific ABI that maps system call numbers differently

; Look up for syscall table(x86_64, 64bit)
; 0 read
; 1 write
; 2 open
