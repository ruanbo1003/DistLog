/*
 * NetMngr.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ruanbo
 */

#ifndef NETMNGR_HPP_
#define NETMNGR_HPP_

#include <Network/ClientAgent.hpp>
#include "comm/comm.hpp"
#include "Msg/MsgComm.hpp"
#include "NetComm.hpp"
#include "TcpServer.hpp"
#include "utils/EpollOp.hpp"
#include "utils/Config.hpp"
#include "utils/LineBuffer.hpp"
#include "utils/DebugLog.hpp"

#include "VoteLeader.hpp"


#define SERVER_NODES 16

class NetMngr
{
private:
    std::list<ClientAgent*> _client_pool;

    Config _config;

    EpollOp _epoll;

    TcpServer _server;

    ClientAgent* _nodes[SERVER_NODES];      // 连接到其他的节点
    long int _conn_interval;                // 尝试连接到其他节点的重试间隔时间(毫秒)
    long int _node_conn_times[SERVER_NODES]; //尝试连接到其他节点的时间(毫秒)

    std::map<int, ClientAgent*> _clients; // key:client fd,连接到其他的节点，来自其他节点的连接,客户端的连接
    std::list<ClientAgent*> _datain;      //有接收到数据的连接

    LineBuffer _buff;

    GenMsg _genmsg;
    map<int, std::function<void (ClientAgent*, MsgHead*)>> _msg_handlers;

    long int _nowms;    //当前时间(毫秒)
    long int _beattime; //心跳时间(毫秒)
    VoteLeader _vote;

    DebugLog _log;

public:
    NetMngr();
    virtual ~NetMngr();

private:
    bool init_pool();
    ClientAgent* get_inst();
    void pool_recycle(ClientAgent* client);
    void clean_pool();
public:
    bool init_msg_handlers();
    bool init_nodes();
    bool init(const Config& config);

    void uninit();

private:
    void on_accept();

    void on_read(int fd);

    void to_write(int fd, size_t len);

    void on_close(int fd);

    //一个服务节点掉线
    void node_close(ClientAgent* node);

    ClientAgent* get_client(int fd);
public:
    void net_loop();

    void epool_event();

    int try_conn(const string& ip, int port);
    //连接其它的节点
    void conn_node();

public:
    void handle_data();

    void parse_data(ClientAgent* client);

    MsgHead* parse_msg(ClientAgent* client);

    void handler_msg(ClientAgent* client, MsgHead* msg);

public:
    void sent_data();

    void on_send(ClientAgent* client, MsgHead* msg);

    //想各节点发送消息
    void sendto_nodes(MsgHead* msg);

    void sent_login(ClientAgent* client);

private:
    long int nowms();

    void sent_beat();
    void heart_beat_now();
    // 心跳包是否超时
    bool is_beat_timeout();
    // 提议是否超时
    bool is_propose_timeout();
    // 自己的投票时间是否超时
    bool is_vote_timeout();

    void update_nowms();

public: //处理leader选举
    //检查来集leader的心跳是否超时，超时就进行选举
    void check_vote_timeout();

    //可用的node数量
    size_t alive_nodes();

    // 数量为num时能不能成为多数
    bool is_majority(size_t num);

    //自谏选举
    void vote_me();

    //向各节点发送提议
    void propose_node();

    // 成为leader
    void become_leader();

    // leader down掉了
    void leader_down();

    bool is_leader(int nodeid);
    bool iam_leader();

    // 告知node，我是leader
    void inform_iam_leader(ClientAgent* node);

private:
    // 处理消息请求
    void on_login_req(ClientAgent* client, MsgHead* msg);

    void on_login_rsp(ClientAgent* client, MsgHead* msg);

    void on_vote_req(ClientAgent* client, MsgHead* msg);

    void on_vote_rsp(ClientAgent* client, MsgHead* msg);

    void on_leader_come(ClientAgent* client, MsgHead* msg);

    void on_heartbeat_req(ClientAgent* client, MsgHead* msg);

    void on_leader_conflict(ClientAgent* client, MsgHead* msg);

    void on_leader_cancle(ClientAgent* client, MsgHead* msg);

private:
    //发送请求消息
    void req_login(ClientAgent* client);

    void req_vote(ClientAgent* client);

private:
    void net_tests();

    void msg_tests();
};





#endif /* NETMNGR_HPP_ */




