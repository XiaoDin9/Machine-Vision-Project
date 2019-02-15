#include "zv_private.h"
#include "zv_core.h"

using namespace cv;


int zv_mat_genConst(ZvMatrix mat, int rows, int cols, double value)
{
    ZV_CHK_NULL1(mat);
    Mat _m(rows, cols, CV_64F);
    _m.setTo(value);
    ZV_ADP_MAT_SETM(mat, _m);

    return ZV_ST_OK;
}

int zv_mat_genEye(ZvMatrix mat, int size)
{
    ZV_CHK_NULL1(mat);
    Mat I = Mat::eye(size, size, CV_64F);
    ZV_ADP_MAT_SETM(mat, I);
    return ZV_ST_OK;
}

int zv_mat_genData(ZvMatrix mat, int rows, int cols, double * data)
{
    ZV_CHK_NULL4(mat, g_zv_adp_notNull, g_zv_adp_notNull, data);
    Mat m(rows, cols, CV_64F, data);
    ZV_ADP_MAT_SETM(mat, m);
    return ZV_ST_OK;
}

double zv_mat_getValue(ZvMatrix mat, int row, int col)
{
    if (NULL == mat)
    {
        return 0;
    }

    Size size = ZV_ADP_MAT_GETM(mat).size();
    if (row >= size.height || col >= size.width)
    {
        return 0;
    }
    return ZV_ADP_MAT_GETM(mat).at<double>(row, col);
}

int zv_mat_setValue(ZvMatrix mat, int row, int col, double value)
{
    ZV_CHK_NULL1(mat);

    cv::Mat * p = ZV_ADP_MAT_MP(mat);
    Size size = p->size();
    if (row >= size.height)
    {
        return ZV_ERR_FA_RANGE_2;
    }
    if (col >= size.width)
    {
        return ZV_ERR_FA_RANGE_3;
    }

    ((double*)(p->data + p->step.p[0] * row))[col] = value;
    return ZV_ST_OK;
}

int zv_mat_getRow(ZvMatrix src, int id, double * buf, int bufLen)
{
    ZV_CHK_NULL3(src, g_zv_adp_notNull, buf);

    Mat mat = ZV_ADP_MAT_GETM(src);
    if (mat.cols > bufLen)
    {
        return ZV_ERR_G_BUF_SMALL;
    }

    double * data = mat.ptr<double>(id, 0);
    memcpy(buf, data, sizeof(double) * mat.cols);

    return ZV_ST_OK;
}

int zv_mat_setRow(ZvMatrix src, int id, double * buf)
{
    ZV_CHK_NULL3(src, g_zv_adp_notNull, buf);

    Mat mat = ZV_ADP_MAT_GETM(src);
    Mat r(1, mat.cols, CV_64F, buf);
    r.copyTo(mat.row(id));
    return ZV_ST_OK;
}

int zv_mat_getCol(ZvMatrix src, int id, double * buf, int bufLen)
{
    ZV_CHK_NULL3(src, g_zv_adp_notNull, buf);

    Mat mat = ZV_ADP_MAT_GETM(src);
    if (mat.rows > bufLen)
    {
        return ZV_ERR_G_BUF_SMALL;
    }
    Mat c(mat.rows, 1, CV_64F, buf);
    mat.col(id).copyTo(c);
    return ZV_ST_OK;
}

int zv_mat_setCol(ZvMatrix mat, int col, double * data)
{
    ZV_CHK_NULL3(mat, g_zv_adp_notNull, data);

    Mat _mat = ZV_ADP_MAT_GETM(mat);

    Mat c(_mat.rows, 1, CV_64F, data);
    c.copyTo(_mat.col(col));
    return ZV_ST_OK;
}

int zv_mat_getData(ZvMatrix mat, double *data, int bufLen)
{
    ZV_CHK_NULL2(mat, data);

    Mat _mat = ZV_ADP_MAT_GETM(mat);
    Mat tmp(_mat.size(), _mat.type(), data);
    if ((int)tmp.total() > bufLen)
    {
        return ZV_ERR_G_BUF_SMALL;
    }

    _mat.copyTo(tmp);

    return ZV_ST_OK;
}

int zv_mat_setData(ZvMatrix mat, double *data)
{
    ZV_CHK_NULL2(mat, data);
    Mat _mat = ZV_ADP_MAT_GETM(mat);
    if (0 == _mat.size().area())
    {
        return ZV_ERR_M_SIZE_INVALID;
    }

    Mat tmp(_mat.size(), _mat.type(), data);
    tmp.copyTo(_mat);
    return ZV_ST_OK;
}

// 从原图（矩阵） 中得到一个子区域
int zv_mat_getSub(ZvMatrix src, ZvMatrix dst, int x, int y, int width, int height)
{
    ZV_CHK_NULL2(src, dst);
    Mat m = ZV_ADP_MAT_GETM(src);   //m = *src, 而：Mat *src;
    Mat sub = m(Rect(x, y, width, height));
    ZV_ADP_MAT_SETM(dst, sub);    //*dst = sub;, 而: Mat *dst;
    return ZV_ST_OK;
}

int zv_mat_setSub(ZvMatrix mat, ZvMatrix sub, int x, int y)
{
    ZV_CHK_NULL2(mat, sub);
    Mat m = ZV_ADP_MAT_GETM(mat);
    Mat _sub = ZV_ADP_MAT_GETM(sub);
    m(Rect(x, y, _sub.cols, _sub.rows)) = _sub;
    return ZV_ST_OK;
}

int zv_mat_copy(ZvMatrix src, ZvMatrix dst)
{
    ZV_CHK_NULL2(src, dst);
    ZV_ADP_MAT_SETM(dst, ZV_ADP_MAT_GETM(src).clone());
    return ZV_ST_OK;
}