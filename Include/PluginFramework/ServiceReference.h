/*
 * @File: ServiceReference.h
 * @Author: INotFound
 * @Date: 2020-07-11 00:24:03
 * @LastEditTime: 2020-07-26 21:17:55
 */ 
#pragma once
#include "Core.h"

namespace Magic{
    class PluginContext;
    class ServiceRegistration;
 
    class ServiceReference{
        friend class PluginContext;
    public:
        operator bool() const;
    private:
        ServiceReference(const Safe<ServiceRegistration>& registration);
        const void* getService() const;
        const std::string& getClazz() const;
    private:
        const Safe<ServiceRegistration>& m_Registration;
    };
}