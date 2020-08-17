/*
 * @File: TimerUtils.cpp
 * @Author: INotFound
 * @Date: 2020-07-21 23:42:46
 * @LastEditTime: 2020-07-21 23:45:00
 */ 
#if defined(_WIN32) || defined(_WIN64)
#include "Platform.h"
#include "TimerUtils.h"

namespace Magic{
    uint64_t GetCurrentTimeMS(){
        SYSTEMTIME st;
        GetLocalTime(&st);
        return st.wMilliseconds;
    }

    uint64_t GetCurrentTimeUS(){
    #define EPOCHFILETIME (116444736000000000UL)
        FILETIME ft;
        LARGE_INTEGER li;
        int64_t tt = 0;
        GetSystemTimeAsFileTime(&ft);
        li.LowPart = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;
        // 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
        tt = (li.QuadPart - EPOCHFILETIME) /10;
        return tt;
    #undef EPOCHFILETIME
    }
}
#endif