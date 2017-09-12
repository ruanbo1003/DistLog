/*
 * GenMsg.hpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ruanbo
 */

#ifndef GENMSG_HPP_
#define GENMSG_HPP_

#include "MsgComm.hpp"

#include <map>
#include <functional>



class GenMsg
{
private:
    map<int, std::function<MsgHead*(void)>> _msgs;

public:
    GenMsg();
    virtual ~GenMsg();

private:
    MsgHead* gen_login();
    MsgHead* gen_loginrsp();

    MsgHead* get_select();
    MsgHead* get_sel_rsp();

    MsgHead* gen_heartbeat();

    MsgHead* gen_leader();

    MsgHead* gen_leader_conflict();

    MsgHead* gen_leader_cancle();
public:
    MsgHead* to_msg(MsgIdDef id);
};

#endif /* GENMSG_HPP_ */





