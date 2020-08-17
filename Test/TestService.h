/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-11 17:21:15
 * @LastEditTime: 2020-07-17 00:49:51
 */ 
#pragma once
#include "PluginFramework.h"
namespace Test{
    class TestService{
    public:
        void printf();
    };
}
MAGIC_SERVICE(Test::TestService,"com.Test.TestService")
