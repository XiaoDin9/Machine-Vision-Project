#include "test_function.h"
#include "test_frame.h"
#include <windows.h>
#include <string>


TEST_FUNC(testTime)
{
    double times = zv_sysGetTimeMs();
    Sleep(1);
    times = zv_sysGetTimeMs() - times;
    TEST_TRACE("Sleep(1):%f\n", times);
    TEST_CHK_TRUE(abs(times-1) < 1);

    times = zv_sysGetTimeMs();
    Sleep(1);
    times = zv_sysGetTimeMs() - times;
    TEST_TRACE("Sleep(1):%f\n", times);
    TEST_CHK_TRUE(abs(times - 1) < 1);

    times = zv_sysGetTimeMs();
    Sleep(2);
    times = zv_sysGetTimeMs() - times;
    TEST_TRACE("Sleep(2):%f\n", times);
    TEST_CHK_TRUE(abs(times - 2) < 1);

    times = zv_sysGetTimeMs();
    Sleep(2);
    times = zv_sysGetTimeMs() - times;
    TEST_TRACE("Sleep(2):%f\n", times);
    TEST_CHK_TRUE(abs(times - 2) < 1);

    times = zv_sysGetTimeMs();
    Sleep(5);
    times = zv_sysGetTimeMs() - times;
    TEST_TRACE("Sleep(5):%f\n", times);
    TEST_CHK_TRUE(abs(times - 5) < 1);

    times = zv_sysGetTimeMs();
    Sleep(20);
    times = zv_sysGetTimeMs() - times;
    TEST_TRACE("Sleep(20):%f\n", times);
    TEST_CHK_TRUE(abs(times - 20) < 2);

    times = zv_sysGetTimeMs();
    Sleep(200);
    times = zv_sysGetTimeMs() - times;
    TEST_TRACE("Sleep(200):%f\n", times);
    TEST_CHK_TRUE(abs(times - 200) < 2);
    TEST_RTN_PASS;
}

