#include "test_function.h"
#include "test_frame.h"
#include <windows.h>
#include <string>
#include <opencv.hpp>

////单元测试日志：
//测试：数学运算 - 标量加
//进入函数 ---->testScalarAdd<----
//输入参数1：[图像]输入索引1(ROOT/1.jpg)
//输入参数2：[数值]18.0000
//输出参数1：[图像]输出索引1
//测试函数：zvScalarAdd
//依赖函数：zvReadImage
//    输出位置[100,100] 134.000 == 134.000
//    输出图像和 134335.0000 == 134335.0000
//测试结果：PASS
//离开函数
//

ZvImage g_test_imgFrame = NULL;
ZvMatrix g_test_matFrame = NULL;

ZvImage g_test_imgStdOut = NULL;
ZvMatrix g_test_matStdOut = NULL;

ZvMatrix g_test_matSrc = NULL;
ZvMatrix g_test_matSrc2 = NULL;
ZvMatrix g_test_matDst = NULL;


//测试函数Demo
TEST_FUNC(testBase)  //test_testBase
{
    TEST_TRACE("Version:%s\n", ZV_VERSION);
    g_zv_errStatus = 0x1001;
    TEST_CHK_TRUE(0x1001 == g_zv_errStatus);
    g_zv_errStatus = 0;
    TEST_CHK_TRUE(0 == g_zv_errStatus);
   
    g_zv_errLastError = 0x1002;
    TEST_CHK_TRUE(0x1002 == g_zv_errLastError);
    g_zv_errLastError = 0;
    TEST_CHK_TRUE(0 == g_zv_errLastError);
    TEST_CHK_TRUE('\0' == g_zv_errLastErrorMsg[0]);
    TEST_CHK_TRUE(false == g_zv_sysIsDrawFill);
    TEST_CHK_TRUE(26066955 == zv_sysGetParamInt("Test"));
    zv_sysSetParamInt("Test", 888);
    TEST_CHK_TRUE(888 == zv_sysGetParamInt("Test"));
    TEST_CHK_NEAR(ZV_PI, zv_sysGetParamDouble("Test"));

    TEST_RTN_PASS;
}

TEST_FUNC(testPass)
{
    TEST_TRACE("模拟测试成功情况\n");
    Sleep(300);
    TEST_RTN_PASS;
}

TEST_FUNC(testFail)
{
    TEST_TRACE("模拟测试失败情况\n");
    TEST_TRACE("不计入统计数据\n");
    Sleep(200);
    ZvImage img1 = test_frm_getImgSrc(0);
    ZvImage img2 = test_frm_getImgSrc(2);

    ZvImage dst1 = test_frm_getImgDst(false);
    ZvImage dst2 = test_frm_getImgDst(true);
    zv_imgCopy(img1, dst1);
    zv_imgCopy(img2, dst2);

    TEST_RTN_FAIL;
}

/*========================图像的基本功能======================*/
TEST_FUNC(zv_matGenEye)
{
    TEST_CHK_RUN(zv_matGenEye(g_test_matSrc, 5));

    // 读取对的矩阵，然后进行匹配
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matDst, TEST_DATA_PATH"./TrueResultData/test_eye_mat.xml", "ZvMat", 0));
  
    TEST_CHK_MAT_NEAR(g_test_matSrc, g_test_matDst);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_matGetData)    
{
    double Src2Data[9] = { 0, 2, 4, -3, -1, 1, -6, -4, -2 };
    int width = 3, height = 3;
    zv_matGenData(g_test_matSrc, height, width, Src2Data);

    // 修改src 矩阵的值
    double data[9] = { 0 };
    TEST_CHK_RUN(zv_matGetData(g_test_matSrc, data, 9));

    TEST_CHK_ARR_NEAR(Src2Data, data);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_matCopy)
{
    // 从.xml 文件中读取数据到 ZvMatrxi　矩阵中去
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matSrc, TEST_DATA_PATH"./TrueResultData/test_data_mat.xml", "ZvMat", 0));

    TEST_CHK_RUN(zv_matCopy(g_test_matSrc, g_test_matDst));

    // 读取对的矩阵，然后进行匹配
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_copy_mat.xml", "ZvMat", 0));

    TEST_CHK_MAT_NEAR(g_test_matStdOut, g_test_matDst);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_matGetSub)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);
    
    double x = 50, y = 100, width = 240, height = 320;
    TEST_CHK_RUN(zv_matGetSub(src, dst, x, y, width, height));

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/sub_image.bmp", 0, 0));
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/sub_image.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_imgConvert)
{
    ZvImage img = test_frm_getImgSrc(0);
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage dst = test_frm_getImgDst(true);
    zv_imgConvert(img, tmp, ZV_PIXEL_32S, 1, 0);
    zv_imgConvert(tmp, dst, ZV_PIXEL_8U, 1, 0);
    ZvImage tmp1 = test_frm_getImgDst(false);
    ZvImage dst1 = test_frm_getImgDst(true);
    zv_imgConvert(img, tmp1, ZV_PIXEL_64F, 1, 0);
    zv_imgConvert(tmp1, dst1, ZV_PIXEL_8U, 1, 0);

    TEST_RTN_PASS;
}

