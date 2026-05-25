export module std.algorithm;

import std.memory;
import std.types;
import std.result;

export {
    result<size_t, error> find(
        const const_sequence auto &X,
        const element_t<decltype(X)> &x
    ) {
        size_t i = 0;
        while (data(X) + i != end(X)) {
            if (X[i] == x)
                return i;
            ++i;
        }
        return error::not_found;
    }

    result<size_t, error> find_if(
        const const_sequence auto &X,
        predicate<element_t<decltype(X)>> auto condition
    ) {
        size_t i = 0;
        while (data(X) + i != end(X)) {
            if (condition(X[i]))
                return i;
            ++i;
        }
        return error::not_found;
    }
};

void quick_sort(sequence auto &A, size_t l, size_t r) {
    if (l >= r)
        return;
    auto pivot = A[(l + r) / 2];
    size_t i = l, j = l, k = r;
    if (l >= r || r >= size(A))
        return;
    while (j <= k) {
        if (A[j] < pivot) {
            swap(A[i++], A[j++]);
        } else if (A[j] > pivot) {
            swap(A[j], A[k--]);
        } else {
            j++;
        }
    }
    quick_sort(A, l, i - 1);
    quick_sort(A, k + 1, r);
}

export {
    void sort(sequence auto & x) {
        quick_sort(x, 0, size(x) - 1);
    }
};
