export module std.panic;

import stdc;
import std.sys;
import std.sys.error;
import std.view;

constexpr char panic_message[] = "error: ";

export [[noreturn]] void panic(str message) {
    const sys::const_iovec iov[3] = {
        { panic_message, sizeof(panic_message) },
        { message.data, message.size },
        { "\n", 1 }
    };
    sys::writev(sys::stderr, iov, 3);
    sys::exit(1);
}

export [[noreturn]] void panic(sys::error err) {
    panic(sys::strerror(err));
}
