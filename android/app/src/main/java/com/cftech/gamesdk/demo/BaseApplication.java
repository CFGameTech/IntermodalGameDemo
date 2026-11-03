package com.cftech.gamesdk.demo;

import android.app.Application;
import android.util.Log;

import com.cftech.gamelibrary.CFGameSDK;
import com.cftech.gamelibrary.CFGameInitSDKModel;

public class BaseApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        CFGameInitSDKModel initSDKModel = new CFGameInitSDKModel();
        initSDKModel.application = this;
        initSDKModel.appId = 1015902;
        initSDKModel.appKey = "30f19f04d7e2e2186f477f28c813";

        initSDKModel.language = "en";
        initSDKModel.area = "fra";
        initSDKModel.isGameSoundPlay = true;
        initSDKModel.isProduct = true;

        CFGameSDK.initSDK(initSDKModel, new CFGameSDK.ICFSDKCallback() {
            @Override
            public void onSuccess() {
                Log.i("BaseApplication", "CFGameSDK Init Success.");
            }

            @Override
            public void onError(int i, String s) {
                Log.i("BaseApplication", "CFGameSDK Init fail.");
            }
        });


    }
}