/*================数学运算======================*/
TEST_FUNC(zv_arithAbs)
{
    ZvImage img = test_frm_getImgSrc(0);
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage dst = test_frm_getImgDst(true);
    zv_imgConvert(img, tmp, ZV_PIXEL_32S, 1, -127);

    TEST_CORE_RUN(zv_arithAbs(tmp, dst));
    zv_imgConvert(tmp, tmp, ZV_PIXEL_8U, 1, 0);
    zv_imgConvert(dst, dst, ZV_PIXEL_8U, 1, 0);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_arithAbsDiff)
{
    double Src1Data[9] = { 0, 1, 2, -15, -14, -13, -30, -29, -28 };
    double Src2Data[9] = { 0, 2, 4, -3, -1, 1, -6, -4, -2 };
    int width = 3, height = 3;
    zv_matGenData(g_test_matSrc, height, width, Src1Data);
    zv_matGenData(g_test_matSrc2, height, width, Src2Data);

    TEST_CHK_RUN(zv_arithAbsDiff(g_test_matSrc, g_test_matSrc2, g_test_matDst, 1));    // 调用求差值的绝对值的函数     

    // 读取对的矩阵，然后进行匹配
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_absdiff_mat.xml", "ZvMat", 0));

    TEST_CHK_MAT_NEAR(g_test_matDst, g_test_matStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_arithAdd)
{
    double Src1Data[9] = { 0, 1, 2, -15, -14, -13, -30, -29, -28 };
    double Src2Data[9] = { 0, 2, 4, -3, -1, 1, -6, -4, -2 };
    int width = 3, height = 3;
    zv_matGenData(g_test_matSrc, height, width, Src1Data);
    zv_matGenData(g_test_matSrc2, height, width, Src2Data);
    TEST_CHK_RUN(zv_arithAdd(g_test_matSrc, g_test_matSrc2, g_test_matDst, 1, 0));

    // 读取对的矩阵，然后进行匹配
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_ADD_mat.xml", "ZvMat", 0));

    TEST_CHK_MAT_NEAR(g_test_matDst, g_test_matStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_arithAddWeighted)
{
    double Src1Data[9] = { 0, 1, 2, -15, -14, -13, -30, -29, -28 };
    double Src2Data[9] = { 0, 2, 4, -3, -1, 1, -6, -4, -2 };
    int width = 3, height = 3;
    zv_matGenData(g_test_matSrc, height, width, Src1Data);
    zv_matGenData(g_test_matSrc2, height, width, Src2Data);

    TEST_CHK_RUN(zv_arithAddWeighted(g_test_matSrc, g_test_matSrc2, g_test_matDst, 2, 3, 4));    // 调用求差值的绝对值的函数     

    // 读取对的矩阵，然后进行匹配
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_AddWeighted_mat.xml", "ZvMat", 0));

    TEST_CHK_MAT_NEAR(g_test_matDst, g_test_matStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_arithSin)    // 包含有问题的值
{
    double Src1Data[9] = { 10, 20, 35, 45, 60, 75, 90, 135, 155 };
    int width = 3, height = 3;
    zv_matGenData(g_test_matSrc, height, width, Src1Data);

    TEST_CHK_RUN(zv_arithSin(g_test_matSrc, g_test_matDst));    // 调用求差值的绝对值的函数     

    // 保存矩阵到 .xml 文件中去, 并自检是否对，对的话以它为最终的标准
    //TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matSrc, TEST_DATA_PATH"./TrueResultData/test_sin_mat.xml", "ZvMat", 0));

    // 读取对的矩阵，然后进行匹配
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_sin_mat.xml", "ZvMat", 0));

    TEST_CHK_MAT_NEAR(g_test_matDst, g_test_matStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_arithAsin)
{
    ZvImage src = test_frm_getImgSrc(3);
    ZvImage cvtDb = test_frm_getImgDst(false);
    zv_imgConvert(src, cvtDb, ZV_PIXEL_64F, 1.0 / 255, 0);

    TEST_CORE_RUN(zv_arithAsin(cvtDb, g_test_matDst));

    //TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matDst, TEST_DATA_PATH"TrueResultData/test_asin_mat.xml", "ASin", 0));
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"TrueResultData/test_asin_mat.xml", "ASin", 0));
    TEST_CHK_MAT_NEAR(g_test_matDst, g_test_matStdOut);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_arithAcos)
{
    ZvImage src = test_frm_getImgSrc(3);
    ZvImage cvtDb = test_frm_getImgDst(false);
    zv_imgConvert(src, cvtDb, ZV_PIXEL_64F, 1.0 / 255, 0);

    TEST_CORE_RUN(zv_arithAcos(cvtDb, g_test_matDst));

    //TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matDst, TEST_DATA_PATH"./TrueResultData/test_acos_mat.xml", "ACos", 0));
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_acos_mat.xml", "ACos", 0));
    TEST_CHK_MAT_NEAR(g_test_matDst, g_test_matStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_arithAnd)
{
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    double val = 0;
    TEST_CHK_RUN(zv_imgGenConst(tmp, zv_imgWidth(src), zv_imgHeight(src), zv_imgDataType(src), zv_imgChannels(src), &val));
    g_zv_sysIsDrawFill = 1;
    zv_draCircle(tmp, 400, 500, 300, 0xFFFFFF);
    zv_draCircle(tmp, 400, 500, 120, 0);
    g_zv_sysIsDrawFill = 0;
    TEST_CHK_TRUE(0 == g_zv_errLastError);

    TEST_CHK_RUN(zv_arithAnd(src, tmp, dst));
    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/and_image.bmp", 0, 0));
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/and_image.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_arithHist)
{
    ZvImage src = test_frm_getImgSrc(6);
    TEST_CHK_RUN(zv_arithHist(src, g_test_matDst, 256, 0, 255));
    //TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matDst, TEST_DATA_PATH"TrueResultData/test_std_mat.xml", "hist_data_6", 0));
    zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"TrueResultData/test_std_mat.xml", "hist_data_6", 0);
    TEST_CHK_MAT_NEAR(g_test_matDst, g_test_matStdOut);
    TEST_RTN_PASS;
}

/*====================图像/矩阵的读取和保存=================*/
TEST_FUNC(zv_fileReadImage)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    TEST_CHK_RUN(zv_fileReadImage(dst, TEST_DATA_PATH"./TrueResultData/gray_image.bmp", 0));    // 正式调用该函数  
  
    TEST_CHK_MAT_NEAR(src, dst);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_fileWriteImage)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    TEST_CHK_RUN(zv_fileWriteImage(src, TEST_DATA_PATH"Temp/write_test.bmp", 100));
    Sleep(10);
    TEST_CHK_RUN(zv_fileReadImage(dst, TEST_DATA_PATH"Temp/write_test.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(src, dst);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_fileReadMatrix)
{
    TEST_CHK_RUN(zv_matGenEye(g_test_matSrc, 5));
    // 读
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_eye_mat.xml", "ZvMat", 0));
    TEST_CHK_MAT_NEAR(g_test_matSrc, g_test_matStdOut);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_fileWriteMatrix)
{
    double Src1Data[9] = { 10, 11, 2, -15, 34, -13, 47, -29, 58 };
    zv_matGenData(g_test_matSrc, 3, 3, Src1Data);

    // 写
    TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matSrc, TEST_DATA_PATH"./TrueResultData/test_fileWriteMat_mat.xml", "WriteMatrix", 0));

    // 读
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_fileWriteMat_mat.xml", "WriteMatrix", 0));
    TEST_CHK_MAT_NEAR(g_test_matSrc, g_test_matStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_fileMatrix)
{
    double Src1Data[9] = { 10, 11, 2, -15, 34, -13, 47, -29, 58 };
    zv_matGenData(g_test_matSrc, 3, 3, Src1Data);

    // 写
    TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matSrc, TEST_DATA_PATH"./TrueResultData/test_fileWrite_mat.yml", "WriteMatrix", 0));

    // 读
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_fileWrite_mat.yml", "WriteMatrix", 0));
    TEST_CHK_MAT_NEAR(g_test_matSrc, g_test_matStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_fileMatrix_update)
{
    double Src1Data[9] = { 10, 11, 2, -15, 34, -13, 47, -29, 58 };
    zv_matGenData(g_test_matSrc, 3, 3, Src1Data);

    // 写
    TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matSrc, TEST_DATA_PATH"Temp/test_fileWrite_mat.yml", "WriteMatrix", 0));
    // 追加
    TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matSrc, TEST_DATA_PATH"Temp/test_fileWrite_mat.yml", "WriteMatrix1", 1));

    // 读
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"Temp/test_fileWrite_mat.yml", "WriteMatrix", 0));
    TEST_CHK_MAT_NEAR(g_test_matSrc, g_test_matStdOut);
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"Temp/test_fileWrite_mat.yml", "WriteMatrix1", 0));
    TEST_CHK_MAT_NEAR(g_test_matSrc, g_test_matStdOut);

    zv_matSetValue(g_test_matSrc, 0, 2, 100);
    // 更新
    TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matSrc, TEST_DATA_PATH"Temp/test_fileWrite_mat.yml", "WriteMatrix1", 1));
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"Temp/test_fileWrite_mat.yml", "WriteMatrix1", 0));
    TEST_CHK_MAT_NEAR(g_test_matSrc, g_test_matStdOut);

    TEST_RTN_PASS;
}

