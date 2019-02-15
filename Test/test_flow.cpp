#include "test_function.h"
#include "test_frame.h"
#include <windows.h>
#include <string>

////流程测试日志：
//测试流程：标定
//进入函数
//调用数量：7
//测试1：[PASS]genMatrix
//
//。。。
//测试7：[PASS]
//测试：PASS
//离开流程

using namespace std;

TEST_FUNC(FlowCalib)
{
    double basePosX = 100;
    double basePosY = 100;

    double stepX = 2;
    double stepY = 2;

    double macPos[3][6] = { 0 };
    double imgPos[9][2] = { 0 };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            macPos[i][2 * j] = basePosX + (j - 1) * stepX;
            macPos[i][2 * j + 1] = basePosY + (i - 1) * stepY;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        ZvImage img = test_frm_loadImgSrc("");
        double locPos[2] = { 0 };
        //find_mark_pos(img, img_pos) ‘通过点定位方法获取图像位置
        imgPos[i][0] = locPos[0];
        imgPos[i][1] = locPos[1];
    }

    zv_matGenData(g_test_matSrc, 9, 2, (double *)imgPos);
    zv_matGenData(g_test_matSrc2, 9, 2, (double *)macPos);
                        
    //估计相似变换矩阵，相机和机械坐标系仅有旋转、缩放、平移关系
    zv_tkEstimateSimilarity(g_test_matSrc, g_test_matSrc2, g_test_matDst, 3, 98, NULL);

    if (0 == g_zv_errLastError)
    {
        zv_fileWriteMatrix(g_test_matDst, TEST_DATA_PATH"calib_result.xml", "calib", 0);
    }

    TEST_RTN_CHK;
}

TEST_FUNC(FlowBlobPos)
{
    ZvImage src = test_frm_getImgSrc(7);
    ZvImage tmp = test_frm_getImgDst(false);
    ZvImage cImg = test_frm_getImgDst(false);

    zv_ipThreshold(src, tmp, 220, 255, false);
    zv_ipOpening(tmp, tmp, 3, 3);
    ZvPtr<ZvContList> contList(zv_modContListCreate(), zv_modContListRelease);

    zv_contGen(tmp, contList, 1, 0);
    int count = zv_contCount(contList);
    TEST_CHK_TRUE(1 <= count);

    zv_contFilter(contList, ZV_FEAT_AREA, 162*162*ZV_PI*0.95, 162*162*ZV_PI*1.02);
    zv_contFilter(contList, ZV_FEAT_CIRCULARITY, 0.8, 1.0);
    count = zv_contCount(contList);
    TEST_CHK_EQ(1, count);
    ZvContour contour = zv_contGetContour(contList, 0);
    zv_ipGrayToRgb(tmp, cImg);
    zv_draContour(cImg, contour, 0xFF00);

    double center[2] = { 0 };
    zv_contCenter(contour, center);
    TEST_TRACE("Center(%.2f, %.2f)\n", center[0], center[1]);
    TEST_RTN_CHK;
}

TEST_FUNC(FlowGrabBasler)
{
    TEST_CHK_RUN(zv_camScan("Basler"));
    TEST_TRACE("Scan: Basler\n");
    TEST_CHK_TRUE(0 != zv_camCount());

    int camId = 0;
    zv_camOpen(camId, 0);
    int camStatus = 0;
    zv_camStatus(camId, &camStatus);
    TEST_CHK_TRUE(ZV_CAM_ST_OPENED == camStatus);
   
    ZvImage img = test_frm_getImgDst(true);
    const int roi_set[4] = { 100, 100, 640, 480 };
    zv_camSetROI(camId, roi_set[0], roi_set[1], roi_set[2], roi_set[3]);
    int roi_get[4] = { 0 };
    zv_camGetROI(camId, roi_get);
    TEST_CHK_ARR_EQ(roi_set, roi_get);

    TEST_CHK_RUN(zv_camGrab(img, camId));
    int grabImgWidth = zv_imgWidth(img);
    int grabImgHeight = zv_imgHeight(img);
    TEST_CHK_TRUE(640 == grabImgWidth);
    TEST_CHK_TRUE(480 == grabImgHeight);
    TEST_RTN_PASS;
}

