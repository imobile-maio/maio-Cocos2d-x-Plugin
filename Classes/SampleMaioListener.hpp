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
    void onChangedCanShow(const std::string &zoneId, const bool newValue);
    void onStartAd(const std::string &zoneId);
    void onFinishedAd(const std::string &zoneId, const int playtime, const bool skipped, const std::string &rewardParam);
    void onClickedAd(const std::string &zoneId);
    void onClosedAd(const std::string &zoneId);
    void onFailed(const std::string &zoneId, const maio::FailReason reason);
};

#endif /* SampleMaioListener_hpp */