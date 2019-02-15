#include "zv_private.h"
#include "zv_basis.h"


using namespace cv;

//对每个像素的绝对值
//500W图片耗时120ms；使用cv::absdiff(*_src, 0, *_dst)耗时760ms
int zv_arith_abs(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL2(src, dst);

    Mat *_src = ZV_ADP_OBJ_MP(src);
    if (CV_8U == _src->depth() || CV_16U == _src->depth())
    {
        _src->copyTo(*ZV_ADP_OBJ_MP(dst));
        return ZV_ST_OK;
    }

    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), _src->type());   
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    if (2 == g_zv_sys_optLevel) //性能测试
    {
        *_dst = cv::abs(*_src);
        return ZV_ST_OK;
    }

    int length = (int)_src->total() * _src->channels();
    switch (_src->depth())
    {
    case CV_32S:
    {
        int *srcData = _src->ptr<int>();
        int *dstData = _dst->ptr<int>();
        for (int i = 0; i < length; i++)
        {
            dstData[i] = abs(srcData[i]);
        }
        break;
    }
    case CV_64F:
    {
        double *srcData = _src->ptr<double>();
        double *dstData = _dst->ptr<double>();
        for (int i = 0; i < length; i++)
        {
            dstData[i] = abs(srcData[i]);
        }
        break;
    }
    default:
        return ZV_ERR_I_DEPTH;
    }

    return ZV_ST_OK;
}

