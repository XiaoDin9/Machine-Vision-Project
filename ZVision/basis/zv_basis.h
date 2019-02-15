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

int zv_arith_abs(ZvObject src, ZvObject dst);
int zv_arith_absDiff(ZvObject src1, ZvObject src2, ZvObject dst, double mult);
int zv_arith_add(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add);
int zv_arith_sub(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add);
int zv_arith_mul(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add);
int zv_arith_div(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add);
int zv_arith_scale(ZvObject src, ZvObject dst, double mult, double add);
int zv_arith_addWeighted(ZvObject src1, ZvObject src2, ZvObject dst, double weight1, double weight2, double add);
int zv_arith_sin(ZvObject src, ZvObject dst);
int zv_arith_cos(ZvObject src, ZvObject dst);
int zv_arith_tan(ZvObject src, ZvObject dst);
int zv_arith_asin(ZvObject src, ZvObject dst);
int zv_arith_acos(ZvObject src, ZvObject dst);
int zv_arith_atan(ZvObject src, ZvObject dst);
int zv_arith_atan2(ZvObject y, ZvObject x, ZvObject dst);
int zv_arith_exp(ZvObject src, ZvObject dst, int baseType);
int zv_arith_log(ZvObject src, ZvObject dst, int baseType);
int zv_arith_pow(ZvObject src, ZvObject dst, double exponent);
int zv_arith_sqrt(ZvObject src, ZvObject dst);
int zv_arith_compare(ZvObject src1, ZvObject src2, ZvImage dst, int op);
int zv_arith_max(ZvObject src1, ZvObject src2, ZvObject dst);
int zv_arith_min(ZvObject src1, ZvObject src2, ZvObject dst);
int zv_arith_maxS(ZvObject src1, ZvObject dst, double *scalar);
int zv_arith_minS(ZvObject src1, ZvObject dst, double *scalar);
int zv_arith_magnitude(ZvObject x, ZvObject y, ZvObject magnitude);
int zv_arith_phase(ZvObject x, ZvObject y, ZvObject radian);
int zv_arith_integral(ZvObject src, ZvObject dst);
int zv_arith_integral2(ZvObject src, ZvObject dst, ZvObject dstSqrt);
int zv_arith_and(ZvImage src1, ZvImage src2, ZvImage dst);
int zv_arith_or(ZvImage src1, ZvImage src2, ZvImage dst);
int zv_arith_not(ZvImage src, ZvImage dst);
int zv_arith_xor(ZvImage src1, ZvImage src2, ZvImage dst);
int zv_arith_transpose(ZvMatrix src, ZvMatrix dst);
int zv_arith_invert(ZvMatrix src, ZvMatrix dst, int method);
double zv_arith_norm(ZvMatrix mat, int normType);
int zv_arith_matrixMult(ZvMatrix mat1, ZvMatrix mat2, ZvMatrix dst);
int zv_arith_eigen(ZvMatrix src, ZvMatrix eigenvalues, ZvMatrix eigenvectors, bool isSymmetric);

int zv_arith_zeroCount(ZvObject src);
int zv_arith_sum(ZvObject src, double * sum);
int zv_arith_statRow(ZvObject src, ZvObject dst, int type);
int zv_arith_statCol(ZvObject src, ZvObject dst, int type);
int zv_arith_mean(ZvObject src, double *mean);
int zv_arith_meanSdev(ZvObject src, double *mean, double *stdDev);
int zv_arith_minMaxLoc(ZvObject src, double *minValue, double *maxValue,
    int *minPosX, int *minPosY, int *maxPosX, int *maxPosY);
int zv_arith_hist(ZvImage img, ZvMatrix hist, int size, double low, double upper);

int zv_ip_mirror(ZvImage src, ZvImage dst, int type);
int zv_ip_rotate(ZvImage src, ZvImage dst, double angle, int interp);
int zv_ip_zoom(ZvImage src, ZvImage dst, double scaleW, double scaleH, int interp);
int zv_ip_resize(ZvImage src, ZvImage dst, int dstW, int dstH, int interp);
int zv_ip_affine(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border);
int zv_ip_perspective(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border);
double zv_ip_moments(ZvImage binImg, int type, int orderX, int orderY);
int zv_ip_warpRect2(ZvImage src, ZvImage _roi, double cx, double cy, double width,
    double height, double angle, int interp);

int zv_ip_warpRing(ZvImage src, ZvImage dst, double cx, double cy, double r,
    double startA, double extentA, double annR, int interp);

int zv_ip_rgbToGray(ZvImage rgb, ZvImage gray);
int zv_ip_grayToRgb(ZvImage gray, ZvImage rgb);
int zv_ip_colorToRgb(ZvImage color, ZvImage rgb, int colorSpace);
int zv_ip_rgbToColor(ZvImage rgb, ZvImage color, int colorSpace);
int zv_ip_bayerToRgb(ZvImage bayer, ZvImage rgb, int bayerType);

int zv_ip_medianBlur(ZvImage src, ZvImage dst, int size);
int zv_ip_meanBlur(ZvImage src, ZvImage dst, int size);
int zv_ip_gaussBlur(ZvImage src, ZvImage dst, int size);
int zv_ip_bilateralFilter(ZvImage src, ZvImage dst, double sigmaSpace, double sigmaColor);
int zv_ip_sobel(ZvImage src, ZvImage dst, int dx, int dy, int size);
int zv_ip_scharr(ZvImage src, ZvImage dst, int dx, int dy);
int zv_ip_laplace(ZvImage src, ZvImage dst, int size);
int zv_ip_canny(ZvImage img, ZvImage dst, double thresh1, double thresh2, int size);
int zv_ip_equalizeHist(ZvImage src, ZvImage dst);

int zv_ip_dilate(ZvImage src, ZvImage dst, int seWidth, int seHeight);
int zv_ip_erode(ZvImage src, ZvImage dst, int seWidth, int seHeight);
int zv_ip_opening(ZvImage src, ZvImage dst, int seWidth, int seHeight);
int zv_ip_closing(ZvImage src, ZvImage dst, int seWidth, int seHeight);
int zv_ip_morphSe(ZvImage kernel, int shape, int sizeX, int sizeY, int anchorX, int anchorY);
int zv_ip_morph(ZvImage src, ZvImage dst, ZvImage kernel,
    int op, int anchorX, int anchorY, int iter, char *border);

int zv_ip_threshold(ZvImage src, ZvImage dst, double thresh0, double thresh1, bool isInv);
int zv_ip_adpThreshold(ZvImage src, ZvImage thresh, ZvImage dst, double offset, bool isInv);
int zv_ip_autoThreshold(ZvImage src, ZvImage dst, double * thresh);

int zv_ip_label(ZvImage src, ZvImage label, int connectivity);

#ifdef __cplusplus
}
#endif

#endif