TEST_FUNC(FlowGrabTIS)
{
    TEST_CHK_RUN(zv_camScan("TIS"));
    TEST_TRACE("Scan: TIS\n");
    TEST_CHK_TRUE(0 != zv_camCount());

    int camId = 0;
    zv_camOpen(camId, 0);
    int camStatus = 0;
    zv_camStatus(camId, &camStatus);
    TEST_CHK_TRUE(ZV_CAM_ST_OPENED == camStatus);

    ZvImage img = test_frm_getImgDst(true);
    zv_camSetROI(camId, 0, 0, 2592, 1944);
    zv_camGrab(img, camId);
    TEST_CHK_TRUE(2592 == zv_imgWidth(img));
    TEST_CHK_TRUE(1944 == zv_imgHeight(img));

    ZvImage imgRoi = test_frm_getImgDst(true);
    const int roi_set[4] = { 100, 100, 640, 480 };
    zv_camSetROI(camId, roi_set[0], roi_set[1], roi_set[2], roi_set[3]);
    int roi_get[4] = { 0 };
    zv_camGetROI(camId, roi_get);
    TEST_CHK_ARR_EQ(roi_set, roi_get);

    zv_camGrab(imgRoi, camId);
    int grabImgWidth = zv_imgWidth(imgRoi);
    int grabImgHeight = zv_imgHeight(imgRoi);
    TEST_CHK_TRUE(640 == grabImgWidth);
    TEST_CHK_TRUE(480 == grabImgHeight);
    zv_camClose(camId);
    TEST_CHK_TRUE(0 == g_zv_errLastError);

    TEST_RTN_PASS;
}

TEST_FUNC(FlowGrabMix)
{
    char * scan = "Basler;TIS";
    TEST_TRACE("Scan: %s\n", scan);
    TEST_CHK_RUN(zv_camScan(scan));

    int basler = 0;
    int tisUsb = 1;
    int camX = 2;
    for (int i = 0; i < zv_camCount(); i++)
    {
        char sn[64] = { 0 };
        zv_camGetInfo(i, ZV_CAM_PS_SN, sn, sizeof(sn));
        if (string("23814598") == sn)
        {
            zv_camOpen(tisUsb, i);
            zv_camGetInfo(i, ZV_CAM_PS_DISPLAY, sn, sizeof(sn));
            TEST_TRACE("TIS Cam Display: %s\n", sn);
            zv_camGetInfo(i, ZV_CAM_PS_DEV_NAME, sn, sizeof(sn));
            TEST_TRACE("TIS Cam DevName: %s\n", sn);
        }
        else if (string("22533411") == sn)
        {
            zv_camOpen(basler, i);
            zv_camGetInfo(i, ZV_CAM_PS_MODEL, sn, sizeof(sn));
            TEST_TRACE("Basler Cam Model: %s\n", sn);
        }
        else
        {
            zv_camOpen(camX, i);
        }
    }
    
    int camStatus = 0;
    zv_camStatus(tisUsb, &camStatus);
    if (ZV_CAM_ST_OPENED == camStatus)
    {
        ZvImage img = test_frm_getImgDst(true);
        zv_camSetROI(tisUsb, 0, 0, 2592, 1944);
        zv_camGrab(img, tisUsb);
        TEST_CHK_TRUE(2592 == zv_imgWidth(img));
        TEST_CHK_TRUE(1944 == zv_imgHeight(img));

        ZvImage imgRoi = test_frm_getImgDst(true);
        const int roi_set[4] = { 100, 100, 640, 480 };
        zv_camSetROI(tisUsb, roi_set[0], roi_set[1], roi_set[2], roi_set[3]);
        int roi_get[4] = { 0 };
        zv_camGetROI(tisUsb, roi_get);
        zv_camGrab(imgRoi, tisUsb);
        TEST_CHK_ARR_EQ(roi_set, roi_get);
        int grabImgWidth = zv_imgWidth(imgRoi);
        int grabImgHeight = zv_imgHeight(imgRoi);
        TEST_CHK_TRUE(640 == grabImgWidth);
        TEST_CHK_TRUE(480 == grabImgHeight);
        zv_camClose(tisUsb);
    }

    zv_camStatus(basler, &camStatus);
    if (ZV_CAM_ST_OPENED == camStatus)
    {
        ZvImage img = test_frm_getImgDst(true);
        zv_camSetROI(basler, 0, 0, 2592, 1944);
        zv_camGrab(img, basler);
        TEST_CHK_TRUE(2592 == zv_imgWidth(img));
        TEST_CHK_TRUE(1944 == zv_imgHeight(img));

        ZvImage imgRoi = test_frm_getImgDst(true);
        const int roi_set[4] = { 100, 100, 640, 480 };
        zv_camSetROI(basler, roi_set[0], roi_set[1], roi_set[2], roi_set[3]);
        int roi_get[4] = { 0 };
        zv_camGetROI(basler, roi_get);
        zv_camGrab(imgRoi, basler);
        TEST_CHK_ARR_EQ(roi_set, roi_get);
        int grabImgWidth = zv_imgWidth(imgRoi);
        int grabImgHeight = zv_imgHeight(imgRoi);
        TEST_CHK_TRUE(640 == grabImgWidth);
        TEST_CHK_TRUE(480 == grabImgHeight);
        zv_camClose(basler);
    }

    TEST_RTN_CHK;
}

