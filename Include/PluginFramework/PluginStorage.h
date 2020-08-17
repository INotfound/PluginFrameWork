/*
 * @File: PluginStorage.h
 * @Author: INotFound
 * @Date: 2020-07-07 15:20:34
 * @LastEditTime: 2020-07-26 18:30:29
 */ 
#include <unordered_map>
#include "Core.h"
#include "PluginArchive.h"
namespace Magic{
    class PluginStorage{
    public:
        PluginStorage();
        void removePlugin(const std::string path);
        const Safe<PluginArchive>& installPlugin(const std::string& path);
    private:
        Safe<PluginArchive> m_EmptyArchive;
        std::unordered_map<std::string,Safe<PluginArchive>> m_Archlives;
    };
}
