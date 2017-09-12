/*
 * Config.hpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ruanbo
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "comm/comm.hpp"

class ServerNode
{
public:
    int _id;
    string _ip;
    int _port;

public:
    ServerNode();

    bool is_valid();
};

class Config
{
public:
    int _myid;
    size_t _node_cnt;
private:
    string _file;
    std::map<int, ServerNode> _nodes;


public:
    Config(const string& file="", int myid=0);
    virtual ~Config();

public:
    bool read_config();

    void show_nodes();

public:
    string get_ip(int nodeid = -1);
    int get_port(int nodeid = -1);

    bool valid_node(int nodeid);
};

#endif /* CONFIG_HPP_ */