TEST_FUNC(FlowMeasLine)
{
    unsigned char mr[ZV_MEASURER_SIZE] = { 0 };
    ZvImage src = test_frm_getImgSrc(6);
    ZvImage img1 = test_frm_getImgDst(false);
    g_zv_sysLineWidth = 1;

    TEST_CHK_RUN(zv_measGenLineMr(mr, 323, 236.5, 400, 120, 13.95, ZV_INTERP_LINEAR, -1, -1));
    TEST_CHK_RUN(zv_imgCopy(src, img1));
    TEST_CHK_RUN(zv_ipGrayToRgb(img1, img1));
    TEST_CHK_RUN(zv_draMeasurer(img1, mr, 0xFF, 0xFF00));
    zv_measSetMrAdvParam(mr, 5, 40, ZV_POLAR_TOLIGHT, ZV_EDGE_FIRST);
    TEST_CHK_TRUE(0 == g_zv_errLastError);

    double lineParam[4] = { 0 };
    TEST_CORE_RUN(zv_measLine(src, mr, lineParam, g_test_matDst));
    double line[4] = { 0 };
    zv_tkLineFromParam(lineParam[0], lineParam[1], lineParam[2], lineParam[3], line);
    TEST_CHK_RUN(zv_draLine(img1, line[0], line[1], line[2], line[3], 0xFF00));
    for (int i = 0; i < zv_matRows(g_test_matDst); i++)
    {
        double temp[3] = { 0 };
        TEST_CHK_RUN(zv_matGetRow(g_test_matDst, i, temp, sizeof(temp)/sizeof(double)));
        TEST_CHK_RUN(zv_draMarker(img1, temp[0], temp[1], 0, 20, 0xFF0000));
    }
    TEST_TRACE("Line(%f, %f, %f, %f)\n", line[0], line[1], line[2], line[3]);
    TEST_RTN_CHK;
}

