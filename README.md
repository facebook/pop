![pop](https://github.com/facebook/pop/blob/master/Images/pop.gif?raw=true)

Pop is an extensible animation engine for iOS and OS X. In addition to basic static animations, it supports spring and decay dynamic animations, making it useful for building realistic, physics-based interactions. The API allows quick integration with existing Objective-C codebases and enables the animation of any property on any object. It's a mature and well-tested framework that drives all the animations and transitions in [Paper](http://www.facebook.com/paper).

## Installation

Pop will soon be available via CocoaPods. Add the following to your project Podfile:

```ruby
pod 'pop'
```
Alternatively, you can add the project to your workspace and adopt the provided configuration files or manually copy the files under the pop subdirectory into your project.

## Usage

Pop adopts the Core Animation explicit animation programming model. Use by including the following import:

```objective-c
#import <POP/POP.h>
```

### Start, Stop & Update

To start an animation, add it to the object you wish to animate:

```objective-c
POPSpringAnimation *anim = [POPSpringAnimation animation];
...
[layer pop_addAnimation:anim forKey:@"myKey"];
```

To stop an animation, remove it from the object referencing the key specified on start:

```objective-c
[layer pop_removeAnimationForKey:@"myKey"];
```

The key can also be used to query for the existence of an animation. Updating the toValue of a running animation can provide the most seamless way to change course:

```objective-c
anim = [layer pop_animationForKey:@"myKey"];
if (anim) {
  /* update to value to new destination */
  anim.toValue = @(42.0);
} else {
  /* create and start a new animation */
  ....
}
```

While a layer was used in the above examples, the Pop interface is implemented as a category addition on NSObject. Any NSObject or subclass can be animated.

### Types

There are four concrete animation types: spring, decay, basic and custom.

Spring animations can be used to give objects a delightful bounce. In this example, we using a spring animation to animates a layer's bounds from its current value to (0, 0, 400, 400):

```objective-c
POPSpringAnimation *anim = [POPSpringAnimation animationWithPropertyNamed:kPOPLayerBounds];
anim.toValue = [NSValue valueWithCGRect:CGRectMake(0, 0, 400, 400)];
[layer pop_addAnimation:anim forKey:@"size"];
```
Decay animations can be used to gradually slow an object to a halt. In this example, we decay a layer's positionX from it's current value and velocity 1000pts per second:

```objective-c
POPDecayAnimation *anim = [POPDecayAnimation animationWithPropertyNamed:kPOPLayerPositionX];
anim.velocity = @(1000.);
[layer pop_addAnimation:anim forKey:@"slide"];
```

Basic animations can be used to interpolate values over a specified time period. To use an ease-in ease-out animation to animate a view's alpha from 0.0 to 1.0 over the default duration:
```objective-c
POPBasicAnimation *anim = [POPBasicAnimation animationWithPropertyNamed:kPOPViewAlpha];
anim.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
anim.fromValue = @(0.0);
anim.toValue = @(1.0);
[view pop_addAnimation:anim forKey:@"slide"];
```
`POPCustomAnimation` makes creating custom animations and transitions easier by handling CADisplayLink and associated time-step management. See header for more details.


### Properties

The property animated is specified by the `POPAnimatableProperty` class. In this example we create a spring animation and explicitly set the animatable property corresponding to `-[CALayer bounds]`:

```objective-c
POPSpringAnimation *anim = [POPSpringAnimation animation];
anim.property = [POPAnimatableProperty propertyWithName:kPOPLayerBounds];
```

The framework provides many common layer and view animatable properties out of box. You can animate a custom property by creating a new instance of the class. In this example, we declare a custom volume property:

```objective-c
prop = [POPAnimatableProperty propertyWithName:@"com.foo.radio.volume" initializer:^(POPMutableAnimatableProperty *prop) {
  // read value
  prop.readBlock = ^(id obj, CGFloat values[]) {
    values[0] = [obj volume];
  };
  // write value
  prop.writeBlock = ^(id obj, const CGFloat values[]) {
    [obj setVolume:values[0]];
  };
  // dynamics threshold
  prop.threshold = 0.01;
}];

anim.property = prop;
```

For a complete listing of provided animatable properties, as well more information on declaring custom properties see `POPAnimatableProperty.h`.


### Debugging

Here are a few tips when debugging. Pop obeys the Simulator's Toggle Slow Animations setting. Try enabling it to slow down animations and more easily observe interactions.

Consider naming your animations. This will allow you to more easily identify them when referencing them, either via logging or in the debugger:

```objective-c
anim.name = @"springOpen";
```

Each animation comes with an associated tracer. The tracer allows you to record all animation-related events, in a fast and efficient manner, allowing you to query and analyze them after animation completion. The below example starts the tracer and configures it to log all events on animation completion:

```objective-c
POPAnimationTracer *tracer = anim.tracer;
tracer.shouldLogAndResetOnCompletion = YES;
[tracer start];
```

See `POPAnimationTracer.h` for more details.

## Testing

Pop has extensive unit test coverage. To install test dependencies, navigate to the root pop directory and type:

```sh
pod install
```

Assuming CocoaPods is installed, this will include the necessary OCMock dependency to the unit test targets.

## Contributing
See the CONTRIBUTING file for how to help out.

## Licence

Pop is released under a BSD License. See LICENSE file for details.
