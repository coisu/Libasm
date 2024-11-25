
# Syscall Table for x86-64 Linux

This file provides a reference table for system call numbers, their names, descriptions, and registers used. It is based on the x86-64 architecture for the Linux operating system.

| Syscall Number | Name         | Description                                        | Registers Used        |
|----------------|--------------|----------------------------------------------------|-----------------------|
| 0              | `read`       | Reads data from a file descriptor                  | `rax`, `rdi`, `rsi`, `rdx` |
| 1              | `write`      | Writes data to a file descriptor                   | `rax`, `rdi`, `rsi`, `rdx` |
| 2              | `open`       | Opens a file                                       | `rax`, `rdi`, `rsi`, `rdx` |
| 3              | `close`      | Closes a file descriptor                           | `rax`, `rdi`          |
| 60             | `exit`       | Exits a process                                    | `rax`, `rdi`          |
| 5              | `fstat`      | Gets file metadata                                | `rax`, `rdi`, `rsi`   |
| 57             | `fork`       | Creates a new process by duplicating the current process | `rax`          |
| 63             | `uname`      | Gets system information                           | `rax`, `rsi`          |
| 39             | `getpid`     | Gets the process ID of the calling process         | `rax`                |
| 41             | `socket`     | Creates a new socket                              | `rax`, `rdi`, `rsi`, `rdx` |
| 42             | `connect`    | Connects a socket to a remote host                | `rax`, `rdi`, `rsi`, `rdx` |
| 43             | `accept`     | Accepts a connection on a socket                  | `rax`, `rdi`, `rsi`, `rdx` |
| 61             | `wait4`      | Waits for a process to change state               | `rax`, `rdi`, `rsi`, `rdx` |
| 78             | `mkdir`      | Creates a new directory                           | `rax`, `rdi`, `rsi`   |
| 80             | `chdir`      | Changes the current working directory             | `rax`, `rdi`          |
| 257            | `openat`     | Opens a file relative to a directory file descriptor | `rax`, `rdi`, `rsi`, `rdx` |

### Notes:
- **`rax`**: Register used to store the syscall number.
- **`rdi`, `rsi`, `rdx`**: Registers used for passing arguments (e.g., file descriptors, buffers).
- **`syscall` Numbers**: Follow the x86-64 architecture conventions.

## Example Usage of `write`

Here is an example of using the `write` syscall in assembly:

```asm
section .data
    msg db "Hello, Extended Syscall Table!", 0xA

section .text
    global _start

_start:
    mov rax, 1          ; syscall number for write
    mov rdi, 1          ; file descriptor (stdout)
    lea rsi, [msg]      ; address of the message
    mov rdx, 32         ; length of the message
    syscall             ; invoke syscall

    mov rax, 60         ; syscall number for exit
    xor rdi, rdi        ; exit code 0
    syscall
```

### References:
- [Linux man pages](https://man7.org/linux/man-pages/)
- [Linux Syscall Reference](https://syscalls.w3challs.com/)
