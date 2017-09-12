/*
 * NetMngr.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ruanbo
 */

#include <Network/NetMngr.hpp>
#include "utils/SockOp.hpp"

#include <sys/time.h>


NetMngr::NetMngr()
{
    _nowms = 0;
    _beattime = 0;
}

NetMngr::~NetMngr()
{

}


bool NetMngr::init_nodes()
{
    for(int i=0; i<SERVER_NODES; ++i)
    {
        _nodes[i] = NULL;
        _node_conn_times[i] = 0;
    }

    _conn_interval = 1000;  // 1000 ms

    return true;
}

bool NetMngr::init(const Config& config)
{
    _config = config;

    update_nowms();

    srand(time(NULL));

    if(_vote.init(nowms()) == false)
    {
        LogError("void init failed");
        return false;
    }

    if(_log.init() == false)
    {
        LogError("debug log file failed");
        return false;
    }

    if(_epoll.init() == false)
    {
        LogError("epoll init failed");
        return false;
    }

    if(_server.init(_config.get_ip(), _config.get_port()) == false)
    {
        LogError("server init failed");
        return false;
    }

    if(_epoll.epoll_add(_server._srv_fd) == false)
    {
        LogError("add server sock fd to epoll failed");
        return false;
    }

    init_pool();

    init_nodes();

    init_msg_handlers();

    heart_beat_now();

    ToLog("server node %d listen on %s:%d\n", _config._myid, _config.get_ip().c_str(), _config.get_port());

    return true;
}

void NetMngr::uninit()
{
    if(_server._srv_fd > 0 && _epoll.iswork()==true )
    {
        _epoll.epoll_del(_server._srv_fd);
    }

    _epoll.uninit();

    _server.uninit();

    while(_clients.empty() == false)
    {
        auto it = _clients.begin();
        ClientAgent* c = it->second;

        delete c;
        c = NULL;

        _clients.erase(it);
    }
    _clients.clear();

    for(int i=0; i<SERVER_NODES; ++i)
    {
        _nodes[i] = NULL;
    }

    clean_pool();
}

