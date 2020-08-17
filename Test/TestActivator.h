/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-05 12:35:13
 * @LastEditTime: 2020-07-25 23:36:41
 */ 
#pragma once
#include "TestService.h"
#include "PluginActivator.h"

namespace Test{
    class TestActivator :public Magic::IPluginActivator{
    public:
        ~TestActivator();
        void onStart(Safe<Magic::PluginContext>&) override;
        void onStop(Safe<Magic::PluginContext>&) override;
    private:
        Safe<TestService> m_TestService;
    };
    MAGIC_PLUGIN(Test::TestActivator)
}
