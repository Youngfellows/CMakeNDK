package com.speex.ndkcmake;

import android.util.Log;

/**
 * Created by Byron on 2018/4/6.
 */

public class Apple extends Fruit {
    private String TAG = this.getClass().getSimpleName();

    public Apple() {
        Log.i(TAG, "Apple()构造");
    }

    @Override
    protected double price() {
        Log.i(TAG, "Apple孩子的price()方法");
        return 888.78;
    }
}
