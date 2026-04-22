#include <stddef.h>

#define HEAP_CAPACITY 1024 * 1024

char heap[HEAP_CAPACITY];
static char * heap_end = heap + HEAP_CAPACITY;
static char * heap_ptr = heap;

void * heap_alloc(size_t size) {
    if (heap_ptr + size > heap_end)
        return NULL;
    void * data = (void *) heap_ptr;
    heap_ptr += size;
    return data;
}

void heap_free(void * ptr) {
    (void) ptr;
}

void * memcpy(void * restrict dest, const void * restrict src, size_t n) {
    char * dp = dest;
    const char * sp = src;
    while (n--)
        *dp++ = *sp++;
    return dest;
}

void * memmove(void * dest, const void * src, size_t n) {
   unsigned char tmp[n];
   memcpy(tmp, src, n);
   memcpy(dest, tmp, n);
   return dest;
}

void * memset(void * ptr, int value, size_t n) {
    unsigned char * p = ptr;
    while (n--)
        *p++ = (unsigned char) value;
    return ptr;
}

int memcmp(const void * s1, const void * s2, size_t n) {
    const unsigned char * p1 = s1, * p2 = s2;
    while (n--)
        if (*p1 != *p2)
            return *p1 - *p2;
        else
            p1++, p2++;
    return 0;
}
