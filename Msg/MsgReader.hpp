/*
 * MsgHandler.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ruanbo
 */

#ifndef MSGREADER_HPP_
#define MSGREADER_HPP_

#include "utils/RingBuff.hpp"
#include "utils/LineBuffer.hpp"
#include <string>

class MsgReader
{
private:
    RingBuff* _rdata;
    static LineBuffer _rbuff;

public:
    MsgReader(RingBuff* rdata);
    virtual ~MsgReader();

public:
    char r_char();
    short r_short();
    int r_int();
    long r_long();
    std::string r_str();
};


#endif /* MSGREADER_HPP_ */
