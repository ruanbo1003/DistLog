/*
 * VodeLeader.hpp
 *
 *  Created on: Sep 10, 2017
 *      Author: ruanbo
 */

#ifndef VOTELEADER_HPP_
#define VOTELEADER_HPP_

#include "comm/comm.hpp"

enum RoleType
{
    Role_Null = 0,
    Role_Learner = 1,
    Role_Proposer = 2,
    Role_Leader = 3
};


class VoteLeader
{
public:
    long int _timeout;    //超时时间：来自leader的心跳超时 ，投票给提议者后提议者确认的超时
    long int _vote_time; //自己投票的时间（毫秒）
    int _vote_id;    // 自己投出的id，超时置-1
    int _leaderid;   // leader的id

    long int _propose_time;  // 提议时间（毫秒）
    RoleType _role;   //自己的角色
    size_t _tickets;

public:
    VoteLeader();
    virtual ~VoteLeader();

public:
    bool init(long int ms);

    bool has_leader()const;

    void set_role(RoleType role);

    bool timeout(int num);

};

#endif /* VOTELEADER_HPP_ */
