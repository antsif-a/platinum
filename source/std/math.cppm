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
    auto abs(totally_ordered auto x) {
        return 0 <= x ? x : -x;
    }

    signed sgn(totally_ordered auto x) {
        if (x == 0) {
            return 0;
        }

        return x < 0 ? -1 : 1;
    }
};
