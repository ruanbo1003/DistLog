/*
 * MsgWriter.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ruanbo
 */

#ifndef MSGWRITER_HPP_
#define MSGWRITER_HPP_

#include <string>

class MsgWriter
{
private:
    char *_data;
    size_t _pos;

public:
    MsgWriter(char* data);
    virtual ~MsgWriter();

private:
    void step(size_t n);

public:
    void w_char(char val);
    void w_short(short val);
    void w_int(int val);
    void w_long(long int val);
    void w_str(const std::string& str);

    size_t datalen();
};

#endif /* MSGWRITER_HPP_ */
