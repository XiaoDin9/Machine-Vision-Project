#include "zv_private.h"
#include "zv_tools.h"


using namespace cv;
// 图像绕着 某一点(x,y)的旋转angle 的角度，同时缩放scale 的规模大小
int zv_tk_getSimilarityParam(ZvMatrix mat, double x, double y, double angle, double scale)
{
    ZV_CHK_NULL1(mat);

    Mat m = getRotationMatrix2D(Point2f((float)x, (float)y), angle, scale);
    ZV_ADP_MAT_SETM(mat, m);

    return ZV_ST_OK;
}

int zv_tk_getRigid(ZvMatrix mat, double *srcPos, double *dstPos)
{
    ZV_CHK_NULL3(mat, srcPos, dstPos);
    double angle1 = atan2(srcPos[3] - srcPos[1], srcPos[2] - srcPos[0]);
    double angle2 = atan2(dstPos[3] - dstPos[1], dstPos[2] - dstPos[0]);

    return zv_tk_getRigidVector(mat, srcPos[0], srcPos[1], ZV_TO_DEG(angle1), dstPos[0], dstPos[1], ZV_TO_DEG(angle2));
}

int zv_tk_getRigidVector(ZvMatrix mat, double x1, double y1, double angle1, double x2, double y2, double angle2)
{
    ZV_CHK_NULL1(mat);
    cv::Mat m = cv::getRotationMatrix2D(cv::Point2f ((float)x1, (float)y1), (angle2 - angle1), 1);
    double* p = m.ptr<double>();
    p[2] += x2 - x1;
    p[5] += y2 - y1;
    ZV_ADP_MAT_SETM(mat, m);
    return ZV_ST_OK;
}

int zv_tk_getSimilarity(ZvMatrix mat, double *from, double *to)
{
    ZV_CHK_NULL3(mat, from, to);
    double angle1 = atan2(from[3] - from[1], from[2] - from[0]);
    double angle2 = atan2(to[3] - to[1], to[2] - to[0]);
    double scale = zv_tk_distancePP(to[0], to[1], to[2], to[3])
        / zv_tk_distancePP(from[0], from[1], from[2], from[3]);

    cv::Mat m = cv::getRotationMatrix2D(cv::Point2f((float)from[0], (float)from[1]), (angle2 - angle1), scale);
    double* p = m.ptr<double>();
    p[2] += to[0] - from[0];
    p[5] += to[1] - from[1];
    ZV_ADP_MAT_SETM(mat, m);
    return ZV_ST_OK;
}

// 得到 仿射变换后的矩阵值, 变换前的三点 -> 变换后的三点
int zv_tk_getAffine(ZvMatrix mat, double *from, double *to)
{
    ZV_CHK_NULL3(mat, from, to);

    // 图像的仿射变换
    cv::Point2f srcTri[3];
    cv::Point2f dstTri[3];

    int k = 0;
    for (int i = 0; i < 6; i += 2)
    {
        srcTri[k] = cv::Point2f((float)from[i], (float)from[i + 1]);
        dstTri[k++] = cv::Point2f((float)to[i], (float)to[i + 1]);
    }

    /// 求得仿射变换
    cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
    if (warp_mat.empty())
    {
        return ZV_ERR_TK_TRANS_MAT;
    }
    ZV_ADP_MAT_SETM(mat, warp_mat);
    return ZV_ST_OK;
}

int zv_tk_estimateSimilarity(ZvMatrix srcPos, ZvMatrix dstPos, ZvMatrix mat,
    double thresh, double confidence, bool *isInliers)
{
    ZV_CHK_NULL3(srcPos, dstPos, mat);
    if (2 != zv_mat_cols(srcPos))
    {
        return ZV_ERR_M_SIZE_INVALID;
    }
    if (zv_mat_rows(srcPos) != zv_mat_rows(dstPos) || zv_mat_cols(srcPos) != zv_mat_cols(dstPos))
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    confidence = confidence > 100 ? 100 : confidence < 0 ? 0 : confidence;
    confidence = confidence / 200 + 0.5;

    OutputArray inliers = NULL != isInliers ? Mat(zv_mat_rows(srcPos), 1, CV_8U, isInliers) : noArray();
    Mat rst = estimateAffinePartial2D(ZV_ADP_MAT_GETM(srcPos), ZV_ADP_MAT_GETM(dstPos),
        inliers, cv::RANSAC, thresh, 2000, confidence);
    if (rst.empty())
    {
        return ZV_ERR_TK_TRANS_MAT;
    }

    ZV_ADP_MAT_SETM(mat, rst);
    return ZV_ST_OK;
}

