//
//  PLUAnalytics.h
//  PLUAnalytics
//
//  Created by DarrenYau on 2016/10/8.
//  Copyright © 2016年 PLU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OpenUDID.h"

typedef NS_ENUM(NSUInteger, eReportPolicy) {
    REPORT_SEND_REALTIME = 1,       //实时（5s发送一次）     (只在“集成测试”设备的DEBUG模式下有效)
    REPORT_SEND_LAUNCH = 2,         //启动发送
    REPORT_SEND_INTERVAL = 3,       //最小间隔发送  ([90-86400]s, default 90s)
};


extern NSNotificationName const PLUAnalyticsAppWillEnterForegroundNotification;
extern NSNotificationName const PLUAnalyticsAppDidEnterBackgroundNotification;
extern NSNotificationName const PLUAnalyticsAppNetworkDidChangedReachablityNotification; // 网络发生变化且有网络通知

typedef NSString * PLUAnalyticsSocialActionString;

extern PLUAnalyticsSocialActionString const PLUAnalyticsSocialActionLike;   // Like
extern PLUAnalyticsSocialActionString const PLUAnalyticsSocialActionShare;  // Share


typedef NSString * PLUAnalyticsSocialTypeString;

extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeSina;                //新浪微博
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeTencent;             //腾讯微博
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeRenren;              //人人网
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeQzone;               //Qzone
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeDouban;              //douban
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeWxsesion;            //微信好友分享
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeWxtimeline;          //微信朋友圈
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeHuaban;              //花瓣
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeKaixin;              //开心
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeFacebook;            //facebook
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeTwitter;             //twitter
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeInstagram;           //instagram
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeFlickr;              //flickr
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeQQ;                  //qq
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeWxfavorite;          //微信收藏
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeLwsession;           //来往
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeLwtimeline;          //来往动态
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeYxsession;           //易信
extern PLUAnalyticsSocialTypeString const PLUAnalyticsSocialTypeYxtimeline;          //易信朋友圈

#define PLUAnalyticsConfigInstance [PLUAnalyticsConfig sharedInstance]

@interface PLUAnalyticsConfig : NSObject

+ (instancetype)sharedInstance;

/** required:  appkey string（服务器分配） */
@property(nonatomic, copy)NSString *appKey;

/** required:  appSecret string(服务器分配) */
@property(nonatomic, copy)NSString *appSecret;

/** required:  route string 路由名称（服务器分配）*/
@property(nonatomic, copy)NSString *routeName;

/** 设置是否打印sdk的log信息, 默认NO(不打印log).
 optional: debugEnabled 设置为YES,PLUAnalytics SDK 会输出log信息可供调试参考. 除非特殊需要，否则发布产品时需改回NO.
 */
@property(nonatomic, assign)BOOL debugEnabled;

/** 设置是否对日志信息进行加密, 默认NO(不加密). (暂未实现)
 optional: encryptEnabled 设置为YES, PLUAnalytics SDK 会将日志信息做加密处理
 */
@property(nonatomic, assign)BOOL encryptEnabled;

/** 当reportPolicy == SEND_INTERVAL 时设定log发送间隔
 optional: logSendInterval 单位为秒,最小90秒,最大86400秒(24hour).  default: 90s
 */
@property(nonatomic, assign)double logSendInterval;

/** optional:  default: "App Store"
 */
@property(nonatomic, copy)NSString *channelId;

/** optional: default: SEND_INTERVAL
 */
@property(nonatomic, assign)eReportPolicy reportPolicy;

/**  SessionID  当前会话id
 */
@property(nonatomic, readonly, copy)NSString *sessionID;

/** IDFA设备唯一标识,如果没有获取到会返回一个格式和idfa不一样的uuid返回，以上都失败则返回@“” */
@property(nonatomic, readonly, copy)NSString *idfa;

/**openUDID 如果没有获取到会返回 @“-1”*/
@property(nonatomic, readonly, copy)NSString *openUDID;

/**当前显示的页面名称，如果不填默认为@“”*/
@property(nonatomic, copy)NSString *currPageName;


//  配置用户信息
- (void)setMemeberUserInfo:(NSDictionary *)userInfo;

@end

@interface PLUAnalytics : NSObject

/** 在application:didFinishLaunchingWithOptions:里被调用监听App启动
 */
+ (void)startWithConfig:(PLUAnalyticsConfig *)config;



/**
 进入房间立即发送心跳，之后30s一次

 @param roomId cd   房间ID
 */
+ (void)enterRoom:(NSString *)roomId;

+ (void)enterRoom:(NSString *)roomId
       attributes:(NSDictionary *)attributes;


/**
 退出房间停止发送心跳
 */
+ (void)exitRoom;


/**
 事件统计.
 @param eventId ec
 @param action ea
 @param label el
 @param value ev
 @param screenName cd
 @param attributes cds
 */
+ (void)event:(NSString *)eventId
       action:(NSString *)action
        label:(NSDictionary *)label
        value:(NSString *)value
       screen:(NSString *)screenName
   attributes:(NSDictionary *)attributes;


/**
 页面统计.

 @param pageName cd
 */
+ (void)logPageView:(NSString *)pageName;


/**
 页面统计.

 @param pageName cd
 @param attributes cds
 */
+ (void)logPageView:(NSString *)pageName
         attributes:(NSDictionary *)attributes;


/**
 社会化分享 统计

 @param socialType sn
 @param actionType sa
 @param content st
 */
+ (void)socialType:(PLUAnalyticsSocialTypeString)socialType
            action:(PLUAnalyticsSocialActionString)actionType
           content:(NSString *)content;


/**
 社会化分享 统计

 @param socialType sn
 @param actionType sa
 @param content st
 @param screenName cd
 @param attributes cds
 */
+ (void)socialType:(PLUAnalyticsSocialTypeString)socialType
            action:(PLUAnalyticsSocialActionString)actionType
           content:(NSString *)content
            screen:(NSString *)screenName
        attributes:(NSDictionary *)attributes;


/**
 异常统计

 @param desc exd
 @param fatal exf  是否严重
 */
+ (void)exception:(NSString *)desc
            fatal:(BOOL)fatal;

/**
 异常统计

 @param desc exd
 @param fatal exf
 @param attributes cds
 */
+ (void)exception:(NSString *)desc
            fatal:(BOOL)fatal
       attributes:(NSDictionary *)attributes;

@end
