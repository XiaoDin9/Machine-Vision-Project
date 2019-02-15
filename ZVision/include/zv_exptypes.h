#ifndef ZV_EXPTYPES_H
#define ZV_EXPTYPES_H


typedef void * ZvObject;
typedef void * ZvMatrix;
typedef void * ZvImage;
#ifdef __cplusplus
struct _ZvContour;
struct _ZvContList;
typedef _ZvContour * ZvContour;
typedef _ZvContList * ZvContList;
struct _ZvModel;
typedef _ZvModel * ZvModel;
#else
typedef void * ZvContour;
typedef void * ZvContList;
typedef void * ZvModel;
#endif

#ifndef __cplusplus
typedef unsigned char bool;
#define false 0  
#define true  1  
#endif

#if defined _MSC_VER || defined __BORLANDC__
typedef __int64 int64;
typedef unsigned __int64 uint64;
#else
typedef int64_t int64;
typedef uint64_t uint64;
#endif

#endif