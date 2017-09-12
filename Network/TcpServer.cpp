/*
 * TcpServer.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ruanbo
 */

#include <Network/TcpServer.hpp>
#include "utils/SockOp.hpp"

TcpServer::TcpServer()
{
    _ip = "";
    _port = 0;
    _srv_fd = 0;
}

TcpServer::~TcpServer()
{
    uninit();
}

bool TcpServer::init(const string& ip, int port)
{
    _ip = ip;
    _port = port;

    if(_ip.length() <=0 || _port <= 0)
    {
        LogError("invalid server address[%s:%d]", _ip.c_str(), _port);
        return false;
    }

    _srv_fd = SockOp::tcp_listen(_ip, _port);
    if(_srv_fd < 0)
    {
        LogError("tcp socket() & listen() failed");
        return false;
    }

    return true;
}

void TcpServer::uninit()
{
    if(_srv_fd > 0)
    {
        close(_srv_fd);
        _srv_fd = 0;
    }
}










