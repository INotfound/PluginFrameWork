/*
 * @File: PluginContext.cpp
 * @Author: INotFound
 * @Date: 2020-06-23 10:19:21
 * @LastEditTime: 2020-07-26 20:47:24
 */ 
#include "Logger.h"
#include "Plugin.h"
#include "PluginContext.h"
#include "PluginFrameworkContext.h"
namespace Magic{
    PluginContext::PluginContext(const Safe<Plugin>& plugin)
        :m_Plugin(plugin){
    }

    void PluginContext::installPlugin(const std::string& path){
        m_Plugin->m_Ctx->m_Plugins->installPlugin(path);
    }

    void PluginContext::unInstallPlugin(const std::string& name){
        m_Plugin->m_Ctx->m_Services->removePluginService(name);
        m_Plugin->m_Ctx->m_Plugins->removePlugin(name);
    }

    void PluginContext::unRegisterService(ServiceReference& reference){
        m_Plugin->m_Ctx->m_Services->removeService(reference.getClazz());
    }

    const void* PluginContext::getService(const ServiceReference& ref) const{
        return ref.getService();
    }

    void PluginContext::registerService(const char* iid,const void* service){
        m_Plugin->m_Ctx->m_Services->registerService(iid,service,m_Plugin);
    }

    ServiceReference PluginContext::getServiceReference(const std::string& iid){
        auto& serviceRegistration = m_Plugin->m_Ctx->m_Services->getServiceRegistration(iid);
        /// NRVO(named-return value optimization) and RVO(unnamed-return value optimization) C++17起才是强制要求
        return ServiceReference(serviceRegistration);/// C++11 copy elision
    }

    std::any& PluginContext::getProperty(const std::string& key){
        auto iter = m_Plugin->m_Ctx->m_GlobalProperties.find(key);
        if(iter != m_Plugin->m_Ctx->m_GlobalProperties.end()){
            return iter->second;
        }
        MAGIC_WARN() << "Property Not Found: " << key;
        return m_EmptyProperty;
    }
}
