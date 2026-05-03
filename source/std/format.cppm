export module std.format;

import std.string;
import std.math;

export string format(int x) {
    if (x == 0)
        return string("0");

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

    return string(ptr, end - ptr); 
}
