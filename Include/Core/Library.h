/*
 * @File: Library.h
 * @Author: INotFound
 * @Date: 2020-07-17 23:54:13
 * @LastEditTime: 2020-07-18 00:01:01
 */ 
#pragma once
#include "Core.h"
#include "Platform.h"

namespace Magic{
    class Library{
    public:
        static void Free(plugin_t handle);
        static plugin_t Load(const std::string& path);
        static void* GetMetaFunction(plugin_t handle,const std::string& func);
    };
}