/*====================图像处理部分==========================*/
TEST_FUNC(zv_ipMirror)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);
    
    TEST_CHK_RUN(zv_ipMirror(src, dst, 0));   

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_mirror_img.bmp", 0, 0));
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_mirror_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipRotate)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    double angle = 45;         // 旋转的度数
    int interp = 0;            // 插值方法，默认旋转最近邻插值方法
    TEST_CHK_RUN(zv_ipRotate(src, dst, angle, interp));

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_rotate_img.bmp", 0, 0));
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_rotate_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipZoom)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    double scaleW = 0.5, scaleH = 0.5;    // 为图像宽、搞缩放的比例因子,大于0 对图像进行放大，小于0对图像进行缩小;
    int interp = 0;            // 插值方法，默认旋转最近邻插值方法
    TEST_CHK_RUN(zv_ipZoom(src, dst, scaleW, scaleH, interp));

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_zoom_img.bmp", 0, 0));
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_zoom_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipAffine)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage rgb = test_frm_getImgSrc(9);

    int width = zv_imgWidth(rgb);
    int height = zv_imgHeight(rgb);
    double from[6], to[6];
    from[0] = 0; from[1] = 0;                   // 图像上的 A 点
    from[2] = width - 1; from[3] = 0;    //图像上的 B 点
    from[4] = 0; from[5] = height - 1;    //图像上的 C 点

    to[0] = width*0.0; to[1] = height*0.33;       //变换后的图像所对应原图 A 的点为A’
    to[2] = width*0.85; to[3] = height*0.25;      //  变换后的图像所对应原图 B 的点为B’
    to[4] = width*0.15; to[5] = height*0.7;         //变换后的图像所对应原图 C的点为C’

    zv_tkGetAffine(g_test_matDst, from, to);
    int interp = 0;     // 仿射后的图像的宽和高
    char *border = NULL;                                                            // 边界的处理方法
    TEST_CHK_RUN(zv_ipAffine(rgb, dst, g_test_matDst, width, height, interp, border));       //进行仿射变换

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_affine_img.bmp", 0, 0));
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_affine_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipPerspective)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage rgb = test_frm_getImgSrc(9);

    int width = zv_imgWidth(rgb);
    int height = zv_imgHeight(rgb);
    // double from[8], to[8];
   // from[0] = 0;                            from[1] = 0;    // A
   // from[2] = (*(cv::Mat*)rgb).cols - 1;    from[3] = 0;   // B
   // from[4] = 0;                            from[5] = (*(cv::Mat*)rgb).rows - 1;   // C
   // from[6] = (*(cv::Mat*)rgb).cols - 1;    from[7] = (*(cv::Mat*)rgb).rows - 1;    //D

   // to[0] = (*(cv::Mat*)rgb).cols*0.05;     to[1] = (*(cv::Mat*)rgb).cols*0.33;
   // to[2] = (*(cv::Mat*)rgb).cols*0.9;      to[3] = (*(cv::Mat*)rgb).rows*0.25;           // 
   // to[4] = (*(cv::Mat*)rgb).cols*0.2;      to[5] = (*(cv::Mat*)rgb).rows*0.7;             // 
   // to[6] = (*(cv::Mat*)rgb).cols*0.8;      to[7] = (*(cv::Mat*)rgb).rows*0.9;             // 
   // zv_tkGetProjective(g_test_matDst, from, to);
   // int dstW = (*(cv::Mat*)rgb).cols, dstH = (*(cv::Mat*)rgb).rows, interp = 0;
   // char *border = NULL;
   // TEST_CHK_RUN(zv_ipPerspective(rgb, dst, g_test_matDst, dstW, dstH, interp, border));       //进行仿射变换
   // 
   //// TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_perspective_img.bmp", 0, 0));
   // TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_perspective_img.bmp", 0));    // 正式调用该函数  
   // TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipRgbToGray)
{
    ZvImage dst = test_frm_getImgDst(true);
    TEST_CORE_RUN(zv_ipRgbToGray(test_frm_getImgSrc(4), dst));
    //zv_fileWriteImage(dst, TEST_DATA_PATH"4_to_gray.bmp", NULL, 0); //保存人工判断的正确图片
    ZvImage stdGray = test_frm_loadImgStd("4_to_gray.bmp");
    TEST_CHK_MAT_EQ(dst, stdGray);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipThreshold)
{
    ZvImage dst = test_frm_getImgDst(true);
    TEST_CORE_RUN(zv_ipThreshold(test_frm_getImgSrc(5), dst, 100, 255, false));
    //zv_fileWriteImage(dst, TEST_DATA_PATH"5_thresh_100_255_F.bmp", NULL, 0); //保存人工判断的正确图片
    ZvImage imgStd = test_frm_loadImgStd("5_thresh_100_255_F.bmp");
    TEST_CHK_MAT_EQ(dst, imgStd);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipThreshold1)
{
    ZvImage dst = test_frm_getImgDst(true);
    TEST_CHK_RUN(zv_ipThreshold(test_frm_getImgSrc(5), dst, 100, 255, true));
    ZvImage stdGray = test_frm_loadImgStd("5_thresh_100_255_T.bmp");
    TEST_CHK_MAT_EQ(dst, stdGray);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipEqualizeHist)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    TEST_CHK_RUN(zv_ipEqualizeHist(src, dst));

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_equalizeHist_img.bmp", 0, 0));
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_equalizeHist_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipMeanBlur)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    TEST_CHK_RUN(zv_ipMeanBlur(src, dst, 3));

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_meanBlur_img.bmp", 0, 0));

    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_meanBlur_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipGaussBlur)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    TEST_CHK_RUN(zv_ipGaussBlur(src, dst, 3));

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_guassBlur_img.bmp", 0, 0));

    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_guassBlur_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_NEAR(dst, g_test_imgStdOut);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipCanny)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);
    
    /// 使用 3x3内核降噪
    int size = 3;
    TEST_CHK_RUN(zv_ipMeanBlur(src, dst, size));    

    /// 运行Canny算子
    int max_lowThreshold = 100, ratio = 3, lowThreshold = 45, kernel_size = 3;
    TEST_CHK_RUN(zv_ipCanny(dst, dst, lowThreshold, lowThreshold*ratio, kernel_size));
    
    // 写
    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_canny_img.bmp", 0, 0));
    // 读
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_canny_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipSobel)
{
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    /// 分别对 x轴 和 y轴进行sobel　梯度求导
    TEST_CHK_RUN(zv_ipSobel(src, g_test_matSrc, 1, 0, 3));
    zv_imgConvert(g_test_matSrc, g_test_matSrc, ZV_PIXEL_8U, 1, 0);

    TEST_CHK_RUN(zv_ipSobel(src, g_test_matSrc2, 0, 1, 3));
    zv_imgConvert(g_test_matSrc2, g_test_matSrc2, ZV_PIXEL_8U, 1, 0);

    /// 合并梯度(近似)
    TEST_CHK_RUN(zv_arithAddWeighted(g_test_matSrc, g_test_matSrc2, dst, 0.5, 0.5, 0));

    // 写
    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_Soble_img.bmp", 0, 0));
    
    // 读
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_Soble_img.bmp", 0));    // 正式调用该函数  

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipOpening)
{
    // 获得灰度图像
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    TEST_CHK_RUN(zv_ipOpening(src, dst, 15, 15));

    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_Opening_img.bmp", 0, 0));

    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_Opening_img.bmp", 0));

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_ipClosing)
{
    // 获得灰度图像
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(9);

    TEST_CHK_RUN(zv_ipClosing(src, dst, 15, 15));
    //TEST_CHK_RUN(zv_fileWriteImage(dst, TEST_DATA_PATH"./TrueResultData/ip_Closing_img.bmp", 0, 0));
    TEST_CHK_RUN(zv_fileReadImage(g_test_imgStdOut, TEST_DATA_PATH"./TrueResultData/ip_Closing_img.bmp", 0));

    TEST_CHK_MAT_EQ(dst, g_test_imgStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_contGen)
{
    // 获得灰度图像
    ZvImage dst = test_frm_getImgDst(true);     // 通过这样定义的 ZvImage 变量既可以显示出来
    ZvImage src = test_frm_getImgSrc(5);

    // 对图像进行阈值化处理
    TEST_CHK_RUN(zv_ipThreshold(src, dst, 100, 255, false));
    //TEST_CORE_RUN(zv_ipThreshold(test_frm_getImgSrc(5), dst, 100, 255, false));

    ZvContList contours = zv_modContListCreate();

    // 得到图像的轮廓
    TEST_CHK_RUN(zv_contGen(dst, contours, 1, 0));     // error

    zv_matGenConst(g_test_matDst, zv_contCount(contours), 2, 0);
    for (int i = 0; i < zv_contCount(contours); i++)
    {
        ZvContour cont2 = zv_contGetContour(contours, i);
        // 把轮廓类型数据 写入到 Matrix 矩阵中去
        double pt[2];
        zv_contGetPoint(cont2, 0, pt);
        TEST_CHK_RUN(zv_matSetRow(g_test_matDst, i, pt));
    }
    // 把矩阵数据写入到.xml 文件中去
    //TEST_CHK_RUN(zv_fileWriteMatrix(g_test_matDst, TEST_DATA_PATH"./TrueResultData/test_contours_mat.xml", "contours", 0));
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matStdOut, TEST_DATA_PATH"./TrueResultData/test_contours_mat.xml", "contours", 0));
    // 对比轮廓数据是否匹配
    TEST_CHK_MAT_EQ(g_test_matDst, g_test_matStdOut);

    TEST_RTN_PASS;
}

