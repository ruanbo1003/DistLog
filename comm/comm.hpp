/*
 * comm.hpp
 *
 *  Created on: Aug 3, 2016
 *      Author: ruanbo
 */

#ifndef COMM_COMM_HPP_
#define COMM_COMM_HPP_


#include "Log.hpp"
#include "Noncopyable.hpp"

#include <iostream>

#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <string.h>
#include <unistd.h>
#include <errno.h>


using namespace std;


template<class T>
void show_vec(const vector<T>& V, string msg="")
{
    if(msg.length() > 0)
    {
        LogLine("%s:", msg.c_str());
    }

    for(auto &i : V)
    {
        cout << i << " ";
    }
    cout << endl;
}

template<class T>
void show_bin(T v)
{
    size_t s = sizeof(T);

    for(size_t i=s; i>0; --i)
    {
        for(size_t b=8; b>0; --b)
        {
            if(v & (0x01 << ((i-1)*8 + (b-1))) )
            {
                LogLine("1");
            }
            else
            {
                LogLine("0");
            }
        }
        LogLine("B ");
    }

    Log(" ");
}







#endif /* COMM_COMM_HPP_ */
