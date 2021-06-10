#include "membermanager.h"

// Item类有关实现

Item::Item() {}

Item::Item(std::string name) : mName(name) {}

const std::string Item::getName() const { return mName; }

std::vector<std::string> &Item::getBranch() { return mBranch; }

const std::vector<std::string> &Item::getBranch() const { return mBranch; }

void Item::setName(std::string name) { mName = name; }

// Item类有关实现结束

// MemberManager类有关实现

std::vector<Member> MemberManager::mFamily{};

std::vector<Item> MemberManager::mFinancialItems{};

std::vector<Member>::reference
MemberManager::emplaceMember(std::string name, Sex sex, size_t age, size_t year,
                             size_t month, size_t day, size_t height,
                             size_t weight, Permission perm,
                             std::string password) {
  return mFamily.emplace_back(name, sex, age, year, month, day, height, weight,
                              perm, password);
}

void MemberManager::addMember(const Member &member) {
  mFamily.push_back(member);
}

void MemberManager::addItem(std::string name) {
  mFinancialItems.emplace_back(name);
}

void MemberManager::addItem(std::string name1, std::string name2) {
  auto it =
      std::find_if(begin(mFinancialItems), end(mFinancialItems),
                   [&](const Item &item) { return item.getName() == name1; });
  if (it != end(mFinancialItems)) {
    it->getBranch().emplace_back(name2);
  }
}

bool MemberManager::editItem(std::string name, std::string newName) {
  auto it =
      std::find_if(begin(mFinancialItems), end(mFinancialItems),
                   [&](const Item &item) { return item.getName() == name; });
  if (it != end(mFinancialItems)) {
    it->setName(newName);
    return true;
  }
  return false;
}

bool MemberManager::editItem(std::string name1, std::string name2,
                             std::string newName) {
  auto it =
      std::find_if(begin(mFinancialItems), end(mFinancialItems),
                   [&](const Item &item) { return item.getName() == name1; });
  if (it != end(mFinancialItems)) {
    auto it2 =
        std::find_if(begin(it->getBranch()), end(it->getBranch()),
                     [&](const Item &item) { return item.getName() == name2; });
    if (it2 != end(it->getBranch())) {
      *it2 = newName;
      return true;
    }
  }
  return false;
}

bool MemberManager::removeItemByName(std::string name) {
  auto it =
      std::find_if(begin(mFinancialItems), end(mFinancialItems),
                   [&](const Item &item) { return item.getName() == name; });
  if (it != end(mFinancialItems)) {
    mFinancialItems.erase(it);
    return true;
  }
  return false;
}

bool MemberManager::removeItemByName(std::string name1, std::string name2) {
  auto it =
      std::find_if(begin(mFinancialItems), end(mFinancialItems),
                   [&](const Item &item) { return item.getName() == name1; });
  if (it != end(mFinancialItems)) {
    auto it2 =
        std::find_if(begin(it->getBranch()), end(it->getBranch()),
                     [&](const Item &item) { return item.getName() == name2; });
    if (it2 != end(it->getBranch())) {
      it->getBranch().erase(it2);
      return true;
    }
  }
  return false;
}

bool MemberManager::removeMemberByName(std::string name) {
  auto it =
      std::find_if(cbegin(mFamily), cend(mFamily), [&](const Member &member) {
        return member.getInfo().getName() == name;
      });
  if (it == std::cend(mFamily)) {
    return false;
  }
  mFamily.erase(it);
  return true;
}

Member *MemberManager::getMemberByName(std::string name) {
  auto it =
      std::find_if(begin(mFamily), end(mFamily), [&](const Member &member) {
        return member.getInfo().getName() == name;
      });
  return it == std::end(mFamily) ? nullptr : &*it;
}

const Member *MemberManager::getMemberByNameConst(std::string name) {
  return getMemberByName(name);
}

size_t MemberManager::getNumberOfPeople() { return mFamily.size(); }

std::vector<std::string> MemberManager::getNameList() {
  std::vector<std::string> temp;
  for (const auto &member : mFamily) {
    temp.emplace_back(member.getInfo().getName());
  }
  return temp;
}

