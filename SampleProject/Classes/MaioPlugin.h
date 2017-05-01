//
//  MaioPlugin.h
//
//  Created by maio on 2016/08/04.
//
//

#ifndef MaioPlugin_h
#define MaioPlugin_h

namespace maio {
    enum class FailReason{
        /// 不明なエラー
        Unknown = 0,
        /// 広告在庫切れ
        AdStockOut,
        /// ネットワーク接続エラー
        NetworkConnection,
        /// HTTP status 4xx クライアントエラー
        NetworkClient,
        /// HTTP status 5xx サーバーエラー
        NetworkServer,
        /// SDK エラー
        Sdk,
        /// クリエイティブダウンロードのキャンセル
        DownloadCancelled,
        /// 動画再生エラー
        VideoPlayback,
    };
    
    class MaioListener {
    public:
        virtual ~MaioListener();
        virtual void onInitialized();
        virtual void onChangedCanShow( const char *zoneId, const bool newValue );
        virtual void onStartAd( const char *zoneId );
        virtual void onFinishedAd( const char *zoneId, const int playtime, const bool skipped, const char *rewardParam );
        virtual void onClickedAd( const char *zoneId );
        virtual void onClosedAd( const char *zoneId );
        virtual void onFailed( const char *zoneId, const FailReason reason );
    };
    
    class MaioPlugin {
    public:
        static std::string getSdkVersion();
        static void setAdTestMode(bool adTestMode);
        static void start( const char *mediaId, MaioListener *listener );
        static bool canShow();
        static bool canShow( const char *zoneId );
        static void show();
        static void show( const char *zoneId );
        static void setListener(MaioListener *listener);
        static void removeListener();
    };
}

#endif
