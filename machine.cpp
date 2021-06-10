#include "machine.h"

// Member���й�ʵ��

Member *Machine::mCurrentUser{nullptr};

const std::array<std::string, 3> Machine::mStartScreenSplash{
    "* * * * * * * * * * * * * * * * *", "*  ��ӭ��ʹ�ü�ͥ��֧����ϵͳ!  *",
    "* * * * * * * * * * * * * * * * *"};

const std::array<std::string, 3> Machine::mUserTopScreenSplash{
    "* * * * * * * * * * * * * * * * *", "*      $��ͥ��֧����ϵͳ$       *",
    "* * * * * * * * * * * * * * * * *"};

const std::array<std::string, 3> Machine::mRootTopScreenSplash{
    "* * * * * * * * * * * * * * * * *", "*      #��ͥ��֧����ϵͳ#       *",
    "* * * * * * * * * * * * * * * * *"};

const std::array<std::string, 3> Machine::mByeScreenSplash{
    "* * * * * * * * * * * * * * * * *", "*   �ڴ�������һ��ʹ��,�ټ���   *",
    "* * * * * * * * * * * * * * * * *"};

const std::array<std::string, 9> Machine::mMainMenu{
    "+ + + + + + + + + +", "+                 +", "+  1����Ա����    +",
    "+  2���������    +", "+  3����֧����    +", "+  4���˳���¼    +",
    "+  5���˳�ϵͳ    +", "+                 +", "+ + + + + + + + + +"};

const std::array<std::string, 10> Machine::mMemberMenu{
    "+ + + + + + + + + + + + + + + +", "+                             +",
    "+  1����ӳ�Ա(����Ա)        +", "+  2��ɾ����Ա(����Ա)        +",
    "+  3���޸ĸ�����Ϣ            +", "+  4������ԱȨ��ת��(����Ա)  +",
    "+  5���鿴���г�Ա            +", "+  6�������ϼ��˵�            +",
    "+                             +", "+ + + + + + + + + + + + + + + +"};

const std::array<std::string, 7> Machine::mPassMenu{
    "+ + + + + + + + + + +", "+                   +", "+  1���鿴����      +",
    "+  2���޸�����      +", "+  3�������ϼ��˵�  +", "+                   +",
    "+ + + + + + + + + + +"};

const std::array<std::string, 13> Machine::mFinancialMenu{
    "+ + + + + + + + + + + + + + +", "+                           +",
    "+  1�������֧��Ŀ(����Ա)  +", "+  2��ɾ����֧��Ŀ(����Ա)  +",
    "+  3���޸���֧��Ŀ(����Ա)  +", "+  4���鿴��֧��Ŀ          +",
    "+  5�������֧(����Ա)      +", "+  6��ɾ����֧(����Ա)      +",
    "+  7���޸���֧(����Ա)      +", "+  8���鿴��֧              +",
    "+  9�������ϼ��˵�          +", "+                           +",
    "+ + + + + + + + + + + + + + +"};

void Machine::run() {
  start();  //��ʼ����
  mainUI(); //�������˵�
  end();    //��������
}

void Machine::showTopBar(Type type) {
  system("cls");
  if (type == Type::top) {
    if (mCurrentUser->getPerm() == Permission::root) {
      for (const auto &i : mRootTopScreenSplash)
        std::cout << i << std::endl;
      std::cout << "�𾴵�" << mCurrentUser->getInfo().getName() << ",����!"
                << "��ǰ���������û�����:����Ա" << std::endl
                << std::endl;
    } else {
      for (const auto &i : mUserTopScreenSplash)
        std::cout << i << std::endl;
      std::cout << "�𾴵�" << mCurrentUser->getInfo().getName() << ",����!"
                << "��ǰ���������û�����:��ͨ�û�" << std::endl
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
    std::cout << "��ǰ���ݿ���û���κ��˻�,���ȴ���һ������Ա�˻�!"
              << std::endl;
  } else {
    showTopBar(Type::top);
  }
  bool flag{true}; //���ڼ�������Ƿ���ȷ
  std::string name, password, sex;
  int age, year, month, day, height, weight;
  while (true) { //�û���Ϣ��������ж�
    std::cout << "��ʾ:����q�س������ϼ��˵�" << std::endl;
    std::cout << "�������Ա������,�Ա�,����,��������,���,���غ͵�¼����("
                 "�Կո�Ϊÿһ����ķָ��):"
              << std::endl;
    std::cin >> name;
    if (name == "q")
      return false;
    std::cin >> sex >> age >> year >> month >> day >> height >> weight >>
        password;
    std::cout << std::endl;
    //�û���Ϣ���ж�
    if ((sex != "��" and sex != "Ů") or age < 0 or height < 0 or weight < 0 or
        year < 0 or month < 0 or month > 12 or day < 0 or day > 31) {
      std::cout << "���������Ϣ����,����������,лл!" << std::endl
                << std::endl;
      flag = false;
    } else {
      if (month == 2) {
        if (!year % 400 or (!year % 4 and year % 100)) {
          if (day > 29) {
            std::cout << "���������Ϣ����,����������,лл!" << std::endl
                      << std::endl;
            flag = false;
          }
        } else {
          if (day > 28) {
            std::cout << "���������Ϣ����,����������,лл!" << std::endl
                      << std::endl;
            flag = false;
          }
        }
      } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                 month == 8 or month == 10 or month == 12) {
        if (day > 31) {
          std::cout << "���������Ϣ����,����������,лл!" << std::endl
                    << std::endl;
          flag = false;
        }
      } else {
        if (day > 30) {
          std::cout << "���������Ϣ����,����������,лл!" << std::endl
                    << std::endl;
          flag = false;
        }
      }
    }
    //����û������Ƿ���ȷ
    if (flag)
      break;
  }
  //��ֹ������ʧЧ
  std::string tempName;
  if (not empty) {
    tempName = mCurrentUser->getInfo().getName();
  }
  MemberManager::emplaceMember(
      name, sex == "��" ? Sex::male : Sex::female, age, year, month, day,
      height, weight, empty ? Permission::root : Permission::user, password);
  if (not empty) {
    mCurrentUser = MemberManager::getMemberByName(tempName);
  }
  std::cout << "��Ա��ӳɹ���" << std::endl;
  system("pause");
  return true;
}

