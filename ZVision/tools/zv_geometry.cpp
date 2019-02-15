#include "zv_private.h"
#include "zv_tools.h"
#include "core/zv_core.h"


double zv_tk_distancePL(double px, double py, double lineX1, double lineY1, double lineX2, double lineY2)
{
    lineX2 -= lineX1;
    lineY2 -= lineY1;
    if (fabs(lineX2) + fabs(lineY2) < ZV_EPS_AC5)
    {
        return zv_tk_distancePP(px, py, lineX1, lineY1);
    }
    px -= lineX1;
    py -= lineY1;
    return fabs(px * lineY2 - py * lineX2) / sqrt(lineX2 * lineX2 + lineY2 * lineY2);
}

double zv_tk_distancePS(double px, double py, double lineX1, double lineY1, double lineX2, double lineY2)
{
    double dl = zv_tk_distancePL(px, py, lineX1, lineY1, lineX2, lineY2);
    double dp = zv_tk_distancePP(px, py, lineX1, lineY1);
    dl = std::min(dl, dp);
    dp = zv_tk_distancePP(px, py, lineX2, lineY2);
    return std::min(dl, dp);
}

double zv_tk_distanceContP(ZvContour cont, double px, double py)
{
    ZV_CHK_NULL1(cont);
    return cv::pointPolygonTest(ZV_ADP_CONT(cont), cv::Point2f((float)px, (float)py), true);
}

int zv_tk_rect2Vertex(double cx, double cy, double width, double height, double angle, double *pt)
{
    if (NULL == pt)
    {
        return ZV_ERR_FA_NULL_6;
    }
    cv::RotatedRect rRect(cv::Point2f((float)cx, (float)cy),
        cv::Point2f((float)width, (float)height), (float)angle);
    cv::Point2f ptsF[4] = { 0 };
    rRect.points(ptsF);
    for (int i = 0; i < 4; i++)
    {
        pt[i * 2] = ptsF[i].x;
        pt[i * 2 + 1] = ptsF[i].y;
    }

    return ZV_ST_OK;
}

int zv_tk_intersectPL(double px, double py, double x1, double y1,
    double x2, double y2, double *sectX, double *sectY)
{
    if (NULL == sectX)
    {
        return ZV_ERR_FA_NULL_7;
    }
    if (NULL == sectY)
    {
        return ZV_ERR_FA_NULL_8;
    }

    double offset = x2*y1 - x1*y2;
    x2 -= x1;
    y2 -= y1;
    double sumSqrt = x2 * x2 + y2 * y2;
    if (sumSqrt < ZV_EPS_AC5)
    {
        return ZV_ERR_TK_LINE_PT;
    }

    *sectX = ( y2*y2*px - x2*y2*py - x2*offset) / sumSqrt;
    *sectY = (-x2*y2*px + x2*x2*py - y2*offset) / sumSqrt;

    return ZV_ST_OK;
}

bool zv_tk_intersectLL(double l1x1, double l1y1, double l1x2, double l1y2,
    double l2x1, double l2y1, double l2x2, double l2y2, double *sectX, double *sectY)
{
    if (NULL == sectX || NULL == sectY)
    {
        return false;
    }

    double dX1 = l1x2 - l1x1;
    double dY1 = l1y2 - l1y1;
    double dX2 = l2x2 - l2x1;
    double dY2 = l2y2 - l2y1;

    double temp = dY1 * dX2 - dY2 * dX1;
    if (fabs(temp) <= ZV_EPS_AC5) //平行
    {
        *sectX = *sectY = 0;
        return false;
    }
    double A = dX1 * l1y1 - dY1 * l1x1;
    double B = dX2 * l2y1 - dY2 * l2x1;
    *sectX = (B*dX1 - A*dX2) / temp;
    *sectY = (B*dY1 - A*dY2) / temp;

    return true;
}

double zv_tk_angleLines(double line1X1, double line1Y1, double line1X2, double line1Y2, double line2X1, double line2Y1, double line2X2, double line2Y2)
{
    double angle = atan2(line2Y2 - line2Y1, line2X2 - line2X1);
    angle -= atan2(line1Y2 - line1Y1, line1X2 - line1X1);
    if (angle > ZV_PI)
    {
        angle -= 2 * ZV_PI;
    }
    if (angle < -ZV_PI)
    {
        angle += 2 * ZV_PI;
    }
    
    return ZV_TO_DEG(angle);
}

