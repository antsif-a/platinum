export module std.algorithm;

import std.memory;
import std.types;
import std.result;

export {
    enum struct error {
        not_found
    };

    template <class T, class E>
    result<size_t, error> find(T x, E element) requires const_sequence<T> {
        size_t i = 0;
        while (data(x) + i != end(x)) {
            if (x[i] == element)
                return i;
            ++i;
        }
        return error::not_found;
    }
};

template <class T>
void quick_sort(T & a, int l, int r) requires sequence<T> {
    if (l >= r)
        return;
    int pivot = a[(l + r) / 2];
    int i = l, j = l, k = r;
    while (j <= k) {
        if (a[j] < pivot) {
            swap(a[i++], a[j++]);
        } else if (a[j] > pivot) {
            swap(a[j], a[k--]);
        } else {
            j++;
        }
    }
    quick_sort(a, l, i - 1);
    quick_sort(a, k + 1, r);
}

export {
    template <class T>
    void sort(T & x) requires sequence<T> {
        quick_sort(x, 0, size(x) - 1);
    }
};
