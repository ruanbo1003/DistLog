/*
 * VodeLeader.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: ruanbo
 */

#include <Network/VoteLeader.hpp>

VoteLeader::VoteLeader()
{
    _timeout = 0;
    _vote_id = -1;
    _leaderid = -1;
    _propose_time = 0;
    _role = Role_Learner;
    _tickets = 0;
}


VoteLeader::~VoteLeader()
{

}


bool VoteLeader::init(long int ms)
{
    _timeout = (rand() % 300) + 100;  // [100, 400)
//    _timeout = 1;

    Log("time out:%ld", _timeout);

    _vote_time = 0;
    _propose_time = ms;

    return true;
}

bool VoteLeader::has_leader()const
{
    return (_leaderid >= 0);
}

void VoteLeader::set_role(RoleType role)
{
    _role = role;
}

bool VoteLeader::timeout(int num)
{
    return (num >= _timeout);
}










