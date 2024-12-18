## Usage
```
    clone git@github.com:coisu/Libasm.git
```
### Automated Test
```
    make test
```
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





Key Concepts for Assembly
Registers:

CPU has a set of registers to perform operations. Common ones for x86-64:
rax, rbx, rcx, rdx, etc. (general-purpose registers)
rdi, rsi, rdx, rcx, etc. (used for passing function arguments)
Function arguments:
rdi → 1st argument
rsi → 2nd argument
rdx → 3rd argument
(Followed by rcx, r8, r9…)
Calling Convention:

In Linux, x86-64 follows the System V ABI:
Function arguments are passed in rdi, rsi, etc.
Return values are placed in rax.
Basic Assembly Instructions:

mov → Move data from one place to another.
cmp → Compare two values.
je, jne → Jump if equal, not equal.
inc → Increment a value.
ret → Return from a function.
String Operations:

Strings in assembly are arrays of bytes ending with a NULL byte (0x00).


