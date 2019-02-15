#include "zv_private.h"
#include "zv_core.h"


using namespace cv;

int zv_img_genConst(ZvImage img, int width, int height, int type, int channel, double *element)
{
    ZV_CHK_NULL1(img);

    if (channel >= ZV_SYS_CHANNELS_MAX)
    {
        return ZV_ERR_FA_RANGE_5;
    }
    if ((uint)type > ZV_PIXEL_64F)
    {
        return ZV_ERR_FA_RANGE_4;
    }

    Mat m(height, width, CV_MAKE_TYPE(g_zv_adp_depthToCV[type], channel));
    Scalar scalar;
    for (int i = 0; i < channel; i++)
    {
        scalar.val[i] = element ? element[i] : 0;
    }
    m.setTo(scalar);
    ZV_ADP_IMG_SETM(img, m);

    return ZV_ST_OK;
}

int zv_img_genData(ZvImage img, int width, int height, int type, int channel, void *data)
{
    ZV_CHK_NULL1(img);
    if (NULL == data)
    {
        return ZV_ERR_FA_NULL_6;
    }

    if (channel >= ZV_SYS_CHANNELS_MAX)
    {
        return ZV_ERR_FA_RANGE_5;
    }
    if ((uint)type > ZV_PIXEL_64F)
    {
        return ZV_ERR_FA_RANGE_4;
    }

    Mat m(height, width, CV_MAKE_TYPE(g_zv_adp_depthToCV[type], channel), data);
    ZV_ADP_IMG_SETM(img, m);
    return ZV_ST_OK;
}

double zv_img_getValue(ZvImage img, int x, int y, int channel)
{
    double element[4] = { 0 };
    if (channel >= zv_img_channels(img))
    {
        return 0;
    }

    zv_img_getElement(img, x, y, element);

    return element[channel];
}

int zv_img_setValue(ZvImage img, int x, int y, int channel, double value)
{
    ZV_CHK_NULL1(img);

    Mat _img = ZV_ADP_IMG_GETM(img);

    if (x >= _img.cols)
    {
        return ZV_ERR_FA_RANGE_2;
    }

    if (y >= _img.rows)
    {
        return ZV_ERR_FA_RANGE_3;
    }

    if (channel >= _img.channels())
    {
        return ZV_ERR_FA_RANGE_4;
    }

    IplImage iplImg(_img);
    CvScalar scalar = cvGet2D(&iplImg, y, x);
    scalar.val[channel] = value;
    cvSet2D(&iplImg, y, x, scalar);

    return ZV_ST_OK;
}

int zv_img_getElement(ZvImage img, int x, int y, double *element)
{
    ZV_CHK_NULL1(img);

    Mat _img = ZV_ADP_IMG_GETM(img);

    if (x >= _img.cols)
    {
        return ZV_ERR_FA_RANGE_2;
    }

    if (y >= _img.rows)
    {
        return ZV_ERR_FA_RANGE_3;
    }

    IplImage iplImg(_img);
    CvScalar scalar = cvGet2D(&iplImg, y, x);
    for (int i = 0; i < _img.channels(); i++)
    {
        element[i] = scalar.val[i];
    }

    return ZV_ST_OK;
}

int zv_img_setElement(ZvImage img, int x, int y, double *element)
{
    ZV_CHK_NULL1(img);

    Mat _img = ZV_ADP_IMG_GETM(img);
    if (x >= _img.cols)
    {
        return ZV_ERR_FA_RANGE_2;
    }
    if (y >= _img.rows)
    {
        return ZV_ERR_FA_RANGE_3;
    }

    CvScalar scalar = { 0 };
    for (int i = 0; i < _img.channels(); i++)
    {
        scalar.val[i] = element[i];
    }

    IplImage iplImg(_img);
    cvSet2D(&iplImg, y, x, scalar);

    return ZV_ST_OK;
}

int zv_img_getData(ZvImage img, void * buf, int size, bool isAlign)
{
    ZV_CHK_NULL2(img, buf);
    Mat src = ZV_ADP_IMG_GETM(img);
    Size dstSize = isAlign ? Size((src.cols + 3) >> 2 << 2, (src.rows + 3) >> 2 << 2) : src.size();
    Mat m(dstSize, src.type(), buf);
    if (m.total() * m.elemSize1() > size)
    {
        return ZV_ERR_G_BUF_SMALL;
    }

    m.setTo(Scalar::all(0));
    Rect roi(Point(0, 0), src.size());
    src.copyTo(m(roi));

    return ZV_ST_OK;
}

int zv_img_setData(ZvImage img, void *buf)
{
    ZV_CHK_NULL2(img, buf);
    if (0 == zv_img_width(img) || 0 == zv_img_height(img))
    {
        return ZV_ERR_M_SIZE_INVALID;
    }
    Mat _mat = ZV_ADP_IMG_GETM(img);
    Mat tmp(_mat.size(), _mat.type(), buf);
    tmp.copyTo(_mat);
    return ZV_ST_OK;
}

// 从原图像中提取一块 子图像
int zv_img_getSub(ZvImage src, ZvImage dst, int x, int y, int width, int height)
{
    ZV_CHK_NULL2(src, dst);
    if (0 > x)
    {
        return ZV_ERR_FA_RANGE_3;
    }
    if (0 > y)
    {
        return ZV_ERR_FA_RANGE_4;
    }
    if (x + width > zv_img_width(src))
    {
        return ZV_ERR_FA_RANGE_5;
    }
    if (y + height > zv_img_height(src))
    {
        return ZV_ERR_FA_RANGE_6;
    }

    Mat m = ZV_ADP_IMG_GETM(src);
    Mat sub = m(Rect(x, y, width, height));
    sub.copyTo(ZV_ADP_IMG_GETM(dst));
    return ZV_ST_OK;
}

