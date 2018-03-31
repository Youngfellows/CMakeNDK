#include "Person.h"

//抽象类
Person::Person(std::string name, int age, std::string address) {
    this->name = name;
    this->age = age;
    this->address = address;
}

Person::~Person() {

}

std::string Person::getName() {
    return this->name;
}

int Person::getAge() {
    return this->age;
}

std::string Person::getAddress() {
    return this->address;
}

Person::Person() {

}
