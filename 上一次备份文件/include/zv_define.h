#ifndef ZV_DEFINE_H
#define ZV_DEFINE_H


#define ZV_SYS_THREAD_MAX       1
#define ZV_SYS_CHANNELS_MAX     4
#define ZV_SYS_DIMS_MAX         2
#define ZV_SYS_IMG_SIZE_MAX     8192
#define ZV_SYS_CAMERA_MAX       4

#define ZV_SYS_ERR_START 0x1000


//#define ZV_USE_SOURCE //定义直接使用源码调用
#define ZV_WITH_TEST

#define ZV_MEASURER_SIZE  (11*sizeof(double))

#define ZV_STR_EXP(__A)  #__A
#define ZV_STR(__A)      ZV_STR_EXP(__A)

#define ZV_STRW_EXP(__A)  L ## #__A
#define ZV_STRW(__A)      ZV_STRW_EXP(__A)


#define ZV_ERR_MSG_BUF_LEN   256
#define ZV_DOUBLE_STR_LEN   32
#define ZV_INT_STR_LEN      16

#define ZV_PI 3.14159265358979323846
#define ZV_TO_DEG(rad) ((rad)*180.0/ZV_PI)
#define ZV_TO_RAD(deg) ((deg)*ZV_PI/180.0)

#ifndef PI
#define PI 3.14159265358979323846
#endif

#ifdef __cplusplus
#define ZV_EXTERN_C extern "C"
#define ZV_CPP_DEF(val) = val
#else
#define ZV_EXTERN_C
#define ZV_CPP_DEF(val)
#endif

#if (defined _WIN32 || defined WINCE || defined __CYGWIN__)
#define ZV_EXPORTS __declspec(dllexport)
#define ZV_IMPORTS __declspec(dllimport)
#elif defined __GNUC__ && __GNUC__ >= 4
#  define ZV_EXPORTS __attribute__ ((visibility ("default")))
#else
#  define ZV_EXPORTS
#endif

#if defined __GNUC__
#define ZV_FUNC__ __func__
#elif defined _MSC_VER
#define ZV_FUNC__ __FUNCTION__
#else
#define ZV_FUNC__ ""
#endif

#endif // ZV_DEFINE_H
