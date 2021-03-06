package com.speex.ndkcmake;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.speex.ndkcmake.bean.Animal;
import com.speex.ndkcmake.bean.Dog;
import com.speex.ndkcmake.bean.Person;
import com.speex.ndkcmake.utils.SpeexUtils;

public class MainActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getSimpleName();
    private JNIUtils mJNIUtils;
    private TextView mTvShow;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTvShow = findViewById(R.id.tv_show);//显示调用结果
        mJNIUtils = new JNIUtils();
    }

    /**
     * JNI获取重C++返回的字符串
     *
     * @param view
     */
    public void stringForJNI(View view) {
        String stringForJNI = mJNIUtils.stringForJNI("深圳市南山区软件产业基地");
        mTvShow.setText(stringForJNI);
    }

    /**
     * C++ jstring字符串拼接
     *
     * @param view
     */
    public void stringFor2JNI(View view) {
        String stringFor2JNI = mJNIUtils.stringFor2JNI("妹妹，哥哥想你了");
        mTvShow.setText(stringFor2JNI);
    }

    /**
     * C->Java，访问Java属性，返回修改之后的属性内容
     *
     * @param view
     */
    public void onAccessJavaFieldClick(View view) {
        Log.i(TAG, "修改前: key = " + mJNIUtils.key);
        StringBuilder builder = new StringBuilder();
        builder.append("修改前: key = " + mJNIUtils.key);
        builder.append("\n");
        mTvShow.setText(builder.toString());
        mJNIUtils.accessJavaField();//C++修改Java字段
        builder.append("修改后: key = " + mJNIUtils.key + "\n");
        Log.i(TAG, "修改后: key = " + mJNIUtils.key);
        mTvShow.setText(builder.toString());
    }

    /**
     * C++ 访问java中的static静态属性
     *
     * @param view
     */
    public void onAccessJavaStaticFieldClick(View view) {
        StringBuilder builder = new StringBuilder();
        builder.append("修改前: count = " + JNIUtils.count + "\n");
        //mTvShow.setText("修改前: count = " + JNIUtils.count);
        mJNIUtils.accessJavaStaticField();//修改java的静态值
        builder.append("修改后: count = " + JNIUtils.count + "\n");
        mTvShow.setText(builder.toString());
    }

    /**
     * C++访问java中的public方法
     */
    public void onAccessJavaMethodClick(View view) {
        //C++调用Java的public方法
        int random = mJNIUtils.accessJavaMethod();
        mTvShow.setText("C++调用java 层public方法: random = " + random);
    }

    /**
     * C++访问Java中的静态方法
     *
     * @param view
     */
    public void onAccessJavaStaticMethodClick(View view) {
        String uuid = mJNIUtils.accessJavaStaticMethod();
        mTvShow.setText("C++调用Java静态方法: uuid = " + uuid);
    }

    /**
     * C++访问Java中对象父类的方法
     *
     * @param view
     */
    public void onAccessJavaFatherMethodClick(View view) {
        StringBuilder builder = new StringBuilder();
        Log.i(TAG, "在Java中调用父类的price()方法,子类的具体实现");
        Fruit fruit = mJNIUtils.mFruit;
        double price_zi = fruit.price();
        builder.append("在Java中调用父类的price()方法,子类的具体实现: price_zi = " + price_zi + "\n");

        Log.i(TAG, "C++调用Fruit父类的price()方法");
        double price_fu = mJNIUtils.accessJavaFatherMethod();
        builder.append("在C++中调用父类的price()方法,父类的实现: price_fu = " + price_fu + "\n");
        mTvShow.setText(builder.toString());
    }

    /**
     * C++ ->Java,解决C++获取java中文乱码问题
     *
     * @param view
     */
    public void onGetChineseFromC1Click(View view) {
        String c_string = mJNIUtils.getChineseFromJava("广东省深圳市南山区");
        mTvShow.setText(c_string);
    }

    /**
     * 解决C++传递中文到java中文乱码问题
     *
     * @param view
     */
    public void onGetChineseFromC2Click(View view) {
        String chineseFromCPP = mJNIUtils.getChineseFromCPP();
        Log.i(TAG, "C++传递过来的中文: " + chineseFromCPP);
        mTvShow.setText(chineseFromCPP);
    }


    /**
     * C++返回一个int[]数组给java
     *
     * @param view
     */
    public void onGetByteArrayFromCClick(View view) {
        int[] array_int = mJNIUtils.getByteArrayFromC();
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < array_int.length; i++) {
            builder.append(String.valueOf(array_int[i]));
            if (i != array_int.length - 1) {
                builder.append(",");
            }
        }
        mTvShow.setText(builder.toString());
        Log.i(TAG, "C++传递出来的int[]: " + builder.toString());
    }

    /**
     * C++对java传入的double[]排序后输出
     *
     * @param view
     */
    public void onGetSortedArrayClick(View view) {
        double[] origin = {13.34, 3.898, 7.77, 4.93, 6.43, 32.23, 44.79, 23.67};
        double[] sort = mJNIUtils.getSortedArray(origin);
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < sort.length; i++) {
            Log.i(TAG, sort[i] + " ");
            builder.append(String.valueOf(sort[i]));
            if (i != sort.length - 1) {
                builder.append(",");
            }
        }
        Log.i(TAG, "排序后: " + builder.toString());
        mTvShow.setText("排序后: " + builder.toString());
    }

    /**
     * C++返回string[]数组
     *
     * @param view
     */
    public void onGetStringArrayClick(View view) {
        StringBuilder builder = new StringBuilder();
        String[] strings = mJNIUtils.stringArrayForCPP(10);
        for (int i = 0; i < strings.length; i++) {
            Log.i(TAG, strings[i] + "\n");
            builder.append(strings[i] + "\n");
        }
        mTvShow.setText(builder.toString());
        Log.i(TAG, "C++返回的String[]: " + strings.toString());
    }

    /**
     * C++返回double
     *
     * @param view
     */
    public void onGetDoubleClick(View view) {
        double result = mJNIUtils.doubleForJNI(1024.4, 32.4);
        mTvShow.setText(result + "");
        Log.i(TAG, "onGetDoubleClick: result = " + result);
    }

    /**
     * C++返回的String
     *
     * @param view
     */
    public void onGetStringClick(View view) {
        String serio = mJNIUtils.stringsForJNI("ro.serialno");
        mTvShow.setText("设备序列号serio: " + serio);
        Log.i(TAG, "设备序列号serio: " + serio);
    }

    /**
     * 获取C++返回的byte[]数组
     *
     * @param view
     */
    public void onGetByteArrayClick(View view) {
        StringBuilder builder = new StringBuilder();
        byte array[] = {'A', 'B', 'C', 'D', 'E', 'a'};
        byte[] resutl = mJNIUtils.getByteArray(array);
        for (int i = 0; i < array.length; i++) {
            Log.d(TAG, "ARRAY : " + array[i] + "->" + resutl[i]);
            builder.append(resutl[i] + " ");
        }
        mTvShow.setText(builder.toString());
    }

    /**
     * C++获取java类的静态属性和静态方法
     *
     * @param view
     */
    public void onGetStaticFieldAndMethodClick(View view) {
        Log.i(TAG, "Speex.STATIC_FIELD前: " + SpeexUtils.STATIC_FIELD);
        mJNIUtils.invokeStaticFieldAndMethod("aispeex", 34, "广东深圳", 12804);
        Log.i(TAG, "Speex.STATIC_FIELD后: " + SpeexUtils.STATIC_FIELD);

    }

    /**
     * C++获取Java对象
     *
     * @param view
     */
    public void invokeJavaObject(View view) {
        String j_string = mJNIUtils.invokeJavaObject("丽丽", 24);
        Toast.makeText(this, j_string, Toast.LENGTH_SHORT).show();
        mTvShow.setText(j_string);
    }

    /**
     * C++返回Person对象数组给Java
     *
     * @param view
     */
    public void invokePersonArray(View view) {
        StringBuilder builder = new StringBuilder();
        Person[] persns = mJNIUtils.getPersonArrayForJNI();

        if (persns != null) {
            if (persns.length > 0) {
                for (Person person : persns) {
                    person.toString();
                    builder.append(person.toString() + "\n");
                }
            }
        }
        mTvShow.setText(builder.toString());
    }

    /**
     * C++调用Java对象父类对象和方法
     *
     * @param view
     */
    public void callSuperMethod(View view) {
//        Animal animal = new Dog("小狗狗");
//        String name = animal.getName();
//        animal.run();
//        Log.i(TAG, "name = " + name);

        //C++调用java父类
        mJNIUtils.callSuperInstanceMethod();
    }
}
