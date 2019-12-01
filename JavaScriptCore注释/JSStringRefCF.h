#ifndef JSStringRefCF_h
#define JSStringRefCF_h

#include "JSBase.h"
#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CFString convenience methods */

/*!
@function
@abstract         Creates a JavaScript string from a CFString.
 |-- 从CFString创建JavaScript字符串。
@discussion       This function is optimized to take advantage of cases when CFStringGetCharactersPtr returns a valid pointer.
 |--  此函数经过优化以利用CFStringGetCharactersPtr返回有效指针的情况。
@param string     The CFString to copy into the new JSString.
 |--  要复制到新JSString中的CFString。
@result           A JSString containing string. Ownership follows the Create Rule.
 |--  包含字符串的JSString。所有权遵循创建规则。
*/
JS_EXPORT JSStringRef JSStringCreateWithCFString(CFStringRef string);
/*!
@function
@abstract         Creates a CFString from a JavaScript string.
 |-- 从JavaScript创建CFString
@param alloc      The alloc parameter to pass to CFStringCreate.
@param string     The JSString to copy into the new CFString.
@result           A CFString containing string. Ownership follows the Create Rule.
*/
JS_EXPORT CFStringRef JSStringCopyCFString(CFAllocatorRef alloc, JSStringRef string) CF_RETURNS_RETAINED;

#ifdef __cplusplus
}
#endif

#endif /* JSStringRefCF_h */

