import stdc;
import std.map;
import std.view;
import std.io;
import std.types;
import std.algorithm;
import std.format;

size_t envc(char * envp[]) {
    size_t i = 0;
    while (envp[i])
        ++i;
    return i;
}

int main(int, char * [], char * envp[]) {
    flat_map<str, str> env(envc(envp));
    for (size_t i = 0; envp[i] != nullptr; ++i) {
        str entry = str(envp[i]);
        int eq_index = find(entry, '=').or_else(-1);
        if (eq_index == -1)
            continue;

        env.put(
            str(entry.data, eq_index),
            str(entry.data + eq_index + 1, entry.size - eq_index)
        );
    }


    println("user = ", * env.get("USER").expect("no value"));
}
