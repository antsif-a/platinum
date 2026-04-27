#include <stddef.h>

size_t strlen(const char * st) {
    size_t i = 0;
    while (st[i])
        ++i;
    return i;
}

size_t arrlen(void * arr[]) {
    size_t i = 0;
    while (arr[i])
        ++i;
    return i;
}
