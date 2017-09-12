/*
 * TcpClient.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ruanbo
 */

#ifndef CLIENTAGENT_HPP_
#define CLIENTAGENT_HPP_

#include "comm/comm.hpp"

#include "NetComm.hpp"
#include "Msg/MsgHead.hpp"

enum LoginStatus
{
    Login_UnConnected = 0,
    Login_Connected = 1,
    Login_UnVerify = 2,
    Login_Verified = 3
};


class ClientAgent
{
public:
    ClientType _type;
    LoginStatus _status;
    int _node_id;
    int _cli_fd;
    string _ip;
    int _port;

    RingBuff _rbuff;

public:
    ClientAgent();
    virtual ~ClientAgent();

public:
    void setid(int id);
    void set_addr(const string& ip, int port, int fd);
    void reset();

public:
    void set_type(ClientType type);
    void set_status(LoginStatus type);
    bool is_verified();

    //是否是服务节点
    bool is_node();
public:
    bool has_msg();

    bool parse_data(MsgHead* msg);
};



#endif /* CLIENTAGENT_HPP_ */



