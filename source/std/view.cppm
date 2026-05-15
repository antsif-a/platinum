export module std.view;

import stdc;
import std.types;

export struct const_buffer {
    const void * data;
    size_t size;
};

export struct buffer {
    void * data;
    size_t size;

    operator const_buffer() {
        return {data, size};
    }
};

export template <typename T> struct const_view {
    const T * data;
    size_t size;

    const T & operator[](size_t n) const {
        return data[n];
    }

    operator const_buffer() {
        return {data, size};
    }
};

export template <typename T> struct view {
    T * data;
    size_t size;

    T & operator[](size_t n) {
        return data[n];
    }

    const T & operator[](size_t n) const {
        return data[n];
    }

    operator buffer() {
        return {data, size};
    }

    operator const_buffer() {
        return {data, size};
    }

    operator const_view<T>() {
        return {data, size};
    }
};

export struct str {
    enum struct error : int {
        none,
        not_found
    };

    const char * data;
    size_t size;

    str():
        data(nullptr),
        size(0) {}

    str(const char * data, size_t size):
        data(data),
        size(size) {}

    template <size_t N>
    str(const char (&data)[N]):
        str(data, N - 1) {}

    str(const char * data):
        str(data, strlen(data)) {}

    bool operator==(const str &st) const {
        if (size != st.size)
            return false;
        for (size_t i = 0; i < size; ++i)
            if (data[i] != st[i])
                return false;
        return true;
    }

    template <size_t N>
    bool operator==(const char (&p)[N]) const {
        if (size != N - 1)
            return false;
        for (size_t i = 0; i < N - 1; ++i)
            if (data[i] != p[i])
                return false;
        return true;
    }

    char operator[](size_t n) const {
        return data[n];
    }

    char operator[](size_t n) {
        return data[n];
    }

    operator const_buffer() {
        return {data, size};
    }

    operator const_view<char>() {
        return {data, size};
    }
};

// we need these functions because .size and .data are already members
export {
    // now "str" is both const_sequence and const_span
    // begin() and end() are generated automatically by template system
    size_t       size(const str &x) { return x.size; };
    const char * data(const str &x) { return x.data; };

    // same for other views
    void * data(const buffer &x) { return x.data; };
    size_t size(const buffer &x) { return x.size; };
    const void * data(const const_buffer &x) { return x.data; };
    size_t       size(const const_buffer &x) { return x.size; };
    template <class T> T *    data(const view<T> &x) { return x.data; };
    template <class T> size_t size(const view<T> &x) { return x.size; };
    template <class T> const T * data(const const_view<T> &x) { return x.data; };
    template <class T> size_t    size(const const_view<T> &x) { return x.size; };
};
