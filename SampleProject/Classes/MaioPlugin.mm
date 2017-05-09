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
    if(self.listener) {
        self.listener->onInitialized();
    }
}
- (void) maioDidChangeCanShow:(NSString *)zoneId newValue:(BOOL)newValue {
    if(self.listener){
        self.listener->onChangedCanShow([zoneId UTF8String], (bool) newValue);
    }
}
- (void) maioWillStartAd:(NSString *)zoneId {
    if(self.listener){
        self.listener->onStartAd([zoneId UTF8String]);
    }
}
- (void) maioDidFinishAd:(NSString *)zoneId playtime:(NSInteger)playtime skipped:(BOOL)skipped rewardParam:(NSString *)rewardParam {
    if(self.listener){
        self.listener->onFinishedAd([zoneId UTF8String], (int) playtime, (bool) skipped, [rewardParam UTF8String]);
    }
}
- (void) maioDidClickAd:(NSString *)zoneId {
    if(self.listener){
        self.listener->onClickedAd([zoneId UTF8String]);
    }
}
- (void) maioDidCloseAd:(NSString *)zoneId {
    if(self.listener){
        self.listener->onClosedAd([zoneId UTF8String]);
    }
}
- (void) maioDidFail:(NSString *)zoneId reason:(MaioFailReason)reason {
    if(self.listener){
        self.listener->onFailed([zoneId UTF8String], [self toFailReason: reason]);
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
        default:
            return maio::FailReason::Unknown;
    }
}

@end

// MaioPlugin methods
void maio::MaioPlugin::start( const char *mediaId, maio::MaioListener *listener ) {
    [MaioDelegateBridge sharedInstance].listener = listener;
    [Maio startWithMediaId:[NSString stringWithUTF8String: mediaId]
                  delegate:(id<MaioDelegate>)[MaioDelegateBridge sharedInstance]];
}

bool maio::MaioPlugin::canShow() {
    return [Maio canShow];
}

bool maio::MaioPlugin::canShow( const char *zoneId ) {
    return [Maio canShowAtZoneId:[NSString stringWithUTF8String: zoneId]];
}

void maio::MaioPlugin::show() {
    [Maio show];
}

void maio::MaioPlugin::show( const char *zoneId ) {
    [Maio showAtZoneId:[NSString stringWithUTF8String: zoneId]];
}

void maio::MaioPlugin::setAdTestMode(bool setAdTestMode){
    [Maio setAdTestMode: (BOOL) setAdTestMode];
}

char const* maio::MaioPlugin::getSdkVersion(){
    return [[Maio sdkVersion] UTF8String];
}

void maio::MaioPlugin::setListener(maio::MaioListener *listener){
    [MaioDelegateBridge sharedInstance].listener = listener;
}

void maio::MaioPlugin::removeListener() {
    [MaioDelegateBridge sharedInstance].listener = NULL;
}
