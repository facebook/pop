//
//  POPGroupAnimation.h
//  pop
//
//  Created by Alexander Cohen on 2015-09-17.
//  Copyright © 2015 Facebook. All rights reserved.
//

#import <pop/POPAnimation.h>

@class POPAnimation;

/**
 @abstract POPGroupAnimation is a concrete animation subclass for grouped animations.
 */
@interface POPGroupAnimation : POPAnimation

/**
 @abstract Creates and returns an initialized group animation instance.
 @discussion This is the designated initializer.
 @return The initialized group animation instance.
 */
+ (instancetype)animation;

/**
 @abstract The array of POPAnimtions to run in this group.
 */
@property (nonatomic,copy) NSArray* animations;

/**
 @abstract The array of keys for the animations running in this group.
 */
@property (nonatomic,copy,readonly) NSArray* animationKeys;

- (void)addAnimation:(POPAnimation*)animation;

@end
