/*
 * @File: PluginFramework.h
 * @Author: INotFound
 * @Date: 2020-05-13 09:59:06
 * @LastEditTime: 2020-07-13 21:51:32
 */
#pragma once
#include <list>
#include "Core.h"
#include "PluginFrameworkContext.h"
namespace Magic{
    class Plugin;
    class PluginFramework{
    public:
        PluginFramework();
        void installPlugin(const std::string& path);
        const PluginMap& getPlugins();
        void setProperty(const std::string& key,const std::any& any);
    private:
        Safe<PluginFrameworkContext> m_Ctx;
    };
}