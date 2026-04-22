export module std.panic;

import stdc;
import std.sys;

constexpr char panic_message[] = "panic: ";

export [[noreturn]] void panic(const char * message) {
    sys::write(sys::stderr, panic_message, sizeof(panic_message));
    sys::write(sys::stderr, message, strlen(message));
    sys::exit(1);
}
