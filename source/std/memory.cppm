export module std.memory;

import stdc;
import std.types;

export template <class T> void swap(T & __restrict a, T & __restrict b) {
    T c = a;
    a = b;
    b = c;
}

export template <class T> void copy(T * __restrict dest, const T * __restrict src, size_t n) {
    memcpy(dest, src, n * sizeof(T));
}


