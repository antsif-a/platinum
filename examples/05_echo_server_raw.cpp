import stdc;
import std.sys;
import std.posix;
import std.string;
import std.io; // println

#define LISTEN_BACKLOG 50

const int so_reuseaddr_value = 1;

int main() {
    int sfd = sys::socket(af_inet, sock_stream, 0);
    sys::setsockopt(sfd, sol_socket,
            so_reuseaddr, &so_reuseaddr_value, sizeof(so_reuseaddr_value));
    if (sfd < 0) {
        println("sfd == -1");
        return 1;
    }

    sockaddr_in addr;
    addr.sin_family        = af_inet;
    addr.sin_port          = htons(6767);
    addr.sin_addr.s_addr   = htonl(0);

    if (sys::bind(sfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        println("bind == -1");
        return 1;
    }

    if (sys::listen(sfd, LISTEN_BACKLOG) == -1) {
        println("listen == -1");
        return 1;
    }

    sockaddr_in peer_addr;
    socklen_t   peer_addr_size = sizeof(peer_addr);

    int cfd = sys::accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
    if (cfd < 0) {
        println("cfd == -1");
        return 1;
    }

    string buf = string(128);
    for (;;) {
        ssize_t n = sys::read(cfd, buf.data(), buf.capacity());
        if (n <= 0)
            goto close;
        buf.set_length_unsafe(n);
        sys::write(cfd, buf.data(), buf.length());
    }

close:
    sys::close(cfd);
    sys::close(sfd);
    return 0;
}

