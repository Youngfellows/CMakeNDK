#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"

class Teacher : Person {

protected:
    std::string course;//课程
    double salary;//工资

public:
    Teacher(std::string name, int age, std::string address);

    ~Teacher();

    void setSalary(double salary);//设置工资
    double getSalary();//获取工资
    std::string getCourse();//教授的课程

};

#endif //NDKCMAKE_TEACHER_H
