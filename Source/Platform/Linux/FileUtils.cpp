/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-26 17:48:59
 * @LastEditTime: 2020-07-26 21:54:35
 */ 
#if defined(linux) || defined(__linux__)
#include <string.h>

#include "Logger.h"
#include "Platform.h"
#include "FileUtils.h"

namespace Magic{
    bool ReadFileList(const std::string& basePath,std::list<std::string>& paths){
        DIR *dir;
        char base[1000];
        struct dirent *direntPtr;
        if((dir=opendir(basePath.c_str())) == nullptr){
            MAGIC_WARN() << "Open dir error...";
            return false;
        }
        
        std::string path;
        while((direntPtr=readdir(dir)) != nullptr){
            path.clear();
            if(strcmp(direntPtr->d_name,".")==0 || strcmp(direntPtr->d_name,"..")==0)    ///current dir OR parrent dir
                continue;
            else if(direntPtr->d_type == 8){
                path += basePath;
                path += "/";
                path += direntPtr->d_name;
                paths.push_back(path);
            }else if(direntPtr->d_type == 10){
                path += basePath;
                path += "/";
                path += direntPtr->d_name;
                paths.push_back(path);
            }
            if(direntPtr->d_type == 4)
            {
                memset(base,0,sizeof(base));
                strcpy(base,basePath.c_str());
                strcat(base,"/");
                strcat(base,direntPtr->d_name);
                ReadFileList(base,paths);
            }
        }
        closedir(dir);
        return true;
    }
}
#endif