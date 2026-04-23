set_toolchains('fasm', 'gcc')
set_policy("build.c++.modules.std", false)
set_policy("build.optimization.lto", true)
set_optimize("fastest")

add_cxflags(
    '-Wall', '-Wextra', '-Werror', '-Wno-main', '-Wno-reserved-module-identifier',
    '-ggdb',
    '-fno-asynchronous-unwind-tables', '-fno-unwind-tables',
    '-ffunction-sections', '-fdata-sections',
    '-fno-exceptions', '-fno-stack-protector',
    '-fno-strict-aliasing',
    '-fno-builtin'
)

add_cxxflags(
    '-fno-rtti', '-fno-exceptions',
    {force = true}
)

add_ldflags(
    '-nostdlib', '-nostdlib++',
    '-static',
    '-Wl,--gc-sections',
    '-Wl,--build-id=none',
    {force = true}
)
add_ldflags('-Wl,-z,noseparate-code', '-Wl,-z,norelro')

target('std')
    set_kind('static')
    set_languages('c99', 'c++20')
    add_files(
        'source/std/c/memory.c',
        'source/std/c/string.c',
        'source/std/c/array.c',
        'source/std/c/module.cppm',
        'source/std/types.cppm',
        'source/std/sys.cppm',
        'source/std/sys-error.cppm',
        'source/std/string.cppm',
        'source/std/array.cppm',
        'source/std/view.cppm',
        'source/std/io.cppm',
        'source/std/memory.cppm',
        'source/std/math.cppm',
        'source/std/result.cppm',
        'source/std/panic.cppm',
        {public = true}
    )
    add_files(
        'source/std/memory.cpp'
    )
    add_includedirs(
        'source/',
        {public = true}
    )

target('rt')
    set_kind('static')
    set_languages('c++20')
    add_deps('std')
    add_files(
        'source/rt/_start.cpp',
        'source/rt/_start.asm'
    )

function example_target(name)
    target(name)
    set_kind('binary')
    set_languages('c++20')
    add_deps('rt', 'std')
    add_files(
        'examples/'..name..'.cpp'
    )
end

example_target('01_hello_world')
example_target('02_print_cmdline')
example_target('02_print_int')
example_target('03_print_file')
example_target('04_echo')
