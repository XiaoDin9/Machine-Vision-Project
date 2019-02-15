#include "zv_private.h"
#include "zv_feature.h"
#include "tools/zv_tools.h"


using namespace cv;

inline void zv_cont_momentsAll(ZvContour cont)
{
    if (!cont->status.mSpatial)
    {
        cont->featVal.moment = moments(ZV_ADP_CONT(cont));
        cont->status.mSpatial = 1;
        cont->status.mCentral = 1;
        cont->status.mNormalC = 1;
    }
}

inline int zv_cont_updateFeature(ZvContour cont, int feature)
{
    ZV_CHK_NULL1(cont);

    switch (feature)
    {
    case ZV_FEAT_AREA:
        zv_cont_area(cont);
        break;
    case ZV_FEAT_CIRCULARITY:
        zv_cont_circularity(cont);
        break;
    case ZV_FEAT_GX:
    case ZV_FEAT_GY:
        zv_cont_center(cont, NULL, NULL);
        break;
    case ZV_FEAT_PERIMETER:
        zv_cont_length(cont);
        break;
    case ZV_FEAT_COMPACT:
        zv_cont_compactness(cont);
        break;
    case ZV_FEAT_ISCONVEX:
        zv_cont_isConvex(cont);
        break;
    case ZV_FEAT_HULL_AREA:
    case ZV_FEAT_CONVEXITY:
        zv_cont_convexity(cont);
        break;
    case ZV_FEAT_RECT_X:
    case ZV_FEAT_RECT_Y:
    case ZV_FEAT_RECT_W:
    case ZV_FEAT_RECT_H:
    case ZV_FEAT_RECT_RX:
    case ZV_FEAT_RECT_BY:
    case ZV_FEAT_RECT_RATIO:
        ZV_RUN_RTN(zv_cont_smallestRect(cont, NULL, NULL, NULL, NULL));
        break;
    case ZV_FEAT_EA_MAJOR:
    case ZV_FEAT_EA_MINOR:
    case ZV_FEAT_EA_ANGLE:
    case ZV_FEAT_EA_RATIO:
        zv_cont_ellipticAxis(cont, NULL, NULL, NULL);
        break;
    case ZV_FEAT_RECT2_CX:
    case ZV_FEAT_RECT2_CY:
    case ZV_FEAT_RECT2_W:
    case ZV_FEAT_RECT2_H:
    case ZV_FEAT_RECT2_ANGLE:
    case ZV_FEAT_RECT2_RATIO:
        zv_cont_smallestRect2(cont, NULL, NULL, NULL, NULL, NULL);
        break;
    case ZV_FEAT_OC_X:
    case ZV_FEAT_OC_Y:
    case ZV_FEAT_OC_R:
        zv_cont_smallestCircle(cont, NULL, NULL, NULL);
        break;
    case ZV_FEAT_HU0:
    case ZV_FEAT_HU1:
    case ZV_FEAT_HU2:
    case ZV_FEAT_HU3:
    case ZV_FEAT_HU4:
    case ZV_FEAT_HU5:
    case ZV_FEAT_HU6:
        zv_cont_huMoments(cont, NULL);
        break;
    default:
        zv_cont_momentsAll(cont);
        break;
    }
    return ZV_ST_OK;
}

// 求轮廓的面积
double zv_cont_area(ZvContour contour, bool isOriented)
{
    if (NULL == contour)
    {
        return 0;
    }

    if (!contour->status.area)
    {
        contour->featVal.area = contourArea(ZV_ADP_CONT(contour), true);
        contour->status.area = 1;
    }
    return isOriented ? contour->featVal.area : abs(contour->featVal.area);
}

// 求轮廓的周长
double zv_cont_length(ZvContour contour, bool isClosed)
{
    if (NULL == contour)
    {
        return 0;
    }

    if (!isClosed)
    {
        return arcLength(ZV_ADP_CONT(contour), false);
    }

    if (!contour->status.perimeter)
    {
        contour->featVal.perimeter = arcLength(ZV_ADP_CONT(contour), true);
        contour->status.perimeter = 1;
    }
    return contour->featVal.perimeter;
}

