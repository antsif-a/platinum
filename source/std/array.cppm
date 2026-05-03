export module std.array;

import std.types;
import std.memory;
import std.view;

export template <typename T, size_t N> class array {
    T * elements;
public:
    array() {
        elements = new T[N];
    }

    array(T * elements) {
        this->elements = new T[N];
        copy(this->elements, elements, N);
    }

    array(std::initializer_list<T> args) {
        this->elements = new T[N];
        copy(this->elements, args.begin(), args.size());
    }

    ~array() {
        delete[] elements;
    }

    size_t count() const {
        return N;
    }

    T * data() const {
        return elements;
    }

    const T & operator[](size_t n) const {
        return elements[n];
    }

    T & operator[](size_t n) {
        return elements[n];
    }

    operator view<T>() {
        return {elements, N};
    }

    operator const_view<T>() {
        return {elements, N};
    }
};

export template <class T> class fixed_array {
    T * elements;
    const size_t size;
public:
    fixed_array(size_t size): size(size) {
        this->elements = new T[size];
    }

    fixed_array(T * elements, size_t size): fixed_array(size) {
        copy(this->elements, elements, size);
    }

    fixed_array(std::initializer_list<T> args):
        fixed_array(args.begin(), args.size()) {}

    ~fixed_array() {
        delete[] elements;
    }

    size_t count() {
        return size;
    }

    T * data() {
        return elements;
    }

    const T & operator[](size_t n) const {
        return elements[n];
    }

    T & operator[](size_t n) {
        return elements[n];
    }

    operator view<T>() {
        return {elements, size};
    }

    operator const_view<T>() {
        return {elements, size};
    }
};

export template <typename T> class dynamic_array {
    T * elements;
    size_t count_;
    size_t capacity_;
public:
    dynamic_array():
        elements(nullptr), count_(0), capacity_(0) {}

    dynamic_array(size_t capacity):
        count_(0), capacity_(capacity)
    {
        elements = new T[capacity];
    }

    dynamic_array(T * elements, size_t size) {
        count_ = size;
        capacity_ = size;
        copy(this->elements, elements, size);
    }

    dynamic_array(std::initializer_list<T> args):
        dynamic_array(args.begin(), args.size()) {}

    size_t count() const {
        return count_;
    }

    size_t capacity() const {
        return capacity_;
    }

    T * data() {
        return elements;
    }

    const T * data() const {
        return elements;
    }

    T & operator[](size_t n) {
        return elements[n];
    }

    const T & operator[](size_t n) const {
        return elements[n];
    }

    void resize(size_t new_capacity) {
        if (capacity_ == 0) {
            elements = new T[new_capacity];
        } else {
            T * new_elements = new T[new_capacity];
            copy(new_elements, elements, count_);
            delete[] elements;
            elements = new_elements;
            capacity_ = new_capacity;
        }
    }

    void push_back_unchecked(const T& element) {
        elements[count_++] = element;
    }

    void push_back(const T& element) {
        if (count_ == capacity_)
            resize(capacity_ * 2);
        elements[count_++] = element;
    }

    operator view<T>() {
        return {elements, count_};
    }

    operator const_view<T>() {
        return {elements, count_};
    }
};

export {
    template <typename T, size_t N>
    size_t size(array<T, N> &) {
        return N;
    }

    template <typename T, size_t N>
    T * data(array<T, N> &arr) {
        return arr.data();
    }

    template <typename T>
    size_t size(fixed_array<T> &arr) {
        return arr.count();
    }

    template <typename T>
    T * data(fixed_array<T> &arr) {
        return arr.data();
    }

    template <typename T>
    size_t size(dynamic_array<T> &arr) {
        return arr.count();
    }

    template <typename T>
    T * data(dynamic_array<T> &arr) {
        return arr.data();
    }
};