void NetMngr::on_accept()
{
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    socklen_t addr_len = sizeof(addr);
    int conn_fd = accept4(_server._srv_fd, (sockaddr*) &addr, &addr_len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if(conn_fd < 0)
    {
        LogError("socket accept() failed, errno:%d", errno);
        return;
    }

    if(SockOp::set_options(conn_fd) == false)
    {
        LogError("new connection set_options failed, errno:%d", errno);
        close(conn_fd);
        return;
    }

    if(_epoll.epoll_add(conn_fd) == false)
    {
        LogError("add new connection to epoll failed, errno:%d", errno);
        close(conn_fd);
        return;
    }

    ClientAgent *client = get_inst();
    string conn_ip = inet_ntoa(addr.sin_addr);
    client->set_addr(conn_ip, addr.sin_port, conn_fd);

    _clients[client->_cli_fd] = client;

    Log("new connectio from:%s", conn_ip.c_str());
}

void NetMngr::on_read(int fd)
{
    _buff.clean_data();
    int loop_read_size = 0;
    ssize_t read_size = 0;

    while (true)
    {
        read_size = WR_BUFF_SIZE - loop_read_size;
        ssize_t read_ret = ::read(fd, _buff.data() + loop_read_size, read_size);

        if(read_ret < 0)
        {
            if(errno == EAGAIN || errno == EWOULDBLOCK)
            {
                break;
            }
            else if(errno == EINTR)
            {
                continue;
            }
            else
            {
                on_close(fd);
                break;
            }
        }
        else if(read_ret == 0)
        {
            on_close(fd);
            break;
        }
        else
        {
            loop_read_size += read_ret;
        }
    }

    if(loop_read_size > 0)
    {
        string peer_ip = SockOp::peer_ip(fd);
//        Log("receive msg[len:%d] from[%s]", loop_read_size, peer_ip.c_str());

        ClientAgent *client = get_client(fd);
        if(client)
        {
            client->_rbuff.add_data(_buff.data(), loop_read_size);

            _datain.push_back(client);
        }
    }
}

void NetMngr::to_write(int fd, size_t len)
{
    size_t wt_len = 0;
    size_t one_len = 0;

    while(wt_len < len)
    {
        if(len - wt_len > _buff.buff_size())
        {
            one_len = _buff.buff_size();
        }
        else
        {
            one_len = len - wt_len;
        }

        int w_ret = ::write(fd, _buff.data()+wt_len, one_len);

        if(w_ret == 0)
        {
            on_close(fd);
            return;
        }
        else if(w_ret < 0)
        {
            if(errno == EINTR)
            {
                continue;
            }
            else if(errno == EAGAIN || errno == EWOULDBLOCK)
            {
                continue;
            }
            else
            {
                on_close(fd);
                return;
            }
        }

        wt_len += one_len;
    }
}

void NetMngr::on_close(int fd)
{
    Log("a connection closed");
    _epoll.epoll_del(fd);
    close(fd);

    auto it = _clients.find(fd);
    if(it == _clients.end())
    {
        return;
    }

    ClientAgent* node = it->second;

    if(node->is_node())
    {
        node_close(node);
    }

    _clients.erase(fd);

    pool_recycle(node);
}

void NetMngr::node_close(ClientAgent* node)
{
    Log("node[%d] disconnect from node[%d]", node->_node_id, _config._myid);

    if(is_leader(node->_node_id) == true)
    {
        leader_down();
    }

    _nodes[node->_node_id] = NULL;
}

ClientAgent* NetMngr::get_client(int fd)
{
    auto it = _clients.find(fd);
    if(it != _clients.end())
    {
        return it->second;
    }

    return NULL;
}

void NetMngr::net_loop()
{
    conn_node();

    epool_event();

    handle_data();

//    sent_data();

//    net_tests();

    update_nowms();

    sent_beat();

    check_vote_timeout();
}

void NetMngr::epool_event()
{
    int ev_num = _epoll.wait(5);   // 200

    for(int i=0; i<ev_num; ++i)
    {
        epoll_event & cur_ev = _epoll._evs[i];

        int sock_fd = cur_ev.data.fd;
        if(sock_fd == _server._srv_fd)
        {
             on_accept();
        }
        else
        {
            if(cur_ev.events & EPOLLIN || cur_ev.events & EPOLLPRI)
            {
                on_read(sock_fd);
            }
        }
    }
}


int NetMngr::try_conn(const string& ip, int port)
{
    return SockOp::conn_to(ip, port);
}

void NetMngr::conn_node()
{
    for(int i=0; i<_config._myid; ++i)
    {
        if(_nodes[i])
        {
            //已经连接上了
            continue;
        }

        if(nowms() - _node_conn_times[i] < _conn_interval)
        {
            // 重试间隔时间没到
            continue;
        }

        string ip = _config.get_ip(i);
        int port = _config.get_port(i);
        int cli_fd = try_conn(ip, port);

        _node_conn_times[i] = nowms();

        if(cli_fd < 0)
        {
            Log("node[%d] connect to node[%d](%s:%d) failed", _config._myid, i, ip.c_str(), port);
            continue;
        }

        if(_epoll.epoll_add(cli_fd) == false)
        {
            LogError("add new connection to epoll failed, errno:%d", errno);
            close(cli_fd);
            return;
        }

        ClientAgent *node = get_inst();
        node->set_addr(ip, port, cli_fd);
        node->set_type(CT_ToServer);
        node->setid(i);
        node->set_status(Login_UnVerify);

        _clients[cli_fd] = node;
        _nodes[i] = node;

        req_login(node);

        Log("node[%d] connect to node[%d] successed\n", _config._myid, i);
    }
}

void NetMngr::handle_data()
{
    for(auto & client : _datain)
    {
        parse_data(client);
    }

    _datain.clear();
}

void NetMngr::parse_data(ClientAgent* client)
{
    while(client->has_msg() == true)
    {
        MsgHead* msg = parse_msg(client);

        handler_msg(client, msg);
    }
}

MsgHead* NetMngr::parse_msg(ClientAgent* client)
{
    char tmp[8] = { 0 };
    client->_rbuff.read_begin(tmp, 8);
    int msgid = 0;
    memcpy(&msgid, tmp+4, 4);

    MsgHead* msg = _genmsg.to_msg((MsgIdDef)msgid);
    if(!msg)
    {
        LogError("gen a client msg failed");
        return NULL;
    }

    client->parse_data(msg);

    return msg;
}

void NetMngr::sent_data()
{
    for(auto &client : _clients)
    {
        sent_login(client.second);
    }
}

void NetMngr::on_send(ClientAgent* client, MsgHead* msg)
{
    size_t pkg_len = msg->todata(_buff.data());

    to_write(client->_cli_fd, pkg_len);

    if(msg->msgid() == MsgId_Vote)
    {
        ToLog("node[%d] send propose to node[%d]", _config._myid, client->_node_id);
    }
    else if(msg->msgid() == MsgId_VoteRsp)
    {
        MsgVoteRsp* rsp = dynamic_cast<MsgVoteRsp*>(msg);
        ToLog("node[%d] anster vote to node[%d] (%d,%d)", _config._myid, client->_node_id, rsp->_answer, rsp->_id);
    }
}

void NetMngr::sendto_nodes(MsgHead* msg)
{
    for(size_t i=0; i<_config._node_cnt; ++i)
    {
        if(i == (size_t)_config._myid)
        {
            continue;
        }

        if(!_nodes[i])
        {
            continue;
        }

        if(_nodes[i]->_status != Login_Verified)
        {
            continue;
        }

        on_send(_nodes[i], msg);
    }
}

void NetMngr::sent_login(ClientAgent* client)
{
    MsgLogin msg;
    msg._id = _config._myid;

    on_send(client, (MsgHead*)&msg);
}

long int NetMngr::nowms()
{
    return _nowms;
}

void NetMngr::sent_beat()
{
    if(iam_leader() == true)
    {
        // leader 发送心跳包
        MsgHeartbeat msg;
        sendto_nodes(&msg);

        heart_beat_now(); //leader也更新自己的心跳时间
    }
}

void NetMngr::heart_beat_now()
{
    _beattime = nowms();
}

bool NetMngr::is_beat_timeout()
{
    return _vote.timeout(nowms() - _beattime);
}

bool NetMngr::is_propose_timeout()
{
    return _vote.timeout(nowms() - _vote._propose_time);
}

bool NetMngr::is_vote_timeout()
{
    return _vote.timeout(nowms() - _vote._vote_time);
}

void NetMngr::update_nowms()
{
    timeval tv;
    gettimeofday(&tv, NULL);

    _nowms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}




