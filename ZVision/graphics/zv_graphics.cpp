#include "zv_private.h"
#include "zv_graphics.h"
#include "system/zv_system.h"
#include "basis/zv_basis.h"
#include "measure/zv_meas.h"
#include "tools/zv_tools.h"

using namespace cv;

int g_zv_dra_colorMap[ZV_DEF_CLR_MAX] = { 0xFF0000, 0xFF00, 0xFF, 0xFFFFFF, 0x0 };

inline void zv_dra_checkParam(ZvImage img)
{
#define MAX_THICKNESS  32767/2
    if (g_zv_sysLineWidth > MAX_THICKNESS)
    {
        g_zv_sysLineWidth = MAX_THICKNESS;
    }
    if (g_zv_sysLineWidth < 1)
    {
        g_zv_sysLineWidth = 1;
    }
}

Scalar zv_dra_colorToScalar(ZvImage img, int color)
{
    Scalar scalar;
    int cn = zv_img_channels(img);

    if (3 == cn || 4 == cn)
    {
        scalar.val[2] = color & 255;
        scalar.val[1] = (color >> 8) & 255;
        scalar.val[0] = (color >> 16) & 255;
        scalar.val[3] = (color >> 24) & 255;
    }
    else
    {
        scalar.val[0] = color;
        scalar.val[1] = 0;
        scalar.val[2] = 0;
        scalar.val[3] = 0;
    }

    return scalar;
}

int zv_dra_line(ZvImage img, double x1, double y1, double x2, double y2, int color)
{
    ZV_CHK_NULL1(img);
    zv_dra_checkParam(img);
    line(ZV_ADP_IMG_GETM(img), cv::Point(cvRound(x1), cvRound(y1)), cv::Point(cvRound(x2), cvRound(y2)),
        zv_dra_colorToScalar(img, color), g_zv_sysLineWidth, g_zv_sys_lineType);
    return ZV_ST_OK;
}

int zv_dra_rect(ZvImage img, double x, double y, double w, double h, int color)
{
    ZV_CHK_NULL1(img);
    zv_dra_checkParam(img);
    rectangle(ZV_ADP_IMG_GETM(img), cv::Rect(cvRound(x), cvRound(y), cvRound(w), cvRound(h)),
        zv_dra_colorToScalar(img, color), 0 != g_zv_sysIsDrawFill ? -1 : g_zv_sysLineWidth, g_zv_sys_lineType);
    return ZV_ST_OK;
}

int zv_dra_rect2(ZvImage img, double cx, double cy, double width, double height, double angle, int color)
{
    ZV_CHK_NULL1(img);
    zv_dra_checkParam(img);

    Point2f _pts[4];
    Point pts[4], *p = pts;
    cv::RotatedRect rRect(cv::Point2f((float)cx, (float)cy), cv::Point2f((float)width, (float)height), (float)angle);
    rRect.points(_pts);
    int count = 4;
    for (int i = 0; i < count; i++)
    {
        pts[i].x = (int)_pts[i].x;
        pts[i].y = (int)_pts[i].y;
    }

    if (0 != g_zv_sysIsDrawFill)
    {
        fillPoly(ZV_ADP_IMG_GETM(img), (const Point**)&p, &count, 1, zv_dra_colorToScalar(img, color), g_zv_sys_lineType);
    }
    else
    {
        polylines(ZV_ADP_IMG_GETM(img), &p, &count, 1, true, zv_dra_colorToScalar(img, color),
            g_zv_sysLineWidth, g_zv_sys_lineType);
    }
    return ZV_ST_OK;
}

int zv_dra_circle(ZvImage img, double cx, double cy, double r, int color)
{
    ZV_CHK_NULL1(img);
    zv_dra_checkParam(img);
    circle(ZV_ADP_IMG_GETM(img), cv::Point(cvRound(cx), cvRound(cy)), cvRound(r),
        zv_dra_colorToScalar(img, color), 0 != g_zv_sysIsDrawFill ? -1 : g_zv_sysLineWidth, g_zv_sys_lineType);
    return ZV_ST_OK;
}