// 绝对差值
int zv_arith_absDiff(ZvObject _src1, ZvObject _src2, ZvObject _dst, double mult)
{
    ZV_CHK_NULL3(_src1, _src2, _dst);

    //判断矩阵的大小、类型是否相同
    Mat *src1 = ZV_ADP_OBJ_MP(_src1);
    Mat *src2 = ZV_ADP_OBJ_MP(_src2);
    if (src1->size() != src2->size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    if (src1->type() != src2->type())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
    if (src1->channels() != src2->channels())
    {
        return ZV_ERR_I_CN_UNMATCH;
    }

    Mat * dst = ZV_ADP_OBJ_MP(_dst);
    dst->create(src1->size(), src1->type());

    cv::absdiff(*src1, *src2, *dst);
    if (fabs(mult - 1.0) > DBL_EPSILON)
    {
        *dst = *dst * mult;
    }

    return ZV_ST_OK;
}

// 矩阵的加法运算 
int zv_arith_add(ZvObject _src1, ZvObject _src2, ZvObject _dst, double mult, double add)
{
    ZV_CHK_NULL3(_src1, _src2, _dst);

    //判断矩阵的大小、类型是否相同
    Mat *src1 = ZV_ADP_OBJ_MP(_src1);
    Mat *src2 = ZV_ADP_OBJ_MP(_src2);
    Mat *dst = ZV_ADP_OBJ_MP(_dst);

    if (src1->size() != src2->size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    if (src1->type() != src2->type())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
    if (src1->channels() != src2->channels())
    {
        return ZV_ERR_I_CN_UNMATCH;
    }

    *dst = (*src1 + *src2) * mult + add;

    return ZV_ST_OK;
}

// 加权和
int zv_arith_addWeighted(ZvObject _src1, ZvObject _src2, ZvObject _dst, double scale1, double scale2, double added)
{
    ZV_CHK_NULL3(_src1, _src2, _dst);

    Mat *src1 = ZV_ADP_OBJ_MP(_src1);
    Mat *src2 = ZV_ADP_OBJ_MP(_src2);

    if (src1->size() != src2->size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    if (src1->type() != src2->type())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
       
    if (src1->channels() != src2->channels())
    {
        return ZV_ERR_I_CN_UNMATCH;
    }
    cv::addWeighted(*src1, scale1, *src2, scale2, added, ZV_ADP_IMG_GETM(_dst));
    return ZV_ST_OK;
}

// 矩阵的减法运算
int zv_arith_sub(ZvObject _src1, ZvObject _src2, ZvObject _dst, double mult, double add)
{
    ZV_CHK_NULL3(_src1, _src2, _dst);

    Mat *src1 = ZV_ADP_OBJ_MP(_src1);
    Mat *src2 = ZV_ADP_OBJ_MP(_src2);

    if (src1->size() != src2->size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    if (src1->type() != src2->type())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
    if (src1->channels() != src2->channels())
    {
        return ZV_ERR_I_CN_UNMATCH;
    }

    *ZV_ADP_OBJ_MP(_dst) = (*src1 - *src2) * mult + add;

    return ZV_ST_OK;
}

// 矩阵的乘法运算
int zv_arith_mul(ZvObject _src1, ZvObject _src2, ZvObject _dst, double mult, double add)
{
    ZV_CHK_NULL3(_src1, _src2, _dst);

    Mat *src1 = ZV_ADP_OBJ_MP(_src1);
    Mat *src2 = ZV_ADP_OBJ_MP(_src2);

    if (src1->size() != src2->size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    if (src1->type() != src2->type())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
    if (src1->channels() != src2->channels())
    {
        return ZV_ERR_I_CN_UNMATCH;
    }

    if (0 == g_zv_sys_optLevel)
    {
        *ZV_ADP_OBJ_MP(_dst) = (*src1).mul(*src2, mult) + add;
    }
    else
    {
        cv::multiply(*src1, *src2, ZV_ADP_IMG_GETM(_dst), mult);
    }

    return ZV_ST_OK;
}

// 矩阵的除法运算
int zv_arith_div(ZvObject _src1, ZvObject _src2, ZvObject _dst, double scale, double add)
{
    ZV_CHK_NULL3(_src1, _src2, _dst);

    Mat *src1 = ZV_ADP_OBJ_MP(_src1);
    Mat *src2 = ZV_ADP_OBJ_MP(_src2);

    if (src1->size() != src2->size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    if (src1->type() != src2->type())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
    if (src1->channels() != src2->channels())
    {
        return ZV_ERR_I_CN_UNMATCH;
    }

    Mat *dst = ZV_ADP_OBJ_MP(_dst);
    dst->create(src1->size(), src1->type());
    if (!src1->isContinuous() || !src2->isContinuous()  || !dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    if (0 == g_zv_sys_optLevel)
    {
        *dst = *src1 / *src2 * scale + add;
    }
    else
    {
        double * dstData = dst->ptr<double>();
        double * src1Data = src1->ptr<double>();
        double * src2Data = src2->ptr<double>();
        int length = (int)src1->total() * src1->channels();
        for (int i = 0; i < length; i++)
        {
            dstData[i] = src1Data[i] / src2Data[i] * scale + add;
        }
    }

    return ZV_ST_OK;
}

// 实现：mult *[src] + add， 对应的元素值依次进行；
int zv_arith_scale(ZvObject _src, ZvObject _dst, double mult, double add)
{
    ZV_CHK_NULL2(_src, _dst);

    Mat *pSrc = ZV_ADP_OBJ_MP(_src);
    if (0 == g_zv_sys_optLevel)
    {
        *ZV_ADP_OBJ_MP(_dst) = *pSrc * mult + add;
    }
    else
    {
        cv::addWeighted(*pSrc, mult, noArray(), 0, add, ZV_ADP_IMG_GETM(_dst));
    }

    return ZV_ST_OK;
}

// 对矩阵 求sin（）函数
int zv_arith_sin(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL2(src, dst);

    Mat * _src = ZV_ADP_OBJ_MP(src);
    if (CV_64F != _src->depth())
    {
        return ZV_ERR_I_DEPTH;
    }

    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), _src->type());
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    double * dstData = _dst->ptr<double>();
    double * srcData = _src->ptr<double>();
    int length = (int)_src->total() * _src->channels();
    for (int i = 0; i < length; i++)
    {
        dstData[i] = sin(srcData[i]);
    }

    return ZV_ST_OK;
}

int zv_arith_cos(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL2(src, dst);

    Mat * _src = ZV_ADP_OBJ_MP(src);
    if (CV_64F != _src->depth())
    {
        return ZV_ERR_I_DEPTH;
    }

    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), _src->type());
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    double * dstData = _dst->ptr<double>();
    double * srcData = _src->ptr<double>();
    int length = (int)_src->total() * _src->channels();
    for (int i = 0; i < length; i++)
    {
        dstData[i] = cos(srcData[i]);
    }

    return ZV_ST_OK;
}

int zv_arith_tan(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL2(src, dst);

    Mat * _src = ZV_ADP_OBJ_MP(src);
    if (CV_64F != _src->depth())
    {
        return ZV_ERR_I_DEPTH;
    }

    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), _src->type());
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    double * dstData = _dst->ptr<double>();
    double * srcData = _src->ptr<double>();
    int length = (int)_src->total() * _src->channels();
    for (int i = 0; i < length; i++)
    {
        dstData[i] = tan(srcData[i]);
    }

    return ZV_ST_OK;
}

int zv_arith_asin(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL2(src, dst);

    Mat * _src = ZV_ADP_OBJ_MP(src);
    if (CV_64F != _src->depth())
    {
        return ZV_ERR_I_DEPTH;
    }

    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), _src->type());
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    double * dstData = _dst->ptr<double>();
    double * srcData = _src->ptr<double>();
    int length = (int)_src->total() * _src->channels();
    for (int i = 0; i < length; i++)
    {
        dstData[i] = srcData[i] > 1 ? 0 : (srcData[i] < -1 ? 0 : asin(srcData[i]));
    }

    return ZV_ST_OK;
}

