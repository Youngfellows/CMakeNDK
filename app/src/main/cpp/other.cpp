
#include <jni.h>
#include <android/log.h>
#define TAG "TAG_OTHER"

extern "C"
JNIEXPORT void JNICALL
Java_com_speex_ndkcmake_JNIUtils_otherCPP(JNIEnv *env, jobject instance) {

    __android_log_print(ANDROID_LOG_INFO, TAG, "ASFSAFSAF");

}