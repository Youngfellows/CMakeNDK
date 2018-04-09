package com.speex.ndkcmake.utils;

import android.util.Log;

/**
 * Created by Byron on 2018/4/9.
 */

public class SpeexUtils {
    public static String TAG = "SpeexUtils";

    public static int STATIC_FIELD = 128;//java中的静态变量

    /**
     * java的静态方法
     *
     * @param name
     * @param age
     * @param address
     * @param salary
     * @return
     */
    public static String getStaticMethod(String name, int age, String address, double salary) {
        String info = name + " ," + age + "岁," + address + "人,每月工资" + salary + "美元";
        Log.i(TAG, info);
        return info;
    }

}
