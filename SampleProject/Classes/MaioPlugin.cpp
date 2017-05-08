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

// extern "C" {
//     JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onInitialized(JNIEnv *, jclass, jstring);
// }

// callback from Java
JNIEXPORT void Java_jp_maio_sdk_plugin_cocos_android_MaioPlugin_onInitialized(JNIEnv *env, jobject thiz) {
    if(_listener != nullptr) {
        _listener->onInitialized();
    }
}

// MaioPlugin methods
void maio::MaioPlugin::start( const char *mediaId, maio::MaioListener *listener ) {

    if(_listener != nullptr) {
        delete _listener;
        // &_listener = 0;
    }
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
        // methodInfo.env->DeleteLocalRef(jResult);
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
    // TODO: 本当は以下のようにダイレクトでconst char*を取ってこれたらいいなあ。
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
