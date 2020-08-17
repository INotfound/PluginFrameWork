/*
 * @File: ServiceReference.cpp
 * @Author: INotFound
 * @Date: 2020-07-11 00:24:09
 * @LastEditTime: 2020-07-26 21:42:00
 */ 
#include "Logger.h"
#include "ServiceReference.h"
#include "ServiceRegistration.h"

namespace Magic{
    ServiceReference::ServiceReference(const Safe<ServiceRegistration>& registration)
        :m_Registration(registration){
    }
    
    ServiceReference::operator bool() const{
        if(m_Registration && m_Registration->m_Plugin){
            return true;
        }
        return false;
    }

    const void* ServiceReference::getService() const{
        return m_Registration->m_Service;
    }

    const std::string& ServiceReference::getClazz() const{
        return m_Registration->m_Clazz;
    }
}