int zv_img_setSub(ZvImage img, ZvImage sub, int x, int y)
{
    ZV_CHK_NULL2(img, sub);
    if (0 > x)
    {
        return ZV_ERR_FA_RANGE_3;
    }
    if (0 > y)
    {
        return ZV_ERR_FA_RANGE_4;
    }
    
    Mat m = ZV_ADP_IMG_GETM(img);
    Mat _sub = ZV_ADP_IMG_GETM(sub);
    if (x + _sub.cols > zv_img_width(img))
    {
        return ZV_ERR_M_OVER_SIZE;
    }
    if (y + _sub.rows > zv_img_height(img))
    {
        return ZV_ERR_M_OVER_SIZE;
    }

    m(Rect(x, y, _sub.cols, _sub.rows)) = _sub;
    return ZV_ST_OK;
}

int zv_img_convert(ZvImage src, ZvImage dst, int dstType, double mult, double add)
{
    ZV_CHK_NULL2(src, dst);
    if ((uint)dstType > ZV_PIXEL_64F)
    {
        return ZV_ERR_FA_RANGE_3;
    }
    ZV_ADP_IMG_GETM(src).convertTo(ZV_ADP_IMG_GETM(dst), g_zv_adp_depthToCV[dstType], mult, add);
    return ZV_ST_OK;
}

//赋值矩阵
int zv_img_copy(ZvImage src, ZvImage dst)
{
    ZV_CHK_NULL2(src, dst);
    ZV_ADP_IMG_SETM(dst, ZV_ADP_IMG_GETM(src).clone());
    return ZV_ST_OK;
}

int zv_img_split2(ZvImage src, ZvImage dst1, ZvImage dst2)
{
    ZV_CHK_NULL3(src, dst1, dst2);
    if (zv_img_channels(src) != 2)
    {
        return ZV_ERR_I_CN_SRC;
    }

    Mat dst[2] = { ZV_ADP_IMG_GETM(dst1), ZV_ADP_IMG_GETM(dst2) };
    split(ZV_ADP_IMG_GETM(src), dst);
    ZV_ADP_IMG_SETM(dst1, dst[0]);
    ZV_ADP_IMG_SETM(dst2, dst[1]);

    return ZV_ST_OK;
}

int zv_img_split3(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3)
{
    ZV_CHK_NULL4(src, dst1, dst2, dst3);
    if (zv_img_channels(src) != 3)
    {
        return ZV_ERR_I_CN_SRC;
    }

    Mat dst[3] = { ZV_ADP_IMG_GETM(dst1), ZV_ADP_IMG_GETM(dst2), ZV_ADP_IMG_GETM(dst3) };
    split(ZV_ADP_IMG_GETM(src), dst);
    ZV_ADP_IMG_SETM(dst1, dst[0]);
    ZV_ADP_IMG_SETM(dst2, dst[1]);
    ZV_ADP_IMG_SETM(dst3, dst[2]);

    return ZV_ST_OK;
}

int zv_img_split4(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3, ZvImage dst4)
{
    ZV_CHK_NULL5(src, dst1, dst2, dst3, dst4);
    if (zv_img_channels(src) != 4)
    {
        return ZV_ERR_I_CN_SRC;
    }

    Mat dst[4] = { ZV_ADP_IMG_GETM(dst1), ZV_ADP_IMG_GETM(dst2),
        ZV_ADP_IMG_GETM(dst3), ZV_ADP_IMG_GETM(dst4) };
    split(ZV_ADP_IMG_GETM(src), dst);
    ZV_ADP_IMG_SETM(dst1, dst[0]);
    ZV_ADP_IMG_SETM(dst2, dst[1]);
    ZV_ADP_IMG_SETM(dst3, dst[2]);
    ZV_ADP_IMG_SETM(dst4, dst[3]);

    return ZV_ST_OK;
}

int zv_img_merge2(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZV_CHK_NULL3(src1, src2, dst);

    Mat src[2] = { ZV_ADP_IMG_GETM(src1), ZV_ADP_IMG_GETM(src2)};
    merge(src, sizeof(src)/sizeof(src[0]), ZV_ADP_IMG_GETM(dst));

    return ZV_ST_OK;
}

int zv_img_merge3(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage dst)
{
    ZV_CHK_NULL4(src1, src2, src3, dst);

    Mat src[4] = { ZV_ADP_IMG_GETM(src1), ZV_ADP_IMG_GETM(src2),
        ZV_ADP_IMG_GETM(src3) };
    merge(src, sizeof(src) / sizeof(src[0]), ZV_ADP_IMG_GETM(dst));

    return ZV_ST_OK;
}

int zv_img_merge4(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage src4, ZvImage dst)
{
    ZV_CHK_NULL5(src1, src2, src3, src4, dst);

    Mat src[4] = { ZV_ADP_IMG_GETM(src1), ZV_ADP_IMG_GETM(src2),
        ZV_ADP_IMG_GETM(src3), ZV_ADP_IMG_GETM(src4) };
    merge(src, sizeof(src) / sizeof(src[0]), ZV_ADP_IMG_GETM(dst));

    return ZV_ST_OK;
}
