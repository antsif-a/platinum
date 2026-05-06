# TODO
There are many things that we need to implement before this library can be released:

## Memory allocation
Currently we *do not* have an allocator. `operator new` is mapped to `heap_alloc` which just returns a pointer and moves internal `heap_ptr` by `size`; `operator delete` is mapped to `heap_free` which does *nothing* (see [memory.c](source/std/c/memory.c)).

## Data structures
We have many data structures and abstract data types missing, including
- stack
- queue
- map (hash_map, tree_map, other implementations)
- graph
- ...

Corresponging algorithms are also missing:
- graph algorithms (dfs, bfs, ...)
- sorting algorithms (only quick sort is supported)
- search algorithms
- ...

## Linking other programs dynamically
I don't even know how to do that without a dynamic linker. should use default one or write it ourselves?

## POSIX coverage
currently we are missing many POSIX syscalls, let alone Linux syscalls

## Examples
with each functionality added there should be a good example covering best practices
