#ifndef MACHINE_H
#define MACHINE_H

#include "membermanager.h"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

enum class Type { start, top, bye };

class Machine //������̬��
{
public:
  Machine() = delete;           //��̬�಻����������Ķ���
  static void showTopBar(Type); //��ʾ����������
  static void run();            //��������
  static void start();          //��ʼ����
  static void mainUI();         //���˵�UI
  static void end();            //��������
  static bool login();          //��¼����
  static bool createAccount(bool = false); //�����˻�
  static void memberManagement();          //��Ա����
  static void passwordService();           //�������
  static void financialManagement();       //��֧����
  static void quitLogin();                 //�˳���¼
private:
  static Member *mCurrentUser; //ָ��ǰ�û���ָ��
  //���ֱ���˵�
  static const std::array<std::string, 3> mStartScreenSplash; //��ʼ��Ϣ������
  static const std::array<std::string, 3>
      mUserTopScreenSplash; //��ͨ�û���Ϣ������
  static const std::array<std::string, 3>
      mRootTopScreenSplash; //����Ա��Ϣ������
  static const std::array<std::string, 3> mByeScreenSplash; //������Ϣ������
  static const std::array<std::string, 9> mMainMenu;        //���˵�
  static const std::array<std::string, 10> mMemberMenu;     //��Ա����˵�
  static const std::array<std::string, 7> mPassMenu;        //�������˵�
  static const std::array<std::string, 13> mFinancialMenu; //��֧��Ŀ�˵�
};

#endif // MACHINE_H
