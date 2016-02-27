//
//  videoDef.h
//  QAVSDK
//
//  Created by xianhuanlin on 15/6/4.
//  Copyright (c) 2015年 xianhuan. All rights reserved.
//

#ifndef QAVSDK_videoDef_h
#define QAVSDK_videoDef_h
#import <Foundation/Foundation.h>
#import "QAVError.h"

/// 视频流的色彩格式
typedef NS_ENUM(NSInteger, avColorFormats){
    AVCOLOR_FORMAT_I420	= 0,  /// AVCOLOR_FORMAT_I420 色彩格式只支持I420。
};

/// 视频源类型。
typedef NS_ENUM(NSInteger, avVideoSrcType){
    QAVVIDEO_SRC_TYPE_NONE	= 0, /// AVVIDEO_SRC_TYPE_NONE 默认值，无意义。
    QAVVIDEO_SRC_TYPE_CAMERA	= 1, /// AVVIDEO_SRC_TYPE_CAMERA 摄像头。
    QAVVIDEO_SRC_TYPE_SCREEN	= 2, /// AVVIDEO_SRC_TYPE_SCREEN 屏幕。
};

/**
 @brief 视频帧描述
 */

@interface QAVFrameDesc:NSObject{
    
}

//详情见avColorFormats的定义。

@property(assign,nonatomic) UInt32 width; ///< 宽度，单位：像素。
@property(assign,nonatomic) UInt32  height; ///< 高度，单位：像素。

/**
 @brief 画面旋转的角度：
 - source_type为AVVIDEO_SRC_TYPE_CAMERA时，表示视频源为摄像头。
 在终端上，摄像头画面是支持旋转的，App需要根据旋转角度调整渲染层的处理，以保证画面的正常显示。
 - source_type为其他值时，rotate恒为0。
 */
@property(assign,nonatomic)int rotate;

@property(assign, nonatomic) avColorFormats color_format; ///< 色彩格式，
@property(assign,nonatomic)avVideoSrcType srcType; ///< 视频源类型，详情见
@end

/// 视频帧
@interface QAVVideoFrame : NSObject{
}

@property(retain,nonatomic) QAVFrameDesc*frameDesc; ///< 视频帧描述
@property(copy, nonatomic) NSString*identifier; ///< 视频帧所属的房间成员ID。
@property(assign, nonatomic)UInt32 dataSize;    ///< 视频帧的数据缓冲区大小，单位：字节。
@property(assign,nonatomic) UInt8* data;    ///< 视频帧的数据缓冲区，SDK内部会管理缓冲区的分配和释放。
@property(assign, nonatomic)UInt64 roomID;  ///< 视频帧所属的房间成员ID。

@end

/**
 @brief 摄像头信息
 */
@interface  QAVCameraInfo:NSObject{
}
@property(copy, nonatomic) NSString *deviceID; ///< 设备ID
@property(assign, nonatomic)NSInteger width;  ///< 采集画面宽度
@property(assign, nonatomic)NSInteger height; ///< 采集画面高度
@property(assign, nonatomic)NSInteger fps; ///< 采集帧率

@end






/**
 @brief 音频数据透传类型
 */
typedef NS_ENUM(NSInteger, QAVAudioDataSourceType){
    QAVAudioDataSource_Mic = 0, ///麦克风输出
    QAVAudioDataSource_MixToSend = 1, ///发送混音输入
    QAVAudioDataSource_Send = 2, ///发送输出
    QAVAudioDataSource_MixToPlay = 3, ///扬声器混音输入
    QAVAudioDataSource_Play = 4, ///扬声器输出
    QAVAudioDataSource_NetStream = 5, ///扬声器远端用户声音输出
    QAVAudioDataSource_End = 6,
};

/**
 @brief 音频帧描述
 */
struct QAVAudioFrameDesc {
    NSInteger SampleRate; ///< 采样率，单位：赫兹（Hz）。
    NSInteger ChannelNum; ///< 通道数，1表示单声道（mono），2表示立体声
    NSInteger Bits;       ///< 音频的位宽，目前只能填16
};

/// 音频帧
@interface QAVAudioFrame : NSObject{
    
}
@property(copy, nonatomic)NSString*identifier; ///< 音频帧所属的房间成员ID。
@property(assign, nonatomic)struct QAVAudioFrameDesc desc;///< 音频帧描述。
@property(retain, nonatomic)NSData* buffer;///< 音频帧的数据缓冲区大小

@end



/// 音视频房间类型
typedef NS_ENUM(NSInteger, avRoomType){
    ROOM_TYPE_PAIR = 1, /// ROOM_TYPE_PAIR 双人音视频房间。
    ROOM_TYPE_MULTI, /// ROOM_TYPE_MULTI 多人音视频房间。
};

