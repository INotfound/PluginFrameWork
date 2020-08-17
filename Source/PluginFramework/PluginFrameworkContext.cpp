/*
 * @File: PluginFrameworkContext.cpp
 * @Author: INotFound
 * @Date: 2020-06-23 10:19:04
 * @LastEditTime: 2020-07-21 22:14:55
 */ 
#include "Logger.h"
#include "PluginFrameworkContext.h"

namespace Magic{
    void PluginFrameworkContext::init(const Safe<PluginFrameworkContext>& ctx){
        m_Plugins.reset(new Plugins(ctx));
        m_Services.reset(new Services(ctx));
        m_Storage.reset(new PluginStorage);
    }
}