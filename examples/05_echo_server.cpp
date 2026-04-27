import std.io;
import std.net;
import std.string;

int main() {
    int sfd = socket(af_inet, sock_stream, 0)
        .unwrap_unsafe();

    /* we pass socket option value by reference and then get it's address inside wrapper */
    setsockopt(sfd, sol_socket, so_reuseaddr, 1)
        .unwrap_unsafe();

    /* host -> network byte order is done at sockaddr_in constructor */
    sockaddr_in addr = sockaddr_in(6767, 0);

    /* we know addr_size at compile time */
    bind(sfd, addr)
        .unwrap_unsafe();

    listen(sfd, 1)
        .unwrap_unsafe();

    sockaddr_in peer_addr;
    int cfd = accept(sfd, peer_addr)
        .unwrap_unsafe();

    string buf = string(128);
    for (;;) {
        /* read(int, string &) overload set string length to actual value returned by read */
        if (!read(cfd, buf))
            goto close;
        write(cfd, buf);
    }

close:
    close(cfd);
    close(sfd);

    return 0;
}

