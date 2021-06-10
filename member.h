#ifndef MEMBER_H
#define MEMBER_H

#include <map>
#include <string>
#include <tuple>

enum class Sex { male, female };      //性别枚举类型
enum class Permission { user, root }; //操作权限枚举类型

class FinancialItem //个人单条收支信息类
{
public:
  FinancialItem();
  FinancialItem(std::string, double, std::string);
  std::string getType() const;   //获得收支种类
  double getAmount() const;      //获得金额
  std::string getDealer() const; //获得经手人
  void setType(std::string);     //设置收支种类
  void setAmount(double);        //设置金额
  void setDealer(std::string);   //设置经手人
private:
  std::string mType;   //收支种类
  double mAmount;      //金额
  std::string mDealer; //经手人
};

class PersonalInfo //成员信息
{
public:
  PersonalInfo();
  PersonalInfo(std::string, Sex, size_t, size_t, size_t, size_t, size_t,
               size_t);
  std::string getName() const; //获得家庭成员的姓名
  Sex getSex() const;          //获得家庭成员的性别
  size_t getAge() const;       //获得家庭成员的年龄
  std::tuple<size_t, size_t, size_t> getBirth() const; //获得家庭成员的生日
  size_t getHeight() const;              //获得家庭成员的身高
  size_t getWeight() const;              //获得家庭成员的体重
  void setName(std::string);             //设置家庭成员的姓名
  void setSex(Sex);                      //设置家庭成员的性别
  void setAge(size_t);                   //设置家庭成员的年龄
  void setBirth(size_t, size_t, size_t); //设置家庭成员的生日
  void setHeight(size_t);                //设置家庭成员的身高
  void setWeight(size_t);                //设置家庭成员的体重
private:
  std::string mName;                         //家庭成员的姓名
  Sex mSex;                                  //家庭成员的性别
  size_t mAge;                               //家庭成员的年龄
  std::tuple<size_t, size_t, size_t> mBirth; //家庭成员的生日
  size_t mHeight;                            //家庭成员的身高
  size_t mWeight;                            //家庭成员的体重
};

class Member //成员类
{
public:
  Member();
  Member(std::string, Sex, size_t, size_t, size_t, size_t, size_t, size_t,
         Permission, std::string);
  Permission getPerm() const;          //获得家庭成员的操作权限
  void setPerm(Permission);            //设置家庭成员的操作权限
  void setPass(std::string);           //设置家庭成员的密码
  PersonalInfo &getInfo();             //获得家庭成员信息
  const PersonalInfo &getInfo() const; //获得家庭成员信息(const)
  std::string getPass() const;         //获得家庭成员的密码
  std::multimap<std::tuple<size_t, size_t, size_t>, FinancialItem> &
  getItems(); //获得家庭成员的所有收支项目
  const std::multimap<std::tuple<size_t, size_t, size_t>, FinancialItem> &
  getItems() const; //获得家庭成员的所有收支项目(const)
private:
  PersonalInfo mInfo; //家庭成员的信息
  Permission mPerm;   //家庭成员的操作权限
  std::string mPass;  //家庭成员的登录密码
  std::multimap<std::tuple<size_t, size_t, size_t>, FinancialItem>
      mItems; //家庭成员的所有收支项目
};

#endif // MEMBER_H
