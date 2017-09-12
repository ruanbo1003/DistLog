/*
 * NetComm.hpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ruanbo
 */

#ifndef NETCOMM_HPP_
#define NETCOMM_HPP_

#include "utils/RingBuff.hpp"


#define WR_BUFF_SIZE 2048

enum ClientType
{
    CT_Null = 0,
    CT_FromClient = 1, // 来自客户段的连接
    CT_ToServer = 2,  // 自己连接其他的节点
    CT_FromServer = 3, //来自其他节点的连接
};




#endif /* NETCOMM_HPP_ */
