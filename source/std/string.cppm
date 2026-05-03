export module std.string;

import stdc;
import std.memory;
import std.types;
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
    size_t _capacity;

    public:
        string() : _data(nullptr), _length(0) {}
        string(const char * data, size_t length) : _length(length), _capacity(length) {
            _data = new char[_length + 1] {};
            copy(_data, data, length);
        }
        string(const char * data) : string(data, strlen(data)) {}

        /* from null-terminated literal */
        template <size_t N>
        string(const char (&data)[N]) : string(data, N - 1) {}

        string(size_t capacity) : _length(capacity), _capacity(capacity) {
            _data = new char[_length + 1];
        }

        char * data() {
            return _data;
        }

        const char * data() const {
            return _data;
        } 

        /* undefined behaviour if actual length do no match or length > capacity */
        void set_length_unsafe(size_t length) {
            _length = length;
        }

        size_t length() const {
            return _length;
        }

        size_t capacity() const {
            return _capacity;
        }

        char & operator[](size_t n) {
            return _data[n];
        }

        const char & operator[](size_t n) const {
            return _data[n];
        }

        const char * begin() const {
            return _data;
        }
        
        const char * end() const {
            return _data + _length;
        }

        const char * c_str() const {
            return _data;
        }

        operator str() const {
            return str(_data, _length);
        }

        operator buffer() const {
            return buffer(reinterpret_cast<unsigned char*>(_data), _length);
        }
};
