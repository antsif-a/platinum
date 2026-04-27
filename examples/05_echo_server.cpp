import stdc;
import std.io;
import std.net;
import std.string;

int main() {
    int sfd = socket(af_inet, sock_stream, 0)
        .unwrap_unsafe();

    setsockopt(sfd, sol_socket, so_reuseaddr, 1)
        .unwrap_unsafe();

    sockaddr_in addr;
    addr.sin_family        = af_inet;
    addr.sin_port          = htons(6767);
    addr.sin_addr.s_addr   = htonl(0);

    bind(sfd, addr)
        .unwrap_unsafe();

    listen(sfd, 1)
        .unwrap_unsafe();

    sockaddr_in peer_addr;
    int cfd = accept(sfd, peer_addr)
        .unwrap_unsafe();

    string buf = string(128);
    for (;;) {
        if (!read(cfd, buf))
            goto close;
        write(cfd, buf);
    }

close:
    close(cfd);
    close(sfd);

    return 0;
}

