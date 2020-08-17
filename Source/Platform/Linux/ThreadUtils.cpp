/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-21 23:36:15
 * @LastEditTime: 2020-07-23 14:28:41
 */ 
#if defined(linux) || defined(__linux__)
#include "Thread.h"
#include "Platform.h"

namespace Magic{
    uint64_t GetThreadId(){
        return syscall(SYS_gettid);
    }
}
#endif