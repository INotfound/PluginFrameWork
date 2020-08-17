/*
 * @File: PluginArchive.h
 * @Author: INotFound
 * @Date: 2020-06-23 10:56:08
 * @LastEditTime: 2020-07-26 17:06:48
 */ 
#pragma once
#include "Core.h"

namespace Magic{
    class PluginArchive{
    public:
        PluginArchive(const std::string& path,const std::string& content);
        const std::string& getLocation() const;
        const std::string& getSymbolicName() const;
    private:
        std::string m_Path;
        std::unordered_map<std::string,std::string> m_KeyValue;
    };
}