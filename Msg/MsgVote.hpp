/*
 * MsgSelect.hpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ruanbo
 */

#ifndef MSGVOTE_HPP_
#define MSGVOTE_HPP_

#include "MsgComm.hpp"

enum VoteRspType
{
    Vote_Null = 0,
    Vote_Yes = 1,    // 同意, _id无意义
    Vote_Other = 2,  // 已经同意了别人，_id 为已同意的node id
    Vote_Leader = 3, // 已经有leader了, _id 为leader的node id
    Vote_Myself = 4  // 自己也是提议人, _id无意义
};

// 发起选举自己为leader
class MsgVote : public MsgHead
{
public:
    long int _op_id;
    short _leader;  //leader的id(node id)

public:
    MsgVote();
    virtual ~MsgVote();

public:
    void to_data(MsgWriter& writer);

    void from_data(MsgReader& reader);
};

/*
 * 选举的回应
 */
class MsgVoteRsp : public MsgHead
{
public:
    VoteRspType _answer;
    short _id;

public:
    MsgVoteRsp();
    ~MsgVoteRsp();

public:
    void to_data(MsgWriter& writer);

    void from_data(MsgReader& reader);
};

// 告知node，我是leader
class MsgLeaderInform : public MsgHead
{
public:

public:
    MsgLeaderInform();
    ~MsgLeaderInform();

public:
    void to_data(MsgWriter& writer);

    void from_data(MsgReader& reader);
};

class MsgLeaderConflict : public MsgHead
{
public:
    short _other_id;

public:
    MsgLeaderConflict();
    ~MsgLeaderConflict();

public:
    void to_data(MsgWriter& writer);

    void from_data(MsgReader& reader);
};

class MsgLeaderCancle : public MsgHead
{
public:

public:
    MsgLeaderCancle();
    ~MsgLeaderCancle();

public:
    void to_data(MsgWriter& writer);

    void from_data(MsgReader& reader);
};




#endif /* MSGVOTE_HPP_ */