double zv_tk_angleLineX(double x1, double y1, double x2, double y2)
{
    double angle = atan2(y2 - y1, x2 - x1);  //(-pi, pi]
    return ZV_TO_DEG(angle);
}

int zv_tk_fitLine2D(ZvMatrix pts, double *x, double *y, double *angle, double *length)
{
    ZV_CHK_NULL5(pts, x, y, angle, length);
    cv::Vec4f line;
    cv::fitLine(ZV_ADP_MAT_GETM(pts), line, CV_DIST_L2, 0, 1.0, 0.01);
    *x = line[2];
    *y = line[3];
    *angle = ZV_TO_DEG(atan2(line[1], line[0]));
    *length = -1;
    return ZV_ST_OK;
}

int zv_tk_fitCircle(ZvMatrix pts, double *cx, double *cy, double *r)
{
    ZV_CHK_NULL4(pts, cx, cy, r);
    *cx = 0;
    *cy = 0;
    *r = 0;
    int ptNum = zv_mat_rows(pts);
    if (3 > ptNum)
    {
        return ZV_ERR_TK_FIT_PTS_NUM;
    }

    double sumx = 0.0, sumy = 0.0;
    double sumx2 = 0.0, sumy2 = 0.0;
    double sumx3 = 0.0, sumy3 = 0;
    double sumxy = 0.0, sumx1y2 = 0, sumx2y1 = 0;
    for (int i = 0; i < ptNum; i++)
    {
        double *point = ZV_ADP_MAT_MP(pts)->ptr<double>(i);
        double x2 = point[0] * point[0];
        double y2 = point[1] * point[1];
        sumx += point[0];
        sumy += point[1];
        sumx2 += x2;
        sumy2 += y2;
        sumx3 += x2 * point[0];
        sumy3 += y2 * point[1];
        sumxy += point[0] * point[1];
        sumx1y2 += point[0] * y2;
        sumx2y1 += x2 * point[1];
    }

    sumxy = ptNum * sumxy - sumx * sumy;
    sumx1y2 = ptNum * (sumx3 + sumx1y2) - (sumx2 + sumy2) * sumx;
    sumx2y1 = ptNum * (sumx2y1 + sumy3) - (sumx2 + sumy2) * sumy;
    double A = ptNum * sumy2 - sumy * sumy;
    double B = ptNum * sumx2 - sumx * sumx;
    double temp = sumxy * sumxy - A * B;

    A = (sumx1y2 * A - sumx2y1 * sumxy) / temp;
    B = (sumx2y1 * B - sumx1y2 * sumxy) / temp;

    *cx = -0.5 * A;
    *cy = -0.5 * B;
    *r = sqrt(*cx * *cx + *cy * *cy + (A * sumx + B * sumy + sumx2 + sumy2) / ptNum);
    return ZV_ST_OK;
}

int zv_tk_fitEllipse(ZvMatrix pts, double *cX, double *cY, double *xR, double *yR, double *angle)
{
    ZV_CHK_NULL6(pts, cX, cY, xR, yR, angle);
    cv::Mat mat;
    ZV_ADP_MAT_GETM(pts).convertTo(mat, CV_32F);
    cv::RotatedRect rrect = cv::fitEllipse(mat);
    *cX = rrect.center.x;
    *cY = rrect.center.y;
    *xR = rrect.size.width / 2.0;
    *yR = rrect.size.height / 2.0;
    *angle = rrect.angle;
    return ZV_ST_OK;
}

int zv_tk_intersectRect2(ZvMatrix pts, double R1X, double R1Y, double R1W, double R1H,
    double R1Angle, double R2X, double R2Y, double R2W, double R2H, double R2Angle)
{
    ZV_CHK_NULL1(pts);

    cv::RotatedRect rRect1(cv::Point2f((float)R1X, (float)R1Y),
        cv::Point2f((float)R1W, (float)R1H), (float)R1Angle);
    cv::RotatedRect rRect2(cv::Point2f((float)R2X, (float)R2Y),
        cv::Point2f((float)R2W, (float)R2H), (float)R2Angle);

    cv::Mat intersect, *_pts = ZV_ADP_MAT_MP(pts);
    cv::rotatedRectangleIntersection(rRect1, rRect2, intersect);
    intersect.convertTo(*_pts, CV_64F);
    *_pts = _pts->reshape(1);

    return ZV_ST_OK;
}

