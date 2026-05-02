export module std.algorithm;

import stdc;
import std.types;
import std.result;

export {
    enum struct error {
        not_found
    };

    template <class T, class E>
    result<size_t, error> find(T x, E element) requires const_sequence<T, E> {
        size_t i = 0;
        while (x[i] != x[size(x)]) {
            if (x[i] == element) {
                return i;
            } else {
                ++i;
            }
        }

        return error::not_found;
    }

    // TODO
    template <class T, class E>
    void sort(T x) requires sequence<T, E> {}
};

