export module std.posix;

import stdc;
import std.types;

/* --- POSIX.1-2024 --- */
export {
    using dev_t      = unsigned long int;
    using uid_t      = unsigned int;
    using gid_t      = unsigned int;
    using ino_t      = unsigned long;
    using ino64_t    = unsigned long int;
    using mode_t     = unsigned int;
    using nlink_t    = unsigned long;
    using off_t      = signed   long;
    using off64_t    = signed   long int;
    using pid_t      = signed   int;
    using blkcnt_t   = signed   long;
    using blkcnt64_t = signed   long int;
    using time_t     = signed   long;
    using blksize_t  = signed   long;
    using ssize_t    = signed   long int;

    struct timespec {
        time_t tv_sec;
        long   tv_nsec;
    };

    /* --- sockets --- */
    using socklen_t   = int32_t;
    using sa_family_t = uint16_t;

    enum sa_family : sa_family_t {
        af_unspec,
        af_local,
        af_inet
        // ...
    };

    struct sockaddr {
        sa_family_t sa_family;
        char        sa_data[14];
    };

    using in_addr_t = uint32_t;
    using in_port_t = uint16_t;

    struct in_addr {
        in_addr_t s_addr;
    };
   
    struct sockaddr_in {
        sa_family_t sin_family;     /* AF_INET */
        in_port_t   sin_port;       /* Port number */
        in_addr     sin_addr;       /* IPv4 address */
        char        sin_zero[8];

        sockaddr_in() {}
        sockaddr_in(in_port_t port, in_addr_t addr)
            : sin_family(af_inet),
              sin_port(htons(port)),
              sin_addr(htonl(addr)) {}
    }; 

    enum socket_type : int {
        sock_stream = 1,
        sock_dgram,
        sock_raw,
        // ...
    };

    enum socket_level : int {
        sol_socket = 1,
        // ...
    };

    enum socket_option : int {
        so_reuseaddr = 2,
        // ...
    };
};
