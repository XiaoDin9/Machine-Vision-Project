#include "zv_private.h"
#include "zv_meas.h"
#include "basis/zv_basis.h"
#include "tools/zv_tools.h"


int zv_meas_genRect(void * mr, double x, double y, double width, double height)
{
    ZV_CHK_NULL1(mr);
    ZvRectMeas * p = (ZvRectMeas*)mr;
    p->type = ZV_MEAS_RECT;
    p->x = x;
    p->y = y;
    p->w = width;
    p->h = height;
    return ZV_ST_OK;
}

int zv_meas_genRect2(void *mr, double cx, double cy, double width, double height, double angle, int interp)
{
    ZV_CHK_NULL1(mr);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_7;
    }

    ZvRect2Meas *p = (ZvRect2Meas*)mr;
    p->type = ZV_MEAS_RECT2;
    p->cx = cx;
    p->cy = cy;
    p->w = width;
    p->h = height;
    p->angle = angle;
    p->interp = interp;
    return ZV_ST_OK;
}

int zv_meas_genArc(void *mr, double cx, double cy, double r, double startA, double extentA, double annR, int interp)
{
    ZV_CHK_NULL1(mr);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_8;
    }
    while (extentA > 360)
    {
        extentA -= 360;
    }

    ZvArcMeas *p = (ZvArcMeas*)mr;
    p->type = ZV_MEAS_ARC;
    p->cx = cx;
    p->cy = cy;
    p->r = r;
    p->startA = startA;
    p->extA = extentA;
    p->annR = annR;
    p->interp = interp;
    return ZV_ST_OK;
}

// 图像的灰度分布 1行n列矩阵
int zv_meas_imgProjection(ZvImage img, ZvMatrix proj, bool isRows)
{
    ZV_CHK_NULL2(img, proj);

    _ZvMatrix stat;
    if (isRows)
    {
        ZV_RUN_RTN(zv_arith_statCol(img, &stat, 0));
    }
    else
    {
        ZV_RUN_RTN(zv_arith_statRow(img, &stat, 0));
    }

    stat = stat.reshape(0, 1);
    stat.convertTo(ZV_ADP_MAT_GETM(proj), CV_64F, 1. / (isRows ? zv_img_height(img) : zv_img_width(img)));

    return ZV_ST_OK;
}

//ROI坐标映射到源图像坐标，y为负值则取ROI中心，否则为坐标
int zv_meas_posMapToImage(ZvImage img, void *mr, double &x, double &y)
{
    ZV_CHK_NULL2(img, mr);
  
    int mrType = zv_meas_mrType(mr);
    if (ZV_MEAS_CIRCLE == mrType || ZV_MEAS_ARC == mrType)
    {
        ZvArcMeas * arcMr;
        if (ZV_MEAS_CIRCLE == mrType)
        {
            arcMr = &((ZvCircleMeas *)mr)->arcMr;
        }
        else
        {
            arcMr = (ZvArcMeas *)mr;
            if (0 > y)
            {
                y = arcMr->annR;
            }
        }
        double dstR = arcMr->r - arcMr->annR + y;
        y = dstR*sin(x / arcMr->r) + arcMr->cy;
        x = dstR*cos(x / arcMr->r) + arcMr->cx;
    }
    else if (ZV_MEAS_RECT == mrType)
    {
        ZvRectMeas * p = (ZvRectMeas *)mr;
        if (0 > y)
        {
            y = p->h / 2;
        }
        x += p->x;
        y += p->y;
    }
    else if (ZV_MEAS_RECT2 == mrType || ZV_MEAS_LINE == mrType)
    {
        ZvRect2Meas * r2Mr;
        if (ZV_MEAS_LINE == mrType)
        {
            r2Mr = &((ZvLineMeas *)mr)->rt2Mr;
        }
        else
        {
            r2Mr = (ZvRect2Meas *)mr;
            if (0 > y)
            {
                y = r2Mr->h / 2;
            }
        }

        double sinAngle = sin(ZV_TO_RAD(r2Mr->angle));
        double cosAngle = cos(ZV_TO_RAD(r2Mr->angle));

        double dX = x - (r2Mr->w / 2.0 - 0.5);
        double dY = y - (r2Mr->h / 2.0 - 0.5);
        x = r2Mr->cx + dX * cosAngle - dY * sinAngle;
        y = r2Mr->cy + dX * sinAngle + dY * cosAngle;
    }
    else
    {
        return ZV_ERR_MR_INVALID;
    }
    
    if (x < 0 || x >= zv_img_width(img))
    {
        return ZV_ERR_MR_PT_OUTER_X;
    }
    if (y < 0 || y >= zv_img_height(img))
    {
        return ZV_ERR_MR_PT_OUTER_Y;
    }
    return ZV_ST_OK;
}

