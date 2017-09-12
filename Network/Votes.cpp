/*
 * Votes.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: ruanbo
 */

#include "NetMngr.hpp"


void NetMngr::check_vote_timeout()
{
    if(is_beat_timeout() == true)
    {
        // 来自leader的心跳超时
        _vote._leaderid = -1;
        vote_me();
    }

    if( (_vote._vote_id != -1) &&  (is_vote_timeout() == true) )
    {
        //投票时间超时
        _vote._vote_id = -1;  // 清空投票id
    }
}


//可用的node数量
size_t NetMngr::alive_nodes()
{
    size_t num = 0;
    for(size_t i=0; i<_config._node_cnt; ++i)
    {
        if(i == (size_t)_config._myid)
        {
            continue;
        }

        ClientAgent* client = _nodes[i];
        if(client && client->is_node())
        {
            num++;
        }
    }

    num++; //加上自己

    return num;
}

// 数量为num时能不能成为多数
bool NetMngr::is_majority(size_t num)
{
    return (num >= (_config._node_cnt / 2 + 1) );
}

//自谏选举
void NetMngr::vote_me()
{
    if(_vote._role == Role_Proposer)
    {
        if(is_propose_timeout() == true)
        {
            // 自己是提议者，并且超时
            _vote.set_role(Role_Learner);
            _vote._propose_time = nowms(); // 更新提议时间，否则会一直处于提议状态
        }

        return;
    }

//    if(_vote.timeout(nowms() - _vote._propose_time) == false)
//    {
//        // 提议还没超时
//        return;
//    }

    if(_vote._vote_id != -1)
    {
        // 已经投别人了
        return;
    }

    if(_vote._leaderid != -1)
    {
        // 已经有leader了
        return;
    }

    _vote._propose_time = nowms();

    size_t node_num = alive_nodes();
    if(is_majority(node_num) == false)
    {
//        ToLog("node[%d] propose a vote but less node num[%u]", _config._myid, (unsigned int)node_num);
        return;
    }

//    ToLog("node[%d] propose a vote. node number is %ld", _config._myid, node_num);

    _vote._tickets = 1;   // 先投自己一票
    _vote.set_role(Role_Proposer);

    propose_node();
}

void NetMngr::propose_node()
{
    MsgVote msg;
    msg._leader = _config._myid;

    sendto_nodes(&msg);
}

void NetMngr::become_leader()
{
    ToLog("node[%d] become the leader", _config._myid);

    _vote._leaderid = _config._myid;

    MsgLeaderInform msg;
    sendto_nodes(&msg);
}

void NetMngr::leader_down()
{
    ToLog("node[%d] know leader[%d] is down.", _config._myid, _vote._leaderid);
    _vote._leaderid = -1;
}

bool NetMngr::is_leader(int nodeid)
{
    return (_vote._leaderid == nodeid);
}

bool NetMngr::iam_leader()
{
    return (_config._myid == _vote._leaderid);
}

void NetMngr::inform_iam_leader(ClientAgent* node)
{
    MsgLeaderInform msg;

    on_send(node, &msg);
}








