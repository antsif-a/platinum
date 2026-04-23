export module std.view;

import stdc;
import std.types;
import std.result;

/*
 * view, const_view, str and buffer have public fields (and are marked as structs)
 * to emphasize their lightweight and trivial copyable nature
 */

/*
 * represents a modifiable view over a contiguous and homogeneous area of memory
 * - does not manage memory
 * - read / write
 */
export template <typename T> struct view {
    T * data;
    const size_t size;

    T * begin() const {
        return data;
    }

    T * end() const {
        return data + size;
    }

    T & operator[](size_t n) {
        return data[n];
    }

    const T & operator[](size_t n) const {
        return data[n];
    }
};

/*
 * represents a view over a contiguous and homogeneous area of memory
 * - does not manage memory
 * - read only
 */
export template <typename T> struct const_view {
    const T * data;
    const size_t size;

    const T * begin() const {
        return data;
    }

    const T * end() const {
        return data + size;
    }

    const T & operator[](size_t n) const {
        return data[n];
    }
};

/*
 * a string slice
 * - does not manage memory
 *   - should be copied
 * - read only
 * - not null terminated
 */
export struct str {
    enum struct error : int {
        none,
        not_found
    };

    const char * data;
    size_t size;

    str() : data(nullptr), size(0) {}

    /* from null-terminated literal */
    template <size_t N>
        str(const char (&data)[N]): data(data), size(N - 1) {}

    str(const char * data, size_t n) : data(data), size(n) {}

    str(const char * p): data(p), size(strlen(p)) {}

    template <size_t N>
    bool operator == (const char (&p)[N]) const {
        if (size != N - 1)
            return false;
        for (size_t i = 0; i < N - 1; ++i)
            if (data[i] != p[i])
                return false;
        return true;
    }

    char operator[](size_t n) {
        return data[n];
    }

    char operator[](size_t n) const {
        return data[n];
    }

    const char * begin() const {
        return data;
    }
    
    const char * end() const {
        return data + size;
    }

    result<size_t, error> find(char c) const {
        size_t i = 0;
        while (data[i] != c) {
            if (data[i] == '\0')
                return error::not_found;
            ++i;
        }

        return i;
    }
};

/*
 * a memory slice over a contiguous area of bytes
 * - does not manage memory
 *   => should be copied
 * - read / write
 * - writeable alternative to str
 */
export struct buffer {
    char * data;
    size_t size;
};
