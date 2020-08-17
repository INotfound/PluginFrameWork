/*
 * @File: Plugin.h
 * @Author: INotFound
 * @Date: 2020-06-16 16:03:45
 * @LastEditTime: 2020-07-26 20:48:03
 */ 
#pragma once
#include "Core.h"
#include "PluginLoader.h"
#include "PluginContext.h"
#include "PluginActivator.h"

namespace Magic{
    class PluginArchive;
    class PluginFrameworkContext;

    class Plugin{
        friend class Plugins;
        friend class Services;
        friend class PluginContext;
    public:
        void start();
        void stop();
        const std::string& getSymbolicName();
    private:
        Plugin(const Safe<PluginArchive>& archive,const Safe<PluginFrameworkContext>& ctx);
        void appendContext(Safe<PluginContext>& selfContext);
    private:
        Safe<PluginLoader> m_Loader;
        std::list<std::string> m_Clazzs;
        Safe<IPluginActivator> m_Activator;
        Safe<PluginContext> m_PluginContext;
        const Safe<PluginArchive>& m_Archive;
        const Safe<PluginFrameworkContext>& m_Ctx;
    };
}
