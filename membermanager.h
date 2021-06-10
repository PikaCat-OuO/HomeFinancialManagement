#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include "member.h"
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>

class Item //一级收支项目类
{
public:
  Item();
  Item(std::string);
  const std::string getName() const;     //返回一级收支项目名字
  std::vector<std::string> &getBranch(); //返回二级收支项目总和
  const std::vector<std::string> &getBranch() const; //返回二级收支项目总和Const
  void setName(std::string); //设置一级收支项目名字
private:
  std::string mName;                //存放一级收支项目
  std::vector<std::string> mBranch; //存放二级收支项目
};

class MemberManager //静态成员管理类
{
public:
  //静态类不允许生成对象
  MemberManager() = delete;
  static std::vector<Member>::reference
      emplaceMember(std::string, Sex, size_t, size_t, size_t, size_t, size_t,
                    size_t, Permission, std::string); //添加成员
  static void addMember(const Member &);              //添加成员
  static void addItem(std::string);                   //添加一级收支项目
  static void addItem(std::string, std::string);      //添加二级收支项目
  static bool editItem(std::string, std::string);     //编辑一级收支项目
  static bool editItem(std::string, std::string,
                       std::string);         //编辑二级收支项目
  static bool removeItemByName(std::string); //通过名字移除一级收支项目
  static bool removeItemByName(std::string,
                               std::string); //通过名字移除二级收支项目
  static bool removeMemberByName(std::string); //通过名字移除成员
  static Member *getMemberByName(std::string); //通过名字取得成员引用
  static const Member *
      getMemberByNameConst(std::string); //通过名字取得成员const引用
  static size_t getNumberOfPeople();     //获得当前人数
  static std::vector<std::string> getNameList(); //获得成员名字列表
  static std::vector<std::string> getItem();     //获得一级收支项目
  static std::vector<std::string> getItem(std::string); //获得二级收支项目
  static bool isEmpty();                                //是非为空
  static bool fileIn();                                 //文件读入
  static bool fileOut();                                //文件输出
private:
  static std::vector<Member> mFamily;       //存放所有家庭成员
  static std::vector<Item> mFinancialItems; //一二级收支项目存放
};

#endif // MEMBERMANAGER_H
