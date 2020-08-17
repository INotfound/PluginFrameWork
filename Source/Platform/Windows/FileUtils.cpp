/*
 * @File: FileUtils.cpp
 * @Author: INotFound
 * @Date: 2020-07-26 17:51:40
 * @LastEditTime: 2020-07-26 21:56:26
 */ 
#if defined(_WIN32) || defined(_WIN64)
#include <stdio.h>
#include <string.h>

#include "Logger.h"
#include "Platform.h"
#include "FileUtils.h"

namespace Magic{
    bool ReadFileList(const std::string& basePath, std::list<std::string>& paths){
        char findFilename[256];
        memset(findFilename, 0, 256);
        sprintf_s(findFilename, "%s\\*.*", basePath.c_str());
        WIN32_FIND_DATAA findFileData;
        HANDLE hFile = FindFirstFileA(findFilename, &findFileData);
        if(INVALID_HANDLE_VALUE == hFile){
            MAGIC_WARN()  << "Open dir error...";
            return false;
        }
        char temp[256];
        while(true){
            if(findFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
                if(findFileData.cFileName[0] != '.'){
                    memset(temp, 0, 256);
                    sprintf_s(temp, "%s\\%s", basePath.c_str(), findFileData.cFileName);
                    ReadFileList(temp, paths);
                }
            }
            else{
                memset(temp, 0, 256);
                sprintf_s(temp, "%s\\%s", basePath.c_str(), findFileData.cFileName);
                paths.push_back(temp);
            }
            if(!FindNextFileA(hFile, &findFileData)){
                break;
            }
        }
        return true;
    }
}
#endif