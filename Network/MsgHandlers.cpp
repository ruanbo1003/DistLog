/*
 * MsgHandlers.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: ruanbo
 */

#include "NetMngr.hpp"

bool NetMngr::init_msg_handlers()
{
    _msg_handlers[MsgId_Login] = std::bind(&NetMngr::on_login_req, this, std::placeholders::_1, std::placeholders::_2);
    _msg_handlers[MsgId_LoginRsp] = std::bind(&NetMngr::on_login_rsp, this, std::placeholders::_1, std::placeholders::_2);
    _msg_handlers[MsgId_Vote] = std::bind(&NetMngr::on_vote_req, this, std::placeholders::_1, std::placeholders::_2);
    _msg_handlers[MsgId_VoteRsp] = std::bind(&NetMngr::on_vote_rsp, this, std::placeholders::_1, std::placeholders::_2);
    _msg_handlers[MsgId_Heartbeat] = std::bind(&NetMngr::on_heartbeat_req, this, std::placeholders::_1, std::placeholders::_2);
    _msg_handlers[MsgId_LeaderInform] = std::bind(&NetMngr::on_leader_come, this, std::placeholders::_1, std::placeholders::_2);
    _msg_handlers[MsgId_LeaderConflict] = std::bind(&NetMngr::on_leader_conflict, this, std::placeholders::_1, std::placeholders::_2);
    _msg_handlers[MsgId_LeaderCancle] = std::bind(&NetMngr::on_leader_cancle, this, std::placeholders::_1, std::placeholders::_2);

    return true;
}

void NetMngr::handler_msg(ClientAgent* client, MsgHead* msg)
{
    auto it = _msg_handlers.find(msg->msgid());
    if(it == _msg_handlers.end())
    {
        ToLog("can not find a handler for msg[%d]", msg->msgid());
        delete msg;

        return;
    }

    if(client->is_verified() == false && msg->msgid() != MsgId_Login)
    {
        ToLog("the first msg should be login msg. is msg[%d] now", msg->msgid());
        return;
    }

    if(client->is_verified() == true && msg->msgid() == MsgId_Login)
    {
        ToLog("verified client to node[%d].msg should not be login", _config._myid);
        return;
    }

    it->second(client, msg);

    delete msg;
}

void NetMngr::on_login_req(ClientAgent* client, MsgHead* msg)
{
    MsgLogin* req = dynamic_cast<MsgLogin*>(msg);
    if(!req)
    {
        ToLog("invalid login req in node[%d]", _config._myid);
    }

    ToLog("node[%d] get login req from node[%d]", _config._myid, req->_id);

    if(_config.valid_node(req->_id) == false)
    {
        ToLog("login req node id[%d] is invalid", req->_id);
        return;
    }

    client->set_type(CT_FromServer);
    client->setid(req->_id);
    client->set_status(Login_Verified);

    _nodes[req->_id] = client;

    MsgVerify rsp;
    on_send(client, &rsp);

    if(iam_leader() == true)
    {
        inform_iam_leader(client);
    }
}

void NetMngr::on_login_rsp(ClientAgent* client, MsgHead* msg)
{
    MsgVerify* req = dynamic_cast<MsgVerify*>(msg);
    if(!req)
    {
        ToLog("invalid login rsp msg in node[%d]", _config._myid);
        return;
    }

    ToLog("node[%d] get login rsp from node[%d]", _config._myid, client->_node_id);

    client->set_status(Login_Verified);

    if(iam_leader() == true)
    {
        inform_iam_leader(client);
    }
}

void NetMngr::on_vote_req(ClientAgent* client, MsgHead* msg)
{
    Log("node [%d] handler a vote req from node[%d]", _config._myid, client->_node_id);

    MsgVoteRsp rsp;

    if(_vote._role == Role_Proposer)
    {
        rsp._answer = Vote_Myself;
        on_send(client, &rsp);

        return;
    }

    if(_vote._vote_id != -1)
    {
        rsp._answer = Vote_Other;
        rsp._id = _vote._vote_id;
        on_send(client, &rsp);

        return;
    }

    if(_vote._leaderid != -1)
    {
        rsp._answer = Vote_Leader;
        rsp._id = _vote._leaderid;
        on_send(client, &rsp);

        return;
    }

    _vote._vote_time = nowms(); // 更新投票时间

    rsp._answer = Vote_Yes;
    on_send(client, &rsp);
}

void NetMngr::on_vote_rsp(ClientAgent* client, MsgHead* msg)
{
    Log("node [%d] handler a vote rsp from node[%d]", _config._myid, client->_node_id);

    MsgVoteRsp* req = dynamic_cast<MsgVoteRsp*>(msg);
    if(!req)
    {
        return;
    }

    if(req->_answer == Vote_Yes)
    {
        _vote._tickets++;

        if(is_majority(_vote._tickets) == true)
        {
            // 成为 leader
            become_leader();
        }
    }
}

void NetMngr::on_leader_come(ClientAgent* client, MsgHead* msg)
{
    heart_beat_now();

    if(_vote._leaderid != -1)
    {
        MsgLeaderConflict rsp;
        rsp._other_id = _vote._leaderid;

        on_send(client, &rsp);

        return;
    }

    _vote._leaderid = client->_node_id;

    Log("node[%d] now know the leader is node[%d]", _config._myid, client->_node_id);
}

void NetMngr::on_heartbeat_req(ClientAgent* client, MsgHead* msg)
{
//    Log("node [%d] handler a heart beat from node[%d]", _config._myid, client->_node_id);

    heart_beat_now();
}


void NetMngr::on_leader_conflict(ClientAgent* client, MsgHead* msg)
{
    MsgLeaderConflict* req = dynamic_cast<MsgLeaderConflict*>(msg);
    if(!req)
    {
        return;
    }

    if(req->_other_id == _config._myid)
    {
        return;
    }

    MsgLeaderCancle rsp;
    sendto_nodes(&rsp);
}

void NetMngr::on_leader_cancle(ClientAgent* client, MsgHead* msg)
{
    if(_vote._leaderid == -1)
    {
        return;
    }

    _vote._leaderid = -1;
}










