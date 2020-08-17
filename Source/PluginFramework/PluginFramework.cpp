/*
 * @File: PluginFramework.cpp
 * @Author: INotFound
 * @Date: 2020-06-23 10:18:49
 * @LastEditTime: 2020-07-26 20:34:03
 */ 
#include "Logger.h"
#include "Plugin.h"
#include "PluginFramework.h"
namespace Magic{
    PluginFramework::PluginFramework()
        :m_Ctx(new PluginFrameworkContext){
        m_Ctx->init(m_Ctx);
        g_Logger.reset(new Magic::Logger("Root",Magic::LogAppenderMgr::GetInstance()));
    }

    void PluginFramework::installPlugin(const std::string& path){
        m_Ctx->m_Plugins->installPlugin(path);
    }

    const PluginMap& PluginFramework::getPlugins(){
        return m_Ctx->m_Plugins->getPlugins();
    }

    void PluginFramework::setProperty(const std::string& key,const std::any& any){
        m_Ctx->m_GlobalProperties.emplace(key,any);
    }
}
