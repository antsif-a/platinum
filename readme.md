<img width="1359" height="340" alt="изображение" src="https://github.com/user-attachments/assets/6e480cfd-8215-407e-980d-a20377cf1865" />
<h1 align=center>platinum — c++ runtime & standard library</h1>

## Examples
> see [examples](examples/)

1. hello world
```cpp
import std.io;

int main() {
    println("Hello, World");
    return 0;
}
```
file size is 576 bytes (after strip):
```
$ stat --printf="%s\n" ./build/linux/x86_64/release/01_hello_world
576
```
and output assembly is relatively clean and short:
```
$ objdump -SMintel --no-show-raw-insn ./build/linux/x86_64/release/01_hello_world
./build/linux/x86_64/release/01_hello_world:     file format elf64-x86-64
Disassembly of section .text:
00000000004000b0 <.text>:
  4000b0:	lea    rsi,[rsp-0x28]
  4000b5:	mov    edi,0x1
  4000ba:	mov    edx,0x2
  4000bf:	mov    QWORD PTR [rsp-0x20],0xc
  4000c8:	mov    QWORD PTR [rsp-0x10],0x1
  4000d1:	lea    rax,[rip+0x3b]        # 0x400113
  4000d8:	mov    QWORD PTR [rsp-0x28],rax
  4000dd:	lea    rax,[rip+0x3c]        # 0x400120
  4000e4:	mov    QWORD PTR [rsp-0x18],rax
  4000e9:	mov    eax,0x14
  4000ee:	syscall
  4000f0:	xor    eax,eax
  4000f2:	ret
  4000f3:	nop    DWORD PTR [rax+rax*1+0x0]
  4000f8:	pop    rdi
  4000f9:	mov    rsi,rsp
  4000fc:	lea    rdx,[rsp+rdi*8+0x8]
  400101:	push   rax
  400102:	call   0x4000b0
  400107:	mov    rdi,rax
  40010a:	mov    rax,0x3c
  400111:	syscall
```
2. echo shell
```cpp
import std.io;
import std.string;

int main() {
    string buf = string(128);
    for (print("> "); input(buf).expect("can't read"); print("> "))
        print(buf);
    println();
    return 0;
}
```
3. file print
```cpp
import std.io;
import std.string;

int main(int argc, char * argv[]) {
    if (argc < 2) {
        println("usage: ", argv[0], " <file>");
        return 1;
    }

    int fd = open(string(argv[1]), open_rdonly, 0)
        .expect("couldn't open file");

    file_status statbuf;
    fstat(fd, statbuf)
        .expect("couldn't get file status");

    string st = string(statbuf.st_size);

    read(fd, st)
        .expect("couldn't read file");

    close(fd)
        .expect("couldn't close file");

    print(st);
    return 0;
}
```

## Documentation

### views
views (aka slices, fat pointers) are lightweight structs that contain a pointer to a memory with additional properties of this memory. views serve as buildings blocks for data structures, therefore views are implemented with `struct` and have all their members public. views are non-owning, meaning they does not manage data they point to, they cannot allocate or deallocate memory by themselves.

```cpp
template <class T>
struct view;
```
a view over a contiguous and homogeneous area of memory
- readable / writable

```cpp
template <class T>
struct const_view;
```
a view over a contiguous and homogeneous area of memory
- read only

```cpp
struct buffer;
```
a view over a contiguous area of memory
- readable / writeable
- structurally equivalent to `view<unsigned char>`

```cpp
struct const_buffer;
```
a view over a contiguous area of memory
- read only
- structurally equivalent to `const_view<unsigned char>`

```cpp
struct str;
```
a string view (slice) that point to immutable sequence of characters
- read only
- not null terminated
- structurally equivalent to `view<const char>`

use cases:
- prefer `str` to `const char *`, as it's more convenient to work with sizes than work with raw pointers

### data structures
data structures are complex types derived from computer science. typically they provide user-friendly interface via methods to a complex logic, therefore data structures are implemented with `class` and have all their members private. data structures are owning types, meaning they manage data they point to, which include allocation and deallocation. data structures are building blocks for abstract data types. data structures can deduce to views.

```cpp
template <class T, size_t N>
class array;
```
an array.

```cpp
template <class T>
class dynamic_array;
```
a dynamic array.

todo:
```cpp
template <class... Types>
class tuple;
```
a tuple.

```cpp
template <class T>
class linked_list;
```
a linked list.

```cpp
template <class K, class V>
class hash_map;
```
a hash map (a map implemented by a hash table).

### abstract data types (ADTs)
abstract data types are types defined by their semantics. they are defined using c++ concepts and implemented using data structures. (todo)

## Other
guidelines for writing for this library: [guidelines.md](guidelines.md)
to-do list: [todo.md](todo.md)
