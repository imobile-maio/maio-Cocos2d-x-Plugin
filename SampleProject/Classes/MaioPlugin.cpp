//
//  MaioPlugin.cpp
//  Sample
//
//  Created by maio on 2017/05/01.
//
//

#include "cocos2d.h"

#include "MaioPlugin.h"
#include "jni.h"
#include "platform/android/jni/JniHelper.h"

#define MAIO_CLASS "jp/maio/sdk/plugin/cocos/android/MaioPlugin"

USING_NS_CC;

static maio::MaioListener *_listener;

extern "C" {
    JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onInitialized(JNIEnv *, jobject);
    JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onChangedCanShow(JNIEnv *, jobject, jstring, jboolean);
    JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onStartAd(JNIEnv *, jobject, jstring);
    JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onFinishedAd(JNIEnv *, jobject, jstring, jint, jboolean, jstring);
    JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onClickedAd(JNIEnv *, jobject, jstring);
    JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onClosedAd(JNIEnv *, jobject, jstring);
    JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onFailed(JNIEnv *, jobject, jstring, jint);
}

// callback from Java
JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onInitialized(JNIEnv *env, jobject thiz) {
    if(_listener) {
        _listener->onInitialized();
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onChangedCanShow(JNIEnv *env, jobject thiz, jstring jzoneId, jboolean newValue){
    if(_listener) {
        const char* zoneId = env->GetStringUTFChars(jzoneId, 0);
        _listener->onChangedCanShow(zoneId, (bool)newValue);
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onStartAd(JNIEnv *env, jobject thiz, jstring jzoneId) {
    if(_listener) {
        const char* zoneId = env->GetStringUTFChars(jzoneId, 0);
        _listener->onStartAd(zoneId);
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onFinishedAd(JNIEnv *env, jobject thiz, jstring jzoneId, jint jplaytime, jboolean jskipped, jstring jrewardParam) {
    if(_listener) {
        const char* zoneId = env->GetStringUTFChars(jzoneId, 0);
        const char* rewardParam = env->GetStringUTFChars(jrewardParam, 0);
        _listener->onFinishedAd(zoneId, (int) jplaytime, (bool)jskipped, rewardParam);
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onClickedAd(JNIEnv *env, jobject thiz, jstring jzoneId) {
    if(_listener) {
        const char* zoneId = env->GetStringUTFChars(jzoneId, 0);
        _listener->onClickedAd(zoneId);
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onClosedAd(JNIEnv *env, jobject thiz, jstring jzoneId) {
    if(_listener) {
        const char* zoneId = env->GetStringUTFChars(jzoneId, 0);
        _listener->onClosedAd(zoneId);
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onFailed(JNIEnv *env, jobject thiz, jstring jzoneId, jint jfailReason) {
    if(_listener) {
        const char* zoneId = env->GetStringUTFChars(jzoneId, 0);
        maio::FailReason failReason;
        switch ((int)jfailReason) {
            case 1: failReason = maio::FailReason::AdStockOut; break;
            case 2: failReason = maio::FailReason::Response; break;
            case 3: failReason = maio::FailReason::NetworkConnection; break;
            case 4: failReason = maio::FailReason::NetworkServer; break;
            case 5: failReason = maio::FailReason::VideoPlayback; break;
            
            case 0: 
            default: 
                failReason = maio::FailReason::Unknown; break;
        }

        _listener->onFailed(zoneId, failReason);
    }
}

// MaioPlugin methods
void maio::MaioPlugin::start( const char *mediaId, maio::MaioListener *listener ) {
    _listener = listener;

    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "start", "(Ljava/lang/String;)V")) 
    {
        jstring jstringMediaId = methodInfo.env->NewStringUTF(mediaId);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jstringMediaId);

        methodInfo.env->DeleteLocalRef(jstringMediaId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
}

bool maio::MaioPlugin::canShow() {
    
    bool result = false;

    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "canShow", "()Z")) 
    {
        jboolean jResult = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        
        result = (bool)jResult;

        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return result;
}

bool maio::MaioPlugin::canShow( const char *zoneId ) {

    bool result = false;

    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "canShow", "(Ljava/lang/String;)Z")) 
    {
        jstring jstringZoneId = methodInfo.env->NewStringUTF(zoneId);
        jboolean jResult = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jstringZoneId);
        
        result = (bool)jResult;

        methodInfo.env->DeleteLocalRef(jstringZoneId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return result;
}

void maio::MaioPlugin::show() {
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "show", "()V")) 
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void maio::MaioPlugin::show( const char *zoneId ) {
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "show", "(Ljava/lang/String;)V")) 
    {
        jstring jstringZoneId = methodInfo.env->NewStringUTF(zoneId);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jstringZoneId);

        methodInfo.env->DeleteLocalRef(jstringZoneId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void maio::MaioPlugin::setAdTestMode(bool setAdTestMode){
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "setAdTestMode", "(Z)V")) 
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, setAdTestMode);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

char const* maio::MaioPlugin::getSdkVersion(){
    const char* sdkVersion;

    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "getSdkVersion", "()Ljava/lang/String;")) 
    {
        jobject result = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        sdkVersion = methodInfo.env->GetStringUTFChars((jstring)result, 0);
        methodInfo.env->DeleteLocalRef(result);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return sdkVersion;
}

void maio::MaioPlugin::setListener(maio::MaioListener *listener){
    _listener = listener;
}

void maio::MaioPlugin::removeListener() {
    _listener = NULL;
}
