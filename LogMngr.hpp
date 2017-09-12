/*
 * LogMngr.hpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ruanbo
 */

#ifndef LOGMNGR_HPP_
#define LOGMNGR_HPP_

#include <utils/Config.hpp>
#include "comm/IThread.hpp"

#include "Network/NetMngr.hpp"

class LogMngr : public IThread
{
private:
    Config _config;

    NetMngr _net_mngr;


public:
    LogMngr(int myid);
    virtual ~LogMngr();

public:
    bool init();

    void unit();

    void thread_loop();
};

#endif /* LOGMNGR_HPP_ */
