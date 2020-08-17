/*
 * @File: PluginStorage.cpp
 * @Author: INotFound
 * @Date: 2020-07-07 15:21:30
 * @LastEditTime: 2020-08-01 09:31:13
 */ 
#include "Logger.h"
#include "PluginStorage.h"
#include "PluginManifest.h"
namespace Magic{
    PluginStorage::PluginStorage(){
    }
    void PluginStorage::removePlugin(const std::string path){
        auto iter = m_Archlives.find(path);
        if(iter != m_Archlives.end()){
            m_Archlives.erase(iter);
        }
    }
    const Safe<PluginArchive>& PluginStorage::installPlugin(const std::string& path){
        auto iter = m_Archlives.find(path);
        if(iter != m_Archlives.end()){
            return  iter->second;
        }
        PluginManifest manifest(path);
        uint64_t length = 0;
        const char* data = manifest.getManifest(length);
        std::string content(data,length);
        if(length > 0  &&  !content.empty()){
            Safe<PluginArchive> archive(new PluginArchive(path,content));
            m_Archlives.emplace(path,std::move(archive));
            return m_Archlives[path];
        }
        MAGIC_WARN() << "Load Plugin Resources Failed: " << path;
        return m_EmptyArchive;
    }
}