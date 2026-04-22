int main(...);

extern "C" int _start_cpp(int argc, char * argv[], char * envp[]) {
    return main(argc, argv, envp);
}
