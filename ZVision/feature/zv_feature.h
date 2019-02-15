#ifndef ZV_FEATURE_H
#define ZV_FEATURE_H


#ifdef __cplusplus
extern "C"
{
#endif
    

double zv_cont_area(ZvContour cont, bool isOriented ZV_CPP_DEF(false));
double zv_cont_length(ZvContour cont, bool isClosed ZV_CPP_DEF(true));
int zv_cont_center(ZvContour cont, double *centerX, double *centerY);
int zv_cont_isConvex(ZvContour cont);
double zv_cont_convexity(ZvContour cont);
double zv_cont_circularity(ZvContour cont);
double zv_cont_compactness(ZvContour cont);
int zv_cont_smallestRect(ZvContour cont, int *x, int *y, int *width, int *height);
int zv_cont_ellipticAxis(ZvContour cont, double *major, double * minor, double *angle);
int zv_cont_smallestRect2(ZvContour cont, double *cx, double *cy,
    double *width, double *height, double *angle);
int zv_cont_smallestCircle(ZvContour cont, double *x, double *y, double *r);
int zv_cont_convexHullIdx(ZvContour cont, int *ptIdx, int *bufLen);
int zv_cont_approxPoly(ZvContour cont, ZvContour poly, double epsilon, bool isClosed);
double zv_cont_moments(ZvContour cont, int type, int orderX, int orderY);
int zv_cont_huMoments(ZvContour cont, double *hu);
int zv_cont_sort(ZvContList contlist, int feature, bool isInc);
int zv_cont_filter(ZvContList contlist, int feature, double min, double max, bool isInvert);
int zv_cont_affine(ZvContour contSrc, ZvContour contDst, ZvMatrix mat);
int zv_cont_perspective(ZvContour contSrc, ZvContour contDst, ZvMatrix mat);

//feat
int zv_feat_houghLine(ZvImage img, ZvMatrix lines, double rho, double theta, int thresh, double minLinelen, double maxLineGap);
int zv_feat_houghCircle(ZvImage img, ZvMatrix circles, double minDist, double param1, double param2, double minR, double maxR);


#ifdef __cplusplus
}
#endif

#endif
