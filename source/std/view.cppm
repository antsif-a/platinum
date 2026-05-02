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

    const T * begin() const {
        return data;
    }

    const T * end() const {
        return data + size;
    }

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

    const char * begin() const {
        return data;
    }
    
    const char * end() const {
        return data + size;
    }

    operator const_buffer() {
        return {data, size};
    }

    operator const_view<char>() {
        return {data, size};
    }
};

export size_t size(str &s) {
    return s.size;
}
