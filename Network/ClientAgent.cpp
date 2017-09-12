/*
 * TcpClient.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ruanbo
 */

#include <Network/ClientAgent.hpp>

ClientAgent::ClientAgent()
{
    _type = CT_Null;
    _status = Login_UnConnected;
    _node_id = -1;
    _cli_fd = -1;
    _ip = "";
    _port = 0;
}

ClientAgent::~ClientAgent()
{

}

void ClientAgent::setid(int id)
{
    _node_id = id;
}
void ClientAgent::set_addr(const string& ip, int port, int fd)
{
    _ip = ip;
    _port = port;
    _cli_fd = fd;
}
void ClientAgent::reset()
{
    _type = CT_Null;
    _status = Login_UnConnected;
    _node_id = -1;
    _cli_fd = -1;
    _ip = "";
    _port = -1;
}

void ClientAgent::set_type(ClientType type)
{
    _type = type;
}

void ClientAgent::set_status(LoginStatus status)
{
    _status = status;
}

bool ClientAgent::is_verified()
{
    return (_type != CT_Null);
}

bool ClientAgent::is_node()
{
    return (_type == CT_FromServer || _type == CT_ToServer);
}

bool ClientAgent::has_msg()
{
    if(_rbuff.data_size() <= 4)
    {
        return false;
    }

    size_t msg_len = 0;
    if(_rbuff.read_begin((char*)&msg_len, sizeof(int)) == false)
    {
        return false;
    }

    if(_rbuff.data_size() < msg_len)
    {
        return false;
    }

    return true;
}

bool ClientAgent::parse_data(MsgHead* msg)
{
    msg->fromdata(_rbuff);

    return true;
}








