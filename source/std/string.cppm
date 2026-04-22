export module std.string;

import stdc;
import std.types;
import std.math;
import std.memory;
import std.view;

/* a string
 * - manages memory
 *   - should be referenced
 * - read/write
 * - null terminated
 */
export class string {
    char * _data;
    size_t _length;

    public:
        string() : _data(nullptr), _length(0) {}
        string(const char * data, size_t length) : _length(length) {
            _data = new char[_length + 1] {};
            memcpy(_data, data, length);
        }
        string(const char * data) : string(data, strlen(data)) {}

        /* from null-terminated literal */
        template <size_t N>
        string(const char (&data)[N]) : string(data, N - 1) {}

        string(size_t length) : _length(length) {
            _data = new char[_length + 1] {};
        }

        const char * data() {
            return _data;
        } 

        size_t length() {
            return _length;
        }

        char & operator[](size_t n) {
            return _data[n];
        }

        const char * begin() {
            return _data;
        }
        
        const char * end() {
            return _data + _length;
        }

        const char * c_str() {
            return _data;
        }

        operator str() {
            return str(_data, _length);
        }

        operator buffer() {
            return buffer(_data, _length);
        }
 };

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
