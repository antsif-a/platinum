import stdc;
import std.io;
import std.string;
import std.array;
import std.types;
import std.view;

int main(size_t argc, char * argv[], char * envp[]) {
    auto args = array<str>(argc);
    while (args.count() < args.capacity())
        args.push_back_unchecked(argv[args.count()]); 

    auto envs = array<str>(arrlen((void **) envp));
    while (envs.count() < envs.capacity())
        envs.push_back_unchecked(envp[envs.count()]);

    print("cmdline: ");
    println(const_view<str>(args));

    for (str env : envs) {
        int idx = env.find('=').or_else(-1);
        if (idx == -1)
            continue;
        auto key = str(env.data, idx);
        if (key == "USER"){
            println("user = ", str(key.end() + 1, env.size - idx));
            return 0;
        }
    }

    return 0;
}
