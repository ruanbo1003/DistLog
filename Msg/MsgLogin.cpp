/*
 * MsgLogin.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ruanbo
 */

#include <Msg/MsgLogin.hpp>

MsgLogin::MsgLogin()
{
    _msgid = MsgId_Login;
    _id = -1;
}

MsgLogin::~MsgLogin()
{

}

void MsgLogin::to_data(MsgWriter& writer)
{
    writer.w_short(_id);
}

void MsgLogin::from_data(MsgReader& reader)
{
    _id = reader.r_short();
}

void MsgLogin::show()
{
    printf("login msg. len:%d, msg_id:%d, type:%d\n", _len, _msgid, _id);
}


MsgVerify::MsgVerify()
{
    _msgid = MsgId_LoginRsp;
}
MsgVerify::~MsgVerify()
{

}
void MsgVerify::to_data(MsgWriter& writer)
{
}
void MsgVerify::from_data(MsgReader& reader)
{
}


MsgHeartbeat::MsgHeartbeat()
{
    _msgid = MsgId_Heartbeat;
}
MsgHeartbeat::~MsgHeartbeat()
{

}
void MsgHeartbeat::to_data(MsgWriter& writer)
{
}
void MsgHeartbeat::from_data(MsgReader& reader)
{
}