void Machine::start() {
  while (true) {
    showTopBar(Type::start);
    std::cout << "���ڶ����Ա�ļ�,���Ժ�...";
    bool isOk = MemberManager::fileIn();
    if (!isOk) { //���������ļ�������ʱִ�еĴ������
      showTopBar(Type::start);
      std::cout << "����:�ļ�����ʧ��" << std::endl
                << "��ʾ:������ǵ�һ��ʹ�ñ�ϵͳ������1�����س�������,"
                   "�����������������ݲ����س�����������:";
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
    } else if (MemberManager::isEmpty()) { //û���˻�ʱִ�еĲ���
      if (createAccount(true)) {
        break;
      }
    } else {
      break;
    }
  }
  while (true) {
    if (!login()) {
      std::cout << "�������Ե�¼������1�����س�,"
                   "�������������������ݰ��س�����������:";
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
  std::cout << "��ӭ����¼ϵͳ!" << std::endl;
  std::cout << "��ʾ:����q�س������˳���¼����!" << std::endl << std::endl;
  std::cout << "�������û���:";
  std::string user;
  std::cin >> user;
  if (user == "q") {
    showTopBar(Type::bye);
    system("pause");
    exit(0);
  }
  mCurrentUser = MemberManager::getMemberByName(user);
  if (mCurrentUser == nullptr) {
    std::cout << "��¼ʧ�ܡ����û��������ڡ�";
    return false;
  }
  std::cout << "����������:";
  std::string pass;
  std::cin >> pass;
  if (pass == "q") {
    showTopBar(Type::bye);
    system("pause");
    exit(0);
  }
  if (pass == mCurrentUser->getPass()) {
    std::cout << "��¼�ɹ�!";
    return true;
  } else {
    std::cout << "��¼ʧ��,�������";
    return false;
  }
}

void Machine::end() {
  //��������
  showTopBar(Type::top);
  while (true) {
    bool fileOk = MemberManager::fileOut();
    if (!fileOk) {
      std::cout << "����:�ļ�����ʧ��" << std::endl;
      std::cout << "�Ƿ����³��Ա�����ĵ��ļ�?���ѡ��,"
                   "�򱾴ε����������и��Ĳ��������ᱻ��¼!"
                << std::endl
                << "������1�س�,�������������������ݻس�:";
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
    std::cout << "�������Ĳ˵���ѡ������Ҫ�Ĳ���:" << std::endl;
    for (const auto &i : mMainMenu)
      std::cout << i << std::endl;
    std::cout << std::endl << "��ѡ��������Ҫ�Ĳ���:";
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
      std::cout << "����������������������!" << std::endl;
      system("pause");
    }
  }
}

void Machine::memberManagement() {
  while (true) {
    showTopBar(Type::top);
    std::cout << "�������Ĳ˵���ѡ������Ҫ�Ĳ���:" << std::endl;
    for (const auto &i : mMemberMenu)
      std::cout << i << std::endl;
    std::cout << std::endl << "��ѡ��������Ҫ�Ĳ���:";
    std::string choice;
    std::cin >> choice;
    std::cout << std::endl;
    if (choice == "1") {
      //��ӳ�Ա
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      createAccount();
    } else if (choice == "2") {
      //ɾ����Ա
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "��ѡ������Ҫ�Ƴ��ĳ�Ա:" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "����������ǰ���(����q�س������ϼ��˵�):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //����û������Ƿ���ȷ
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "���������������������롣" << std::endl;
          system("pause");
          continue;
        }
        //�ж��Ƿ�ɾ���Լ�
        if (nameList.at(choice - 1) == mCurrentUser->getInfo().getName()) {
          std::cout << "����Ա����ɾ���Լ�������ɾ��������ת�ù���ԱȨ�ޣ�����"
                       "�Ĺ���Ա��ɾ����"
                    << std::endl;
          system("pause");
          continue;
        }
        MemberManager::removeMemberByName(nameList.at(choice - 1));
        std::cout << "��Ա�Ƴ��ɹ�!" << std::endl;
        system("pause");
        break;
      }
    } else if (choice == "3") {
      //�޸ĸ�����Ϣ
      Member *target{mCurrentUser};
      bool flag{false}; //����Ƿ�����q
      //����Աѡ���Ա
      if (mCurrentUser->getPerm() == Permission::root) {
        while (true) {
        rootBack2:
          showTopBar(Type::top);
          std::vector<std::string> nameList = MemberManager::getNameList();
          std::cout << "��ѡ������Ҫ�޸ĸ�����Ϣ�ĳ�Ա:" << std::endl;
          for (size_t i = 0; i < nameList.size(); ++i) {
            std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
          }
          std::cout << std::endl << "����������ǰ���(����q�س������ϼ��˵�):";
          std::string sign;
          std::cin >> sign;
          if (sign == "q") {
            flag = true;
            break;
          }
          //����û������Ƿ���ȷ
          for (const auto &i : sign) {
            if (!isdigit(i)) {
              std::cout << "���������������������롣" << std::endl;
              system("pause");
              continue;
            }
          }
          size_t choice;
          std::stringstream ss;
          ss << sign;
          ss >> choice;
          if (choice > nameList.size() or choice == 0) {
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            continue;
          }
          target = MemberManager::getMemberByName(nameList.at(choice - 1));
          break;
        }
      }
      if (flag)
        continue;
      //�޸ĳ�Ա��Ϣ
      while (true) {
        showTopBar(Type::top);
        auto [year, month, day] = target->getInfo().getBirth();
        std::cout << "��ѡ����Ҫ�޸ĵĳ�Ա��Ϣ:" << std::endl
                  << "1������:" << target->getInfo().getName() << std::endl
                  << "2���Ա�:"
                  << (target->getInfo().getSex() == Sex::male ? "��" : "Ů")
                  << std::endl
                  << "3������:" << target->getInfo().getAge() << std::endl
                  << "4������:" << year << "��" << month << "��" << day << "��"
                  << std::endl
                  << "5�����:" << target->getInfo().getHeight() << "cm"
                  << std::endl
                  << "6������:" << target->getInfo().getWeight() << "kg"
                  << std::endl
                  << std::endl;
        std::cout << "��ѡ��(����q�س������ϼ��˵�):";
        std::string choice;
        std::cin >> choice;
        std::cout << std::endl;
        if (choice == "q" and mCurrentUser->getPerm() == Permission::root) {
          goto rootBack2;
        } else if (choice == "q") {
          break;
        }
        if (choice == "1") {
          std::cout << "��������Ҫ�޸ĳɵ�����(����q�س�ȡ������):";
          std::string name;
          std::cin >> name;
          if (name == "q")
            continue;
          target->getInfo().setName(name);
          std::cout << "�����޸ĳɹ�!" << std::endl;
          system("pause");
        } else if (choice == "2") {
          std::cout << "ȷ���޸��Ա�������y�س�,���������������ݻس�ȡ������:";
          target->getInfo().setSex(target->getInfo().getSex() == Sex::male
                                       ? Sex::female
                                       : Sex::male);
          std::cout << "�Ա��޸ĳɹ�!" << std::endl;
          system("pause");
        } else if (choice == "3") {
          while (true) {
            std::cout << "��������Ҫ�޸ĳɵ�����(����q�س�ȡ������):";
            std::string sign;
            std::cin >> sign;
            if (sign == "q")
              break;
            int age;
            std::stringstream ss;
            ss << sign;
            ss >> age;
            if (age < 0) {
              std::cout << "���䲻��Ϊ����,�޸�ʧ��!" << std::endl;
              system("pause");
              std::cout << std::endl;
            } else {
              target->getInfo().setAge(age);
              std::cout << "�����޸ĳɹ�!" << std::endl;
              system("pause");
              break;
            }
          }
        } else if (choice == "4") {
          while (true) {
            std::cout
                << "��������Ҫ�޸ĳɵĳ�������(�� �� ��)(����q�س�ȡ������):"
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
              std::cout << "���������Ϣ����,����������,лл!" << std::endl
                        << std::endl;
              system("pause");
              std::cout << std::endl;
            } else if (month == 2) {
              if (!year % 400 or (!year % 4 and year % 100)) {
                if (day > 29) {
                  std::cout << "���������Ϣ����,����������,лл!" << std::endl
                            << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              } else {
                if (day > 28) {
                  std::cout << "���������Ϣ����,����������,лл!" << std::endl
                            << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              }
            } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                       month == 8 or month == 10 or month == 12) {
              if (day > 31) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl
                          << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 30) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl
                          << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            target->getInfo().setBirth(year, month, day);
            std::cout << "���������޸ĳɹ�!" << std::endl;
            system("pause");
            break;
          }
        } else if (choice == "5") {
          while (true) {
            std::cout << "��������Ҫ�޸ĳɵ����(����q�س�ȡ������):";
            std::string sign;
            std::cin >> sign;
            if (sign == "q")
              break;
            int height;
            std::stringstream ss;
            ss << sign;
            ss >> height;
            if (height <= 0) {
              std::cout << "��߲���С�ڵ���0,�޸�ʧ��!" << std::endl;
              system("pause");
              std::cout << std::endl;
            } else {
              target->getInfo().setHeight(height);
              std::cout << "����޸ĳɹ�!" << std::endl;
              system("pause");
              break;
            }
          }
        } else if (choice == "6") {
          while (true) {
            std::cout << "��������Ҫ�޸ĳɵ�����(����q�س�ȡ������):";
            std::string sign;
            std::cin >> sign;
            if (sign == "q")
              break;
            int weight;
            std::stringstream ss;
            ss << sign;
            ss >> weight;
            if (weight <= 0) {
              std::cout << "���ز���С�ڵ���0,�޸�ʧ��!" << std::endl;
              system("pause");
              std::cout << std::endl;
            } else {
              target->getInfo().setWeight(weight);
              std::cout << "�����޸ĳɹ�!" << std::endl;
              system("pause");
              break;
            }
          }
        } else {
          std::cout << "���������������������롣" << std::endl;
          system("pause");
          continue;
        }
      }
    } else if (choice == "4") {
      //����ԱȨ��ת��
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "��ѡ������Ҫת�õĳ�Ա:" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "����������ǰ���(����q�س������ϼ��˵�):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //����û������Ƿ���ȷ
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "���������������������롣" << std::endl;
          system("pause");
          continue;
        }
        //�ж��Ƿ�ת�ø��Լ�
        if (nameList.at(choice - 1) == mCurrentUser->getInfo().getName()) {
          std::cout << "����ת�ù���ԱȨ�޸��Լ�!" << std::endl;
          system("pause");
          continue;
        }
        auto *newRoot = MemberManager::getMemberByName(nameList.at(choice - 1));
        newRoot->setPerm(Permission::root);
        mCurrentUser->setPerm(Permission::user);
        std::cout << "����ԱȨ��ת�óɹ�!" << std::endl;
        system("pause");
        break;
      }
    } else if (choice == "5") {
      //�鿴���г�Ա
      showTopBar(Type::top);
      std::vector<std::string> nameList = MemberManager::getNameList();
      std::cout << "�������г�Ա:" << std::endl;
      for (size_t i = 0; i < nameList.size(); ++i) {
        std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
      }
      std::cout << std::endl;
      system("pause");
    } else if (choice == "6") {
      //�����ϼ��˵�
      return;
    } else {
      //���������
      std::cout << "����������������������!" << std::endl;
      system("pause");
    }
  }
}

