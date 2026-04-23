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
file size is 672 bytes (after strip):
```
$ stat --printf="%s\n" ./build/linux/x86_64/release/01_hello_world
672
```
and output assembly is relatively clean and short:
```
$ objdump -SMintel --no-show-raw-insn ./build/linux/x86_64/release/01_hello_world
./build/linux/x86_64/release/01_hello_world:     file format elf64-x86-64
Disassembly of section .text:
00000000004000b0 <.text>:
  4000b0:       lea    rsi,[rsp-0x28]
  4000b5:       mov    edi,0x1
  4000ba:       mov    edx,0x2
  4000bf:       mov    QWORD PTR [rsp-0x20],0xc
  4000c8:       mov    QWORD PTR [rsp-0x10],0x1
  4000d1:       lea    rax,[rip+0x3a]        # 0x400112
  4000d8:       mov    QWORD PTR [rsp-0x28],rax
  4000dd:       lea    rax,[rip+0x3b]        # 0x40011f
  4000e4:       mov    QWORD PTR [rsp-0x18],rax
  4000e9:       mov    eax,0x14
  4000ee:       syscall
  4000f0:       xor    eax,eax
  4000f2:       ret
  4000f3:       nop    DWORD PTR [rax+rax*1+0x0]
  4000f8:       pop    rdi
  4000f9:       mov    rsi,rsp
  4000fc:       lea    rdx,[rsp+rdi*8+0x8]
  400101:       call   0x4000b0
  400106:       mov    rdi,rax
  400109:       mov    rax,0x3c
  400110:       syscall
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
