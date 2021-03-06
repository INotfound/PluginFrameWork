/*
 * @File: Platform.h
 * @Author: INotFound
 * @Date: 2020-07-17 23:14:41
 * @LastEditTime: 2020-07-17 23:24:27
 */ 
#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <io.h>
#undef DELETE


typedef struct{
    enum class RW {
        Read,
        Wirte
    };
    RW flag;
    SRWLOCK lock;
}WinRWLock;

typedef HANDLE               sem_t;
typedef HANDLE               mutex_t;
typedef WinRWLock            rwlock_t;
typedef HINSTANCE            plugin_t;
typedef CRITICAL_SECTION     spinlock_t;
#define IS_FILE(Path)        _access(Path,0)
#endif

#if defined(linux) || defined(__linux__)
#include <dlfcn.h>
#include <sys/io.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <execinfo.h>
#include <semaphore.h>
#include <sys/syscall.h>

typedef sem_t                sem_t;
typedef pthread_mutex_t      mutex_t;
typedef pthread_spinlock_t   spinlock_t;
typedef pthread_rwlock_t     rwlock_t;
typedef void*                plugin_t;
#define IS_FILE(Path)        access(Path,0)
#endif