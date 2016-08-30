//
//  MaioPlugin.mm
//
//  Created by maio on 2016/08/04.
//
//

#import "MaioPlugin.h"
#import "Maio/Maio.h"

// objective-cからc++へ、デリゲートメソッドの橋渡しを行うクラス

@interface MaioDelegateBridge : NSObject<MaioDelegate>

@property maio::MaioListener *listener;
+ (MaioDelegateBridge *) sharedInstance;

@end

@implementation MaioDelegateBridge

+ (MaioDelegateBridge *)sharedInstance {
    static MaioDelegateBridge *_sharedInstance = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedInstance = [[self alloc] init];
    });
    return _sharedInstance;
}
- (void) maioDidInitialize {
    if([self isListenerExist]) {
        self.listener->onInitialized();
    }
}
- (void) maioDidChangeCanShow:(NSString *)zoneId newValue:(BOOL)newValue {
    if([self isListenerExist]){
        self.listener->onChangedCanShow([zoneId UTF8String], (bool) newValue);
    }
}
- (void) maioWillStartAd:(NSString *)zoneId {
    if([self isListenerExist]){
        self.listener->onStartAd([zoneId UTF8String]);
    }
}
- (void) maioDidFinishAd:(NSString *)zoneId playtime:(NSInteger)playtime skipped:(BOOL)skipped rewardParam:(NSString *)rewardParam {
    if([self isListenerExist]){
        std::string _rewardParam = std::string();
        if(rewardParam){
            _rewardParam = [rewardParam UTF8String];
        }
        self.listener->onFinishedAd([zoneId UTF8String], (int) playtime, (bool) skipped, _rewardParam);
    }
}
- (void) maioDidClickAd:(NSString *)zoneId {
    if([self isListenerExist]){
        self.listener->onClickedAd([zoneId UTF8String]);
    }
}
- (void) maioDidCloseAd:(NSString *)zoneId {
    if([self isListenerExist]){
        self.listener->onClosedAd([zoneId UTF8String]);
    }
}
- (void) maioDidFail:(NSString *)zoneId reason:(MaioFailReason)reason {
    if([self isListenerExist]){
        std::string _zoneId = std::string();
        if(zoneId){
            _zoneId = std::string([zoneId UTF8String]);
        }
        self.listener->onFailed(_zoneId, [self toFailReason: reason]);
    }
}

- (maio::FailReason) toFailReason: (MaioFailReason) reason {
    switch (reason) {
        case MaioFailReasonUnknown:
            return maio::FailReason::Unknown;
        case MaioFailReasonAdStockOut:
            return maio::FailReason::AdStockOut;
        case MaioFailReasonNetworkConnection:
            return maio::FailReason::NetworkConnection;
        case MaioFailReasonNetworkClient:
            return maio::FailReason::NetworkClient;
        case MaioFailReasonNetworkServer:
            return maio::FailReason::NetworkServer;
        case MaioFailReasonSdk:
            return maio::FailReason::Sdk;
        case MaioFailReasonDownloadCancelled:
            return maio::FailReason::DownloadCancelled;
        case MaioFailReasonVideoPlayback:
            return maio::FailReason::VideoPlayback;
    }
}

- (BOOL) isListenerExist {
    return (BOOL) (self.listener != NULL);
}

@end


// MaioListener methods
maio::MaioListener::~MaioListener(){}
void maio::MaioListener::onInitialized(){}
void maio::MaioListener::onChangedCanShow(const std::string &zoneId, const bool newValue){}
void maio::MaioListener::onStartAd(const std::string &zoneId){}
void maio::MaioListener::onFinishedAd(const std::string &zoneId, const int playtime, const bool skipped, const std::string &rewardParam){}
void maio::MaioListener::onClickedAd(const std::string &zoneId){}
void maio::MaioListener::onClosedAd(const std::string &zoneId){}
void maio::MaioListener::onFailed(const std::string &zoneId, const FailReason reason){}


// MaioPlugin methods
void maio::MaioPlugin::start(const std::string &mediaId, maio::MaioListener *listener) {
    [MaioDelegateBridge sharedInstance].listener = listener;
    [Maio startWithMediaId: [NSString stringWithUTF8String: mediaId.c_str()] delegate: (id<MaioDelegate>)[MaioDelegateBridge sharedInstance]];
}

bool maio::MaioPlugin::canShow() {
    return [Maio canShow];
}

bool maio::MaioPlugin::canShow(const std::string &zoneId) {
    return [Maio canShowAtZoneId:[NSString stringWithUTF8String: zoneId.c_str()]];
}

void maio::MaioPlugin::show() {
    [Maio show];
}

void maio::MaioPlugin::show(const std::string &zoneId) {
    [Maio showAtZoneId:[NSString stringWithUTF8String: zoneId.c_str()]];
}

void maio::MaioPlugin::setAdTestMode(bool setAdTestMode){
    [Maio setAdTestMode: (BOOL) setAdTestMode];
}

std::string maio::MaioPlugin::getSdkVersion(){
    return [[Maio sdkVersion] UTF8String];
}

void maio::MaioPlugin::setListener(maio::MaioListener *listener){
    [MaioDelegateBridge sharedInstance].listener = listener;
}

void maio::MaioPlugin::removeListener() {
    [MaioDelegateBridge sharedInstance].listener = NULL;
}