//
//  DTFREUtils.h
//  CoreNativeExtension
//
//  Created by Michael Archbold on 27/08/13.
//  Copyright (c) 2013 distriqt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "FlashRuntimeExtensions.h"


#define MAP_FUNCTION(fn, name, data) { (const uint8_t*)(name), (data), &(fn) }

#define SYSTEM_VERSION_LESS_THAN(v) ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)

#define UIColorFromRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]


@interface DTFREUtils : NSObject


+(float) iosVersion;

+(void) log: (NSString*) tag message: (NSString*) message, ...;

+(void) debug: (NSString*) message;


+(void) dispatchStatusEvent: (FREContext) context code: (NSString*) code level: (NSString*) level;

//
//  FREObject HELPERS
//


+(NSString*) getFREObjectAsString: (FREObject) object;
+(int) getFREObjectAsInt: (FREObject) object;
+(Boolean) getFREObjectAsBoolean: (FREObject) object;
+(NSData*) getFREObjectAsNSData: (FREObject) object;
+(double) getFREObjectAsDouble: (FREObject) object;

+(NSArray*) getFREObjectAsArrayOfStrings: (FREObject) source;
+(NSArray*) getFREObjectAsArrayOfNumbers: (FREObject) source;



+(FREObject) newFREObjectFromString: (NSString*) value;
+(FREObject) newFREObjectFromInt: (int) value;
+(FREObject) newFREObjectFromLong: (long) value;
+(FREObject) newFREObjectFromBoolean: (Boolean) value;
+(FREObject) newFREObjectFromDouble: (double) value;
+(FREObject) newFREObjectFromObject: (id) value;

+(FREObject) newFREObjectFromNSUInteger: (NSUInteger) integer;
+(FREObject) newFREObjectFromNSInteger: (NSInteger) integer;
+(FREObject) newFREObjectFromNSNumber: (NSNumber*) value;
+(FREObject) newFREObjectFromNSData: (NSData*) data;

+(FREObject) newFREObject;

+(FREObject) newFREArrayFromStringArray: (NSArray*)array;




+(NSString*) getFREObjectPropertyAsString: (NSString*) property object: (FREObject) object;

+(Boolean) getFREObjectPropertyAsBoolean: (NSString*) property object: (FREObject) object;

+(int32_t) getFREObjectPropertyAsInt: (NSString*) property object: (FREObject) object;

+(double) getFREObjectPropertyAsDouble: (NSString*) property object: (FREObject) object;

+(FREObject) getFREObjectPropertyAsObject: (NSString*) property object: (FREObject) object;



+(FREResult) setFREObjectProperty: (NSString*) property object: (FREObject) object value: (FREObject) value;



//
//  ARRAY CONVERSIONS
//

+(NSDictionary*) keyValueStringFREArraysToNSDictionary: (FREObject) keys values: (FREObject) values;
+(NSDictionary*) keyValueArraysToNSDictionary: (NSArray*) keys values: (NSArray*) values;



//
//  COLOURS
//

+(UIColor*) colorFromRGB: (int) rgbValue;


//
//  VIEW (CONTROLLER) HELPERS
//


+(UIViewController*) getRootViewController;

+(UIViewController*) currentViewController;



//
//  BITMAP HELPERS
//


+(Boolean) drawUIImageToBitmapData: (UIImage*) image bitmapData: (FREBitmapData*) data;

+(Boolean) drawCGImageRefToBitmapData: (CGImageRef) imageRef bitmapData: (FREBitmapData*) bitmapData;


+(UIImage*) createUIImageFromBitmapData: (FREBitmapData*) bitmapData;

+(UIImage*) createUIImageFromBitmapData: (FREBitmapData*) bitmapData scale: (double) scale;


//
//  Base 64
//

+(NSData*) initDataWithString: (NSString*) source;

+(NSString*) base64EncodedStringFromNSData: (NSData*) data;



@end
