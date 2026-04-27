import std.io;
import std.fs;
import std.string;

int main(int argc, char * argv[]) {
    if (argc < 2) {
        println("usage: ", argv[0], " <file>");
        return 1;
    }

    int fd = open(string(argv[1]), open_rdonly)
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