int zv_arith_acos(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL2(src, dst);

    Mat * _src = ZV_ADP_OBJ_MP(src);
    if (CV_64F != _src->depth())
    {
        return ZV_ERR_I_DEPTH;
    }

    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), _src->type());

    if (3 == g_zv_sys_optLevel) //迭代方式
    {
        int cn = _src->channels();
        *_src = _src->reshape(1);
        *_dst = _dst->reshape(1);

        MatIterator_<double> dstit = _dst->begin<double>();
        MatIterator_<double> srcit = _src->begin<double>(), srcEnd = _src->end<double>();
        while (srcit != srcEnd)
        {
            *dstit = *srcit > 1 ? 0 : (*srcit < -1 ? 0 : acos(*srcit));
            srcit++;
            dstit++;
        }
        *_dst = _dst->reshape(cn);
        return ZV_ST_OK;
    }

    if (4 == g_zv_sys_optLevel)
    {
        if (1 != _src->channels())
        {
            return ZV_ERR_I_ONLY_CN1;
        }

        for (int i = 0; i < _src->rows; i++)
        {
            for (int j = 0; j < _src->cols; j++)
            {
                double val = _src->at<double>(i, j);
                _dst->at<double>(i, j) = val > 1 ? 0 : (val < -1 ? 0 : acos(val));
            }
        }
        return ZV_ST_OK;
    }

    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    double * dstData = _dst->ptr<double>();
    double * srcData = _src->ptr<double>();
    int length = (int)_src->total() * _src->channels();
    for (int i = 0; i < length; i++)
    {
        dstData[i] = srcData[i] > 1 ? 0 : (srcData[i] < -1 ? 0 : acos(srcData[i]));
    }

    return ZV_ST_OK;
}

int zv_arith_atan(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL2(src, dst);

    Mat * _src = ZV_ADP_OBJ_MP(src);
    if (CV_64F != _src->depth())
    {
        return ZV_ERR_I_DEPTH;
    }

    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), _src->type());
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    double * srcData = _src->ptr<double>();
    double * dstData = _dst->ptr<double>();
    int length = (int)_src->total() * _src->channels();
    for (int i = 0; i < length; i++)
    {
        dstData[i] = atan(srcData[i]);
    }

    return ZV_ST_OK;
}

template<typename A>
inline void zv_arith_atan2Impl(A* src1, A* src2, double* dst, int size)
{
    for (int i = 0; i < size; i++)
    {
        dst[i] = (double)atan2(src1[i], src2[i]);
    }
}

