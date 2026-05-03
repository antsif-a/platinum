import std.types;
import std.view;
import std.array;
import std.algorithm;
import std.io;

size_t envc(char * envp[]) {
    size_t i = 0;
    while (envp[i])
        ++i;
    return i;
}

int main(int argc, char * argv[], char * envp[]) {
    auto args = fixed_array<str>(argc);
    for (int i = 0; i < argc; ++i)
        args[i] = str(argv[i]);

    auto envs = fixed_array<str>(envc(envp));
    for (size_t i = 0; i < size(envs); ++i)
        envs[i] = str(envp[i]);

    print("cmdline: ");
    println(args);

    for (str env : envs) {
        int idx = find(env, '=').or_else(-1);
        if (idx == -1)
            continue;
        str key = str(env.data, idx);
        if (key == "USER"){
            println("user = ", str(env.data + idx + 1, env.size - idx));
            return 0;
        }
    }

    return 0;
}
