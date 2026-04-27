export module std.net;

import stdc;
import std.types;
import std.result;
import std.posix;
import std.sys;

export {
    using enum sa_family;
    using enum socket_type;
    using enum socket_level;
    using enum socket_option;

    using sockaddr_in = sockaddr_in;

    sys::result<int> socket(sa_family_t family, int type, int protocol) {
        return sys::make_result<int>(sys::socket(family, type, protocol));
    }

    sys::result<int> accept(int fd, sockaddr_in &peer_addr) {
        socklen_t peer_addrlen = sizeof(sockaddr_in);
        return sys::make_result<int>(sys::accept(fd, (sockaddr *) &peer_addr, &peer_addrlen));
    }

    sys::result<int> bind(int fd, const sockaddr_in &addr) {
        return sys::make_result<int>(sys::bind(fd, (const sockaddr *) &addr, sizeof(sockaddr_in)));
    }

    sys::result<int> listen(int fd, int backlog) {
        return sys::make_result<int>(sys::listen(fd, backlog));
    }

    template <class T>
    sys::result<int> setsockopt(int fd, int level, int optname, const T &optref) {
        return sys::make_result<int>(sys::setsockopt(fd, level, optname, &optref, sizeof(T)));
    }
};
