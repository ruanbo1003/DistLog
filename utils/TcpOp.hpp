/*
 * TcpOp.hpp
 *
 *      Author: ruanbo
 */

#ifndef UTIL_TCPOP_HPP_
#define UTIL_TCPOP_HPP_


#include "comm/global.hpp"
#include "EpollOp.hpp"


class TcpOp : public NonCopyable
{
public:
    int _sock_fd;    // SERVER:监听 socket fd， CLIENT:连接的服务端的 socket fd

    string _ip_addr;
    int _ip_port;   // SERVER:监听的地址，端口， CLIENT:要连接的服务端地址，端口

public:
    TcpOp();
    virtual ~TcpOp();

private:
    bool init_server();
    bool init_client();

public:
    int get_sockfd()const;
    void set_addr(const string& ip, int port);

    bool init();
    void unit();

public:
    int epoll_wait();

    int accept();

    void close_op(int sock_fd);
    int read();
    int write();

    int event_op();
    void del_epev(int sock_fd);
    bool add_epev(int sock_fd);
};


#endif /* UTIL_TCPOP_HPP_ */
