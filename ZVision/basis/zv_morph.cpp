#include "zv_private.h"
#include "zv_basis.h"


static int zv_ip_rectMorph(ZvImage src, ZvImage dst, int kw, int kh, int op)
{
    ZV_CHK_NULL2(src, dst);
    if (-1 == kh)
    {
        kh = kw;
    }

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kw, kh));
    cv::morphologyEx(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), op, kernel);
    return ZV_ST_OK;
}

int zv_ip_erode(ZvImage src, ZvImage dst, int kw, int kh)
{
    return zv_ip_rectMorph(src, dst, kw, kh, cv::MORPH_ERODE);
}

int zv_ip_dilate(ZvImage src, ZvImage dst, int kw, int kh)
{
    return zv_ip_rectMorph(src, dst, kw, kh, cv::MORPH_DILATE);
}

int zv_ip_opening(ZvImage src, ZvImage dst, int kw, int kh)
{
    return zv_ip_rectMorph(src, dst, kw, kh, cv::MORPH_OPEN);
}

int zv_ip_closing(ZvImage src, ZvImage dst, int kw, int kh)
{
    return zv_ip_rectMorph(src, dst, kw, kh, cv::MORPH_CLOSE);
}

int zv_ip_morphSe(ZvImage kernel, int shape, int sizeX, int sizeY, int anchorX, int anchorY)
{
    ZV_CHK_NULL1(kernel);
    if (shape > cv::MORPH_ELLIPSE)
    {
        return ZV_ERR_MP_SHAPE;
    }

    cv::Mat k = cv::getStructuringElement(shape, cv::Size(sizeX, sizeY), cv::Point(anchorX, anchorY));
    ZV_ADP_IMG_SETM(kernel, k);
    return ZV_ST_OK;
}

int zv_ip_morph(ZvImage src, ZvImage dst, ZvImage kernel,
    int op, int anchorX, int anchorY, int iter, char *border)
{
    ZV_CHK_NULL2(src, dst);
    cv::Mat _kernel = cv::Mat();
    if (NULL != kernel)
    {
        _kernel = ZV_ADP_IMG_GETM(kernel);
    }
    if (ZV_MORPH_MAX <= op)
    {
        return ZV_ERR_MP_TYPE;
    }
    if (NULL == border)
    {
        border = "continue";
    }

    int borderType;
    double borderValue;
    zv_adp_borderInfo(border, borderType, borderValue);
    cv::morphologyEx(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), op, _kernel, cv::Point(anchorX, anchorY), iter, borderType, borderValue);
    return ZV_ST_OK;
}
