//
//  DTNotifications.h
//  CoreNativeExtension
//
//  Created by Michael Archbold on 27/02/2015.
//  Copyright (c) 2015 distriqt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


#define DTCoreDidRegisterForRemoteNotificationsWithDeviceTokenNotification  @"dtCoreDidRegisterForRemoteNotificationsWithDeviceTokenNotification"
#define DTCoreDidFailToRegisterForRemoteNotificationsWithErrorNotification  @"dtCoreDidFailToRegisterForRemoteNotificationsWithErrorNotification"

#define DTCoreDidReceiveRemoteNotificationNotification  @"dtCoreDidReceiveRemoteNotificationNotification"
#define DTCoreDidReceiveRemoteNotificationFetchCompletionHandlerNotification  @"dtCoreDidReceiveRemoteNotificationFetchCompletionHandlerNotification"
#define DTCoreHandleActionWithIdentifierForRemoteNotificationCompletionHandlerNotification  @"dtCoreHandleActionWithIdentifierForRemoteNotificationCompletionHandlerNotification"
#define DTCoreDidReceiveLocalNotificationNotification  @"dtCoreDidReceiveLocalNotificationNotification"
#define DTCoreHandleActionWithIdentifierForLocalNotificationCompletionHandlerNotification  @"dtCoreHandleActionWithIdentifierForLocalNotificationCompletionHandlerNotification"

#define DTCoreDidFinishLaunchingWithOptionsNotification  @"dtCoreDidFinishLaunchingWithOptionsNotification"
#define DTCoreDidRegisterUserNotificationSettingsNotification  @"dtCoreDidRegisterUserNotificationSettingsNotification"
#define DTCoreOpenURLNotification  @"dtCoreOpenURLNotification"
#define DTCoreOpenURLOptionsNotification @"dtCoreOpenURLOptionsNotification"
#define DTCorePerformActionForShortcutItemNotification @"dtCorePerformActionForShortcutItemNotification"


@protocol DTNotificationsDelegate <NSObject>

@optional


-(void) didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
-(void) didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings;
-(void) didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

-(void) didReceiveRemoteNotification:(NSDictionary*)userInfo;
-(void) didReceiveRemoteNotification:(NSDictionary*)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler;
-(void) handleActionWithIdentifier: (NSString*)identifier forRemoteNotification: (NSDictionary*)notification;

-(void) didReceiveLocalNotification:(UILocalNotification*)notification;
-(void) handleActionWithIdentifier: (NSString*)identifier forLocalNotification: (UILocalNotification*)notification;

-(void) didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
-(void) openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;
-(void) openURL:(NSURL *)url options: (NSDictionary*)options;
-(void) performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem;


@end


@interface DTNotifications : NSObject

@property (nonatomic, weak) id<DTNotificationsDelegate> delegate;


-(void) checkLaunchOptions;

-(void) addObservers;
-(void) removeObservers;


@end




