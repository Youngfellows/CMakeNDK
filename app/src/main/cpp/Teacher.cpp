#include "Teacher.h"

//教师类
Teacher::Teacher(std::string name, int age, std::string address) : Person(name, age, address) {

}

Teacher::~Teacher() {

}

/**
 * 获取教授课程
 * @return
 */
std::string Teacher::getCourse() {
    return "国学";
}

/**
 * 设置工资
 * @param salary
 */
void Teacher::setSalary(double salary) {
    this->salary = salary;
}

/**
 * 获取工资
 * @return
 */
double Teacher::getSalary() {
    return this->salary;
}

/**
 * 实现抽象函数 -- 职位
 * @return
 */
std::string Person::getJob() {
    return "教师";
}