TEST_FUNC(Perf_ptrVfun)
{
    ZvImage img = test_frm_getImgSrc(0);
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage dst1 = test_frm_getImgDst(true);
    ZvImage dst2 = test_frm_getImgDst(true);
    zv_imgConvert(img, tmp, ZV_PIXEL_32S, 1, -127);

    TEST_TRACE("数据类型：32S\n直接使用指针\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAbs(tmp, dst1));
    zv_sysSetParamInt("OptLevel", 2);
    TEST_TRACE("库函数调用\n");
    TEST_CHK_TRUE(2 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAbs(tmp, dst2));
    zv_sysSetParamInt("OptLevel", 0);
    TEST_CHK_MAT_EQ(dst1, dst2);

    zv_imgConvert(dst1, dst1, ZV_PIXEL_8U, 1, 0);
    zv_imgConvert(dst2, dst2, ZV_PIXEL_8U, 1, 0);

    ZvImage dst3 = test_frm_getImgDst(true);
    ZvImage dst4 = test_frm_getImgDst(true);
    zv_imgConvert(img, tmp, ZV_PIXEL_64F, 1, -127);

    TEST_TRACE("数据类型：64F\n直接使用指针\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAbs(tmp, dst3));
    zv_sysSetParamInt("OptLevel", 2);
    TEST_TRACE("库函数调用\n");
    TEST_CHK_TRUE(2 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAbs(tmp, dst4));
    zv_sysSetParamInt("OptLevel", 0);
    TEST_CHK_MAT_EQ(dst3, dst4);

    zv_imgConvert(tmp, tmp, ZV_PIXEL_8U, 1, 0);
    zv_imgConvert(dst3, dst3, ZV_PIXEL_8U, 1, 0);
    zv_imgConvert(dst4, dst4, ZV_PIXEL_8U, 1, 0);

    TEST_RTN_PASS;
}

TEST_FUNC(Perf_ptrViterVat)
{
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage src = test_frm_getImgSrc(3);
    zv_imgConvert(src, tmp, ZV_PIXEL_64F, 1.0 / 255, 0);
    ZvPtr<ZvMatrix> matDst(zv_modMatCreate(), zv_modMatRelease);
    ZvPtr<ZvMatrix> matDst1(zv_modMatCreate(), zv_modMatRelease);

    TEST_TRACE("数据类型：64F\n指针遍历\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAcos(tmp, g_test_matDst));
    zv_sysSetParamInt("OptLevel", 3);
    TEST_TRACE("迭代\n");
    TEST_CHK_TRUE(3 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAcos(tmp, matDst1));
    zv_sysSetParamInt("OptLevel", 4);
    TEST_TRACE("逐像素访问\n");
    TEST_CHK_TRUE(4 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAcos(tmp, matDst));
    zv_sysSetParamInt("OptLevel", 0);

    TEST_CHK_MAT_NEAR(g_test_matDst, matDst1);
    TEST_CHK_MAT_NEAR(matDst, matDst1);

    TEST_RTN_CHK;
}

TEST_FUNC(Perf_expVfun)
{
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage src = test_frm_getImgSrc(3);
    ZvImage dst1 = test_frm_getImgDst(true);
    ZvImage dst2 = test_frm_getImgDst(true);
    zv_imgConvert(src, tmp, ZV_PIXEL_64F, 1.0 / 255, 0);

    TEST_TRACE_IMG_INFO(src);
    TEST_TRACE("矩阵表达式\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithMul(tmp, tmp, dst1, 0.8, 0.0));

    zv_sysSetParamInt("OptLevel", 2);
    TEST_TRACE("函数调用\n");
    TEST_CHK_TRUE(2 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithMul(tmp, tmp, dst2, 0.8, 0.0));
    zv_sysSetParamInt("OptLevel", 0);

    TEST_CHK_MAT_NEAR(dst1, dst2);

    TEST_RTN_CHK;
}

TEST_FUNC(Perf_ptrVexp)
{
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage src = test_frm_getImgSrc(3);
    ZvImage dst1 = test_frm_getImgDst(true);
    ZvImage dst2 = test_frm_getImgDst(true);
    zv_imgConvert(src, tmp, ZV_PIXEL_64F, 1.0 / 255, 0);

    TEST_TRACE("图像元数据：(%dx%d) -cn%d - 64F\n", zv_imgWidth(src), zv_imgHeight(src), zv_imgChannels(src));
    TEST_TRACE("矩阵表达式\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    double t1 = 0, t2 = 0;
    TEST_CORE_RUN(zv_arithDiv(tmp, tmp, dst1, 0.8, 0.1), t1);
    zv_sysSetParamInt("OptLevel", 3);
    TEST_TRACE("指针遍历\n");
    TEST_CHK_TRUE(3 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithDiv(tmp, tmp, dst2, 0.8, 0.1), t2);
    zv_sysSetParamInt("OptLevel", 0);

    TEST_CHK_MAT_NEAR(dst1, dst2);
    TEST_CHK_TRUE(t2 < t1);

    TEST_RTN_CHK;
}

TEST_FUNC(Perf_expVfun1)
{
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage src = test_frm_getImgSrc(0);
    ZvImage dst1 = test_frm_getImgDst(true);
    ZvImage dst2 = test_frm_getImgDst(true);
    zv_ipRgbToGray(src, tmp);
    zv_imgConvert(tmp, tmp, ZV_PIXEL_64F, 1.0 / 255, 0);

    TEST_TRACE("图像元数据：(%dx%d) -cn%d - 64F\n", zv_imgWidth(src), zv_imgHeight(src), zv_imgChannels(src));
    TEST_TRACE("矩阵表达式\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithMul(tmp, tmp, dst1, 0.8, 0.0));

    zv_sysSetParamInt("OptLevel", 2);
    TEST_TRACE("函数调用\n");
    TEST_CHK_TRUE(2 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithMul(tmp, tmp, dst2, 0.8, 0.0));
    zv_sysSetParamInt("OptLevel", 0);

    TEST_CHK_MAT_NEAR(dst1, dst2);

    TEST_RTN_CHK;
}

TEST_FUNC(Perf_ptrVtemp)
{
    ZvImage tmp1 = test_frm_getImgDst(false);
    ZvImage tmp2 = test_frm_getImgDst(false);
    ZvImage src1 = test_frm_getImgSrc(2);
    ZvImage src2 = test_frm_getImgSrc(3);
    ZvImage dst1 = test_frm_getImgDst(true);
    ZvImage dst2 = test_frm_getImgDst(true);
    zv_imgConvert(src1, tmp1, ZV_PIXEL_32S, 1.0, 0);
    zv_imgConvert(src2, tmp2, ZV_PIXEL_32S, 1.0, 0);

    TEST_TRACE("图像元数据：(%dx%d) -cn%d - %d\n", zv_imgWidth(tmp1),
        zv_imgHeight(tmp1), zv_imgChannels(tmp1), zv_imgDataType(tmp1));
    TEST_TRACE("模板函数\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAtan2(tmp1, tmp2, dst1));

    zv_sysSetParamInt("OptLevel", 2);
    TEST_TRACE("指针\n");
    TEST_CHK_TRUE(2 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithAtan2(tmp1, tmp2, dst2));
    zv_sysSetParamInt("OptLevel", 0);

    TEST_CHK_MAT_NEAR(dst1, dst2);

    TEST_RTN_CHK;
}

TEST_FUNC(Perf_ptrVexp1)
{
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage src = test_frm_getImgSrc(0);
    ZvImage dst1 = test_frm_getImgDst(true);
    ZvImage dst2 = test_frm_getImgDst(true);
    zv_ipRgbToGray(src, tmp);
    zv_imgConvert(tmp, tmp, ZV_PIXEL_64F, 1.0 / 255, 0);

    TEST_TRACE("图像元数据：(%dx%d) -cn%d - 64F\n", zv_imgWidth(tmp), zv_imgHeight(tmp), zv_imgChannels(tmp));
    TEST_TRACE("矩阵表达式\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithDiv(tmp, tmp, dst1, 0.8, 0.1));
    zv_sysSetParamInt("OptLevel", 3);
    TEST_TRACE("指针遍历\n");
    TEST_CHK_TRUE(3 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithDiv(tmp, tmp, dst2, 0.8, 0.1));
    zv_sysSetParamInt("OptLevel", 0);

    TEST_CHK_MAT_NEAR(dst1, dst2);

    TEST_RTN_CHK;
}

TEST_FUNC(Perf_funVtemp)
{
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage src = test_frm_getImgSrc(2);
    ZvImage dst1 = test_frm_getImgDst(true);
    ZvImage dst2 = test_frm_getImgDst(true);
    zv_imgConvert(src, tmp, ZV_PIXEL_64F, 1.0 / 255, 0);

    TEST_TRACE_IMG_INFO(tmp);
    TEST_TRACE("指数 - 0\n模板\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithPow(tmp, dst1, 0));
    zv_sysSetParamInt("OptLevel", 3);
    TEST_TRACE("函数\n");
    TEST_CHK_TRUE(3 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithPow(tmp, dst2, 0));
    zv_sysSetParamInt("OptLevel", 0);
    TEST_CHK_MAT_NEAR(dst1, dst2);

    TEST_TRACE("指数 - 1.2\n模板\n");
    TEST_CHK_TRUE(0 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithPow(tmp, dst1, 1.2));
    zv_sysSetParamInt("OptLevel", 3);
    TEST_TRACE("函数\n");
    TEST_CHK_TRUE(3 == zv_sysGetParamInt("OptLevel"));
    TEST_CORE_RUN(zv_arithPow(tmp, dst2, 1.2));
    zv_sysSetParamInt("OptLevel", 0);
    TEST_CHK_MAT_NEAR(dst1, dst2);

    TEST_RTN_CHK;
}

int testRegisterPerf()
{
    test_frm_setSetDisp(TEST_PERF, "性能");
    REG_FUNCTION(TEST_PERF, "时间精度", testTime);
    REG_FUNCTION(TEST_PERF, "指针-函数", Perf_ptrVfun);
    REG_FUNCTION(TEST_PERF, "指针-迭代-访问", Perf_ptrViterVat);
    REG_FUNCTION(TEST_PERF, "表达式-函数", Perf_expVfun);
    REG_FUNCTION(TEST_PERF, "指针-表达式", Perf_ptrVexp);
    REG_FUNCTION(TEST_PERF, "表达式-函数1", Perf_expVfun1);
    REG_FUNCTION(TEST_PERF, "指针-表达式1", Perf_ptrVexp1);
    REG_FUNCTION(TEST_PERF, "atan2指针-模板", Perf_ptrVtemp);
    REG_FUNCTION(TEST_PERF, "pow函数-模板", Perf_funVtemp);

    return 0;
}