std::vector<std::string> MemberManager::getItem() {
  std::vector<std::string> temp;
  for (const auto &item : mFinancialItems) {
    temp.push_back(item.getName());
  }
  return temp;
}

std::vector<std::string> MemberManager::getItem(std::string name) {
  auto it =
      std::find_if(begin(mFinancialItems), end(mFinancialItems),
                   [&](const Item &item) { return item.getName() == name; });
  std::vector<std::string> temp;
  if (it != end(mFinancialItems)) {
    for (const auto &item : it->getBranch()) {
      temp.push_back(item);
    }
  }
  return temp;
}

bool MemberManager::isEmpty() { return mFamily.empty(); }

bool MemberManager::fileIn() {
  std::fstream fio{R"(family.db)", std::ios::in};
  if (!fio)
    return false;
  //总人数的输入
  size_t totalMembers{};
  fio >> totalMembers;
  mFamily.reserve(totalMembers);
  for (size_t i = 0; i < totalMembers; ++i) {
    std::string name, password, sex, perm;
    size_t age, year, month, day, height, weight;
    //个人信息的输入
    fio >> name >> sex >> age >> year >> month >> day >> height >> weight >>
        perm >> password;
    //成员创建
    emplaceMember(name, sex == "男" ? Sex::male : Sex::female, age, year, month,
                  day, height, weight,
                  perm == "root" ? Permission::root : Permission::user,
                  password);
    //收支信息的输入
    size_t totalItems{};
    fio >> totalItems; //个数输入
    for (size_t j = 0; j < totalItems; ++j) {
      std::string type, dealer;
      double amount;
      fio >> year >> month >> day >> type >> amount >> dealer;
      getMemberByName(name)->getItems().emplace(
          std::tuple<size_t, size_t, size_t>{year, month, day},
          FinancialItem{type, amount, dealer});
    }
  }
  //个数输入
  size_t size;
  fio >> size;
  mFinancialItems.reserve(size);
  for (size_t i = 0; i < size; ++i) {
    //一级收支项目名字输入
    std::string name;
    fio >> name;
    std::vector<Item>::reference ref = mFinancialItems.emplace_back(name);
    //该一级收支项目里包含的二级收支项目的个数输入
    size_t amount;
    fio >> amount;
    ref.getBranch().reserve(amount);
    for (size_t j = 0; j < amount; ++j) {
      //二级收支项目名字输入
      fio >> name;
      ref.getBranch().emplace_back(name);
    }
  }
  return true;
}

bool MemberManager::fileOut() {
  std::fstream fio{R"(family.db)", std::ios::out};
  if (!fio)
    return false;
  //总人数的输出
  fio << mFamily.size() << " ";
  for (const auto &member : mFamily) {
    //个人信息的输出
    auto [year, month, day] = member.getInfo().getBirth();
    fio << member.getInfo().getName() << " "
        << (member.getInfo().getSex() == Sex::male ? "男" : "女") << " "
        << member.getInfo().getAge() << " " << year << " " << month << " "
        << day << " " << member.getInfo().getHeight() << " "
        << member.getInfo().getWeight() << " "
        << (member.getPerm() == Permission::root ? "root" : "user") << " "
        << member.getPass() << " ";
    //收支信息的输出
    fio << member.getItems().size() << " "; //个数输出
    for (const auto &item : member.getItems()) {
      auto [year, month, day] = item.first;
      fio << year << " " << month << " " << day << " " << item.second.getType()
          << " " << item.second.getAmount() << " " << item.second.getDealer()
          << " ";
    }
  }
  //个数输出
  fio << mFinancialItems.size() << " ";
  for (const auto &i : mFinancialItems) {
    //一级收支项目名字输出
    fio << i.getName() << " ";
    //该一级收支项目里包含的二级收支项目的个数输出
    fio << i.getBranch().size() << " ";
    for (const auto &j : i.getBranch()) {
      //二级收支项目名字输出
      fio << j << " ";
    }
  }
  return true;
}

// MemberManager类有关实现结束
