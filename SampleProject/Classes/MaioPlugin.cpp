//
//  MaioPlugin.cpp
//  Sample
//
//  Created by maio on 2017/05/01.
//
//

#include "MaioPlugin.h"
#include "jni.h"
#include "platform/android/jni/JniHelper.h"

#define MAIO_CLASS "jp/maio/sdk/plugin/cocos/android/MaioPlugin"

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
    if(_listener != nullptr) {
        _listener->onInitialized();
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onChangedCanShow(JNIEnv *env, jobject thiz, jstring jzoneId, jboolean newValue){
    if(_listener != nullptr) {
        std::string zoneId = cocos2d::JniHelper::jstring2string(jzoneId); // jstringをstd::stringに変換
        _listener->onChangedCanShow(zoneId.c_str(), (bool)newValue);
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onStartAd(JNIEnv *env, jobject thiz, jstring jzoneId) {
    if(_listener != nullptr) {
        std::string zoneId = cocos2d::JniHelper::jstring2string(jzoneId); // jstringをstd::stringに変換
        _listener->onStartAd(zoneId.c_str());
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onFinishedAd(JNIEnv *env, jobject thiz, jstring jzoneId, jint jplaytime, jboolean jskipped, jstring jrewardParam) {
    if(_listener != nullptr) {
        std::string zoneId = cocos2d::JniHelper::jstring2string(jzoneId); // jstringをstd::stringに変換
        std::string rewardParam = cocos2d::JniHelper::jstring2string(jrewardParam); // jstringをstd::stringに変換
        _listener->onFinishedAd(zoneId.c_str(), (int) jplaytime, (bool)jskipped, rewardParam.c_str());
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onClickedAd(JNIEnv *env, jobject thiz, jstring jzoneId) {
    if(_listener != nullptr) {
        std::string zoneId = cocos2d::JniHelper::jstring2string(jzoneId); // jstringをstd::stringに変換
        _listener->onClickedAd(zoneId.c_str());
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onClosedAd(JNIEnv *env, jobject thiz, jstring jzoneId) {
    if(_listener != nullptr) {
        std::string zoneId = cocos2d::JniHelper::jstring2string(jzoneId); // jstringをstd::stringに変換
        _listener->onClosedAd(zoneId.c_str());
    }
}

JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onFailed(JNIEnv *env, jobject thiz, jstring jzoneId, jint jfailReason) {
    if(_listener != nullptr) {
        std::string zoneId = cocos2d::JniHelper::jstring2string(jzoneId); // jstringをstd::stringに変換
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

        _listener->onFailed(zoneId.c_str(), failReason);
    }
}


// MaioPlugin methods
void maio::MaioPlugin::start( const char *mediaId, maio::MaioListener *listener ) {

    if(_listener != nullptr) {
        delete _listener;
        // &_listener = 0;
    }

    if(listener == nullptr) {
        _listener = new maio::MaioListener();
    } else {
        _listener = listener;
    }
    
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

        // TODO: これなくていいのか確認。booleanはプリミティブだから解放しなくていいかもしれんが
        // MEMO: 実際はCppからJavaに戻ったときに解放されるらしいが、ローカルに持ちすぎるとVMを使い切ってしまう恐れがあるらしい。
        // methodInfo.env->DeleteLocalRef(jResult);
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
    std::string sdkVersion;

    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "getSdkVersion", "()Ljava/lang/String;")) 
    {
        jobject result = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        sdkVersion = cocos2d::JniHelper::jstring2string((jstring)result); // jstringをstd::stringに変換
        methodInfo.env->DeleteLocalRef(result);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    // TODO: 本当は以下のようにダイレクトでconst char*を取ってこれたらいいなあ。(下記は動かない)
        // jobject objResult = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        // sdkVersion = methodInfo.env->GetStringUTFChars(methodInfo.env, (jstring)objResult, 0);
        // methodInfo.env->DeleteLocalRef(objResult);
        // methodInfo.env->DeleteLocalRef(methodInfo.classID);

    return sdkVersion.c_str();
}

void maio::MaioPlugin::setListener(maio::MaioListener *listener){
    if(_listener != nullptr) {
        delete _listener;
        // &_listener = 0;
    }
    _listener = listener;
}

void maio::MaioPlugin::removeListener() {
    delete _listener;
    // &_listener = 0;
}
