#ifndef MACHINE_H
#define MACHINE_H

#include "membermanager.h"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

enum class Type { start, top, bye };

class Machine //机器静态类
{
public:
  Machine() = delete;           //静态类不允许生成类的对象
  static void showTopBar(Type); //显示顶部标题栏
  static void run();            //机器启动
  static void start();          //开始界面
  static void mainUI();         //主菜单UI
  static void end();            //结束界面
  static bool login();          //登录程序
  static bool createAccount(bool = false); //创建账户
  static void memberManagement();          //成员管理
  static void passwordService();           //密码服务
  static void financialManagement();       //收支管理
  static void quitLogin();                 //退出登录
private:
  static Member *mCurrentUser; //指向当前用户的指针
  //各种标题菜单
  static const std::array<std::string, 3> mStartScreenSplash; //开始信息标题栏
  static const std::array<std::string, 3>
      mUserTopScreenSplash; //普通用户信息标题栏
  static const std::array<std::string, 3>
      mRootTopScreenSplash; //管理员信息标题栏
  static const std::array<std::string, 3> mByeScreenSplash; //结束信息标题栏
  static const std::array<std::string, 9> mMainMenu;        //主菜单
  static const std::array<std::string, 10> mMemberMenu;     //成员管理菜单
  static const std::array<std::string, 7> mPassMenu;        //密码服务菜单
  static const std::array<std::string, 13> mFinancialMenu; //收支项目菜单
};

#endif // MACHINE_H
