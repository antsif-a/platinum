; vim: set filetype=fasm :
format ELF64

public _start

; int _start_cpp(int argc, char * argv[], char * envp[])
extrn _start_cpp

section '.text' executable
_start:
    pop  rdi                      ; argc
    mov  rsi, rsp                 ; argv[]
    lea  rdx, [rsp + 8 * rdi + 8] ; envp[]
    call _start_cpp

    mov rdi, rax
    mov rax, 60
    syscall
