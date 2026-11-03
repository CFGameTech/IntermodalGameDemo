var cfgCallJsBacks={};

var cf_game={
    GameLife: {
        gameLoadFail() {
            console.log("sdk gameLoadFail()");
            CFGameLife.gameLoadFail();
        },
        gameLoadSuccess() {
            console.log("sdk gameLoadSuccess()");
            CFGameLife.gameLoadSuccess();
        },
        preJoinGame(uid, seat, callback) {
            console.log("sdk preJoinGame()");
            var invokeId = getInvokeId();
            cfgCallJsBacks[invokeId] = callback;
            CFGameLife.preJoinGame(uid, seat, invokeId);
        },
       onSeatAvatarTouch(userid, seat) {
            console.log("sdk onSeatAvatarTouch()");
            CFGameLife.onSeatAvatarTouch(userid, seat);
        },
        joinGame(index) {
            console.log("sdk joinGame()");
            CFGameLife.joinGame(index);
        },
        getGameloadProgress(progress) {
            CFGameLife.getGameloadProgress(progress);
        },
        gamePrepare(uid) {
            console.log("sdk gamePrepare()");
            CFGameLife.gamePrepare(uid);
        },
        cancelPrepare(uid) {
            console.log("sdk cancelPrepare()");
            CFGameLife.cancelPrepare(uid);
        },
        gameTerminated(uid) {
            console.log("sdk gameTerminated()");
            CFGameLife.gameTerminated(uid);
        },
        quitGame(uid) {
            console.log("sdk quitGame()");
            CFGameLife.quitGame(uid);
        },
        gameOver(uid) {
            console.log("sdk gameOver()");
            CFGameLife.gameOver(uid);
        },
        gameLoadOfflineProps(){
            console.log("sdk gameLoadOfflineProps()");
            CFGameLife.gameLoadOfflineProps();
        },
        setPlayerRole(role){
             console.log("sdk setPlayerRole()");
             CFGameLife.setPlayerRole(role);
        },
        pauseGame(){
             console.log("sdk pauseGame()");
             CFGameLife.pauseGame();
        },
        playGame(){
             console.log("sdk playGame()");
             CFGameLife.playGame();
        },
        appCallGame(dataJson){
            console.log("sdk appCallGame()");
            CFGameLife.appCallGame(dataJson);
        },
        playerStateChange(dataJson){
            console.log("sdk playerStateChange()");
            CFGameLife.playerStateChange(dataJson);
        },
        gameStateChange(dataJson){
            console.log("sdk gameStateChange()");
            CFGameLife.gameStateChange(dataJson);
        },
        onGamePurchaseResult(code, orderId) {
            console.log("sdk onGamePurchaseResult()");
            CFGameLife.onGamePurchaseResult(code, orderId);
        },
         onGameMusicStartPlay(musicId,musicUrl,isLoop){
             console.log("sdk onGameMusicStartPlay");
             CFGameLife.onGameMusicStartPlay(musicId,musicUrl,isLoop);
         },
         onGameMusicStopPlay(musicId){
             console.log("sdk onGameMusicStopPlay");
             CFGameLife.onGameMusicStopPlay(musicId);
         },
         onGameEffectSoundStartPlay(soundId,soundUrl,isLoop){
             console.log("sdk onGameEffectSoundStartPlay");
             CFGameLife.onGameEffectSoundStartPlay(soundId,soundUrl,isLoop);
         },
         onGameEffectSoundStopPlay(soundId){
              console.log("sdk onGameEffectSoundStopPlay");
              CFGameLife.onGameEffectSoundStopPlay(soundId);
         },
         gameSendScreenshot(data,json){
              console.log("sdk gameSendScreenshot");
              CFGameLife.gameSendScreenshot(data,json);
          }

    },
    OpenApi:{
        getBaseInfo: function (callback) {
                    console.log("sdk getBaseInfo()");
                    var invokeId = getInvokeId();
                    cfgCallJsBacks[invokeId] = callback;
                    CFGameOpenApi.getBaseInfo(invokeId);
        },

        getWindowSafeArea: function (callback) {
                    console.log("sdk getWindowSafeArea()");
                    var invokeId = getInvokeId();
                    cfgCallJsBacks[invokeId] = callback;
                    CFGameOpenApi.getWindowSafeArea(invokeId);
        },

        openChargePage: function () {
                    console.log("sdk openChargePage()");
                    CFGameOpenApi.openChargePage();
        },

        closeGamePage: function () {
                    console.log("sdk closeGamePage()");
                    CFGameOpenApi.closeGamePage();
        }
    },
    GameRTC:{
            onCFGamePushSelfRTC: function (push, callback) {
                console.log("sdk onCFGamePushSelfRTC()");
                var invokeId = getInvokeId();
                cfgCallJsBacks[invokeId] = callback;
                CFGameRTC.onCFGamePushSelfRTC(push, invokeId);
            },
            onCFGamePullOtherRTC: function (uid, pull, callback) {
                console.log("sdk onCFGamePullOtherRTC()");
                var invokeId = getInvokeId();
                cfgCallJsBacks[invokeId] = callback;
                CFGameRTC.onCFGamePullOtherRTC(uid, pull, invokeId);
            }
    }
};

function getInvokeId(){
	return Date.now().toString();
}

function callCFJs(invokeId, data) {
    var callback = cfgCallJsBacks[invokeId];
    if(callback == undefined){
        console.log("callback is null !");
    } else {
	    callback(data);
        delete (cfgCallJsBacks[invokeId]);
    }
}

window.CFGame=cf_game;