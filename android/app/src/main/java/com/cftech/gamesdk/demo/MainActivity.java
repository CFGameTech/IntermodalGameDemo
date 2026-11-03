package com.cftech.gamesdk.demo;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Rect;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.cftech.gamelibrary.CFGameSDK;
import com.cftech.gamelibrary.utils.CFDensityUtil;
import com.cftech.gamelibrary.utils.CFFP;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setUpSDK();


        findViewById(R.id.btnShowGameList).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String uid = ((EditText)findViewById(R.id.etUserId)).getText().toString();

                if (uid == null){
                    Toast.makeText(MainActivity.this, "请填写用户id", Toast.LENGTH_SHORT).show();
                }


                CFGameSDK.showGameListDialog(MainActivity.this, uid, "", new CFGameSDK.ICFSDKCallback() {
                    @Override
                    public void onSuccess() {
                        Log.i("MainActivity", "show GameList Dialog success");
                    }

                    @Override
                    public void onError(int i, String s) {
                        Log.i("MainActivity", "show GameList Dialog fail");
                    }
                });
            }
        });

    }

    private void setUpSDK() {

        CFGameSDK.setBizCallback(new CFGameSDK.ICFBizCallback() {
            @Override
            public void onOpenChargePage() {
                Log.i("MainActivity", "open charge page.");
                Toast.makeText(MainActivity.this, "拉起充值", Toast.LENGTH_SHORT).show();
            }

            @Override
            public String onGetCurrentRoomId() {
                Log.i("MainActivity", "get current room id.");
                return "200016";
            }

            @Override
            public boolean onIsRoomOwner() {
                return true;
            }

            @Override
            public CFGameSDK.CFRect onWindowSafeArea() {
                return new CFGameSDK.CFRect(0, 0, 0, 0, 0.6f);
            }

            @Override
            public void onGamePageClose() {
                Log.i("MainActivity", "on Game Page Close.");
                CFGameSDK.finishGameWindow();
            }

            @Override
            public void openPlatformPage(String s, String s1) {

            }

            @Override
            public String onGetGameConfig(String s) {
                return "";
            }
        });

        CFGameSDK.setCFGameLifecycle(new CFGameSDK.ICFGameLifecycle() {
            @Override
            public void onGameLoadFail() {
                Log.i("MainActivity", "on Game Load Fail");
            }

            @Override
            public boolean onPreJoinGame(String s, int i) {
                return true;
            }

            @Override
            public boolean onCanStartGame(String s) {
                return false;
            }


            @Override
            public void onGamePrepare(String s) {
                Log.i("MainActivity", "on Game Prepare uid:"+s);
            }

            @Override
            public void onCancelPrepare(String s) {
                Log.i("MainActivity", "on Cancel Prepare uid:"+s);
            }


            @Override
            public void onGameOver() {
                Log.i("MainActivity", "on Game Over");
            }

            @Override
            public void onGameDidFinishLoad() {
                Log.i("MainActivity", "on Game Did Finish Load");
            }

            @Override
            public void onSeatAvatarTouch(String s, int i) {
                Log.i("MainActivity", "on Seat Avatar Touch uid:"+s+",seatIndex:"+i);
            }

            @Override
            public void onGameStateChangeState(String s, String s1) {

            }

            @Override
            public void onPlayerStateChangeState(String s, String s1, String s2) {

            }

            @Override
            public void onGamePurchaseResult(int i, String s) {

            }

            @Override
            public int onGameMusicStartPlay(int i, String s, boolean b) {
                return 0;
            }

            @Override
            public int onGameMusicStopPlay(int i) {
                return 0;
            }

            @Override
            public int onGameEffectSoundStartPlay(int i, String s, boolean b) {
                return 0;
            }

            @Override
            public int onGameEffectSoundStopPlay(int i) {
                return 0;
            }

            @Override
            public void onGameScreenShotBaseData(String s, String s1) {

            }
        });
    }
}