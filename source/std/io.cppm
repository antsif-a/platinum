export module std.io;

import std.sys;
import std.result;
import std.types;
import std.view;
import std.string;
import std.array;

export {
    using enum sys::stdio;

    /* --- read --- */
    inline sys::result<size_t> read(int fd, const buffer buf) {
        return sys::make_result<size_t>(sys::read(fd, buf.data, buf.size));
    }

    inline sys::result<size_t> read(int fd, string &st) {
        auto res = sys::make_result<size_t>(sys::read(fd, st.data(), st.capacity()));
        if (!res)
            return res;
        st.set_length_unsafe(res.value);
        return res;
    }

    /* --- input --- */
    inline sys::result<size_t> input(const buffer buf) {
        return read(stdin, buf);
    }

    inline sys::result<size_t> input(string &st) {
        return read(stdin, st);
    } 

    /* --- write --- */
    inline sys::result<size_t> write(int fd, str st) {
        return sys::make_result<size_t>(sys::write(fd, st.data, st.size));
    }

    inline sys::result<size_t> write(int fd, const const_view<str> arr) {
        if (arr.size == 0)
            return 0;

        if (arr.size == 1)
            return write(fd, arr[0]);

        return sys::make_result<size_t>(
            // we can avoid copy because const_iovec is equivalent to const_view<str>@data
            sys::writev(fd, reinterpret_cast<const sys::const_iovec *>(arr.data), arr.size)
        );
    }

    template <typename... T> requires (convertible_to<T, str> && ...)
    constexpr sys::result<size_t> write(int fd, T const &...args) {
        constexpr size_t n = sizeof...(T);

        if constexpr (n == 0)
            return 0;

        if constexpr (n == 1)
            return write(fd, str(args)...);

        // no allocation or construction is done here, this function is constexpr
        str stv[n] = { args... };
        sys::const_iovec iov[n];
        for (size_t i = 0; i < n; ++i) {
            iov[i].iov_base = stv[i].data;
            iov[i].iov_len  = stv[i].size;
        }

        return sys::make_result<size_t>(sys::writev(fd, iov, n));
    }

    /* --- writeln --- */
    inline sys::result<size_t> writeln(int fd, const const_view<str> arr) {
        const size_t n = arr.size;

        if (n == 0)
            return write(fd, "\n");

        // allocation and copying is only done here,
        // but it's cheaper than another syscall
        sys::const_iovec iov[n];
        for (size_t i = 0; i < n; ++i) {
            iov[i].iov_base = arr[i].data;
            iov[i].iov_len  = arr[i].size;
        }
        iov[n].iov_base = "\n";
        iov[n].iov_len  = 1;

        return sys::make_result<size_t>(sys::writev(fd, iov, n + 1));
    }

    template <typename... T> requires (convertible_to<T, str> && ...)
    constexpr sys::result<size_t> writeln(int fd, T const &...args) {
        return write(fd, args..., str("\n"));
    }

    /* --- print --- */
    template <typename ...T> requires (convertible_to<T, str> && ...)
    constexpr sys::result<size_t> print(T const &...args) {
        return write(stdout, args...);
    }

    /* --- println --- */
    inline sys::result<size_t> println(const const_view<str> arr) {
        return writeln(stdout, arr);
    }

    template <typename ...T> requires (convertible_to<T, str> && ...)
    constexpr sys::result<size_t> println(T const &...args) {
        return writeln(stdout, args...);
    }  

    /* --- close --- */
    inline sys::result<int> close(int fd) {
        return sys::make_result<int>(sys::close(fd));
    }
}
