#ifndef MEMBER_H
#define MEMBER_H

#include <map>
#include <string>
#include <tuple>

enum class Sex { male, female };      //�Ա�ö������
enum class Permission { user, root }; //����Ȩ��ö������

class FinancialItem //���˵�����֧��Ϣ��
{
public:
  FinancialItem();
  FinancialItem(std::string, double, std::string);
  std::string getType() const;   //�����֧����
  double getAmount() const;      //��ý��
  std::string getDealer() const; //��þ�����
  void setType(std::string);     //������֧����
  void setAmount(double);        //���ý��
  void setDealer(std::string);   //���þ�����
private:
  std::string mType;   //��֧����
  double mAmount;      //���
  std::string mDealer; //������
};

class PersonalInfo //��Ա��Ϣ
{
public:
  PersonalInfo();
  PersonalInfo(std::string, Sex, size_t, size_t, size_t, size_t, size_t,
               size_t);
  std::string getName() const; //��ü�ͥ��Ա������
  Sex getSex() const;          //��ü�ͥ��Ա���Ա�
  size_t getAge() const;       //��ü�ͥ��Ա������
  std::tuple<size_t, size_t, size_t> getBirth() const; //��ü�ͥ��Ա������
  size_t getHeight() const;              //��ü�ͥ��Ա�����
  size_t getWeight() const;              //��ü�ͥ��Ա������
  void setName(std::string);             //���ü�ͥ��Ա������
  void setSex(Sex);                      //���ü�ͥ��Ա���Ա�
  void setAge(size_t);                   //���ü�ͥ��Ա������
  void setBirth(size_t, size_t, size_t); //���ü�ͥ��Ա������
  void setHeight(size_t);                //���ü�ͥ��Ա�����
  void setWeight(size_t);                //���ü�ͥ��Ա������
private:
  std::string mName;                         //��ͥ��Ա������
  Sex mSex;                                  //��ͥ��Ա���Ա�
  size_t mAge;                               //��ͥ��Ա������
  std::tuple<size_t, size_t, size_t> mBirth; //��ͥ��Ա������
  size_t mHeight;                            //��ͥ��Ա�����
  size_t mWeight;                            //��ͥ��Ա������
};

class Member //��Ա��
{
public:
  Member();
  Member(std::string, Sex, size_t, size_t, size_t, size_t, size_t, size_t,
         Permission, std::string);
  Permission getPerm() const;          //��ü�ͥ��Ա�Ĳ���Ȩ��
  void setPerm(Permission);            //���ü�ͥ��Ա�Ĳ���Ȩ��
  void setPass(std::string);           //���ü�ͥ��Ա������
  PersonalInfo &getInfo();             //��ü�ͥ��Ա��Ϣ
  const PersonalInfo &getInfo() const; //��ü�ͥ��Ա��Ϣ(const)
  std::string getPass() const;         //��ü�ͥ��Ա������
  std::multimap<std::tuple<size_t, size_t, size_t>, FinancialItem> &
  getItems(); //��ü�ͥ��Ա��������֧��Ŀ
  const std::multimap<std::tuple<size_t, size_t, size_t>, FinancialItem> &
  getItems() const; //��ü�ͥ��Ա��������֧��Ŀ(const)
private:
  PersonalInfo mInfo; //��ͥ��Ա����Ϣ
  Permission mPerm;   //��ͥ��Ա�Ĳ���Ȩ��
  std::string mPass;  //��ͥ��Ա�ĵ�¼����
  std::multimap<std::tuple<size_t, size_t, size_t>, FinancialItem>
      mItems; //��ͥ��Ա��������֧��Ŀ
};

#endif // MEMBER_H