int zv_dra_ellipse(ZvImage img, double cx, double cy, double xR, double yR, double angle, int color)
{
    ZV_CHK_NULL1(img);
    zv_dra_checkParam(img);
    cv::RotatedRect elli(cv::Point2f((float)cx, (float)cy), cv::Point2f((float)xR*2.f, (float)yR*2.f), (float)angle);
    ellipse(ZV_ADP_IMG_GETM(img), elli, zv_dra_colorToScalar(img, color),
        0 != g_zv_sysIsDrawFill ? -1 : g_zv_sysLineWidth, g_zv_sys_lineType);
    return ZV_ST_OK;
}

int zv_dra_ellipseArc(ZvImage img, double cx, double cy, double xR, double yR, double angle, double angleStart, double angleEnd, int color)
{
    ZV_CHK_NULL1(img);
    zv_dra_checkParam(img);
    ellipse(ZV_ADP_IMG_GETM(img), Point(cvRound(cx), cvRound(cy)), Size(cvRound(xR), cvRound(yR)),
        angle, angleStart, angleEnd, zv_dra_colorToScalar(img, color),
        0 != g_zv_sysIsDrawFill ? -1 : g_zv_sysLineWidth, g_zv_sys_lineType);
    return ZV_ST_OK;
}

int zv_dra_arrow(ZvImage img, double x1, double y1, double x2, double y2, int color, int size)
{
    ZV_CHK_NULL1(img);
    zv_dra_checkParam(img);
    double tipLen = size / zv_tk_distancePP(x1, y1, x2, y2);
    arrowedLine(ZV_ADP_IMG_GETM(img), Point(cvRound(x1), cvRound(y1)), Point(cvRound(x2), cvRound(y2)),
        zv_dra_colorToScalar(img, color), g_zv_sysLineWidth, g_zv_sys_lineType, 0, tipLen);
    return ZV_ST_OK;
}

int zv_dra_polygon(ZvImage img, ZvMatrix pts, bool isClosed, int color)
{
    ZV_CHK_NULL2(img, pts);
    if (2 != zv_mat_cols(pts))
    {
        return ZV_ERR_M_SIZE;
    }
    zv_dra_checkParam(img);

    Mat ipts;
    ZV_ADP_MAT_GETM(pts).convertTo(ipts, CV_32S);
    vector<Mat> poly(1, ipts.reshape(2));
    if (0 != g_zv_sysIsDrawFill)
    {
        fillPoly(ZV_ADP_IMG_GETM(img), poly, zv_dra_colorToScalar(img, color), g_zv_sys_lineType);
    }
    else
    {
        polylines(ZV_ADP_IMG_GETM(img), poly, isClosed, zv_dra_colorToScalar(img, color),
            g_zv_sysLineWidth, g_zv_sys_lineType);
    }
    return ZV_ST_OK;
}

int zv_dra_contour(ZvImage img, ZvContour cont, int color)
{
    ZV_CHK_NULL2(img, cont);
    zv_dra_checkParam(img);
    vector<Point> & contour = ZV_ADP_CONT(cont);
    Point *p = &contour[0];
    int count = (int)contour.size();
    if (0 != g_zv_sysIsDrawFill)
    {
        fillPoly(ZV_ADP_IMG_GETM(img), (const Point**)&p, &count, 1, zv_dra_colorToScalar(img, color), g_zv_sys_lineType);
    }
    else
    {
        polylines(ZV_ADP_IMG_GETM(img), &p, &count, 1, true, zv_dra_colorToScalar(img, color),
            g_zv_sysLineWidth, g_zv_sys_lineType);
    }
    return ZV_ST_OK;
}

