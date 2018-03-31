#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "../cpp/Person.h"

class Student : Person {
protected:
    double score;//分数

public:
    Student(std::string name, int age, std::string address, double score);

    ~Student();

    double getScore();//获取分数
};

#endif //NDKCMAKE_HELLO_H
