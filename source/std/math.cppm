export module std.math;

import std.types;

template <class T> concept totally_ordered = requires(T a, T b) {
    {a <  b} -> boolean_testable;
    {a >  b} -> boolean_testable;
    {a <= b} -> boolean_testable;
    {a >= b} -> boolean_testable;
    {b <  a} -> boolean_testable;
    {b >  a} -> boolean_testable;
    {b <= a} -> boolean_testable;
    {b >= a} -> boolean_testable;
};

export {
    template <totally_ordered T>
    T abs(T x) {
        return 0 <= x ? x : -x;
    }

    template <totally_ordered T>
    signed sgn(T x) {
        if (x == 0) {
            return 0;
        }

        return x < 0 ? -1 : 1;
    }
};