TEST_FUNC(FlowMeasCircle)
{
    unsigned char mr[ZV_MEASURER_SIZE] = { 0 };
    ZvImage src = test_frm_getImgSrc(7);
    ZvImage img1 = test_frm_getImgDst(false);
    g_zv_sysLineWidth = 1;

    double cx = 305.679214;
    TEST_CHK_RUN(zv_measGenCircleMr(mr, cx, 227.119476, 166.396559, 0, 360, 60.758312, ZV_INTERP_LINEAR, -1, -1));
    TEST_CHK_RUN(zv_imgCopy(src, img1));
    TEST_CHK_RUN(zv_ipGrayToRgb(img1, img1));
    TEST_CHK_RUN(zv_draMeasurer(img1, mr, 0xFF, 0xFF00));
    TEST_CHK_RUN(zv_draCircle(img1, cx, 227.119476, 166.396559, 0xFF0000));
    zv_measSetMrAdvParam(mr, 5, 20, ZV_POLAR_TODARK, ZV_EDGE_MAX);
    TEST_CHK_TRUE(0 == g_zv_errLastError);

    double circle[3] = { 0 };
    TEST_CORE_RUN(zv_measCircle(src, mr, circle, g_test_matDst));

    TEST_CHK_RUN(zv_draCircle(img1, circle[0], circle[1], circle[2], 0xFF00));
    for (int i = 0; i < zv_matRows(g_test_matDst); i++)
    {
        double temp[3] = { 0 };
        TEST_CHK_RUN(zv_matGetRow(g_test_matDst, i, temp, sizeof(temp) / sizeof(double)));
        TEST_CHK_RUN(zv_draMarker(img1, temp[0], temp[1], 0, 20, 0xFF0000));
    }
    TEST_TRACE("Circle(%f, %f, %f)\n", circle[0], circle[1], circle[2]);
    TEST_RTN_PASS;
}

TEST_FUNC(FlowMeasCircle1)
{
    unsigned char mr[ZV_MEASURER_SIZE] = { 0 };
    ZvImage src = test_frm_getImgSrc(7);
    ZvImage img1 = test_frm_getImgDst(false);
    g_zv_sysLineWidth = 1;

    double cx = 305.679214;
    TEST_CHK_RUN(zv_measGenCircleMr(mr, cx, 227.119476, 166.396559, 0, 355, 60.758312, ZV_INTERP_LINEAR, -1, -1));
    TEST_CHK_RUN(zv_imgCopy(src, img1));
    TEST_CHK_RUN(zv_ipGrayToRgb(img1, img1));
    TEST_CHK_RUN(zv_draMeasurer(img1, mr, 0xFF, 0xFF00));
    TEST_CHK_RUN(zv_draCircle(img1, cx, 227.119476, 166.396559, 0xFF0000));
    zv_measSetMrAdvParam(mr, 5, 20, ZV_POLAR_TODARK, ZV_EDGE_MAX);
    TEST_CHK_TRUE(0 == g_zv_errLastError);

    double circle[3] = { 0 };
    TEST_CORE_RUN(zv_measCircle(src, mr, circle, g_test_matDst));

    TEST_CHK_RUN(zv_draCircle(img1, circle[0], circle[1], circle[2], 0xFF00));
    for (int i = 0; i < zv_matRows(g_test_matDst); i++)
    {
        double temp[3] = { 0 };
        TEST_CHK_RUN(zv_matGetRow(g_test_matDst, i, temp, sizeof(temp) / sizeof(double)));
        TEST_CHK_RUN(zv_draMarker(img1, temp[0], temp[1], 0, 20, 0xFF0000));
    }
    TEST_TRACE("Circle(%f, %f, %f)\n", circle[0], circle[1], circle[2]);
    TEST_RTN_PASS;
}