int zv_meas_posImpl(ZvMatrix proj, ZvMatrix pts, int filterSize, double thresh, int type, int select)
{
    ZV_CHK_NULL2(proj, pts);
    if (type > ZV_POLAR_ALL)
    {
        return ZV_ERR_FA_RANGE_5;
    }
    if (select > ZV_EDGE_ALL)
    {
        return ZV_ERR_FA_RANGE_6;
    }
    
    int cols = zv_mat_cols(proj);
    double *pData = ZV_ADP_MAT_GETM(proj).ptr<double>();
    filterSize = filterSize | 0x1;
    //ZV_RUN_RTN(zv_ip_sobel(proj, proj, 1, 0, filterSize));
    ZV_RUN_RTN(zv_ip_gaussBlur(proj, proj, filterSize));
    for (int i = 0; i < cols-1; i++)
    {
        pData[i] = pData[i + 1] - pData[i];
    }
    pData[cols - 1] = 0;

    std::vector<cv::Point3d>  measResult;
    for (int i = 0; i < cols; i++)
    {
        //type边缘极性：0-白黑(负数)、1-黑白、2-所有；
        // 筛选符合要求的边界点 阈值、极性、位置、极值。
        double fabsCurr = fabs(pData[i]);
        double fabsPrev = 0 == i ? 0 : fabs(pData[i - 1]);
        double fabsNext = cols - 1 == i ? 0 : fabs(pData[i + 1]);

        if (fabsCurr >= thresh && fabsCurr >= fabsPrev && fabsCurr >= fabsNext) //极值点
        {
            // 记下位置和阈值
            if ((ZV_POLAR_ALL == type)
                || (pData[i] < 0 && ZV_POLAR_TODARK == type)
                || (pData[i] >= 0 && ZV_POLAR_TOLIGHT == type))
            {
                double pos = i;
                double maxValue = pData[i];
                if (0 != i && cols - 1 != i)
                {
                    double pts[] = { (double)i - 1, pData[i - 1], (double)i, pData[i], (double)i + 1, pData[i + 1] };
                    zv_tk_subPixInterp1d(pts, 3, pos, maxValue);
                }
                measResult.push_back(cv::Point3d(pos, -1, maxValue));
                if (ZV_EDGE_FIRST == select)
                {
                    break;
                }
            }
        }
    }

    if (0 == measResult.size())
    {
        ZV_ADP_MAT_SETM(pts, cv::Mat());
        return ZV_ST_OK;
    }

    //select边缘位置：0-第一点、1-最后点、2-最强点、3-所有点。
    if (ZV_EDGE_LAST == select)
    {
        measResult[0] = measResult[measResult.size() - 1];
    }
    else if (ZV_EDGE_MAX == select)
    {
        for (int i = 1; i < measResult.size(); i++)
        {
            if (fabs(measResult[i].z) > fabs(measResult[0].z))
            {
                measResult[0] = measResult[i];
            }
        }
    }

    if (ZV_EDGE_ALL != select && measResult.size() > 1)
    {
        measResult.resize(1);
    }
    cv::Mat edgeMat(measResult, true);
    edgeMat = edgeMat.reshape(1); //nX1三通道改为nX3单通道
    ZV_ADP_MAT_SETM(pts, edgeMat);

    return ZV_ST_OK;
}

// 区域的灰度分布 即：从白到黑 和 从黑到白的 灰度值变换情况
int zv_meas_projection(ZvImage _img, ZvMatrix proj, void *mr)
{
    ZV_CHK_NULL3(_img, proj, mr);
    if (1 != zv_img_channels(_img))
    {
        return ZV_ERR_I_ONLY_CN1;
    }

    _ZvImage roi;
    ZvRectMeas * meas = (ZvRectMeas*)mr;

    switch (meas->type)
    {
    case ZV_MEAS_ARC:
    {
        ZvArcMeas * arcMr = (ZvArcMeas *)mr;
        //圆环区域展开
        ZV_RUN_RTN(zv_ip_warpRing(_img, &roi, arcMr->cx, arcMr->cy, arcMr->r,
            arcMr->startA, arcMr->extA, arcMr->annR, arcMr->interp));
        break;
    }
    case ZV_MEAS_RECT2:
    {
        ZvRect2Meas *r2Mr = (ZvRect2Meas *)mr;
        ZV_RUN_RTN(zv_ip_warpRect2(_img, &roi, r2Mr->cx, r2Mr->cy,
            r2Mr->w, r2Mr->h, r2Mr->angle, r2Mr->interp));
        break;
    }
    case ZV_MEAS_RECT:
        ZV_RUN_RTN(zv_img_getSub(_img, &roi, (int)meas->x, (int)meas->y, (int)meas->w, (int)meas->h));
        break;
    default:
        return ZV_ERR_MR_INVALID;
    }

    zv_meas_imgProjection(&roi, proj, true);

    return ZV_ST_OK;
}

