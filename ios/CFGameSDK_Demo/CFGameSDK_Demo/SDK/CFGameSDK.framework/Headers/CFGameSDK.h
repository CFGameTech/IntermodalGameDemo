//
//  CFGameSDK.h
//  CFGameSDK
//
//  Created by YQ_Mac on 2024/9/5.
//


#import <CFGameSDK/CFGameModel.h>
#import <CFGameSDK/CFGameWebviewController.h>

typedef struct {
    CGFloat top;
    CGFloat left;
    CGFloat bottom;
    CGFloat right;
    CGFloat minScaleLimit;
} CFGameEdgeInsets;


typedef void(^GetGameListSuccessBlk)(NSArray<CFGameModel *> *gameList);
typedef void(^GetGameListFailureBlk)(int code ,NSString *msg);

@protocol CFGameSDKDelegate <NSObject>

@required

/**
 *
 * sdk回调渠道方，拉起渠道方的充值页面
 */
- (void)openChargePage;

/**
 *
 * Returns：当前用户所在的房间号，如果没有互动玩法可直接返回空字符串
 */
- (NSString *)onGetCurrentRoomId;
/**
 *
 * Returns：如果平台无需指定游戏管理员可直接返回false
 */
- (BOOL)onIsRoomOwner;
/**
 *
 * Returns：游戏视图的安全区域，若无要求可返回null
 */
- (CFGameEdgeInsets)onWindowSafeArea;

@end


@protocol CFGameSDKLoginDelegate <NSObject>
@required

/**
 *
 * 用户登录成功回调
 */
- (void)onLoginSuccess;

/**
 *
 * 用户登录失败回调
 */
- (void)onLoginFailCode:(int)code message:(NSString *)msg;
/**
 *
 * token 更新后回调，接入方通常无需关注此接口
 */
- (void)onRefreshToken:(NSString *)token;

@end

@protocol CFGameLifeCycleDelegate <NSObject>
@required

/**
 *
 * 游戏加载失败
 */
- (void)onGameLoadFail;

/**
    游戏加载完毕
 */
- (void)gameDidFinishLoad;

/**
 *
 * 用户自动上麦加入游戏
 */
- (BOOL)onPreJoinGame:(NSString *)uid seatIndex:(int)seatIndex;

/**
 *
 * 用户加入游戏
 */
- (void)onJoinGame:(NSString *)uid;

/**
 *
 * 用户准备游戏
 */
- (void)onGamePrepare:(NSString *)uid;

/**
 *
 * 用户取消准备
 */
- (void)onCancelPrepare:(NSString *)uid;


/**
 *
 * 用户游戏终结
 */
- (void)onGameTerminated:(NSString *)uid;

/**
 *
 * 游戏结束
 */
- (void)onGameOver;


@end


@protocol CFGameSDKRTCDelegate <NSObject>
@required

- (BOOL)onCFGamePushSelfRTC:(BOOL)push;

- (BOOL)onCFGamePullOtherRTC:(NSString *)uid pull:(BOOL)pull;

@end



NS_ASSUME_NONNULL_BEGIN

@interface CFGameSDK : NSObject
/**
    sdk日志打印接口
    logMsg : 日志msg
 
 */

+ (void)cfGameSDKLog:(void(^)(NSString *logMsg))handler;


/*
 *  @param app : UIApplication 当前application
 *  @param appId : 创发提供的appId
 *  @param appKey : 创发提供的appKey
 */
+(void)setUpSDKWithApplication:(UIApplication *)app appId:(NSString *)appId language:(NSString *)language isProduct:(BOOL)isProduct;


/*
 *  @param userId : 接入方的用户id
 *  @param userCode : 接入方的用户code,用于创发向接入方校验用户的合法性
 */
+(void)setUserInfo:(NSString *)userId code:(NSString *)userCode loginCallBack:(id<CFGameSDKLoginDelegate>)loginCallBack;


/*
 *  拉起游戏列表弹窗
 */
+(void)showGameList;

/*
 *  获取游戏列表
 */
+(void)getGameListWithSuccess:(GetGameListSuccessBlk)successBlk failure:(GetGameListFailureBlk)failBlk;

/*
 *  加载半屏游戏
 *  @param gameId : 游戏id
 *  @url   url : 游戏url
 */
+(void)loadHalfWindowGame:(NSString *)gameId url:(NSString *)url;

/*
 *  加载全屏游戏
 *  @param gameId : 游戏id
 *  @url   url : 游戏url
 */
+(void)loadFullWindowGame:(NSString *)gameId url:(NSString *)url;

/*
    上报透传参数 extString : 透传参数 (传字符串类型，内容由平台自定义)
 
 */

+(void)sentExtToGame:(NSString *)extString;


/*
 *  销毁游戏窗口
 */
+(void)finishGameWindow;

/*
 *  释放当前游戏
 */
+(void)terminateGame;

/*
 *  加入当前游戏
 *  @param position : 位置
 */
+(void)joinGame:(int)position;

/*
 *  通过js通知游戏刷新用户资产信息
 */
+(void)refreshUserInfo;

/*
 *  开始游戏
 */
+(void)gameStart;

/**
    踢人
 @param uid 用户id
 */

+(void)playerRemoveWithUid:(NSString *)uid;

/**
    打开/关闭 背景音乐
    @param mode  YES 开 NO 关
 */
+(void)gameBackgroundMusicSet:(BOOL)mode;

/**
    打开/关闭音效
 @param mode YES 开 NO 关
 */
+(void)gameSoundSet:(BOOL)mode;

/*
 *  设置接入方回调
 */
+(void)setBizCallback:(id<CFGameSDKDelegate>)callback;


/*
 *  设置CFGame LifeCycle回调
 */
+(void)setCFGameLifecycleCallback:(id<CFGameLifeCycleDelegate>)callback;


/*
 *  设置RTC回调
 */
+(void)setRTCCallback:(id<CFGameSDKRTCDelegate>)callback;

/*
 *  获取CFGameWebViewController 用于自定义展示
 */
+(CFGameWebviewController *)createGameWebViewWithUrl:(NSString *)gameUrl gameId:(int)gameId;


/*
 * 释放sdk
 */
+(void)releaseSDK;


/*
 * 获取当前版本号
 */
+ (NSString *)sdkVersion;


@end

NS_ASSUME_NONNULL_END
