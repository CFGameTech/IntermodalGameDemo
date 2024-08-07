//
//  CFUserModel.h
//  Tofee
//
//  Created by mac on 2023/7/10.
//

#import <Foundation/Foundation.h>
#import "CFGameSDK.h"
@class CFGameModel;


NS_ASSUME_NONNULL_BEGIN

@interface CFGameEngine : NSObject


@property (nonatomic,assign) NSInteger appId;

@property (nonatomic,copy) NSString *language;

/*
 *  open game list
 */
-(void)showGameList;

/*
 *  set user info and code
 */
-(void)setUserInfo:(NSString *)userId userCode:(NSString *)userCode;


-(void)getGameListWithSuccess:(GetGameListSuccessBlk)successBlk failure:(GetGameListFailureBlk)failBlk;


-(void)loadHalfWindowGame:(NSString *)gameId url:(NSString *)url;

-(void)loadFullWindowGame:(NSString *)gameId url:(NSString *)url;


/*
 *  finish game window
 */
-(void)finishGameWindow;

/*
 *  terminate current game
 */
-(void)terminateGame;

/*
 *  joinGame with position
 */
-(void)joinGame:(int)position;


/*
 *  refresh game userInfo
 */
-(void)refreshUserInfo;

-(CFGameWebviewController *)createGameWebViewWithUrl:(NSString *)gameUrl gameId:(int)gameId;

@end

NS_ASSUME_NONNULL_END
