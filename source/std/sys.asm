; vim: set filetype=fasm :
format ELF64

;public sys_read
;public sys_write
public sys_mmap
public sys_mprotect
public sys_munmap
public sys_exit

;section '.text.sys_read' executable
; ssize_t sys_read(unsigned int fd, char *buf, size_t count)
;sys_read:
;    mov rax, 0
;    syscall
;    ret

;section '.text.sys_write' executable
; ssize_t sys_write(unsigned int fd, const char *buf, size_t count)
;sys_write: 
;    mov rax, 1
;    syscall
;    ret

section '.text.sys_mmap' executable
; void * sys_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
sys_mmap:
    mov rax, 9
    mov r10, rcx
    syscall
    ret


section '.text.sys_mprotect' executable
; int sys_mprotect(void *addr, size_t len, int prot);
sys_mprotect:
    mov rax, 10
    syscall
    ret


section '.text.sys_munmap' executable
; int sys_munmap(void *addr, size_t length);
sys_munmap:
    mov rax, 11 
    syscall
    ret


section '.text.sys_exit' executable
; void sys_exit(int error_code)
sys_exit:
    mov rax, 60
    syscall

