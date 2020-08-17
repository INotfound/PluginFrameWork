/*
 * @File: Thread.h
 * @Author: INotFound
 * @Date: 2020-07-21 23:26:10
 * @LastEditTime: 2020-07-21 23:35:26
 */ 
#pragma once
#include <thread>
#include <functional>

#include "Core.h"
#include "Mutex.h"

namespace Magic{
    /**
     * @brief: 线程类
     */
    class Thread :public Noncopyable{
    public:
        /**
         * @brief: 析构函数
         */
        ~Thread();
        /**
         * @brief: 构造函数
         * @param threadName 线程名称
         * @param callBack 回调函数
         */
        Thread(const std::string& threadName,const std::function<void()>& callBack);
        /**
         * @brief: 等待线程执行函数
         */
        void join();
        /**
         * @brief: 分离线程执行函数
         */
        void detach();
        /**
         * @brief: 获取线程Id函数
         * @return: 返回线程Id,若返回-1,即线程未初始化
         */
        int64_t getId();
        /**
         * @brief: 获取线程名称
         * @return: 返回线程名,若返回空,即线程未初始化
         */
        static const std::string& GetName();
        /**
         * @brief: 设置线程名称
         * @param threadName 需设置的线程名称
         */
        static void SetName(const std::string& threadName);
    protected:
        /**
         * @brief: 线程内部回调函数
         */
        void run();
    private:
        int64_t  m_Id;
        Semaphore m_Mutex;
        std::string m_Name;
        std::thread m_Thread;
        std::function<void()> m_CallBack;
    };
    /**
     * @brief: 获取线程Id
     * @return: 返回线程Id
     */
    uint64_t GetThreadId();
}