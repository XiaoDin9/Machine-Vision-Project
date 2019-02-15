#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

#include "zv.h"  //zvision的头文件和库文件为项目生成后自动拷贝。

#define TEST_VERSION "0.1.0"


#ifdef __cplusplus
template <class T>
class ZvPtr
{
public:
    typedef int(*ZvPtrDel)(T*);

    ZvPtr()
    {
        p = NULL;
        r = NULL;
    }

    ZvPtr(T _p, ZvPtrDel _r)
    {
        p = _p;
        r = _r;
    }

    ~ZvPtr()
    {
        if (p)
        {
            r ? r(&p) : zv_modImgRelease((ZvImage *)&p);
        }
    }

    inline operator T () const  //类型转换
    {
        return p;
    }

    inline T operator -> () const //指向
    {
        return p;
    }

    T p;
    ZvPtrDel r;
};
#endif

ZV_EXTERN_C int testRegisterC();
ZV_EXTERN_C int testRegisterCPP();
ZV_EXTERN_C int testRegisterFlow();
ZV_EXTERN_C int testRegisterPerf();

extern ZvImage g_test_imgFrame;
extern ZvMatrix g_test_matFrame;


//追踪
#define TRACE_FUN_IN()   test_frm_log(p, "进入函数：%s\n", ZV_FUNC__)
#define TEST_TRACE(format, ...)   test_frm_log(p, (format), ##__VA_ARGS__)
#define TEST_TRACE_IMG_INFO(img)  TEST_TRACE("图像元数据：%dx%d - %sC%d\n", \
 zv_imgWidth(img), zv_imgHeight(img), test_frm_dataTypeStr(img), zv_imgChannels(img));

#define TEST_SUB_FUNC(name, ...) bool test_##name(TestLog *p, ##__VA_ARGS__)
#define TEST_SUB_CALL(name, ...) test_##name(p, ##__VA_ARGS__)

#define TEST_FUNC(name) bool test_##name##_Body(TestLog *p); \
bool test_##name(TestLog *p){ g_zv_errLastError = 0; \
TRACE_FUN_IN(); return test_##name##_Body(p);} \
bool test_##name##_Body(TestLog *p)

#define TEST_RTN_PASS  return true
#define TEST_RTN_FAIL  return false
#define TEST_RTN_RST(isPass)  return (isPass)
#define TEST_RTN_CHK    do { if (ZV_SYS_ERR_START <= g_zv_errLastError) \
    {test_frm_log(p, "运行失败[0X%X]：%s", g_zv_errLastError, g_zv_errLastErrorMsg); return false; } \
    return true; } while (0)


//检查
#define TEST_CHK_TRUE(chk) do { \
    bool test_chk_true_cond = (chk); \
    test_frm_log(p, "测试[%s]:%s\n", test_chk_true_cond ? "通过" : "失败", #chk); \
    if (!test_chk_true_cond) return false; \
} while (0)

#define TEST_CHK_EQ(val1, val2) do { \
    bool test_chk_true_cond = ((val1) == (val2)); \
    test_frm_log(p, "测试[%s]:%s(%d) == %s(%d)\n", test_chk_true_cond ? "通过" : "失败", #val1, (val1), #val2, (val2)); \
    if (!test_chk_true_cond) return false; \
} while (0)