int zv_tk_lineToParam(double x1, double y1, double x2, double y2,
    double *cx, double *cy, double *angle, double *length)
{
    if (NULL == cx)
    {
        return ZV_ERR_FA_NULL_5;
    }
    if (NULL == cy)
    {
        return ZV_ERR_FA_NULL_6;
    }
    if (NULL == angle)
    {
        return ZV_ERR_FA_NULL_7;
    }
    if (NULL == length)
    {
        return ZV_ERR_FA_NULL_8;
    }

    *cx = (x1 + x2) / 2;
    *cy = (y1 + y2) / 2;
    *length = zv_tk_distancePP(x1, y1, x2, y2);
    *angle = ZV_TO_DEG(atan2(y2 - y1, x2 - x1));

    return ZV_ST_OK;
}

int zv_tk_lineFromParam(double cx, double cy, double angle, double len,
    double *x1, double *y1, double *x2, double *y2)
{
    if (NULL == x1)
    {
        return ZV_ERR_FA_NULL_5;
    }
    if (NULL == y1)
    {
        return ZV_ERR_FA_NULL_6;
    }
    if (NULL == x2)
    {
        return ZV_ERR_FA_NULL_7;
    }
    if (NULL == y2)
    {
        return ZV_ERR_FA_NULL_8;
    }

    angle = ZV_TO_RAD(angle);
    double vx = cos(angle);
    double vy = sin(angle);
    if (0 > len)
    {
        len = zv_tk_distancePP(cx, cy, 0, 0) / 2;
    }

    len /= 2.0;
    *x1 = cx - len * vx;
    *y1 = cy - len * vy;
    *x2 = cx + len * vx;
    *y2 = cy + len * vy;
    return ZV_ST_OK;
}

int zv_tk_fitLineEx(ZvMatrix pts, double *line, int method, double reps, double aeps)
{
    return ZV_ST_OK;
}

int zv_tk_fitEllipseEx(ZvMatrix pts, double *cX, double *cY, double *xR,
    double *yR, double *angle, int method)
{
    ZV_CHK_NULL6(pts, cX, cY, xR, yR, angle);

    if (0 == method)
    {
        return zv_tk_fitEllipse(pts, cX, cY, xR, yR, angle);
    }

    cv::Mat mat;
    cv::RotatedRect elli;
    ZV_ADP_MAT_GETM(pts).convertTo(mat, CV_32F);
    if (1 == method)
    {
        elli = cv::fitEllipseAMS(mat);
    }
    else if (2 == method)
    {
        elli = cv::fitEllipseDirect(mat);
    }
    else
    {
        return ZV_ERR_FA_NULL_7;
    }
    *cX = elli.center.x;
    *cY = elli.center.y;
    *xR = elli.size.width / 2.0;
    *yR = elli.size.height / 2.0;
    *angle = elli.angle;

    return ZV_ST_OK;
}

int zv_tk_fitPolyn(ZvMatrix pts, int order, double *param)
{
    ZV_CHK_NULL3(pts, g_zv_adp_notNull, param);
    if (2 != zv_mat_cols(pts))
    {
        return ZV_ERR_M_SIZE;
    }
    int ptNum = zv_mat_rows(pts);
    if (ptNum <= order)
    {
        return ZV_ERR_TK_FIT_PTS_NUM;
    }

    //构造矩阵
    order = order + 1;
    double * ptList = (double *)ZV_ADP_MAT_GETM(pts).data;
    cv::Mat matX = cv::Mat::zeros(order, order, CV_64FC1);
    cv::Mat matY = cv::Mat::zeros(order, 1, CV_64FC1);
    for (int i = 0; i < order; i++)
    {
        double * xData = (double *)(matX.data + i * matX.step);
        double * yData = (double *)(matY.data);
        for (int j = 0; j < order; j++)
        {
            if (0 == i)
            {
                for (int k = 0; k < ptNum; k++)
                {
                    double tmp = std::pow(ptList[2 * k], j);
                    xData[j] = xData[j] + tmp;
                    yData[j] = yData[j] + tmp * ptList[2 * k + 1];
                }
            }
            else
            {
                if (j == order - 1)
                {
                    for (int k = 0; k < ptNum; k++)
                    {
                        xData[j] = xData[j] + std::pow(ptList[2 * k], i + j);
                    }
                }
                else
                {
                    xData[j] = xData[j - order + 1];
                }
            }
        }
    }

    cv::Mat matA = cv::Mat(order, 1, CV_64FC1, param);
    cv::solve(matX, matY, matA, cv::DECOMP_LU); //求解矩阵A

    return ZV_ST_OK;
}

