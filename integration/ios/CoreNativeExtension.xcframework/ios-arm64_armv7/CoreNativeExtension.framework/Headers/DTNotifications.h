//
//  DTNotifications.h
//  CoreNativeExtension
//
//  Created by Michael Archbold on 27/02/2015.
//  Copyright (c) 2015 distriqt. All rights reserved.
//

#import <Foundation/Foundation.h>

#if !TARGET_OS_OSX


#import <UIKit/UIKit.h>

#define DTCoreDidRegisterForRemoteNotificationsWithDeviceTokenNotification  @"dtCoreDidRegisterForRemoteNotificationsWithDeviceTokenNotification"
#define DTCoreDidFailToRegisterForRemoteNotificationsWithErrorNotification  @"dtCoreDidFailToRegisterForRemoteNotificationsWithErrorNotification"

#define DTCoreDidReceiveRemoteNotificationNotification  @"dtCoreDidReceiveRemoteNotificationNotification"
#define DTCoreDidReceiveRemoteNotificationFetchCompletionHandlerNotification  @"dtCoreDidReceiveRemoteNotificationFetchCompletionHandlerNotification"
#define DTCoreHandleActionWithIdentifierForRemoteNotificationCompletionHandlerNotification  @"dtCoreHandleActionWithIdentifierForRemoteNotificationCompletionHandlerNotification"
#define DTCoreDidReceiveLocalNotificationNotification  @"dtCoreDidReceiveLocalNotificationNotification"
#define DTCoreHandleActionWithIdentifierForLocalNotificationCompletionHandlerNotification  @"dtCoreHandleActionWithIdentifierForLocalNotificationCompletionHandlerNotification"

#define DTCoreDidFinishLaunchingWithOptionsNotification  @"dtCoreDidFinishLaunchingWithOptionsNotification"
#define DTCoreApplicationContinueUserActivityNotification @"dtCoreApplicationContinueUserActivityNotification"
#define DTCoreDidRegisterUserNotificationSettingsNotification  @"dtCoreDidRegisterUserNotificationSettingsNotification"
#define DTCoreOpenURLNotification  @"dtCoreOpenURLNotification"
#define DTCoreOpenURLOptionsNotification @"dtCoreOpenURLOptionsNotification"
#define DTCorePerformActionForShortcutItemNotification @"dtCorePerformActionForShortcutItemNotification"


#define DTCoreRequestUserNotificationDelegateEventNotification @"dtCoreRequestUserNotificationDelegateEventNotification"
#define DTCoreUserNotificationWillPresentNotification @"dtCoreUserNotificationWillPresentNotification"
#define DTCoreUserNotificationDidReceiveResponseNotification @"dtCoreUserNotificationDidReceiveResponseNotification"

#define DTCoreUserNotificationWillPresentResultNotification @"dtCoreUserNotificationWillPresentResultNotification"
#define DTCoreUserNotificationDidReceiveResponseResultNotification @"dtCoreUserNotificationDidReceiveResponseResultNotification"



@protocol DTNotificationsDelegate <NSObject>

@optional


-(void) didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
#if !TARGET_OS_TV
-(void) didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings;
#endif
-(void) didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

-(void) didReceiveRemoteNotification:(NSDictionary*)userInfo;
-(void) didReceiveRemoteNotification:(NSDictionary*)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler;
-(void) handleActionWithIdentifier: (NSString*)identifier forRemoteNotification: (NSDictionary*)notification completionHandler:(void(^)(void))handler;

#if !TARGET_OS_TV
-(void) didReceiveLocalNotification:(UILocalNotification*)notification;
-(void) handleActionWithIdentifier: (NSString*)identifier forLocalNotification: (UILocalNotification*)notification completionHandler:(void(^)(void))handler;
#endif

-(void) didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
-(void) continueUserActivity: (NSUserActivity*)userActivity;
-(void) openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;
-(void) openURL:(NSURL *)url options: (NSDictionary*)options;
#if !TARGET_OS_TV
-(void) performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem completionHandler:(void(^)(BOOL))handler;
#endif

@end


@interface DTNotifications : NSObject

@property (nonatomic, weak) id<DTNotificationsDelegate> delegate;


-(void) checkLaunchOptions;

-(void) addObservers;
-(void) removeObservers;


@end




#endif
