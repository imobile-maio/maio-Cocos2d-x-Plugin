package jp.maio.sdk.plugin.cocos.android;

import android.util.Log;

import org.cocos2dx.lib.Cocos2dxHelper;

import jp.maio.sdk.android.FailNotificationReason;
import jp.maio.sdk.android.MaioAds;
import jp.maio.sdk.android.MaioAdsListener;

public class MaioPlugin
{
    private static native void onInitialized();
    private static native void onChangedCanShow(String zoneId, boolean newValue);
    private static native void onStartAd(String zoneId);
    private static native void onFinishedAd(String zoneId, int playtime, boolean skipped, String rewardParam);
    private static native void onClickedAd(String zoneId);
    private static native void onClosedAd(String zoneId);
    private static native void onFailed(String zoneId, int reason);

    public static void start(String mediaId) {
        Log.d("Maio", "called start");
        MaioAds.init(Cocos2dxHelper.getActivity(), mediaId, new MaioAdsListener(){
            @Override
            public void onInitialized() {
                MaioPlugin.onInitialized();
            }
            @Override
            //変更時の処理
            public void onChangedCanShow(String zoneId, boolean newValue) {
                MaioPlugin.onChangedCanShow(zoneId, newValue);
            }
            @Override
            //再生直前に呼ばれる処理
            public void onOpenAd(String zoneId) {
                MaioPlugin.onStartAd(zoneId);
            }
            @Override
            //再生時に呼ばれる処理
            public void onStartedAd(String zoneId) {
                // MEMO: onStartedAdはiOS側に実装がなく、onOpenAdとほぼ同タイミングの為無視
            }
            @Override
            //再生終了時に呼ばれる処理
            public void onFinishedAd(int playtime, boolean skipped, int duration, String zoneId) {
                // TODO: androidではrewardParamを実装していないので、実装されたら以下の 0 を修正する
                MaioPlugin.onFinishedAd(zoneId, playtime, skipped, "0");
            }
            @Override
            //広告クリック時に呼ばれる処理
            public void onClickedAd(String zoneId) {
                MaioPlugin.onClickedAd(zoneId);
            }
            @Override
            //広告が閉じられた際の処理
            public void onClosedAd(String zoneId) {
                MaioPlugin.onClosedAd(zoneId);
            }
            @Override
            //エラー時に呼ばれる処理
            public void onFailed(FailNotificationReason reason, String zoneId) {
                int failReason;
                switch (reason)
                {
                    case AD_STOCK_OUT       :failReason = 1; break;
                    case RESPONSE           :failReason = 2; break;
                    case NETWORK_NOT_READY  :failReason = 3; break;
                    case NETWORK            :failReason = 4; break;
                    case VIDEO              :failReason = 5; break;
                    
                    case UNKNOWN:
                    default:
                        failReason = 0; break;
                }

                MaioPlugin.onFailed(zoneId, failReason);
            }
        });
    }

    public static boolean canShow() {
        return MaioAds.canShow();
    }

    public static boolean canShow(String zoneId) {
        return MaioAds.canShow(zoneId);
    }

    public static void show() {
        MaioAds.show();
    }

    public static void show(String zoneId) {
        MaioAds.show(zoneId);
    }

    public static String getSdkVersion() {
        return MaioAds.getSdkVersion();
    }

    public static void setAdTestMode(boolean setAdTestMode) {
        MaioAds.setAdTestMode(setAdTestMode);
    }
}