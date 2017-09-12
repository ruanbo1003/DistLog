/*
 * LogMngr.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ruanbo
 */

#include <LogMngr.hpp>

#include "comm/comm.hpp"

LogMngr::LogMngr(int myid)
{
    _config = Config("/home/ruanbo/Codes/DistLog/Config/server_nodes.xml", myid);
}

LogMngr::~LogMngr()
{

}

bool LogMngr::init()
{
    if(_config.read_config() == false)
    {
        LogError("read config failed");
        return false;
    }
//    _config.show_nodes();

    if(_net_mngr.init(_config) == false)
    {
        Log("NetMnanger init failed");
        return false;
    }


    return true;
}

void LogMngr::unit()
{
    _net_mngr.uninit();
    LogFunc(" ");
}

void LogMngr::thread_loop()
{
//    sleep(1);
//    usleep(1000000);

    _net_mngr.net_loop();

//    LogFunc(" ");

    return;
}

