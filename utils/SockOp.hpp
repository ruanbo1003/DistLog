/*
 * SockOp.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ruanbo
 */

#ifndef SOCKOP_HPP
#define SOCKOP_HPP

#include "comm/comm.hpp"

#include <sys/ioctl.h>
#include <netinet/if_ether.h> // arpreq
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  // addrinfo
#include <fcntl.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>   //bzero()
#include <unistd.h>   // close()
#include <errno.h>
#include <sys/epoll.h>   //epoll

namespace SockOp
{

bool set_options(int fd);

string peer_ip(int fd);

int tcp_listen(const string& ip, int port);

int conn_to(const string& ip, int port);

}

#endif


