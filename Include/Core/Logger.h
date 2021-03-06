/*
 * @File: Logger.h
 * @Author: INotFound
 * @Date: 2020-07-16 22:18:46
 * @LastEditTime: 2020-07-23 22:29:12
 */ 
#pragma once
#include <sstream>
#include <fstream>

#include "Core.h"
#include "Mutex.h"
#include "Thread.h"
#include "TimerUtils.h"
#include "StringUtils.h"

namespace Magic{
    /**
     * @brief: 日志级别枚举类
     */
    enum class LogLevel{
        Debug    = 1,
        Info     = 2,
        Warn     = 3,
        Error    = 4,
        Fatal    = 5
    };
    /**
     * @brief: 日志级别枚举转字符串
     */
    const char* ToString(const LogLevel level);
    /**
     * @brief: 日志事件类
     */
    class LogEvent{
    public:
        /**
         * @brief: 构造函数
         * @param line 行数
         * @param time 时间
         * @param elapse 耗时
         * @param threadId 线程Id
         * @param file 文件名称
         * @param LogName 日志器名称
         * @param threadName 线程名称
         */
        LogEvent(uint32_t line, uint64_t time, uint64_t elapse,
            uint64_t threadId, const std::string& file, const std::string& LogName, const std::string& threadName);
        /**
         * @brief: 获取行数
         * @return: 返回行数
         */
        uint32_t getLine()                  const;
        /**
         * @brief: 获取时间
         * @return: 返回时间
         */
        uint64_t getTime()                  const;
        /**
         * @brief: 获取耗时
         * @return: 返回耗时
         */
        uint64_t getElapse()                const;
        /**
         * @brief: 获取线程Id
         * @return: 返回线程Id
         */
        uint64_t getThreadId()              const;
        /**
         * @brief: 获取日志正文
         * @return: 返回日志正文
         */
        const std::string  getContent()     const;
        /**
         * @brief: 获取文件名称
         * @return: 返回文件名称
         */
        const std::string& getFile()        const;
        /**
         * @brief: 获取日志器名称
         * @return: 返回日志器名称
         */
        const std::string& getLogName()     const;
        /**
         * @brief: 获取线程名称
         * @return: 返回线程名称
         */
        const std::string& getThreadName()  const;
        /**
         * @brief: 获取输出流
         * @return: 返回输出流
         */
        std::stringstream& getStream();
    private:
        uint32_t m_Line;
        uint64_t m_Time;
        uint64_t m_Elapse;
        uint64_t m_ThreadId;
        std::string m_File;
        std::string m_LogName;
        std::string m_ThreadName;
        std::stringstream m_StringStream;
    };
    /**
     * @brief: 日志格式化项类
     */
    class ILogFormatItem{
    public:
        virtual ~ILogFormatItem();
        virtual void format(std::ostream& os, const LogLevel  level, const Safe<LogEvent>& event) = 0;
    };
    /**
     * @brief: 日志格式化类
     */
    class LogFormatter{
    public:
        /**
         * @brief: 构造函数
         * @param pattern 格式化字符串
         */
        explicit LogFormatter(const std::string& pattern);
        /**
         * @brief: 格式化函数
         * @param os 输出流
         * @param level 日志级别
         * @param event 日志事件
         */
        void format(std::ostream& os, const LogLevel  level, const Safe<LogEvent>& event);
    private:
        std::list<Safe<ILogFormatItem>> m_Items;
    };
    /**
     * @brief: 日志附加器类
     */
    class ILogAppender{
        friend class LogAppenderManager;
    public:
        /**
         * @brief: 虚析构函数
         */
        virtual ~ILogAppender(){};
        /**
         * @brief: 日志输出函数
         * @param level 日志级别
         * @param event 日志事件
         */
        virtual void log(LogLevel level,const Safe<LogEvent>& event) = 0;
    protected:
        Safe<LogFormatter> m_Formatter;
    };
    /**
     * @brief: 日志附加器管理器类
     */
    class LogAppenderManager{
        friend class Logger;
    public:
        LogAppenderManager();
        /**
         * @brief: 设置日志格式化器函数
         * @param level 日志级别
         */
        void setFormatter(const std::string& pattern);
        /**
         * @brief: 添加日志附件器
         * @param logAppender 日志附件器
         */
        void addILogAppender(Safe<ILogAppender>& logAppender);
        /**
         * @brief: 删除日志附件器
         * @param logAppender 日志附件器
         */
        void delILogAppender(Safe<ILogAppender>& logAppender);
    private:
         /**
         * @brief: 日志输出函数
         * @param level 日志级别
         * @param event 日志事件
         */
        void log(LogLevel level,const Safe<LogEvent>& event);
    private:
        Mutex m_Mutex;
        std::string m_Formatter;
        std::list<Safe<ILogAppender>> m_ILogAppenders;
    };
    /**
     * @brief: 日志器类
     */
    class Logger{
    public:
        /**
         * @brief: 构造函数
         * @param name 日志名称
         */
        Logger(const std::string& name,const Safe<LogAppenderManager>& logAppenderMgr);
        /**
         * @brief: 设置日志级别函数
         * @param level 日志级别
         */
        void setLevel(LogLevel level);
        /**
         * @brief: 获取日志级别函数
         * @return: 返回日志级别
         */
        LogLevel getLevel() const;
        /**
         * @brief: 设置日志名称函数
         * @return: 返回日志名称
         */
        const std::string& getLogName() const;
        /**
         * @brief: 日志输出函数
         * @param level 日志级别
         * @param event 日志事件
         */
        void log(LogLevel level,const Safe<LogEvent>& event);
    private:
        Mutex m_Mutex;
        LogLevel m_Level;
        std::string m_LogName;
        const Safe<LogAppenderManager>& m_LogAppenderMgr;
    };
    /**
     * @brief: 日志包装器类
     */
    class LogWrap{
    public:
        /**
         * @brief: 析构函数
         */
        ~LogWrap();
        /**
         * @brief: 构造函数
         * @param level 日志级别
         * @param event 日志事件
         * @param logger 日志器
         */
        LogWrap(const LogLevel level, Safe<LogEvent>&& event ,const Safe<Logger>& logger);
        /**
         * @brief:获取输出流函数 
         * @return 返回输出流
         */
        std::stringstream& get();
    private:
        LogLevel m_Level;
        Safe<LogEvent> m_Event;
        const Safe<Logger>& m_Logger;
    };
    /**
     * @brief: 日志文件附加器类
     */
    class FileLogAppender :public ILogAppender{
    public:
        explicit FileLogAppender(const std::string& path);
        void log(LogLevel level,const Safe<LogEvent>& event) override;
    private:
        //Mutex m_Mutex;
        std::string m_Path;
        std::ofstream m_FileStream;
    };
    /**
     * @brief: 日志网页附加器类
     */
    class HtmlLogAppender :public ILogAppender{
    public:
        explicit HtmlLogAppender(const std::string& path);
        void log(LogLevel level,const Safe<LogEvent>& event) override;
    private:
        //Mutex m_Mutex;
        std::string m_Path;
        std::ofstream m_FileStream;
    };
    /**
     * @brief: 日志标准输出附加器类
     */
    class StdOutLogAppender :public ILogAppender{
    public:
        void log(LogLevel level,const Safe<LogEvent>& event) override;
    };
    extern Safe<Logger> g_Logger;
    typedef SingletonPtr<LogAppenderManager> LogAppenderMgr;
}

