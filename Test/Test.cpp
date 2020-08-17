/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-08 16:40:20
 * @LastEditTime: 2020-07-27 11:56:02
 */ 
#include <cstdlib>
#include <iostream>
#include "PluginFramework.h"

    // if(true){
    //     MAGIC_DEBUG() << "true";
    // }else
    //     MAGIC_DEBUG() << "false";

int main(){

    try{
        Safe<Magic::ILogAppender> stdOutLogAppender(new Magic::StdOutLogAppender);
        Magic::LogAppenderMgr::GetInstance()->addILogAppender(stdOutLogAppender);
        Magic::PluginFramework framework;
        MAGIC_DEBUG() << "Init Framework";
#if defined(_WIN32) || defined(_WIN64)
        framework.installPlugin("C:/Users/61419/Desktop/Magic/Test/out/build/x64-Debug/Client2.dll");
        framework.installPlugin("C:/Users/61419/Desktop/Magic/Test/out/build/x64-Debug/TestPlugins.dll");
#else
        framework.installPlugin("/home/magic/WorkSpace/Magic/build/test/libClient2.so");
        framework.installPlugin("/home/magic/WorkSpace/Magic/build/test/libTestPlugins.so");
#endif
        auto& map = framework.getPlugins();
        map.find("Client2")->second->start();
        map.find("Client1")->second->start();
        MAGIC_DEBUG() << "233333333333333";
    }catch(std::system_error ec){
        std::cout << ec.what() << std::endl;
    }
    return EXIT_SUCCESS;
}