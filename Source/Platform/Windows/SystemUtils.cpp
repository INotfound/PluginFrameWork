/*
 * @File: SystemUtils.cpp
 * @Author: INotFound
 * @Date: 2020-07-26 17:54:27
 * @LastEditTime: 2020-07-26 17:58:25
 */ 
#if defined(_WIN32) || defined(_WIN64)
#include "Logger.h"
#include "Platform.h"
#include "SystemUtils.h"

namespace Magic{
    uint32_t GetProcessorsNumber(){
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        return info.dwNumberOfProcessors;
    }
}
#endif