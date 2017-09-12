/*
 * SockOp.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ruanbo
 */

#include "SockOp.hpp"

namespace SockOp
{

bool set_options(int fd)
{
    int flags = ::fcntl(fd, F_GETFL, 0);
    if(flags == -1)
    {
        LogError("set nonblock : F_GETFL error");
        return false;
    }

    flags = flags | O_NONBLOCK;
    int ret = ::fcntl(fd, F_SETFL, flags);
    if(ret == -1)
    {
        LogError("set nonblock : F_SETFL error");
        return false;
    }

    int on = 1;
    ret = ::setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const char*)&on, sizeof(on));
    if(ret == -1)
    {
        LogError("setsockopt TCP_NODELAY failed");
        return false;
    }

    return true;
}

string peer_ip(int fd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, sizeof(addr));

    getpeername(fd, (struct sockaddr *)&addr, &len);

    return inet_ntoa(addr.sin_addr);
}

int tcp_listen(const string& ip, int port)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0)
    {
        LogError("SocketOp socket() failed");
        return -1;
    }

    sockaddr_in sock_addr;
    {
        bzero(&sock_addr, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = ip.empty()==true? INADDR_ANY : inet_addr(ip.c_str());
        sock_addr.sin_port = htons(port);
    }

    if(bind(sock_fd, (sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
    {
        LogError("SocketOp bind() failed, errno:%d", errno);
        close(sock_fd);
        return -1;
    }

    if(listen(sock_fd, SOMAXCONN) < 0)
    {
        LogError("SokcetOp listen() failed");
        close(sock_fd);
        return -1;
    }

    return sock_fd;
}

int conn_to(const string& ip, int port)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0)
    {
        return -1;
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr)); // 初始化服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    int ret = connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));      // 主动连接服务器
    if(ret == -1)
    {
        close(sock_fd);
        return -1;
    }

    if(set_options(sock_fd) == -1)
    {
        close(sock_fd);
        return -1;
    }

    return sock_fd;
}

}

