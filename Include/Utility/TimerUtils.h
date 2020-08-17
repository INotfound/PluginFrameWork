/*
 * @File: TimerUtils.h
 * @Author: INotFound
 * @Date: 2020-07-21 23:41:46
 * @LastEditTime: 2020-07-22 00:26:07
 */ 
#pragma once
#include "Core.h"

namespace Magic{
    /**
     * @brief: 获取当前时间
     * @return: 返回当前时间
     */
    uint64_t GetCurrentTimeMS();
    /**
     * @brief: 获取当前时间
     * @return: 返回当前时间
     */
    uint64_t GetCurrentTimeUS();
}