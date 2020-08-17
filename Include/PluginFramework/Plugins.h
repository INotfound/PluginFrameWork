/*
 * @File: Plugins.h
 * @Author: INotFound
 * @Date: 2020-06-17 23:03:13
 * @LastEditTime: 2020-07-26 20:33:35
 */ 
#pragma once
#include "Core.h"
#include "Mutex.h"
#include "Plugin.h"

namespace Magic{
    class PluginFrameworkContext;
    typedef std::unordered_map<std::string,Safe<Plugin>> PluginMap;

    class Plugins{
    public:
        Plugins(const Safe<PluginFrameworkContext>& ctx);
        const PluginMap& getPlugins() const;
        void removePlugin(const std::string& name);
        const Safe<Plugin>& installPlugin(const std::string& path);
        const Safe<Plugin>& getPlugin(const std::string& name) const;
    private:
        Mutex m_Mutex;
        PluginMap m_Plugins; 
        Safe<Plugin> m_EmptyPlugin;
        const Safe<PluginFrameworkContext>& m_Ctx;
    };

}