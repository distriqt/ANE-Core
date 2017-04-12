//
//  DTGPFREImageUtils.h
//  CoreNativeExtension
//
//  Created by Michael Archbold on 20/02/2015.
//  Copyright (c) 2015 distriqt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "FlashRuntimeExtensions.h"


@interface DTFREImageUtils : NSObject

+(NSString*) writeBitmapDataToTmpFile: (FREObject) bitmapDataObject;

+(UIImage*) createUIImageFromBitmapData: (FREBitmapData*) bitmapData;

+(FREObject) newFREBitmapDataFromUIImage: (UIImage*)image;

@end
