#include "Student.h"

//学生类
Student::Student(std::string name, int age, std::string address, double score) : Person(name, age,
                                                                                        address) {
    this->score = score;
}

Student::~Student() {

}

//实现特有函数
double Student::getScore() {
    return this->score;
}

//实现抽象函数
std::string Person::getJob() {
    return "学生";
}






