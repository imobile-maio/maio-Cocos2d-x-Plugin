//
//  SampleMaioListener.hpp
//  Sample
//
//  Created by maio on 2016/08/29.
//
//

#ifndef SampleMaioListener_hpp
#define SampleMaioListener_hpp

#include <stdio.h>
#include "MaioPlugin.h"

class SampleMaioListener : public maio::MaioListener {
private:
    // イベントが起きた際に呼び出されるメソッドを宣言します。使用しないメソッドは宣言する必要はありません。
    void onInitialized();
    void onChangedCanShow( const char *zoneId, const bool newValue );
    void onStartAd( const char *zoneId );
    void onFinishedAd( const char *zoneId, const int playtime, const bool skipped, const char *rewardParam );
    void onClickedAd( const char *zoneId );
    void onClosedAd( const char *zoneId );
    void onFailed( const char *zoneId, const maio::FailReason reason );
    ~SampleMaioListener(){};
};

#endif /* SampleMaioListener_hpp */