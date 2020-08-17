/*
 * @File: Plugin.cpp
 * @Author: INotFound
 * @Date: 2020-06-23 10:19:32
 * @LastEditTime: 2020-07-26 18:16:20
 */ 
#include "Any.h"
#include "Logger.h"
#include "Plugin.h"
#include "PluginArchive.h"
#include "PluginFrameworkContext.h"

namespace Magic{
    Plugin::Plugin(const Safe<PluginArchive>& archive,const Safe<PluginFrameworkContext>& ctx)
        :m_Loader(new PluginLoader(archive->getLocation()))
        ,m_Archive(archive)
        ,m_Ctx(ctx){
        m_Archive.get();
        m_Ctx.get();
    }

    void Plugin::appendContext(Safe<PluginContext>& selfContext){
        m_PluginContext = std::move(selfContext);
    }

    void Plugin::start(){
        m_Loader->load();
        if(!m_Activator){
            auto* activator = m_Loader->getInstance();
            if(!activator){
                MAGIC_WARN() << "Start Plugin Failed";
            }
            m_Activator.reset(activator);
        }
        if(!m_PluginContext){
            MAGIC_WARN() << "Plugin Context Is Null";
            return;
        }
        m_Activator->onStart(m_PluginContext);
    }

    void Plugin::stop(){
        if(!m_Activator){
            MAGIC_WARN() << "Stop Plugin Failed";
            return;
        }
        if(!m_PluginContext){
            MAGIC_WARN() << "Plugin Context Is Null";
            return;
        }
        m_Activator->onStop(m_PluginContext);
    }
    
    const std::string& Plugin::getSymbolicName(){
        return m_Archive->getSymbolicName();
    }
}
