
#import <JavaScriptCore/JavaScriptCore.h>

#if JSC_OBJC_API_ENABLED

/*!
@interface
@discussion An instance of JSVirtualMachine represents a single JavaScript "object space"
 or set of execution resources. Thread safety is supported by locking the
 virtual machine, with concurrent JavaScript execution supported by allocating
 separate instances of JSVirtualMachine.

 A virtual machine may need to run deferred tasks on a run loop, such as garbage collection
 or resolving WebAssembly compilations. By default, a virtual machine will use the run loop
 of the thread it was initialized on. Currently, there is no API to change a
 JSVirtualMachine's run loop once it has been initialized.
*/
NS_CLASS_AVAILABLE(10_9, 7_0)
@interface JSVirtualMachine : NSObject

/*!
@methodgroup Creating New Virtual Machines
*/
/*!
@method
@abstract Create a new JSVirtualMachine.
*/
- (instancetype)init;

/*!
@methodgroup Memory Management
*/
/*!
@method
@abstract Notify the JSVirtualMachine of an external object relationship.
@discussion Allows clients of JSVirtualMachine to make the JavaScript runtime aware of
 arbitrary external Objective-C object graphs. The runtime can then use
 this information to retain any JavaScript values that are referenced
 from somewhere in said object graph.

 For correct behavior clients must make their external object graphs
 reachable from within the JavaScript runtime. If an Objective-C object is
 reachable from within the JavaScript runtime, all managed references
 transitively reachable from it as recorded using
 -addManagedReference:withOwner: will be scanned by the garbage collector.
@param object The object that the owner points to.
@param owner The object that owns the pointed to object.
*/
- (void)addManagedReference:(id)object withOwner:(id)owner;

/*!
@method
@abstract Notify the JSVirtualMachine that a previous object relationship no longer exists.
@discussion The JavaScript runtime will continue to scan any references that were
 reported to it by -addManagedReference:withOwner: until those references are removed.
@param object The object that was formerly owned.
@param owner The former owner.
*/
- (void)removeManagedReference:(id)object withOwner:(id)owner;

@end

#endif

