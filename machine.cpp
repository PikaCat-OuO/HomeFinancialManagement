#include "machine.h"

// Member类有关实现

Member *Machine::mCurrentUser{nullptr};

const std::array<std::string, 3> Machine::mStartScreenSplash{
    "* * * * * * * * * * * * * * * * *", "*  欢迎您使用家庭收支管理系统!  *",
    "* * * * * * * * * * * * * * * * *"};

const std::array<std::string, 3> Machine::mUserTopScreenSplash{
    "* * * * * * * * * * * * * * * * *", "*      $家庭收支管理系统$       *",
    "* * * * * * * * * * * * * * * * *"};

const std::array<std::string, 3> Machine::mRootTopScreenSplash{
    "* * * * * * * * * * * * * * * * *", "*      #家庭收支管理系统#       *",
    "* * * * * * * * * * * * * * * * *"};

const std::array<std::string, 3> Machine::mByeScreenSplash{
    "* * * * * * * * * * * * * * * * *", "*   期待您的下一次使用,再见！   *",
    "* * * * * * * * * * * * * * * * *"};

const std::array<std::string, 9> Machine::mMainMenu{
    "+ + + + + + + + + +", "+                 +", "+  1、成员管理    +",
    "+  2、密码服务    +", "+  3、收支管理    +", "+  4、退出登录    +",
    "+  5、退出系统    +", "+                 +", "+ + + + + + + + + +"};

const std::array<std::string, 10> Machine::mMemberMenu{
    "+ + + + + + + + + + + + + + + +", "+                             +",
    "+  1、添加成员(管理员)        +", "+  2、删除成员(管理员)        +",
    "+  3、修改个人信息            +", "+  4、管理员权限转让(管理员)  +",
    "+  5、查看现有成员            +", "+  6、返回上级菜单            +",
    "+                             +", "+ + + + + + + + + + + + + + + +"};

const std::array<std::string, 7> Machine::mPassMenu{
    "+ + + + + + + + + + +", "+                   +", "+  1、查看密码      +",
    "+  2、修改密码      +", "+  3、返回上级菜单  +", "+                   +",
    "+ + + + + + + + + + +"};

const std::array<std::string, 13> Machine::mFinancialMenu{
    "+ + + + + + + + + + + + + + +", "+                           +",
    "+  1、添加收支项目(管理员)  +", "+  2、删除收支项目(管理员)  +",
    "+  3、修改收支项目(管理员)  +", "+  4、查看收支项目          +",
    "+  5、添加收支(管理员)      +", "+  6、删除收支(管理员)      +",
    "+  7、修改收支(管理员)      +", "+  8、查看收支              +",
    "+  9、返回上级菜单          +", "+                           +",
    "+ + + + + + + + + + + + + + +"};

void Machine::run() {
  start();  //开始界面
  mainUI(); //进入主菜单
  end();    //结束界面
}

void Machine::showTopBar(Type type) {
  system("cls");
  if (type == Type::top) {
    if (mCurrentUser->getPerm() == Permission::root) {
      for (const auto &i : mRootTopScreenSplash)
        std::cout << i << std::endl;
      std::cout << "尊敬的" << mCurrentUser->getInfo().getName() << ",您好!"
                << "当前您所属的用户组是:管理员" << std::endl
                << std::endl;
    } else {
      for (const auto &i : mUserTopScreenSplash)
        std::cout << i << std::endl;
      std::cout << "尊敬的" << mCurrentUser->getInfo().getName() << ",您好!"
                << "当前您所属的用户组是:普通用户" << std::endl
                << std::endl;
    }
  } else if (type == Type::start) {
    for (const auto &i : mStartScreenSplash)
      std::cout << i << std::endl;
  } else {
    for (const auto &i : mByeScreenSplash)
      std::cout << i << std::endl;
  }
}

bool Machine::createAccount(bool empty) {
  if (empty) {
    showTopBar(Type::start);
    std::cout << "当前数据库内没有任何账户,请先创建一个管理员账户!"
              << std::endl;
  } else {
    showTopBar(Type::top);
  }
  bool flag{true}; //用于检测输入是否正确
  std::string name, password, sex;
  int age, year, month, day, height, weight;
  while (true) { //用户信息的输入和判断
    std::cout << "提示:输入q回车返回上级菜单" << std::endl;
    std::cout << "请输入成员的姓名,性别,年龄,出生日期,身高,体重和登录密码("
                 "以空格为每一个项的分割符):"
              << std::endl;
    std::cin >> name;
    if (name == "q")
      return false;
    std::cin >> sex >> age >> year >> month >> day >> height >> weight >>
        password;
    std::cout << std::endl;
    //用户信息的判断
    if ((sex != "男" and sex != "女") or age < 0 or height < 0 or weight < 0 or
        year < 0 or month < 0 or month > 12 or day < 0 or day > 31) {
      std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                << std::endl;
      flag = false;
    } else {
      if (month == 2) {
        if (!year % 400 or (!year % 4 and year % 100)) {
          if (day > 29) {
            std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                      << std::endl;
            flag = false;
          }
        } else {
          if (day > 28) {
            std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                      << std::endl;
            flag = false;
          }
        }
      } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                 month == 8 or month == 10 or month == 12) {
        if (day > 31) {
          std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                    << std::endl;
          flag = false;
        }
      } else {
        if (day > 30) {
          std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                    << std::endl;
          flag = false;
        }
      }
    }
    //检测用户输入是否正确
    if (flag)
      break;
  }
  //防止迭代器失效
  std::string tempName;
  if (not empty) {
    tempName = mCurrentUser->getInfo().getName();
  }
  MemberManager::emplaceMember(
      name, sex == "男" ? Sex::male : Sex::female, age, year, month, day,
      height, weight, empty ? Permission::root : Permission::user, password);
  if (not empty) {
    mCurrentUser = MemberManager::getMemberByName(tempName);
  }
  std::cout << "成员添加成功。" << std::endl;
  system("pause");
  return true;
}

void Machine::start() {
  while (true) {
    showTopBar(Type::start);
    std::cout << "正在读入成员文件,请稍后...";
    bool isOk = MemberManager::fileIn();
    if (!isOk) { //读入错误或文件不存在时执行的处理程序
      showTopBar(Type::start);
      std::cout << "错误:文件读入失败" << std::endl
                << "提示:如果您是第一次使用本系统请输入1并按回车键继续,"
                   "否则请输入任意内容并按回车键结束程序:";
      std::string sign;
      std::cin >> sign;
      if (sign == "1") {
        if (createAccount(true)) {
          break;
        } else {
          continue;
        }
      } else {
        exit(0);
      }
    } else if (MemberManager::isEmpty()) { //没有账户时执行的操作
      if (createAccount(true)) {
        break;
      }
    } else {
      break;
    }
  }
  while (true) {
    if (!login()) {
      std::cout << "继续尝试登录请输入1并按回车,"
                   "否则输入其他任意内容按回车键结束程序:";
      std::string sign;
      std::cin >> sign;
      if (sign != "1") {
        showTopBar(Type::bye);
        system("pause");
        exit(0);
      }
    } else {
      break;
    }
  }
}

