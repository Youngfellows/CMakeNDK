#include <jni.h>
#include <string>
#include "Teacher.h"
#include <android/log.h>

#define TAG "STUDENT"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_speex_ndkcmake_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    Person *person;//父类的指针变量

    Teacher *teacher = new Teacher("大黑牛", 45, "广州白云区");
    person = (Person *) teacher;//子类对象指向父类的指针变量
    std::string name = person->getName();//姓名
    std::string job = person->getJob();//工作
    int age = person->getAge();//年龄
    teacher->setSalary(17800);//设置工资
    std::string course = teacher->getCourse();//教授课程
    double salary = teacher->getSalary();//教师工资

    __android_log_print(ANDROID_LOG_INFO, TAG, "姓名: %s ,职位: %s ,年龄: %d ,工资: %lf ,课程: %s",
                        name.c_str(), job.c_str(), age, salary, course.c_str());


    //    Student *student = new Student("丽丽", 23, "深圳南山", 48.79);
    //    double score = student->getScore();//分数


//    __android_log_print(ANDROID_LOG_INFO, TAG, "姓名: %s ,职位: %s ,年龄: %d ,分数: %lf",
//                        name.c_str(), job.c_str(), age, score);



    std::string str = "你好小驰";
    return env->NewStringUTF(str.c_str());
}