TEST_FUNC(zv_contFromMatrix)
{
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matSrc, TEST_DATA_PATH"./TrueResultData/test_contours_mat.xml", "contours", 0));

    ZvContour contours = zv_modContCreate();
    TEST_CHK_RUN(zv_contFromMatrix(contours, g_test_matSrc));    // 把矩阵的数据转换成轮廓数据

    TEST_CHK_RUN(zv_contToMatrix(contours, g_test_matStdOut));

    TEST_CHK_MAT_EQ(g_test_matSrc, g_test_matStdOut);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_contArea)
{
    // 得到轮廓的数据
    TEST_CHK_RUN(zv_fileReadMatrix(g_test_matSrc, TEST_DATA_PATH"./TrueResultData/test_contours_mat.xml", "contours", 0));
    ZvContour contours = zv_modContCreate();
    TEST_CHK_RUN(zv_contFromMatrix(contours, g_test_matSrc));    // 把矩阵的数据转换成轮廓数据

    // 求轮廓的面积
    double area;
    TEST_CHK_RUN(zv_contArea(contours, false, &area));
    TEST_TRACE("Area:%.8f\n", area);

    TEST_CHK_TRUE(fabs(area - 123211) < 0.1);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_tkFitPolyn)
{
    double data[] = { 5, 9, 6, 11, 7, 0 };
    zv_matGenData(g_test_matSrc, 3, 2, data);
    double param[3] = { 0 };
    TEST_CORE_RUN(zv_tkFitPolyn(g_test_matSrc, 2, param));
    double paramStd[] = { -196, 73.5, -6.5 };
    TEST_CHK_ARR_NEAR(param, paramStd);
    TEST_RTN_PASS;
}

