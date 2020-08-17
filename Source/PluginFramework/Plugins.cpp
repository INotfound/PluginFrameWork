/*
 * @File: Plugins.cpp
 * @Author: INotFound
 * @Date: 2020-06-23 10:19:46
 * @LastEditTime: 2020-07-26 21:36:10
 */
#include "Logger.h"
#include "Plugin.h"
#include "Plugins.h"
#include "PluginArchive.h"
#include "PluginContext.h"
#include "PluginFrameworkContext.h"

namespace Magic{
    Plugins::Plugins(const Safe<PluginFrameworkContext>& ctx)
        :m_Ctx(ctx){
    }

    const PluginMap& Plugins::getPlugins() const{
        return m_Plugins;
    }

    void Plugins::removePlugin(const std::string& name){
        Mutex::Lock lock(m_Mutex);
        auto iter = m_Plugins.find(name);
        if(iter != m_Plugins.end()){
            iter->second->stop();
            m_Ctx->m_Storage->removePlugin(iter->second->m_Archive->getLocation());
            iter->second.reset();
            
        }
    }

    const Safe<Plugin>& Plugins::installPlugin(const std::string& path){
        Mutex::Lock lock(m_Mutex);
        auto& archive = m_Ctx->m_Storage->installPlugin(path);
        if(!archive){
            return m_EmptyPlugin;
        }
        auto& symbolic = archive->getSymbolicName();
        auto iter = m_Plugins.find(symbolic);
        if(iter != m_Plugins.end()){
            if(iter->second){
                return iter->second;
            }
            iter->second.reset(new Plugin(archive,m_Ctx));
            Safe<PluginContext> context(new PluginContext(iter->second));
            iter->second->appendContext(context);
            return iter->second;
        }
        MAGIC_INFO() << "Installing Plugin: " << symbolic;
        
        Safe<Plugin> plugin(new Plugin(archive,m_Ctx));
        m_Plugins.emplace(symbolic,std::move(plugin));
        /// 获取m_Plugins中的元素引用
        auto& pluginRef = m_Plugins[symbolic];
        Safe<PluginContext> context(new PluginContext(pluginRef));
        pluginRef->appendContext(context);
        return pluginRef;
    }
    
    const Safe<Plugin>& Plugins::getPlugin(const std::string& name) const{
        for(auto& v : m_Plugins){
            return v.second;
        }
        MAGIC_WARN() << "Plugin Not Found: " << name;
        return m_EmptyPlugin;
    }
}