static int s_zv_dra_markerType[] = {
    MARKER_CROSS, MARKER_TILTED_CROSS, MARKER_STAR, MARKER_DIAMOND, MARKER_SQUARE,
    MARKER_TRIANGLE_UP, MARKER_TRIANGLE_DOWN };
int zv_dra_marker(ZvImage img, double x, double y, int type, int size, int color)
{
    ZV_CHK_NULL1(img);
    if (type >= sizeof(s_zv_dra_markerType) / sizeof(s_zv_dra_markerType[0]))
    {
        return ZV_ERR_DRA_MARKER_TYPE;
    }
    if (0 > type)
    {
        type = 1;
    }
    if (0 > size)
    {
        size = 20;
    }

    zv_dra_checkParam(img);
    drawMarker(ZV_ADP_IMG_GETM(img), Point(cvRound(x), cvRound(y)), zv_dra_colorToScalar(img, color),
        s_zv_dra_markerType[type], size, g_zv_sysLineWidth, g_zv_sys_lineType);
    return ZV_ST_OK;
}

int zv_dra_text(ZvImage img, char * text, double x, double y, double scale, int color)
{
    ZV_CHK_NULL1(img);
    zv_dra_checkParam(img);
    putText(ZV_ADP_IMG_GETM(img), String(text), Point(cvRound(x), cvRound(y)), 2, 0.5*scale,
        zv_dra_colorToScalar(img, color), g_zv_sysLineWidth, g_zv_sys_lineType);
    return ZV_ST_OK;
}

int zv_dra_mask(ZvImage img, ZvImage mask)
{
    ZV_CHK_NULL1(img);
    zv_arith_and(img, mask, img);
    return ZV_ST_OK;
}

