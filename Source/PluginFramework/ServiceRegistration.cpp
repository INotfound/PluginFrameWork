/*
 * @File: ServiceRegistration.cpp
 * @Author: INotFound
 * @Date: 2020-07-10 23:27:10
 * @LastEditTime: 2020-07-26 21:25:51
 */ 
#include "Logger.h"
#include "ServiceRegistration.h"

namespace Magic{
    ServiceRegistration::ServiceRegistration(const void* service,const std::string& clazz,const Safe<Plugin>& plugin)
        :m_Service(service)
        ,m_Clazz(clazz)
        ,m_Plugin(plugin){
    }
}