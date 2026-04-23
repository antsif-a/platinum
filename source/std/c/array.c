#include <stddef.h>

size_t arrlen(void * arr[]) {
    size_t i = 0;
    while (arr[i])
        ++i;
    return i;
}