/// 音视频通话模式
typedef NS_ENUM(NSInteger, avRoomMode){
    MODE_AUDIO = 0, /// MODE_AUDIO 纯语音通话，双方都不能进行视频上下行。
    MODE_VIDEO = 1, /// MODE_VIDEO 音视频通话，对视频上下行没有约束。
};

/// 音视频场景策略。
typedef NS_ENUM(NSInteger, avAudioCategory){
    CATEGORY_VOICECHAT = 0, /// CATEGORY_VOICECHAT VoIP模式。适合于实时音频通信场景，如实时语音通话。
    CATEGORY_MEDIA_PLAY_AND_RECORD = 1, /// CATEGORY_MEDIA_PLAY_AND_RECORD 媒体采集与播放模式。适合于那些对音质要求比较高的直播场景，如主播场景中的主播人员。
    CATEGORY_MEDIA_PLAYBACK = 2, /// CATEGORY_MEDIA_PLAYBACK 媒体播放模式。适合于那些对音质要求比较高的直播场景，如主播场景中的听众。
};


/// 输出类型
typedef NS_ENUM(NSInteger, QAVOutputMode){
    QAVOUTPUTMODE_EARPHONE = 0,     /// QAVOUTPUTMODE_EARPHONE 输出类型为耳机模式
    QAVOUTPUTMODE_SPEAKER,     /// QAVOUTPUTMODE_SPEAKER 输出类型为扬声器模式
};

/// 音视频事件更新
typedef NS_ENUM(NSInteger, QAVUpdateEvent){
    QAV_EVENT_ID_NONE = 0,                  /// QAV_EVENT_ID_NONE 无。
    QAV_EVENT_ID_ENDPOINT_ENTER = 1,        /// QAV_EVENT_ID_ENDPOINT_ENTER 进入房间事件。
    QAV_EVENT_ID_ENDPOINT_EXIT = 2,         /// QAV_EVENT_ID_ENDPOINT_EXIT 退出房间事件。
    QAV_EVENT_ID_ENDPOINT_HAS_CAMERA_VIDEO = 3,    /// QAV_EVENT_ID_ENDPOINT_HAS_CAMERA_VIDEO 有发摄像头视频事件。
    QAV_EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO = 4,     /// QAV_EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO 无发摄像头视频事件。
    QAV_EVENT_ID_ENDPOINT_HAS_AUDIO = 5,    /// QAV_EVENT_ID_ENDPOINT_HAS_AUDIO 有发语音事件。
    QAV_EVENT_ID_ENDPOINT_NO_AUDIO = 6,     /// QAV_EVENT_ID_ENDPOINT_NO_AUDIO 无发语音事件。
    QAV_EVENT_ID_ENDPOINT_HAS_SCREEN_VIDEO = 7,    /// QAV_EVENT_ID_ENDPOINT_HAS_SCREEN_VIDEO 有发屏幕视频事件。
    QAV_EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO = 8,     /// QAV_EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO 无发屏幕视频事件。
};


/**
 @brief 房间参数

 */
@interface QAVRoomParam: NSObject{
    
}
@property(assign, nonatomic)avRoomType roomtype;    ///< 音视频房间类型
@end



/**
 @brief 多人房间参数
 
 */
@interface QAVMultiParam : QAVRoomParam{
    
}
@property(assign, nonatomic)avAudioCategory audioCategory; ///< 音视频场景策略，多人房间专用。
@property(assign, nonatomic)UInt32 roomID;    ///< App指定的房间ID。

//advance property
@property(assign, nonatomic)UInt64 authBitMap;///< 音视频权限位。
@property(copy, nonatomic)NSData*authBuffer;  ///< 音视频权限加密串。
@property(copy, nonatomic)NSString*controlRole; ///< 角色名，web端音视频参数配置工具所设置的角色名。

@end

//权限位
#define QAV_AUTH_BITS_DEFUALT     0xFFFFFFFFFFFFFFFF ///< 缺省值。拥有所有权限。
#define QAV_AUTH_BITS_CREATE_ROOM 0x00000001 ///< 创建房间权限。
#define QAV_AUTH_BITS_JOIN_ROOM   0x00000002 ///< 加入房间的权限。
#define QAV_AUTH_BITS_SEND_AUDIO  0x00000004 ///< 发送语音的权限。
#define QAV_AUTH_BITS_RECV_AUDIO  0x00000008 ///< 接收语音的权限。
#define QAV_AUTH_BITS_SEND_VIDEO  0x00000010 ///< 发送视频的权限。
#define QAV_AUTH_BITS_RECV_VIDEO  0x00000020 ///< 接收视频的权限。
#define QAV_AUTH_BITS_SEND_SUB    0x00000040 ///< 发送辅路视频的权限。暂不支持辅路。
#define QAV_AUTH_BITS_RECV_SUB    0x00000080 ///< 接收辅路视频的权限。暂不支持辅路。

#endif