// 灰度匹配
TEST_FUNC(zv_matchFastTempl)
{
    ZvImage src = test_frm_getImgSrc(9);
    ZvImage temp = test_frm_getImgSrc(8);

    int pos[2];
    TEST_CHK_RUN(zv_matchFastTempl(src, temp, pos, 0));
    int stdPos[2] = { 65, 115 };

    TEST_CHK_ARR_EQ(pos, stdPos);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_matchBestTempl)
{
    ZvImage src = test_frm_getImgSrc(9);
    ZvImage temp = test_frm_getImgDst(true);
    zv_imgGetSub(src, temp, 180, 543, 40, 40);

    double pos[3];
    TEST_CORE_RUN(zv_matchBestTempl(src, temp, 60, pos, true, 0));
    double stdPos[3] = { 199.5, 562.5, 100 };
    ZvImage dst = test_frm_getImgDst(true);
    zv_ipGrayToRgb(src, dst);
    zv_draRect2(dst, pos[0], pos[1], zv_imgWidth(temp), zv_imgHeight(temp), 0, 0x00FF00);
    TEST_CHK_ARR_NEAR(pos, stdPos, 0.5);
    TEST_RTN_PASS;
}

TEST_SUB_FUNC(matchMultiTrace, ZvImage src, ZvImage temp, ZvMatrix rst, double minScore, int num, int polar)
{
    TEST_CORE_RUN(zv_matchMultiTempl(src, temp, rst, minScore, num, 20, true, polar));
    ZvImage dst = test_frm_getImgDst(true);
    zv_ipGrayToRgb(src, dst);
    double maxPos[3] = { 0 };
    for (int i = 0; i < zv_matRows(rst); i++)
    {
        zv_matGetRow(rst, i, maxPos, 3);
        zv_draRect2(dst, maxPos[0], maxPos[1], zv_imgWidth(temp), zv_imgHeight(temp), 0, 0x00FF00);
        char text[32] = { 0 };
        sprintf(text, "%.2f", maxPos[2]);
        zv_draText(dst, text, maxPos[0], maxPos[1], 1, 0xFF);
    }
    TEST_TRACE("Total Match %d\n", zv_matRows(rst));
    TEST_RTN_CHK;
}