int zv_tk_subPixInterp1d(double * pts, int ptNum, double &pos, double &value)
{
    ZV_CHK_NULL1(pts);
    _ZvMatrix mat;
    zv_mat_genData(&mat, ptNum, 2, pts);
    double param[3] = { 0 };
    zv_tk_fitPolyn(&mat, 2, param);
    pos = -param[1] / (2 * param[2]);
    value = param[0] - param[1] * param[1] / (4 * param[2]);
    return ZV_ST_OK;
}

int zv_tk_subPixInterp2d(double * pts, int ptNum, double &posX, double &posY, double &value)
{
    ZV_CHK_NULL1(pts);
#define FIT_COEFF_NUM 6
    if (ptNum < FIT_COEFF_NUM)
    {
        return ZV_ERR_TK_FIT_PTS_NUM;
    }

    //构造矩阵
    double param[FIT_COEFF_NUM] = { 0 };  //低次项在前p0+y*p1+x*p2+xy*p3+yy*p4+xx*p5
    double y[FIT_COEFF_NUM] = { 0 };
    double x[FIT_COEFF_NUM][FIT_COEFF_NUM] = { 0 };
    cv::Mat matX = cv::Mat(FIT_COEFF_NUM, FIT_COEFF_NUM, CV_64FC1, x);
    cv::Mat matY = cv::Mat(FIT_COEFF_NUM, 1, CV_64FC1, y);
    cv::Mat matA = cv::Mat(FIT_COEFF_NUM, 1, CV_64FC1, param);

    double(*p3d)[3] = (double (*)[3])pts;       //x,y,z
    x[0][0] = ptNum;
    for (int i = 0; i < ptNum; i++)
    {
        double _xy = p3d[i][0] * p3d[i][1];
        x[0][1] += p3d[i][1];               //y
        x[0][2] += p3d[i][0];               //x
        x[0][3] += _xy;                     //yx
        x[0][4] += p3d[i][1] * p3d[i][1];   //y*y
        x[0][5] += p3d[i][0] * p3d[i][0];   //x*x

        x[1][1] += p3d[i][1] * p3d[i][1];
        x[1][2] += _xy;
        x[1][3] += _xy * p3d[i][1];
        x[1][4] += p3d[i][1] * p3d[i][1] * p3d[i][1];
        x[1][5] += p3d[i][0] * _xy;

        x[2][2] += p3d[i][0] * p3d[i][0];
        x[2][3] += _xy * p3d[i][0];
        x[2][4] += p3d[i][1] * _xy;
        x[2][5] += p3d[i][0] * p3d[i][0] * p3d[i][0];

        x[3][3] += _xy * _xy;
        x[3][4] += p3d[i][1] * p3d[i][1] * _xy;
        x[3][5] += p3d[i][0] * p3d[i][0] * _xy;

        x[4][4] += p3d[i][1] * p3d[i][1] * p3d[i][1] * p3d[i][1];
        x[4][5] += _xy * _xy;
        x[5][5] += p3d[i][0] * p3d[i][0] * p3d[i][0] * p3d[i][0];

        y[0] += p3d[i][2];
        y[1] += p3d[i][2] * p3d[i][1];
        y[2] += p3d[i][2] * p3d[i][0];
        y[3] += p3d[i][2] * _xy;
        y[4] += p3d[i][2] * p3d[i][1] * p3d[i][1];
        y[5] += p3d[i][2] * p3d[i][0] * p3d[i][0];
    }

    for (int i = 1; i < FIT_COEFF_NUM; i++) //下三角部分
    {
        for (int k = 0; k < i; k++)
        {
            x[i][k] = x[k][i];
        }
    }

    cv::solve(matX, matY, matA, cv::DECOMP_LU); //求解矩阵A
    double delta = param[3] * param[3] - 4 * param[4] * param[5];
    if (fabs(delta) < ZV_EPS_AC5)
    {
        return ZV_ERR_TK_INTERP2D_VAL;
    }
    posX = (2 * param[4] * param[2] - param[1] * param[3]) / delta;
    posY = (2 * param[5] * param[1] - param[2] * param[3]) / delta;
    value = (param[5]*posX + param[3]*posY + param[2]) * posX +
        (param[4]*posY + param[1]) * posY + param[0];

    return ZV_ST_OK;
}