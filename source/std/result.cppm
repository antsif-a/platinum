export module std.result;

import std.types;
import std.panic; 
import std.view;
import std.sys;

struct unit_type {};

export template <class T, class E>
struct result {
    enum struct Type { Value, Error } type;
    union {
        T value;
        E error;
    };

    result(T value) : type(Type::Value), value(value) {}
    result(E error) : type(Type::Error), error(error) {}

    bool operator !() {
        return type == Type::Error;
    }

    T operator *() {
        return value;
    }

    /* returns value on success, otherwise prints message with "panic: " prefix */
    T expect(str message) {
        if (type == Type::Error)
            panic(message);
        return value;
    }

    /* returns value on success, otherwise prints message based on error with "panic: " prefix */
    T expect() {
        if (type == Type::Error)
            panic(error);
        return value;
    }

    /* returns value on success, otherwise returns fallback value */
    T or_else(const T & fallback) {
        if (type == Type::Error)
            return fallback;
        return value;
    }

    /* returns value on success, undefined behaviour on error */
    T unwrap_unsafe() {
        return value;
    }
};

export namespace sys {
    template <class T = unit_type>
    using result = ::result<T, sys::error>;

    template <class T>
    inline ::result<T, sys::error> make_result(int ret) {
        if (ret < 0)
            return static_cast<sys::error>(-ret);
        return static_cast<T>(ret);
    }

    inline ::result<unit_type, sys::error> make_result(int ret) {
        if (ret < 0)
            return static_cast<sys::error>(-ret);
        return unit_type {};
    }
};

