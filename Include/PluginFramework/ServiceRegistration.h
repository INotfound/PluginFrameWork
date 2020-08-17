/*
 * @File: ServiceRegistration.h
 * @Author: INotFound
 * @Date: 2020-06-19 23:54:15
 * @LastEditTime: 2020-07-26 21:25:43
 */ 
#pragma once
#include "Core.h"

namespace Magic{
    class Plugin;
    class ServiceRegistration{
        friend class Services;
        friend class ServiceReference;
    private:
        ServiceRegistration(const void* service,const std::string& clazz,const Safe<Plugin>& plugin);
    private:
        const void* m_Service;
        const std::string m_Clazz;
        const Safe<Plugin>& m_Plugin;
    };
}