bool Machine::login() {
  showTopBar(Type::start);
  std::cout << "欢迎您登录系统!" << std::endl;
  std::cout << "提示:输入q回车即可退出登录界面!" << std::endl << std::endl;
  std::cout << "请输入用户名:";
  std::string user;
  std::cin >> user;
  if (user == "q") {
    showTopBar(Type::bye);
    system("pause");
    exit(0);
  }
  mCurrentUser = MemberManager::getMemberByName(user);
  if (mCurrentUser == nullptr) {
    std::cout << "登录失败、该用户名不存在。";
    return false;
  }
  std::cout << "请输入密码:";
  std::string pass;
  std::cin >> pass;
  if (pass == "q") {
    showTopBar(Type::bye);
    system("pause");
    exit(0);
  }
  if (pass == mCurrentUser->getPass()) {
    std::cout << "登录成功!";
    return true;
  } else {
    std::cout << "登录失败,密码错误。";
    return false;
  }
}

void Machine::end() {
  //结束界面
  showTopBar(Type::top);
  while (true) {
    bool fileOk = MemberManager::fileOut();
    if (!fileOk) {
      std::cout << "错误:文件保存失败" << std::endl;
      std::cout << "是否重新尝试保存更改到文件?如果选否,"
                   "则本次的所做的所有更改操作将不会被记录!"
                << std::endl
                << "是输入1回车,否则输入其他任意内容回车:";
      std::string sign;
      std::cin >> sign;
      std::cout << std::endl;
      if (sign != "1") {
        break;
      }
    } else {
      break;
    }
  }
  showTopBar(Type::bye);
  system("pause");
}

void Machine::mainUI() {
  while (true) {
    showTopBar(Type::top);
    std::cout << "请从下面的菜单中选择您想要的操作:" << std::endl;
    for (const auto &i : mMainMenu)
      std::cout << i << std::endl;
    std::cout << std::endl << "请选择您所需要的操作:";
    std::string choice;
    std::cin >> choice;
    if (choice == "1") {
      memberManagement();
    } else if (choice == "2") {
      passwordService();
    } else if (choice == "3") {
      financialManagement();
    } else if (choice == "4") {
      quitLogin();
    } else if (choice == "5") {
      return;
    } else {
      std::cout << "您的输入有误，请重新输入!" << std::endl;
      system("pause");
    }
  }
}

