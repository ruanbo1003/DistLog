/*
 * MsgHead.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ruanbo
 */

#include <Msg/MsgHead.hpp>
#include "comm/comm.hpp"

MsgHead::MsgHead()
{
    _len = 0;
    _msgid = 0;
}

MsgHead::~MsgHead()
{

}

int MsgHead::todata(char* data)
{
    if(data == NULL)
    {
        return 0;
    }

    MsgWriter writer(data);
    writer.w_int(_len);
    writer.w_int(_msgid);

    to_data(writer);

    _len = writer.datalen();
    memcpy(data, &_len, sizeof(int));

    return _len;
}

void MsgHead::fromdata(RingBuff& data)
{
    MsgReader reader(&data);

    _len = reader.r_int();
    _msgid = reader.r_int();

    from_data(reader);
}

int MsgHead::msgid()
{
    return _msgid;
}






