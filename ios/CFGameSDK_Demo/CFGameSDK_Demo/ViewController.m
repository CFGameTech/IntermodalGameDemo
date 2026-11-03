//
//  ViewController.m
//  CFGameSDK_Demo
//
//  Created by apple developer on 2024/6/5.
//

#import "ViewController.h"
#import "CFGameSDK/CFGameSDK.h"

@interface ViewController () <CFGameSDKDelegate,CFGameSDKRTCDelegate,CFGameLifeCycleDelegate>
@property (weak, nonatomic) IBOutlet UITextField *languageTF;
@property (weak, nonatomic) IBOutlet UITextField *channelTF;
@property (weak, nonatomic) IBOutlet UITextField *userIDTF;
@property (weak, nonatomic) IBOutlet UITextField *roomIDTF;
@property (weak, nonatomic) IBOutlet UITextField *isOwnerTF;
@property (weak, nonatomic) IBOutlet UIButton *envBtn;


@property (copy,nonatomic) NSString *selectLanguage;


@property (nonatomic,assign) BOOL isProduct;


@property (weak, nonatomic) IBOutlet UITextField *topPaddingTF;
@property (weak, nonatomic) IBOutlet UITextField *leftPaddingTF;
@property (weak, nonatomic) IBOutlet UITextField *bottomPaddingTF;
@property (weak, nonatomic) IBOutlet UITextField *rightPaddingTF;
@property (weak, nonatomic) IBOutlet UITextField *scalePaddingTF;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [CFGameSDK cfGameSDKLog:^(NSString * _Nonnull logMsg) {
        NSLog(@"sdk log %@",logMsg);
    }];
    
    
}

- (IBAction)initAction:(id)sender {
    if (self.channelTF.text.length == 0){

        UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"提示" message:@"渠道号为必填项" preferredStyle:(UIAlertControllerStyleAlert)];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
           }];
        [alertVc addAction:okAction];
        [self presentViewController:alertVc animated:TRUE completion:nil];
        return;
    }
    
    if (self.languageTF.text.length == 0){
       
        UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"提示" message:@"语言为必填项" preferredStyle:(UIAlertControllerStyleAlert)];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
           }];
        [alertVc addAction:okAction];
        [self presentViewController:alertVc animated:TRUE completion:nil];
        return;
    }
 
    [self.view endEditing:YES];

    
    CFGameInitSDKModel *initModel = [[CFGameInitSDKModel alloc] init];
    initModel.app = UIApplication.sharedApplication;
    initModel.appId = [self.channelTF.text intValue];
    initModel.appKey = @"30f19f04d7e2e2186f477f28c813";
    initModel.area = @"fra";
    initModel.language = @"en";
    initModel.isGameSoundPlay = YES;
    initModel.isProduct = YES;
    
    
    [CFGameSDK setUpSDKWithModel:initModel onSuccess:^{
            
        NSLog(@"CFGameSDK init success");
        
        [CFGameSDK setBizCallback:self];

        [CFGameSDK setCFGameLifecycleCallback:self];
        [CFGameSDK setRTCCallback:self];
        
    } onFailure:^(int code, NSString * _Nonnull msg) {
        NSLog(@"CFGameSDK init failure, code:%d msg:%@",code,msg);
    }];
    
    

    

}

- (IBAction)gameListAction:(id)sender {
    [self.view endEditing:YES];

    if (self.roomIDTF.text.length == 0){
       
        UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"提示" message:@"房间id为必填项" preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
           }];
        [alertVc addAction:okAction];

        [self presentViewController:alertVc animated:TRUE completion:nil];
        return;
    }
    
   
    
    if (self.isOwnerTF.text.length == 0){
        
        UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"提示" message:@"是否房主为必填项" preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
           }];
        [alertVc addAction:okAction];

        [self presentViewController:alertVc animated:TRUE completion:nil];
        
        return;
    }
    [CFGameSDK showGameListDialog:self userId:self.userIDTF.text userCode:@"" onSuccess:^{
        NSLog(@"showGameListDialog init success");
    } onFailure:^(int code, NSString * _Nonnull msg) {
        NSLog(@"showGameListDialog  failure, code:%d msg:%@",code,msg);
    }];
}

- (IBAction)envAction:(id)sender {
    [self.view endEditing:YES];
    
    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"请选择环境" message:@"" preferredStyle:UIAlertControllerStyleActionSheet];
    UIAlertAction *testAction = [UIAlertAction actionWithTitle:@"测试环境" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        self.isProduct = FALSE;
        [self.envBtn setTitle:@"测试环境" forState:UIControlStateNormal];
        
       }];
    UIAlertAction *productAction = [UIAlertAction actionWithTitle:@"生产环境" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        self.isProduct = TRUE;
        [self.envBtn setTitle:@"生产环境" forState:UIControlStateNormal];
       }];
    
    [alertVc addAction:testAction];
    [alertVc addAction:productAction];
                                  
    [self presentViewController:alertVc animated:TRUE completion:nil];
}



