import std.sys;
import std.types;
import std.io;
import std.string;
import std.result;

int main(int argc, char * argv[]) {
    if (argc < 2) {
        print("usage: ");
        print(argv[0]);
        print(" <file>");
        println();
        return 1;
    }

    int fd = ::open(string(argv[1]), sys::open_rdonly, 0)
        .expect("couldn't open file");

    sys::stat_info statbuf;
    sys::fstat(fd, &statbuf);
    string st = string(statbuf.st_size);

    ::read(fd, st);
    ::print(st);
    return 0;
}

