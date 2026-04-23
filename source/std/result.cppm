export module std.result;

import std.types;
import std.panic; 
import std.sys;

export template <class T, class E>
struct result {
    enum struct Type { Value, Error };
    Type type;
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

    /* we use const char * here to avoid dependency loop with std.view */
    T expect(const char * message) {
        if (type == Type::Error)
            panic(message);
        return value;
    }

    T or_else(const T & fallback) {
        if (type == Type::Error)
            return fallback;
        return value;
    }
};

export namespace sys {
    template <class T>
    using result = ::result<T, sys::error>;

    template <class T>
    ::result<T, sys::error> make_result(int ret) {
        if (ret < 0) {
            return static_cast<sys::error>(-ret);
        } else {
            return static_cast<T>(ret);
        }
    }
};

