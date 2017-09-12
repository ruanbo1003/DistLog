/*
 * DebugLog.hpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ruanbo
 */

#ifndef DEBUGLOG_HPP_
#define DEBUGLOG_HPP_

#include "comm/comm.hpp"

#define ToLog(...) {char buff[1024] = { 0 }; sprintf(buff, __VA_ARGS__); _log.write(buff); \
                    printf(__VA_ARGS__); printf("\n"); }

class DebugLog
{
private:
    string _path;

public:
    DebugLog();
    virtual ~DebugLog();

private:
    bool is_directory(const string& f);

    bool create_folder(string& f);

private:
    string now_date();
    string now_minute();

public:
    bool init();

    bool write(const string& log);
};

#endif /* DEBUGLOG_HPP_ */
