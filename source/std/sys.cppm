module;

export module std.sys;

import std.types;
import std.posix;
import std.sys.error;

enum {
    SYS_read,
    SYS_write,
    SYS_open,
    SYS_close,
    SYS_stat,
    SYS_fstat,
    SYS_lstat,
    SYS_poll,
    SYS_lseek,
    SYS_mmap,
    SYS_mprotect,
    SYS_munmap,
    // ...
    SYS_readv = 19,
    SYS_writev,
    // ...
    SYS_socket = 41,
    SYS_connect,
    SYS_accept,
    SYS_sendto,
    SYS_recvfrom,
    SYS_sendmsg,
    SYS_recvmsg,
    SYS_shutdown,
    SYS_bind,
    SYS_listen,
    // ...
    SYS_setsockopt = 54,
    // ...
    SYS_exit = 60
};

export namespace sys {
    using error = sys::error;

    /* --- read / write --- */
    enum stdio : int {
        stdin, stdout, stderr
    };

    /* --- stat --- */
    // credit: https://git.musl-libc.org/cgit/musl/tree/arch/x86_64/bits/stat.h
    struct stat {
        dev_t st_dev;
        ino_t st_ino;
        nlink_t st_nlink;

        mode_t st_mode;
        uid_t st_uid;
        gid_t st_gid;
        unsigned int    __pad0;
        dev_t st_rdev;
        off_t st_size;
        blksize_t st_blksize;
        blkcnt_t st_blocks;

        timespec st_atim;
        timespec st_mtim;
        timespec st_ctim;
        long __unused[3];
    };

    /* --- open --- */
    enum struct open_flag : int {
        open_rdonly    = 0,
        open_wronly    = 1,
        open_rdwr      = 2,
        open_creat     = 0100,
        open_excl      = 0200,
        open_noctty    = 0400,
        open_trunc     = 01000,
        open_append    = 02000,
        open_nonblock  = 04000,
        open_directory = 0200000,
        open_nofollow  = 0400000,
        open_cloexec   = 02000000,
    };

    enum struct open_mode : mode_t {
        // Owner permissions
        open_irusr = 0400,   // Read by owner
        open_iwusr = 0200,   // Write by owner
        open_ixusr = 0100,   // Execute/search by owner

        // Group permissions
        open_irgrp = 0040,   // Read by group
        open_iwgrp = 0020,   // Write by group
        open_ixgrp = 0010,   // Execute/search by group

        // Others permissions
        open_iroth = 0004,   // Read by others
        open_iwoth = 0002,   // Write by others
        open_ixoth = 0001,   // Execute/search by others

        // Special bits
        open_isuid = 04000,  // Set-user-ID on execution
        open_isgid = 02000,  // Set-group-ID on execution
        open_isvtx = 01000   // Sticky bit (restricts deletion)
    };


    /* --- readv / writev --- */
    struct iovec {
        void * iov_base;    /* Starting address */
        size_t iov_len;     /* Number of bytes to transfer */
    };
};

export {
    namespace sys { 
        #define rax "a"
        #define rbx "b"
        #define rcx "c"
        #define rdx "d"
        #define rsi "S"
        #define rdi "D"
        #define r "r"
        #define out "="
        
        #define syscall(return_type, nd, ...)       \
            return_type ret;            \
            asm volatile ("syscall"     \
                    : out rax(ret)      \
                    : rax(nd), __VA_ARGS__       \
                    : "%rcx", "%r11", "memory");  \
            return ret;

        ssize_t read(int fd, char * buf, size_t n) {
            syscall(ssize_t, SYS_read, rdi(fd), rsi(buf), rdx(n));
        }

        ssize_t write(int fd, const char * buf, size_t n) {
            syscall(ssize_t, SYS_write, rdi(fd), rsi(buf), rdx(n));
        }

        int open(const char *pathname, int flags, mode_t mode) {
            syscall(int, SYS_open, rdi(pathname), rsi(flags), rdx(mode));
        }

        int close(int fd) {
            syscall(int, SYS_close, rdi(fd));
        }

        int stat(const char * path, struct stat * statbuf);
        int fstat(int fd, struct stat * statbuf) {
            syscall(int, SYS_fstat, rdi(fd), rsi(statbuf));
        }

        int lstat(const char * path, struct stat * statbuf);

        /*
        void * mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
            register long r10 asm("r10") = flags;
            register long r8  asm("r8")  = fd;
            register long r9  asm("r9")  = offset;

            syscall(void *, SYS_mmap, rdi(addr), rsi(length), rdx(prot), r(r10), r(r8), r(r9));
        }

        int mprotect(void *addr, size_t len, int prot);
        int munmap(void *addr, size_t length);
        */

        size_t readv(int fd, const iovec * vec, size_t vlen) {
            syscall(size_t, SYS_readv, rdi(fd), rsi(vec), rdx(vlen));
        }

        size_t writev(int fd, const iovec * vec, size_t vlen) {
            syscall(size_t, SYS_writev, rdi(fd), rsi(vec), rdx(vlen));
        }

        int socket(int family, int type, int protocol) {
            syscall(int, SYS_socket, rdi(family), rsi(type), rdx(protocol));
        }

        int accept(int fd, sockaddr *upeer_sockaddr, int *upeer_addrlen) {
            syscall(int, SYS_accept, rdi(fd), rsi(upeer_sockaddr), rdx(upeer_addrlen));
        }

        int bind(int fd, const sockaddr *umyaddr, int addrlen) {
            syscall(int, SYS_bind, rdi(fd), rsi(umyaddr), rdx(addrlen));
        }

        int listen(int fd, int backlog) {
            syscall(int, SYS_listen, rdi(fd), rsi(backlog));
        }

        int setsockopt(int fd, int level, int optname, const void * optval, int optlen) {
            register const void * r10 asm("r10") = optval;
            register int          r8  asm("r8")  = optlen;
            syscall(int, SYS_setsockopt,
                    rdi(fd), rsi(level), rdx(optname), r(r10), r(r8));
        } 

        [[noreturn]] void exit(int status) {
            asm volatile ("syscall" :: rax(SYS_exit), rdi(status) :);
            __builtin_unreachable();
        }
    };
};
