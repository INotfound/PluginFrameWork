/*
 * @File: Core.h
 * @Author: INotFound
 * @Date: 2020-06-17 21:39:26
 * @LastEditTime: 2020-08-13 23:06:54
 */ 
#pragma once
#include <list>
#include <string>
#include <memory>
#include <unordered_map>

#ifndef Safe
    #define Safe std::shared_ptr
#endif

static const std::string g_EmptyString;

class Noncopyable{
public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

template <class T>
class SingletonPtr{
public:
    static const Safe<T>& GetInstance(){
        static Safe<T> v(new T);
        return v;
    }
};

template <class T> inline const char * PluginInterfaceIId()
{ return nullptr; }

#define MAGIC_SERVICE(TYPE,IId) \
    template <> inline const char *PluginInterfaceIId<TYPE>(){ \
        return IId; \
    }
