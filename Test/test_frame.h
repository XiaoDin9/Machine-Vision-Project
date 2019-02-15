#ifndef TEST_FRAME_H
#define TEST_FRAME_H

#include "test_function.h"

#define TEST_DATA_PATH_ERR -1

#define TEST_DATA_PATH "../Data/"

#define REG_FUNCTION(set, disp, fun) test_frm_addFunc((set), (disp), (test_##fun), ("test_"#fun))  

#define TEST_IMAGE_COUNT 20    // 测试图像的最大数量
#define TEST_IMAGE_LOAD_COUNT 10
#define DST_IMAGE_OFFSET TEST_IMAGE_COUNT
#define STD_OUT_IMG_COUNT 5

#define TEST_INFO_BUF_LEN  1024
typedef struct _TestLog
{
    char buf[TEST_INFO_BUF_LEN];
    int cur;
}TestLog;

typedef enum _TestSetID
{
    TEST_TEST,
    TEST_CORE,
    TEST_ARITH,
    TEST_IP,
    TEST_FILE,
    TEST_FEATURE,
    TEST_TK,
    TEST_MATCH,
    TEST_PERF,
    TEST_FLOW,
    TEST_SET_MAX,
}TestSetID;

typedef bool(*TestFuncPtr)(TestLog * p);    // 测试函数指针

typedef struct _TestFunction
{
    char name[64];    //要调用的函数名字
    char disp[32];    //函数要实现的功能
    TestFuncPtr func;   //保存具体调用的函数,如 func = add; 目的是以后调用func(a, b);实现具体的add(a, b)功能;
    int rst;
}TestFunction;

typedef struct _TestSet
{
    char disp[32]; 
    int size;                    //记录实际保存的函数个数;
    TestFunction *funcList;      //通过结构体指针来保存调用函数的一些信息;
    int capacity;                //函数库的容量，即最大能保存多少个函数;
    TestFunction _fList[64];     
}TestSet;

typedef struct _TestImageInfo
{
    bool isParam;
    bool isUse;
    int channels;
    int width;
    int height;
    ZvImage img;
    char path[64];
    char attach[256];
}TestImageInfo;

typedef struct _TestItemInfo
{
    bool isSrcImgUse[TEST_IMAGE_COUNT];
    bool isDstImgOut[TEST_IMAGE_COUNT];
    int dstImgNum;
    ZvImage imgOut[TEST_IMAGE_COUNT];
    TestLog tLog;
}TestInfo;

ZV_EXTERN_C TestImageInfo g_testImgInfo[];
ZV_EXTERN_C TestSet g_testAll[]; //测试函数列表

ZV_EXTERN_C int test_frm_init();
ZV_EXTERN_C void test_frm_exit();
ZV_EXTERN_C void test_frm_start();
ZV_EXTERN_C int test_frm_clearCurInfo();
ZV_EXTERN_C int test_frm_funcTest(TestLog *p, int set, int func);
ZV_EXTERN_C int test_frm_rstSet(TestLog *p, bool isPass);

ZV_EXTERN_C TestInfo * test_frm_getNgInfo(int id);
ZV_EXTERN_C int test_frm_appendNgInfo(TestInfo * info);
ZV_EXTERN_C void test_frm_clearNgInfo();

//输入图像缓存
ZV_EXTERN_C ZvImage test_frm_getImgSrc(int id);
ZV_EXTERN_C ZvImage test_frm_loadImgSrc(char *name);
ZV_EXTERN_C ZvImage test_frm_getImgDst(bool isOut);
ZV_EXTERN_C bool test_frm_chkDstImgInfo(int id);
ZV_EXTERN_C ZvImage test_frm_loadImgStd(char *fileName);

ZV_EXTERN_C void test_frm_setSetDisp(int set, char *name);
ZV_EXTERN_C void test_frm_addFunc(int set, char *disp, TestFuncPtr func, char *name);
ZV_EXTERN_C void test_frm_log(TestLog *p, char * format, ...);

ZV_EXTERN_C char * test_frm_currPath();
ZV_EXTERN_C bool test_frm_createPath(const char * path);
ZV_EXTERN_C char * test_frm_dataTypeStr(ZvImage img);

#endif
