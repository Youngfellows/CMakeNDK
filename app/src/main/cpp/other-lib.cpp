#include <jni.h>
#include <android/log.h>
#include "util.h"
#include <sys/system_properties.h>
#include <string>
#include <cstring>


/**
 * C++返回double给java
 */
extern "C"
JNIEXPORT jdouble JNICALL
Java_com_speex_ndkcmake_JNIUtils_doubleForJNI(JNIEnv *env, jobject instance, jdouble salary,
                                              jdouble bonus) {
    LOGD("工资: %f ,奖金: %f", salary, bonus);
    jint len;
    char buf[1024];
    __system_property_get("ro.serialno", buf);//获取设备序列号
    LOGI("serialno: %s", buf);
    len = strlen(buf);
    return salary + bonus + len;
}

/**
 * C++返回的String
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_speex_ndkcmake_JNIUtils_stringsForJNI(JNIEnv *env, jobject instance, jstring str_) {

    //1. 将unicode编码的java字符串转换成C风格字符串
    const char *str = env->GetStringUTFChars(str_, JNI_FALSE);

    int len = strlen(str);
    char n_name[len];
    strcpy(n_name, str);//拷贝字符串

    //2. 释放内存
    env->ReleaseStringUTFChars(str_, str);

    //3. 处理
    char buf[1024];
    __system_property_get(n_name, buf);
    LOGD("serialno : %s", buf);

    //4. 去掉尾部"\0"
    int len_buf = strlen(buf);
    std::string result(buf, len_buf);
    return env->NewStringUTF(result.c_str());
}


/**
 * C++返回boolean给java
 */
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_speex_ndkcmake_JNIUtils_booleanForJNI(JNIEnv *env, jobject instance) {

    return JNI_FALSE;
}

/**
 * C++返回int到java
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_ndkcmake_JNIUtils_intForJNI(JNIEnv *env, jobject instance, jint apple, jint orange) {
    return apple + orange;
}


/**
 * C++返回String[]数组给java
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_speex_ndkcmake_JNIUtils_stringArrayForJNI(JNIEnv *env, jobject instance, jstring key_) {
    const char *key = env->GetStringUTFChars(key_, 0);

    env->ReleaseStringUTFChars(key_, key);
}

/**
 * 获取byte[]数组
 */
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_speex_ndkcmake_JNIUtils_getByteArray(JNIEnv *env, jobject instance, jbyteArray array) {

    //1. 获取数组指针和长度
    jbyte *array_body = env->GetByteArrayElements(array, JNI_FALSE);
    int len_body = env->GetArrayLength(array);

    //2.具体处理
    jbyteArray result = env->NewByteArray(len_body);//获取一个byte数组
    jbyte buf[len_body];//byte数组
    for (int i = 0; i < len_body; ++i) {
        buf[i] = *array_body + 1;//给数组赋值
        array_body++;//指针变化
    }

    //3. 释放内存
    env->ReleaseByteArrayElements(array, array_body, JNI_FALSE);

    //4. 赋值
    env->SetByteArrayRegion(result, 0, len_body, buf);
    return result;
}