int zv_arith_atan2(ZvObject y, ZvObject x, ZvObject dst)
{
    ZV_CHK_NULL3(y, x, dst);

    Mat * py = ZV_ADP_OBJ_MP(y);
    Mat * px = ZV_ADP_OBJ_MP(x);
    if (py->size() != px->size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    if (py->type() != px->type())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
    if (py->channels() != px->channels())
    {
        return ZV_ERR_I_CN_UNMATCH;
    }

    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(py->size(), CV_MAKE_TYPE(CV_64F, py->channels()));

    if (!py->isContinuous() || !px->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    double *dstData = _dst->ptr<double>();
    int length = (int)py->total() * py->channels();


    switch (py->depth())
    {
    case CV_8U:
        zv_arith_atan2Impl<uchar>(py->ptr<uchar>(), px->ptr<uchar>(), dstData, length);
        break;
    case CV_16U:
        zv_arith_atan2Impl<ushort>(py->ptr<ushort>(), px->ptr<ushort>(), dstData, length);
        break;
    case CV_32S:
    {
        if (0 == g_zv_sys_optLevel)
        {
            zv_arith_atan2Impl<int>(py->ptr<int>(), px->ptr<int>(), dstData, length);
        }
        else
        {
            int *yData = py->ptr<int>();
            int *xData = px->ptr<int>();
            for (int i = 0; i < length; i++)
            {
                dstData[i] = atan2(yData[i], xData[i]);
            }
        }
        break;
    }
    case CV_64F:
    {
        zv_arith_atan2Impl<double>(py->ptr<double>(), px->ptr<double>(), dstData, length);
        break;
    }
    default:
        return ZV_ERR_I_DEPTH;
    }

    return ZV_ST_OK;
}

template<typename A>
inline void zv_arith_expImpl(A* src, double* dst, int baseType, int size)
{
    switch (baseType)
    {
    case 0:
        for (int i = 0; i < size; i++)
        {
            dst[i] = exp(src[i]);
        }
        break;
    case 1:
        for (int i = 0; i < size; i++)
        {
            dst[i] = exp2(src[i]);
        }
        break;
    case 2:
        for (int i = 0; i < size; i++)
        {
            dst[i] = pow(10, src[i]);
        }
        break;
    default:
        break;
    }
}

int zv_arith_exp(ZvObject src, ZvObject dst, int baseType)
{
    ZV_CHK_NULL2(src, dst);
    if (0 > baseType || 2 < baseType)
    {
        return ZV_ERR_FA_RANGE_2;
    }

    Mat * _src = ZV_ADP_OBJ_MP(src);
    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), CV_MAKE_TYPE(CV_64F, _src->channels()));
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    int length = (int)_src->total() * _src->channels();
    switch (_src->depth())
    {
    case CV_8U:
        zv_arith_expImpl<uchar>(_src->ptr<uchar>(), _dst->ptr<double>(), baseType, length);
        break;
    case CV_16U:
        zv_arith_expImpl<ushort>(_src->ptr<ushort>(), _dst->ptr<double>(), baseType, length);
        break;
    case CV_32S:
        zv_arith_expImpl<int>(_src->ptr<int>(), _dst->ptr<double>(), baseType, length);
        break;
    case CV_64F:
        zv_arith_expImpl<double>(_src->ptr<double>(), _dst->ptr<double>(), baseType, length);
        break;
    default:
        return ZV_ERR_I_DEPTH;
    }

    return ZV_ST_OK;
}

template<typename A>
inline void zv_arith_logImpl(A* src, double* dst, int baseType, int size)
{
    switch (baseType)
    {
    case 0:
        for (int i = 0; i < size; i++)
        {
            dst[i] = src[i] > 0 ? log(src[i]) : 0;
        }
        break;
    case 1:
        for (int i = 0; i < size; i++)
        {
            dst[i] = src[i] > 0 ? log2(src[i]) : 0;
        }
        break;
    case 2:
        for (int i = 0; i < size; i++)
        {
            dst[i] = src[i] > 0 ? log10(src[i]) : 0;
        }
        break;
    default:
        break;
    }
}