void Machine::memberManagement() {
  while (true) {
    showTopBar(Type::top);
    std::cout << "请从下面的菜单中选择您想要的操作:" << std::endl;
    for (const auto &i : mMemberMenu)
      std::cout << i << std::endl;
    std::cout << std::endl << "请选择您所需要的操作:";
    std::string choice;
    std::cin >> choice;
    std::cout << std::endl;
    if (choice == "1") {
      //添加成员
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      createAccount();
    } else if (choice == "2") {
      //删除成员
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "请选择您需要移除的成员:" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "请输入名字前序号(输入q回车返回上级菜单):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //检测用户输入是否正确
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "您的输入有误，请重新输入。" << std::endl;
          system("pause");
          continue;
        }
        //判断是否删除自己
        if (nameList.at(choice - 1) == mCurrentUser->getInfo().getName()) {
          std::cout << "管理员不能删除自己！如需删除，请先转让管理员权限，让新"
                       "的管理员来删除。"
                    << std::endl;
          system("pause");
          continue;
        }
        MemberManager::removeMemberByName(nameList.at(choice - 1));
        std::cout << "成员移除成功!" << std::endl;
        system("pause");
        break;
      }
    } else if (choice == "3") {
      //修改个人信息
      Member *target{mCurrentUser};
      bool flag{false}; //检测是否输入q
      //管理员选择成员
      if (mCurrentUser->getPerm() == Permission::root) {
        while (true) {
        rootBack2:
          showTopBar(Type::top);
          std::vector<std::string> nameList = MemberManager::getNameList();
          std::cout << "请选择您需要修改个人信息的成员:" << std::endl;
          for (size_t i = 0; i < nameList.size(); ++i) {
            std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
          }
          std::cout << std::endl << "请输入名字前序号(输入q回车返回上级菜单):";
          std::string sign;
          std::cin >> sign;
          if (sign == "q") {
            flag = true;
            break;
          }
          //检测用户输入是否正确
          for (const auto &i : sign) {
            if (!isdigit(i)) {
              std::cout << "您的输入有误，请重新输入。" << std::endl;
              system("pause");
              continue;
            }
          }
          size_t choice;
          std::stringstream ss;
          ss << sign;
          ss >> choice;
          if (choice > nameList.size() or choice == 0) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
          target = MemberManager::getMemberByName(nameList.at(choice - 1));
          break;
        }
      }
      if (flag)
        continue;
      //修改成员信息
      while (true) {
        showTopBar(Type::top);
        auto [year, month, day] = target->getInfo().getBirth();
        std::cout << "请选择您要修改的成员信息:" << std::endl
                  << "1、姓名:" << target->getInfo().getName() << std::endl
                  << "2、性别:"
                  << (target->getInfo().getSex() == Sex::male ? "男" : "女")
                  << std::endl
                  << "3、年龄:" << target->getInfo().getAge() << std::endl
                  << "4、生日:" << year << "年" << month << "月" << day << "日"
                  << std::endl
                  << "5、身高:" << target->getInfo().getHeight() << "cm"
                  << std::endl
                  << "6、体重:" << target->getInfo().getWeight() << "kg"
                  << std::endl
                  << std::endl;
        std::cout << "请选择(输入q回车返回上级菜单):";
        std::string choice;
        std::cin >> choice;
        std::cout << std::endl;
        if (choice == "q" and mCurrentUser->getPerm() == Permission::root) {
          goto rootBack2;
        } else if (choice == "q") {
          break;
        }
        if (choice == "1") {
          std::cout << "请输入需要修改成的名字(输入q回车取消操作):";
          std::string name;
          std::cin >> name;
          if (name == "q")
            continue;
          target->getInfo().setName(name);
          std::cout << "名字修改成功!" << std::endl;
          system("pause");
        } else if (choice == "2") {
          std::cout << "确认修改性别请输入y回车,输入其他任意内容回车取消操作:";
          target->getInfo().setSex(target->getInfo().getSex() == Sex::male
                                       ? Sex::female
                                       : Sex::male);
          std::cout << "性别修改成功!" << std::endl;
          system("pause");
        } else if (choice == "3") {
          while (true) {
            std::cout << "请输入需要修改成的年龄(输入q回车取消操作):";
            std::string sign;
            std::cin >> sign;
            if (sign == "q")
              break;
            int age;
            std::stringstream ss;
            ss << sign;
            ss >> age;
            if (age < 0) {
              std::cout << "年龄不能为负数,修改失败!" << std::endl;
              system("pause");
              std::cout << std::endl;
            } else {
              target->getInfo().setAge(age);
              std::cout << "年龄修改成功!" << std::endl;
              system("pause");
              break;
            }
          }
        } else if (choice == "4") {
          while (true) {
            std::cout
                << "请输入需要修改成的出生日期(年 月 日)(输入q回车取消操作):"
                << std::endl;
            std::string sign;
            std::cin >> sign;
            if (sign == "q")
              break;
            std::stringstream ss;
            ss << sign;
            int year, month, day;
            ss >> year;
            std::cin >> year >> month >> day;
            if (year < 0 or month < 0 or day < 0) {
              std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                        << std::endl;
              system("pause");
              std::cout << std::endl;
            } else if (month == 2) {
              if (!year % 400 or (!year % 4 and year % 100)) {
                if (day > 29) {
                  std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                            << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              } else {
                if (day > 28) {
                  std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                            << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              }
            } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                       month == 8 or month == 10 or month == 12) {
              if (day > 31) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                          << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 30) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl
                          << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            target->getInfo().setBirth(year, month, day);
            std::cout << "出生日期修改成功!" << std::endl;
            system("pause");
            break;
          }
        } else if (choice == "5") {
          while (true) {
            std::cout << "请输入需要修改成的身高(输入q回车取消操作):";
            std::string sign;
            std::cin >> sign;
            if (sign == "q")
              break;
            int height;
            std::stringstream ss;
            ss << sign;
            ss >> height;
            if (height <= 0) {
              std::cout << "身高不能小于等于0,修改失败!" << std::endl;
              system("pause");
              std::cout << std::endl;
            } else {
              target->getInfo().setHeight(height);
              std::cout << "身高修改成功!" << std::endl;
              system("pause");
              break;
            }
          }
        } else if (choice == "6") {
          while (true) {
            std::cout << "请输入需要修改成的体重(输入q回车取消操作):";
            std::string sign;
            std::cin >> sign;
            if (sign == "q")
              break;
            int weight;
            std::stringstream ss;
            ss << sign;
            ss >> weight;
            if (weight <= 0) {
              std::cout << "体重不能小于等于0,修改失败!" << std::endl;
              system("pause");
              std::cout << std::endl;
            } else {
              target->getInfo().setWeight(weight);
              std::cout << "体重修改成功!" << std::endl;
              system("pause");
              break;
            }
          }
        } else {
          std::cout << "您的输入有误，请重新输入。" << std::endl;
          system("pause");
          continue;
        }
      }
    } else if (choice == "4") {
      //管理员权限转让
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "请选择您需要转让的成员:" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "请输入名字前序号(输入q回车返回上级菜单):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //检测用户输入是否正确
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "您的输入有误，请重新输入。" << std::endl;
          system("pause");
          continue;
        }
        //判断是否转让给自己
        if (nameList.at(choice - 1) == mCurrentUser->getInfo().getName()) {
          std::cout << "不能转让管理员权限给自己!" << std::endl;
          system("pause");
          continue;
        }
        auto *newRoot = MemberManager::getMemberByName(nameList.at(choice - 1));
        newRoot->setPerm(Permission::root);
        mCurrentUser->setPerm(Permission::user);
        std::cout << "管理员权限转让成功!" << std::endl;
        system("pause");
        break;
      }
    } else if (choice == "5") {
      //查看所有成员
      showTopBar(Type::top);
      std::vector<std::string> nameList = MemberManager::getNameList();
      std::cout << "现有所有成员:" << std::endl;
      for (size_t i = 0; i < nameList.size(); ++i) {
        std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
      }
      std::cout << std::endl;
      system("pause");
    } else if (choice == "6") {
      //返回上级菜单
      return;
    } else {
      //输入错误处理
      std::cout << "您的输入有误，请重新输入!" << std::endl;
      system("pause");
    }
  }
}

void Machine::passwordService() {
  while (true) {
    showTopBar(Type::top);
    std::cout << "请从下面的菜单中选择您想要的操作:" << std::endl;
    for (const auto &i : mPassMenu)
      std::cout << i << std::endl;
    std::cout << std::endl << "请选择您所需要的操作:";
    std::string choice;
    std::cin >> choice;
    std::cout << std::endl;
    if (choice == "1") {
      const Member *target{mCurrentUser};
      if (mCurrentUser->getPerm() == Permission::root) {
      rootBack:           //管理员查看密码时输入q回到此处
        bool flag{false}; //检测是否输入q
        //管理员选择成员
        while (true) {
          showTopBar(Type::top);
          std::vector<std::string> nameList = MemberManager::getNameList();
          std::cout << "您想要查看哪位成员的密码?" << std::endl;
          for (size_t i = 0; i < nameList.size(); ++i) {
            std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
          }
          std::cout << std::endl << "请输入名字前序号(输入q回车取消操作):";
          std::string sign;
          std::cin >> sign;
          if (sign == "q") {
            flag = true;
            break;
          }
          //检测用户输入是否正确
          for (const auto &i : sign) {
            if (!isdigit(i)) {
              std::cout << "您的输入有误，请重新输入。" << std::endl;
              system("pause");
              continue;
            }
          }
          size_t choice;
          std::stringstream ss;
          ss << sign;
          ss >> choice;
          if (choice > nameList.size() or choice == 0) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
          target = MemberManager::getMemberByName(nameList.at(choice - 1));
          break;
        }
        if (flag)
          continue;
      }
      showTopBar(Type::top);
      std::cout << (mCurrentUser->getPerm() == Permission::root
                        ? "您"
                        : target->getInfo().getName())
                << "的密码是:" << target->getPass() << std::endl;
      system("pause");
      if (mCurrentUser->getPerm() == Permission::root)
        goto rootBack;
    } else if (choice == "2") {
      Member *target{mCurrentUser};
      if (mCurrentUser->getPerm() == Permission::root) {
      rootUser:           //管理员修改密码时输入q回到此处
        bool flag{false}; //检测是否输入q
        //管理员选择成员
        while (true) {
          showTopBar(Type::top);
          std::vector<std::string> nameList = MemberManager::getNameList();
          std::cout << "您想要修改哪位成员的密码?" << std::endl;
          for (size_t i = 0; i < nameList.size(); ++i) {
            std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
          }
          std::cout << std::endl << "请输入名字前序号(输入q回车取消操作):";
          std::string sign;
          std::cin >> sign;
          if (sign == "q") {
            flag = true;
            break;
          }
          //检测用户输入是否正确
          for (const auto &i : sign) {
            if (!isdigit(i)) {
              std::cout << "您的输入有误，请重新输入。" << std::endl;
              system("pause");
              continue;
            }
          }
          size_t choice;
          std::stringstream ss;
          ss << sign;
          ss >> choice;
          if (choice > nameList.size() or choice == 0) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
          target = MemberManager::getMemberByName(nameList.at(choice - 1));
          break;
        }
        if (flag)
          continue;
      }
      showTopBar(Type::top);
      std::cout << (mCurrentUser->getPerm() == Permission::root
                        ? "您"
                        : target->getInfo().getName())
                << "当前的密码是:" << target->getPass() << std::endl;
      std::cout << "您想将"
                << (mCurrentUser->getPerm() == Permission::root
                        ? target->getInfo().getName() + "的"
                        : "")
                << "密码修改为(输入q回车取消操作):";
      std::string pass;
      std::cin >> pass;
      if (pass == "q" and mCurrentUser->getPerm() == Permission::root) {
        goto rootUser;
      } else if (pass == "q") {
        continue;
      }
      target->setPass(pass);
      std::cout << std::endl << "修改成功!" << std::endl;
      system("pause");
    } else if (choice == "3") {
      //返回上级菜单
      return;
    } else {
      //输入错误处理
      std::cout << "您的输入有误，请重新输入!" << std::endl;
      system("pause");
    }
  }
}

