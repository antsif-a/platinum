module;
#include <stddef.h>
#include <stdint.h>

export module stdc;

export extern "C" {
    #include <std/c/memory.h>
    #include <std/c/string.h>
    #include <std/c/byteswap.h>
    #include <std/c/network.h>
};

