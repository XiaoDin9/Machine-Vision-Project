#include "zv_private.h"
#include "zv_basis.h"


// 图像做镜像处理
//type:标志来指定如何翻转数组; 
//0 表示围绕x轴翻转，1表示围绕y轴翻转。 2表示翻转两个轴。
int zv_ip_mirror(ZvImage src, ZvImage dst, int type)
{
    ZV_CHK_NULL2(src, dst);

    if (2 == type)
    {
        type = -1;
    }
    else if (0 != type && 1 != type)
    {
        return ZV_ERR_FA_RANGE_3;
    }
    cv::Mat _dst = ZV_ADP_IMG_GETM(dst);
    cv::flip(ZV_ADP_IMG_GETM(src), _dst, type);
    ZV_ADP_IMG_SETM(dst, _dst);
    return ZV_ST_OK;
}

// 图像旋转处理, angle角度
int zv_ip_rotate(ZvImage src, ZvImage dst, double angle, int interp)
{
    ZV_CHK_NULL2(src, dst);

    cv::Mat _src = ZV_ADP_IMG_GETM(src);
    cv::Mat _dst = ZV_ADP_IMG_GETM(dst);
    cv::Point2f center(_src.cols / 2.f, _src.rows / 2.f);

    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);    // 获得旋转矩阵, 这个函数返回一个 2 x 3 矩阵 
    cv::warpAffine(_src, _dst, rot, _src.size(), interp);   // rot: 得到旋转的矩阵，bbox.size() 最终旋转后的图像

    ZV_ADP_IMG_SETM(dst, _dst);
    return ZV_ST_OK;
}

int zv_ip_zoom(ZvImage src, ZvImage dst, double scaleW, double scaleH, int interp)
{
    ZV_CHK_NULL2(src, dst);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_5;
    }

    if (scaleW < ZV_EPS_AC7)
    {
        return ZV_ERR_FA_RANGE_3;
    }

    if (scaleH < ZV_EPS_AC7)
    {
        scaleH = scaleW;
    }
    cv::resize(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), cv::Size(0, 0), scaleW, scaleH, interp);
    return ZV_ST_OK;
}

int zv_ip_resize(ZvImage src, ZvImage dst, int width, int height, int interp)
{
    ZV_CHK_NULL2(src, dst);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_5;
    }

    if (width <= 0)
    {
        return ZV_ERR_FA_RANGE_3;
    }

    if (height <= 0)
    {
        height = width;
    }
    cv::resize(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), cv::Size(width, height), 0, 0, interp);
    return ZV_ST_OK;
}

// 图像仿射变换
// mat 矩阵为 3x2矩阵，为变换后的图像上的三个点坐标值， 数据类型为CV_64FC1
int zv_ip_affine(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border)
{
    ZV_CHK_NULL3(src, dst, mat);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_6;
    }
    if (NULL == border)
    {
        border = "0";
    }

    int borderType;
    double borderValue;
    zv_adp_borderInfo(border, borderType, borderValue);
    warpAffine(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), ZV_ADP_MAT_GETM(mat),
        cv::Size(dstW, dstH), interp, borderType, borderValue);

    return ZV_ST_OK;
}

// 图像透射变换
int zv_ip_perspective(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border)
{
    ZV_CHK_NULL3(src, dst, mat);
    if (ZV_INTERP_MAX <= interp)
    {
        return ZV_ERR_FA_RANGE_6;
    }
    if (NULL == border)
    {
        border = "0";
    }

    int borderType;
    double borderValue;
    zv_adp_borderInfo(border, borderType, borderValue);
    cv::warpPerspective(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), ZV_ADP_MAT_GETM(mat),
        cv::Size(dstW, dstH), interp, borderType, borderValue);
    return ZV_ST_OK;
}

double zv_ip_moments(ZvImage binImg, int type, int orderX, int orderY)
{
    //////////////////TODO
    return 0;
}

// 在src 图像上得到一个 旋转矩形 ROI 的图 
// angle 负数为逆时针旋转
int zv_ip_warpRect2(ZvImage src, ZvImage roi, double cx, double cy, double width,
    double height, double angle, int interp)
{
    ZV_CHK_NULL2(src, roi);

    cv::Mat mapx, mapy;
    angle = ZV_TO_RAD(angle);
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    cv::Size dstSize(cvRound(width), cvRound(height));
    mapx.create(dstSize, CV_32F);
    mapy.create(dstSize, CV_32F);

    width = width / 2.0 - 0.5;
    height = height / 2.0 - 0.5;
    for (int k = 0; k < dstSize.height; k++)
    {
        float* mx = (float*)(mapx.data + k*mapx.step);
        float* my = (float*)(mapy.data + k*mapy.step);
        for (int i = 0; i < dstSize.width; i++)
        {
            double dX = i - width;
            double dY = k - height;
            mx[i] = (float)(cx + dX * cosAngle - dY * sinAngle);
            my[i] = (float)(cy + dX * sinAngle + dY * cosAngle);
        }
    }

    cv::remap(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(roi), mapx, mapy, 0 > interp ? cv::INTER_LINEAR : ZV_ADP_INTERP(interp), cv::BORDER_REPLICATE);
    return ZV_ST_OK;
}

int zv_ip_warpRing(ZvImage src, ZvImage dst, double cx, double cy, double r,
    double angleStart, double angleExt, double annR, int interp)
{
    ZV_CHK_NULL2(src, dst);

    cv::Mat mapx, mapy;
    angleStart = ZV_TO_RAD(angleStart);
    cv::Size dstSize(cvRound(2 * ZV_PI * r * angleExt / 360.0), cvRound(2 * annR + 1));
    mapx.create(dstSize, CV_32F);
    mapy.create(dstSize, CV_32F);
    
    for (int k = 0; k < dstSize.height; k++)
    {
        double dstR = r - annR + k;
        float* mx = (float*)(mapx.data + k*mapx.step);
        float* my = (float*)(mapy.data + k*mapy.step);

        for (int i = 0; i < dstSize.width; i++)
        {
            mx[i] = (float)(dstR*cos(i / r + angleStart) + cx);
            my[i] = (float)(dstR*sin(i / r + angleStart) + cy);
        }
    }

    cv::remap(ZV_ADP_IMG_GETM(src), ZV_ADP_IMG_GETM(dst), mapx, mapy, 0 > interp ? cv::INTER_LINEAR : ZV_ADP_INTERP(interp), cv::BORDER_REPLICATE);

    return ZV_ST_OK;
}