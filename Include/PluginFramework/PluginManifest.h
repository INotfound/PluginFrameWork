/*
 * @File: PluginManifest.h
 * @Author: INotFound
 * @Date: 2020-07-07 16:04:54
 * @LastEditTime: 2020-08-01 09:30:50
 */ 
/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-05-13 09:40:40
 * @LastEditTime: 2020-07-05 13:16:33
 */
#pragma once
#include "Core.h"
#include "Library.h"
#include "PluginActivator.h"


namespace Magic{
    /// 函数类型
    typedef const char* (*content_t)(uint64_t&);
    /**
     * @brief: 插件加载类
     */
    class PluginManifest{
    public:
        /**
         * @brief: 虚构函数
         */
        ~PluginManifest();
        /**
         * @brief: 构造函数
         */
        PluginManifest(const std::string& path);
        /**
         * @brief: 获取数据内容
         * @param length 数据长度
         * @return: 返回数据内容和长度
         */    
        const char* getManifest(uint64_t& length);
    private:
        plugin_t m_Handle;
        std::string m_Path;
        content_t m_Content;
    };
}