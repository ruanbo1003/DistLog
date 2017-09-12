/*
 * RunHelper.hpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ruanbo
 */

#ifndef RUNHELPER_HPP_
#define RUNHELPER_HPP_

#include "comm/comm.hpp"

#include "LogMngr.hpp"


class RunHelper : public NonCopyable
{
public:
    RunHelper();
    virtual ~RunHelper();

public:
    void run(int argc, char* argv[]);

};

#endif /* RUNHELPER_HPP_ */
