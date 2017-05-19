//
//  SampleMaioListener.cpp
//  Sample
//
//  Created by maio on 2016/08/29.
//
//

#include "cocos2d.h"
#include "SampleMaioListener.hpp"
#include <iostream>

using maio::MaioPlugin;
using maio::MaioListener;
using maio::FailReason;
using std::cout;
using std::endl;

USING_NS_CC;

void SampleMaioListener::onInitialized(){
    // 広告表示準備完了時の処理
    log("初期化が完了しました");
};
void SampleMaioListener::onChangedCanShow( const char *zoneId, const bool newValue ) {
    // 広告の配信可能状態が変更された際の処理
    log("配信可能状態が変更されました zoneId:%s, newValue:%d", zoneId, (int)newValue);
};
void SampleMaioListener::onStartAd( const char *zoneId ) {
    // 広告が再生開始された際の処理
    log("再生開始しました: %s", zoneId);
};
void SampleMaioListener::onFinishedAd( const char *zoneId, const int playtime, const bool skipped, const char *rewardParam ){
    // 広告の再生が完了した際の処理
    log("再生終了しました Playtime: %dsec Skipped:%d ", playtime, skipped);
};
void SampleMaioListener::onClickedAd( const char *zoneId ){
    // 広告がクリックされた際の処理
    log("ストア遷移しました: %s", zoneId);
};
void SampleMaioListener::onClosedAd( const char *zoneId ){
    // エンドカードが閉じられた際の処理
    log("エンドカードが閉じられました: %s", zoneId);
};
void SampleMaioListener::onFailed( const char *zoneId, const maio::FailReason reason ){
    // エラーが発生した際の処理
    log("エラーが発生しました. ZoneId: %s FailReason: %d", zoneId, (int)reason);
};
