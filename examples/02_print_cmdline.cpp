import stdc;
import std.io;
import std.string;
import std.array;
import std.types;
import std.view;

int main(int argc, char * argv[], char * envp[]) {
    /* array is the std::vector analogue */
    auto args = array<str>(argc);

    while (args.count() < args.capacity())
        /* we can use unsafe / unchecked functions to improve performance
           here we are sure that length will not overflow capacity
           so we safely ignore capacity check */
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
        str key = str(env.data, idx);
        if (key == "USER"){
            println("user = ", str(key.end() + 1, env.size - idx));
            return 0;
        }
    }

    return 0;
}