TEST_FUNC(zv_matchMultiTempl)
{
    ZvImage src = test_frm_getImgSrc(9);
    ZvImage temp = test_frm_getImgDst(true);
    zv_imgGetSub(src, temp, 180, 543, 40, 40);
    double stdPos[3] = { 199.5, 562.5, 100 };

    TEST_SUB_CALL(matchMultiTrace, src, temp, g_test_matDst, 70, 0, 0);
    double maxPos[3] = { 0 };
    zv_matGetRow(g_test_matDst, 0, maxPos, 3);
    TEST_CHK_ARR_NEAR(maxPos, stdPos, 0.5);
    TEST_RTN_PASS;
}

TEST_FUNC(zv_matchMultiTempl1)
{
    ZvImage src = test_frm_getImgSrc(9);
    ZvImage temp = test_frm_getImgDst(true);
    zv_imgGetSub(src, temp, 180, 543, 40, 40);
    double stdPos[3] = { 199.5, 562.5, 100 };

    TEST_SUB_CALL(matchMultiTrace, src, temp, g_test_matDst, 70, 0, 0);

    double maxPos[3] = { 0 };
    zv_matGetRow(g_test_matDst, 0, maxPos, 3);
    TEST_CHK_ARR_NEAR(maxPos, stdPos, 0.5);

    TEST_SUB_CALL(matchMultiTrace, src, temp, g_test_matSrc, 60, 0, 0);
    zv_matGetRow(g_test_matSrc, 0, maxPos, 3);
    TEST_CHK_ARR_NEAR(maxPos, stdPos, 0.5);

    TEST_SUB_CALL(matchMultiTrace, src, temp, g_test_matSrc2, 60, 10, 0);
    zv_matGetRow(g_test_matSrc2, 0, maxPos, 3);
    TEST_CHK_ARR_NEAR(maxPos, stdPos, 0.5);
    TEST_CHK_TRUE(10 == zv_matRows(g_test_matSrc2));

    TEST_TRACE("测试前10个匹配是否相同\n");
    for (int i = 0; i < 10; i++)
    {
        zv_matGetRow(g_test_matDst, i, stdPos, 3);
        zv_matGetRow(g_test_matSrc, i, maxPos, 3);
        TEST_CHK_ARR_NEAR(maxPos, stdPos, 0.5);
        zv_matGetRow(g_test_matSrc2, i, maxPos, 3);
        TEST_CHK_ARR_NEAR(maxPos, stdPos, 0.5);
    }

    TEST_RTN_CHK;
}

