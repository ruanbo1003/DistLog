/*
 * MsgRequest.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: ruanbo
 */


#include "NetMngr.hpp"


void NetMngr::req_login(ClientAgent* client)
{
    MsgLogin msg;
    msg._id = _config._myid;

    client->set_status(Login_UnVerify);
    on_send(client, &msg);
}


