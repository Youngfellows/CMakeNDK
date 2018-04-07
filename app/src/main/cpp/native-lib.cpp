#include "Teacher.h"
#include <android/log.h>
#include <jni.h>
#include <string>
#include <cstring>
#include <cstdlib>
//#include "com_speex_ndkcmake_JNIUtils.h"

#define TAG "AISPEEX_LOG"

/**
 * 比较规则
 * @param a
 * @param b
 * @return
 */
int compare(const void *a, const void *b) {
    return *(double *) a - *(double *) b;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_ndkcmake_JNIUtils_stringLength(JNIEnv *env, jobject instance, jstring string_) {
    const char *string = env->GetStringUTFChars(string_, 0);

    // TODO

    env->ReleaseStringUTFChars(string_, string);
}

/**
 * 1.Java访问本地函数，返回一个字符串
 * 2. Java访问本地函数，返回一个拼接字符串
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_speex_ndkcmake_JNIUtils_stringForJNI(JNIEnv *env, jobject instance, jstring address_) {
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


    __android_log_print(ANDROID_LOG_INFO, TAG, "传递过来的: %s", address_);
    const char *address = env->GetStringUTFChars(address_, 0);//解决java传递过来String中文乱码
    __android_log_print(ANDROID_LOG_INFO, TAG, "传递过来的: %s", address);
    __android_log_print(ANDROID_LOG_INFO, TAG, "传递过来大小: %d", env->GetStringUTFLength(address_));


    //拼接字符串
    std::string str = "你好小驰,我们去XX吧";

    env->ReleaseStringUTFChars(address_, address);
    return env->NewStringUTF(str.c_str());
}

/*
 * C++ jstring字符串拼接
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_speex_ndkcmake_JNIUtils_stringFor2JNI(JNIEnv *env, jobject instance, jstring address_) {
    const char *address = env->GetStringUTFChars(address_, 0);//获取到字符串数组

    int size = env->GetStringUTFLength(address_);
    __android_log_print(ANDROID_LOG_INFO, TAG, "origin size = %d", size);

    //char *数组
    char charArr[] = "我是要拼接的字符串";
    char des[size + strlen(charArr)];//目标数组大小: 原串 + 新串
    strcpy(des, address);//拷贝原始数据到des数组
    strcat(des, charArr);//拼接字符串到des数组

    __android_log_print(ANDROID_LOG_INFO, TAG, "拼接后 = %s", des);

    env->ReleaseStringUTFChars(address_, address);

    return env->NewStringUTF(des);//返回拼接后的字符串
}


extern "C"
JNIEXPORT jdouble JNICALL
Java_com_speex_ndkcmake_JNIUtils_doubleForJNI(JNIEnv *env, jobject instance, jdouble salary,
                                              jdouble bonus) {

    // TODO

}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_speex_ndkcmake_JNIUtils_booleanForJNI(JNIEnv *env, jobject instance, jstring key_) {
    const char *key = env->GetStringUTFChars(key_, 0);

    // TODO

    env->ReleaseStringUTFChars(key_, key);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_ndkcmake_JNIUtils_intForJNI(JNIEnv *env, jobject instance, jint apple, jint orange) {

    // TODO

}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_speex_ndkcmake_JNIUtils_arrayList(JNIEnv *env, jobject instance, jstring key_) {
    const char *key = env->GetStringUTFChars(key_, 0);

    // TODO

    env->ReleaseStringUTFChars(key_, key);
}


extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_speex_ndkcmake_JNIUtils_stringArray(JNIEnv *env, jobject instance, jstring key_) {
    const char *key = env->GetStringUTFChars(key_, 0);

    // TODO

    env->ReleaseStringUTFChars(key_, key);
}


/**
 * C/C++层访问Java对象的属性
 * C++->Java，访问Java属性，返回修改之后的属性内容
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_speex_ndkcmake_JNIUtils_accessJavaField(JNIEnv *env, jobject jobj) {
    //得到Java类JNIUtils.clas
    jclass jclazz = env->GetObjectClass(jobj);

    // 得到java对象的key属性ID()
    jfieldID key_fid = env->GetFieldID(jclazz, "key", "Ljava/lang/String;");

    // 得到Java对象Key属性的值
    jstring key_value = (jstring) env->GetObjectField(jobj, key_fid);
    __android_log_print(ANDROID_LOG_INFO, TAG, "C++获取到的java属性值:  key = %s",
                        env->GetStringUTFChars(key_value, 0));

    //修改key的值
    // 拼接一个新的c字符串
    const char *src = env->GetStringUTFChars(key_value, JNI_FALSE);//java key的值
    char des[2048] = "www.xxxyy.";//新串
    strcat(des, src);//拼接字符串
    __android_log_print(ANDROID_LOG_INFO, TAG, "C++拼接后的java属性: key = %s", des);


    // 修改key属性的值
    jstring key_new_value = env->NewStringUTF(des);//char * 字符串 转换为jstring字符串
    env->SetObjectField(jobj, key_fid, key_new_value);//修改key属性的值

    return key_new_value;
}

/**
 * C->Java，访问Java静态属性
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_speex_ndkcmake_JNIUtils_accessJavaStaticField(JNIEnv *env, jobject jobj) {
    //获取java类JNIUtils.class对象
    jclass jclazz = env->GetObjectClass(jobj);

    //得到JNIUtils类静态属性count的ID
    jfieldID count_fid = env->GetStaticFieldID(jclazz, "count", "I");

    //得到count属性的值
    jint count_value = env->GetStaticIntField(jclazz, count_fid);

    __android_log_print(ANDROID_LOG_INFO, TAG, "C++获取到static的count: %d", count_value);

    //修改count属性的值
    jint count_value_new = count_value + 5;
    env->SetStaticIntField(jclazz, count_fid, count_value_new);//修改java static 属性值
}

/**
 * C/C++访问Java中的public方法
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_ndkcmake_JNIUtils_accessJavaMethod(JNIEnv *env, jobject jobj) {
    //获取JNIUtils.class类对象
    jclass jclazz = env->GetObjectClass(jobj);

    //得到JNIUtils类对象genRandomInt方法的ID
    jmethodID methodId = env->GetMethodID(jclazz, "genRandomInt", "(I)I");

    //调用genRandomInt方法
    jint random = env->CallIntMethod(jobj, methodId, 500);
    __android_log_print(ANDROID_LOG_INFO, TAG, "C++调用java的方法,随机数: random = %d", random);

    return random;
}


/**
 * C++访问Java的static静态方法
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_speex_ndkcmake_JNIUtils_accessJavaStaticMethod(JNIEnv *env, jobject jobj) {
    //获取JNIUtils.class类对象
    jclass jclazz = env->GetObjectClass(jobj);

    // 得到JNIUtils类getUUID静态方法ID
    jmethodID methodId = env->GetStaticMethodID(jclazz, "getUUID", "()Ljava/lang/String;");

    // 调用getUUID方法
    jstring uuid = (jstring) env->CallStaticObjectMethod(jclazz, methodId);

    __android_log_print(ANDROID_LOG_INFO, TAG, "UUID = %s",
                        env->GetStringUTFChars(uuid, JNI_FALSE));

    return uuid;
}

/**
 * C++ ->Java，访问Java父类对象的方法
 */
extern "C"
JNIEXPORT jdouble JNICALL
Java_com_speex_ndkcmake_JNIUtils_accessJavaFatherMethod(JNIEnv *env, jobject jobj) {
    //获取JNIUtils.class类对象
    jclass jclazz = env->GetObjectClass(jobj);

    // Lcom/speex/ndkcmake/Fruit;
    // 得到JNIUtils对象mFruit属性对象的ID
    jfieldID fieldId = env->GetFieldID(jclazz, "mFruit", "Lcom/speex/ndkcmake/Fruit;");

    // 得到mFruit属性对象
    jobject fruit_jobj = env->GetObjectField(jobj, fieldId);

    //得到父类Fruit
    jclass fruit_clazz = env->FindClass("com/speex/ndkcmake/Fruit");

    // 得到父类的price()方法，调用该方法
    jmethodID fruit_mid = env->GetMethodID(fruit_clazz, "price", "()D");

    //调用父类Fruit的price方法
    jdouble price_fu = env->CallNonvirtualDoubleMethod(fruit_jobj, fruit_clazz, fruit_mid);
    __android_log_print(ANDROID_LOG_INFO, TAG, "父类的price = %f", price_fu);

    return price_fu;
}


/**
 * 解决C++获取java中文乱码问题
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_speex_ndkcmake_JNIUtils_getChineseFromJava(JNIEnv *env, jobject instance,
                                                    jstring java_str_) {
    const char *java_str = env->GetStringUTFChars(java_str_, 0);//解决中文乱码问题
    long size = env->GetStringUTFLength(java_str_);
    __android_log_print(ANDROID_LOG_INFO, TAG, "size = %d ,s = %s", size, java_str);

    //拼接一个新的字符串
    char charArr[] = "中国";
    char des[size + strlen(charArr)];//新串的大小
    strcpy(des, charArr);
    strcat(des, java_str);
    __android_log_print(ANDROID_LOG_INFO, TAG, "拼接后: %s", des);

    env->ReleaseStringUTFChars(java_str_, java_str);
    return env->NewStringUTF(des);
}

/**
 * Java->C，C/C++传递中文到Java乱码
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_speex_ndkcmake_JNIUtils_getChineseFromCPP(JNIEnv *env, jobject instance) {

    char chineseArr[] = "这是C++的中文字符串";

    return env->NewStringUTF(chineseArr);
}

/**
 * C++返回一个int[]数组给java
 */
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_speex_ndkcmake_JNIUtils_getByteArrayFromC(JNIEnv *env, jobject instance) {
    jsize size = 20;//数组大小
    jsize i = 0;

    //创建一个jintArray数组
    jintArray int_array = env->NewIntArray(size);

    //jint *指针变量指向int_array数组
    jint *p_array = env->GetIntArrayElements(int_array, JNI_FALSE);

    //写入数据
    for (i = 0; i < size; i++) {
        *(p_array + i) = i;
    }

    //同步到java层
    env->ReleaseIntArrayElements(int_array, p_array, JNI_COMMIT);
    return int_array;//返回int[]数组到java层
}

/**
 * C++对java传入定的数组排序后返回
 */
extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_speex_ndkcmake_JNIUtils_getSortedArray(JNIEnv *env, jobject instance,
                                                jdoubleArray origin_) {
    //jdoubleArray 转换为jdouble *
    jdouble *origin = env->GetDoubleArrayElements(origin_, JNI_FALSE);

    //获取jdoubleArray数组的长度
    jsize size = env->GetArrayLength(origin_);

    //打印java传递过来的数组
    jsize i = 0;
    for (i = 0; i < size; i++) {
        __android_log_print(ANDROID_LOG_INFO, TAG, "%f ", *(origin + i));
    }

    //排序
    qsort(origin, size, sizeof(jdouble), compare);

    // 同步数据到Java层
    env->ReleaseDoubleArrayElements(origin_, origin, JNI_COMMIT);
    return origin_;
}

