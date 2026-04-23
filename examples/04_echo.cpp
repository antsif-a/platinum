import std.io;
import std.types;
import std.view;
import std.array;
import std.string;
import std.sys;

int main() {
    auto arr = tuple<char, 128>();
    
    for (;;) {
        print("> ");
        auto read_size = input(arr);
        if (!read_size) {
            string errcode = format((int) read_size.error); 
            print("failed to read, error code is");
            println(errcode);
        } else {
            println(str(arr.data(), read_size.value - 1));
        }
    }

    return 0;
}
