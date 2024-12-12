section .text
    global ft_strdup

    extern ft_strlen
    extern ft_strcpy        ; External strcpy function
    extern errno_location   ; to get error pointer

ft_strdup:
                            ; char *strdup(const char *s)
                            ; rdi: const char *s
    test rdi, rdi           ; Check if s is NULL
    jz .set_errno_null      ; If NULL, set errno and return NUL

    push rdi                ; Save s on the stack
    call ft_strlen
    mov rdx, rax            ; rax = ft_strlen(s)

; Call mmap to allocate memory
    mov rdi, 0              ; addr = NULL (let the system choose the address)
    mov rsi, rdx            ; length = rdx (strlen(s) + 1)
    mov rdx, 0x3            ; prot = PROT_READ | PROT_WRITE
    mov r10, 0x22           ; flags = MAP_PRIVATE | MAP_ANONYMOUS
    mov r8, -1              ; fd = -1 (not backed by a file)
    mov r9, 0               ; offset = 0
    mov rax, 9              ; syscall number for mmap
    syscall                 ; Perform syscall

    test rax, rax           ; Check if malloc failed
    jz .set_errno_nomem

    pop rsi                 ; Restore s from the stack
    mov rdi, rax
    call ft_strcpy          ; strcpy(rdi, rsi)

    ret

.set_errno_null:
    call errno_location    ; Get the address of errno
    mov rdi, rax           ; rdi = EINVAL (22)
    mov dword [rdi], 22
    xor rax, rax
    ret

.set_errno_nomem:
    call errno_location
    mov rdi, rax           ; rdi = ENOMEM (12)
    mov dword [rdi], 12
    xor rax, rax
    ret


mmap 호출을 통한 메모리 할당
1. mmap란?
mmap은 운영체제의 시스템 호출로, 프로세스의 가상 메모리 공간에 메모리를 매핑하거나 할당하는 데 사용됩니다.
이 호출을 통해 파일 기반 매핑이나 익명 메모리(파일과 연결되지 않은 메모리) 할당이 가능합니다.
이 코드는 익명 메모리를 동적으로 할당하는 데 사용됩니다.
2. 각 레지스터의 역할
mmap 호출에서 각 레지스터는 다음과 같은 매개변수를 전달합니다:

rdi (addr):

0으로 설정하면, 운영체제가 적절한 메모리 주소를 자동으로 선택하도록 합니다.
수동으로 특정 주소를 지정하려면 해당 주소를 넣으면 됩니다.
rsi (length):

할당할 메모리의 크기(바이트 단위)를 설정합니다.
여기서는 rdx에 저장된 값, 즉 문자열 길이(strlen) + 1(NULL 문자 포함)을 전달합니다.
rdx (prot):

메모리 보호 속성을 지정합니다.
0x1 (PROT_READ): 읽기 권한.
0x2 (PROT_WRITE): 쓰기 권한.
여기서는 0x3 (PROT_READ | PROT_WRITE)로, 읽기와 쓰기 모두 가능한 메모리를 요청합니다.
r10 (flags):

매핑 플래그를 설정합니다:
MAP_PRIVATE (0x2): 메모리는 프로세스 내에서만 사용됩니다. 변경 내용은 다른 프로세스와 공유되지 않습니다.
MAP_ANONYMOUS (0x20): 메모리가 파일에 연결되지 않으며, 익명 메모리를 할당합니다.
여기서는 0x22 (MAP_PRIVATE | MAP_ANONYMOUS)로 설정됩니다.
r8 (fd):

파일 디스크립터를 지정합니다.
익명 메모리 매핑(MAP_ANONYMOUS)일 경우, 파일이 없으므로 -1로 설정합니다.
r9 (offset):

매핑 시작 지점을 설정합니다.
익명 메모리 매핑에서는 사용되지 않으므로 0으로 설정합니다.
rax (syscall 번호):

시스템 호출 번호를 설정합니다.
x86-64 Linux에서 mmap의 시스템 호출 번호는 9입니다.
syscall:

시스템 호출을 실행합니다.
실행 후 결과는 rax에 저장됩니다. 성공하면 할당된 메모리의 주소를 반환하고, 실패하면 음수 값이 반환됩니다.
3. 예제 코드의 동작 흐름
addr = 0:

메모리 주소를 운영체제가 선택하도록 요청합니다.
length = strlen(s) + 1:

문자열 길이와 NULL 문자를 포함한 총 메모리 크기를 요청합니다.
prot = PROT_READ | PROT_WRITE:

읽기와 쓰기 권한이 있는 메모리를 요청합니다.
flags = MAP_PRIVATE | MAP_ANONYMOUS:

메모리는 프로세스 내에서만 사용되며, 파일과 연결되지 않은 익명 메모리입니다.
fd = -1, offset = 0:

익명 매핑이므로 파일 디스크립터와 오프셋 값은 무시됩니다.
syscall 실행:

mmap 호출이 실행되며, 성공 시 반환된 메모리 주소는 rax에 저장됩니다.
실패 시 rax에는 음수 값이 저장되며, 적절히 에러 처리를 해야 합니다.
4. 코드 결과
성공 시: 메모리가 정상적으로 할당되고 rax에 시작 주소가 반환됩니다.
실패 시: 음수 값이 반환되며, errno를 통해 오류 원인을 확인해야 합니다.
