/*
 * MsgLogin.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ruanbo
 */

#ifndef MSGLOGIN_HPP_
#define MSGLOGIN_HPP_

#include "MsgComm.hpp"

class MsgLogin : public MsgHead
{
public:
    short _id;   // -1:客户段，>=0:节点id

public:
    MsgLogin();
    virtual ~MsgLogin();

public:
    void to_data(MsgWriter& writer);

    void from_data(MsgReader& reader);

    void show();
};

class MsgVerify : public MsgHead
{
public:
    MsgVerify();
    virtual ~MsgVerify();
public:
    void to_data(MsgWriter& writer);

    void from_data(MsgReader& reader);
};

class MsgHeartbeat : public MsgHead
{
public:
    MsgHeartbeat();
    virtual ~MsgHeartbeat();

public:
    void to_data(MsgWriter& writer);

    void from_data(MsgReader& reader);

};



#endif /* MSGLOGIN_HPP_ */










