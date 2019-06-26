//
// Created by xcy on 19-6-26.
//
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include "AuboSDK.h"

#define SERVER_HOST "192.168.1.13"
#define SERVER_PORT 8899

AuboSDK::AuboSDK()
{
    robotService = new ServiceInterface;
}
AuboSDK::~AuboSDK()
{
    delete robotService;
}
bool AuboSDK::robotStartUp()
{
    ret = robotService->robotServiceLogin(SERVER_HOST,SERVER_PORT,"aubo", "123456");
    if(ret == aubo_robot_namespace::InterfaceCallSuccCode)
    {
        std::cerr<<"登录成功."<<std::endl;
    }
    else
    {
        std::cerr<<"登录失败."<<std::endl;
        return false;
    }
    //工具动力学参数
    aubo_robot_namespace::ToolDynamicsParam toolDynamicsParam;
    memset(&toolDynamicsParam, 0, sizeof(toolDynamicsParam));

    ret = robotService->rootServiceRobotStartup(toolDynamicsParam/**工具动力学参数**/,
                                                6        /*碰撞等级*/,
                                                true     /*是否允许读取位姿　默认为true*/,
                                                true,    /*保留默认为true */
                                                1000,    /*保留默认为1000 */
                                                result); /*机械臂初始化*/
    if(ret == aubo_robot_namespace::InterfaceCallSuccCode)
    {
        std::cerr<<"机械臂初始化成功."<<std::endl;
    }
    else
    {
        std::cerr<<"机械臂初始化失败."<<std::endl;
        return false;
    }
    return true;
}
int AuboSDK::robotShutDown()
{
    /** 机械臂Shutdown **/
    robotService->robotServiceRobotShutdown();
    /** 接口调用: 退出登录　**/
    robotService->robotServiceLogout();

    return aubo_robot_namespace::InterfaceCallSuccCode;
}
void AuboSDK::RealTimeEventInfoCallback(const aubo_robot_namespace::RobotEventInfo *pEventInfo, void *arg)
{
    (void)arg;
    Util::printEventInfo(*pEventInfo);
}
bool AuboSDK::robotEventRegister()
{
    ret = robotService->robotServiceRegisterRobotEventInfoCallback(AuboSDK::RealTimeEventInfoCallback, NULL);
    if(ret == aubo_robot_namespace::InterfaceCallSuccCode)
        return true;
    else
        return false;
}
bool AuboSDK::getSwitchStatus()
{
    double value;
    ret = robotService->robotServiceGetBoardIOStatus(aubo_robot_namespace::RobotBoardUserDI, "U_DI_00", value);
    std::cout<<"微动开关IO状态为 "<<value<<std::endl;
    if(ret == aubo_robot_namespace::InterfaceCallSuccCode)
        return true;
    else
        return false;
}