#define  MAGIC_LOG_LEVEL(logger,level)                                \
            if(level >= logger->getLevel())                           \
                Magic::LogWrap(                                       \
                    level,                                            \
                    Safe<Magic::LogEvent>(                            \
                        new Magic::LogEvent(                          \
                            __LINE__,                                 \
                            static_cast<uint64_t>(time(nullptr)),     \
                            Magic::GetCurrentTimeMS(),                \
                            Magic::GetThreadId(),                     \
                            __FILE__,                                 \
                            logger->getLogName(),                     \
                            Magic::Thread::GetName())),               \
                    logger                                            \
                ).get()

#define MAGIC_INFO()         MAGIC_LOG_LEVEL(Magic::g_Logger,Magic::LogLevel::Info)
#define MAGIC_WARN()         MAGIC_LOG_LEVEL(Magic::g_Logger,Magic::LogLevel::Warn)
#define MAGIC_DEBUG()        MAGIC_LOG_LEVEL(Magic::g_Logger,Magic::LogLevel::Debug)
#define MAGIC_ERROR()        MAGIC_LOG_LEVEL(Magic::g_Logger,Magic::LogLevel::Error)
#define MAGIC_FATAL()        MAGIC_LOG_LEVEL(Magic::g_Logger,Magic::LogLevel::Fatal)