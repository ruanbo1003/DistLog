/*
 * Config.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ruanbo
 */

#include <utils/Config.hpp>
#include "Thirdlibs/TinyXml2/tinyxml2.h"

using namespace tinyxml2;

ServerNode::ServerNode()
{
    _id = -1;
    _ip = "";
    _port = 0;
}

bool ServerNode::is_valid()
{
    return (_id >= 0 && _ip.length() > 0 && _port > 0);
}

Config::Config(const string& file, int myid)
{
    _myid = myid;
    _node_cnt = 0;
    _file = file;
}

Config::~Config()
{
}

bool Config::read_config()
{
    XMLDocument doc;
    int ret = doc.LoadFile(_file.data());
    if(ret != 0)
    {
        Log("xml load config file(%s) failed(%d)", _file.data(), ret);
        return false;
    }

    XMLElement* root = doc.RootElement();
    if(!root)
    {
        Log("config file has no root element?");
        return false;
    }

    const XMLElement* xml_node = root->FirstChildElement("node");
    while(xml_node)
    {
        ServerNode srv_node;
        if(xml_node->FindAttribute("id"))
        {
            srv_node._id = xml_node->IntAttribute("id", 0);
        }
        if(xml_node->FindAttribute("ip"))
        {
            srv_node._ip = xml_node->Attribute("ip");
        }
        if(xml_node->FindAttribute("port"))
        {
            srv_node._port = xml_node->IntAttribute("port", 0);
        }

        if(srv_node.is_valid() == false)
        {
            LogError("节点的配置不正确。");
            return false;
        }

        _nodes[srv_node._id] = srv_node;
        _node_cnt++;

        xml_node = xml_node->NextSiblingElement();
    }

    return true;
}

string Config::get_ip(int nodeid)
{
    if(nodeid == -1)
    {
        nodeid = _myid;
    }

    auto it = _nodes.find(nodeid);
    if(it == _nodes.end())
    {
        return "";
    }
    return it->second._ip;
}
int Config::get_port(int nodeid)
{
    if(nodeid == -1)
    {
        nodeid = _myid;
    }
    auto it = _nodes.find(nodeid);
    if(it == _nodes.end())
    {
        return 0;
    }
    return it->second._port;
}

bool Config::valid_node(int nodeid)
{
    auto it = _nodes.find(nodeid);
    return it != _nodes.end();
}

void Config::show_nodes()
{
    for(auto it=_nodes.begin(); it!=_nodes.end(); ++it)
   {
       Log("one server node[%d,%s:%d]", it->second._id, it->second._ip.c_str(), it->second._port);
   }
}



