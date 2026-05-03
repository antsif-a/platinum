#ifndef _MEMORY_H
#define _MEMORY_H

#ifdef __cplusplus
#define restrict __restrict
#endif

void * memcpy(void * restrict dest, const void * restrict src, size_t n);
void * memmove(void * dest, const void * src, size_t n);
void * memset(void * ptr, int value, size_t n);
int memcmp(const void * s1, const void * s2, size_t n);

void * heap_alloc(size_t size);
void heap_free(void * ptr);

#endif

