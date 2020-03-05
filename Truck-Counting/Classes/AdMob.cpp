#include "AdMob.h"

#define CLASS_NAME "com/nazoroot/jni/AdMob"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

void AdMob::showInterstitial() {
    JniMethodInfo method;
    JniHelper::getStaticMethodInfo(method, CLASS_NAME, "showInterstitial", "()V");
    method.env->CallStaticVoidMethod(method.classID, method.methodID);
    method.env->DeleteLocalRef(method.classID);
}

#endif
