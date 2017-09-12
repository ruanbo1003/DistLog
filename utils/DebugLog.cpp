/*
 * DebugLog.cpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ruanbo
 */

#include <fstream>
#include <sys/stat.h>
#include <utils/DebugLog.hpp>
#include <ctime>

#include <iostream>
#include <stdio.h>

DebugLog::DebugLog()
{
    _path = "/home/ruanbo/Codes/DistLog/DebugFiles/" + now_date() + "/";
}

DebugLog::~DebugLog()
{

}

bool DebugLog::is_directory(const string& f)
{
    struct stat st;
    if(stat(f.data(), &st) != 0)
    {
        return false;
    }

    if(S_ISDIR(st.st_mode))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DebugLog::create_folder(string& f)
{
    size_t len = f.length();
    if(len <= 1)
    {
        return false;
    }

    for(size_t i = 1; i<len; ++i)
    {
        if(f[i] == '/')
        {
            string parent_dir(f, 0, i);

            if(is_directory(parent_dir) == false)
            {
                int ret = mkdir(parent_dir.data(), 0755);
                if(ret != 0)
                {
                    return false;
                }
            }
        }
    }

    return true;
}


bool DebugLog::init()
{
    if(is_directory(_path) == true)
    {
        return true;
    }

    if(create_folder(_path) == false)
    {
        return false;
    }

    return true;
}

string DebugLog::now_date()
{
    std::time_t now = time(NULL);
    char buf[32] = { 0 };
    size_t len = std::strftime(buf, 32, "%Y%m%d", std::localtime(&now));
    return string(buf, len);
}

string DebugLog::now_minute()
{
    std::time_t now = time(NULL);
    char buf[32] = { 0 };
    size_t len = std::strftime(buf, 32, "%H%M", std::localtime(&now));
    return string(buf, len);
}

bool DebugLog::write(const string& log)
{
    string file_name = _path + now_minute() + ".log";

    ofstream file;
    file.open(file_name.data(), ios::out | ios::app);
    if(file.is_open() == false)
    {
        return false;
    }

    file << log;

    file.flush();

    file.close();

    return true;
}














