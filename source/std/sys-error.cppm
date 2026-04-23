export module std.sys.error;

import std.types;

export namespace sys {
    enum struct error {
        E2BIG           = 7,
        EACCES          = 13,
        EADDRINUSE      = 98,
        EADDRNOTAVAIL   = 99,
        EAFNOSUPPORT    = 97,
        EAGAIN          = 11,
        EALREADY        = 114,
        EBADE           = 52,
        EBADF           = 9,
        EBADFD          = 77,
        EBADMSG         = 74,
        EBADR           = 53,
        EBADRQC         = 56,
        EBADSLT         = 57,
        EBUSY           = 16,
        ECANCELED       = 125,
        ECHILD          = 10,
        ECHRNG          = 44,
        ECOMM           = 70,
        ECONNABORTED    = 103,
        ECONNREFUSED    = 111,
        ECONNRESET      = 104,
        EDEADLK         = 35,
        EDEADLOCK       = 35,   // same as EDEADLK on most architectures
        EDESTADDRREQ    = 89,
        EDOM            = 33,
        EDQUOT          = 122,
        EEXIST          = 17,
        EFAULT          = 14,
        EFBIG           = 27,
        EHOSTDOWN       = 112,
        EHOSTUNREACH    = 113,
        EHWPOISON       = 133,
        EIDRM           = 43,
        EILSEQ          = 84,
        EINPROGRESS     = 115,
        EINTR           = 4,
        EINVAL          = 22,
        EIO             = 5,
        EISCONN         = 106,
        EISDIR          = 21,
        EISNAM          = 120,
        EKEYEXPIRED     = 127,
        EKEYREJECTED    = 129,
        EKEYREVOKED     = 128,
        EL2HLT          = 51,
        EL2NSYNC        = 45,
        EL3HLT          = 46,
        EL3RST          = 47,
        ELIBACC         = 83,
        ELIBBAD         = 80,
        ELIBMAX         = 82,
        ELIBSCN         = 81,
        ELIBEXEC        = 80,   // actually ELIBEXEC = 80? Not standard, skip or set to unused
        ELNRNG          = 48,
        ELOOP           = 40,
        EMEDIUMTYPE     = 124,
        EMFILE          = 24,
        EMLINK          = 31,
        EMSGSIZE        = 90,
        EMULTIHOP       = 72,
        ENAMETOOLONG    = 36,
        ENETDOWN        = 100,
        ENETRESET       = 102,
        ENETUNREACH     = 101,
        ENFILE          = 23,
        ENOANO          = 55,
        ENOBUFS         = 105,
        ENODATA         = 61,
        ENODEV          = 19,
        ENOENT          = 2,    // ← this is the one you hit
        ENOEXEC         = 8,
        ENOKEY          = 126,
        ENOLCK          = 37,
        ENOLINK         = 67,
        ENOMEDIUM       = 123,
        ENOMEM          = 12,
        ENOMSG          = 42,
        ENONET          = 64,
        ENOPKG          = 65,
        ENOPROTOOPT     = 92,
        ENOSPC          = 28,
        ENOSR           = 63,
        ENOSTR          = 60,
        ENOSYS          = 38,
        ENOTBLK         = 15,
        ENOTCONN        = 107,
        ENOTDIR         = 20,
        ENOTEMPTY       = 39,
        ENOTRECOVERABLE = 131,
        ENOTSOCK        = 88,
        ENOTSUP         = 95,   // note: ENOTSUP = 95, EOPNOTSUPP is also 95 on Linux
        ENOTTY          = 25,
        ENOTUNIQ        = 76,
        ENXIO           = 6,
        EOPNOTSUPP      = 95,   // same as ENOTSUP
        EOVERFLOW       = 75,
        EOWNERDEAD      = 130,
        EPERM           = 1,
        EPFNOSUPPORT    = 96,
        EPIPE           = 32,
        EPROTO          = 71,
        EPROTONOSUPPORT = 93,
        EPROTOTYPE      = 91,
        ERANGE          = 34,
        EREMCHG         = 78,
        EREMOTE         = 66,
        EREMOTEIO       = 121,
        ERESTART        = 85,
        ERFKILL         = 132,
        EROFS           = 30,
        ESHUTDOWN       = 108,
        ESPIPE          = 29,
        ESOCKTNOSUPPORT = 94,
        ESRCH           = 3,
        ESTALE          = 116,
        ESTRPIPE        = 86,
        ETIME           = 62,
        ETIMEDOUT       = 110,
        ETOOMANYREFS    = 109,
        ETXTBSY         = 26,
        EUCLEAN         = 117,
        EUNATCH         = 49,
        EUSERS          = 87,
        EWOULDBLOCK     = 11,   // same as EAGAIN
        EXDEV           = 18,
        EXFULL          = 54
    };

