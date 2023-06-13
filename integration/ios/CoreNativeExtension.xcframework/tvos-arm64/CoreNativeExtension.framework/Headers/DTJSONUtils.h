//
//  DTJSONUtils.h
//  CoreNativeExtension
//
//  Created by Michael Archbold on 29/5/2023.
//  Copyright © 2023 distriqt. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DTJSONUtils : NSObject


+(NSString*) dictToJSONString: (NSDictionary*)dict;

+(NSDictionary*) jsonStringToDict: (NSString*)jsonString;


@end

NS_ASSUME_NONNULL_END