TEST_FUNC(FlowLinesIntersect)
{
    g_zv_sysLineWidth = 1;
    unsigned char mr0[ZV_MEASURER_SIZE] = { 0 };
    unsigned char mr1[ZV_MEASURER_SIZE] = { 0 };
    TEST_CHK_RUN(zv_measGenLineMr(mr0, 128.78, 284.64, 514.21, 217.56, -90, ZV_INTERP_LINEAR, 20, 5));
    TEST_CHK_RUN(zv_measGenLineMr(mr1, 334.29, 461.93, 570.77, 214.94, 180, ZV_INTERP_LINEAR, 20, 5));

    ZvImage src = test_frm_loadImgSrc("10.bmp");
    ZvImage img1 = test_frm_getImgDst(false);

    TEST_CHK_RUN(zv_imgCopy(src, img1));
    TEST_CHK_RUN(zv_ipGrayToRgb(img1, img1));
    TEST_CHK_RUN(zv_draMeasurer(img1, mr0, 0xFF, 0xFF00));
    TEST_CHK_RUN(zv_draMeasurer(img1, mr1, 0xFF, 0xFF00));

    zv_measSetMrAdvParam(mr0, 5, 10, ZV_POLAR_ALL, ZV_EDGE_FIRST);
    zv_measSetMrAdvParam(mr1, 5, 10, ZV_POLAR_ALL, ZV_EDGE_FIRST);
    TEST_CHK_TRUE(0 == g_zv_errLastError);

    double lineParam[4] = { 0 };
    TEST_CORE_RUN(zv_measLine(src, mr0, lineParam, g_test_matDst));
    double line[4] = { 0 };
    zv_tkLineFromParam(lineParam[0], lineParam[1], lineParam[2], lineParam[3], line);
    TEST_CHK_RUN(zv_draLine(img1, round(line[0]), round(line[1]), round(line[2]), round(line[3]), 0xFF0000));
    TEST_TRACE("Line0(%f, %f, %f, %f)\n", line[0], line[1], line[2], line[3]);

    TEST_CORE_RUN(zv_measLine(src, mr1, lineParam, g_test_matDst));
    double line1[4] = { 0 };
    zv_tkLineFromParam(lineParam[0], lineParam[1], lineParam[2], lineParam[3], line1);
    TEST_CHK_RUN(zv_draLine(img1, round(line1[0]), round(line1[1]), round(line1[2]), round(line1[3]), 0xFF00));
    TEST_TRACE("Line1(%f, %f, %f, %f)\n", line1[0], line1[1], line1[2], line1[3]);

    double sect[2] = { 0 };
    if (zv_tkIntersectLL(line[0], line[1], line[2], line[3], line1[0], line1[1], line1[2], line1[3], sect))
    {
        TEST_TRACE("Sect(%.2f, %.2f)\n", sect[0], sect[1]);
        TEST_CHK_RUN(zv_draMarker(img1, round(sect[0]), round(sect[1]), 0, 20, 0xFF));
        char text[32] = { 0 };
        sprintf(text, "%.2f, %.2f", sect[0], sect[1]);
        zv_draText(img1, text, round(sect[0]), round(sect[1]), 1, 0xFF);
    }
    else
    {
        TEST_TRACE("无交点\n", sect[0], sect[1]);
    }

    TEST_RTN_PASS;
}

int testRegisterFlow()
{
    test_frm_setSetDisp(TEST_FLOW, "流程");
    REG_FUNCTION(TEST_FLOW, "Basler采集", FlowGrabBasler);
    REG_FUNCTION(TEST_FLOW, "TIS采集", FlowGrabTIS);
    REG_FUNCTION(TEST_FLOW, "混合采集", FlowGrabMix);
    REG_FUNCTION(TEST_FLOW, "标定流程", FlowCalib);
    REG_FUNCTION(TEST_FLOW, "轮廓重心定位", FlowBlobPos);
    REG_FUNCTION(TEST_FLOW, "测量直线", FlowMeasLine);
    REG_FUNCTION(TEST_FLOW, "测量圆", FlowMeasCircle);
    REG_FUNCTION(TEST_FLOW, "测量圆1", FlowMeasCircle1);
    REG_FUNCTION(TEST_FLOW, "直线交点", FlowLinesIntersect);
    return 0;
}
