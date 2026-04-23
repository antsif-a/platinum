import std.io;
import std.string;

int main() {
    string buf = string(128);
    for (print("> "); input(buf).expect("can't read"); print("> "))
        print(buf);
    println();
    return 0;
}
