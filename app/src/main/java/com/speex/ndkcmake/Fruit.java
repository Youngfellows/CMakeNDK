package com.speex.ndkcmake;

import android.util.Log;

/**
 * Created by Byron on 2018/4/6.
 * 水果的父类
 */

public class Fruit {
    private final String TAG = this.getClass().getSimpleName();

    public Fruit() {
        Log.i(TAG, "Fruit()构造");
    }

    protected double price() {
        Log.i(TAG, "Fruit父类的price()方法");
        return 3.14159;
    }
}
