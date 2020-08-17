/*
 * @File: Services.cpp
 * @Author: INotFound
 * @Date: 2020-07-11 00:46:26
 * @LastEditTime: 2020-07-26 21:40:51
 */ 
#include "Logger.h"
#include "Plugin.h"
#include "Plugins.h"
#include "Services.h"
#include "PluginFrameworkContext.h"

namespace Magic{
    Services::Services(const Safe<PluginFrameworkContext>& ctx)
        :m_Ctx(ctx){
    }

    void Services::removeService(const std::string& clazz){
        Mutex::Lock lock(m_Mutex);
        auto iter = m_Services.find(clazz);
        if(iter != m_Services.end()){
            iter->second.reset();
        }
    }
    
    void Services::removePluginService(const std::string& name){
        auto& plugin = m_Ctx->m_Plugins->getPlugin(name);
        if(plugin){
            for(auto& v : plugin->m_Clazzs){
                this->removeService(v);
            }
            Mutex::Lock lock(m_Mutex);
            plugin->m_Clazzs.clear();
        }
    }

    const Safe<ServiceRegistration>& Services::getServiceRegistration(const std::string& clazz){
        auto iter = m_Services.find(clazz);
        if(iter != m_Services.end()){
            return iter->second;
        }
        MAGIC_WARN() << "Service Not Found: " << clazz;
        return m_EmptyServiceRegistration;
    }
    
    Safe<ServiceRegistration>& Services::registerService(const std::string& clazz,const void* service,const Safe<Plugin>& plugin){
        Mutex::Lock lock(m_Mutex);
        auto iter = m_Services.find(clazz);
        if(iter != m_Services.end()){
            if(iter->second){
                MAGIC_WARN() << "Duplicate Registration Service: " << clazz;
                return iter->second;
            }
            plugin->m_Clazzs.emplace_back(clazz);
            iter->second.reset(new ServiceRegistration(service,clazz,plugin));
            return iter->second;
        }
        plugin->m_Clazzs.emplace_back(clazz);
        Safe<ServiceRegistration> registration(new ServiceRegistration(service,clazz,plugin));
        m_Services.emplace(clazz,std::move(registration));
        return m_Services[clazz];
    }
}