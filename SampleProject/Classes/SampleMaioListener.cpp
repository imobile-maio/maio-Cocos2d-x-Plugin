//
//  SampleMaioListener.cpp
//  Sample
//
//  Created by maio on 2016/08/29.
//
//

#include "SampleMaioListener.hpp"
#include <iostream>

using maio::MaioPlugin;
using maio::MaioListener;
using maio::FailReason;
using std::cout;
using std::endl;

void SampleMaioListener::onInitialized(){
    // 広告表示準備完了時の処理
    cout << "初期化が完了しました" << endl;
};
void SampleMaioListener::onChangedCanShow( const char *zoneId, const bool newValue ) {
    // 広告の配信可能状態が変更された際の処理
    cout << "配信可能状態が変更されました" << endl;
};
void SampleMaioListener::onStartAd( const char *zoneId ) {
    // 広告が再生開始された際の処理
    cout << "再生開始しました" << endl;
};
void SampleMaioListener::onFinishedAd( const char *zoneId, const int playtime, const bool skipped, const char *rewardParam ){
    // 広告の再生が完了した際の処理
    cout << "再生終了しました Playtime: " << playtime << "sec Skipped: " << skipped << endl;
};
void SampleMaioListener::onClickedAd( const char *zoneId ){
    // 広告がクリックされた際の処理
    cout << "ストア遷移しました" << endl;
};
void SampleMaioListener::onClosedAd( const char *zoneId ){
    // エンドカードが閉じられた際の処理
    cout <<"エンドカードが閉じられました" << endl;
};
void SampleMaioListener::onFailed( const char *zoneId, const FailReason reason ){
    // エラーが発生した際の処理
    cout << "エラーが発生しました FailReason: " << (int)reason << endl;
};