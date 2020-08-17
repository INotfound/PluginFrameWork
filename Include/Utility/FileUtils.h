/*
 * @File: FileUtils.h
 * @Author: INotFound
 * @Date: 2020-07-23 00:03:37
 * @LastEditTime: 2020-07-26 21:52:14
 */ 
#pragma once
#include "Core.h"

namespace Magic{
    bool ReadFileList(const std::string& basePath,std::list<std::string>& paths);
}