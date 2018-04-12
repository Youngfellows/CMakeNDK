package com.speex.ndkcmake.bean;

import android.util.Log;

/**
 * Created by Byron on 2018/4/12.
 */

public class Dog extends Animal {

    public Dog() {
        super();
    }

    public Dog(String name) {
        super(name);
        Log.i(TAG, "Dog 构造调用了");
    }

    @Override
    public String getName() {
        Log.i(TAG, "Dog getName call ..." + this.name);
        return "这是Dog类的" + this.name;
    }

    @Override
    public void run() {
        Log.i(TAG, "Dog run调用了..");
    }
}
