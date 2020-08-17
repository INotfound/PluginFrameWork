/*
 * @File: ThreadUtils.cpp
 * @Author: INotFound
 * @Date: 2020-07-21 23:36:55
 * @LastEditTime: 2020-07-21 23:38:07
 */ 
#if defined(_WIN32) || defined(_WIN64)
#include "Thread.h"

namespace Magic{
    uint64_t GetThreadId(){
        return GetCurrentThreadId();
    }
}
#endif