/*
 * @File: Services.h
 * @Author: INotFound
 * @Date: 2020-06-17 23:03:25
 * @LastEditTime: 2020-07-26 18:36:51
 */ 
#pragma once
#include <unordered_map>

#include "Core.h"
#include "Mutex.h"
#include "ServiceRegistration.h"

namespace Magic{
    class ServiceRegistration;
    class PluginFrameworkContext;
    typedef std::unordered_map<std::string,Safe<ServiceRegistration>> ServiceMap;
    
    class Services{
    public:
        Services(const Safe<PluginFrameworkContext>& ctx);
        void removeService(const std::string& clazz);
        void removePluginService(const std::string& plugin);
        const Safe<ServiceRegistration>& getServiceRegistration(const std::string& clazz);
        Safe<ServiceRegistration>& registerService(const std::string& clazz,const void* service,const Safe<Plugin>& plugin);
    private:
        Mutex m_Mutex;
        ServiceMap m_Services;
        const Safe<PluginFrameworkContext>& m_Ctx;
        Safe<ServiceRegistration> m_EmptyServiceRegistration;
    };
}
