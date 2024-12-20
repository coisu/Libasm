section .text
    global ft_read
    extern __errno_location

ft_read:
    mov rax, 0
    syscall
    cmp rax, 0
	jl .error
	ret

.error:
	push rbx
	mov rbx, rax
	neg rbx
	call __errno_location WRT ..plt
	mov [rax], rbx
	mov rax, -1
	pop rbx
	ret