/**
 * C++调用java静态方法和静态变量
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_speex_ndkcmake_JNIUtils_invokeStaticFieldAndMethod(JNIEnv *env, jobject jobj, jstring name,
                                                            jint age, jstring address,
                                                            jdouble salary) {
    jclass clazz = NULL;
    jfieldID fid = NULL;
    jmethodID mid = NULL;
    jstring j_result = NULL;

    //1. 获取SpeexUtils类的Class引用
    clazz = env->FindClass("com/speex/ndkcmake/utils/SpeexUtils");

    if (clazz == NULL) {
        LOGD("clazz null");
        return;
    }

    //2. 获取静态变量属性ID和方法ID
    fid = env->GetStaticFieldID(clazz, "STATIC_FIELD", "I");
    if (fid == NULL) {
        LOGD("field id null");
        return;
    }

    mid = env->GetStaticMethodID(clazz, "getStaticMethod",
                                 "(Ljava/lang/String;ILjava/lang/String;D)Ljava/lang/String;");
    if (mid == NULL) {
        LOGD("methond null");
        return;
    }

    //3. 获取静态变量值和调用静态方法
    jint num = env->GetStaticIntField(clazz, fid);//静态属性
    LOGI("静态变量的值: num = %d", num);

    j_result = (jstring) env->CallStaticObjectMethod(clazz, mid, name, age, address, salary);//静态方法
    const char *buf_result = env->GetStringUTFChars(j_result, JNI_FALSE);
    LOGI("静态方法的返回值: %s", buf_result);

    //释放内存
    env->ReleaseStringUTFChars(j_result, buf_result);

    //4. 修改静态变量值
    env->SetStaticIntField(clazz, fid, 2048);

    //5. 释放局部引用
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(j_result);

}

/**
 * C++获取Java对象Person
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_speex_ndkcmake_JNIUtils_invokeJavaObject(JNIEnv *env, jobject object, jstring name_,
                                                  jint age) {

    //1. 获取Person类的Class引用
    jclass clazz = env->FindClass("com/speex/ndkcmake/bean/Person");
    if (clazz == NULL) {
        LOGE("clazz null");
        return NULL;
    }

    //2. 获取类的默认构造函数ID
    jmethodID mid_construct = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;I)V");
    if (mid_construct == NULL) {
        LOGE("construct null");
        return NULL;
    }

    //3. 获取实例方法ID和变量ID
    jfieldID fid_name = env->GetFieldID(clazz, "name", "Ljava/lang/String;");
    jfieldID fid_age = env->GetFieldID(clazz, "age", "I");
    jmethodID mid_to_string = env->GetMethodID(clazz, "toString", "()Ljava/lang/String;");

    //4. 创建该类Person的实例
    jobject jobj = env->NewObject(clazz, mid_construct, name_, age);

    if (jobj == NULL) {
        LOGE("jobject null");
        return NULL;
    }

    //5.修改age/name变量的值
    env->SetIntField(jobj, fid_age, age);//修改age变量的值

    jstring j_new_str = env->NewStringUTF("小红");
    env->SetObjectField(jobj, fid_name, j_new_str);//修改name属性

    //6.调用实例方法toString()
    jstring j_result = (jstring) env->CallObjectMethod(jobj, mid_to_string);
    const char *buf_result = env->GetStringUTFChars(j_result, JNI_FALSE);//结果
    LOGI("Person toString = %s", buf_result);

    //7.释放内存
    env->ReleaseStringUTFChars(j_result, buf_result);

    //8. 释放局部引用
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(jobj);
    env->DeleteLocalRef(j_new_str);
    env->DeleteLocalRef(j_result);

    return env->NewStringUTF(buf_result);
}

/**
 * 获取C++返回的Person数组
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_speex_ndkcmake_JNIUtils_getPersonArrayForJNI(JNIEnv *env, jobject instance) {
    jclass clazz = NULL;
    jobject jobj = NULL;
    jmethodID mid_construct = NULL;
    jfieldID fid_age = NULL;
    jfieldID fid_name = NULL;
    jmethodID mid_to_string = NULL;
    jstring j_name;

    //1. 获取Person类的Class引用
    clazz = env->FindClass("com/speex/ndkcmake/bean/Person");
    if (clazz == NULL) {
        LOGE("clazz null");
        return NULL;
    }

    //2. 获取类的Person(name,age)构造函数ID
    mid_construct = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;I)V");
    if (mid_construct == NULL) {
        LOGE("construct null");
        return NULL;
    }

    //3.获取实例方法toString()和变量name,age的ID
    fid_name = env->GetFieldID(clazz, "name", "Ljava/lang/String;");
    fid_age = env->GetFieldID(clazz, "age", "I");
    mid_to_string = env->GetMethodID(clazz, "toString", "()Ljava/lang/String;");

    if (fid_name == NULL || fid_age == NULL) {
        LOGE("fid_name | fid_age 为null");
        return NULL;
    }

    //4. 处理单个对象并添加到数组
    int size = 10;
    jobjectArray obj_array = env->NewObjectArray(size, clazz, 0);//保存Person对象的数组
    for (int i = 0; i < size; i++) {
        std::string name = "香香";//string 字符串 转换为 jstring字符串
        jint age = 24 + i;
        jobj = env->NewObject(clazz, mid_construct, env->NewStringUTF(name.c_str()),
                              age);//创建Person对象
        if (jobj == NULL) {
            LOGE("jobj null");
            return NULL;
        }
        jstring tostring = (jstring) env->CallObjectMethod(jobj, mid_to_string);
        const char *buf_result = env->GetStringUTFChars(tostring, JNI_FALSE);
        LOGI("%d ,%s", i, buf_result);

        //修改属性
        env->SetIntField(jobj, fid_age, 23 + i);//设置年龄
        j_name = env->NewStringUTF("大梅");
        env->SetObjectField(jobj, fid_name, j_name);//设置姓名
        env->SetObjectArrayElement(obj_array, i, jobj);//设置数组元素
    }
//    std::string name = "香香";//string 字符串 转换为 jstring字符串
//    jobj = env->NewObject(clazz, mid_construct, env->NewStringUTF(name.c_str()), 24);
//    jstring tostring = (jstring) env->CallObjectMethod(jobj, mid_to_string);
//    const char *buf_result = env->GetStringUTFChars(tostring, JNI_FALSE);
//    LOGI("%s", buf_result);

    //5. 释放局部变量
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(jobj);
    return obj_array;
}

/**
 * C++调用java父类构造方法和实例方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_speex_ndkcmake_JNIUtils_callSuperInstanceMethod(JNIEnv *env, jobject instance) {

    //1. 获取Dog类Class引用
    jclass cls_dog = env->FindClass("com/speex/ndkcmake/bean/Dog");
    if (cls_dog == NULL) {
        LOGI("获取Dog类的class引用为空");
        return;
    }

    //2. 获取Dog类构造方法ID -->> Dog(name)含有参数的构造
    jmethodID mid_dog_init = env->GetMethodID(cls_dog, "<init>", "(Ljava/lang/String;)V");
    if (mid_dog_init == NULL) {
        LOGI("Dog类对象构造方法ID为 null");
        return;
    }

    //3. 创建Dog对象实例
    jstring c_str_name = env->NewStringUTF("大黄");
    jobject jobj_dog = env->NewObject(cls_dog, mid_dog_init, c_str_name);
    if (jobj_dog == NULL) {
        LOGI("创建dog对象为空");
        return;
    }

    //4. 获取animal类Class引用
    jclass cls_animal = env->FindClass("com/speex/ndkcmake/bean/Animal");
    if (cls_animal == NULL) {
        LOGI("获取Animal类的class引用为null");
        return;
    }

    //5. 获取Animal父类run方法ID并调用
    jmethodID mid_run = env->GetMethodID(cls_animal, "run", "()V");
    if (mid_run == NULL) {
        LOGI("获取Animal父类run方法ID为null");
        return;
    }
    //子类对象dog调用父类的run方法(执行的是父类的run方法)
    env->CallNonvirtualVoidMethod(jobj_dog, cls_animal, mid_run);

    //6. 调用父类getName方法
    //获取父类的getName方法的ID
    jmethodID mid_get_name = env->GetMethodID(cls_animal, "getName", "()Ljava/lang/String;");
    if (mid_get_name == NULL) {
        LOGI("父类的getName方法的ID为null");
        return;
    }

    //子类对象调用父类的getName方法
    jstring ani_name = (jstring) env->CallNonvirtualObjectMethod(jobj_dog, cls_animal,
                                                                 mid_get_name);
    const char *name = env->GetStringUTFChars(ani_name, JNI_FALSE);
    LOGI("Animal名字是 %s", name);

    //7. 释放从java层获取到的字符串所分配的内存
    env->ReleaseStringUTFChars(ani_name, name);

    //8. 释放局部变量
    env->DeleteLocalRef(cls_animal);
    env->DeleteLocalRef(cls_dog);
    env->DeleteLocalRef(jobj_dog);
    env->DeleteLocalRef(c_str_name);
}

