/*
 * @File: PluginContext.h
 * @Author: INotFound
 * @Date: 2020-05-13 09:27:50
 * @LastEditTime: 2020-07-26 19:21:19
 */
#pragma once
#include "Any.h"
#include "Core.h"
#include "ServiceReference.h"

namespace Magic{
    class Plugin;

    class PluginContext{
        friend class Plugin;
        friend class Plugins;
    public:
        //void getPlugin();

        void installPlugin(const std::string& path);
        
        void unInstallPlugin(const std::string& name);

        void unRegisterService(ServiceReference& reference);

        template<class T>
        T* getService(const ServiceReference& ref){
            auto service = this->getService(ref);
            return reinterpret_cast<T*>(const_cast<void*>(service));
        }

        template<class T>
        void registerService(const void* service){
          const char* iid = PluginInterfaceIId<T>();
          this->registerService(iid,service);
        }

        template<class T>
        ServiceReference getServiceReference(){
           const char* iid = PluginInterfaceIId<T>();
           return this->getServiceReference(iid);
        }
        
        std::any& getProperty(const std::string& key);
    private:
        PluginContext(const Safe<Plugin>& plugin);
        const void* getService(const ServiceReference& ref) const;
        void registerService(const char* iid,const void* service);
        ServiceReference getServiceReference(const std::string& iid);
    private:
        std::any m_EmptyProperty;
        const Safe<Plugin>& m_Plugin;
    };
}