// 求轮廓的重心
int zv_cont_center(ZvContour contour, double *centerX, double *centerY)
{
    ZV_CHK_NULL1(contour);

    if (!contour->status.gc)
    {
        zv_cont_momentsAll(contour);
        double m00 = contour->featVal.moment.m00;
        if (fabs(m00) > DBL_EPSILON)
        {
            contour->featVal.gcX = (contour->featVal.moment.m10 / m00);
            contour->featVal.gcY = (contour->featVal.moment.m01 / m00);
        }
        contour->status.gc = 1;
    }

    if (centerX)
        *centerX = contour->featVal.gcX;
    if (centerY)
        *centerY = contour->featVal.gcY;

    return ZV_ST_OK;
}

// 求凸性
int zv_cont_isConvex(ZvContour cont)
{
    if (NULL == cont)
    {
        return false;
    }

    if (!cont->status.isConvex)
    {
        bool isConvex = isContourConvex(ZV_ADP_CONT(cont));
        cont->featVal.isConvex = (double)isConvex;
        cont->status.isConvex = 1;
        if (isConvex && !cont->status.convexity)
        {
            cont->status.convexity = cont->status.area;
            cont->featVal.hullArea = cont->featVal.area;
            cont->featVal.convexity = (double)cont->status.convexity;  //如果面积没有计算过，convexity状态无法更新
        }
    }
    return cont->featVal.isConvex > 0.5;
}

double zv_cont_convexity(ZvContour cont)
{
    if (NULL == cont)
    {
        return 0;
    }

    if (!cont->status.convexity)
    {
        std::vector < cv::Point > hull;
        convexHull(ZV_ADP_CONT(cont), hull);
        cont->featVal.convexity = zv_cont_area(cont) / contourArea(cv::Mat(hull));
        cont->status.convexity = 1;
        if (cont->featVal.convexity >= 1 || 1 - cont->featVal.convexity < ZV_EPS_AC5)
        {
            cont->featVal.isConvex = 1;
            cont->status.isConvex = 1;
        }
    }
    
    return cont->featVal.convexity;
}

double zv_cont_circularity(ZvContour contour)
{
    if (NULL == contour)
    {
        return 0;
    }

    if (!contour->status.circularity)
    {
        double r = 0;
        zv_cont_smallestCircle(contour, NULL, NULL, &r);
        contour->featVal.circularity = std::min(zv_cont_area(contour) / (r * r * PI), 1.0);
        contour->status.circularity = 1;
    }
    return contour->featVal.circularity;
}

double zv_cont_compactness(ZvContour contour)
{
    if (NULL == contour)
    {
        return 0;
    }

    if (!contour->status.compact)
    {
        double c = zv_cont_length(contour);
        contour->featVal.compact = std::max(c * c / (4 * PI * zv_cont_area(contour)), 1.0);
        contour->status.compact = 1;
    }
    return contour->featVal.compact;
}

// 外接矩形
int zv_cont_smallestRect(ZvContour cont, int *x, int *y, int *width, int *height)
{
    ZV_CHK_NULL1(cont);

    if (!cont->status.rect)
    {
        cv::Rect rect = cv::boundingRect(ZV_ADP_CONT(cont));
        cont->featVal.rectX = rect.x;
        cont->featVal.rectY = rect.y;
        cont->featVal.rectW = rect.width;
        cont->featVal.rectH = rect.height;
        cont->featVal.rectRX = rect.x + rect.width;
        cont->featVal.rectBY = rect.y + rect.height;
        cont->featVal.rectRatio = cont->featVal.rectH / cont->featVal.rectW;
        cont->status.rect = 1;
    }

    if (x) *x = cvRound(cont->featVal.rectX);
    if (y) *y = cvRound(cont->featVal.rectY);
    if (width) *width = cvRound(cont->featVal.rectW);
    if (height) *height = cvRound(cont->featVal.rectH);

    return ZV_ST_OK;
}

