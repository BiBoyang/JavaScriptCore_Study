#ifndef JSBase_h
#define JSBase_h

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

/* JavaScript engine interface */

/*! @typedef JSContextGroupRef A group that associates JavaScript contexts with one another. Contexts in the same group may share and exchange JavaScript objects. */
/* 一个将JavaScript上下文相互关联的组。同一组中的上下文可以共享和交换JavaScript对象。 */
typedef const struct OpaqueJSContextGroup* JSContextGroupRef;

/*! @typedef JSContextRef A JavaScript execution context. Holds the global object and other execution state. */
/* 一个JavaScript的执行上下文。保存全局对象和其他执行状态 */
typedef const struct OpaqueJSContext* JSContextRef;

/*! @typedef JSGlobalContextRef A global JavaScript execution context. A JSGlobalContext is a JSContext. */
/*  一个全局 JavaScript 执行上下文.一个JSGlobalContext就是一个JSContext.  */
typedef struct OpaqueJSContext* JSGlobalContextRef;

/*! @typedef JSStringRef A UTF16 character buffer. The fundamental string representation in JavaScript. */
/* 一个UTF16字符缓冲区。JavaScript中的基本字符串表示。 */
typedef struct OpaqueJSString* JSStringRef;

/*! @typedef JSClassRef A JavaScript class. Used with JSObjectMake to construct objects with custom behavior. */
/*

JSClassRef一个JavaScript类。与JSObjectMake一起用于构造具有自定义行为的对象。  */
typedef struct OpaqueJSClass* JSClassRef;

/*! @typedef JSPropertyNameArrayRef An array of JavaScript property names. */
/* JSPropertyNameArrayRef一个JavaScript属性名数组 */
typedef struct OpaqueJSPropertyNameArray* JSPropertyNameArrayRef;

/*! @typedef JSPropertyNameAccumulatorRef An ordered set used to collect the names of a JavaScript object's properties. */
/*  用于收集JavaScript对象属性名称的有序集合。 */
typedef struct OpaqueJSPropertyNameAccumulator* JSPropertyNameAccumulatorRef;

/*! @typedef JSTypedArrayBytesDeallocator A function used to deallocate bytes passed to a Typed Array constructor. The function should take two arguments. The first is a pointer to the bytes that were originally passed to the Typed Array constructor. The second is a pointer to additional information desired at the time the bytes are to be freed. */
/*  用于释放传递给类型化数组构造函数的字节的函数。函数应该有两个参数。第一个是指向最初传递给类型化数组构造函数的字节的指针。第二个是指向释放字节时所需的附加信息的指针。  */
typedef void (*JSTypedArrayBytesDeallocator)(void* bytes, void* deallocatorContext);

/* JavaScript data types */

/*! @typedef JSValueRef A JavaScript value. The base type for all JavaScript values, and polymorphic functions on them. */
/*  一个JavaScript值。所有JavaScript值的基类型及其上的多态函数  */
typedef const struct OpaqueJSValue* JSValueRef;

/*! @typedef JSObjectRef A JavaScript object. A JSObject is a JSValue. */
/*  一个JavaScript对象。JSObject是JSValue。  */
typedef struct OpaqueJSValue* JSObjectRef;

/* Clang's __has_declspec_attribute emulation */
/* https://clang.llvm.org/docs/LanguageExtensions.html#has-declspec-attribute */

#ifndef __has_declspec_attribute
#define __has_declspec_attribute(x) 0
#endif

/* JavaScript symbol exports */
/* These rules should stay the same as in WebKit/Shared/API/c/WKDeclarationSpecifiers.h */
/*  */
#undef JS_EXPORT
#if defined(JS_NO_EXPORT)
#define JS_EXPORT
#elif defined(WIN32) || defined(_WIN32) || defined(__CC_ARM) || defined(__ARMCC__) || (__has_declspec_attribute(dllimport) && __has_declspec_attribute(dllexport))
#if defined(BUILDING_JavaScriptCore) || defined(STATICALLY_LINKED_WITH_JavaScriptCore)
#define JS_EXPORT __declspec(dllexport)
#else
#define JS_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__)
#define JS_EXPORT __attribute__((visibility("default")))
#else /* !defined(JS_NO_EXPORT) */
#define JS_EXPORT
#endif /* defined(JS_NO_EXPORT) */

