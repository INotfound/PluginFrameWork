/*
 * @File: Library.cpp
 * @Author: INotFound
 * @Date: 2020-07-18 00:01:49
 * @LastEditTime: 2020-07-21 23:08:05
 */ 
#if defined(_WIN32) || defined(_WIN64)
#include "Library.h"

namespace Magic{
    void Library::Free(plugin_t handle){
        if(handle){
            FreeLibrary(handle);
        }
    }

    plugin_t Library::Load(const std::string& path){
        return LoadLibrary(path.c_str());
    }

    void* Library::GetMetaFunction(plugin_t handle,const std::string& func){
        if(handle){
            return reinterpret_cast<void*>(GetProcAddress(handle,func.c_str()));
        }
        return nullptr;
    }
}
#endif