// 检测点
int zv_meas_pos(ZvImage img, ZvMatrix pts, void *mr, int filterSize, double thresh, int type, int select)
{
    ZV_CHK_NULL3(img, pts, mr);
    if (type > ZV_POLAR_ALL)
    {
        return ZV_ERR_FA_RANGE_6;
    }
    if (select > ZV_EDGE_ALL)
    {
        return ZV_ERR_FA_RANGE_7;
    }

    _ZvMatrix proj;
    ZV_RUN_RTN(zv_meas_projection(img, &proj, mr));
    ZV_RUN_RTN(zv_meas_posImpl(&proj, pts, filterSize, thresh, type, select));

    for (int i = 0; i < zv_mat_rows(pts); i++)
    {
        double *val = ZV_ADP_MAT_GETM(pts).ptr<double>();
        zv_meas_posMapToImage(img, mr, val[0], val[1]);
        val += 3;
    }

    return ZV_ST_OK;
}

//检测间距 独立测量功能，延后开发
int zv_meas_pairs(ZvImage img, ZvMatrix pairs, void *mr, int filterSize, double thresh, int type, int select)
{
    return ZV_ERR_G_UNFINISHED;
    ZV_CHK_NULL3(img, pairs, mr);
    _ZvMatrix proj;
    zv_meas_projection(img, &proj, mr);

    int m = 0, num1, num2, num3;
    double distGray[50];
    for (int i = 0; i < proj.rows; i++)
    {
        if (i == 0)
        {
            num1 = 0;
            num2 = (int)proj.at<double>(i, 1);
            num3 = (int)proj.at<double>(i + 1, 1);
        }
        else if (i == proj.rows - 1)
        {
            num3 = 0;
            num1 = (int)proj.at<double>(i - 1, 1);
            num2 = (int)proj.at<double>(i, 1);
        }
        else
        {
            num1 = (int)proj.at<double>(i - 1, 1);
            num2 = (int)proj.at<double>(i, 1);
            num3 = (int)proj.at<double>(i + 1, 1);
        }


        if (type == 0 && num1 < num2 && num2 > num3)    // 黑色的区域的宽度
        {
            distGray[m] = (double)proj.at<double>(i + 1, 0) - (double)proj.at<double>(i, 0);
            m++;
        }
        if (type == 1 && num2 < 0 && num1 > num2 && num2 < num3)   // 求白色区域的间距 (白到黑）
        {
            distGray[m] = (double)proj.at<double>(i + 1, 0) - (double)proj.at<double>(i, 0);
            m++;
        }
    }

    cv::Mat matD(m, 1, CV_64FC1);
    for (int i = 0; i < m; i++)
        matD.at<double>(i, 0) = (double)distGray[i];

    ZV_ADP_MAT_SETM(pairs, matD);
    return ZV_ST_OK;
}


int zv_meas_genLineMr(void *mr, double cx, double cy, double width, double height,
    double angle, int interp, int subNum, int subWidth)
{
    ZV_CHK_NULL1(mr);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_7;
    }

    ZvLineMeas *p = (ZvLineMeas*)mr;
    p->mrType = ZV_MEAS_LINE;
    ZV_RUN_RTN(zv_meas_genRect2(&p->rt2Mr, cx, cy, width, height, angle, interp));
    p->subNum = 2 > subNum ? 8 : subNum;
    p->subWidth = subWidth;
    if (-1 == subWidth)
    {
        p->subWidth = std::min((int)width / 10, 10);
        p->subWidth = std::max(p->subWidth, 5);
    }
    p->thresh = 30;
    p->filterSize = 5;
    p->type = ZV_POLAR_ALL;
    p->select = ZV_EDGE_FIRST;
    return ZV_ST_OK;
}

