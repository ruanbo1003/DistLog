/*
 * TcpOp.cpp
 *
 *      Author: ruanbo
 */

#include "TcpOp.hpp"

TcpOp::TcpOp()
{
}

TcpOp::~TcpOp()
{


}

bool TcpOp::init_server()
{
    return true;
}


bool TcpOp::init_client()
{


    return true;
}

int TcpOp::get_sockfd()const
{
    return _sock_fd;
}

void TcpOp::set_addr(const string& ip, int port)
{
    _ip_addr = ip;
    _ip_port = port;
}

bool TcpOp::init()
{

    return true;
}



void TcpOp::unit()
{

}

int TcpOp::epoll_wait()
{

    return 0;
}


int TcpOp::accept()
{

    return 1;
}

void TcpOp::close_op(int sock_fd)
{
}

int TcpOp::read()
{

    return 0;
}


int TcpOp::write()
{

    return 0;
}



int TcpOp::event_op()
{
    return 0;
}

void TcpOp::del_epev(int sock_fd)
{
}

bool TcpOp::add_epev(int sock_fd)
{

    return true;
}