int zv_arith_log(ZvObject src, ZvObject dst, int baseType)
{
    ZV_CHK_NULL2(src, dst);
    if (0 > baseType || 2 < baseType)
    {
        return ZV_ERR_FA_RANGE_2;
    }

    Mat * _src = ZV_ADP_OBJ_MP(src);
    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), CV_MAKE_TYPE(CV_64F, _src->channels()));
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    int length = (int)_src->total() * _src->channels();
    switch (_src->depth())
    {
    case CV_8U:
        zv_arith_logImpl<uchar>(_src->ptr<uchar>(), _dst->ptr<double>(), baseType, length);
        break;
    case CV_16U:
        zv_arith_logImpl<ushort>(_src->ptr<ushort>(), _dst->ptr<double>(), baseType, length);
        break;
    case CV_32S:
        zv_arith_logImpl<int>(_src->ptr<int>(), _dst->ptr<double>(), baseType, length);
        break;
    case CV_64F:
        zv_arith_logImpl<double>(_src->ptr<double>(), _dst->ptr<double>(), baseType, length);
        break;
    default:
        return ZV_ERR_I_DEPTH;
    }

    return ZV_ST_OK;
}

template<typename A>
inline void zv_arith_powImpl(A* src, double* dst, double exponent, int size)
{
    for (int i = 0; i < size; i++)
    {
        dst[i] = pow(src[i], exponent);
    }
}

int zv_arith_pow(ZvObject src, ZvObject dst, double exponent)
{
    ZV_CHK_NULL2(src, dst);

    Mat * _src = ZV_ADP_OBJ_MP(src);
    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), CV_MAKE_TYPE(CV_64F, _src->channels()));
    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    if (0 != g_zv_sys_optLevel)
    {
        cv::pow(*_src, exponent, *_dst);
        return ZV_ST_OK;
    }

    int length = (int)_src->total() * _src->channels();
    switch (_src->depth())
    {
    case CV_8U:
        zv_arith_powImpl<uchar>(_src->ptr<uchar>(), _dst->ptr<double>(), exponent, length);
        break;
    case CV_16U:
        zv_arith_powImpl<ushort>(_src->ptr<ushort>(), _dst->ptr<double>(), exponent, length);
        break;
    case CV_32S:
        zv_arith_powImpl<int>(_src->ptr<int>(), _dst->ptr<double>(), exponent, length);
        break;
    case CV_64F:
        zv_arith_powImpl<double>(_src->ptr<double>(), _dst->ptr<double>(), exponent, length);
        break;
    default:
        return ZV_ERR_I_DEPTH;
    }

    return ZV_ST_OK;
}

template<typename A>
inline void zv_arith_sqrtImpl(A* src, A* dst, int size)
{
    for (int i = 0; i < size; i++)
    {
        dst[i] = src[i] > 0 ? (A)sqrt(src[i]) : (A)0;
    }
}

int zv_arith_sqrt(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL2(src, dst);

    Mat * _src = ZV_ADP_OBJ_MP(src);
    Mat * _dst = ZV_ADP_OBJ_MP(dst);
    _dst->create(_src->size(), _src->type());

    if (!_src->isContinuous() || !_dst->isContinuous())
    {
        return ZV_ERR_M_DATA_FORMAT;
    }

    int length = (int)_src->total() * _src->channels();
    switch (_src->depth())
    {
    case CV_8U:
        zv_arith_sqrtImpl<uchar>(_src->ptr<uchar>(), _dst->ptr<uchar>(), length);
        break;
    case CV_16U:
        zv_arith_sqrtImpl<ushort>(_src->ptr<ushort>(), _dst->ptr<ushort>(), length);
        break;
    case CV_32S:
        zv_arith_sqrtImpl<int>(_src->ptr<int>(), _dst->ptr<int>(), length);
        break;
    case CV_64F:
        zv_arith_sqrtImpl<double>(_src->ptr<double>(), _dst->ptr<double>(), length);
        break;
    default:
        return ZV_ERR_I_DEPTH;
    }

    return ZV_ST_OK;
}