int zv_cont_ellipticAxis(ZvContour cont, double *major, double * minor, double *angle)
{
    ZV_CHK_NULL1(cont);
    if (!cont->status.elliAxis)
    {
        zv_cont_momentsAll(cont);
        cv::Moments &moms = cont->featVal.moment;

        double tmp = moms.mu02 - moms.mu20;
        cont->featVal.axisAngle = -0.5 * atan2(2 * moms.mu11, tmp);
        cont->featVal.axisAngle = ZV_TO_DEG(cont->featVal.axisAngle);

        tmp = std::sqrt(4 * moms.mu11 * moms.mu11 + tmp * tmp);
        cont->featVal.axisMinor = std::sqrt(8 * (moms.mu20 + moms.mu02 - tmp));
        cont->featVal.axisMajor = std::sqrt(8 * (moms.mu20 + moms.mu02 + tmp));
        cont->featVal.axisRatio = cont->featVal.axisMinor / cont->featVal.axisMajor;
        cont->status.elliAxis = 1;
    }

    if (major) *major = cont->featVal.axisMajor;
    if (minor) *minor = cont->featVal.axisMinor;
    if (angle) *angle = cont->featVal.axisAngle;
    return ZV_ST_OK;
}

// 最小包围矩形
int zv_cont_smallestRect2(ZvContour cont, double *cx, double *cy,
    double *width, double *height, double *angle)
{
    ZV_CHK_NULL1(cont);

    if (!cont->status.rect2)
    {
        cv::RotatedRect rRect = minAreaRect(ZV_ADP_CONT(cont));
        cont->featVal.rect2CX = (double)rRect.center.x;
        cont->featVal.rect2CY = (double)rRect.center.y;
        cont->featVal.rect2W = (double)rRect.size.width;
        cont->featVal.rect2H = (double)rRect.size.height;
        cont->featVal.rect2Anale = (double)rRect.angle;
        cont->featVal.rect2Ratio = cont->featVal.rect2H / cont->featVal.rect2W;
        cont->status.rect2 = 1;
    }

    if (cx) *cx = cont->featVal.rect2CX;
    if (cy) *cy = cont->featVal.rect2CY;
    if (width) *width = cont->featVal.rect2W;
    if (height) *height = cont->featVal.rect2H;
    if (angle) *angle = cont->featVal.rect2Anale;

    return ZV_ST_OK;
}

// 最小包围圆
int zv_cont_smallestCircle(ZvContour cont, double *x, double *y, double *r)
{
    ZV_CHK_NULL1(cont);

    if (!cont->status.outerCircle)
    {
        cv::Point2f center;
        float radius;
        minEnclosingCircle(ZV_ADP_CONT(cont), center, radius);
        cont->featVal.outerCX = center.x;
        cont->featVal.outerCY = center.y;
        cont->featVal.outerCR = radius;
        cont->status.outerCircle = 1;
    }

    if (x) *x = cont->featVal.outerCX;
    if (y) *y = cont->featVal.outerCY;
    if (r) *r = cont->featVal.outerCR;

    return ZV_ST_OK;
}

// 凸包 bufLen输入输出参数，输入ptIdx长度，输出ptIdx有效数据数量
int zv_cont_convexHullIdx(ZvContour cont, int *ptIdx, int *bufLen)
{
    ZV_CHK_NULL3(cont, ptIdx, bufLen);

    vector<int> hull;
    cv::convexHull(ZV_ADP_CONT(cont), hull, false, false);

    if (hull.size() > *bufLen)
    {
        return ZV_ERR_G_BUF_SMALL;
    }
    for (int i = 0; i < hull.size(); i++)
        ptIdx[i] = hull[i];
    *bufLen = (int)hull.size();

    return ZV_ST_OK;
}

// 转多边形
int zv_cont_approxPoly(ZvContour cont, ZvContour poly, double epsilon, bool isClosed)
{
    ZV_CHK_NULL2(cont, poly);
    if (!poly->createContour())
    {
        return ZV_ERR_MEM_ALLOC;
    }

    approxPolyDP(ZV_ADP_CONT(cont), ZV_ADP_CONT(poly), epsilon, isClosed);   // 用指定精度 逼近 多边形曲线, contours 是输出的

    return ZV_ST_OK;
}

