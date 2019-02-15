#include "zv_private.h"
#include "zv_basis.h"

//三种阈值算法
int zv_ip_threshold(ZvImage src, ZvImage dst, double lowThresh, double uppThresh, bool isInv)
{
    ZV_CHK_NULL2(src, dst);
    cv::Mat _dst = ZV_ADP_IMG_GETM(dst);
    cv::inRange(ZV_ADP_IMG_GETM(src), cv::Scalar::all(lowThresh), cv::Scalar::all(uppThresh), _dst);
    if (isInv)
        _dst = 255 - _dst;
    ZV_ADP_IMG_SETM(dst, _dst);
    return ZV_ST_OK;
}

int zv_ip_adpThreshold(ZvImage src, ZvImage thresh, ZvImage dst, double offset, bool isInv)
{
    ZV_CHK_NULL3(src, thresh, dst);
    /////////////////TODO
    //cv::adaptiveThreshold(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), 255, filterType, rangeType, blockSize, offset);
    return ZV_ST_OK;
}

int zv_ip_autoThreshold(ZvImage src, ZvImage dst, double * thresh)
{
    ZV_CHK_NULL2(src, dst);
    double _thresh = cv::threshold(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), 0, 255, cv::THRESH_OTSU | cv::THRESH_BINARY);
    if (NULL != thresh)
    {
        *thresh = _thresh;
    }
    return ZV_ST_OK;
}

int zv_ip_label(ZvImage src, ZvImage label, int connectivity)
{
    ZV_CHK_NULL2(src, label);
    cv::connectedComponents(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(label), connectivity, CV_16U);

    return ZV_ST_OK;
}