package jp.maio.sdk.plugin.cocos.android;

import jp.maio.sdk.android.MaioAds;

public class MaioPlugin
{
    private static native void onGetSdkVersion(String version);

    public static String getSdkVersion()
    {
        return MaioAds.getSdkVersion();
    }
}