/*=============================新添加代码=======================*/
TEST_FUNC(zv_matchNccFind)
{
    /**********************************************************************************
    **                      Test1 单目标匹配，但是目标是不旋转
    ***********************************************************************************
    ZvImage src = test_frm_getImgSrc(9);
    ZvImage templ = test_frm_getImgSrc(8);
    ZvImage dst = test_frm_getImgSrc(9);
    //zv_imgGetSub(src, temp, 180, 543, 40, 40);

    // error 这种写法肯定是错误的；
    int T_w = zv_imgWidth(templ);
    int T_h = zv_imgHeight(templ);

    ZvModel mod = zv_zvModelCreate();
    double angleStart = 0, angleExt = 0, angleStep = 0;
    int NumLevel = 2;
    double x, y;
    double minScore = 0.5, minDist = 0;
    int isSubPix = 0;

    zv_matchNccCreate(mod, templ, angleStart, angleExt, angleStep, NumLevel);
    zv_matchNccFind(mod, src, g_test_matFrame, NumLevel, minScore, &x, &y, minDist, isSubPix);

    //画出找到的像素ROI区域
    zv_draRect(dst, x, y, T_w, T_h, 255);

    //显示输出图像
    cv::imshow("x1", *(cv::Mat *)dst);
    cv::waitKey(0);
    */

    /**********************************************************************************
    ***                      Test2 单目标匹配，但是目标是有角度的                    ***
    ***********************************************************************************/
    ZvImage src = test_frm_getImgSrc(9);
    ZvImage dst = test_frm_getImgSrc(9);
    ZvImage temp = test_frm_getImgDst(true);
    zv_imgGetSub(src, temp, 53, 34, 67, 149);
    //zv_fileWriteImage(temp, TEST_DATA_PATH"./Temp/TemplImg.bmp", 0);

    int T_w = zv_imgWidth(temp);
    int T_h = zv_imgHeight(temp);

    ZvModel mod = zv_zvModelCreate();
    double angleStart = -180, angleExt = 180, angleStep = 1;
    int NumLevel = 1;            //考虑没有采用金字塔下采样时候的，旋转图像的匹配
    double x, y;
    double minScore = 0.98, minDist = 0;
    int isSubPix = 0;

    zv_matchNccCreate(mod, temp, angleStart, angleExt, angleStep, NumLevel);


    clock_t start = clock();   //时钟开始的时间 
    // 测试的程序代码段 
    zv_matchNccFind(mod, src, g_test_matFrame, NumLevel, minScore, &x, &y, minDist, isSubPix);
    clock_t ends = clock();   //时钟的结束时间
    std::cout << "Running Time : " << (double)(ends - start) / CLOCKS_PER_SEC * 1000 << "ms!" << std::endl;


    //画出找到的像素ROI区域
    zv_draRect(dst, x, y, T_w, T_h, 0);

    //在图像上画旋转矩形
    //double angle = -64;
    //zv_draRect2(dst, x+T_w/2 + 30, y+T_h/2 + 80, T_w, T_h, angle, 255);

    //显示输出图像
    std::cout << "(x, y) = " << "(" << x << ", " << y << ")" << std::endl;
    cv::imshow("x1", *(cv::Mat *)dst);
    cv::waitKey(0);

    TEST_RTN_CHK;
}


