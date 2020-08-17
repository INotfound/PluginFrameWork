/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-21 23:42:40
 * @LastEditTime: 2020-07-21 23:54:34
 */ 
#if defined(linux) || defined(__linux__)
#include "Platform.h"
#include "TimerUtils.h"

namespace Magic{
    uint64_t GetCurrentTimeMS(){
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec * 1000ul  + tv.tv_usec / 1000;
    }

    uint64_t GetCurrentTimeUS(){
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec * 1000 * 1000ul  + tv.tv_usec;
    }
}
#endif