void Machine::financialManagement() {
  while (true) {
    showTopBar(Type::top);
    std::cout << "请从下面的菜单中选择您想要的操作:" << std::endl;
    for (const auto &i : mFinancialMenu)
      std::cout << i << std::endl;
    std::cout << std::endl << "请选择您所需要的操作:";
    std::string choice;
    std::cin >> choice;
    std::cout << std::endl;
    if (choice == "1") {
      //权限检查
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        std::cout
            << "请选择添加一级项目或二级项目(请输入1或2，输入q回车取消操作):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q") {
          break;
        } else if (sign == "1") {
          showTopBar(Type::top);
          std::cout << "请输入要添加的一级项目(输入q回车取消操作):";
          std::string name;
          std::cin >> name;
          if (name == "q")
            continue;
          MemberManager::addItem(name);
          std::cout << "添加成功" << std::endl;
          system("pause");
          break;
        } else if (sign == "2") {
          while (true) {
            showTopBar(Type::top);
            std::cout << "请输入要添加的二级项目(输入q回车取消操作):";
            std::string name2;
            std::cin >> name2;
            if (name2 == "q")
              break;
            std::cout << "请选择该二级项目所属的一级项目:" << std::endl;
            size_t choice{0};
            for (const auto &item : MemberManager::getItem()) {
              std::cout << ++choice << "、" << item << std::endl;
            }
            std::cout << std::endl << "请选择(输入q回车取消操作):";
            std::string name1;
            std::cin >> name1;
            if (name1 == "q") {
              break;
            }
            std::stringstream ss;
            ss << name1;
            ss >> choice;
            if (choice == 0 or choice > MemberManager::getItem().size()) {
              std::cout << "您的输入有误，请重新输入。" << std::endl;
              system("pause");
              continue;
            }
            MemberManager::addItem(MemberManager::getItem().at(choice - 1),
                                   name2);
            std::cout << "添加成功" << std::endl;
            system("pause");
            break;
          }
        } else {
          std::cout << "您的输入有误，请重新输入!" << std::endl;
          system("pause");
        }
      }
    } else if (choice == "2") {
      //权限检查
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        if (MemberManager::getItem().empty()) {
          std::cout << "当前收支项目为空，请先创建收支项目。" << std::endl;
          system("pause");
          break;
        }
        std::cout << "请选择您需要删除的一级项目或二级项目:" << std::endl;
        std::cout << "提示:需要删除一级项目请输入x,删除二级项目请输入x "
                     "x(x代表一级或二级项目前的数字)"
                  << std::endl;
        size_t choice1{0}, choice2{0};
        for (const auto &i : MemberManager::getItem()) {
          std::cout << ++choice1 << "、" << i << ":" << std::endl;
          choice2 = 0;
          for (const auto &j : MemberManager::getItem(i)) {
            std::cout << "  " << ++choice2 << "、" << j << std::endl;
          }
          std::cout << std::endl;
        }
        std::cout << std::endl << "请选择(输入q回车取消操作):";
        std::cin.ignore();
        std::string sign;
        std::getline(std::cin, sign);
        if (sign == "q")
          break;
        bool two{false};
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            if (isspace(i) and not two) {
              two = true;
              continue;
            }
            sign = "1";
            break;
          }
        }
        if (two and sign.length() == 1) {
          std::cout << "您的输入有误，请重新输入。" << std::endl;
          system("pause");
          continue;
        }
        if (two) {
          std::stringstream ss;
          ss << sign;
          ss >> choice1 >> choice2;
          if (choice1 == 0 or choice2 == 0 or
              choice1 > MemberManager::getItem().size() or
              choice2 > MemberManager::getItem(
                            MemberManager::getItem().at(choice1 - 1))
                            .size()) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            std::cout << std::endl;
            continue;
          }
          MemberManager::removeItemByName(
              MemberManager::getItem().at(choice1 - 1),
              MemberManager::getItem(MemberManager::getItem().at(choice1 - 1))
                  .at(choice2 - 1));
          std::cout << "删除成功!" << std::endl;
          system("pause");
        } else {
          std::stringstream ss;
          ss << sign;
          ss >> choice1;
          if (choice1 == 0 or choice1 > MemberManager::getItem().size()) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            std::cout << std::endl;
            continue;
          }
          MemberManager::removeItemByName(
              MemberManager::getItem().at(choice1 - 1));
          std::cout << "删除成功!" << std::endl;
          system("pause");
        }
        if (MemberManager::getItem().empty())
          break;
      }
    } else if (choice == "3") {
      //权限检查
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        if (MemberManager::getItem().empty()) {
          std::cout << "当前收支项目为空，请先创建收支项目。" << std::endl;
          system("pause");
          break;
        }
        std::cout << "请选择您需要修改的一级项目或二级项目:" << std::endl;
        std::cout << "提示:需要修改一级项目请输入x,修改二级项目请输入x "
                     "x(x代表一级或二级项目前的数字)"
                  << std::endl;
        size_t choice1{0}, choice2{0};
        for (const auto &i : MemberManager::getItem()) {
          std::cout << ++choice1 << "、" << i << ":" << std::endl;
          choice2 = 0;
          for (const auto &j : MemberManager::getItem(i)) {
            std::cout << "  " << ++choice2 << "、" << j << std::endl;
          }
          std::cout << std::endl;
        }
        std::cout << std::endl << "请选择(输入q回车取消操作):";
        std::cin.ignore();
        std::string sign;
        std::getline(std::cin, sign);
        if (sign == "q")
          break;
        bool two{false};
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            if (isspace(i) and not two) {
              two = true;
              continue;
            }
            sign = "1";
            break;
          }
        }
        if (two and sign.length() == 1) {
          std::cout << "您的输入有误，请重新输入。" << std::endl;
          system("pause");
          continue;
        }
        if (two) {
          std::stringstream ss;
          ss << sign;
          ss >> choice1 >> choice2;
          if (choice1 == 0 or choice2 == 0 or
              choice1 > MemberManager::getItem().size() or
              choice2 > MemberManager::getItem(
                            MemberManager::getItem().at(choice1 - 1))
                            .size()) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            std::cout << std::endl;
            continue;
          }
          std::cout << "请输入新的收支项目名(输入q回车取消操作):";
          std::string name;
          std::cin >> name;
          if (name == "q")
            continue;
          MemberManager::editItem(
              MemberManager::getItem().at(choice1 - 1),
              MemberManager::getItem(MemberManager::getItem().at(choice1 - 1))
                  .at(choice2 - 1),
              name);
          std::cout << "修改成功!" << std::endl;
          system("pause");
          continue;
        } else {
          std::stringstream ss;
          ss << sign;
          ss >> choice1;
          if (choice1 == 0 or choice1 > MemberManager::getItem().size()) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            std::cout << std::endl;
            continue;
          }
          std::cout << "请输入新的收支项目名(输入q回车取消操作):";
          std::string name;
          std::cin >> name;
          if (name == "q")
            continue;
          MemberManager::editItem(MemberManager::getItem().at(choice1 - 1),
                                  name);
          std::cout << "修改成功!" << std::endl;
          system("pause");
          continue;
        }
        if (MemberManager::getItem().empty())
          break;
      }
    } else if (choice == "4") {
      showTopBar(Type::top);
      if (MemberManager::getItem().empty()) {
        std::cout << "当前收支项目为空，请先创建收支项目。" << std::endl;
        system("pause");
        continue;
      }
      std::cout << "以下是所有的收支项目:" << std::endl;
      size_t choice1{0}, choice2{0};
      for (const auto &i : MemberManager::getItem()) {
        std::cout << ++choice1 << "、" << i << ":" << std::endl;
        choice2 = 0;
        for (const auto &j : MemberManager::getItem(i)) {
          std::cout << "  " << ++choice2 << "、" << j << std::endl;
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
      system("pause");
    } else if (choice == "5") {
      //权限检查
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      showTopBar(Type::top);
      if (MemberManager::getItem().empty()) {
        std::cout << "当前收支项目为空，请先创建收支项目。" << std::endl;
        system("pause");
        break;
      }
      Member *target{nullptr};
      //管理员选择成员
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "您想要为哪位成员添加收支信息?" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "请输入名字前序号(输入q回车取消操作):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //检测用户输入是否正确
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "您的输入有误，请重新输入。" << std::endl;
          system("pause");
          continue;
        }
        showTopBar(Type::top);
        while (true) {
          target = MemberManager::getMemberByName(nameList.at(choice - 1));
          std::cout << "请输入要添加的收支信息的时间(年月日),金额,经手人("
                       "输入q回车取消操作):";
          std::string dealer;
          size_t year, month, day;
          double amount;
          std::cin >> sign;
          if (sign == "q")
            break;
          ss.clear();
          ss.str("");
          ss << sign;
          ss >> year;
          std::cin >> month >> day >> amount >> dealer;
          if (!std::cin.good()) {
            std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
            std::cin.clear();
            std::cin.sync();
            system("pause");
            std::cout << std::endl;
            continue;
          }
          if (month == 2) {
            if (!year % 400 or (!year % 4 and year % 100)) {
              if (day > 29) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 28) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
          } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                     month == 8 or month == 10 or month == 12) {
            if (day > 31) {
              std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          } else {
            if (day > 30) {
              std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          }
          std::cout << std::endl;
          //选择收支种类
          size_t choice1{0}, choice2{0};
          while (true) {
            std::cout << "请选择该收支信息所属的一级项目或二级项目:"
                      << std::endl;
            std::cout << "提示:需要选择一级项目请输入x,选择二级项目请输入x "
                         "x(x代表一级或二级项目前的数字)"
                      << std::endl;
            choice1 = 0;
            choice2 = 0;
            for (const auto &i : MemberManager::getItem()) {
              std::cout << ++choice1 << "、" << i << ":" << std::endl;
              choice2 = 0;
              for (const auto &j : MemberManager::getItem(i)) {
                std::cout << "  " << ++choice2 << "、" << j << std::endl;
              }
              std::cout << std::endl;
            }
            std::cout << std::endl << "请选择(输入q回车取消操作):";
            std::cin.ignore();
            std::string sign;
            std::getline(std::cin, sign);
            if (sign == "q")
              break;
            bool two{false};
            for (const auto &i : sign) {
              if (!isdigit(i)) {
                if (isspace(i) and not two) {
                  two = true;
                  continue;
                }
                sign = "1";
                break;
              }
            }
            if (two and sign.length() == 1) {
              std::cout << "您的输入有误，请重新输入。" << std::endl;
              system("pause");
              continue;
            }
            std::string itemName;
            if (two) {
              std::stringstream ss;
              ss << sign;
              ss >> choice1 >> choice2;
              if (choice1 == 0 or choice2 == 0 or
                  choice1 > MemberManager::getItem().size() or
                  choice2 > MemberManager::getItem(
                                MemberManager::getItem().at(choice1 - 1))
                                .size()) {
                std::cout << "您的输入有误，请重新输入。" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
              itemName = MemberManager::getItem().at(choice1 - 1) + "-" +
                         MemberManager::getItem(
                             MemberManager::getItem().at(choice1 - 1))
                             .at(choice2 - 1);
            } else {
              std::stringstream ss;
              ss << sign;
              ss >> choice1;
              if (choice1 == 0 or choice1 > MemberManager::getItem().size()) {
                std::cout << "您的输入有误，请重新输入。" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
              itemName = MemberManager::getItem().at(choice1 - 1);
            }
            target->getItems().emplace(
                std::tuple<size_t, size_t, size_t>{year, month, day},
                FinancialItem{itemName, amount, dealer});
            std::cout << "添加成功!" << std::endl;
            system("pause");
            break;
          }
          break;
        }
        break;
      }
    } else if (choice == "6") {
      //权限检查
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      Member *target{nullptr};
      //管理员选人
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "您想要删除哪位成员的收支信息?" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "请输入名字前序号(输入q回车取消操作):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //检测用户输入是否正确
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "您的输入有误，请重新输入。" << std::endl;
          system("pause");
          continue;
        }
        target = MemberManager::getMemberByName(nameList.at(choice - 1));
        while (true) {
          showTopBar(Type::top);
          //检查是否为空
          if (target->getItems().empty()) {
            std::cout << (target == mCurrentUser
                              ? "您的收支信息为空!"
                              : target->getInfo().getName() + "的收支信息为空!")
                      << std::endl;
            system("pause");
            break;
          }
          std::cout << "提示:删除收支信息需要知道准确日期!如果您不知道,"
                       "可以在“查看收支”中查看。"
                    << std::endl;
          std::cout << "请输入您要删除的收支信息所属的准确日期(年月日)("
                       "输入q取消操作):";
          size_t year, month, day;
          std::cin >> sign;
          if (sign == "q")
            break;
          ss.clear();
          ss.str("");
          ss << sign;
          ss >> year;
          std::cin >> month >> day;
          //日期检查
          if (month == 2) {
            if (!year % 400 or (!year % 4 and year % 100)) {
              if (day > 29) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 28) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
          } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                     month == 8 or month == 10 or month == 12) {
            if (day > 31) {
              std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          } else {
            if (day > 30) {
              std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          }
          std::cout << std::endl;
          //输出项目供选择
          while (true) {
            auto [it1, it2] = target->getItems().equal_range(
                std::tuple<size_t, size_t, size_t>{year, month, day});
            size_t size = std::distance(it1, it2);
            if (it1 == it2) {
              std::cout << "该日期没有任何的收支记录!" << std::endl;
              system("pause");
              std::cout << std::endl;
              break;
            }
            showTopBar(Type::top);
            std::cout << "请选择需要删除的项目信息:" << std::endl;
            std::cout << target->getInfo().getName() << year << "年" << month
                      << "月" << day << "日的收支信息:" << std::endl;
            for (size_t i = 0; it1 != it2; ++it1) {
              std::cout << ++i << "、"
                        << "收支类型:" << it1->second.getType() << " "
                        << "金额:" << it1->second.getAmount() << " "
                        << "经手人:" << it1->second.getDealer() << std::endl;
            }
            std::cout << std::endl;
            std::cout << "请选择(输入q取消操作):";
            std::cin >> sign;
            if (sign == "q")
              break;
            for (const auto &i : sign) {
              if (!isdigit(i)) {
                std::cout << "您输入的信息有误，请重新输入，谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            if (sign.length() == 0 or sign.length() > size) {
              std::cout << "您输入的信息有误，请重新输入，谢谢!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
            std::size_t choice;
            ss.clear();
            ss.str("");
            ss << sign;
            ss >> choice;
            --it1;
            for (size_t i = 0; i < size - choice; ++i)
              --it1;
            target->getItems().erase(it1);
            std::cout << "删除成功!";
            break;
          }
        }
      }
    } else if (choice == "7") {
      //权限检查
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "权限不足:您不是管理员，没有操作权限!" << std::endl;
        system("pause");
        continue;
      }
      Member *target{nullptr};
      //管理员选人
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "您想要修改哪位成员的收支信息?" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "请输入名字前序号(输入q回车取消操作):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //检测用户输入是否正确
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "您的输入有误，请重新输入。" << std::endl;
          system("pause");
          continue;
        }
        target = MemberManager::getMemberByName(nameList.at(choice - 1));
        while (true) {
          showTopBar(Type::top);
          std::cout << "提示:修改收支信息需要知道准确日期!如果您不知道,"
                       "可以在“查看收支”中查看。"
                    << std::endl;
          std::cout << "请输入您要删除的收支信息所属的准确日期(年月日)("
                       "输入q取消操作):";
          size_t year, month, day;
          std::cin >> sign;
          if (sign == "q")
            break;
          ss.clear();
          ss.str("");
          ss << sign;
          ss >> year;
          std::cin >> month >> day;
          //日期检查
          if (month == 2) {
            if (!year % 400 or (!year % 4 and year % 100)) {
              if (day > 29) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 28) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
          } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                     month == 8 or month == 10 or month == 12) {
            if (day > 31) {
              std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          } else {
            if (day > 30) {
              std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          }
          std::cout << std::endl;
          //输出项目供选择
          while (true) {
            auto [it1, it2] = target->getItems().equal_range(
                std::tuple<size_t, size_t, size_t>{year, month, day});
            size_t size = std::distance(it1, it2);
            if (it1 == it2) {
              std::cout << "该日期没有任何的收支记录!" << std::endl;
              system("pause");
              std::cout << std::endl;
              break;
            }
            showTopBar(Type::top);
            std::cout << "请选择需要修改的项目信息:" << std::endl;
            std::cout << target->getInfo().getName() << year << "年" << month
                      << "月" << day << "日的收支信息:" << std::endl;
            for (size_t i = 0; it1 != it2; ++it1) {
              std::cout << ++i << "、"
                        << "收支类型:" << it1->second.getType() << " "
                        << "金额:" << it1->second.getAmount() << " "
                        << "经手人:" << it1->second.getDealer() << std::endl;
            }
            std::cout << std::endl;
            std::cout << "请选择(输入q取消操作):";
            std::cin >> sign;
            if (sign == "q")
              break;
            for (const auto &i : sign) {
              if (!isdigit(i)) {
                std::cout << "您输入的信息有误，请重新输入，谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            if (sign.length() == 0 or sign.length() > size) {
              std::cout << "您输入的信息有误，请重新输入，谢谢!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
            std::size_t choice;
            ss.clear();
            ss.str("");
            ss << sign;
            ss >> choice;
            --it1;
            for (size_t i = 0; i < size - choice; ++i)
              --it1;
            while (true) {
              showTopBar(Type::top);
              std::cout << "您想要修改什么?" << std::endl;
              auto [year, month, day] = it1->first;
              std::cout << "1、日期:" << year << "年" << month << "月" << day
                        << "日" << std::endl;
              std::cout << "2、收支项目:" << it1->second.getType() << std::endl;
              std::cout << "3、金额:" << it1->second.getAmount() << std::endl;
              std::cout << "4、经手人:" << it1->second.getDealer() << std::endl;
              std::cout << std::endl << "请选择(输入q回车取消操作):";
              std::string choice;
              std::cin >> choice;
              std::cout << std::endl;
              if (choice == "q") {
                break;
              } else if (choice == "1") {
                //改日期
                while (true) {
                  std::cout << "您想将日期修改为(年月日)(输入q回车取消操作):";
                  std::string sign;
                  std::cin >> sign;
                  if (sign == "q")
                    break;
                  ss.clear();
                  ss.str("");
                  ss << sign;
                  ss >> year;
                  std::cin >> month >> day;
                  //检查日期
                  if (month == 2) {
                    if (!year % 400 or (!year % 4 and year % 100)) {
                      if (day > 29) {
                        std::cout << "您输入的信息有误,请重新输入,谢谢!"
                                  << std::endl;
                        system("pause");
                        std::cout << std::endl;
                        continue;
                      }
                    } else {
                      if (day > 28) {
                        std::cout << "您输入的信息有误,请重新输入,谢谢!"
                                  << std::endl;
                        system("pause");
                        std::cout << std::endl;
                        continue;
                      }
                    }
                  } else if (month == 1 or month == 3 or month == 5 or
                             month == 7 or month == 8 or month == 10 or
                             month == 12) {
                    if (day > 31) {
                      std::cout << "您输入的信息有误,请重新输入,谢谢!"
                                << std::endl;
                      system("pause");
                      std::cout << std::endl;
                      continue;
                    }
                  } else {
                    if (day > 30) {
                      std::cout << "您输入的信息有误,请重新输入,谢谢!"
                                << std::endl;
                      system("pause");
                      std::cout << std::endl;
                      continue;
                    }
                  }
                  std::cout << std::endl;
                  auto it2 = target->getItems().emplace(
                      std::tuple<size_t, size_t, size_t>{year, month, day},
                      it1->second);
                  target->getItems().erase(it1);
                  it1 = it2;
                  break;
                }
              } else if (choice == "2") {
                //改收支项目
                if (MemberManager::getItem().empty()) {
                  std::cout << "当前收支项目为空，请先创建收支项目。"
                            << std::endl;
                  system("pause");
                  continue;
                }
                //选择收支种类
                size_t choice1{0}, choice2{0};
                while (true) {
                  std::cout << "请选择新的收支项目:" << std::endl;
                  std::cout
                      << "提示:需要选择一级项目请输入x,选择二级项目请输入x "
                         "x(x代表一级或二级项目前的数字)"
                      << std::endl;
                  choice1 = 0;
                  choice2 = 0;
                  for (const auto &i : MemberManager::getItem()) {
                    std::cout << ++choice1 << "、" << i << ":" << std::endl;
                    choice2 = 0;
                    for (const auto &j : MemberManager::getItem(i)) {
                      std::cout << "  " << ++choice2 << "、" << j << std::endl;
                    }
                    std::cout << std::endl;
                  }
                  std::cout << std::endl << "请选择(输入q回车取消操作):";
                  std::cin.ignore();
                  std::string sign;
                  std::getline(std::cin, sign);
                  if (sign == "q")
                    break;
                  bool two{false};
                  for (const auto &i : sign) {
                    if (!isdigit(i)) {
                      if (isspace(i) and not two) {
                        two = true;
                        continue;
                      }
                      sign = "1";
                      break;
                    }
                  }
                  if (two and sign.length() == 1) {
                    std::cout << "您的输入有误，请重新输入。" << std::endl;
                    system("pause");
                    continue;
                  }
                  std::string itemName;
                  if (two) {
                    std::stringstream ss;
                    ss << sign;
                    ss >> choice1 >> choice2;
                    if (choice1 == 0 or choice2 == 0 or
                        choice1 > MemberManager::getItem().size() or
                        choice2 > MemberManager::getItem(
                                      MemberManager::getItem().at(choice1 - 1))
                                      .size()) {
                      std::cout << "您的输入有误，请重新输入。" << std::endl;
                      system("pause");
                      std::cout << std::endl;
                      continue;
                    }
                    itemName = MemberManager::getItem().at(choice1 - 1) + "-" +
                               MemberManager::getItem(
                                   MemberManager::getItem().at(choice1 - 1))
                                   .at(choice2 - 1);
                  } else {
                    std::stringstream ss;
                    ss << sign;
                    ss >> choice1;
                    if (choice1 > MemberManager::getItem().size() or
                        choice1 == 0) {
                      std::cout << "您的输入有误，请重新输入。" << std::endl;
                      system("pause");
                      std::cout << std::endl;
                      continue;
                    }
                    itemName = MemberManager::getItem().at(choice1 - 1);
                  }
                  it1->second.setType(itemName);
                  break;
                }
              } else if (choice == "3") {
                //改金额
                while (true) {
                  std::cout << "请输入想要更改成的金额(输入q回车取消操作):";
                  std::string temp;
                  std::cin >> temp;
                  if (temp == "q")
                    break;
                  if (temp[0] != '-' and !isdigit(temp[0])) {
                    std::cout << "您输入的信息有误,请重新输入,谢谢!"
                              << std::endl;
                    system("pause");
                    std::cout << std::endl;
                    continue;
                  }
                  for (const auto &i : temp) {
                    if (!isdigit(i)) {
                      std::cout << "您输入的信息有误,请重新输入,谢谢!"
                                << std::endl;
                      system("pause");
                      std::cout << std::endl;
                      continue;
                    }
                  }
                  double amount;
                  std::stringstream ss;
                  ss << temp;
                  ss >> amount;
                  it1->second.setAmount(amount);
                  break;
                }
              } else if (choice == "4") {
                //改经手人
                std::cout << "请输入想要更改成的经手人(输入q回车取消操作):";
                std::string temp;
                std::cin >> temp;
                if (temp == "q")
                  break;
                it1->second.setDealer(temp);
              } else {
                std::cout << "您输入的信息有误，请重新输入，谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
              std::cout << "修改成功!" << std::endl;
              system("pause");
            }
            break;
          }
        }
      }
    } else if (choice == "8") {
      Member *target{mCurrentUser};
      //管理员选人
      if (mCurrentUser->getPerm() == Permission::root) {
      rootBack2:
        bool flag{false}; //检测是否输入q
        while (true) {
          showTopBar(Type::top);
          std::vector<std::string> nameList = MemberManager::getNameList();
          std::cout << "您想要查看哪位成员的收支信息?" << std::endl;
          for (size_t i = 0; i < nameList.size(); ++i) {
            std::cout << i + 1 << "、" << nameList.at(i) << std::endl;
          }
          std::cout << std::endl << "请输入名字前序号(输入q回车取消操作):";
          std::string sign;
          std::cin >> sign;
          if (sign == "q") {
            flag = true;
            break;
          }
          //检测用户输入是否正确
          for (const auto &i : sign) {
            if (!isdigit(i)) {
              std::cout << "您的输入有误，请重新输入。" << std::endl;
              system("pause");
              continue;
            }
          }
          size_t choice;
          std::stringstream ss;
          ss << sign;
          ss >> choice;
          if (choice > nameList.size() or choice == 0) {
            std::cout << "您的输入有误，请重新输入。" << std::endl;
            system("pause");
            continue;
          }
          target = MemberManager::getMemberByName(nameList.at(choice - 1));
          break;
        }
        if (flag)
          continue;
      }
      while (true) {
        showTopBar(Type::top);
        //检查是否为空
        if (target->getItems().empty()) {
          std::cout << (target == mCurrentUser
                            ? "您的收支信息为空!"
                            : target->getInfo().getName() + "的收支信息为空!")
                    << std::endl;
          system("pause");
          if (mCurrentUser->getPerm() == Permission::root)
            goto rootBack2;
          break;
        }
        std::cout
            << "您要查看某一天的收支信息还是某一时间段还是全部的收支信息?"
            << std::endl
            << "请输入(某一天输入1，时间段输入2,全部输入3,输入q取消操作):";
        std::string sign;
        std::cin >> sign;
        std::cout << std::endl;
        if (sign == "1") {
          while (true) {
            size_t year, month, day;
            std::cout << "请输入您要查看的日期(年月日)(输入q取消操作):";
            std::cin >> sign;
            if (sign == "q")
              break;
            std::stringstream ss;
            ss << sign;
            ss >> year;
            std::cin >> month >> day;
            //日期检查
            if (month == 2) {
              if (!year % 400 or (!year % 4 and year % 100)) {
                if (day > 29) {
                  std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              } else {
                if (day > 28) {
                  std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              }
            } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                       month == 8 or month == 10 or month == 12) {
              if (day > 31) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 30) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            auto [it1, it2] = target->getItems().equal_range(
                std::tuple<size_t, size_t, size_t>{year, month, day});
            if (it1 == it2) {
              std::cout << "该日期没有任何的收支记录!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
            std::cout << target->getInfo().getName() << year << "年" << month
                      << "月" << day << "日的收支信息:" << std::endl;
            for (size_t i = 0; it1 != it2; ++it1) {
              std::cout << ++i << "、"
                        << "收支类型:" << it1->second.getType() << " "
                        << "金额:" << it1->second.getAmount() << " "
                        << "经手人:" << it1->second.getDealer() << std::endl;
            }
            std::cout << std::endl;
          }
        } else if (sign == "2") {
          while (true) {
            size_t year1, year2, month1, month2, day1, day2;
            std::cout
                << "请输入您要查看的开始日期和结束日期(年月日)(输入q取消操作):";
            std::cin >> sign;
            if (sign == "q")
              break;
            std::stringstream ss;
            ss << sign;
            ss >> year1;
            std::cin >> month1 >> day1 >> year2 >> month2 >> day2;
            //开始日期检查
            if (month1 == 2) {
              if (!year1 % 400 or (!year1 % 4 and year1 % 100)) {
                if (day1 > 29) {
                  std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              } else {
                if (day1 > 28) {
                  std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              }
            } else if (month1 == 1 or month1 == 3 or month1 == 5 or
                       month1 == 7 or month1 == 8 or month1 == 10 or
                       month1 == 12) {
              if (day1 > 31) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day1 > 30) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            //结束日期检查
            if (month2 == 2) {
              if (!year2 % 400 or (!year2 % 4 and year2 % 100)) {
                if (day2 > 29) {
                  std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              } else {
                if (day2 > 28) {
                  std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              }
            } else if (month2 == 1 or month2 == 3 or month2 == 5 or
                       month2 == 7 or month2 == 8 or month2 == 10 or
                       month2 == 12) {
              if (day2 > 31) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day2 > 30) {
                std::cout << "您输入的信息有误,请重新输入,谢谢!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            auto it1 = target->getItems().lower_bound(
                std::tuple<size_t, size_t, size_t>{year1, month1, day1});
            auto it2 = target->getItems().upper_bound(
                std::tuple<size_t, size_t, size_t>{year2, month2, day2});
            if (it1 == it2) {
              std::cout << "该日期区间没有任何的收支记录!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
            std::cout << target->getInfo().getName() << year1 << "年" << month1
                      << "月" << day1 << "日到" << year2 << "年" << month2
                      << "月" << day2 << "日的收支信息:" << std::endl;
            for (; it1 != it2; ++it1) {
              auto [year, month, day] = it1->first;
              std::cout << year << "年" << month << "月" << day << "日  "
                        << "收支类型:" << it1->second.getType() << "  "
                        << "金额:" << it1->second.getAmount() << "  "
                        << "经手人:" << it1->second.getDealer() << std::endl;
            }
            std::cout << std::endl;
            system("pause");
          }
        } else if (sign == "3") {
          std::cout << target->getInfo().getName()
                    << "的收支信息:" << std::endl;
          for (const auto &i : target->getItems()) {
            auto [year, month, day] = i.first;
            std::cout << year << "年" << month << "月" << day << "日  "
                      << "收支类型:" << i.second.getType() << "  "
                      << "金额:" << i.second.getAmount() << "  "
                      << "经手人:" << i.second.getDealer() << std::endl;
          }
          std::cout << std::endl;
          system("pause");
        } else if (sign == "q") {
          if (mCurrentUser->getPerm() == Permission::root)
            goto rootBack2;
          break;
        } else {
          std::cout << "您的输入有误，请重新输入!" << std::endl;
          system("pause");
          continue;
        }
      }
    } else if (choice == "9") {
      //返回上级菜单
      return;
    } else {
      //输入错误处理
      std::cout << "您的输入有误，请重新输入!" << std::endl;
      system("pause");
    }
  }
}

void Machine::quitLogin() {
  showTopBar(Type::top);
  std::cout << "您已成功退出登录!" << std::endl;
  system("pause");
  while (true) {
    if (!login()) {
      std::cout << "继续尝试登录请输入1并按回车,"
                   "否则输入其他任意内容按回车键结束程序:";
      std::string sign;
      std::cin >> sign;
      if (sign != "1") {
        end();
        exit(0);
      }
    } else {
      break;
    }
  }
}
