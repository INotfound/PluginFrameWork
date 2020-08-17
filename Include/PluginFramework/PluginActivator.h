/*
 * @File: PluginActivator.h
 * @Author: INotFound
 * @Date: 2020-05-13 09:28:13
 * @LastEditTime: 2020-07-27 22:17:47
 */
#pragma once
#include "Core.h"
#include "Logger.h"
#include "PluginContext.h"
namespace Magic{
    class IPluginActivator{
    public:
        virtual ~IPluginActivator(){};
        virtual void onStart(Safe<Magic::PluginContext>&)    =0;
        virtual void onStop(Safe<Magic::PluginContext>&)     =0;
    };
}

#if (defined(_WIN32) || defined(_WIN64)) && !defined(__GNUC__)
#define MAGIC_PLUGIN(TYPE) \
    extern "C"{ \
        _declspec(dllexport) Magic::IPluginActivator* create(const Safe<Magic::LogAppenderManager>& logAppenderMgr){ \
            std::string logName(#TYPE); \
            Magic::g_Logger.reset(new Magic::Logger(logName.substr(0,logName.find_first_of(':')),logAppenderMgr)); \
            return static_cast<Magic::IPluginActivator*>(new TYPE); \
        } \
    }
#else //#if defined(linux) || defined(__linux__)
#define MAGIC_PLUGIN(TYPE) \
    extern "C" { \
        Magic::IPluginActivator* create(const Safe<Magic::LogAppenderManager>& logAppenderMgr) { \
            std::string logName(#TYPE); \
            Magic::g_Logger.reset(new Magic::Logger(logName.substr(0,logName.find_first_of(':')),logAppenderMgr)); \
            return static_cast<Magic::IPluginActivator*>(new TYPE); \
        } \
    }
#endif