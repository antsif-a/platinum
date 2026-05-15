export module std.format;

import std.string;
import std.math;
import std.memory;

export {
    void format_to(string &st, int x) {
        if (x == 0) {
            st[0] = '0';
            st.set_length_unsafe(1);
        }

        // 12 bytes is enough for 32-bit int: "-2147483648" + null
        char buf[12];
        char * end = buf + 12;
        char * ptr = end;

        signed sign = sgn(x);
        x = abs(x);

        do {
            *--ptr = '0' + (x % 10);
            x /= 10;
        } while (x != 0);

        if (sign == -1)
            *--ptr = '-';

        copy(st.data(), ptr, end - ptr);
        st.set_length_unsafe(end - ptr);
    }

    string format(int x) {
        string st = string(12);
        format_to(st, x);
        return st;
    }
};