/* 矩阵的比较函数
说明：cmpop 的取值为： CMP_EQ \ GT \ GE \ LT （小于）\ LE （小于等于）\ NE (不等于）
*/
int zv_arith_compare(ZvObject _src1, ZvObject _src2, ZvImage dst, int op)
{
    ZV_CHK_NULL3(_src1, _src2, dst);
    if (cv::CMP_NE < op)
    {
        return ZV_ERR_FA_RANGE_4;
    }

    Mat *src1 = ZV_ADP_OBJ_MP(_src1);
    Mat *src2 = ZV_ADP_OBJ_MP(_src2);
    if (0 == src1->size().area())
    {
        return ZV_ERR_M_SIZE_INVALID;
    }
    if (src1->size() != src2->size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
    if (src1->depth() != src2->depth())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
    if (src1->channels() != src2->channels())
    {
        return ZV_ERR_I_CN_UNMATCH;
    }

    cv::compare(*src1, *src2, ZV_ADP_IMG_GETM(dst), op);
    return ZV_ST_OK;
}

int zv_arith_max(ZvObject src1, ZvObject src2, ZvObject dst)
{
    ZV_CHK_NULL3(src1, src2, dst);
    cv::max(*ZV_ADP_OBJ_MP(src1), *ZV_ADP_OBJ_MP(src2), *ZV_ADP_OBJ_MP(dst));
    return ZV_ST_OK;
}

int zv_arith_min(ZvObject src1, ZvObject src2, ZvObject dst)
{
    ZV_CHK_NULL3(src1, src2, dst);
    cv::min(*ZV_ADP_OBJ_MP(src1), *ZV_ADP_OBJ_MP(src2), *ZV_ADP_OBJ_MP(dst));
    return ZV_ST_OK;
}

int zv_arith_maxS(ZvObject src1, ZvObject dst, double *scalar)
{
    ZV_CHK_NULL3(src1, dst, scalar);
    cv::Scalar scal(scalar[0], scalar[1], scalar[2], scalar[3]);
    cv::max(*ZV_ADP_OBJ_MP(src1), scal, *ZV_ADP_OBJ_MP(dst));
    return ZV_ST_OK;
}

int zv_arith_minS(ZvObject src1, ZvObject dst, double *scalar)
{
    ZV_CHK_NULL3(src1, dst, scalar);
    cv::Scalar scal(scalar[0], scalar[1], scalar[2], scalar[3]);
    cv::min(*ZV_ADP_OBJ_MP(src1), scal, *ZV_ADP_OBJ_MP(dst));
    return ZV_ST_OK;
}

int zv_arith_magnitude(ZvObject x, ZvObject y, ZvObject magnitude)
{
    ZV_CHK_NULL3(x, y, magnitude);
    cv::magnitude(*ZV_ADP_OBJ_MP(x), *ZV_ADP_OBJ_MP(y), *ZV_ADP_OBJ_MP(magnitude));
    return ZV_ST_OK;
}

int zv_arith_phase(ZvObject x, ZvObject y, ZvObject radian)
{
    ZV_CHK_NULL3(x, y, radian);
    phase(*ZV_ADP_OBJ_MP(x), *ZV_ADP_OBJ_MP(y), *ZV_ADP_OBJ_MP(radian));
    return ZV_ST_OK;
}

int zv_arith_integral(ZvObject src, ZvObject dst)
{
    ZV_CHK_NULL3(src, dst, magnitude);
    cv::integral(*ZV_ADP_OBJ_MP(src), *ZV_ADP_OBJ_MP(dst), noArray(), noArray());
    return ZV_ST_OK;
}

int zv_arith_integral2(ZvObject src, ZvObject dst, ZvObject dstSqrt)
{
    ZV_CHK_NULL3(src, dst, magnitude);
    cv::integral(*ZV_ADP_OBJ_MP(src), *ZV_ADP_OBJ_MP(dst), *ZV_ADP_OBJ_MP(dstSqrt), noArray());
    return ZV_ST_OK;
}

int zv_arith_and(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZV_CHK_NULL3(src1, src2, dst);

    bitwise_and(ZV_ADP_IMG_GETM(src1), ZV_ADP_IMG_GETM(src2), ZV_ADP_IMG_GETM(dst));
    return ZV_ST_OK;
}

int zv_arith_or(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZV_CHK_NULL3(src1, src2, dst);

    bitwise_or(ZV_ADP_IMG_GETM(src1), ZV_ADP_IMG_GETM(src2), ZV_ADP_IMG_GETM(dst));
    return ZV_ST_OK;
}

int zv_arith_not(ZvImage src, ZvImage dst)
{
    ZV_CHK_NULL2(src, dst);

    bitwise_not(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst));
    return ZV_ST_OK;
}

