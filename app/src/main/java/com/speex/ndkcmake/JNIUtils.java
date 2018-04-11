package com.speex.ndkcmake;

import com.speex.ndkcmake.bean.Person;

import java.util.Random;
import java.util.UUID;

/**
 * Created by Byron on 2018/4/1.
 */

public class JNIUtils {
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("other-lib");
    }

    //父类的引用指向一个子类的对象
    public Fruit mFruit = new Apple();

    public String key = "aispeex";//java public属性

    public static int count = 97;//java static属性

    // 产生一个随机数
    public int genRandomInt(int max) {
        return new Random().nextInt(max);
    }

    // 产生一个UUID字符串
    public static String getUUID() {
        return UUID.randomUUID().toString();
    }

    public native int stringLength(String string);//获取字符串的长度

    public native String stringForJNI(String address);//获取JNI返回的String

    public native String stringFor2JNI(String address);//获取JNI返回的String

    public native String accessJavaField();// C->Java，访问Java属性，返回修改之后的属性内容

    public native void accessJavaStaticField();//C->Java，访问Java静态属性

    public native int accessJavaMethod();//C++访问Java中的public方法

    public native String accessJavaStaticMethod();// C++ ->Java，访问Java静态方法

    public native double accessJavaFatherMethod();//C++ ->Java，访问Java父类对象的方法

    public native String getChineseFromJava(String java_str);//C++ ->Java,解决C++获取java中文乱码问题

    public native String getChineseFromCPP();//Java -> C++，C/C++传递中文到Java乱码

    public native int[] getByteArrayFromC();// C++ -> Java，返回一个int[]数组给Java

    public native double[] getSortedArray(double[] origin);//C++->Java，C/C++对传入的数组进行排序后返回

    public native String[] stringArrayForCPP(int size);//获取JNI返回的String[]数组

    /**
     * other-lib.so相关
     */
    public native double doubleForJNI(double salary, double bonus);//获取JNI返回的double

    public native String stringsForJNI(String str);//获取JNI返回的string

    public native boolean booleanForJNI();//获取JNI返回的boolean

    public native int intForJNI(int apple, int orange);//获取JNI返回的int

    public native String[] stringArrayForJNI(String key);//获取JNI返回的ArrayList

    public native byte[] getByteArray(byte[] data);//获取字节数组

    public native void invokeStaticFieldAndMethod(String name, int age, String address, double salary);//C++调用Java静态方法和静态变量

    public native String invokeJavaObject(String name, int age);//C++调用Java对象

    public native Person[] getPersonArrayForJNI();//获取C++返回的Person[]素组

}