#ifdef __cplusplus
extern "C" {
#endif

/* Script Evaluation */

/*!
@function JSEvaluateScript
@abstract Evaluates a string of JavaScript.
|-- 解析一个JavaScript字符
@param ctx The execution context to use.
|-- 要被用到的上下
@param script A JSString containing the script to evaluate.
|-- 包含要计算的脚本的JSString
@param thisObject The object to use as "this," or NULL to use the global object as "this."
|-- 用作this的对象，或者NULL作为this去使用全局对象
@param sourceURL A JSString containing a URL for the script's source file. This is used by debuggers and when reporting exceptions. Pass NULL if you do not care to include source file information.
|-- 包含脚本源文件的URL的JSString。调试程序和报告异常时都会使用此选项。如果不想包含源文件信息，请传递NULL。
@param startingLineNumber An integer value specifying the script's starting line number in the file located at sourceURL. This is only used when reporting exceptions. The value is one-based, so the first line is line 1 and invalid values are clamped to 1.
|-- 一个整数值，指定位于sourceURL的文件中脚本的起始行号。这仅在报告异常时使用。该值是基于一的，因此第一行是第1行，无效值被钳制为1。
@param exception A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
|-- 指向JSValueRef的指针，在其中存储异常（如果有）。如果不想存储异常，请传递NULL。
@result The JSValue that results from evaluating script, or NULL if an exception is thrown.
|-- 对脚本求值的JSValue，如果抛出异常，则为空。
 */

/*  */
JS_EXPORT JSValueRef JSEvaluateScript(JSContextRef ctx, JSStringRef script, JSObjectRef thisObject, JSStringRef sourceURL, int startingLineNumber, JSValueRef* exception);

/*!
@function JSCheckScriptSyntax
@abstract Checks for syntax errors in a string of JavaScript.
@param ctx The execution context to use.
@param script A JSString containing the script to check for syntax errors.
@param sourceURL A JSString containing a URL for the script's source file. This is only used when reporting exceptions. Pass NULL if you do not care to include source file information in exceptions.
@param startingLineNumber An integer value specifying the script's starting line number in the file located at sourceURL. This is only used when reporting exceptions. The value is one-based, so the first line is line 1 and invalid values are clamped to 1.
@param exception A pointer to a JSValueRef in which to store a syntax error exception, if any. Pass NULL if you do not care to store a syntax error exception.
@result true if the script is syntactically correct, otherwise false.
*/
/*  */
JS_EXPORT bool JSCheckScriptSyntax(JSContextRef ctx, JSStringRef script, JSStringRef sourceURL, int startingLineNumber, JSValueRef* exception);

/*!
@function JSGarbageCollect
@abstract Performs a JavaScript garbage collection.
@param ctx The execution context to use.
@discussion JavaScript values that are on the machine stack, in a register,
 protected by JSValueProtect, set as the global object of an execution context,
 or reachable from any such value will not be collected.

 During JavaScript execution, you are not required to call this function; the
 JavaScript engine will garbage collect as needed. JavaScript values created
 within a context group are automatically destroyed when the last reference
 to the context group is released.
*/
/*  */
JS_EXPORT void JSGarbageCollect(JSContextRef ctx);

#ifdef __cplusplus
}
#endif

/* Enable the Objective-C API for platforms with a modern runtime. NOTE: This is duplicated in VM.h. */
#if !defined(JSC_OBJC_API_ENABLED)
#if (defined(__clang__) && defined(__APPLE__) && ((defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && !defined(__i386__)) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)))
#define JSC_OBJC_API_ENABLED 1
#else
#define JSC_OBJC_API_ENABLED 0
#endif
#endif

#endif /* JSBase_h */