int zv_dra_measurer(ZvImage img, void *mr, int color1, int color2)
{
    ZV_CHK_NULL2(img, mr);
    int mrType = zv_meas_mrType(mr);
    switch (mrType)
    {
    case ZV_MEAS_RECT:
    {
        ZvRectMeas *p = (ZvRectMeas*)mr;
        return zv_dra_rect(img, p->x, p->y, p->w, p->h, color1);
    }
    case ZV_MEAS_RECT2:
    {
        ZvRect2Meas * p = (ZvRect2Meas *)mr;
        return zv_dra_rect2(img, p->cx, p->cy, p->w, p->h, p->angle, color1);
    }
    case ZV_MEAS_LINE:
    {
        ZvLineMeas * p = (ZvLineMeas *)mr;
        ZV_RUN_RTN(zv_dra_rect2(img, p->rt2Mr.cx, p->rt2Mr.cy, p->rt2Mr.w, p->rt2Mr.h, p->rt2Mr.angle, color1));

        double cosA = cos(ZV_TO_RAD(p->rt2Mr.angle))*0.5;
        double sinA = sin(ZV_TO_RAD(p->rt2Mr.angle))*0.5;

        double x1 = p->rt2Mr.cx - sinA*p->rt2Mr.h - cosA*p->rt2Mr.w;
        double y1 = p->rt2Mr.cy + cosA*p->rt2Mr.h - sinA*p->rt2Mr.w;
        double x2 = p->rt2Mr.cx + sinA*p->rt2Mr.h - cosA*p->rt2Mr.w;
        double y2 = p->rt2Mr.cy - cosA*p->rt2Mr.h - sinA*p->rt2Mr.w;

        double subStep = (p->rt2Mr.w - p->subWidth) / (p->subNum - 1.0);
        cosA *= 2;
        sinA *= 2;
        for (int i = 0; i < p->subNum-1; i++)
        {
            double dtX = p->subWidth * cosA;
            double dtY = p->subWidth * sinA;
            ZV_RUN_RTN(zv_dra_line(img, x1 + dtX, y1 + dtY, x2 + dtX, y2 + dtY, color2));
            dtX = subStep * cosA;
            dtY = subStep * sinA;
            x1 += dtX;
            y1 += dtY;
            x2 += dtX;
            y2 += dtY;
            ZV_RUN_RTN(zv_dra_line(img, x1, y1, x2, y2, color2));
        }
        return ZV_ST_OK;
    }
    case ZV_MEAS_ARC:
    {
        ZvArcMeas * p = (ZvArcMeas *)mr;
        double interR = p->r - p->annR;
        double outerR = p->r + p->annR;
        double endA = p->startA + p->extA;

        double cosA = cos(ZV_TO_RAD(p->startA));
        double sinA = sin(ZV_TO_RAD(p->startA));
        ZV_RUN_RTN(zv_dra_line(img, interR*cosA + p->cx, interR*sinA + p->cy,
            outerR*cosA + p->cx, outerR*sinA + p->cy, color1));
        if (p->extA >= 360)
        {
            ZV_RUN_RTN(zv_dra_circle(img, p->cx, p->cy, interR, color1));
            ZV_RUN_RTN(zv_dra_circle(img, p->cx, p->cy, outerR, color1));
        }
        else
        {
            ZV_RUN_RTN(zv_dra_ellipseArc(img, p->cx, p->cy, interR, interR, 0, p->startA, endA, color1));
            ZV_RUN_RTN(zv_dra_ellipseArc(img, p->cx, p->cy, outerR, outerR, 0, p->startA, endA, color1));
        }

        cosA = cos(ZV_TO_RAD(endA));
        sinA = sin(ZV_TO_RAD(endA));
        ZV_RUN_RTN(zv_dra_line(img, interR*cosA + p->cx, interR*sinA + p->cy,
            outerR*cosA + p->cx, outerR*sinA + p->cy, color1));
        return ZV_ST_OK;
    }
    case ZV_MEAS_CIRCLE:
    {
        ZvCircleMeas *p = (ZvCircleMeas *)mr;
        ZV_RUN_RTN(zv_dra_measurer(img, &p->arcMr, color1, 0)); //ÍâÂÖÀª

        double aStart = ZV_TO_RAD(p->arcMr.startA);
        double aStep;
        bool isClosed = false;
        if (p->arcMr.extA + 180.0 / p->subWidth >= 360)
        {
            aStep = ZV_TO_RAD(p->arcMr.extA) / p->subNum;
            isClosed = true;
        }
        else
        {
            aStep = ZV_TO_RAD(p->arcMr.extA - 180.0 / p->subWidth) / (p->subNum - 1);
        }
        double aWidth = p->subWidth / p->arcMr.r;
        double interR = p->arcMr.r - p->arcMr.annR;
        double outerR = p->arcMr.r + p->arcMr.annR;

        for (int i = 0; i < p->subNum - 1; i++)
        {
            double cosA = cos(aStart + aWidth);
            double sinA = sin(aStart + aWidth);
            ZV_RUN_RTN(zv_dra_line(img, interR*cosA + p->arcMr.cx, interR*sinA + p->arcMr.cy,
                outerR*cosA + p->arcMr.cx, outerR*sinA + p->arcMr.cy, color2));
            aStart += aStep;
            cosA = cos(aStart);
            sinA = sin(aStart);
            ZV_RUN_RTN(zv_dra_line(img, interR*cosA + p->arcMr.cx, interR*sinA + p->arcMr.cy,
                outerR*cosA + p->arcMr.cx, outerR*sinA + p->arcMr.cy, color2));
        }

        if (isClosed)
        {
            double cosA = cos(aStart + aWidth);
            double sinA = sin(aStart + aWidth);
            ZV_RUN_RTN(zv_dra_line(img, interR*cosA + p->arcMr.cx, interR*sinA + p->arcMr.cy,
                outerR*cosA + p->arcMr.cx, outerR*sinA + p->arcMr.cy, color2));
        }
        return ZV_ST_OK;
    }
    }

    return ZV_ERR_MR_INVALID;
}
