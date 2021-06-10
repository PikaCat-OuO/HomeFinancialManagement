#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include "member.h"
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>

class Item //һ����֧��Ŀ��
{
public:
  Item();
  Item(std::string);
  const std::string getName() const;     //����һ����֧��Ŀ����
  std::vector<std::string> &getBranch(); //���ض�����֧��Ŀ�ܺ�
  const std::vector<std::string> &getBranch() const; //���ض�����֧��Ŀ�ܺ�Const
  void setName(std::string); //����һ����֧��Ŀ����
private:
  std::string mName;                //���һ����֧��Ŀ
  std::vector<std::string> mBranch; //��Ŷ�����֧��Ŀ
};

class MemberManager //��̬��Ա������
{
public:
  //��̬�಻�������ɶ���
  MemberManager() = delete;
  static std::vector<Member>::reference
      emplaceMember(std::string, Sex, size_t, size_t, size_t, size_t, size_t,
                    size_t, Permission, std::string); //��ӳ�Ա
  static void addMember(const Member &);              //��ӳ�Ա
  static void addItem(std::string);                   //���һ����֧��Ŀ
  static void addItem(std::string, std::string);      //��Ӷ�����֧��Ŀ
  static bool editItem(std::string, std::string);     //�༭һ����֧��Ŀ
  static bool editItem(std::string, std::string,
                       std::string);         //�༭������֧��Ŀ
  static bool removeItemByName(std::string); //ͨ�������Ƴ�һ����֧��Ŀ
  static bool removeItemByName(std::string,
                               std::string); //ͨ�������Ƴ�������֧��Ŀ
  static bool removeMemberByName(std::string); //ͨ�������Ƴ���Ա
  static Member *getMemberByName(std::string); //ͨ������ȡ�ó�Ա����
  static const Member *
      getMemberByNameConst(std::string); //ͨ������ȡ�ó�Աconst����
  static size_t getNumberOfPeople();     //��õ�ǰ����
  static std::vector<std::string> getNameList(); //��ó�Ա�����б�
  static std::vector<std::string> getItem();     //���һ����֧��Ŀ
  static std::vector<std::string> getItem(std::string); //��ö�����֧��Ŀ
  static bool isEmpty();                                //�Ƿ�Ϊ��
  static bool fileIn();                                 //�ļ�����
  static bool fileOut();                                //�ļ����
private:
  static std::vector<Member> mFamily;       //������м�ͥ��Ա
  static std::vector<Item> mFinancialItems; //һ������֧��Ŀ���
};

#endif // MEMBERMANAGER_H