int zv_arith_xor(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZV_CHK_NULL3(src1, src2, dst);

    bitwise_xor(ZV_ADP_IMG_GETM(src1), ZV_ADP_IMG_GETM(src2), ZV_ADP_IMG_GETM(dst));
    return ZV_ST_OK;
}

int zv_arith_transpose(ZvMatrix src, ZvMatrix dst)
{
    ZV_CHK_NULL2(src, dst);

    transpose(ZV_ADP_MAT_GETM(src), ZV_ADP_MAT_GETM(dst));
    return ZV_ST_OK;
}

////LU分解，矩阵必须是方阵；特征值分解，矩阵必须对称；Cholesky分解，矩阵必须正定；SVD分解
int zv_arith_invert(ZvMatrix src, ZvMatrix dst, int method)
{
    ZV_CHK_NULL2(src, dst);
    static int invertCvt[] = { 0, 2, 3, 1 };
    if (method >= sizeof(invertCvt) / sizeof(invertCvt[0]))
    {
        return ZV_ERR_FA_RANGE_3;
    }

    Mat srcMat = ZV_ADP_MAT_GETM(src);
    if (3 != method && srcMat.cols != srcMat.rows)
    {
        return ZV_ERR_MAT_NOT_SQUARE;
    }

    invert(srcMat, ZV_ADP_MAT_GETM(dst), method);
    return ZV_ST_OK;
}

// 0/1/2 -- 无穷范数（最值），1 - 范数（绝对值和），2 - 范数
double zv_arith_norm(ZvMatrix mat, int normType)
{
    if (NULL == mat)
    {
        return 0;
    }
    static int normCvt[] = { NORM_INF, NORM_L1, NORM_L2 };
    if (normType >= sizeof(normCvt) / sizeof(normCvt[0]))
    {
        return 0;
    }

    return norm(ZV_ADP_MAT_GETM(mat), normCvt[normType]);
}

int zv_arith_matrixMult(ZvMatrix mat1, ZvMatrix mat2, ZvMatrix dst)
{
    ZV_CHK_NULL3(mat1, mat2, dst);

    Mat _mat1 = ZV_ADP_MAT_GETM(mat1);
    Mat _mat2 = ZV_ADP_MAT_GETM(mat2);
    Mat _dst(_mat1.rows, _mat2.cols, _mat1.type());

    if (_mat1.cols == _mat2.rows)
    {
        _dst = _mat1 * _mat2;
        ZV_ADP_IMG_SETM(dst, _dst);
        return ZV_ST_OK;
    }
    else
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }
}

int zv_arith_eigen(ZvMatrix src, ZvMatrix eigenvalues, ZvMatrix eigenvectors, bool isSymmetric)
{
    ZV_CHK_NULL3(src, eigenvalues, eigenvectors);
    if(isSymmetric)
        eigen(ZV_ADP_MAT_GETM(src), ZV_ADP_MAT_GETM(eigenvalues), ZV_ADP_MAT_GETM(eigenvectors));
    else 
        eigenNonSymmetric(ZV_ADP_MAT_GETM(src), ZV_ADP_MAT_GETM(eigenvalues),
            ZV_ADP_MAT_GETM(eigenvectors));
    return ZV_ST_OK;
}


// 统计 src 中零元素的数量
int zv_arith_zeroCount(ZvObject src)
{
    ZV_CHK_NULL1(src);
    cv::Mat *_src = ZV_ADP_OBJ_MP(src);
    cv::Mat tmp = _src->reshape(1);
    return (int)tmp.total() - cv::countNonZero(tmp);
}

