//
//  DTGPFREImageUtils.h
//  CoreNativeExtension
//
//  Created by Michael Archbold on 20/02/2015.
//  Copyright (c) 2015 distriqt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreNativeExtension/FlashRuntimeExtensions.h>

#if !TARGET_OS_OSX
#import <UIKit/UIKit.h>
#endif



@interface DTFREImageUtils : NSObject

+(NSString*) writeBitmapDataToTmpFile: (FREObject) bitmapDataObject;

#if !TARGET_OS_OSX
+(UIImage*) createUIImageFromBitmapData: (FREBitmapData*) bitmapData;
+(UIImage*) createUIImageFromBitmapData: (FREBitmapData*) bitmapData cacheInternally: (Boolean)cacheBitmapInternally;
+(FREObject) newFREBitmapDataFromUIImage: (UIImage*)image;
#else
//+(NSImage*) createUIImageFromBitmapData: (FREBitmapData*) bitmapData;
//+(NSImage*) createUIImageFromBitmapData: (FREBitmapData*) bitmapData cacheInternally: (Boolean)cacheBitmapInternally;
//+(FREObject) newFREBitmapDataFromUIImage: (NSImage*)image;
#endif


@end

