export module std.result;

import std.types;
import std.panic;

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
};
