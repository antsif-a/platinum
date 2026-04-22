export module std.array;

import stdc;
import std.types;
import std.memory;
import std.view;

export template<typename T> size_t arrlen(T * arr) {
    size_t i = 0;
    while (arr[i])
        ++i;
    return i;
}

/*
 * a dynamic linear array
 * - manages memory
 *   => should be referenced
 * - dynamic size
 * - readable / writable
 */
export template <typename T> class array {
    T * elements;
    size_t _count;
    size_t _capacity;
public:
    array() : elements(nullptr), _count(0), _capacity(0) {}
    array(size_t _capacity) : _count(0), _capacity(_capacity) {
        elements = new T[_capacity]; 
    }

    void resize(size_t new_capacity) {
        if (_capacity == 0) {
            elements = new T[new_capacity];
        } else {
            T * new_elements = new T[new_capacity];
            memcpy(new_elements, elements, _count);
            delete[] elements;
            elements = new_elements;
            _capacity = new_capacity;
        }
    }

    void push(T element) {
        if (_count == _capacity)
            resize(_capacity * 2);
        elements[_count++] = element;
    }

    T & operator[](size_t n) {
        return elements[n];
    }

    T * data() {
        return elements;
    }

    T * begin() {
        return elements;
    }

    T * end() {
        return elements + _count;
    }

    size_t count() {
        return _count;
    }

    size_t capacity() {
        return _capacity;
    }
};

/*
 * represents a static array
 * - manages memory
 *   => should be referenced
 * - constant size
 * - readable / writable
 */
export template <typename T, size_t N> class tuple {
    T * elements;

    public:
        tuple() {
            elements = new T[N];
        }

        ~tuple() {
            delete[] elements;
        }

        T * data() {
            return elements;
        }

        size_t count() {
            return N;
        }

        operator buffer() requires is_same_v<T, char> {
            return buffer(elements, N);
        }
};


