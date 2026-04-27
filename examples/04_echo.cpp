import std.io;
import std.string;

int main() {
    string buf = string(128);
    /* loop will exit when input() returns zero or error is emitted.
       again, we pass string::capacity to read, but string::length to write */
    for (print("> "); input(buf).expect("can't read"); print("> "))
        print(buf);
    println();
    return 0;
}
