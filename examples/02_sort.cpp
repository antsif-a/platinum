import std.array;
import std.algorithm;
import std.format;
import std.io;
import std.types;
import std.string;

template <class T, size_t N>
void print_array(array<T, N> &arr) {
    for (size_t i = 0; i < N; ++i) {
        string x = format(arr[i]);
        if (i == 0) {
            print("[", x, ", ");
        } else if (i == N - 1) {
            println(x, "]");
        } else {
            print(x, ", ");
        }
    }
}

int main() {
    array<int, 10> arr { 5, 4, 3, 2, 0, 1, 6, 7, 8, 9 };
    print_array(arr);
    sort(arr);
    print_array(arr);
    return 0;
}
