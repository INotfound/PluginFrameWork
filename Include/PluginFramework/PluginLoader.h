/*
 * @File: PluginLoader.h
 * @Author: INotFound
 * @Date: 2020-05-13 09:40:40
 * @LastEditTime: 2020-07-21 21:45:29
 */
#pragma once
#include "Core.h"
#include "Library.h"
#include "PluginActivator.h"

namespace Magic{
     /// 函数类型
    typedef IPluginActivator* (*create_t)(const Safe<LogAppenderManager>&);
    /**
     * @brief: 插件加载类
     */
    class PluginLoader{
    public:
        /**
         * @brief: 虚构函数
         */
        ~PluginLoader();
        /**
         * @brief: 构造函数
         */
        PluginLoader(const std::string& path);
        
        void load();
        /**
         * @brief: 获取实体接口的对象
         * @return: 返回创建接口对象实例
         */
        IPluginActivator* getInstance();
    private:
        create_t m_Create;
        plugin_t m_Handle;
        std::string m_Path;
    };
}