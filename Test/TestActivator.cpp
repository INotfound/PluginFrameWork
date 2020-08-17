/*
 * @File: 
 * @Author: INotFound
 * @Date: 2020-07-05 12:35:21
 * @LastEditTime: 2020-07-26 21:05:06
 */ 
#include <iostream>
#include "PluginContext.h"
#include "TestActivator.h"

namespace Test{
    TestActivator::~TestActivator(){}
    
    void TestActivator::onStart(Safe<Magic::PluginContext>& ctx){

        try{
            m_TestService.reset(new TestService);
            ctx->registerService<TestService>(m_TestService.get());
            MAGIC_DEBUG() << "Hello TestActivator!";
            auto ref = ctx->getServiceReference<TestService>();
            TestService* test = ctx->getService<TestService>(ref);
            test->printf();
            //ctx->unRegisterService(ref);
            ctx->unInstallPlugin("Client2");
        }
        catch (const std::exception& ec){
            MAGIC_DEBUG() << ec.what();
        }
        
        //if (ref) {
        //    MAGIC_DEBUG() << "true";
        //}
        //else {
        //    MAGIC_DEBUG() << "false";
        //}
    }

    void TestActivator::onStop(Safe<Magic::PluginContext>&){
        MAGIC_DEBUG() << "Stop";
    }
}