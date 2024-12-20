- [Automated Test](#automated-test)
- [Manual Test](#manual-test)
- [Challenges and Failures 1](#challenges-and-failures-1)
- [Callee-Saved Registers](#callee-saved-registers)
- [Challenges and Failures 2](#challenges-and-failures-2)
- [Assembly Basic - Register](#assembly-basic)
- [Tech Stack](#tech-stack)

# Libasm
Master the art of low-level programming by implementing standard C library functions in Assembly language. Dive deeper into performance optimization and gain a better understanding of how functions work at the machine level!

## Features
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



## Challenges and Failures 1
> Ensuring Register Safety in Assembly

When working with assembly, managing register values safely is a fundamental practice. Here's a summary of challenges and how to handle them effectively:

### The Challenge: Preserving Register Values
In assembly, registers are often used for temporary data storage during computations or function calls. However, failing to preserve register values can lead to unexpected behavior:

1. **Calling Convention Violations**:
   - Some registers, like `rbx`, `rbp`, and `r12~r15`, are **callee-saved** registers. According to the x86-64 calling convention, functions must restore these registers to their original values before returning.
   
2. **Data Loss**:
   - If a register's original value is overwritten without preservation, the program may encounter unpredictable errors when that value is accessed later.

3. **Nested Function Calls**:
   - A function that calls another function risks having its registers modified, leading to cascading failures if values are not restored properly.

---

### The Solution: Safe Register Management
To avoid these pitfalls, always save and restore registers when they are used temporarily. There are two primary methods:

#### 1. **Using `push` and `pop`**
Save the current value of a register on the stack and restore it after usage:
```asm
push rbx          ; Save the current value of rbx
mov rbx, rax      ; Use rbx for temporary storage
pop rbx           ; Restore the original value of rbx
```
#### 2. Using Stack Frames
Allocate space in the stack and store register values explicitly:
```asm
sub rsp, 8        ; Allocate 8 bytes on the stack
mov [rsp], rbx    ; Save rbx in the stack
mov rbx, rax      ; Use rbx for temporary storage
mov rbx, [rsp]    ; Restore the original value of rbx
add rsp, 8        ; Deallocate the stack space
```
---

### Consequences of Unsafe Practices
Failing to preserve registers can result in:

Corrupted Data: Overwritten register values can interfere with program logic.
Hard-to-Debug Errors: Unpredictable behavior makes debugging assembly code significantly more challenging.
Broken Functionality: Violating the calling convention can cause crashes or incorrect results in higher-level functions.

### Key Takeaway
To ensure safe and reliable assembly code:

Always follow the push-then-pop or stack frame methodology when using temporary registers.
Adhere to calling conventions to maintain the integrity of callee-saved registers.
Proactively manage register usage to prevent data conflicts and ensure robust program behavior.

---
---

## Callee-Saved Registers

### **Callee-Saved Registers: Overview**
> Callee-Saved registers are part of the calling convention used to preserve the state of specific registers across function calls. These registers must be saved and restored by the called function (Callee) if it intends to use them.

---

### **Key Features of Callee-Saved Registers**
#### **1. Preservation Obligation**
- The **Callee** must:
  - **Save** (push) the register values before using them.
  - **Restore** (pop) the original values before returning.

#### **2. Primary Purpose**
- Ensures that the **Caller**'s expected register states remain intact.
- Prevents data loss or corruption when the Callee modifies registers.

#### **3. Usage Pattern**
- **Save**: The Callee pushes register values onto the stack at the beginning of the function.
- **Restore**: The Callee pops the values from the stack before returning.

---

### **Callee-Saved Registers in x86-64**
According to the **System V AMD64 ABI**, the following registers are designated as Callee-Saved:

| **Register** | **Purpose**                         |
|--------------|-------------------------------------|
| `rbx`        | Temporary storage                  |
| `rsp`        | Stack pointer                      |
| `rbp`        | Base pointer (frame pointer)       |
| `r12`        | Temporary storage                  |
| `r13`        | Temporary storage                  |
| `r14`        | Temporary storage                  |
| `r15`        | Temporary storage                  |

---

### **Callee-Saved vs. Caller-Saved Registers**

| **Feature**             | **Callee-Saved**                | **Caller-Saved**                |
|--------------------------|----------------------------------|----------------------------------|
| **Preservation Responsibility** | Callee                        | Caller                        |
| **Examples**             | `rbx`, `rsp`, `rbp`, `r12-r15` | `rax`, `rcx`, `rdx`, `r8-r11`  |
| **Save Timing**          | Before Callee uses the register | Before Caller makes the call   |
| **Restore Timing**       | Before Callee returns           | After the function call        |

---

### **Advantages of Callee-Saved Registers**
#### **1. Simplified Design**
- The Caller does not need to save or restore these registers.
- The Callee focuses only on its own register usage.

#### **2. Efficient Use of Registers**
- Avoids repeated save/restore operations by the Caller at each function call site.
- Provides a reliable and consistent environment for function execution.

---

### **Conclusion**
Callee-Saved registers play a critical role in maintaining data integrity across function calls. By adhering to these conventions, programs with deep or complex call hierarchies can ensure stability and predictable behavior.







---
## Challenges and Failures 2

> Below is a summary of the issues encountered while implementing the `ft_strcpy` function in assembly, the reasons behind the failures, and the lessons learned from each experience.

#### Original Approach with `lodsb`, `stosb`, and `jne`
What was tried:
> I aimed to simplify memory operations by using `lodsb` to load bytes and `stosb` to store bytes, combined with conditional jumps (`jne`) for null termination checks.


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

### **Issues and Lessons Learned**

#### **Implicit Behavior of `lodsb` and `stosb`**
- The `lodsb` and `stosb` instructions implicitly modify the `rsi` and `rdi` registers by incrementing or decrementing them based on the direction flag (`DF`).
- While this implicit behavior worked fine in isolated tests, it caused conflicts when `ft_strcpy` was called within `ft_strdup`, as these registers needed to remain intact for correct memory operations.

#### **Direction Flag Dependency (`cld`)**
- The `cld` instruction was used to explicitly clear the direction flag (`DF`) to ensure forward memory traversal.
- However, if another function altered the `DF` before calling `ft_strcpy` and failed to reset it, the behavior of `lodsb` and `stosb` became unpredictable.
- This reliance on external factors made `ft_strcpy` fragile and context-dependent in broader programs.

#### **Reduced Debuggability**
- The implicit memory operations of `lodsb` and `stosb` made debugging more difficult, as changes to `rsi` and `rdi` were not directly visible.
- Errors in larger or nested contexts were harder to trace, making the debugging process inefficient and time-consuming.

#### **Register Modifications in Broader Contexts**
- The shared usage of `rsi` and `rdi` between `ft_strcpy` and `ft_strdup` led to unexpected side effects.
- The implicit changes caused by `lodsb` and `stosb` exacerbated these issues, resulting in incorrect copying behavior or memory corruption.

---

### **What I Learned:**  
> This approach, while elegant for small, isolated use cases, introduces implicit behavior that can conflict in larger, nested contexts. Understanding these limitations helped refine my future approaches to be more explicit and robust.

#### **Explicit Behavior is Key**
- Implicit register modifications, while convenient, can introduce hidden dependencies that conflict with other parts of the program.
- Explicitly managing registers and memory operations reduces the risk of unintended side effects and improves maintainability.

#### **Avoid Contextual Fragility**
- Functions should not rely on external conditions (e.g., the state of the direction flag) to operate correctly.
- By designing `ft_strcpy` to be self-contained and independent, it became more robust and reusable.

#### **Clarity Over Complexity**
- While advanced instructions like `lodsb` and `stosb` can simplify code in specific cases, they obscure the logic in more complex, nested scenarios.
- Using straightforward, explicit memory operations improved both readability and reliability.



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

1. **Explicit Control**  
   - Replaced `lodsb` and `stosb` with explicit `mov` instructions:  
     - `mov dh, byte [rsi + rcx]` for loading.  
     - `mov byte [rdi + rcx], dh` for storing.  
   - This ensures that `rsi` and `rdi` are not modified unintentionally.

2. **Removed Direction Flag Dependency**  
   - Eliminated the need for `cld` by using explicit address calculations (`rsi + rcx`, `rdi + rcx`).  
   - This makes the function independent of the direction flag, ensuring consistent behavior.

3. **Improved Debuggability**  
   - By explicitly showing all memory operations, the function becomes easier to debug and trace in case of errors.

4. **Register Isolation**  
   - The final code ensures that only `dh` is used for temporary storage, avoiding any modifications to critical registers like `rsi` or `rdi`.

---

### **Conclusion**

- The original code relied on implicit behavior (`lodsb` and `stosb`) and was dependent on the direction flag (`DF`), making it fragile and prone to bugs in nested contexts.  

- The final code resolves these issues by adopting explicit memory operations, removing direction flag dependency, and improving register isolation, resulting in a robust implementation suitable for broader use cases.


---


## Assembly Basic
# Assembly: Basic Knowledge on Registers

This document provides a beginner-friendly explanation of registers in assembly language, focusing on the x86-64 architecture. It includes an overview of register types, usage, and examples to help you get started.

---

### (1) **What Are Registers?**

Registers are high-speed storage areas within the CPU. They are used to perform arithmetic operations, store temporary data, and handle memory addresses. In x86-64 assembly, registers are named based on their roles and sizes.

---

### (2) **Register Types and Sizes**

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

### (3) **Categories of Registers**

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

### (4) **Basic Register Operations**

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

### (5) **Specialized String Operations**

For string manipulation, specific registers and instructions are used:

- rsi (source) and rdi (destination).
- rcx (counter for iterations).
- cld: Clears the direction flag to process memory forward.

  
##### Example
```asm
cld                 ; Clear direction flag
rep movsb           ; Copy bytes from [rsi] to [rdi]
```


### (6) **Function Call Example**

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

### (7) Common Use Cases

#### **Arithmetic and Logic**
- Use `rax` for calculations.
- Use `rdx` as a helper register.

#### **Memory Operations**
- Use `rdi` and `rsi` for source/destination.
- Use `rsp` for stack operations.

#### **Function Calls**
- Follow the calling convention (arguments in `rdi`, `rsi`, etc.).

---

### (8) Additional Tips

#### **Avoid overwriting important registers**
- Save registers with `push` before modifying and restore them with `pop`.

#### **Optimize for clarity**
- Use specific registers for their intended purposes (e.g., `rax` for results).

#### **Test with small programs**
- Practice writing and running assembly code with simple functions like addition or string copying.

---


### (9) x86-64 Jump Instructions Cheat Sheet

| **Instruction** | **Meaning**                           | **Condition**                                                  |
|------------------|---------------------------------------|----------------------------------------------------------------|
| `jmp`           | Unconditional jump                   | Always jumps to the specified address or label.               |
| `je` / `jz`     | Jump if equal / zero                 | ZF (Zero Flag) is set (e.g., result of comparison is zero).    |
| `jne` / `jnz`   | Jump if not equal / not zero         | ZF is clear (e.g., result of comparison is non-zero).          |
| `jg` / `jnle`   | Jump if greater                      | ZF is clear and SF == OF (signed comparison).                 |
| `jge` / `jnl`   | Jump if greater or equal             | SF == OF (signed comparison).                                 |
| `jl` / `jnge`   | Jump if less                        | SF != OF (signed comparison).                                 |
| `jle` / `jng`   | Jump if less or equal                | ZF is set or SF != OF (signed comparison).                    |
| `ja` / `jnbe`   | Jump if above                       | CF and ZF are clear (unsigned comparison).                    |
| `jae` / `jnc`   | Jump if above or equal               | CF is clear (unsigned comparison).                            |
| `jb` / `jnae`   | Jump if below                       | CF is set (unsigned comparison).                              |
| `jbe` / `jna`   | Jump if below or equal               | CF is set or ZF is set (unsigned comparison).                 |
| `jo`            | Jump if overflow                    | OF (Overflow Flag) is set.                                    |
| `jno`           | Jump if not overflow                | OF is clear.                                                  |
| `js`            | Jump if sign                        | SF (Sign Flag) is set.                                        |
| `jns`           | Jump if not sign                    | SF is clear.                                                  |
| `jp` / `jpe`    | Jump if parity even                 | PF (Parity Flag) is set (even number of 1 bits).              |
| `jnp` / `jpo`   | Jump if parity odd                  | PF is clear (odd number of 1 bits).                          |
| `jcxz`          | Jump if `rcx` is zero               | `rcx` is zero (used in loops).                                |
| `jecxz`         | Jump if `ecx` is zero               | `ecx` is zero (used in loops).                                |

## **Key Flag Descriptions**
- **ZF (Zero Flag)**: Set when the result of an operation is zero.
- **CF (Carry Flag)**: Set when an unsigned operation generates a carry/borrow.
- **SF (Sign Flag)**: Set when the result of an operation is negative.
- **OF (Overflow Flag)**: Set when a signed operation causes an overflow.
- **PF (Parity Flag)**: Set if the number of 1 bits in the result is even.

## **Examples**
```asm
cmp rax, rbx       ; Compare rax and rbx
je .equal          ; Jump to ".equal" if rax == rbx
jg .greater        ; Jump to ".greater" if rax > rbx (signed)
jb .below          ; Jump to ".below" if rax < rbx (unsigned)
jmp .unconditional ; Always jump to ".unconditional"
```
---


## Tech Stack
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
