/*
 * @File: PluginFrameworkContext.h
 * @Author: INotFound
 * @Date: 2020-06-17 22:38:35
 * @LastEditTime: 2020-07-26 18:16:55
 */ 
#pragma once
#include "Any.h"
#include "Plugins.h"
#include "Services.h"
#include "PluginStorage.h"

namespace Magic{
    typedef std::unordered_map<std::string,std::any> PropertieMap;
    class PluginFrameworkContext{
        friend class Plugins;
        friend class Services;
        friend class PluginContext;
        friend class PluginFramework;
    private:
        void init(const Safe<PluginFrameworkContext>& ctx);
    private:
        Safe<Plugins> m_Plugins;
        Safe<Services> m_Services;
        Safe<PluginStorage> m_Storage;
        PropertieMap m_GlobalProperties;
    };
}