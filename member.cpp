#include "member.h"

// FinancialItem类有关实现

FinancialItem::FinancialItem() {}

FinancialItem::FinancialItem(std::string type, double amount,
                             std::string dealer)
    : mType(type), mAmount(amount), mDealer(dealer) {}

std::string FinancialItem::getType() const { return mType; }

double FinancialItem::getAmount() const { return mAmount; }

std::string FinancialItem::getDealer() const { return mDealer; }

void FinancialItem::setType(std::string type) { mType = type; }

void FinancialItem::setAmount(double amount) { mAmount = amount; }

void FinancialItem::setDealer(std::string dealer) { mDealer = dealer; }

// FinancialItem类有关实现结束

// PersonalInfo类有关实现

PersonalInfo::PersonalInfo() {}

PersonalInfo::PersonalInfo(std::string name, Sex sex, size_t age, size_t year,
                           size_t month, size_t day, size_t height,
                           size_t weight)
    : mName(name), mSex(sex), mAge(age), mBirth(year, month, day),
      mHeight(height), mWeight(weight) {}

std::string PersonalInfo::getName() const { return mName; }

Sex PersonalInfo::getSex() const { return mSex; }

size_t PersonalInfo::getAge() const { return mAge; }

std::tuple<size_t, size_t, size_t> PersonalInfo::getBirth() const {
  return mBirth;
}

size_t PersonalInfo::getHeight() const { return mHeight; }

size_t PersonalInfo::getWeight() const { return mWeight; }

void PersonalInfo::setName(std::string name) { mName = name; }

void PersonalInfo::setSex(Sex sex) { mSex = sex; }

void PersonalInfo::setAge(size_t age) { mAge = age; }

void PersonalInfo::setBirth(size_t year, size_t month, size_t day) {
  mBirth = {year, month, day};
}

void PersonalInfo::setHeight(size_t height) { mHeight = height; }

void PersonalInfo::setWeight(size_t weight) { mWeight = weight; }

// PersonalInfo类有关实现结束

// Member类有关实现

Member::Member() {}

Member::Member(std::string name, Sex sex, size_t age, size_t year, size_t month,
               size_t day, size_t height, size_t weight, Permission perm,
               std::string password)
    : mInfo(name, sex, age, year, month, day, height, weight), mPerm(perm),
      mPass(password) {}

Permission Member::getPerm() const { return mPerm; }

void Member::setPerm(Permission perm) { mPerm = perm; }

void Member::setPass(std::string password) { mPass = password; }

PersonalInfo &Member::getInfo() { return mInfo; }

const PersonalInfo &Member::getInfo() const { return mInfo; }

std::string Member::getPass() const { return mPass; }

std::multimap<std::tuple<size_t, size_t, size_t>, FinancialItem> &
Member::getItems() {
  return mItems;
}

const std::multimap<std::tuple<size_t, size_t, size_t>, FinancialItem> &
Member::getItems() const {
  return mItems;
}

// Member类有关实现结束
