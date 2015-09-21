//
//  POPAnimatablePropertyInternal.h
//  pop
//
//  Created by Alexander Cohen on 2015-09-16.
//  Copyright © 2015 Facebook. All rights reserved.
//

#import "POPAnimatableProperty.h"
#import "POPAnimationRuntime.h"

@interface POPAnimatableProperty ()

/**
 @abstract Property accessor.
 @param name The name of the property.
 @param keyPath The keyPath of the property.
 @param valueType The type of objC value of the property.
 @return The animatable property for that keyPath or nil if it can't be created.
 @discussion Used by animations created with keyPaths.
 */
+ (id)propertyWithName:(NSString*)name keyPath:(NSString*)keyPath valueType:(POPValueType)valueType;

@end
