
#ifndef __WebKitAvailability__
#define __WebKitAvailability__

#if defined(__APPLE__)

#include <AvailabilityMacros.h>
#include <CoreFoundation/CoreFoundation.h>

#if !TARGET_OS_IPHONE && __MAC_OS_X_VERSION_MIN_REQUIRED < 101100
/* To support availability macros that mention newer OS X versions when building on older OS X versions,
   we provide our own definitions of the underlying macros that the availability macros expand to. We're
   free to expand the macros as no-ops since frameworks built on older OS X versions only ship bundled with
   an application rather than as part of the system.
*/

#ifndef __NSi_10_10 // Building from trunk rather than SDK.
#define __NSi_10_10 introduced=10.0 // Use 10.0 to indicate that everything is available.
#endif

#ifndef __NSi_10_11 // Building from trunk rather than SDK.
#define __NSi_10_11 introduced=10.0 // Use 10.0 to indicate that everything is available.
#endif

#ifndef __NSi_10_12 // Building from trunk rather than SDK.
#define __NSi_10_12 introduced=10.0 // Use 10.0 to indicate that everything is available.
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_9
#define __AVAILABILITY_INTERNAL__MAC_10_9
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_10
#define __AVAILABILITY_INTERNAL__MAC_10_10
#endif

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER
#endif

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_10_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_10_AND_LATER
#endif

#endif /* !TARGET_OS_IPHONE && __MAC_OS_X_VERSION_MIN_REQUIRED < 101100 */

#if defined(BUILDING_GTK__)
#undef API_AVAILABLE
#define API_AVAILABLE(...)
#endif

#else
#define API_AVAILABLE(...)
#endif

#endif /* __WebKitAvailability__ */

