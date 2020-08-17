/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-26 17:54:07
 * @LastEditTime: 2020-07-26 17:56:01
 */ 
#if defined(linux) || defined(__linux__)
#include "Logger.h"
#include "Platform.h"
#include "SystemUtils.h"

namespace Magic{
    uint32_t GetProcessorsNumber(){
        unsigned int count = 1;
        count = sysconf(_SC_NPROCESSORS_CONF);
        return count;
    }
}
#endif