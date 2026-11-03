declare namespace CFGame {
    /**
    * let接口用于原生调用js
    * function接口用于js调用原生
    */

    /**
     * 游戏生命周期相关
     */
    export module GameLife {

        /**
         *     -- 描述：游戏加载启动失败调用
         */
        function gameLoadFail()

        /**
         *     -- 描述：用户准备加入游戏
         *     -- 参数：
         *     -- userId: 加入游戏用户id
          *     -- seat ：传-1表示随机加入, 从0开始，不可大于座位数
          *     --  result | 结果回调 function result（string result):
          *     --      {
          *     --          int    code,//回调状态，0为成功，其余为异常
          *     --          string msg,//错误信息
          *     --          result: {
          *     --              boolean is_ready, //是否成功
          *     --          }
          *     --      }
         */
        function preJoinGame(userId: string, seat: number, result: (arg0: string) => any)
        /**
         *     -- 描述：用户加入游戏
         *     -- 参数：
         *     -- userId: 加入游戏用户id
         */
         function joinGame(index: number)

        /**
         *     -- 描述：用户准备游戏
         *     -- 参数：
         *     -- userId: 游戏用户id
         */
        function gamePrepare(userId: string)

        /**
         *     -- 描述：用户取消准备
         *     -- 参数：
         *     -- userId: 游戏用户id
         */
        function cancelPrepare(userId: string)

        /**
         *     -- 描述：强制中止游戏
         *     -- 参数：
         *     -- userId: 操作者id
         */
        function gameTerminated(userId: string)

        /**
         *     -- 描述：退出游戏
         *     -- 参数：
         *     -- userId: 操作者id
         */
        function quitGame(userId: string)

        /**
         *     -- 描述：游戏结束
         *     -- 参数：
         */
        function gameOver(userId: string)

        /**
         *     -- 描述：用户点击头像
         *     -- 参数：被点击的seat 和 userid
         */
        function onSeatAvatarTouch(userid: string, seat: number)


        /**
         *      -- 游戏状态发生变化
         *      -- 参数：自定义dataJson
         */
        function gameStateChange(dataJson: string)

        /**
         *      -- 游戏玩家状态发生变化
         *      -- 参数：自定义dataJson
         */
        function playerStateChange(dataJson: string)

        /**
         *     -- 描述：游戏进入前台回调
         */
        let appShow: () => any

        /**
         *     -- 描述：游戏进入后台回调
         */
        let appHide: () => any
    }
    /**
     * 游戏RTC相关
     */
    export module GameRTC {

        /**
         *     -- 描述：是否推送自己的流
         *     -- 参数：
         *     --  result | 结果回调 function result（string result):
         *     --      {
         *     --          int    code,//回调状态，0为成功，其余为异常
         *     --          string msg,//错误信息
         *     --          result: {
         *     --              boolean complete, //是否成功
         *     --          }
         *     --      }
         */
        let onCFGamePushSelfRTC: (push: boolean) : any

        /**
         *     -- 描述：是否拉取其他人的流
         *     -- 参数：
         *     --  result | 结果回调 function result（string result):
         *     --      {
         *     --          int    code,//回调状态，0为成功，其余为异常
         *     --          string msg,//错误信息
         *     --          result: {
         *     --              boolean complete, //是否成功
         *     --          }
         *     --      }
         */
        let onCFGamePullOtherRTC: (uid: string, pull: boolean) : any
    }

    /**
    * 通用逻辑相关
    */
    export module OpenApi {

        /**
         *     -- 描述：获取当前用户信息（异步）
         *     -- 参数：
         *     --  result | 结果回调 function result（string result):
         *     --      {
         *     --          int    code,//回调状态，0为成功，其余为异常
         *     --          string msg,//错误信息
         *     --          result: {
         *     --              string cid,//渠道id
         *     --              string gid,//游戏id
         *     --              string uid,//渠道用户id
         *     --              string token,//sdk平台令牌
         *     --              string version,//客户端sdk版本号
         *     --              string language,//语言
         *     --              string widow,//窗口大小->"宽度x高度"
         *     --              string rid,//当前房间号
         *     --              boolean room_owner,//是否房主
         *     --          }
         *     --      }
         */
        function getBaseInfo(result : (arg0: string) => any)

        /**
         *     -- 描述：获取窗口安全距离，四个字段分别对应顶部、左侧、右侧、底部的安全距离，根据实际业务进行使用；
         *     -- 参数：
         *     --  result | 结果回调 function result（string result):
         *     --      {
         *     --          int    code,//回调状态，0为成功，其余为异常
         *     --          string msg,//错误信息
         *     --          result: {
         *     --               "top":48,
         *     --           	"left":16,
         *     --           	"right":16,
         *     --           	"bottom":0,
         *     --           	"scale_min_limit":0.6,
         *     --          }
         *     --      }
         */
        function getWindowSafeArea(result : (arg0: string) => any)

         /**
         *     -- 描述：拉起平台支付页面
         */
        function openChargePage()

        /**
         *     -- 描述：关闭游戏页面
         */
        function closeGamePage()

         /**
         *     -- 描述：原生调用js刷新用户信息
         */
        let refreshUserInfo: () => any

        /**
         *     -- 描述：原生调用js销毁游戏
         */
        let destroyGame: () => any
    }

}