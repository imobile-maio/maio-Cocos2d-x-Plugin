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

// MaioPlugin methods
void maio::MaioPlugin::start( const char *mediaId, maio::MaioListener *listener ) {
    
}

bool maio::MaioPlugin::canShow() {
    
}

bool maio::MaioPlugin::canShow( const char *zoneId ) {
}

void maio::MaioPlugin::show() {
}

void maio::MaioPlugin::show( const char *zoneId ) {
}

void maio::MaioPlugin::setAdTestMode(bool setAdTestMode){
}

char const* maio::MaioPlugin::getSdkVersion(){
    std::string ret;

    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, MAIO_CLASS, "getSdkVersion", "()Ljava/lang/String;")) 
    {
        jobject objResult = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        ret = cocos2d::JniHelper::jstring2string((jstring)objResult);
        methodInfo.env->DeleteLocalRef(objResult);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    return ret.c_str();
}

void maio::MaioPlugin::setListener(maio::MaioListener *listener){
}

void maio::MaioPlugin::removeListener() {
}
