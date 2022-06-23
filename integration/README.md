
Core Libraries for the distriqt native extensions.

- iOS/tvOS/macOS: 
  -  `CoreNativeExtension.xcframework` 
- Android: 
  - `corenativeextension.android.lib.air.jar` : AIR common interfaces for activity state callbacks
  - `corenativeextension.android.lib.jar` : 

These are packaged into the Core ANE but we link each ANE against them to provide common functionality.

>
> We are providing these libraries to facilitate ANE developers to build extensions that work 
> alongside each other in the hope of providing a more consistent environment for developing 
> extensions and reducing the integration issues of using ANEs.
>


# Packaging

It is important that you **do not** package these libraries in your extension.

You should instead include the [`Core` extension](https://github.com/distriqt/ANE-Core) in your application which contains these libraries (iOS frameworks and android jars).



# iOS/tvOS/macOS 


## Add the xcframework

Firstly drag the xcframework into your Xcode project and include it in your build.

Then import the framework header to expose the framework's functionality:

```objc
#import <CoreNativeExtension/CoreNativeExtension.h>
```


## `UIApplicationDelegate` 

The most important part for most developers is the application delegate (`UIApplicationDelegate`) functionality. This converts the delegate methods calls into notifications which we use for all our extensions that require `UIApplicationDelegate` functions and allows multiple extensions to access this same functionality. 

The `DTNotifications` class is the central location for this code. In order to use this in your application you must create an instance of this class in your main context initializer:

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

When initialised the `DTNotifications` class tracks the launch options, however you can control when your delegate receives the launch notifications by calling `checkLaunchOptions` at a specific place in your code.

This allows you to ensure that you can create your notifications delegate in your native extension and setup any SDKs you are using before the `didFinishLaunchingWithOptions` is called. Normally this function would be called well before your extension is created. 

You will probably need a dedicated native extension function in your extension to call this to allow the ANE user to have correctly added event handlers etc. This is not a requirement, we often bundle the call of this in a particular call of the extension, eg when a developer calls something like `MyExtension.instance.initialiseSDK()`. 

The important thing to note is that calling this function will result in the `didFinishLaunchingWithOptions` method in your delegate being called with the launch options.

```objc
[yourextension_notifications checkLaunchOptions];
```

For example, calling it in a dedicated function:

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


## Usage

You must ensure your developers call `Core.init();` some point in their application before initialising your extension.

This call is responsible for initialising the UIApplicationDelegate and without calling it, none of the above functionality will work.



# Android 

## Activity State 

If you use any of the activity state callbacks from AIR you should include the `corenativeextension.android.lib.air.jar` in your Android project and link against the AIR classes exposed there. This will avoid conflicts.

This library contains:

- `com.adobe.air.ActivityResultCallback`
- `com.adobe.air.StateChangeCallback`
- `com.adobe.air.InputEventCallback`

If you utilise any of these interfaces then we suggest you use this library instead of defining them in your own code.

