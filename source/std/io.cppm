export module std.io;

import std.result;
import std.types;
import std.view;
import std.sys;
import std.string;

export {
    result<size_t, sys::error> read(int fd, buffer buf) {
        ssize_t ret = sys::read(fd, buf.data, buf.size);
        if (ret < 0) {
            return static_cast<sys::error>(-ret);
        } else {
            return static_cast<size_t>(ret);
        }
    }

    result<size_t, sys::error> write(int fd, str st) {
        ssize_t ret = sys::write(fd, st.data, st.size);
        if (ret < 0) {
            return static_cast<sys::error>(-ret);
        } else {
            return static_cast<size_t>(ret);
        }
    }

    void writeln(int fd) {
        write(fd, "\n");
    }

    void writeln(int fd, str st) {
        write(fd, st);
        writeln(fd);
    }

    void print(str st) {
        write(sys::stdout, st);
    }

    void println() {
        writeln(sys::stdout);
    }

    void println(str st) {
        writeln(sys::stdout, st);
    } 

    result<int, sys::error> open(string path, int flags, mode_t mode) {
        int ret = sys::open(path.c_str(), flags, mode);
        if (ret < 0) {
            return static_cast<sys::error>(-ret);
        } else {
            return ret;
        }
    }
}
