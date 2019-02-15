#include "zv_private.h"
#include "zv_basis.h"

using namespace cv;

int zv_ip_rgbToGray(ZvImage rgb, ZvImage gray)
{
    ZV_CHK_NULL2(rgb, gray);
    if (ZV_PIXEL_8U != zv_img_dataType(rgb) && ZV_PIXEL_16U != zv_img_dataType(rgb))
    {
        return ZV_ERR_I_DEPTH;
    }

    Mat src = ZV_ADP_IMG_GETM(rgb);
    int scn = src.channels();
    if (3 != scn && 4 != scn)
    {
        return ZV_ERR_I_CN_SRC;
    }

    int code = 4 == scn ? COLOR_RGBA2GRAY : COLOR_RGB2GRAY;
    cvtColor(src, ZV_ADP_IMG_GETM(gray), code);

    return ZV_ST_OK;
}

int zv_ip_grayToRgb(ZvImage gray, ZvImage rgb) 
{
    ZV_CHK_NULL2(gray, rgb);
    if (ZV_PIXEL_8U != zv_img_dataType(gray) && ZV_PIXEL_16U != zv_img_dataType(gray))
    {
        return ZV_ERR_I_DEPTH;
    }

    cvtColor(ZV_ADP_IMG_GETM(gray), ZV_ADP_IMG_GETM(rgb), COLOR_GRAY2BGR);

    return ZV_ST_OK;
}

static int s_zv_ip_cvtToRgb[ZV_CLR_MAX] = { COLOR_YUV2RGB, COLOR_HSV2RGB, COLOR_Lab2RGB,
    COLOR_HLS2RGB, COLOR_YCrCb2RGB, COLOR_Luv2RGB, COLOR_XYZ2RGB, COLOR_RGBA2RGB };
int zv_ip_colorToRgb(ZvImage color, ZvImage rgb, int colorSpace)
{
    ZV_CHK_NULL2(color, rgb);
    if (3 > zv_img_channels(color))
    {
        return ZV_ERR_I_CN_SRC;
    }
    if (ZV_PIXEL_8U != zv_img_dataType(rgb))
    {
        return ZV_ERR_I_DEPTH;
    }
    if (colorSpace >= sizeof(s_zv_ip_cvtToRgb)/sizeof(s_zv_ip_cvtToRgb[0]))
    {
        return ZV_ERR_FA_RANGE_3;
    }

    cvtColor(ZV_ADP_IMG_GETM(color), ZV_ADP_IMG_GETM(rgb), s_zv_ip_cvtToRgb[colorSpace]);

    return ZV_ST_OK;
}

static int s_zv_ip_cvtToClr[] = { COLOR_RGB2YUV, COLOR_RGB2HSV, COLOR_RGB2Lab,
    COLOR_BGR2HLS, COLOR_RGB2YCrCb, COLOR_RGB2Luv, COLOR_RGB2XYZ, COLOR_RGB2RGBA };
int zv_ip_rgbToColor(ZvImage rgb, ZvImage color, int colorSpace)
{
    ZV_CHK_NULL2(rgb, color);
    if (3 != zv_img_channels(rgb))
    {
        return ZV_ERR_I_CN_SRC;
    }
    if (ZV_PIXEL_8U != zv_img_dataType(rgb))
    {
        return ZV_ERR_I_DEPTH;
    }
    if (colorSpace >= sizeof(s_zv_ip_cvtToClr)/sizeof(s_zv_ip_cvtToClr[0]))
    {
        return ZV_ERR_FA_RANGE_3;
    }

    cvtColor(ZV_ADP_IMG_GETM(rgb), ZV_ADP_IMG_GETM(color), s_zv_ip_cvtToClr[colorSpace]);

    return ZV_ST_OK;
}

static int s_zv_ip_cvtBayer[] = { COLOR_BayerBG2RGB, COLOR_BayerGB2RGB, COLOR_BayerRG2RGB, COLOR_BayerGR2RGB };
int zv_ip_bayerToRgb(ZvImage bayer, ZvImage rgb, int bayerType)
{
    ZV_CHK_NULL2(bayer, rgb);
    if (bayerType >= sizeof(s_zv_ip_cvtBayer)/sizeof(s_zv_ip_cvtBayer[0]))
    {
        return ZV_ERR_FA_RANGE_3;
    }
    if (ZV_PIXEL_8U != zv_img_dataType(bayer) && ZV_PIXEL_16U != zv_img_dataType(bayer))
    {
        return ZV_ERR_I_DEPTH;
    }

    cvtColor(ZV_ADP_IMG_GETM(bayer), ZV_ADP_IMG_GETM(rgb), s_zv_ip_cvtBayer[bayerType]);

    return ZV_ST_OK;
}
