export module std.panic;

import stdc;
import std.sys;
import std.sys.error;

constexpr char panic_message[] = "error: ";

export [[noreturn]] void panic(const char * message) {
    sys::iovec iov[3];
    iov[0].iov_base = (void *) panic_message;
    iov[0].iov_len  = sizeof(panic_message);
    iov[1].iov_base = (void *) message;
    iov[1].iov_len  = strlen(message);
    iov[2].iov_base = (void *) "\n";
    iov[2].iov_len  = 1;
    sys::writev(sys::stderr, iov, 3);
    sys::exit(1);
}

export [[noreturn]] void panic(sys::error err) {
    panic(sys::strerror(err));
}
