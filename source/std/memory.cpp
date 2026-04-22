import stdc;
import std.types;

void * operator new(size_t count) {
    return (void *) heap_alloc(count);
}

void * operator new[](size_t count) {
    return operator new(count);
}

void operator delete(void * ptr) noexcept {
    heap_free(ptr);
}

void operator delete(void * ptr, size_t size) noexcept {
    (void) size;
    heap_free(ptr);
}

void operator delete[](void * ptr) noexcept {
    return operator delete(ptr);
}

void operator delete[](void * ptr, size_t size) noexcept {
    (void) size;
    return operator delete(ptr);
}
