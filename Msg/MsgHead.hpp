/*
 * MsgHead.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ruanbo
 */

#ifndef MSGHEAD_HPP_
#define MSGHEAD_HPP_

#include "MsgWriter.hpp"
#include "MsgReader.hpp"

enum MsgIdDef
{
    MsgId_Null = 0,

    MsgId_Login = 1,

    MsgId_LoginRsp = 2,

    MsgId_Vote = 3,

    MsgId_VoteRsp = 4,

    MsgId_Heartbeat = 5,

    MsgId_LeaderInform = 6,

    // 产生了多个leader
    MsgId_LeaderConflict = 7,

    // 产生了多个leader，旧的leader通知取消
    MsgId_LeaderCancle = 8
};

class MsgHead
{
protected:
    int _len;
    int _msgid;

public:
    MsgHead();
    virtual ~MsgHead();

private:
    virtual void to_data(MsgWriter& writer) = 0;
    virtual void from_data(MsgReader& reader) = 0;

public:
    int todata(char* data);
    void fromdata(RingBuff& data);

public:
    int msgid();
};

#endif /* MSGHEAD_HPP_ */



