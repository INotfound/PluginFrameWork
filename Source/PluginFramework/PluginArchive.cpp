/*
 * @File: PluginArchive.cpp
 * @Author: INotFound
 * @Date: 2020-06-23 17:43:06
 * @LastEditTime: 2020-07-26 17:19:37
 */ 
#include "Logger.h"
#include "PluginArchive.h"

namespace Magic{
    PluginArchive::PluginArchive(const std::string& path,const std::string& content)
        :m_Path(path){
        std::string key;
        std::string value;
        bool isValue = false;
        size_t length = content.length();
        for(size_t i = 0; i < length; i++){
            std::string::value_type charValue = content.at(i);
            
            if(charValue == '\n' || i == (length - 1)){
                isValue = false;
                value.append(1, charValue);
                m_KeyValue.emplace(key,value);
                key.clear();
                value.clear();
                continue;
            }
            
            if(charValue == ':'){
                isValue = true;
                continue;
            }
            
            if(charValue == ' ' || charValue == '\r'){
                continue;
            }

            if(isValue){
                value.append(1,charValue);
                continue;
            }

            key.append(1,charValue);
        }
    }

    const std::string& PluginArchive::getLocation() const{
        return m_Path;
    }
    
    const std::string& PluginArchive::getSymbolicName() const{
        auto iter = m_KeyValue.find("Plugin-SymbolicName");
        if(iter != m_KeyValue.end()){
            return iter->second;
        }
        return g_EmptyString;
    }
}