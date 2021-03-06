/*
 * comm.hpp
 *
 *      Author: ruanbo
 */

#ifndef COMM_GLOBAL_HPP_
#define COMM_GLOBAL_HPP_

#include <string>
#include <string.h>
#include <sys/types.h>
#include <tr1/memory>

using namespace std;


using int8 = int8_t;
using uint8 = u_int8_t;

using int16 = int16_t;
using uint16 = u_int16_t;

using int32 = int32_t;
using uint32 = u_int32_t;

using int64 = int64_t;
using uint64 = u_int64_t;



void stdcopy(char* dest, const char* src, size_t len);



#endif /* COMM_GLOBAL_HPP_ */



