int zv_meas_genCircleMr(void *mr, double cx, double cy, double r, double startA,
    double extentA, double annR, int interp, int subNum, int subWidth)
{
    ZV_CHK_NULL1(mr);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_8;
    }
    if (extentA > 360)
    {
        return ZV_ERR_FA_RANGE_6;
    }

    ZvCircleMeas *p = (ZvCircleMeas*)mr;
    p->mrType = ZV_MEAS_CIRCLE;
    ZV_RUN_RTN(zv_meas_genArc(&p->arcMr, cx, cy, r, startA, extentA, annR, interp));
    p->subNum = 3 > subNum ? 8 : subNum;
    p->subWidth = subWidth;
    if (-1 == subWidth)
    {
        p->subWidth = std::min((int)(2 * ZV_PI*r*extentA / 360) / 10, 10);
        p->subWidth = std::max(p->subWidth, 5);
    }
    p->thresh = 30;
    p->filterSize = 5;
    p->type = ZV_POLAR_ALL;
    p->select = ZV_EDGE_FIRST;

    return ZV_ST_OK;
}

int zv_meas_setMrAdvParam(void *mr, int filterSize, double thresh, int type, int select)
{
    ZV_CHK_NULL1(mr);
    if (type > ZV_POLAR_ALL)
    {
        return ZV_ERR_FA_RANGE_4;
    }
    if (select >= ZV_EDGE_ALL) //只能取其中一点
    {
        return ZV_ERR_FA_RANGE_5;
    }
    ZvLineMeas *p = (ZvLineMeas*)mr;
    if (ZV_MEAS_LINE == p->mrType)
    {
        p->thresh = thresh;
        p->filterSize = filterSize;
        p->type = type;
        p->select = select;
        return ZV_ST_OK;
    }
    ZvCircleMeas *p1 = (ZvCircleMeas*)mr;
    if (ZV_MEAS_CIRCLE == p1->mrType)
    {
        p1->thresh = thresh;
        p1->filterSize = filterSize;
        p1->type = type;
        p1->select = select;
        return ZV_ST_OK;
    }
    return ZV_ERR_MR_INVALID;
}

int zv_meas_getMrAdvParam(void *mr, int *filterSize, double *thresh, int *type, int *select)
{
    ZV_CHK_NULL1(mr);
    ZvLineMeas *p = (ZvLineMeas*)mr;
    if (ZV_MEAS_LINE == p->mrType)
    {
        if (thresh) *thresh = p->thresh;
        if (filterSize) *filterSize = p->filterSize;
        if (type) *type = p->type;
        if (select) *select = p->select;
        return ZV_ST_OK;
    }
    ZvCircleMeas *p1 = (ZvCircleMeas*)mr;
    if (ZV_MEAS_CIRCLE == p1->mrType)
    {
        if (thresh) *thresh = p1->thresh;
        if (filterSize) *filterSize = p1->filterSize;
        if (type) *type = p1->type;
        if (select) *select = p1->select;
        return ZV_ST_OK;
    }
    return ZV_ERR_MR_INVALID;
}

int zv_meas_line(ZvImage img, void *mr, double *cx, double *cy, double *angle, double *length, ZvMatrix pts)
{
    ZV_CHK_NULL6(img, mr, cx, cy, angle, length);
    ZvLineMeas * lmr = (ZvLineMeas*)mr;
    if (ZV_MEAS_LINE != lmr->mrType)
    {
        return ZV_ERR_MR_MR_UNMATCH;
    }

    _ZvImage roi;
    _ZvMatrix proj;
    //RECT2区域X方向展开
    ZV_RUN_RTN(zv_ip_warpRect2(img, &roi, lmr->rt2Mr.cx, lmr->rt2Mr.cy, lmr->rt2Mr.w,
        lmr->rt2Mr.h, lmr->rt2Mr.angle, lmr->rt2Mr.interp));

    //切分子区域
    int width = zv_img_width(&roi);
    int height = zv_img_height(&roi);
    if (width <= lmr->subWidth)
    {
        return ZV_ERR_FA_RANGE_9;
    }

    double subStep = (double)(width - lmr->subWidth) / (lmr->subNum - 1); //浮点数步长，避免ROI位置的累计误差
    std::vector<cv::Point3d> linePts;
    for (int i = 0; i < lmr->subNum; i++)
    {
        _ZvImage subRoi;
        _ZvMatrix proj, subPos;
        zv_img_getSub(&roi, &subRoi, cvRound(i*subStep), 0, lmr->subWidth, height);
        ZV_RUN_RTN(zv_meas_imgProjection(&subRoi, &proj, false));
        ZV_RUN_RTN(zv_meas_posImpl(&proj, &subPos, lmr->filterSize, lmr->thresh, lmr->type, lmr->select));
        double *val = ZV_ADP_MAT_GETM(&subPos).ptr<double>(); //列方向运算，需要交换行列坐标
        if (!val)
        {
            continue;
        }
        cv::Point3d roiPos(cvRound(i*subStep) + lmr->subWidth/2.0 - 0.5, val[0], val[2]);
        //映射到图像坐标
        if (ZV_ST_OK == zv_meas_posMapToImage(img, mr, roiPos.x, roiPos.y))
        {
            linePts.push_back(roiPos);
        }
    }

    if (2 > linePts.size())
    {
        return ZV_ERR_MR_PTS_NUM;
    }

    //拟合直线
    cv::Mat matPts(linePts, true);
    matPts = matPts.reshape(1);
    _ZvMatrix fitPts;
    ZV_ADP_MAT_SETM(&fitPts, matPts(cv::Rect(0, 0, 2, matPts.rows)));
    ZV_RUN_RTN(zv_tk_fitLine2D(&fitPts, cx, cy, angle, length));

    if (NULL != pts)
    {
        ZV_ADP_MAT_SETM(pts, matPts);
    }

    return ZV_ST_OK;
}

