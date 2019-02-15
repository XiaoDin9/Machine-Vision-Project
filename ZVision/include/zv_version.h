#ifndef ZV_VERSION_H
#define ZV_VERSION_H

#define ZV_VERSION_MAJOR    0
#define ZV_VERSION_MINOR    1
#define ZV_VERSION_REVISION 0

#ifdef _DEBUG
#define ZV_VERSION_STATUS   " Debug"
#else
#define ZV_VERSION_STATUS
#endif

#define ZV_VERSION       ZV_STR(ZV_VERSION_MAJOR) "." ZV_STR(ZV_VERSION_MINOR) "." ZV_STR(ZV_VERSION_REVISION) ZV_VERSION_STATUS


#endif