double zv_cont_moments(ZvContour cont, int type, int orderX, int orderY)
{
    ZV_CHK_NULL1(cont);
    if ((uint)type > 2)
    {
        return ZV_ERR_FEAT_MOMENT_TYPE;
    }

    zv_cont_momentsAll(cont);

    if (0 == type)
    {
        if (0 == orderX && 0 == orderY)
        {
            return cont->featVal.moment.m00;
        }
        else if (1 == orderX && 0 == orderY)
        {
            return cont->featVal.moment.m10;
        }
        else if (0 == orderX && 1 == orderY)
        {
            return cont->featVal.moment.m01;
        }
    }

    if ((uint)orderX > 3 || (uint)orderY > 3) //[0 ,3]
    {
        return ZV_ERR_FEAT_MOMENT_ORDER;
    }
    int orderId = orderX + orderY - 2;
    if ((uint)orderId > 1)
    {
        return ZV_ERR_FEAT_MOMENT_ORDER;
    }

    return (&cont->featVal.moment.m20)[type * 7 + orderId * 4 + orderY];
}

int zv_cont_huMoments(ZvContour cont, double *hu)
{
    ZV_CHK_NULL1(cont);
    if (!cont->status.hu)
    {
        cont->status.hu = 1;
        zv_cont_momentsAll(cont);
        HuMoments(cont->featVal.moment, cont->featVal.hu);
    }

    if (hu)
    {
        memcpy(hu, cont->featVal.hu, sizeof(cont->featVal.hu));
    }

    return ZV_ST_OK;
}

int zv_cont_filter(ZvContList conts, int feature, double minVal, double maxVal, bool isInvert)
{
    ZV_CHK_NULL1(conts);
    if (feature > ZV_FEAT_HU6 || feature < 0
        || ZV_FEAT_MEAN == feature || ZV_FEAT_HOLE_NUMS == feature)
    {
        return ZV_ERR_FEAT_TYPE;
    }

    int size = conts->size();
    conts->_size = 0;
    int curIdx = 0;
    for (int contourIdx = 0; contourIdx < size; contourIdx++)
    {
        ZvContour cont = (*conts)[contourIdx];
        double value =  minVal + isInvert - 0.5; //默认值设置为选定范围外
        if (ZV_ST_OK == zv_cont_updateFeature(cont, feature))
        {
            value = cont->value[feature];
            if (ZV_FEAT_AREA == feature && 0 > value)
            {
                value = -value;
            }
        }

        if (curIdx != contourIdx) //如果错位则需要移动指针
        {
            conts->cptr[curIdx] = conts->cptr[contourIdx];
            conts->cptr[curIdx]->curId = curIdx;
        }

        if ((!isInvert && value >= minVal && value <= maxVal)
            || isInvert && (value < minVal || value > maxVal)) //选定项不用处理，否则curId置为-1表示没有指针指向
        {
            curIdx++;
        }
        else
        {
            conts->cptr[contourIdx]->curId = -1;
        }
    }
    conts->_size = curIdx;
    for (; curIdx < size; curIdx++)
    {
        conts->cptr[curIdx] = NULL;
    }

    return ZV_ST_OK;
}

// 轮廓的 排序
int zv_cont_sort(ZvContList contlist, int feature, bool isInc)
{
    ZV_CHK_NULL1(contlist);

    _ZvContList &contours = *contlist;
    int num = (int)contours.size();
    if (1 >= num)
    {
        return ZV_ST_OK;
    }

    vector<double> featVal(num, 0);
    for (int i = 0; i < num; i++)
    {
        if (ZV_ST_OK != zv_cont_updateFeature(contours[i], feature))
        {
            return ZV_ERR_FEAT_CALC;
        }
        featVal[i] = contours[i]->value[feature];
        if (ZV_FEAT_AREA == feature && featVal[i] < 0)
        {
            featVal[i] = -featVal[i];
        }
    }

    for (int j = 0; j < num - 1; j++)
    {
        for (int k = j + 1; k < num; k++)
        {
            if ((!isInc && featVal[j] < featVal[k])     // 从大到小的排序
                || (isInc && featVal[j] > featVal[k]))  // 从小到大的排序
            {
                // 值交换
                std::swap(featVal[j], featVal[k]);

                // 指针交换
                _ZvContour *p = contours[j];
                contlist->cptr[j] = contours[k];
                contlist->cptr[j]->curId = j;
                contlist->cptr[k] = p;
                contlist->cptr[k]->curId = k;
            }
            else break;
        }
    }

    return ZV_ST_OK;
}