int zv_tk_estimateAffine(ZvMatrix srcPos, ZvMatrix dstPos, ZvMatrix mat,
    double thresh, double confidence, bool * isInliers)
{
    ZV_CHK_NULL3(srcPos, dstPos, mat);
    if (2 != zv_mat_cols(srcPos))
    {
        return ZV_ERR_M_SIZE_INVALID;
    }
    if (zv_mat_rows(srcPos) != zv_mat_rows(dstPos) || zv_mat_cols(srcPos) != zv_mat_cols(dstPos))
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    confidence = confidence > 100 ? 100 : confidence < 0 ? 0 : confidence;
    confidence = confidence / 200 + 0.5;

    OutputArray inliers = NULL != isInliers ? Mat(zv_mat_rows(srcPos), 1, CV_8U, isInliers) : noArray();
    Mat rst = estimateAffine2D(ZV_ADP_MAT_GETM(srcPos), ZV_ADP_MAT_GETM(dstPos),
        inliers, cv::RANSAC, thresh, 2000, confidence);
    if (rst.empty())
    {
        return ZV_ERR_TK_TRANS_MAT;
    }
    ZV_ADP_MAT_SETM(mat, rst);
    return ZV_ST_OK;
}

// 仿射变换
int zv_tk_affineTrans(ZvMatrix mat, double *srcPt, double *dstPt, int ptNum)
{
    ZV_CHK_NULL3(mat, srcPt, dstPt);
    if (2 != zv_mat_rows(mat) || 3 != zv_mat_cols(mat))
    {
        return ZV_ERR_M_SIZE_INVALID;
    }

    cv::Mat src(ptNum, 1, CV_64FC2, srcPt);
    cv::Mat dst(ptNum, 1, CV_64FC2, dstPt);
    transform(src, dst, ZV_ADP_MAT_GETM(mat));
    return ZV_ST_OK;
}

int zv_tk_getProjective(ZvMatrix mat, double *from, double *to)
{
    ZV_CHK_NULL3(mat, from, to);

    cv::Point2f srcTri[4];
    cv::Point2f dstTri[4];

    int k = 0;
    for (int i = 0; i < 8; i += 2)
    {
        srcTri[k] = cv::Point2f((float)from[i], (float)from[i + 1]);
        dstTri[k++] = cv::Point2f((float)to[i], (float)to[i + 1]);
    }

    cv::Mat warp_mat = cv::getPerspectiveTransform(srcTri, dstTri);
    ZV_ADP_MAT_SETM(mat, warp_mat);
    return ZV_ST_OK;
}

int zv_tk_projectiveTrans2d(ZvMatrix mat, double *from, double *to, int num)
{
    ZV_CHK_NULL3(mat, from, to);
    if (3 != zv_mat_rows(mat) || 3 != zv_mat_cols(mat))
    {
        return ZV_ERR_M_SIZE_INVALID;
    }

    cv::Mat src(num, 1, CV_64FC2, from);
    cv::Mat dst(num, 1, CV_64FC2, to);
    perspectiveTransform(src, dst, ZV_ADP_MAT_GETM(mat));
    return ZV_ST_OK;
}

int zv_tk_projectiveTrans3d(ZvMatrix mat, double *from, double *to, int num)
{
    ZV_CHK_NULL3(mat, from, to);
    if (4 != zv_mat_rows(mat) || 4 != zv_mat_cols(mat))
    {
        return ZV_ERR_M_SIZE_INVALID;
    }

    cv::Mat src(num, 1, CV_64FC3, from);
    cv::Mat dst(num, 1, CV_64FC3, to);
    perspectiveTransform(src, dst, ZV_ADP_MAT_GETM(mat));
    return ZV_ST_OK;
}
