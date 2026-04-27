export module std.fs;

import std.sys;
import std.result;
import std.types;
import std.string;
import std.posix;

export {
    using enum sys::open_flag;
    using enum sys::open_mode;

    inline sys::result<int> open(const string &path, sys::open_flag flags, sys::open_mode mode) {
        return sys::make_result<int>(
                sys::open(
                    path.c_str(),
                    to_underlying(flags),
                    to_underlying(mode)
                )
        );
    } 

    inline sys::result<int> open(const string &path, sys::open_flag flags) {
        return sys::make_result<int>(
                sys::open(
                    path.c_str(),
                    to_underlying(flags),
                    0
                )
        );
    } 
    using file_status = struct sys::stat;

    inline sys::result<int> stat(const string &path, file_status &statbuf) {
        return sys::make_result<int>(sys::stat(path.c_str(), &statbuf));
    }

    inline sys::result<int> fstat(int fd, file_status &statbuf) {
        return sys::make_result<int>(sys::fstat(fd, &statbuf));
    }

    inline sys::result<int> lstat(const string &path, file_status &statbuf) {
        return sys::make_result<int>(sys::lstat(path.c_str(), &statbuf));
    }
};
