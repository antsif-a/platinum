#include <stddef.h>

size_t strlen(const char * st) {
    size_t i = 0;
    while (st[i])
        ++i;
    return i;
}