    const char * strerror(error err) {
        switch (err) {
            case error::EPERM:             return "Operation not permitted";
            case error::ENOENT:            return "No such file or directory";
            case error::ESRCH:             return "No such process";
            case error::EINTR:             return "Interrupted system call";
            case error::EIO:               return "Input/output error";
            case error::ENXIO:             return "No such device or address";
            case error::E2BIG:             return "Argument list too long";
            case error::ENOEXEC:           return "Exec format error";
            case error::EBADF:             return "Bad file descriptor";
            case error::ECHILD:            return "No child processes";
            case error::EAGAIN:            return "Resource temporarily unavailable";
            case error::ENOMEM:            return "Cannot allocate memory";
            case error::EACCES:            return "Permission denied";
            case error::EFAULT:            return "Bad address";
            case error::ENOTBLK:           return "Block device required";
            case error::EBUSY:             return "Device or resource busy";
            case error::EEXIST:            return "File exists";
            case error::EXDEV:             return "Invalid cross‑device link";
            case error::ENODEV:            return "No such device";
            case error::ENOTDIR:           return "Not a directory";
            case error::EISDIR:            return "Is a directory";
            case error::EINVAL:            return "Invalid argument";
            case error::ENFILE:            return "Too many open files in system";
            case error::EMFILE:            return "Too many open files";
            case error::ENOTTY:            return "Inappropriate ioctl for device";
            case error::ETXTBSY:           return "Text file busy";
            case error::EFBIG:             return "File too large";
            case error::ENOSPC:            return "No space left on device";
            case error::ESPIPE:            return "Illegal seek";
            case error::EROFS:             return "Read‑only file system";
            case error::EMLINK:            return "Too many links";
            case error::EPIPE:             return "Broken pipe";
            case error::EDOM:              return "Numerical argument out of domain";
            case error::ERANGE:            return "Numerical result out of range";
            case error::EDEADLK:           return "Resource deadlock avoided";
            case error::ENAMETOOLONG:      return "File name too long";
            case error::ENOLCK:            return "No locks available";
            case error::ENOSYS:            return "Function not implemented";
            case error::ENOTEMPTY:         return "Directory not empty";
            case error::ELOOP:             return "Too many levels of symbolic links";
            case error::ENOMSG:            return "No message of desired type";
            case error::EIDRM:             return "Identifier removed";
            case error::ECHRNG:            return "Channel number out of range";
            case error::EL2NSYNC:          return "Level 2 not synchronized";
            case error::EL3HLT:            return "Level 3 halted";
            case error::EL3RST:            return "Level 3 reset";
            case error::ELNRNG:            return "Link number out of range";
            case error::EUNATCH:           return "Protocol driver not attached";
            case error::EBADE:             return "Invalid exchange";
            case error::EBADR:             return "Invalid request descriptor";
            case error::EXFULL:            return "Exchange full";
            case error::ENOANO:            return "No anode";
            case error::EBADRQC:           return "Invalid request code";
            case error::EBADSLT:           return "Invalid slot";
            case error::ENOSTR:            return "Not a STREAM";
            case error::ENODATA:           return "No data available";
            case error::ETIME:             return "Timer expired";
            case error::ENOSR:             return "No STREAM resources";
            case error::ENONET:            return "Machine is not on the network";
            case error::ENOPKG:            return "Package not installed";
            case error::EREMOTE:           return "Object is remote";
            case error::ENOLINK:           return "Link has been severed";
            case error::EPROTO:            return "Protocol error";
            case error::EMULTIHOP:         return "Multihop attempted";
            case error::EBADMSG:           return "Bad message";
            case error::EOVERFLOW:         return "Value too large for defined data type";
            case error::ENOTUNIQ:          return "Name not unique on network";
            case error::EBADFD:            return "File descriptor in bad state";
            case error::EREMCHG:           return "Remote address changed";
            case error::ELIBEXEC:          return "Cannot exec a shared library directly";
            case error::ELIBSCN:           return ".lib section in a.out corrupted";
            case error::ELIBMAX:           return "Attempting to link in too many shared libraries";
            case error::ELIBACC:           return "Cannot access a needed shared library";
            case error::EILSEQ:            return "Illegal byte sequence";
            case error::ERESTART:          return "Interrupted system call should be restarted";
            case error::ESTRPIPE:          return "Streams pipe error";
            case error::EUSERS:            return "Too many users";
            case error::ENOTSOCK:          return "Socket operation on non‑socket";
            case error::EDESTADDRREQ:      return "Destination address required";
            case error::EMSGSIZE:          return "Message too long";
            case error::EPROTOTYPE:        return "Protocol wrong type for socket";
            case error::ENOPROTOOPT:       return "Protocol not available";
            case error::EPROTONOSUPPORT:   return "Protocol not supported";
            case error::ESOCKTNOSUPPORT:   return "Socket type not supported";
            case error::EOPNOTSUPP:        return "Operation not supported on socket";
            case error::EPFNOSUPPORT:      return "Protocol family not supported";
            case error::EAFNOSUPPORT:      return "Address family not supported";
            case error::EADDRINUSE:        return "Address already in use";
            case error::EADDRNOTAVAIL:     return "Cannot assign requested address";
            case error::ENETDOWN:          return "Network is down";
            case error::ENETUNREACH:       return "Network is unreachable";
            case error::ENETRESET:         return "Network dropped connection on reset";
            case error::ECONNABORTED:      return "Software caused connection abort";
            case error::ECONNRESET:        return "Connection reset by peer";
            case error::ENOBUFS:           return "No buffer space available";
            case error::EISCONN:           return "Transport endpoint already connected";
            case error::ENOTCONN:          return "Transport endpoint not connected";
            case error::ESHUTDOWN:         return "Cannot send after transport endpoint shutdown";
            case error::ETOOMANYREFS:      return "Too many references: cannot splice";
            case error::ETIMEDOUT:         return "Connection timed out";
            case error::ECONNREFUSED:      return "Connection refused";
            case error::EHOSTDOWN:         return "Host is down";
            case error::EHOSTUNREACH:      return "No route to host";
            case error::EALREADY:          return "Operation already in progress";
            case error::EINPROGRESS:       return "Operation now in progress";
            case error::ESTALE:            return "Stale file handle";
            case error::EUCLEAN:           return "Structure needs cleaning";
            case error::EISNAM:            return "Is a named type file";
            case error::EREMOTEIO:         return "Remote I/O error";
            case error::EDQUOT:            return "Disk quota exceeded";
            case error::ENOMEDIUM:         return "No medium found";
            case error::EMEDIUMTYPE:       return "Wrong medium type";
            case error::ECANCELED:         return "Operation canceled";
            case error::ENOKEY:            return "Required key not available";
            case error::EKEYEXPIRED:       return "Key has expired";
            case error::EKEYREVOKED:       return "Key has been revoked";
            case error::EKEYREJECTED:      return "Key was rejected by service";
            case error::EOWNERDEAD:        return "Owner died";
            case error::ENOTRECOVERABLE:   return "State not recoverable";
            case error::ERFKILL:           return "Operation not possible due to RF‑kill";
            case error::EHWPOISON:         return "Memory page has hardware error";
            default:                       return "Unknown error";
        }
    }
};


