import std.io;
import std.fs;
import std.string;

int main(int argc, char * argv[]) {
    if (argc < 2) {
        /* string literals and common char arrays implicitly converted to "str" views */
        println("usage: ", argv[0], " <file>");
        return 1;
    }

    /* third argument of open - open mode - can be omitted
       if neither open_creat nor open_tmpfile is specified in flags */
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