// 霍夫找直线
int zv_feat_houghLine(ZvImage img, ZvMatrix l, double rho, double theta, int thresh, double minLinelen, double maxLineGap)
{
    ZV_CHK_NULL2(img, l);

    cv::Mat _img = ZV_ADP_IMG_GETM(img);
    if (CV_8UC1 != _img.type())
    {
        return ZV_ERR_I_ONLY_8UC1;
    }

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(_img, lines, rho, theta, thresh, minLinelen, maxLineGap);
    cv::Mat dst((int)lines.size(), 4, CV_64FC1);
    for (int i = 0; i < (int)lines.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            dst.at<double>(i, j) = lines[i][j];
        }
    }

    ZV_ADP_MAT_SETM(l, dst);
    return ZV_ST_OK;
}

// 霍夫找圆
int zv_feat_houghCircle(ZvImage img, ZvMatrix c, double minDist,
    double param1, double param2, double minR, double maxR)
{
    ZV_CHK_NULL2(img, c);

    cv::Mat _img = ZV_ADP_IMG_GETM(img);
    if (CV_8UC1 != _img.type())
    {
        return ZV_ERR_I_ONLY_8UC1;
    }

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(_img, circles, cv::HOUGH_GRADIENT, 1, minDist, param1, param2, (int)minR, (int)maxR);
    cv::Mat dst((int)circles.size(), 3, CV_64FC1);

    for (int i = 0; i < dst.rows; i++)
        for (int j = 0; j < dst.cols; j++)
            dst.at<double>(i, j) = circles[i][j];

    ZV_ADP_MAT_SETM(c, dst);
    return ZV_ST_OK;
}

int zv_cont_affine(ZvContour contSrc, ZvContour contDst, ZvMatrix mat)
{
    ZV_CHK_NULL3(contSrc, contDst, mat);
    int size = zv_cont_pointCount(contSrc);
    if (!contDst->createContour(size))
    {
        return ZV_ERR_MEM_ALLOC;
    }

    vector<Point2d> from(size), to(size);
    for (int i = 0; i < size; i++)
    {
        from[i].x = ZV_ADP_CONT(contSrc)[i].x;
        from[i].y = ZV_ADP_CONT(contSrc)[i].y;
    }
 
    zv_tk_affineTrans(mat, (double *)from.data(), (double *)to.data(), size);
    for (int i = 0; i < size; i++)
    {
        ZV_ADP_CONT(contDst)[i].x = cvRound(to[i].x);
        ZV_ADP_CONT(contDst)[i].y = cvRound(to[i].y);
    }

    return ZV_ST_OK;
}

int zv_cont_perspective(ZvContour contSrc, ZvContour contDst, ZvMatrix mat)
{
    ZV_CHK_NULL3(contSrc, contDst, mat);
    int size = zv_cont_pointCount(contSrc);
    if (!contDst->createContour(size))
    {
        return ZV_ERR_MEM_ALLOC;
    }

    vector<Point2d> from(size), to(size);
    for (int i = 0; i < size; i++)
    {
        from[i].x = ZV_ADP_CONT(contSrc)[i].x;
        from[i].y = ZV_ADP_CONT(contSrc)[i].y;
    }

    zv_tk_projectiveTrans2d(mat, (double *)from.data(), (double *)to.data(), size);
    for (int i = 0; i < size; i++)
    {
        ZV_ADP_CONT(contDst)[i].x = cvRound(to[i].x);
        ZV_ADP_CONT(contDst)[i].y = cvRound(to[i].y);
    }

    return ZV_ST_OK;
}
