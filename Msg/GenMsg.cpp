/*
 * GenMsg.cpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ruanbo
 */

#include <Msg/GenMsg.hpp>

GenMsg::GenMsg()
{
    _msgs[MsgId_Login] = std::bind(&GenMsg::gen_login, this);
    _msgs[MsgId_LoginRsp] = std::bind(&GenMsg::gen_loginrsp, this);
    _msgs[MsgId_Vote] = std::bind(&GenMsg::get_select, this);
    _msgs[MsgId_VoteRsp] = std::bind(&GenMsg::get_sel_rsp, this);
    _msgs[MsgId_Heartbeat] = std::bind(&GenMsg::gen_heartbeat, this);
    _msgs[MsgId_LeaderInform] = std::bind(&GenMsg::gen_leader, this);
    _msgs[MsgId_LeaderConflict] = std::bind(&GenMsg::gen_leader_conflict, this);
    _msgs[MsgId_LeaderCancle] = std::bind(&GenMsg::gen_leader_cancle, this);
}

GenMsg::~GenMsg()
{

}

MsgHead* GenMsg::gen_login()
{
    return new MsgLogin();
}

MsgHead* GenMsg::gen_loginrsp()
{
    return new MsgVerify();
}

MsgHead* GenMsg::get_select()
{
    return new MsgVote();
}

MsgHead* GenMsg::get_sel_rsp()
{
    return new MsgVoteRsp();
}

MsgHead* GenMsg::gen_heartbeat()
{
    return new MsgHeartbeat();
}

MsgHead* GenMsg::gen_leader()
{
    return new MsgLeaderInform();
}

MsgHead* GenMsg::gen_leader_conflict()
{
    return new MsgLeaderConflict();
}

MsgHead* GenMsg::gen_leader_cancle()
{
    return new MsgLeaderCancle();
}


MsgHead* GenMsg::to_msg(MsgIdDef id)
{
    auto func_it = _msgs.find(id);
    if(func_it != _msgs.end())
    {
        return func_it->second();
    }

    return NULL;
}








