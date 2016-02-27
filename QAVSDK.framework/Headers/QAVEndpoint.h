//
//  QAVEndpoint.h
//  QAVSDK
//
//  Created by xianhuan on 15/7/18.
//  Copyright (c) 2015年 xianhuan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QAVSDK/QAVContext.h"

@class QAVContext;

/**
 @brief 请求画面回调block
 */
typedef void (^requestViewBlock)(QAVResult result);

/**
 @brief 请求多个成员的画面回调block
 */
typedef void (^RequestViewListBlock)(QAVResult result);

/**
 @brief 取消多个成员的画面回调block
 */
typedef void (^CancelViewListBlock)(QAVResult result);


/**
 @brief 房间成员的封装类
 */
@interface QAVEndpoint : NSObject{
}

@property(readonly,nonatomic)NSString*identifier;   ///< 房间成员的ID
@property(readonly,nonatomic)BOOL isAudio;      ///< 判断是否为音频模式
@property(readonly,nonatomic)BOOL isCameraVideo;      ///< 判断是否为摄像头视频模式
@property(readonly,nonatomic)BOOL isScreenVideo;      ///< 判断是否为屏幕视频模式



/**
 @brief 请求多个成员的画面
 
 @details 异步返回结果。
 
 @param context 当前的QAVContext实例
 
 @param identifierList 请求的成员列表，传递成员的identifier(NSString*)
 
 @param srcTypeList 请求的成员列表，传递成员的avVideoSrcType(NSNumber*)
 
 @param block 申请的回调

 @return 具体查看QAVError.h
 */
+(int)requsetViewList:(QAVContext*)context identifierList:(NSArray*)identifierList srcTypeList:(NSArray*)srcTypeList ret:(RequestViewListBlock)block;

/**
 @brief 取消多个成员的画面
 
 @details 异步返回结果。
 
 @param context 当前的QAVContext实例
 
 @param list 取消的成员列表，传递成员的identifier(NSString*)
 
 @param block 申请的回调
 
 @return 具体查看QAVError.h
 */
+(int)cancelAllview:(QAVContext*)context ret:(CancelViewListBlock)block;

/**
 @brief 请求成员的视频画面。
 
 @details 异步返回结果。不同AVEndpoint对象的请求画面操作不是互斥的，既可以请求成员A的画面，也可以请求成员B的画面，但同一个时间点只能请求一个成员的画面。
 即必须等待异步结果返回后，才能进行新的请求画面操作。在请求画面前最好检查该成员是否有对应的视频源。
 
 @param block 返回请求视频画面是成功还是失败。
 
 @return QAV_OK表示调用成功，其他值表示失败：
 
 @remark
 － RequestView和CancelView不能并发执行，即同一时间点只能进行一种操作。
 － RequestView和CancelView配对使用。
 */
-(QAVResult)requestView:(requestViewBlock)block;

/**
 @brief 取消请求成员的视频画面。
 
 @details 和RequestView对应的逆操作，约束条件和RequestView一样。
 @param block 申请的回调
 @return QAV_OK表示调用成功，其他值表示失败：
 
 @remark
 － RequestView和CancelView不能并发执行，即同一时间点只能进行一种操作。
 － RequestView和CancelView配对使用。
 */
-(QAVResult)cancelView:(requestViewBlock)block;


@end
