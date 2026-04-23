export module std.io;

import std.result;
import std.types;
import std.view;
import std.sys;
import std.string;
import std.array;

export {
    using enum sys::stdio;

    inline sys::result<size_t> read(int fd, const buffer buf) {
        return sys::make_result<size_t>(sys::read(fd, buf.data, buf.size));
    }

    inline sys::result<size_t> read(int fd, string &st) {
        auto res = sys::make_result<size_t>(sys::read(fd, st.data(), st.capacity()));
        if (!res)
            return res;
        st.set_length_unsafe(res.value);
        st[res.value] = '\0';
        return res;
    }

    inline sys::result<size_t> write(int fd, str st) {
        return sys::make_result<size_t>(sys::write(fd, st.data, st.size));
    }

    inline sys::result<size_t> write(int fd, const const_view<str> arr) {
        const size_t n = arr.size;

        if (n == 0)
            return 0;
        if (n == 1)
            return write(fd, arr[0]);

        sys::iovec iov[n];
        for (size_t i = 0; i < n; ++i) {
            iov[i].iov_base = (void *) arr[i].data;
            iov[i].iov_len  = arr[i].size;
        }

        return sys::make_result<size_t>(sys::writev(fd, iov, n));
    }

    template <typename... Args>
    inline sys::result<size_t> write(int fd, Args const &...args) {
        constexpr size_t n = sizeof...(Args);

        if constexpr (n == 0)
            return 0;

        if constexpr (n == 1)
            return write(fd, str(args)...);

        str stv[n] = { args... };
        sys::iovec iov[n];
        for (size_t i = 0; i < n; ++i) {
            iov[i].iov_base = (void *) stv[i].data;
            iov[i].iov_len  = stv[i].size;
        }

        return sys::make_result<size_t>(sys::writev(fd, iov, n));
    }

    inline sys::result<size_t> writeln(int fd, const const_view<str> arr) {
        const size_t n = arr.size;

        if (n == 0)
            return write(fd, str("\n"));

        sys::iovec iov[n + 1];
        for (size_t i = 0; i < n; ++i) {
            iov[i].iov_base = (void *) arr[i].data;
            iov[i].iov_len  = arr[i].size;
        }
        iov[n].iov_base = (void *) "\n";
        iov[n].iov_len  = 1;

        return sys::make_result<size_t>(sys::writev(fd, iov, n + 1));
    }

    template <typename... Args>
    inline sys::result<size_t> writeln(int fd, Args const &...args) {
        return write(fd, args..., str("\n"));
    }

    template <typename ...Args>
    inline sys::result<size_t> print(Args const &...args) {
        return write(stdout, args...);
    }

    inline sys::result<size_t> println(const const_view<str> arr) {
        return writeln(stdout, arr);
    }

    template <typename ...Args>
    inline sys::result<size_t> println(Args const &...args) {
        return writeln(stdout, args...);
    } 

    inline sys::result<size_t> input(const buffer buf) {
        return read(stdin, buf);
    }

    inline sys::result<size_t> input(string &st) {
        return read(stdin, st);
    }

    using enum sys::open_flag;
    using enum sys::open_mode;

    inline sys::result<int> open(const string &path, int flags, mode_t mode) {
        return sys::make_result<int>(sys::open(path.c_str(), flags, mode));
    }

    inline sys::result<int> close(int fd) {
        return sys::make_result<int>(sys::close(fd));
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
}
