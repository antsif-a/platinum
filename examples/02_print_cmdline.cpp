import std.io;
import std.string;
import std.array;
import std.types;
import std.view;

int main(int argc, char * argv[], char * envp[]) {
    auto args = array<str>(argc);
    for (int i = 0; i < argc; ++i) {
        args.push(str(argv[i]));
    }

    auto env = array<str>(arrlen(envp));
    for (size_t i = 0; i < env.capacity(); ++i) {
        env.push(str(envp[i]));
    }

    print("cmdline: ");
    for (str arg : args) {
        print(arg);
        print(" ");
    }
    println();

    for (str env_str : env) {
        auto idx = env_str.find('=');
        if (idx.error == str::error::not_found)
            continue;
        auto key = str(env_str.data, *idx);
        if (key == "USER"){
            print("user = ");
            println(str(key.end() + 1));
        }
    }

    return 0;
}
