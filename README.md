- [Automated Test](#automated-test)
- [Manual Test](#manual-test)
- [Assembly Basic - Register](#assembly-basic)
- [Challenges and Failures](challenges-and-failures)
- [Tech Stack](tech-stack)

Libasm
Master the art of low-level programming by implementing standard C library functions in Assembly language. Dive deeper into performance optimization and gain a better understanding of how functions work at the machine level!

# Features
- Implement core C library functions in x86-64 Assembly (e.g., `strlen`, `strcpy`, `strcmp`, `write`, `read`, `strdup`).
- Develop an optimized and minimalistic approach to function implementations.
- Experience the intricacies of working directly with registers and memory.

### Automated Testing (required) and Manual Testing
To ensure the reliability of your Assembly implementations, the project includes automated test suites:

- Automated Testing:
    - Compare the custom `ft_` functions with their standard counterparts (e.g., `strcmp` vs. `ft_strcmp`).
    - Detailed success/failure reporting for each test case.
    - Integrated into the Makefile with a `make test` rule for seamless testing.
- Manual Testing:
    - Additional command-line argument-based test binaries for interactive testing.
    - Located in the `manual_tests/` directory, allowing flexibility and edge case verification.

### GitLab CI Integration
This project is CI-ready with a configured GitLab CI pipeline:

- Ensures all functions pass rigorous automated tests on every commit.
- Validates compatibility and correctness across different environments.
- Keeps your code clean, reliable, and ready for deployment.

---


## 1. Usage
```
    clone git@github.com:coisu/Libasm.git
```
### 1-1 Automated Test
```
    make test
```
![image](https://github.com/user-attachments/assets/2ebed980-8302-4f8e-8278-1e4839f9883c)
![image](https://github.com/user-attachments/assets/7563d8b0-9960-44db-a4dc-98a7cf03340c)

### 1-2 Manual Test
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



## 2. Assembly Basic
# Assembly: Basic Knowledge on Registers

This document provides a beginner-friendly explanation of registers in assembly language, focusing on the x86-64 architecture. It includes an overview of register types, usage, and examples to help you get started.

---

### 2-1 **What Are Registers?**

Registers are high-speed storage areas within the CPU. They are used to perform arithmetic operations, store temporary data, and handle memory addresses. In x86-64 assembly, registers are named based on their roles and sizes.

---

### 2-2 **Register Types and Sizes**

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

### 2-3 **Categories of Registers**

#### a. General Purpose Registers
Used for arithmetic, data storage, and memory addressing.

| Register | Purpose                     | Description                          |
|----------|-----------------------------|--------------------------------------|
| `rax`    | Accumulator                 | Stores results, return values        |
| `rbx`    | Base Register               | General-purpose data storage         |
| `rcx`    | Counter Register            | Loop and shift instructions          |
| `rdx`    | Data Register               | Additional storage for operations    |

---

#### b. Pointer and Index Registers
Used for memory access and addressing.

| Register | Purpose                     | Description                          |
|----------|-----------------------------|--------------------------------------|
| `rdi`    | Destination Pointer         | Destination for string operations    |
| `rsi`    | Source Pointer              | Source for string operations         |
| `rsp`    | Stack Pointer               | Points to the top of the stack       |
| `rbp`    | Base Pointer                | Marks the base of the current stack frame |
| `rip`    | Instruction Pointer         | Points to the next instruction to execute |

---

#### c. Argument-Passing Registers
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

#### d. Flags Register
Stores the results of operations for conditional branching.

| Flag  | Description                           |
|-------|---------------------------------------|
| `ZF`  | Zero Flag: Set if the result is zero  |
| `SF`  | Sign Flag: Set if the result is negative |
| `CF`  | Carry Flag: Set if there’s a carry out of the most significant bit |
| `OF`  | Overflow Flag: Set if signed overflow occurs |

---

### 2-4 **Basic Register Operations**

#### Moving Data
```asm
mov rax, 5          ; Load 5 into rax
mov rbx, rax        ; Copy rax value to rbx
mov [rsp], rax      ; Store rax value in memory at rsp
mov rax, [rsp]      ; Load value from memory at rsp to rax
```
#### Arithmetic
```asm
add rax, rbx        ; Add rbx to rax
sub rax, 2          ; Subtract 2 from rax
mul rbx             ; Multiply rax by rbx
```
#### Conditional Branching
```asm
cmp rax, rbx        ; Compare rax and rbx
je equal_label      ; Jump if equal
jg greater_label    ; Jump if greater
```

### 2-5 **Specialized String Operations**

For string manipulation, specific registers and instructions are used:

- rsi (source) and rdi (destination).
- rcx (counter for iterations).
- cld: Clears the direction flag to process memory forward.

  
##### Example
```asm
cld                 ; Clear direction flag
rep movsb           ; Copy bytes from [rsi] to [rdi]
```


### 2-6 **Function Call Example**

#### C
```c
int add(int a, int b) {
    return a + b;
}
```

#### Assembly
```asm
mov rdi, 5          ; First argument a = 5
mov rsi, 3          ; Second argument b = 3
call add            ; Call the function
; Result is stored in rax
```

### 2-7 Common Use Cases

#### **Arithmetic and Logic**
- Use `rax` for calculations.
- Use `rdx` as a helper register.

#### **Memory Operations**
- Use `rdi` and `rsi` for source/destination.
- Use `rsp` for stack operations.

#### **Function Calls**
- Follow the calling convention (arguments in `rdi`, `rsi`, etc.).

---

### 2-8 Additional Tips

#### **Avoid overwriting important registers**
- Save registers with `push` before modifying and restore them with `pop`.

#### **Optimize for clarity**
- Use specific registers for their intended purposes (e.g., `rax` for results).

#### **Test with small programs**
- Practice writing and running assembly code with simple functions like addition or string copying.

---

### 2-9 Conclusion

Understanding registers is crucial for assembly programming. Familiarize yourself with their roles, calling conventions, and basic operations to write efficient and clear assembly code. Good luck 🎉




---





## 3. Challenges and Failures
While Implementing ft_strcpy
- Below is a summary of the issues encountered while implementing the ft_strcpy function in assembly, the reasons behind the failures, and the lessons learned from each experience.

### Original Code:
```asm
section .text
global ft_strcpy

ft_strcpy:
                        ; rdi = dest, rsi = src
    cld                 ; DF = 0 auto inc 1
    mov rax, rdi        ; rax = dest address

.loop:
                        ; rdi = rsi memory address, al = read value from the memory
    lodsb               ; al = *rsi, rsi++
    stosb               ; rdi[0] = p, rdi++
    cmp al, 0           ; if al == '\0', set Zero Flag
    jne .loop           ; if not null terminator, loop
    ret
```


---

### **Issues**

1. **Implicit Behavior of `lodsb` and `stosb`**:  
   - Both `lodsb` and `stosb` modify the `rsi` and `rdi` registers implicitly by incrementing or decrementing them depending on the direction flag (`DF`).  
   - While this might work in isolated tests, it introduces potential bugs when `ft_strcpy` is used in a context like `ft_strdup`, where the integrity of `rsi` and `rdi` needs to be preserved for proper memory operations.  

2. **Direction Flag Dependency (`cld`)**:  
   - The direction flag (`DF`) is explicitly cleared with `cld` at the start of the function to ensure forward memory traversal.  
   - If another function sets `DF` before calling `ft_strcpy` but does not reset it, the behavior of `lodsb` and `stosb` becomes unpredictable.  
   - This makes `ft_strcpy` context-dependent and fragile when integrated into a broader program.  

3. **Implicit Logic Reduces Debuggability**:  
   - Since `lodsb` and `stosb` hide the memory operations, debugging becomes challenging as the explicit state of `rsi` and `rdi` is not directly visible.  
   - This leads to errors that are harder to trace back to their source, particularly in larger or nested contexts.  

4. **Register Modifications in Broader Contexts**:  
   - When `ft_strcpy` is called inside `ft_strdup`, modifying `rsi` and `rdi` causes unexpected side effects because these registers are shared between the two functions.  
   - The implicit nature of `lodsb` and `stosb` exacerbates the problem, leading to incorrect copying behavior.  

---


### Final Code:
```asm
section .text
global ft_strcpy

ft_strcpy:
    mov rax, rdi
    xor rcx, rcx                ; i = 0

.loop:
    mov dh, byte [rsi + rcx]    ; dh = src[i]
    mov byte [rdi + rcx], dh
    inc rcx                     ; i++
    test dh, dh                 ; test dh == '\0'
    jnz .loop                   ; if not null, continue loop

    ret
```
---

### **Key Changes**

1. **Explicit Control**:  
   - Replaced `lodsb` and `stosb` with explicit `mov` instructions:  
     - `mov dh, byte [rsi + rcx]` for loading.  
     - `mov byte [rdi + rcx], dh` for storing.  
   - This ensures that `rsi` and `rdi` are not modified unintentionally.  

2. **Removed Direction Flag Dependency**:  
   - Eliminated the need for `cld` by using explicit address calculations (`rsi + rcx`, `rdi + rcx`).  
   - This makes the function independent of the direction flag, ensuring consistent behavior.  

3. **Improved Debuggability**:  
   - By explicitly showing all memory operations, the function becomes easier to debug and trace in case of errors.  

4. **Register Isolation**:  
   - The final code ensures that only `dh` is used for temporary storage, avoiding any modifications to critical registers like `rsi` or `rdi`.  

---

### **Conclusion**

- The original code relied on implicit behavior (`lodsb` and `stosb`) and was dependent on the direction flag (`DF`), making it fragile and prone to bugs in nested contexts.  

- The final code resolves these issues by adopting explicit memory operations, removing direction flag dependency, and improving register isolation, resulting in a robust implementation suitable for broader use cases.


---

## 4. Tech Stack
- Assembly:

    - x86-64 architecture for low-level implementation.
    - Focus on performance optimization and register-level programming.

- C

- Build Tools:

    - Make: Manage builds and compile Assembly code into executables.
    - NASM (Netwide Assembler): Assemble x86-64 Assembly source code into object files.

- Version Control:

    - Git: Track project progress and manage changes.
    - GitLab CI: Automate testing pipelines for consistent quality assurance.

- Testing:

    - Automated Testing: Validate implementations by comparing with standard functions.
    - Command-line Testing: Pass test cases as arguments for flexible and interactive validation.

- Unix/Linux Environment
