/*
 * NetTests.cpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ruanbo
 */

#include "NetMngr.hpp"


void NetMngr::net_tests()
{
    if(true)
    {
        return;
    }

    msg_tests();

}

void NetMngr::msg_tests()
{
    MsgLogin msg;
    msg._id = 111;

    int len = msg.todata(_buff.data());

    ClientAgent client;

    client._rbuff.add_data(_buff.data(), len);

    MsgLogin msg2;
    msg2.fromdata(client._rbuff);
    msg2.show();
}

















