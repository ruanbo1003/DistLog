/*
 * MsgWriter.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ruanbo
 */

#include <Msg/MsgWriter.hpp>
#include <string.h>

MsgWriter::MsgWriter(char* data)
{
    _data = data;
    _pos = 0;
}

MsgWriter::~MsgWriter()
{

}

void MsgWriter::step(size_t n)
{
    _pos += n;
}

void MsgWriter::w_char(char val)
{
    size_t datalen = sizeof(val);
    memcpy(_data+_pos, &val, datalen);
    step(sizeof(char));
}

void MsgWriter::w_short(short val)
{
    size_t datalen = sizeof(val);
    memcpy(_data+_pos, &val, datalen);
    step(sizeof(short));
}

void MsgWriter::w_int(int val)
{
    size_t datalen = sizeof(val);
    memcpy(_data+_pos, &val, datalen);
    step(sizeof(int));
}

void MsgWriter::w_long(long int val)
{
    size_t datalen = sizeof(val);
    memcpy(_data+_pos, &val, datalen);
    step(sizeof(long int));
}

void MsgWriter::w_str(const std::string& str)
{
    size_t str_len = str.length();
    w_short(str_len);

    memcpy(_data+_pos, str.data(), str.length());
    step(str_len);
}

size_t MsgWriter::datalen()
{
    return _pos;
}