- (NSString *)onGetCurrentRoomId {
    return self.roomIDTF.text;
}

- (BOOL)onIsRoomOwner {
    return [self.isOwnerTF.text isEqualToString:@"1"];
}

- (CFGameEdgeInsets)onWindowSafeArea {
    CFGameEdgeInsets insets;
    insets.top = self.topPaddingTF.text.floatValue;
    insets.left = self.leftPaddingTF.text.floatValue;
    insets.bottom = self.bottomPaddingTF.text.floatValue;
    insets.right = self.rightPaddingTF.text.floatValue;
    insets.minScaleLimit = self.scalePaddingTF.text.floatValue;
    return insets;
}

- (void)openChargePage {
    
}

- (void)onGamePageClose{
    
    [CFGameSDK finishGameWindow];
}

- (NSString * _Nullable)onGetGameConfig:(NSString * _Nullable)dataJson { 
    return @"";
}


- (void)onPreLoadGameSuccess:(NSInteger)gid gameState:(GameState)state { 
    
}


- (void)openPlatformPage:(NSString * _Nonnull)path data:(NSString * _Nullable)data { 
    
}


- (void)reportStatsEvent:(NSString * _Nullable)event Code:(long)code Msg:(NSString * _Nullable)msg { 
    
}


- (void)onPreLoadGameSuccess:(NSInteger)gid { 
    
}



/**
 *
 * 游戏加载失败
 */
- (void)onGameLoadFail{
    NSLog(@"CFViewController callback onGameLoadFail ");
    
}


/**
 *
 * 用户自动上麦加入游戏
 */
- (BOOL)onPreJoinGame:(NSString *)uid seatIndex:(NSInteger)seatIndex{
    NSLog(@"CFViewController callback  onPreJoinGame uid = %@ , seatIndex = %ld",uid,seatIndex);
    return YES;
}

/**
 *
 * 用户加入游戏
 */
- (void)onJoinGame:(NSString *)uid{
    NSLog(@"CFViewController callback  uid = %@, JoinGame ",uid);
    
}

/**
 *
 * 用户准备游戏
 */
- (void)onGamePrepare:(NSString *)uid{
    NSLog(@"CFViewController callback uid = %@, gamePrepare ",uid);
    
}

/**
 *
 * 用户取消准备
 */
- (void)onCancelPrepare:(NSString *)uid{
    NSLog(@"CFViewController callback uid = %@, CancelPrepare ",uid);
    
}




/**
 *
 * 用户游戏终结
 */
- (void)onGameTerminated:(NSString *)uid{
    NSLog(@"CFViewController callback uid = %@, game terminated ",uid);
}

/**
 *
 * 游戏结束
 */
- (void)onGameOver{
    NSLog(@"CFViewController callback game over ");
}

- (void)gameDidFinishLoad { 
    
}


- (void)onSeatAvatarTouch:(NSString * _Nonnull)uid seatIndex:(NSInteger)index { 
    
}

- (BOOL)onCanStartGame:(NSString * _Nonnull)uid { 
    return YES;
}


- (int)onGameEffectSoundStartPlay:(int)soundId soundUrl:(NSString * _Nonnull)soundUrl isLoop:(BOOL)isLoop { 
    return 1;
}


- (int)onGameEffectSoundStopPlay:(int)effectId { 
    return 1;
}


- (int)onGameMusicStartPlay:(int)musicId musicUrl:(NSString * _Nonnull)musicUrl isLoop:(BOOL)isLoop { 
    return 1;
}


- (int)onGameMusicStopPlay:(int)musicId { 
    return 1;
}


- (void)onGamePurchaseResult:(int)code OrderId:(NSString * _Nonnull)orderId { 
    
}


- (void)onGameScreenShotBaseData:(NSString * _Nullable)base64String dataJson:(NSString * _Nullable)dataJson { 
    
}


- (void)onGameStateChangeState:(NSString * _Nonnull)state dataJson:(NSString * _Nullable)dataJson { 
    
}


- (void)onPlayerStateChangeState:(NSString * _Nonnull)uid state:(NSString * _Nonnull)state dataJson:(NSString * _Nullable)dataJson { 
    
}




- (BOOL)onCFGamePushSelfRTC:(BOOL)push{
    return YES;
}

- (BOOL)onCFGamePullOtherRTC:(NSString *)uid pull:(BOOL)pull{
    return YES;
}

@end
