/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-18 00:01:49
 * @LastEditTime: 2020-07-23 23:26:53
 */ 
#if defined(linux) || defined(__linux__)
#include "Library.h"

namespace Magic{
    void Library::Free(plugin_t handle){
        if(handle){
            dlclose(handle);
        }
    }

    plugin_t Library::Load(const std::string& path){
        return dlopen(path.c_str(),RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND);
    }
    
    void* Library::GetMetaFunction(plugin_t handle,const std::string& func){
        if(handle){
            return dlsym(handle,func.c_str());
        }
        return nullptr;
    }
}
#endif