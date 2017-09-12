/*
 * TcpServer.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ruanbo
 */

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_


#include "comm/comm.hpp"
#include <netinet/in.h>


class TcpServer : public NonCopyable
{
public:
    string _ip;
    int _port;

    int _srv_fd;

private:


public:
    TcpServer();
    virtual ~TcpServer();

public:
    bool init(const string& ip, int port);

    void uninit();
};

#endif /* TCPSERVER_HPP_ */




