#ifndef ZV_PUBLIC_H
#define ZV_PUBLIC_H
/*
与OpenCV无关并且不导出的定义。
*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <string>
using namespace std;

#include "zv_define.h"
#include "zv_types.h"
#include "system\zv_adapter.h"
#include "system\zv_error.h"
#include "core\zv_core.h"


#define ZV_BUILD_DLL
#define ZV_TRACE_FUNC_NAME  //错误跟踪打印函数名字


#define ZV_EPS_AC7 1e-7
#define ZV_EPS_AC5 1e-5
#define ZV_EPS_AC3 0.001

extern double g_zv_sys_grabTimeout;
extern int g_zv_sys_lineType;
extern int g_zv_sys_optLevel;

#define ZV_RUN_RTN(func) do {int rtn = (func); if (ZV_ST_OK != rtn) return rtn;} while(0)

#define ZV_CHK_NULL1(_p1) do {if (NULL == (_p1)) return ZV_ERR_FA_NULL_1;} while (0);
#define ZV_CHK_NULL2(_p1, _p2) do { \
    if (NULL == (_p1)) return ZV_ERR_FA_NULL_1; \
    if (NULL == (_p2)) return ZV_ERR_FA_NULL_2; \
} while (0);
#define ZV_CHK_NULL3(_p1, _p2, _p3) do { \
    if (NULL == (_p1)) return ZV_ERR_FA_NULL_1; \
    if (NULL == (_p2)) return ZV_ERR_FA_NULL_2; \
    if (NULL == (_p3)) return ZV_ERR_FA_NULL_3; \
} while (0);
#define ZV_CHK_NULL4(_p1, _p2, _p3, _p4) do { \
    if (NULL == (_p1)) return ZV_ERR_FA_NULL_1; \
    if (NULL == (_p2)) return ZV_ERR_FA_NULL_2; \
    if (NULL == (_p3)) return ZV_ERR_FA_NULL_3; \
    if (NULL == (_p4)) return ZV_ERR_FA_NULL_4; \
} while (0);
#define ZV_CHK_NULL5(_p1, _p2, _p3, _p4, _p5) do { \
    if (NULL == (_p1)) return ZV_ERR_FA_NULL_1; \
    if (NULL == (_p2)) return ZV_ERR_FA_NULL_2; \
    if (NULL == (_p3)) return ZV_ERR_FA_NULL_3; \
    if (NULL == (_p4)) return ZV_ERR_FA_NULL_4; \
    if (NULL == (_p5)) return ZV_ERR_FA_NULL_5; \
} while (0);
#define ZV_CHK_NULL6(_p1, _p2, _p3, _p4, _p5, _p6) do { \
    if (NULL == (_p1)) return ZV_ERR_FA_NULL_1; \
    if (NULL == (_p2)) return ZV_ERR_FA_NULL_2; \
    if (NULL == (_p3)) return ZV_ERR_FA_NULL_3; \
    if (NULL == (_p4)) return ZV_ERR_FA_NULL_4; \
    if (NULL == (_p5)) return ZV_ERR_FA_NULL_5; \
    if (NULL == (_p6)) return ZV_ERR_FA_NULL_6; \
} while (0);

#define ZV_CHK_NULL7(_p1, _p2, _p3, _p4, _p5, _p6, _p7) \
    ZV_CHK_NULL6(_p1, _p2, _p3, _p4, _p5, _p6); \
    do {if (NULL == (_p7)) return ZV_ERR_FA_NULL_7;} while (0);

#endif