int testRegisterCPP()
{
    g_test_imgFrame = zv_modImgCreate();
    g_test_matFrame = zv_modMatCreate();

    g_test_matStdOut = zv_modMatCreate();
    g_test_imgStdOut = zv_modImgCreate();

    g_test_matSrc = zv_modMatCreate();
    g_test_matSrc2 = zv_modMatCreate();
    g_test_matDst = zv_modMatCreate();

    test_frm_setSetDisp(TEST_TEST, "框架测试");
    REG_FUNCTION(TEST_TEST, "基本测试", testBase);
    REG_FUNCTION(TEST_TEST, "通过例程", testPass);
    REG_FUNCTION(TEST_TEST, "失败例程", testFail);

    test_frm_setSetDisp(TEST_CORE, "基本功能");
    REG_FUNCTION(TEST_CORE, "生成单位矩阵", zv_matGenEye);
    REG_FUNCTION(TEST_CORE, "修改矩阵的值", zv_matGetData);
    REG_FUNCTION(TEST_CORE, "矩阵的拷贝", zv_matCopy);
    REG_FUNCTION(TEST_CORE, "获得图像的子区域", zv_matGetSub);
    REG_FUNCTION(TEST_CORE, "获得图像轮廓", zv_contGen);
    REG_FUNCTION(TEST_CORE, "矩阵数据转为轮廓", zv_contFromMatrix);
    REG_FUNCTION(TEST_CORE, "图像格式转换", zv_imgConvert);

    test_frm_setSetDisp(TEST_ARITH, "数学运算");
    REG_FUNCTION(TEST_ARITH, "绝对值", zv_arithAbs);
    REG_FUNCTION(TEST_ARITH, "绝对差", zv_arithAbsDiff);
    REG_FUNCTION(TEST_ARITH, "求和运算", zv_arithAdd);
    REG_FUNCTION(TEST_ARITH, "加权和", zv_arithAddWeighted);
    REG_FUNCTION(TEST_ARITH, "正弦", zv_arithSin);
    REG_FUNCTION(TEST_ARITH, "反正弦", zv_arithAsin);
    REG_FUNCTION(TEST_ARITH, "反余弦", zv_arithAcos);
    REG_FUNCTION(TEST_ARITH, "位与", zv_arithAnd);
    REG_FUNCTION(TEST_ARITH, "直方图", zv_arithHist);

    test_frm_setSetDisp(TEST_FILE, "文件");
    REG_FUNCTION(TEST_FILE, "读取图像", zv_fileReadImage);
    REG_FUNCTION(TEST_FILE, "保存图像", zv_fileWriteImage);
    REG_FUNCTION(TEST_FILE, "读取矩阵", zv_fileReadMatrix);
    REG_FUNCTION(TEST_FILE, "保存矩阵", zv_fileWriteMatrix);
    REG_FUNCTION(TEST_FILE, "YAML读写", zv_fileMatrix);
    REG_FUNCTION(TEST_FILE, "YAML更新", zv_fileMatrix_update);

    test_frm_setSetDisp(TEST_IP, "图像处理");
    REG_FUNCTION(TEST_IP, "镜像变换", zv_ipMirror);
    REG_FUNCTION(TEST_IP, "旋转变换", zv_ipRotate);
    REG_FUNCTION(TEST_IP, "缩放变换", zv_ipZoom);
    REG_FUNCTION(TEST_IP, "仿射变换", zv_ipAffine);
    REG_FUNCTION(TEST_IP, "透射变换", zv_ipPerspective);
    REG_FUNCTION(TEST_IP, "彩色转灰度", zv_ipRgbToGray);
    REG_FUNCTION(TEST_IP, "二值化", zv_ipThreshold);
    REG_FUNCTION(TEST_IP, "二值化取反", zv_ipThreshold1);
    REG_FUNCTION(TEST_IP, "直方图均衡化", zv_ipEqualizeHist);
    REG_FUNCTION(TEST_IP, "均值滤波", zv_ipMeanBlur);
    REG_FUNCTION(TEST_IP, "高斯滤波", zv_ipGaussBlur);
    REG_FUNCTION(TEST_IP, "Canny算子边缘提取", zv_ipCanny);
    REG_FUNCTION(TEST_IP, "Soble算子边缘提取", zv_ipSobel);
    REG_FUNCTION(TEST_IP, "形态学开运算", zv_ipOpening);
    REG_FUNCTION(TEST_IP, "形态学闭运算", zv_ipClosing);

    test_frm_setSetDisp(TEST_FEATURE, "特征");
    REG_FUNCTION(TEST_FEATURE, "轮廓面积", zv_contArea);

    test_frm_setSetDisp(TEST_TK, "辅助功能");
    REG_FUNCTION(TEST_TK, "拟合多项式", zv_tkFitPolyn);

    test_frm_setSetDisp(TEST_MATCH, "匹配");
    REG_FUNCTION(TEST_MATCH, "快速模板匹配", zv_matchFastTempl);
    REG_FUNCTION(TEST_MATCH, "模板匹配", zv_matchBestTempl);
    REG_FUNCTION(TEST_MATCH, "多目标匹配", zv_matchMultiTempl);
    REG_FUNCTION(TEST_MATCH, "多目标匹配1", zv_matchMultiTempl1);

    /*=============================新添加代码=======================*/
    REG_FUNCTION(TEST_MATCH, "NCC灰度匹配", zv_matchNccFind);


    return 0;
}
