
Core Libraries for the distriqt native extensions.

- iOS: CoreNativeExtension framework 
- Android: corenativeextension.lib 

These are packaged into the Core ANE but we link each ANE against them to provide common functionality.

>
> We are providing these libraries to facilitate ANE developers to build extensions that work 
> alongside each other in the hope of providing a more consistent environment for developing 
> extensions and reducing the integration issues of using ANEs.
>



# iOS 


## Add the framework

In order to use this functionality on iOS you will need to import the framework header:

```objc
#import <CoreNativeExtension/CoreNativeExtension.h>
```


## iOS UIApplicationDelegate 

The most important part on iOS is the application delegate (`UIApplicationDelegate`) functionality 
conversion into notifications which we use for all our ANEs that require `UIApplicationDelegate` functions.
This functionality overrides the default application delegate and creates notifications from the delegate
calls that we can use in multiple native extensions.


The `DTNotifications` class is the central location for this code. In order to use this in your application
you must create an instance of this class in your main context initializer:

```objc
DTNotifications* yourextension_notifications;

void YOUREXTENSIONContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToTest, const FRENamedFunction** functionsToSet)
{

	// Other initialisation functions


	yourextension_notifications = [[DTNotifications alloc] init];
}
```

In order to receive notifications from `DTNotifications` you must set the delegate. 
The delegate should be a class that implements the `DTNotificationsDelegate`.

```objc
@interface YOUREXTENSIONNotificationsController : NSObject <DTNotificationsDelegate>

@end
```

Then you should implement the functions defined in the delegate that you require to listen for:

```objc
@implementation YOUREXTENSIONNotificationsController 


// Other functionality...


#pragma mark DTNotificationsDelegate

-(void) didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	// Process as you would the similar UIApplicationDelegate call
}

@end
```


You set the delegate as below:


```objc
DTNotifications* yourextension_notifications;
YOUREXTENSIONNotificationsController* yourextension_notificationscontroller;

void YOUREXTENSIONContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToTest, const FRENamedFunction** functionsToSet)
{

	// Other initialisation functions

	yourextension_notificationscontroller = [[YOUREXTENSIONNotificationsController alloc] init];

	yourextension_notifications = [[DTNotifications alloc] init];
	yourextension_notifications.delegate = yourextension_notificationscontroller;
}
```



See the `DTNotifications` header for all the available delegate functions, including:

```objc
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
```

All of these are optional, so you can implement only the functions you need.



### Checking launch options

When initialised the `DTNotifications` class tracks the launch options, however you can 
control when your delegate receives the launch notifications by calling `checkLaunchOptions` 
at a specific place in your code.

This allows you to ensure that you can create your notifications delegate in your native 
extension before the `didFinishLaunchingWithOptions` is called. Normally this function would
be called well before your extension is created. 

You will probably need a dedicated native extension function in your extension to call this
to allow the ANE user to have correctly added event handlers etc.


```objc
[yourextension_notifications checkLaunchOptions];
```

Eg:

```objc
FREObject YOUREXTENSIONCheckStartupData( FREContext ctx, void* funcData, uint32_t argc, FREObject argv[] )
{
    @autoreleasepool
    {
        [yourextension_notifications checkLaunchOptions];
    }
    return NULL;
}
```

