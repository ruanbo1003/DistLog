/*
 * Pools.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: ruanbo
 */

#include "NetMngr.hpp"

bool NetMngr::init_pool()
{
    for(int i=0; i<1; ++i)
    {
        _client_pool.push_back(new ClientAgent());
    }

    return true;
}

ClientAgent* NetMngr::get_inst()
{
    if(_client_pool.empty() == false)
    {
        ClientAgent* c = _client_pool.front();
        _client_pool.pop_front();
        return c;
    }

    Log("pool inst is not enough");

    return new ClientAgent();
}
void NetMngr::pool_recycle(ClientAgent* client)
{
    client->reset();

    _client_pool.push_back(client);
}

void NetMngr::clean_pool()
{
    while(_client_pool.empty() == false)
    {
        ClientAgent* c = _client_pool.front();
        _client_pool.pop_front();
        delete c;
    }
}

