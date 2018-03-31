#ifndef NDKCMAKE_PERSON_H
#define NDKCMAKE_PERSON_H

#include <string>

//抽象类
class Person {
protected:
    std::string name;//姓名
    int age;//年龄
    std::string address;//地址

public:
    Person(std::string name, int age, std::string address);

    Person();

    ~Person();

    std::string getName();

    int getAge();

    std::string getAddress();

    virtual std::string getJob();//获取工作
};

#endif //NDKCMAKE_PERSON_H
