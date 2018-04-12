package com.speex.ndkcmake.bean;

import android.util.Log;

/**
 * Created by Byron on 2018/4/12.
 */

public class Animal {
    protected static String TAG = "Animal";
    protected String name;

    public Animal(String name) {
        this.name = name;
        Log.i(TAG, "Animal()构造call ...");
    }

    public Animal() {
    }

    public String getName() {
        Log.i(TAG, "Animal getName call ..." + this.name);
        return "这是Animal类的 " + this.name;
    }

    public void run() {
        Log.i(TAG, "Aninam run调用了 ...");
    }
}