// 求各个独立通道所有像素的和
int zv_arith_sum(ZvObject src, double *channelSum)
{
    ZV_CHK_NULL2(src, channelSum);

    cv::Mat * pSrc = ZV_ADP_OBJ_MP(src);
    Scalar scalar = sum(*pSrc);

    for (int i = 0; i < pSrc->channels(); i++)
    {
        channelSum[i] = scalar[i];
    }

    return ZV_ST_OK;
}

//行元素统计-和、均值、最大、最小
int zv_arith_statRow(ZvObject src, ZvObject dst, int type)
{
    ZV_CHK_NULL2(src, dst);
    if (type > cv::REDUCE_MIN || 0 > type)
    {
        return ZV_ERR_FA_RANGE_3;
    }
    reduce(*(ZV_ADP_OBJ_MP(src)), *(ZV_ADP_OBJ_MP(dst)), 1, type, cv::REDUCE_AVG >= type ? CV_64F : -1);
    return ZV_ST_OK;
}

int zv_arith_statCol(ZvObject src, ZvObject dst, int type)
{
    ZV_CHK_NULL2(src, dst);
    if (type > cv::REDUCE_MIN || 0 > type)
    {
        return ZV_ERR_FA_RANGE_3;
    }
    reduce(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), 0, type, cv::REDUCE_AVG >= type ? CV_64F : -1);
    return ZV_ST_OK;
}

// 求图像的均值
int zv_arith_mean(ZvObject src, double *mean)
{
    ZV_CHK_NULL2(src, mean);

    cv::Mat *pSrc = ZV_ADP_OBJ_MP(src);
    int cn = pSrc->channels();
    cv::Scalar scale = cv::mean(*pSrc);

    for (int i = 0; i < cn; i++)
    {
        mean[i] = scale[i];
    }

    return ZV_ST_OK;
}

// 求图像的均值和标准差
int zv_arith_meanSdev(ZvObject src, double *mean, double *stdDev)
{
    ZV_CHK_NULL3(src, mean, stdDev);
    
    cv::Mat *pSrc = ZV_ADP_OBJ_MP(src);
    int cn = pSrc->channels();
    vector<double> vMean, vDev;
    cv::meanStdDev(*pSrc, vMean, vDev);
    for (int i = 0; i < cn; i++)
    {
        mean[i] = vMean[i];
        stdDev[i] = vDev[i];
    }
    return ZV_ST_OK;
}

// 最值定位
int zv_arith_minMaxLoc(ZvObject _src, double *minValue, double *maxValue,
    int *minPosX, int *minPosY, int *maxPosX, int *maxPosY)
{
    ZV_CHK_NULL7(_src, minValue, maxValue, minPosX, minPosY, maxPosX, maxPosY);

    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(*ZV_ADP_OBJ_MP(_src), minValue, maxValue, &minLoc, &maxLoc);
    *minPosX = minLoc.x;
    *minPosY = minLoc.y;
    *maxPosX = maxLoc.x;
    *maxPosY = maxLoc.y;

    return ZV_ST_OK;
}

// 求 灰度图像 的直方图, size: 为设置的bin的个数, {low, upper} 为：统计像素值的区间
int zv_arith_hist(ZvImage img, ZvMatrix hist, int size, double low, double upper)
{
    ZV_CHK_NULL2(img, hist);
    if (1 != zv_img_channels(img))
    {
        return ZV_ERR_I_CN_SRC;
    }

    cv::Mat matImg = ZV_ADP_IMG_GETM(img);
    cv::Mat matHist;

    int channels = 0;     // 图像的第0通道
    float range[] = { (float)low, (float)upper };
    const float* histrange = { range };

    cv::calcHist(&matImg, 1, &channels, cv::noArray(), matHist, 1, &size, &histrange);
    matHist.convertTo(ZV_ADP_MAT_GETM(hist), CV_64F);

    return ZV_ST_OK;
}
