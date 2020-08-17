/*
 * @File: PluginLoader.cpp
 * @Author: INotFound
 * @Date: 2020-06-17 21:32:26
 * @LastEditTime: 2020-07-26 18:10:15
 */ 
#include "Logger.h"
#include "PluginLoader.h"

namespace Magic{
    
    PluginLoader::~PluginLoader(){
        Library::Free(m_Handle);
    }

    PluginLoader::PluginLoader(const std::string& path)
        :m_Create(nullptr)
        ,m_Path(path){ 
        m_Handle = Library::Load(path);
        MAGIC_INFO() << "Loading Plugin Module: " << path.c_str();
    }

    void PluginLoader::load(){
        if(m_Handle){
            m_Create = reinterpret_cast<create_t>(Library::GetMetaFunction(m_Handle, "create"));
            //MAGIC_ASSERT(m_Create, "Not Found Function");
        }
        else{
            MAGIC_ERROR() << "Load Plugin Failed";
        }
    }

    IPluginActivator* PluginLoader::getInstance(){
        return (m_Create == nullptr) ? nullptr : m_Create(LogAppenderMgr::GetInstance());
    }
}