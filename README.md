- [Automated Test](#automated-test)
- [Manual Test](#manual-test)
- [Assembly Basic - Register](#assemblt-basic)


## Usage
```
    clone git@github.com:coisu/Libasm.git
```
### Automated Test
```
    make test
```
![image](https://github.com/user-attachments/assets/2ebed980-8302-4f8e-8278-1e4839f9883c)
![image](https://github.com/user-attachments/assets/7563d8b0-9960-44db-a4dc-98a7cf03340c)

### Manual Test
```
    make manual
```
```
    ./manual_tests/ft_read [file to read]
    ./manual_tests/ft_write [string 1] 
    ./manual_tests/ft_strcmp [string 1] [string 2]
    ./manual_tests/ft_strcpy [string 1]
    ./manual_tests/ft_strlen [string 1]
    ./manual_tests/ft_strdup [string 1]
```
![image](https://github.com/user-attachments/assets/f4b0d86c-419c-4042-a333-a8e7fb1e8ee9)



## Assembly Basic
# Assembly: Basic Knowledge on Registers

This document provides a beginner-friendly explanation of registers in assembly language, focusing on the x86-64 architecture. It includes an overview of register types, usage, and examples to help you get started.

---

## 1. **What Are Registers?**

Registers are high-speed storage areas within the CPU. They are used to perform arithmetic operations, store temporary data, and handle memory addresses. In x86-64 assembly, registers are named based on their roles and sizes.

---

## 2. **Register Types and Sizes**

Each register can be accessed in different sizes:
- **64-bit registers**: `rax`, `rbx`, `rcx`, etc. (full 64-bit usage)
- **32-bit registers**: `eax`, `ebx`, `ecx`, etc. (lower 32 bits of the 64-bit register)
- **16-bit registers**: `ax`, `bx`, `cx`, etc. (lower 16 bits of the 64-bit register)
- **8-bit registers**: `al`, `ah` (lower 8 bits or higher 8 bits of the lower 16 bits)

For example:
- `rax` → Full 64-bit register.
- `eax` → Lower 32 bits of `rax`.
- `ax` → Lower 16 bits of `rax`.
- `al` → Lower 8 bits of `rax`.
- `ah` → Upper 8 bits of `ax`.

---

## 3. **Categories of Registers**

### a. General Purpose Registers
Used for arithmetic, data storage, and memory addressing.

| Register | Purpose                     | Description                          |
|----------|-----------------------------|--------------------------------------|
| `rax`    | Accumulator                 | Stores results, return values        |
| `rbx`    | Base Register               | General-purpose data storage         |
| `rcx`    | Counter Register            | Loop and shift instructions          |
| `rdx`    | Data Register               | Additional storage for operations    |

---

### b. Pointer and Index Registers
Used for memory access and addressing.

| Register | Purpose                     | Description                          |
|----------|-----------------------------|--------------------------------------|
| `rdi`    | Destination Pointer         | Destination for string operations    |
| `rsi`    | Source Pointer              | Source for string operations         |
| `rsp`    | Stack Pointer               | Points to the top of the stack       |
| `rbp`    | Base Pointer                | Marks the base of the current stack frame |
| `rip`    | Instruction Pointer         | Points to the next instruction to execute |

---

### c. Argument-Passing Registers
In x86-64 System V calling convention, these registers pass function arguments.

| Register | Argument Number             |
|----------|-----------------------------|
| `rdi`    | 1st                         |
| `rsi`    | 2nd                         |
| `rdx`    | 3rd                         |
| `rcx`    | 4th                         |
| `r8`     | 5th                         |
| `r9`     | 6th                         |

---

### d. Flags Register
Stores the results of operations for conditional branching.

| Flag  | Description                           |
|-------|---------------------------------------|
| `ZF`  | Zero Flag: Set if the result is zero  |
| `SF`  | Sign Flag: Set if the result is negative |
| `CF`  | Carry Flag: Set if there’s a carry out of the most significant bit |
| `OF`  | Overflow Flag: Set if signed overflow occurs |

---

## 4. **Basic Register Operations**

### Moving Data
```asm
mov rax, 5          ; Load 5 into rax
mov rbx, rax        ; Copy rax value to rbx
mov [rsp], rax      ; Store rax value in memory at rsp
mov rax, [rsp]      ; Load value from memory at rsp to rax
```
### Arithmetic
```
add rax, rbx        ; Add rbx to rax
sub rax, 2          ; Subtract 2 from rax
mul rbx             ; Multiply rax by rbx
```
### Conditional Branching
```
cmp rax, rbx        ; Compare rax and rbx
je equal_label      ; Jump if equal
jg greater_label    ; Jump if greater
```

## 5. **Specialized String Operations**

For string manipulation, specific registers and instructions are used:

- rsi (source) and rdi (destination).
- rcx (counter for iterations).
- cld: Clears the direction flag to process memory forward.

  
#### Example
```
cld                 ; Clear direction flag
rep movsb           ; Copy bytes from [rsi] to [rdi]
```


## 6. **Function Call Example**

### C
```
int add(int a, int b) {
    return a + b;
}
```

### Assembly
```
mov rdi, 5          ; First argument a = 5
mov rsi, 3          ; Second argument b = 3
call add            ; Call the function
; Result is stored in rax
```

## 7. Common Use Cases

### **Arithmetic and Logic**
- Use `rax` for calculations.
- Use `rdx` as a helper register.

### **Memory Operations**
- Use `rdi` and `rsi` for source/destination.
- Use `rsp` for stack operations.

### **Function Calls**
- Follow the calling convention (arguments in `rdi`, `rsi`, etc.).

---

## 8. Additional Tips

### **Avoid overwriting important registers**
- Save registers with `push` before modifying and restore them with `pop`.

### **Optimize for clarity**
- Use specific registers for their intended purposes (e.g., `rax` for results).

### **Test with small programs**
- Practice writing and running assembly code with simple functions like addition or string copying.

---

## 9. Conclusion

Understanding registers is crucial for assembly programming. Familiarize yourself with their roles, calling conventions, and basic operations to write efficient and clear assembly code. Good luck 🎉




