#include "zv_private.h"
#include "zv_basis.h"

using namespace cv;

int zv_ip_medianBlur(ZvImage src, ZvImage dst, int size)
{
    ZV_CHK_NULL2(src, dst);
    size = size | 0x1; //必须奇数
    cv::medianBlur(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), size);
    return ZV_ST_OK;
}

int zv_ip_gaussBlur(ZvImage src, ZvImage dst, int size)
{
    ZV_CHK_NULL2(src, dst);
    size = size | 0x1; //必须奇数
    cv::GaussianBlur(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), cv::Size(size, size), 0, 0);
    return ZV_ST_OK;
}

//均值滤波
int zv_ip_meanBlur(ZvImage src, ZvImage dst, int size)
{
    ZV_CHK_NULL2(src, dst);
    cv::boxFilter(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), -1, cv::Size(size, size));
    return ZV_ST_OK;
}

//双边滤波
int zv_ip_bilateralFilter(ZvImage src, ZvImage dst, double sigmaSpace, double sigmaColor)
{
    ZV_CHK_NULL2(src, dst);
    cv::bilateralFilter(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), -1, sigmaColor, sigmaSpace);
    return ZV_ST_OK;
}

// soble 滤波
int zv_ip_sobel(ZvImage src, ZvImage dst, int dx, int dy, int size)
{
    ZV_CHK_NULL2(src, dst);
    size |= 0x1;
    if (size > 31)
    {
        return ZV_ERR_FA_RANGE_5;
    }

    cv::Mat _src = ZV_ADP_IMG_GETM(src);
    cv::Mat _dst = ZV_ADP_IMG_GETM(dst);

    cv::Sobel(_src, _dst, _src.depth(), dx, dy, size, 1, 0);
    ZV_ADP_IMG_SETM(dst, _dst);
    return ZV_ST_OK;
}

// Scharr 滤波
int zv_ip_scharr(ZvImage src, ZvImage dst, int dx, int dy)
{
    ZV_CHK_NULL2(src, dst);

    cv::Mat _src = ZV_ADP_IMG_GETM(src);
    cv::Mat _dst = ZV_ADP_IMG_GETM(dst);

    cv::Scharr(_src, _dst, _src.depth(), dx, dy, 1, 0);
    ZV_ADP_IMG_SETM(dst, _dst);
    return ZV_ST_OK;
}

// Laplacian 滤波变换
int zv_ip_laplace(ZvImage src, ZvImage dst, int size)
{
    ZV_CHK_NULL2(src, dst);
    size |= 0x1;
    if (size > 31)
    {
        return ZV_ERR_FA_RANGE_5;
    }

    cv::Mat _src = ZV_ADP_IMG_GETM(src);
    cv::Mat _dst = ZV_ADP_IMG_GETM(dst);

    cv::Laplacian(_src, _dst, _src.depth(), size, 1, 0);
    ZV_ADP_IMG_SETM(dst, _dst);
    return ZV_ST_OK;
}

// Canny 算子 得到图像的边缘
int zv_ip_canny(ZvImage src, ZvImage dst, double thresh1, double thresh2, int size)
{
    ZV_CHK_NULL2(src, dst);
    size |= 0x1;
    if (size < 3 || size > 7)
    {
        size = -1;
    }

    cv::Mat *_src = ZV_ADP_IMG_MP(src);
    cv::Mat *_dst = ZV_ADP_IMG_MP(dst);

    cv::Canny(*_src, *_dst, thresh1, thresh2, size);
    return ZV_ST_OK;
}

// 直方图均衡化增强 - 8UC1
int zv_ip_equalizeHist(ZvImage _src, ZvImage _dst)
{
    ZV_CHK_NULL2(_src, _dst);   // 检查合法性

    if (1 != zv_img_channels(_src))
    {
        return ZV_ERR_I_CN_SRC;
    }
    if (ZV_PIXEL_8U != zv_img_dataType(_src))
    {
        return ZV_ERR_I_DEPTH;
    }

    equalizeHist(ZV_ADP_IMG_GETM(_src), ZV_ADP_IMG_GETM(_dst));

    return ZV_ST_OK;
}
