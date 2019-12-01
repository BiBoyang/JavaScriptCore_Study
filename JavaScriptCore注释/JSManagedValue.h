#ifndef JSManagedValue_h
#define JSManagedValue_h

#import <JavaScriptCore/JSBase.h>
#import <JavaScriptCore/WebKitAvailability.h>

#if JSC_OBJC_API_ENABLED

@class JSValue;
@class JSContext;

/*!
@interface
@discussion JSManagedValue represents a "conditionally retained" JSValue.
 "Conditionally retained" means that as long as the JSManagedValue's
 JSValue is reachable through the JavaScript object graph,
 or through the Objective-C object graph reported to the JSVirtualMachine using
 addManagedReference:withOwner:, the corresponding JSValue will
 be retained. However, if neither graph reaches the JSManagedValue, the
 corresponding JSValue will be released and set to nil.

The primary use for a JSManagedValue is to store a JSValue in an Objective-C
or Swift object that is exported to JavaScript. It is incorrect to store a JSValue
in an object that is exported to JavaScript, since doing so creates a retain cycle.
*/
NS_CLASS_AVAILABLE(10_9, 7_0)
@interface JSManagedValue : NSObject

/*!
@method
@abstract Create a JSManagedValue from a JSValue.
@result The new JSManagedValue.
*/
+ (JSManagedValue *)managedValueWithValue:(JSValue *)value;
+ (JSManagedValue *)managedValueWithValue:(JSValue *)value andOwner:(id)owner API_AVAILABLE(macos(10.10), ios(8.0));

/*!
@method
@abstract Create a JSManagedValue.
@result The new JSManagedValue.
*/
- (instancetype)initWithValue:(JSValue *)value;

/*!
@property
@abstract Get the JSValue from the JSManagedValue.
@result The corresponding JSValue for this JSManagedValue or
 nil if the JSValue has been collected.
*/
@property (readonly, strong) JSValue *value;

@end

#endif // JSC_OBJC_API_ENABLED

#endif // JSManagedValue_h

