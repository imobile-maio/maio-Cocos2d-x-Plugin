package jp.maio.sdk.plugin.cocos.android;

import android.util.Log;

import org.cocos2dx.lib.Cocos2dxHelper;

import jp.maio.sdk.android.FailNotificationReason;
import jp.maio.sdk.android.MaioAds;
import jp.maio.sdk.android.MaioAdsListener;

public class MaioPlugin
{
    private static native void onInitialized();
//    private static native void onChangedCanShow(String zoneId, boolean newValue);
//    private static native void onStartAd(String zoneId);
//    private static native void onFinishedAd(String zoneId, int playtime, boolean skipped, String rewardParam);
//    private static native void onClickedAd(String zoneId);
//    private static native void onClosedAd(String zoneId);
//    private static native void onFailed(String zoneId, int reason);

    public static void start(String mediaId) {
        Log.d("Maio", "called start");
        MaioAds.init(Cocos2dxHelper.getActivity(), mediaId, new MaioAdsListener(){
            @Override
            public void onInitialized() {
                Log.d("Maio", "onInitialized");
            }
            @Override
            //変更時の処理
            public void onChangedCanShow(String zoneId, boolean newValue) {
                Log.d("Maio", "onChangedCanShow");
            }
            @Override
            //再生直前に呼ばれる処理
            public void onOpenAd(String zoneId) {
                Log.d("Maio", "onOpenAd");
            }
            @Override
            //再生時に呼ばれる処理
            public void onStartedAd(String zoneId) {
                Log.d("Maio", "onStartedAd");
            }
            @Override
            //再生終了時に呼ばれる処理
            public void onFinishedAd(int playtime, boolean skipped, int duration, String zoneId) {
                Log.d("Maio", "onFinishedAd");
            }
            @Override
            //広告が閉じられた際の処理
            public void onClosedAd(String zoneId) {
                Log.d("Maio", "onClosedAd");
            }
            @Override
            //広告クリック時に呼ばれる処理
            public void onClickedAd(String zoneId) {
                Log.d("Maio", "onClickedAd");
            }
            @Override
            //エラー時に呼ばれる処理
            public void onFailed(FailNotificationReason reason, String zoneId) {
                Log.d("Maio", "onFailed");
            }
        });
    }

    public static boolean canShow() {
        Log.d("Maio", "called can show");
        return MaioAds.canShow();
    }

    public static boolean canShow(String zoneId) {
        Log.d("Maio", "called can show zoneId");
        return MaioAds.canShow(zoneId);
    }

    public static void show() {
        Log.d("Maio", "called show");
        MaioAds.show();
    }

    public static void show(String zoneId) {
        Log.d("Maio", "called show zoneId");
        MaioAds.show(zoneId);
    }

    public static String getSdkVersion() {
        Log.d("Maio", "called getSdkVersion");
        return MaioAds.getSdkVersion();
    }

    public static void setAdTestMode(boolean setAdTestMode) {
        Log.d("Maio", "called setAdTestMode");
        MaioAds.setAdTestMode(setAdTestMode);
    }
}