void Machine::passwordService() {
  while (true) {
    showTopBar(Type::top);
    std::cout << "�������Ĳ˵���ѡ������Ҫ�Ĳ���:" << std::endl;
    for (const auto &i : mPassMenu)
      std::cout << i << std::endl;
    std::cout << std::endl << "��ѡ��������Ҫ�Ĳ���:";
    std::string choice;
    std::cin >> choice;
    std::cout << std::endl;
    if (choice == "1") {
      const Member *target{mCurrentUser};
      if (mCurrentUser->getPerm() == Permission::root) {
      rootBack:           //����Ա�鿴����ʱ����q�ص��˴�
        bool flag{false}; //����Ƿ�����q
        //����Աѡ���Ա
        while (true) {
          showTopBar(Type::top);
          std::vector<std::string> nameList = MemberManager::getNameList();
          std::cout << "����Ҫ�鿴��λ��Ա������?" << std::endl;
          for (size_t i = 0; i < nameList.size(); ++i) {
            std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
          }
          std::cout << std::endl << "����������ǰ���(����q�س�ȡ������):";
          std::string sign;
          std::cin >> sign;
          if (sign == "q") {
            flag = true;
            break;
          }
          //����û������Ƿ���ȷ
          for (const auto &i : sign) {
            if (!isdigit(i)) {
              std::cout << "���������������������롣" << std::endl;
              system("pause");
              continue;
            }
          }
          size_t choice;
          std::stringstream ss;
          ss << sign;
          ss >> choice;
          if (choice > nameList.size() or choice == 0) {
            std::cout << "���������������������롣" << std::endl;
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
                        ? "��"
                        : target->getInfo().getName())
                << "��������:" << target->getPass() << std::endl;
      system("pause");
      if (mCurrentUser->getPerm() == Permission::root)
        goto rootBack;
    } else if (choice == "2") {
      Member *target{mCurrentUser};
      if (mCurrentUser->getPerm() == Permission::root) {
      rootUser:           //����Ա�޸�����ʱ����q�ص��˴�
        bool flag{false}; //����Ƿ�����q
        //����Աѡ���Ա
        while (true) {
          showTopBar(Type::top);
          std::vector<std::string> nameList = MemberManager::getNameList();
          std::cout << "����Ҫ�޸���λ��Ա������?" << std::endl;
          for (size_t i = 0; i < nameList.size(); ++i) {
            std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
          }
          std::cout << std::endl << "����������ǰ���(����q�س�ȡ������):";
          std::string sign;
          std::cin >> sign;
          if (sign == "q") {
            flag = true;
            break;
          }
          //����û������Ƿ���ȷ
          for (const auto &i : sign) {
            if (!isdigit(i)) {
              std::cout << "���������������������롣" << std::endl;
              system("pause");
              continue;
            }
          }
          size_t choice;
          std::stringstream ss;
          ss << sign;
          ss >> choice;
          if (choice > nameList.size() or choice == 0) {
            std::cout << "���������������������롣" << std::endl;
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
                        ? "��"
                        : target->getInfo().getName())
                << "��ǰ��������:" << target->getPass() << std::endl;
      std::cout << "���뽫"
                << (mCurrentUser->getPerm() == Permission::root
                        ? target->getInfo().getName() + "��"
                        : "")
                << "�����޸�Ϊ(����q�س�ȡ������):";
      std::string pass;
      std::cin >> pass;
      if (pass == "q" and mCurrentUser->getPerm() == Permission::root) {
        goto rootUser;
      } else if (pass == "q") {
        continue;
      }
      target->setPass(pass);
      std::cout << std::endl << "�޸ĳɹ�!" << std::endl;
      system("pause");
    } else if (choice == "3") {
      //�����ϼ��˵�
      return;
    } else {
      //���������
      std::cout << "����������������������!" << std::endl;
      system("pause");
    }
  }
}

void Machine::financialManagement() {
  while (true) {
    showTopBar(Type::top);
    std::cout << "�������Ĳ˵���ѡ������Ҫ�Ĳ���:" << std::endl;
    for (const auto &i : mFinancialMenu)
      std::cout << i << std::endl;
    std::cout << std::endl << "��ѡ��������Ҫ�Ĳ���:";
    std::string choice;
    std::cin >> choice;
    std::cout << std::endl;
    if (choice == "1") {
      //Ȩ�޼��
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        std::cout
            << "��ѡ�����һ����Ŀ�������Ŀ(������1��2������q�س�ȡ������):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q") {
          break;
        } else if (sign == "1") {
          showTopBar(Type::top);
          std::cout << "������Ҫ��ӵ�һ����Ŀ(����q�س�ȡ������):";
          std::string name;
          std::cin >> name;
          if (name == "q")
            continue;
          MemberManager::addItem(name);
          std::cout << "��ӳɹ�" << std::endl;
          system("pause");
          break;
        } else if (sign == "2") {
          while (true) {
            showTopBar(Type::top);
            std::cout << "������Ҫ��ӵĶ�����Ŀ(����q�س�ȡ������):";
            std::string name2;
            std::cin >> name2;
            if (name2 == "q")
              break;
            std::cout << "��ѡ��ö�����Ŀ������һ����Ŀ:" << std::endl;
            size_t choice{0};
            for (const auto &item : MemberManager::getItem()) {
              std::cout << ++choice << "��" << item << std::endl;
            }
            std::cout << std::endl << "��ѡ��(����q�س�ȡ������):";
            std::string name1;
            std::cin >> name1;
            if (name1 == "q") {
              break;
            }
            std::stringstream ss;
            ss << name1;
            ss >> choice;
            if (choice == 0 or choice > MemberManager::getItem().size()) {
              std::cout << "���������������������롣" << std::endl;
              system("pause");
              continue;
            }
            MemberManager::addItem(MemberManager::getItem().at(choice - 1),
                                   name2);
            std::cout << "��ӳɹ�" << std::endl;
            system("pause");
            break;
          }
        } else {
          std::cout << "����������������������!" << std::endl;
          system("pause");
        }
      }
    } else if (choice == "2") {
      //Ȩ�޼��
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        if (MemberManager::getItem().empty()) {
          std::cout << "��ǰ��֧��ĿΪ�գ����ȴ�����֧��Ŀ��" << std::endl;
          system("pause");
          break;
        }
        std::cout << "��ѡ������Ҫɾ����һ����Ŀ�������Ŀ:" << std::endl;
        std::cout << "��ʾ:��Ҫɾ��һ����Ŀ������x,ɾ��������Ŀ������x "
                     "x(x����һ���������Ŀǰ������)"
                  << std::endl;
        size_t choice1{0}, choice2{0};
        for (const auto &i : MemberManager::getItem()) {
          std::cout << ++choice1 << "��" << i << ":" << std::endl;
          choice2 = 0;
          for (const auto &j : MemberManager::getItem(i)) {
            std::cout << "  " << ++choice2 << "��" << j << std::endl;
          }
          std::cout << std::endl;
        }
        std::cout << std::endl << "��ѡ��(����q�س�ȡ������):";
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
          std::cout << "���������������������롣" << std::endl;
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
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            std::cout << std::endl;
            continue;
          }
          MemberManager::removeItemByName(
              MemberManager::getItem().at(choice1 - 1),
              MemberManager::getItem(MemberManager::getItem().at(choice1 - 1))
                  .at(choice2 - 1));
          std::cout << "ɾ���ɹ�!" << std::endl;
          system("pause");
        } else {
          std::stringstream ss;
          ss << sign;
          ss >> choice1;
          if (choice1 == 0 or choice1 > MemberManager::getItem().size()) {
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            std::cout << std::endl;
            continue;
          }
          MemberManager::removeItemByName(
              MemberManager::getItem().at(choice1 - 1));
          std::cout << "ɾ���ɹ�!" << std::endl;
          system("pause");
        }
        if (MemberManager::getItem().empty())
          break;
      }
    } else if (choice == "3") {
      //Ȩ�޼��
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      while (true) {
        showTopBar(Type::top);
        if (MemberManager::getItem().empty()) {
          std::cout << "��ǰ��֧��ĿΪ�գ����ȴ�����֧��Ŀ��" << std::endl;
          system("pause");
          break;
        }
        std::cout << "��ѡ������Ҫ�޸ĵ�һ����Ŀ�������Ŀ:" << std::endl;
        std::cout << "��ʾ:��Ҫ�޸�һ����Ŀ������x,�޸Ķ�����Ŀ������x "
                     "x(x����һ���������Ŀǰ������)"
                  << std::endl;
        size_t choice1{0}, choice2{0};
        for (const auto &i : MemberManager::getItem()) {
          std::cout << ++choice1 << "��" << i << ":" << std::endl;
          choice2 = 0;
          for (const auto &j : MemberManager::getItem(i)) {
            std::cout << "  " << ++choice2 << "��" << j << std::endl;
          }
          std::cout << std::endl;
        }
        std::cout << std::endl << "��ѡ��(����q�س�ȡ������):";
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
          std::cout << "���������������������롣" << std::endl;
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
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            std::cout << std::endl;
            continue;
          }
          std::cout << "�������µ���֧��Ŀ��(����q�س�ȡ������):";
          std::string name;
          std::cin >> name;
          if (name == "q")
            continue;
          MemberManager::editItem(
              MemberManager::getItem().at(choice1 - 1),
              MemberManager::getItem(MemberManager::getItem().at(choice1 - 1))
                  .at(choice2 - 1),
              name);
          std::cout << "�޸ĳɹ�!" << std::endl;
          system("pause");
          continue;
        } else {
          std::stringstream ss;
          ss << sign;
          ss >> choice1;
          if (choice1 == 0 or choice1 > MemberManager::getItem().size()) {
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            std::cout << std::endl;
            continue;
          }
          std::cout << "�������µ���֧��Ŀ��(����q�س�ȡ������):";
          std::string name;
          std::cin >> name;
          if (name == "q")
            continue;
          MemberManager::editItem(MemberManager::getItem().at(choice1 - 1),
                                  name);
          std::cout << "�޸ĳɹ�!" << std::endl;
          system("pause");
          continue;
        }
        if (MemberManager::getItem().empty())
          break;
      }
    } else if (choice == "4") {
      showTopBar(Type::top);
      if (MemberManager::getItem().empty()) {
        std::cout << "��ǰ��֧��ĿΪ�գ����ȴ�����֧��Ŀ��" << std::endl;
        system("pause");
        continue;
      }
      std::cout << "���������е���֧��Ŀ:" << std::endl;
      size_t choice1{0}, choice2{0};
      for (const auto &i : MemberManager::getItem()) {
        std::cout << ++choice1 << "��" << i << ":" << std::endl;
        choice2 = 0;
        for (const auto &j : MemberManager::getItem(i)) {
          std::cout << "  " << ++choice2 << "��" << j << std::endl;
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
      system("pause");
    } else if (choice == "5") {
      //Ȩ�޼��
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      showTopBar(Type::top);
      if (MemberManager::getItem().empty()) {
        std::cout << "��ǰ��֧��ĿΪ�գ����ȴ�����֧��Ŀ��" << std::endl;
        system("pause");
        break;
      }
      Member *target{nullptr};
      //����Աѡ���Ա
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "����ҪΪ��λ��Ա�����֧��Ϣ?" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "����������ǰ���(����q�س�ȡ������):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //����û������Ƿ���ȷ
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "���������������������롣" << std::endl;
          system("pause");
          continue;
        }
        showTopBar(Type::top);
        while (true) {
          target = MemberManager::getMemberByName(nameList.at(choice - 1));
          std::cout << "������Ҫ��ӵ���֧��Ϣ��ʱ��(������),���,������("
                       "����q�س�ȡ������):";
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
            std::cout << "���������Ϣ����,����������,лл!" << std::endl;
            std::cin.clear();
            std::cin.sync();
            system("pause");
            std::cout << std::endl;
            continue;
          }
          if (month == 2) {
            if (!year % 400 or (!year % 4 and year % 100)) {
              if (day > 29) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 28) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
          } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                     month == 8 or month == 10 or month == 12) {
            if (day > 31) {
              std::cout << "���������Ϣ����,����������,лл!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          } else {
            if (day > 30) {
              std::cout << "���������Ϣ����,����������,лл!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          }
          std::cout << std::endl;
          //ѡ����֧����
          size_t choice1{0}, choice2{0};
          while (true) {
            std::cout << "��ѡ�����֧��Ϣ������һ����Ŀ�������Ŀ:"
                      << std::endl;
            std::cout << "��ʾ:��Ҫѡ��һ����Ŀ������x,ѡ�������Ŀ������x "
                         "x(x����һ���������Ŀǰ������)"
                      << std::endl;
            choice1 = 0;
            choice2 = 0;
            for (const auto &i : MemberManager::getItem()) {
              std::cout << ++choice1 << "��" << i << ":" << std::endl;
              choice2 = 0;
              for (const auto &j : MemberManager::getItem(i)) {
                std::cout << "  " << ++choice2 << "��" << j << std::endl;
              }
              std::cout << std::endl;
            }
            std::cout << std::endl << "��ѡ��(����q�س�ȡ������):";
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
              std::cout << "���������������������롣" << std::endl;
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
                std::cout << "���������������������롣" << std::endl;
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
                std::cout << "���������������������롣" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
              itemName = MemberManager::getItem().at(choice1 - 1);
            }
            target->getItems().emplace(
                std::tuple<size_t, size_t, size_t>{year, month, day},
                FinancialItem{itemName, amount, dealer});
            std::cout << "��ӳɹ�!" << std::endl;
            system("pause");
            break;
          }
          break;
        }
        break;
      }
    } else if (choice == "6") {
      //Ȩ�޼��
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      Member *target{nullptr};
      //����Աѡ��
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "����Ҫɾ����λ��Ա����֧��Ϣ?" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "����������ǰ���(����q�س�ȡ������):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //����û������Ƿ���ȷ
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "���������������������롣" << std::endl;
          system("pause");
          continue;
        }
        target = MemberManager::getMemberByName(nameList.at(choice - 1));
        while (true) {
          showTopBar(Type::top);
          //����Ƿ�Ϊ��
          if (target->getItems().empty()) {
            std::cout << (target == mCurrentUser
                              ? "������֧��ϢΪ��!"
                              : target->getInfo().getName() + "����֧��ϢΪ��!")
                      << std::endl;
            system("pause");
            break;
          }
          std::cout << "��ʾ:ɾ����֧��Ϣ��Ҫ֪��׼ȷ����!�������֪��,"
                       "�����ڡ��鿴��֧���в鿴��"
                    << std::endl;
          std::cout << "��������Ҫɾ������֧��Ϣ������׼ȷ����(������)("
                       "����qȡ������):";
          size_t year, month, day;
          std::cin >> sign;
          if (sign == "q")
            break;
          ss.clear();
          ss.str("");
          ss << sign;
          ss >> year;
          std::cin >> month >> day;
          //���ڼ��
          if (month == 2) {
            if (!year % 400 or (!year % 4 and year % 100)) {
              if (day > 29) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 28) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
          } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                     month == 8 or month == 10 or month == 12) {
            if (day > 31) {
              std::cout << "���������Ϣ����,����������,лл!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          } else {
            if (day > 30) {
              std::cout << "���������Ϣ����,����������,лл!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          }
          std::cout << std::endl;
          //�����Ŀ��ѡ��
          while (true) {
            auto [it1, it2] = target->getItems().equal_range(
                std::tuple<size_t, size_t, size_t>{year, month, day});
            size_t size = std::distance(it1, it2);
            if (it1 == it2) {
              std::cout << "������û���κε���֧��¼!" << std::endl;
              system("pause");
              std::cout << std::endl;
              break;
            }
            showTopBar(Type::top);
            std::cout << "��ѡ����Ҫɾ������Ŀ��Ϣ:" << std::endl;
            std::cout << target->getInfo().getName() << year << "��" << month
                      << "��" << day << "�յ���֧��Ϣ:" << std::endl;
            for (size_t i = 0; it1 != it2; ++it1) {
              std::cout << ++i << "��"
                        << "��֧����:" << it1->second.getType() << " "
                        << "���:" << it1->second.getAmount() << " "
                        << "������:" << it1->second.getDealer() << std::endl;
            }
            std::cout << std::endl;
            std::cout << "��ѡ��(����qȡ������):";
            std::cin >> sign;
            if (sign == "q")
              break;
            for (const auto &i : sign) {
              if (!isdigit(i)) {
                std::cout << "���������Ϣ�������������룬лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            if (sign.length() == 0 or sign.length() > size) {
              std::cout << "���������Ϣ�������������룬лл!" << std::endl;
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
            std::cout << "ɾ���ɹ�!";
            break;
          }
        }
      }
    } else if (choice == "7") {
      //Ȩ�޼��
      if (mCurrentUser->getPerm() == Permission::user) {
        std::cout << "Ȩ�޲���:�����ǹ���Ա��û�в���Ȩ��!" << std::endl;
        system("pause");
        continue;
      }
      Member *target{nullptr};
      //����Աѡ��
      while (true) {
        showTopBar(Type::top);
        std::vector<std::string> nameList = MemberManager::getNameList();
        std::cout << "����Ҫ�޸���λ��Ա����֧��Ϣ?" << std::endl;
        for (size_t i = 0; i < nameList.size(); ++i) {
          std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
        }
        std::cout << std::endl << "����������ǰ���(����q�س�ȡ������):";
        std::string sign;
        std::cin >> sign;
        if (sign == "q")
          break;
        //����û������Ƿ���ȷ
        for (const auto &i : sign) {
          if (!isdigit(i)) {
            std::cout << "���������������������롣" << std::endl;
            system("pause");
            continue;
          }
        }
        size_t choice;
        std::stringstream ss;
        ss << sign;
        ss >> choice;
        if (choice > nameList.size() or choice == 0) {
          std::cout << "���������������������롣" << std::endl;
          system("pause");
          continue;
        }
        target = MemberManager::getMemberByName(nameList.at(choice - 1));
        while (true) {
          showTopBar(Type::top);
          std::cout << "��ʾ:�޸���֧��Ϣ��Ҫ֪��׼ȷ����!�������֪��,"
                       "�����ڡ��鿴��֧���в鿴��"
                    << std::endl;
          std::cout << "��������Ҫɾ������֧��Ϣ������׼ȷ����(������)("
                       "����qȡ������):";
          size_t year, month, day;
          std::cin >> sign;
          if (sign == "q")
            break;
          ss.clear();
          ss.str("");
          ss << sign;
          ss >> year;
          std::cin >> month >> day;
          //���ڼ��
          if (month == 2) {
            if (!year % 400 or (!year % 4 and year % 100)) {
              if (day > 29) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 28) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
          } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                     month == 8 or month == 10 or month == 12) {
            if (day > 31) {
              std::cout << "���������Ϣ����,����������,лл!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          } else {
            if (day > 30) {
              std::cout << "���������Ϣ����,����������,лл!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
          }
          std::cout << std::endl;
          //�����Ŀ��ѡ��
          while (true) {
            auto [it1, it2] = target->getItems().equal_range(
                std::tuple<size_t, size_t, size_t>{year, month, day});
            size_t size = std::distance(it1, it2);
            if (it1 == it2) {
              std::cout << "������û���κε���֧��¼!" << std::endl;
              system("pause");
              std::cout << std::endl;
              break;
            }
            showTopBar(Type::top);
            std::cout << "��ѡ����Ҫ�޸ĵ���Ŀ��Ϣ:" << std::endl;
            std::cout << target->getInfo().getName() << year << "��" << month
                      << "��" << day << "�յ���֧��Ϣ:" << std::endl;
            for (size_t i = 0; it1 != it2; ++it1) {
              std::cout << ++i << "��"
                        << "��֧����:" << it1->second.getType() << " "
                        << "���:" << it1->second.getAmount() << " "
                        << "������:" << it1->second.getDealer() << std::endl;
            }
            std::cout << std::endl;
            std::cout << "��ѡ��(����qȡ������):";
            std::cin >> sign;
            if (sign == "q")
              break;
            for (const auto &i : sign) {
              if (!isdigit(i)) {
                std::cout << "���������Ϣ�������������룬лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            if (sign.length() == 0 or sign.length() > size) {
              std::cout << "���������Ϣ�������������룬лл!" << std::endl;
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
              std::cout << "����Ҫ�޸�ʲô?" << std::endl;
              auto [year, month, day] = it1->first;
              std::cout << "1������:" << year << "��" << month << "��" << day
                        << "��" << std::endl;
              std::cout << "2����֧��Ŀ:" << it1->second.getType() << std::endl;
              std::cout << "3�����:" << it1->second.getAmount() << std::endl;
              std::cout << "4��������:" << it1->second.getDealer() << std::endl;
              std::cout << std::endl << "��ѡ��(����q�س�ȡ������):";
              std::string choice;
              std::cin >> choice;
              std::cout << std::endl;
              if (choice == "q") {
                break;
              } else if (choice == "1") {
                //������
                while (true) {
                  std::cout << "���뽫�����޸�Ϊ(������)(����q�س�ȡ������):";
                  std::string sign;
                  std::cin >> sign;
                  if (sign == "q")
                    break;
                  ss.clear();
                  ss.str("");
                  ss << sign;
                  ss >> year;
                  std::cin >> month >> day;
                  //�������
                  if (month == 2) {
                    if (!year % 400 or (!year % 4 and year % 100)) {
                      if (day > 29) {
                        std::cout << "���������Ϣ����,����������,лл!"
                                  << std::endl;
                        system("pause");
                        std::cout << std::endl;
                        continue;
                      }
                    } else {
                      if (day > 28) {
                        std::cout << "���������Ϣ����,����������,лл!"
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
                      std::cout << "���������Ϣ����,����������,лл!"
                                << std::endl;
                      system("pause");
                      std::cout << std::endl;
                      continue;
                    }
                  } else {
                    if (day > 30) {
                      std::cout << "���������Ϣ����,����������,лл!"
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
                //����֧��Ŀ
                if (MemberManager::getItem().empty()) {
                  std::cout << "��ǰ��֧��ĿΪ�գ����ȴ�����֧��Ŀ��"
                            << std::endl;
                  system("pause");
                  continue;
                }
                //ѡ����֧����
                size_t choice1{0}, choice2{0};
                while (true) {
                  std::cout << "��ѡ���µ���֧��Ŀ:" << std::endl;
                  std::cout
                      << "��ʾ:��Ҫѡ��һ����Ŀ������x,ѡ�������Ŀ������x "
                         "x(x����һ���������Ŀǰ������)"
                      << std::endl;
                  choice1 = 0;
                  choice2 = 0;
                  for (const auto &i : MemberManager::getItem()) {
                    std::cout << ++choice1 << "��" << i << ":" << std::endl;
                    choice2 = 0;
                    for (const auto &j : MemberManager::getItem(i)) {
                      std::cout << "  " << ++choice2 << "��" << j << std::endl;
                    }
                    std::cout << std::endl;
                  }
                  std::cout << std::endl << "��ѡ��(����q�س�ȡ������):";
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
                    std::cout << "���������������������롣" << std::endl;
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
                      std::cout << "���������������������롣" << std::endl;
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
                      std::cout << "���������������������롣" << std::endl;
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
                //�Ľ��
                while (true) {
                  std::cout << "��������Ҫ���ĳɵĽ��(����q�س�ȡ������):";
                  std::string temp;
                  std::cin >> temp;
                  if (temp == "q")
                    break;
                  if (temp[0] != '-' and !isdigit(temp[0])) {
                    std::cout << "���������Ϣ����,����������,лл!"
                              << std::endl;
                    system("pause");
                    std::cout << std::endl;
                    continue;
                  }
                  for (const auto &i : temp) {
                    if (!isdigit(i)) {
                      std::cout << "���������Ϣ����,����������,лл!"
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
                //�ľ�����
                std::cout << "��������Ҫ���ĳɵľ�����(����q�س�ȡ������):";
                std::string temp;
                std::cin >> temp;
                if (temp == "q")
                  break;
                it1->second.setDealer(temp);
              } else {
                std::cout << "���������Ϣ�������������룬лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
              std::cout << "�޸ĳɹ�!" << std::endl;
              system("pause");
            }
            break;
          }
        }
      }
    } else if (choice == "8") {
      Member *target{mCurrentUser};
      //����Աѡ��
      if (mCurrentUser->getPerm() == Permission::root) {
      rootBack2:
        bool flag{false}; //����Ƿ�����q
        while (true) {
          showTopBar(Type::top);
          std::vector<std::string> nameList = MemberManager::getNameList();
          std::cout << "����Ҫ�鿴��λ��Ա����֧��Ϣ?" << std::endl;
          for (size_t i = 0; i < nameList.size(); ++i) {
            std::cout << i + 1 << "��" << nameList.at(i) << std::endl;
          }
          std::cout << std::endl << "����������ǰ���(����q�س�ȡ������):";
          std::string sign;
          std::cin >> sign;
          if (sign == "q") {
            flag = true;
            break;
          }
          //����û������Ƿ���ȷ
          for (const auto &i : sign) {
            if (!isdigit(i)) {
              std::cout << "���������������������롣" << std::endl;
              system("pause");
              continue;
            }
          }
          size_t choice;
          std::stringstream ss;
          ss << sign;
          ss >> choice;
          if (choice > nameList.size() or choice == 0) {
            std::cout << "���������������������롣" << std::endl;
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
        //����Ƿ�Ϊ��
        if (target->getItems().empty()) {
          std::cout << (target == mCurrentUser
                            ? "������֧��ϢΪ��!"
                            : target->getInfo().getName() + "����֧��ϢΪ��!")
                    << std::endl;
          system("pause");
          if (mCurrentUser->getPerm() == Permission::root)
            goto rootBack2;
          break;
        }
        std::cout
            << "��Ҫ�鿴ĳһ�����֧��Ϣ����ĳһʱ��λ���ȫ������֧��Ϣ?"
            << std::endl
            << "������(ĳһ������1��ʱ�������2,ȫ������3,����qȡ������):";
        std::string sign;
        std::cin >> sign;
        std::cout << std::endl;
        if (sign == "1") {
          while (true) {
            size_t year, month, day;
            std::cout << "��������Ҫ�鿴������(������)(����qȡ������):";
            std::cin >> sign;
            if (sign == "q")
              break;
            std::stringstream ss;
            ss << sign;
            ss >> year;
            std::cin >> month >> day;
            //���ڼ��
            if (month == 2) {
              if (!year % 400 or (!year % 4 and year % 100)) {
                if (day > 29) {
                  std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              } else {
                if (day > 28) {
                  std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              }
            } else if (month == 1 or month == 3 or month == 5 or month == 7 or
                       month == 8 or month == 10 or month == 12) {
              if (day > 31) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day > 30) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            auto [it1, it2] = target->getItems().equal_range(
                std::tuple<size_t, size_t, size_t>{year, month, day});
            if (it1 == it2) {
              std::cout << "������û���κε���֧��¼!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
            std::cout << target->getInfo().getName() << year << "��" << month
                      << "��" << day << "�յ���֧��Ϣ:" << std::endl;
            for (size_t i = 0; it1 != it2; ++it1) {
              std::cout << ++i << "��"
                        << "��֧����:" << it1->second.getType() << " "
                        << "���:" << it1->second.getAmount() << " "
                        << "������:" << it1->second.getDealer() << std::endl;
            }
            std::cout << std::endl;
          }
        } else if (sign == "2") {
          while (true) {
            size_t year1, year2, month1, month2, day1, day2;
            std::cout
                << "��������Ҫ�鿴�Ŀ�ʼ���ںͽ�������(������)(����qȡ������):";
            std::cin >> sign;
            if (sign == "q")
              break;
            std::stringstream ss;
            ss << sign;
            ss >> year1;
            std::cin >> month1 >> day1 >> year2 >> month2 >> day2;
            //��ʼ���ڼ��
            if (month1 == 2) {
              if (!year1 % 400 or (!year1 % 4 and year1 % 100)) {
                if (day1 > 29) {
                  std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              } else {
                if (day1 > 28) {
                  std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              }
            } else if (month1 == 1 or month1 == 3 or month1 == 5 or
                       month1 == 7 or month1 == 8 or month1 == 10 or
                       month1 == 12) {
              if (day1 > 31) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day1 > 30) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            }
            //�������ڼ��
            if (month2 == 2) {
              if (!year2 % 400 or (!year2 % 4 and year2 % 100)) {
                if (day2 > 29) {
                  std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              } else {
                if (day2 > 28) {
                  std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                  system("pause");
                  std::cout << std::endl;
                  continue;
                }
              }
            } else if (month2 == 1 or month2 == 3 or month2 == 5 or
                       month2 == 7 or month2 == 8 or month2 == 10 or
                       month2 == 12) {
              if (day2 > 31) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
                system("pause");
                std::cout << std::endl;
                continue;
              }
            } else {
              if (day2 > 30) {
                std::cout << "���������Ϣ����,����������,лл!" << std::endl;
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
              std::cout << "����������û���κε���֧��¼!" << std::endl;
              system("pause");
              std::cout << std::endl;
              continue;
            }
            std::cout << target->getInfo().getName() << year1 << "��" << month1
                      << "��" << day1 << "�յ�" << year2 << "��" << month2
                      << "��" << day2 << "�յ���֧��Ϣ:" << std::endl;
            for (; it1 != it2; ++it1) {
              auto [year, month, day] = it1->first;
              std::cout << year << "��" << month << "��" << day << "��  "
                        << "��֧����:" << it1->second.getType() << "  "
                        << "���:" << it1->second.getAmount() << "  "
                        << "������:" << it1->second.getDealer() << std::endl;
            }
            std::cout << std::endl;
            system("pause");
          }
        } else if (sign == "3") {
          std::cout << target->getInfo().getName()
                    << "����֧��Ϣ:" << std::endl;
          for (const auto &i : target->getItems()) {
            auto [year, month, day] = i.first;
            std::cout << year << "��" << month << "��" << day << "��  "
                      << "��֧����:" << i.second.getType() << "  "
                      << "���:" << i.second.getAmount() << "  "
                      << "������:" << i.second.getDealer() << std::endl;
          }
          std::cout << std::endl;
          system("pause");
        } else if (sign == "q") {
          if (mCurrentUser->getPerm() == Permission::root)
            goto rootBack2;
          break;
        } else {
          std::cout << "����������������������!" << std::endl;
          system("pause");
          continue;
        }
      }
    } else if (choice == "9") {
      //�����ϼ��˵�
      return;
    } else {
      //���������
      std::cout << "����������������������!" << std::endl;
      system("pause");
    }
  }
}

void Machine::quitLogin() {
  showTopBar(Type::top);
  std::cout << "���ѳɹ��˳���¼!" << std::endl;
  system("pause");
  while (true) {
    if (!login()) {
      std::cout << "�������Ե�¼������1�����س�,"
                   "�������������������ݰ��س�����������:";
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
