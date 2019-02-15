#ifndef ZV_BASIS_H
#define ZB_BASIS_H


#ifdef __cplusplus
extern "C"
{
#endif

typedef enum _ZvMorphType
{
    ZV_MORPH_ERODE = 0,
    ZV_MORPH_DILATE,
    ZV_MORPH_OPEN,
    ZV_MORPH_CLOSE,
    ZV_MORPH_GRADIENT,
    ZV_MORPH_TOPHAT,
    ZV_MORPH_BLACKHAT,
    ZV_MORPH_HITMISS,
    ZV_MORPH_MAX,
}ZvMorphType;

// zv_Arithmetic_op.cpp 文件中的函数声明
int zvAbsDiff(ZvImage _src1, ZvImage _src2, ZvImage _dst);
int zvAdd(ZvImage _src1, ZvImage _src2, ZvImage _dst);
int zvScaleAdd(ZvImage _src1, ZvImage _src2, ZvImage _dst, double scale1);
int zvSubtract(ZvImage _src1, ZvImage _src2, ZvImage _dst);
int zvAddWeighted(ZvImage _src1, ZvImage _src2, ZvImage _dst, double scale1, double scale2, double added, int dtype);
int zvMultiply(ZvImage _src1, ZvImage _src2, ZvImage _dst, double scale);
int zvDivide(double scale, ZvImage _src, ZvImage _dst);
int zvScaleRange(ZvImage src, ZvImage dst, int lower, int upper, int dType);
int zvCompare(ZvImage _src1, ZvImage _src2, ZvImage _dst, int cmpop);

int zvMedianFilter(ZvImage src, ZvImage dst, int size);
int zvGaussFilter(ZvImage src, ZvImage dst, int size);
int zvMeanFilter(ZvImage src, ZvImage dst, int size);
int zvBilateralFilter(ZvImage src, ZvImage dst, double sigmaSpace, double sigmaColor);
int zvEqualizeHist(ZvImage _src, ZvImage _dst);
int zvFilter2DEnhance(ZvImage _src, ZvImage _dst, ZvImage Kernel);

int zvThreshold(ZvImage src, ZvImage dst, int lowThresh, int uppThresh);
//filterType-滤波类型 0-均值 1-高斯；rangeType 0-大于 1-小于 /*2-范围内 3-范围外*/
int zvAdaptiveThreshold(ZvImage src, ZvImage dst, int blockSize, double offset, int rangeType, int filterType);
int zvAutoThreshold(ZvImage src, ZvImage dst, double *thresh);

int zvErode(ZvImage src, ZvImage dst, int kw, int kh);
int zvDilate(ZvImage src, ZvImage dst, int kw, int kh);
int zvOpening(ZvImage src, ZvImage dst, int kw, int kh);
int zvClosing(ZvImage src, ZvImage dst, int kw, int kh);

int zvZoom(ZvImage src, ZvImage dst, double scaleW, double scaleH, int interp);
int zvResize(ZvImage src, ZvImage dst, int width, int height, int interp);
int zvMirrorImage(ZvImage _src, ZvImage _dst, int flip_mode);
int zvRotateImage(ZvImage _src, ZvImage _dst, double angle, int interp);
int zvAffine(ZvImage _src, ZvImage _dst, ZvMatrix affineMat, int dstWidth, int dstHeight, int interp, int border);

#ifdef __cplusplus
}
#endif

#endif