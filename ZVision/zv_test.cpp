#include "zv_private.h"
#include "zv_module.h"


#ifdef ZV_WITH_TEST
using namespace cv;

// 0/1/2 -- 无穷范数（最值），1 - 范数（绝对值和），2 - 范数
double zv_testNorm(ZvMatrix mat, int normType)
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

// 绝对差值
int zv_testAbsDiff(ZvObject _src1, ZvObject _src2, ZvObject _dst)
{
    ZV_CHK_NULL3(_src1, _src2, _dst);

    //判断矩阵的大小、类型是否相同
    Mat src1 = ZV_ADP_IMG_GETM(_src1);
    Mat src2 = ZV_ADP_IMG_GETM(_src2);

    if (src1.size() != src2.size())
    {
        return ZV_ERR_M_SIZE_UNMATCH;
    }

    if (src1.type() != src2.type())
    {
        return ZV_ERR_M_TYPE_UNMATCH;
    }
    cv::absdiff(src1, src2, ZV_ADP_IMG_GETM(_dst));
    return ZV_ST_OK;
}

int zv_testFillRandU(ZvObject obj, double lower, double upper)
{
    ZV_CHK_NULL1(obj);

    RNG r;
    r.fill(*ZV_ADP_OBJ_MP(obj), RNG::UNIFORM, lower, upper);
    return ZV_ST_OK;
}

int zv_testFillRandN(ZvObject obj, double mean, double stddev)
{
    ZV_CHK_NULL1(obj);

    RNG r;
    r.fill(*ZV_ADP_OBJ_MP(obj), RNG::NORMAL, mean, stddev);
    return ZV_ST_OK;
}

int zv_testRandU()
{
    return int(theRNG());
}

double zv_testRandUD()
{
    return double(theRNG());
}

double zv_testRandN()
{
    return theRNG().gaussian(1);
}

#endif