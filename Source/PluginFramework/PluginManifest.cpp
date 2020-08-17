/*
 * @File: PluginManifest.cpp
 * @Author: INotFound
 * @Date: 2020-07-07 16:05:05
 * @LastEditTime: 2020-08-01 09:30:40
 */ 
#include "Logger.h"
#include "PluginManifest.h"

namespace Magic{
    PluginManifest::~PluginManifest(){
        Library::Free(m_Handle);
    }
    
    PluginManifest::PluginManifest(const std::string& path)
        :m_Path(path)
        ,m_Content(nullptr){ 
        m_Handle = Library::Load(path);
        if(m_Handle){
            m_Content = reinterpret_cast<content_t>(Library::GetMetaFunction(m_Handle, "getManifest"));
            //MAGIC_ASSERT(m_Create, "Not Found Function");
        }
        else{
            MAGIC_WARN() << "Load Manifest Failed: " << path;
        }
    }

    const char* PluginManifest::getManifest(uint64_t& length){
        if(m_Content == nullptr){
            return nullptr;
        }
        return m_Content(length);
    }
}