int zv_meas_circle(ZvImage img, void *mr, double *cx, double * cy, double *r, ZvMatrix pts)
{
    ZV_CHK_NULL5(img, mr, cx, cy, r);
    ZvCircleMeas * cmr = (ZvCircleMeas*)mr;
    if (ZV_MEAS_CIRCLE != cmr->mrType)
    {
        return ZV_ERR_MR_MR_UNMATCH;
    }
   
    _ZvImage roi;
    _ZvMatrix proj;
    //圆环区域径向展开
    ZV_RUN_RTN(zv_ip_warpRing(img, &roi, cmr->arcMr.cx, cmr->arcMr.cy, cmr->arcMr.r,
        cmr->arcMr.startA, cmr->arcMr.extA, cmr->arcMr.annR, cmr->arcMr.interp));
    
    //切分子区域
    int width = zv_img_width(&roi);
    int height = zv_img_height(&roi);
    if (width <= cmr->subWidth)
    {
        return ZV_ERR_FA_RANGE_9;
    }
    
    double subStep;  //环形情况下避免第一个和最后一个测量区域重合。
    if (cmr->arcMr.extA + 180.0 / cmr->subWidth >= 360)
    {
        subStep = (double)width / cmr->subNum;
    }
    else
    {
        subStep = (width - cmr->subWidth) / (cmr->subNum - 1.0);
    }
    std::vector<cv::Point3d> circlePts;
    for (int i = 0; i < cmr->subNum; i++)
    {
        _ZvImage subRoi;
        _ZvMatrix proj, subPos;
        zv_img_getSub(&roi, &subRoi, cvRound(i*subStep), 0, cmr->subWidth, height);
        ZV_RUN_RTN(zv_meas_imgProjection(&subRoi, &proj, false));
        ZV_RUN_RTN(zv_meas_posImpl(&proj, &subPos, cmr->filterSize, cmr->thresh, cmr->type, cmr->select));
        double *val = ZV_ADP_MAT_GETM(&subPos).ptr<double>(); //列方向运算，需要交换行列坐标
        if (!val)
        {
            continue;
        }

        cv::Point3d roiPos(cvRound(i*subStep) + cmr->subWidth/2.0 - 0.5, val[0], val[2]);
        if (ZV_ST_OK == zv_meas_posMapToImage(img, mr, roiPos.x, roiPos.y))    //映射到图像坐标
        {
            circlePts.push_back(roiPos);
        }
    }

    if (3 > circlePts.size())
    {
        return ZV_ERR_MR_PTS_NUM;
    }

    //拟合圆
    cv::Mat matPts(circlePts, true);
    matPts = matPts.reshape(1);
    _ZvMatrix fitPts;
    ZV_ADP_MAT_SETM(&fitPts, matPts(cv::Rect(0, 0, 2, matPts.rows)));
    ZV_RUN_RTN(zv_tk_fitCircle(&fitPts, cx, cy, r));

    if (NULL != pts)
    {
        ZV_ADP_MAT_SETM(pts, matPts);
    }

    return ZV_ST_OK;
}
