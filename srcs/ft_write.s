section .text
    global ft_write
    extern __errno_location

ft_write:
    mov rax, 1            ; syscall number
    syscall
	cmp		rax, 0
	jl		.error
	ret

.error:
    push    rbx
    mov     rbx, rax
    call    __errno_location WRT ..plt
    neg     rbx
    mov     [rax], rbx
    mov     rax, -1
    pop     rbx
    ret


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
