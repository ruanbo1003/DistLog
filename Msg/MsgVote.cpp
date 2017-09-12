/*
 * MsgSelect.cpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ruanbo
 */

#include <Msg/MsgVote.hpp>

MsgVote::MsgVote()
{
    _msgid = MsgId_Vote;
    _op_id = -1;
    _leader = -1;
}

MsgVote::~MsgVote()
{

}

void MsgVote::to_data(MsgWriter& writer)
{
    writer.w_long(_op_id);
    writer.w_short(_leader);
}

void MsgVote::from_data(MsgReader& reader)
{
    _op_id = reader.r_long();
    _leader = reader.r_short();
}


MsgVoteRsp::MsgVoteRsp()
{
    _msgid = MsgId_VoteRsp;
    _answer = Vote_Null;
    _id = -1;
}
MsgVoteRsp::~MsgVoteRsp()
{

}
void MsgVoteRsp::to_data(MsgWriter& writer)
{
    writer.w_char((char)_answer);
    writer.w_short(_id);
}
void MsgVoteRsp::from_data(MsgReader& reader)
{
    _answer = (VoteRspType)reader.r_char();
    _id = reader.r_short();
}


MsgLeaderInform::MsgLeaderInform()
{
    _msgid = MsgId_LeaderInform;
}
MsgLeaderInform::~MsgLeaderInform()
{
}
void MsgLeaderInform::to_data(MsgWriter& writer)
{
}
void MsgLeaderInform::from_data(MsgReader& reader)
{
}


MsgLeaderConflict::MsgLeaderConflict()
{
    _msgid = MsgId_LeaderConflict;
    _other_id = -1;
}
MsgLeaderConflict::~MsgLeaderConflict()
{
}
void MsgLeaderConflict::to_data(MsgWriter& writer)
{
    writer.w_short(_other_id);
}
void MsgLeaderConflict::from_data(MsgReader& reader)
{
    _other_id = reader.r_short();
}

MsgLeaderCancle::MsgLeaderCancle()
{
    _msgid = MsgId_LeaderCancle;
}
MsgLeaderCancle::~MsgLeaderCancle()
{
}
void MsgLeaderCancle::to_data(MsgWriter& writer)
{
}
void MsgLeaderCancle::from_data(MsgReader& reader)
{
}











