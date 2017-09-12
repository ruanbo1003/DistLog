/*
 * MsgHandler.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ruanbo
 */

#include <Msg/MsgReader.hpp>


LineBuffer MsgReader::_rbuff;

MsgReader::MsgReader(RingBuff* rdata)
{
    _rdata = rdata;
}

MsgReader::~MsgReader()
{

}
char MsgReader::r_char()
{
    char val = 0;
    _rdata->read_del_begin((char*)&val, sizeof(char));
    return val;
}

short MsgReader::r_short()
{
    short val = 0;
    _rdata->read_del_begin((char*)&val, sizeof(short));
    return val;
}

int MsgReader::r_int()
{
    int val = 0;
    _rdata->read_del_begin((char*)&val, sizeof(int));
    return val;
}

long MsgReader::r_long()
{
    long val = 0;
    _rdata->read_del_begin((char*)&val, sizeof(long));
    return val;
}

std::string MsgReader::r_str()
{
    size_t len = r_short();

    _rbuff.append_size(len);
    _rdata->read_del_begin(_rbuff.data(), len);

    return string(_rbuff.data(), len);
}


