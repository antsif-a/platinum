export module std.array;

import stdc;
import std.types;
import std.memory;
import std.view;

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
    array(T * elements) requires is_pointer_v<T> {
        _count = arrlen(static_cast<void * []>(elements));
        _capacity = _count;
        memcpy(this->elements, elements, _count);
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

    void push_back_unchecked(const T& element) {
        elements[_count++] = element;
    }

    void push_back(const T& element) {
        if (_count == _capacity)
            resize(_capacity * 2);
        elements[_count++] = element;
    }

    T & operator[](size_t n) {
        return elements[n];
    }

    const T & operator[](size_t n) const {
        return elements[n];
    }

    T * data() const {
        return elements;
    }

    T * begin() const {
        return elements;
    }

    T * end() const {
        return elements + _count;
    }

    size_t count() const {
        return _count;
    }

    size_t capacity() const {
        return _capacity;
    }

    operator view<T>() {
        return view(elements, _count);
    }

    operator const_view<T>() {
        return const_view(elements, _count);
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

        T & operator[](size_t n) {
            return elements[n];
        }

        const T & operator[](size_t n) const {
            return elements[n];
        }

        operator buffer() requires is_same_v<T, char> {
            return buffer(elements, N);
        }
};