#define TEST_CHK_NEAR(val1, val2, ...) do { \
    bool test_chk_true_cond = fabs((val1) - (val2)) < (10e-8, ##__VA_ARGS__); \
    test_frm_log(p, "测试[%s]:%s(%f) == %s(%f)\n", test_chk_true_cond ? "通过" : "失败", #val1, (double)(val1), #val2, (double)(val2)); \
    if (!test_chk_true_cond) return false; \
} while (0)

#define TEST_CHK_ARR_EQ(arr1, arr2) do { \
    int i = 0; \
    while (i < sizeof(arr1)/sizeof(arr1[0])) \
        if (arr1[i] != arr2[i]) break; else ++i; \
    bool test_chk_true = i == sizeof(arr1)/sizeof(arr1[0]); \
    test_frm_log(p, "测试[%s]：%s == %s\n", test_chk_true ? "通过" : "失败", #arr1, #arr2); \
    if (!test_chk_true) { \
        test_frm_log(p, "---->%s[%d](%d) != %s[%d](%d)\n", #arr1, i, arr1[i], #arr2, i, arr2[i]); \
        return false; }\
} while (0)

#define TEST_CHK_ARR_NEAR(arr1, arr2, ...) do { \
    int i = 0; \
    while (i < sizeof(arr1)/sizeof(arr1[0])) \
        if (fabs(arr1[i] - arr2[i]) > (10e-8, ##__VA_ARGS__)) break; else ++i; \
    bool test_chk_true = i == sizeof(arr1)/sizeof(arr1[0]); \
    test_frm_log(p, "测试[%s]：%s == %s\n", test_chk_true ? "通过" : "失败", #arr1, #arr2); \
    if (!test_chk_true) { \
        test_frm_log(p, "---->%s[%d](%f) != %s[%d](%f)\n", #arr1, i, (double)arr1[i], #arr2, i, (double)arr2[i]); \
        return false; }\
} while (0)

#define TEST_CHK_MAT_EQ(img, stdImg) do { \
    if (NULL == stdImg) {test_frm_log(p, "测试[失败]：标准图像为空[%s]\n", #stdImg);} \
    TEST_CHK_RUN(zv_arithCompare(img, stdImg, g_test_imgFrame, 0)); \
    int test_chk_count = -1; TEST_CHK_RUN(zv_arithZeroCount(g_test_imgFrame, &test_chk_count)); \
    test_frm_log(p, "测试[%s]：%s == %s\n", 0 == test_chk_count ? "通过" : "失败", #img, #stdImg); \
    if (0 != test_chk_count) {test_frm_log(p, "不等元素数量：[%d]\n", test_chk_count); return false;} \
} while (0)

#define TEST_CHK_MAT_NEAR(mat, stdMat, ...) do { \
    if (NULL == stdMat) {test_frm_log(p, "测试[失败]：标准矩阵为空[%s]\n", #stdMat);} \
    int test_frm_run_code = zv_testAbsDiff(mat, stdMat, g_test_matFrame); \
    if(0 != test_frm_run_code) \
    {test_frm_log(p, "矩阵比较出错[0X%X]：%s\n", test_frm_run_code, zv_errStatusStr(test_frm_run_code)); return false; } \
    double norm_value_ = zv_testNorm(g_test_matFrame, 0); bool norm_value_test_pass = (10e-8, ##__VA_ARGS__) >= norm_value_;\
    test_frm_log(p, "测试[%s]：%s == %s\n", norm_value_test_pass ? "通过" : "失败", #mat, #stdMat); \
    if (!norm_value_test_pass) {test_frm_log(p, "最大差值：[%.8f]\n", norm_value_); return false;} \
} while (0)

#define TEST_CHK_RUN(func)  do{ \
    int test_chk_run_code = (func); \
    if (0 != test_chk_run_code) {test_frm_log(p, "任务管理出错[0X%X]：%s\n", test_chk_run_code, #func); return false; }\
    if(0 != g_zv_errLastError) \
    {test_frm_log(p, "运行失败[0X%X]：%s\n函数：%s", g_zv_errLastError, g_zv_errLastErrorMsg, #func); return false; } \
}while(0)

#define TEST_CORE_RUN(func, ...)  do{ \
    double test_core_tmp_ = zv_sysGetTickFreq(); int64 test_core_stTick_ = zv_sysGetTickCount(); \
    int test_chk_run_code = (func); int64 test_core_edTick_ = zv_sysGetTickCount(); \
    test_core_tmp_ = (test_core_edTick_ - test_core_stTick_) * 1000.0 / test_core_tmp_; \
    test_core_tmp_, ##__VA_ARGS__ =  test_core_tmp_; \
    test_frm_log(p, "时间统计(%.3fms)：%s\n", test_core_tmp_, #func); \
    if (0 != test_chk_run_code) {test_frm_log(p, "任务管理出错[0X%X]：%s\n", test_chk_run_code, #func); return false; }\
    if(0 != g_zv_errLastError) \
    {test_frm_log(p, "运行失败[0X%X]：%s\n函数：%s", g_zv_errLastError, g_zv_errLastErrorMsg, #func); return false; } \
}while(0)


extern ZvImage g_test_imgStdOut;
extern ZvMatrix g_test_matStdOut;

extern ZvMatrix g_test_matSrc;
extern ZvMatrix g_test_matSrc2;
extern ZvMatrix g_test_matDst;

#endif
