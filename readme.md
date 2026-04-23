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
