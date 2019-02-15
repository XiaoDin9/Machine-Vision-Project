/*************************************************************
该文件为自动生成文件，如果修改请注意备份，重新生成将被覆盖
////由zv_module_gen.py生成，需要zv_module_templ.py模块内的
////固定字符串定义和zv_module.h文件内的函数声明，声明需要符
////合特定格式
*************************************************************/

#include "zv_private.h"
#include "core\zv_core.h"
#include "basis\zv_basis.h"
#include "camera\zv_camera.h"
#include "file\zv_file.h"
#include "match\zv_match.h"
#include "measure\zv_meas.h"
#include "feature\zv_feature.h"
#include "system\zv_system.h"
#include "tools\zv_tools.h"


typedef void(*ZvTaskFun)(void *);

typedef struct _ZvTaskData
{
    ZvTaskFun fun;
    unsigned char paramBuf[8 * sizeof(double)];
}ZvTaskData;

static ZvTaskData s_zv_mod_taskData[ZV_SYS_THREAD_MAX] = { 0 };
bool s_zv_mod_isBlocking = false;


void zv_mod_registerRun(ZvTaskFun fun, void *param, int paramSize)
{
    int id = 0;

    if (paramSize > sizeof(s_zv_mod_taskData[0].paramBuf))
    {
        static volatile int* p = 0;
        *p = 0;
    }

    memset(s_zv_mod_taskData[id].paramBuf, 0, sizeof(s_zv_mod_taskData[id].paramBuf));
    memcpy(s_zv_mod_taskData[id].paramBuf, param, paramSize);
    s_zv_mod_taskData[id].fun = fun;
    if (s_zv_mod_isBlocking)
    {
        s_zv_mod_taskData[id].fun(s_zv_mod_taskData[id].paramBuf);
    }
}

void zv_mod_threadRun()
{
    int id = 0; // 获取线程ID
    if (NULL != s_zv_mod_taskData[id].fun && false == s_zv_mod_isBlocking)
    {
        s_zv_mod_taskData[id].fun(s_zv_mod_taskData[id].paramBuf);
    }
    s_zv_mod_taskData[id].fun = NULL;
}


//sys
int zv_sys_getParamInt(char *name, int *outValue);
int zv_sys_setParamInt(char *name, int value);
int zv_sys_getParamDouble(char *name, double *outValue);
int zv_sys_setParamDouble(char *name, double value);
int zv_sys_getParamString(char *name, char *value, int maxValLen);
int zv_sys_setParamString(char *name, char *value);
double zv_sys_getTimeUs();
double zv_sys_getTimeMs();
int64 zv_sys_getTickCount();
double zv_sys_getTickFreq();

//cam
int zv_cam_scan(char *type);
int zv_cam_count();
int zv_cam_getInfo(int scanId, char *name, char *value, int maxValLen);
int zv_cam_open(int camId, int scanId);
int zv_cam_status(int camId);
int zv_cam_close(int camId);
int zv_cam_payloadSize(int camId);
int zv_cam_grab(ZvImage img, int camId);
int zv_cam_getIO(int camId);
int zv_cam_setIO(int camId, int offset);
int zv_cam_getROI(int camId, int *x, int *y, int *width, int *height);
int zv_cam_setROI(int camId, int x, int y, int width, int height);
double zv_cam_getExposure(int camId);
int zv_cam_setExposure(int camId, double time);
int zv_cam_startGrabbing(int camId, int bufCount);
int zv_cam_isGrabbing(int camId, int *isGrabbing);
int zv_cam_retrieve(int camId, int bufId, ZvImage img);
int zv_cam_reset(int camId);
int zv_cam_getParam(int camId, char *name, char *value, int maxValLen);
int zv_cam_setParam(int camId, char *name, char *value);

//file
int zv_file_readImage(ZvImage img, char *name, int type);
int zv_file_writeImage(ZvImage img, char *name, int *param, int num);
int zv_file_readMatrix(ZvMatrix mat, char *name, int type);
int zv_file_writeMatrix(ZvMatrix mat, char *name, int type);

//img
int zv_img_width(ZvImage img);
int zv_img_height(ZvImage img);
int zv_img_channels(ZvImage img);
int zv_img_dataType(ZvImage img);
int zv_img_valueSize(ZvImage img);
int zv_img_genConst(ZvImage img, int width, int height, int type, int channel, double *value);
int zv_img_genData(ZvImage img, int width, int height, int type, int channel, double *data);
double zv_img_getValue(ZvImage img, int x, int y, int channel);
int zv_img_setValue(ZvImage img, int x, int y, int channel, double value);
int zv_img_getElement(ZvImage img, int x, int y, double *element);
int zv_img_setElement(ZvImage img, int x, int y, double *element);
int zv_img_getData(ZvImage img, void *buf, int size, bool isAlign);
int zv_img_setData(ZvImage img, void *buf);
int zv_img_getSub(ZvImage img, ZvImage sub, int x, int y, int width, int height);
int zv_img_setSub(ZvImage img, ZvImage sub, int x, int y);
int zv_img_convert(ZvImage src, ZvImage dst, int dstType, double mult, double add);
int zv_img_copy(ZvImage src, ZvImage dst);
int zv_img_split2(ZvImage src, ZvImage dst1, ZvImage dst2);
int zv_img_split3(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3);
int zv_img_split4(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3, ZvImage dst4);
int zv_img_merge2(ZvImage src1, ZvImage src2, ZvImage dst);
int zv_img_merge3(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage dst);
int zv_img_merge4(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage src4, ZvImage dst);

//mat
int zv_mat_rows(ZvMatrix mat);
int zv_mat_cols(ZvMatrix mat);
int zv_mat_genConst(ZvMatrix mat, int rows, int cols, double value);
int zv_mat_genEye(ZvMatrix mat, int size);
int zv_mat_genData(ZvMatrix mat, int rows, int cols, double *data);
double zv_mat_getValue(ZvMatrix mat, int row, int col);
int zv_mat_setValue(ZvMatrix mat, int row, int col, double value);
int zv_mat_getRow(ZvMatrix mat, int row, double *data);
int zv_mat_setRow(ZvMatrix mat, int row, double *data);
int zv_mat_getCol(ZvMatrix mat, int col, double * data);
int zv_mat_setCol(ZvMatrix mat, int col, double * data);
int zv_mat_getData(ZvMatrix mat, double *data);
int zv_mat_setData(ZvMatrix mat, double *data);
int zv_mat_getSub(ZvMatrix mat, ZvMatrix sub, int x, int y, int width, int height);
int zv_mat_setSub(ZvMatrix mat, ZvMatrix sub, int x, int y);
int zv_mat_copy(ZvMatrix src, ZvMatrix dst);

//cont
int zv_cont_count(ZvContList contList);
int zv_cont_getContour(ZvContList contList, int id, ZvContour cont);
int zv_cont_pointCount(ZvContour cont);
int zv_cont_getPoint(ZvContour cont, int id, double *pt);
int zv_cont_getPointsAll(ZvContour cont, double *pts);
int zv_cont_genContours(ZvImage img, ZvContList contList, bool isExter);
int zv_cont_genContoursEx(ZvImage img, ZvContList contList, int mode, int appro);
int zv_cont_toMatrix(ZvContour cont, ZvMatrix mat);
int zv_cont_fromMatrix(ZvContour cont, ZvMatrix mat);
double zv_cont_area(ZvContour cont, bool isOriented);
double zv_cont_length(ZvContour cont, bool isClosed);
int zv_cont_center(ZvContour cont, double *center);
int zv_cont_isConvex(ZvContour cont);
double zv_cont_circularity(ZvContour cont);
double zv_cont_compactness(ZvContour cont);
int zv_cont_smallestRect(ZvContour cont, int *rect);
int zv_cont_smallestRect2(ZvContour cont, double *rect2);
int zv_cont_smallestCircle(ZvContour cont, double *circle);
int zv_cont_convexHull(ZvContour cont, ZvMatrix hull);
int zv_cont_approxPoly(ZvContour cont, ZvMatrix poly, double epsilon, bool isClosed);
int zv_cont_sort(ZvContList contlist, int *sortedId, int type, bool isInc, bool isRowFirst);
int zv_cont_select(ZvContList contlist, ZvContList selected, char *feature, double min, double max);
double zv_cont_moments(ZvContour cont, int type, int orderX, int orderY);
int zv_cont_huMoments(ZvContour cont, double *hu);
int zv_cont_affine(ZvContour contSrc, ZvContour contDst, ZvMatrix mat);
int zv_cont_perspective(ZvContour contSrc, ZvContour contDst, ZvMatrix mat);

//arith
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
int zv_arith_atan2(ZvObject src1, ZvObject src2, ZvObject dst);
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
int zv_arith_phase(ZvObject x, ZvObject y, ZvObject angle);
int zv_arith_integral(ZvObject src, ZvObject dst, int dstType);
int zv_arith_integral2(ZvObject src, ZvObject dst, ZvObject dstSqrt, int dstType);
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
int zv_arith_sumRow(ZvObject src, ZvObject dst);
int zv_arith_sumCol(ZvObject src, ZvObject dst);
int zv_arith_mean(ZvObject src, double *mean);
int zv_arith_meanSdev(ZvObject src, double *mean, double *stdDev);
int zv_arith_minMaxLoc(ZvObject src, double *value, int *pos);
int zv_arith_hist(ZvImage img, ZvMatrix hist, int size, double low, double upper);
int zv_arith_histRgb(ZvImage img, ZvMatrix hist);

//ip
int zv_ip_mirror(ZvImage src, ZvImage dst, int type);
int zv_ip_rotate(ZvImage src, ZvImage dst, double angle, int interp);
int zv_ip_zoom(ZvImage src, ZvImage dst, double scaleW, double scaleH, int interp);
int zv_ip_resize(ZvImage src, ZvImage dst, int dstW, int dstH, int interp);
int zv_ip_affine(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border);
int zv_ip_perspective(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border);
double zv_ip_moments(ZvImage binImg, int type, int orderX, int orderY);
int zv_ip_rgbToGray(ZvImage rgb, ZvImage gray, bool isRgba);
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
int zv_ip_gaborKernel(ZvImage kernel, int width, int height, double sigma, double theta, double lambd, double gamma, double psi);
int zv_ip_derivKernel(ZvImage kernelX, ZvImage kernelY, int dX, int dY, int size);
int zv_ip_dct(ZvImage src, ZvImage dst);
int zv_ip_idct(ZvImage src, ZvImage dst);
int zv_ip_filter(ZvImage src, ZvImage kernel, ZvImage dst, int dstType, int anchorX, int anchorY, double delta, char * border);
int zv_ip_sepFilter(ZvImage src, ZvImage kernelX, ZvImage kernelY, ZvImage dst, int dstType, int anchorX, int anchorY, double delta, char *border);
int zv_ip_fft(ZvImage src, ZvImage dstRe, ZvImage dstIm);
int zv_ip_ifft(ZvImage srcRe, ZvImage srcIm, ZvImage dst);
int zv_ip_pyramid(ZvImage src, ZvImage *dst, int level, char *border);
int zv_ip_pyramidDown(ZvImage src, ZvImage dst, double factor, char *border);
int zv_ip_pyramidUp(ZvImage src, ZvImage dst, double factor, char *border);
int zv_ip_morphSe(ZvImage kernel, int shape, int sizeX, int sizeY, int anchorX, int anchorY);
int zv_ip_morphology(ZvImage src, ZvImage dst, ZvImage kernel, int op, int anchorX, int anchorY, int iter, char *border);
int zv_ip_label(ZvImage src, ZvImage label, int connectivity, int labelType);
int zv_ip_labelStat(ZvImage src, ZvImage label, ZvMatrix stat, ZvMatrix centroid, int connectivity, int labelType);
int zv_ip_threshold(ZvImage src, ZvImage dst, double thresh0, double thresh1, bool isInv);
int zv_ip_adpThreshold(ZvImage src, ZvImage thresh, ZvImage dst, double offset, bool isInv);
int zv_ip_autoThreshold(ZvImage src, ZvImage dst, bool isInv);

//match
int zv_match_fastTempl(ZvImage img, ZvImage templ, int *x, int *y, ZvImage mask);
int zv_match_bestTempl(ZvImage img, ZvImage templ, double minScore, double *x, double *y, double *score, int method, bool isSubPix);
int zv_match_multiTempl(ZvImage img, ZvImage templ, ZvMatrix matches, double minScore, int method, bool isSubPix);

//meas
int zv_meas_genRect(void * mr, int x, int y, int width, int height, int filterSize);
int zv_meas_genRect2(void *mr, double cx, double cy, double size1, double size2, double angle, int filterSize, int interp);
int zv_meas_genArc(void *mr, double cx, double cy, double r, double angleStart, double angleEnd, double rAnnulus, int filterSize, int interp);
int zv_meas_projection(ZvImage img, ZvMatrix proj, void *mr);
int zv_meas_pos(ZvImage img, ZvMatrix pts, void *mr, int thresh, int type, int select);
int zv_meas_pairs(ZvImage img, ZvMatrix pairs, void *mr, int thresh, int type, int select);
int zv_meas_lines(ZvImage img, ZvMatrix lines, void *mr, int thresh, int type, int select, int subNum, int subWidth);
int zv_meas_circle(ZvImage img, ZvMatrix circles, void *mr, int thresh, int type, int select, int subNum, int subWidth);

//feat
int zv_feat_houghLine(ZvImage img, ZvMatrix lines, double rho, double theta, int thresh, double minLinelen, double maxLineGap);
int zv_feat_houghCircle(ZvImage img, ZvMatrix circles, double minDist, double param1, double param2, double minR, double maxR);

//tk
int zv_tk_getRotScaleMat(ZvMatrix mat, double cx, double cy, double angle, double scale);
int zv_tk_getRigid(ZvMatrix mat, double *from, double *to);
int zv_tk_getRigidVector(ZvMatrix mat, double xFrom, double yFrom, double angleFrom, double xTo, double yTo, double angleTo);
int zv_tk_getSimilarity(ZvMatrix mat, double *from, double *to);
int zv_tk_getAffine(ZvMatrix mat, double *from, double *to);
int zv_tk_estimateSimilarity(ZvMatrix mat, double *from, double *to, int maxIters, int *inliersId);
int zv_tk_estimateAffine(ZvMatrix mat, double * from, double * to, int maxIters, int * inliersId, double thresh);
int zv_tk_affineTrans(ZvMatrix mat, double *from, double *to, int ptNum);
int zv_tk_getProjective(ZvMatrix mat, double *from, double *to);
int zv_tk_projectiveTrans2d(ZvMatrix mat, double *from, double *to, int num);
int zv_tk_projectiveTrans3d(ZvMatrix mat, double *from, double *to, int num);
double zv_tk_distPoints(double x1, double y1, double x2, double y2);
double zv_tk_distPointLine(double px, double py, double lineX1, double lineY1, double lineX2, double lineY2);
double zv_tk_distPointCont(ZvContour cont, double px, double py);
int zv_tk_rect2Vertex(double cx, double cy, double size1, double size2, double angle, double *pt);
bool zv_tk_intersectLines(double l1x1, double l1y1, double l1x2, double l1y2, double l2x1, double l2y1, double l2x2, double l2y2, double *sectX, double *sectY);
double zv_tk_angleLines(double line1X1, double line1Y1, double line1X2, double line1Y2, double line2X1, double line2Y1, double line2X2, double line2Y2);
double zv_tk_angleXAxis(double x1, double y1, double x2, double y2);
int zv_tk_fitLine(ZvMatrix pts, double *line);
int zv_tk_fitEllipse(ZvMatrix pts, double *ellipse);
int zv_tk_intersectRect2(double R1X, double R1Y, double R1Size1, double R1Size2, double R1Angle, double R2X, double R2Y, double R2Size1, double R2Size2, double R2angle, ZvMatrix pts);
int zv_tk_lineToParam(double x1, double y1, double x2, double y2, double *lineParam);
int zv_tk_lineFromParam(double cx, double cy, double angle, double len, double *line);
int zv_tk_fitLineEx(ZvMatrix pts, double *line, int method, double reps, double aeps);
int zv_tk_fitEllipseEx(ZvMatrix pts, double *ellipse, int method);

//dra
int zv_dra_color(int r, int g, int b);
int zv_dra_colorName(char *colorName);
int zv_dra_point(ZvImage img, int x, int y, int color);
int zv_dra_line(ZvImage img, int x1, int y1, int x2, int y2, int color);
int zv_dra_rect(ZvImage img, int x, int y, int w, int h, int color);
int zv_dra_rect2(ZvImage img, double cx, double cy, double size1, double size2, double angle, int color);
int zv_dra_circle(ZvImage img, int cx, int cy, int r, int color);
int zv_dra_ellipse(ZvImage img, int cx, int cy, int size1, int size2, double angle, int color);
int zv_dra_ellipseArc(ZvImage img, int cx, int cy, int size1, int size2, double angle, double angleStart, double angleEnd, int color);
int zv_dra_polygon(ZvImage img, ZvMatrix pts, bool isClosed, int color);
int zv_dra_contour(ZvImage img, ZvContour cont, int color);
int zv_dra_marker(ZvImage img, int x, int y, int type, int size, int color);
int zv_dra_text(ZvImage img, char * text, int x, int y, double scale, int color);
int zv_dra_mask(ZvImage img, ZvImage mask);


//sys system：参数、时间、日志、调试
int zv_sysGetParamInt(char *name)
{
    int value = 0;
#error 函数调用要求内部函数输出参数为最后一个参数，请检查确保无异常
    ZV_ERR_RUN(zv_sys_getParamInt(name, &value));
    return value;
}

void zv_sysSetParamInt(char *name, int value)
{
    ZV_ERR_RUN(zv_sys_setParamInt(name, value));
}

double zv_sysGetParamDouble(char *name)
{
    double value = 0;
#error 函数调用要求内部函数输出参数为最后一个参数，请检查确保无异常
    ZV_ERR_RUN(zv_sys_getParamDouble(name, &value));
    return value;
}

void zv_sysSetParamDouble(char *name, double value)
{
    ZV_ERR_RUN(zv_sys_setParamDouble(name, value));
}

void zv_sysGetParamString(char *name, char *value, int maxValLen)
{
    ZV_ERR_RUN(zv_sys_getParamString(name, value, maxValLen));
}

void zv_sysSetParamString(char *name, char *value)
{
    ZV_ERR_RUN(zv_sys_setParamString(name, value));
}

double zv_sysGetTimeUs()
{
    return zv_sys_getTimeUs();
}

double zv_sysGetTimeMs()
{
    return zv_sys_getTimeMs();
}

int64 zv_sysGetTickCount()
{
    return zv_sys_getTickCount();
}

double zv_sysGetTickFreq()
{
    return zv_sys_getTickFreq();
}


//cam
typedef struct
{
    char *type;
}ZvTPCamScan;
void zv_task_cam_scan(void *param)
{
    ZvTPCamScan *p = (ZvTPCamScan *)param;
    ZV_ERR_RUN(zv_cam_scan(p->type));
}
void zv_camScan(char *type)
{
    ZvTPCamScan taskParam_0 = {type};
    zv_mod_registerRun(zv_task_cam_scan, &taskParam_0, sizeof(taskParam_0));
}

int zv_camCount()
{
    return zv_cam_count();
}

typedef struct
{
    int scanId;
    char *name;
    char *value;
    int maxValLen;
}ZvTPCamGetInfo;
void zv_task_cam_getInfo(void *param)
{
    ZvTPCamGetInfo *p = (ZvTPCamGetInfo *)param;
    ZV_ERR_RUN(zv_cam_getInfo(p->scanId, p->name, p->value, p->maxValLen));
}
void zv_camGetInfo(int scanId, char *name, char *value, int maxValLen)
{
    ZvTPCamGetInfo taskParam_0 = {scanId, name, value, maxValLen};
    zv_mod_registerRun(zv_task_cam_getInfo, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    int scanId;
}ZvTPCamOpen;
void zv_task_cam_open(void *param)
{
    ZvTPCamOpen *p = (ZvTPCamOpen *)param;
    ZV_ERR_RUN(zv_cam_open(p->camId, p->scanId));
}
void zv_camOpen(int camId, int scanId)
{
    ZvTPCamOpen taskParam_0 = {camId, scanId};
    zv_mod_registerRun(zv_task_cam_open, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    int *status;
}ZvTPCamStatus;
void zv_task_cam_status(void *param)
{
    ZvTPCamStatus *p = (ZvTPCamStatus *)param;
    *p->status = zv_cam_status(p->camId);
}
void zv_camStatus(int camId, int *status)
{
    ZvTPCamStatus taskParam_0 = {camId, status};
    zv_mod_registerRun(zv_task_cam_status, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
}ZvTPCamClose;
void zv_task_cam_close(void *param)
{
    ZvTPCamClose *p = (ZvTPCamClose *)param;
    ZV_ERR_RUN(zv_cam_close(p->camId));
}
void zv_camClose(int camId)
{
    ZvTPCamClose taskParam_0 = {camId};
    zv_mod_registerRun(zv_task_cam_close, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    int *size;
}ZvTPCamPayloadSize;
void zv_task_cam_payloadSize(void *param)
{
    ZvTPCamPayloadSize *p = (ZvTPCamPayloadSize *)param;
    *p->size = zv_cam_payloadSize(p->camId);
}
void zv_camPayloadSize(int camId, int *size)
{
    ZvTPCamPayloadSize taskParam_0 = {camId, size};
    zv_mod_registerRun(zv_task_cam_payloadSize, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    int camId;
}ZvTPCamGrab;
void zv_task_cam_grab(void *param)
{
    ZvTPCamGrab *p = (ZvTPCamGrab *)param;
    ZV_ERR_RUN(zv_cam_grab(p->img, p->camId));
}
void zv_camGrab(ZvImage img, int camId)
{
    ZvTPCamGrab taskParam_0 = {img, camId};
    zv_mod_registerRun(zv_task_cam_grab, &taskParam_0, sizeof(taskParam_0));
}

int zv_camGetIO(int camId)
{
    return zv_cam_getIO(camId);
}

void zv_camSetIO(int camId, int offset)
{
    ZV_ERR_RUN(zv_cam_setIO(camId, offset));
}

typedef struct
{
    int camId;
    int *x;
    int *y;
    int *width;
    int *height;
}ZvTPCamGetROI;
void zv_task_cam_getROI(void *param)
{
    ZvTPCamGetROI *p = (ZvTPCamGetROI *)param;
    ZV_ERR_RUN(zv_cam_getROI(p->camId, p->x, p->y, p->width, p->height));
}
void zv_camGetROI(int camId, int *x, int *y, int *width, int *height)
{
    ZvTPCamGetROI taskParam_0 = {camId, x, y, width, height};
    zv_mod_registerRun(zv_task_cam_getROI, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    int x;
    int y;
    int width;
    int height;
}ZvTPCamSetROI;
void zv_task_cam_setROI(void *param)
{
    ZvTPCamSetROI *p = (ZvTPCamSetROI *)param;
    ZV_ERR_RUN(zv_cam_setROI(p->camId, p->x, p->y, p->width, p->height));
}
void zv_camSetROI(int camId, int x, int y, int width, int height)
{
    ZvTPCamSetROI taskParam_0 = {camId, x, y, width, height};
    zv_mod_registerRun(zv_task_cam_setROI, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    double *time;
}ZvTPCamGetExposure;
void zv_task_cam_getExposure(void *param)
{
    ZvTPCamGetExposure *p = (ZvTPCamGetExposure *)param;
    *p->time = zv_cam_getExposure(p->camId);
}
void zv_camGetExposure(int camId, double *time)
{
    ZvTPCamGetExposure taskParam_0 = {camId, time};
    zv_mod_registerRun(zv_task_cam_getExposure, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    double time;
}ZvTPCamSetExposure;
void zv_task_cam_setExposure(void *param)
{
    ZvTPCamSetExposure *p = (ZvTPCamSetExposure *)param;
    ZV_ERR_RUN(zv_cam_setExposure(p->camId, p->time));
}
void zv_camSetExposure(int camId, double time)
{
    ZvTPCamSetExposure taskParam_0 = {camId, time};
    zv_mod_registerRun(zv_task_cam_setExposure, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    int bufCount;
}ZvTPCamStartGrabbing;
void zv_task_cam_startGrabbing(void *param)
{
    ZvTPCamStartGrabbing *p = (ZvTPCamStartGrabbing *)param;
    ZV_ERR_RUN(zv_cam_startGrabbing(p->camId, p->bufCount));
}
void zv_camStartGrabbing(int camId, int bufCount)
{
    ZvTPCamStartGrabbing taskParam_0 = {camId, bufCount};
    zv_mod_registerRun(zv_task_cam_startGrabbing, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    int *isGrabbing;
}ZvTPCamIsGrabbing;
void zv_task_cam_isGrabbing(void *param)
{
    ZvTPCamIsGrabbing *p = (ZvTPCamIsGrabbing *)param;
    ZV_ERR_RUN(zv_cam_isGrabbing(p->camId, p->isGrabbing));
}
void zv_camIsGrabbing(int camId, int *isGrabbing)
{
    ZvTPCamIsGrabbing taskParam_0 = {camId, isGrabbing};
    zv_mod_registerRun(zv_task_cam_isGrabbing, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    int bufId;
    ZvImage img;
}ZvTPCamRetrieve;
void zv_task_cam_retrieve(void *param)
{
    ZvTPCamRetrieve *p = (ZvTPCamRetrieve *)param;
    ZV_ERR_RUN(zv_cam_retrieve(p->camId, p->bufId, p->img));
}
void zv_camRetrieve(int camId, int bufId, ZvImage img)
{
    ZvTPCamRetrieve taskParam_0 = {camId, bufId, img};
    zv_mod_registerRun(zv_task_cam_retrieve, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
}ZvTPCamReset;
void zv_task_cam_reset(void *param)
{
    ZvTPCamReset *p = (ZvTPCamReset *)param;
    ZV_ERR_RUN(zv_cam_reset(p->camId));
}
void zv_camReset(int camId)
{
    ZvTPCamReset taskParam_0 = {camId};
    zv_mod_registerRun(zv_task_cam_reset, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    char *name;
    char *value;
    int maxValLen;
}ZvTPCamGetParam;
void zv_task_cam_getParam(void *param)
{
    ZvTPCamGetParam *p = (ZvTPCamGetParam *)param;
    ZV_ERR_RUN(zv_cam_getParam(p->camId, p->name, p->value, p->maxValLen));
}
void zv_camGetParam(int camId, char *name, char *value, int maxValLen)
{
    ZvTPCamGetParam taskParam_0 = {camId, name, value, maxValLen};
    zv_mod_registerRun(zv_task_cam_getParam, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    int camId;
    char *name;
    char *value;
}ZvTPCamSetParam;
void zv_task_cam_setParam(void *param)
{
    ZvTPCamSetParam *p = (ZvTPCamSetParam *)param;
    ZV_ERR_RUN(zv_cam_setParam(p->camId, p->name, p->value));
}
void zv_camSetParam(int camId, char *name, char *value)
{
    ZvTPCamSetParam taskParam_0 = {camId, name, value};
    zv_mod_registerRun(zv_task_cam_setParam, &taskParam_0, sizeof(taskParam_0));
}


//file
typedef struct
{
    ZvImage img;
    char *name;
    int type;
}ZvTPFileReadImage;
void zv_task_file_readImage(void *param)
{
    ZvTPFileReadImage *p = (ZvTPFileReadImage *)param;
    ZV_ERR_RUN(zv_file_readImage(p->img, p->name, p->type));
}
void zv_fileReadImage(ZvImage img, char *name, int type)
{
    ZvTPFileReadImage taskParam_0 = {img, name, type};
    zv_mod_registerRun(zv_task_file_readImage, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    char *name;
    int *param;
    int num;
}ZvTPFileWriteImage;
void zv_task_file_writeImage(void *param)
{
    ZvTPFileWriteImage *p = (ZvTPFileWriteImage *)param;
    ZV_ERR_RUN(zv_file_writeImage(p->img, p->name, p->param, p->num));
}
void zv_fileWriteImage(ZvImage img, char *name, int *param, int num)
{
    ZvTPFileWriteImage taskParam_0 = {img, name, param, num};
    zv_mod_registerRun(zv_task_file_writeImage, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    char *name;
    int type;
}ZvTPFileReadMatrix;
void zv_task_file_readMatrix(void *param)
{
    ZvTPFileReadMatrix *p = (ZvTPFileReadMatrix *)param;
    ZV_ERR_RUN(zv_file_readMatrix(p->mat, p->name, p->type));
}
void zv_fileReadMatrix(ZvMatrix mat, char *name, int type)
{
    ZvTPFileReadMatrix taskParam_0 = {mat, name, type};
    zv_mod_registerRun(zv_task_file_readMatrix, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    char *name;
    int type;
}ZvTPFileWriteMatrix;
void zv_task_file_writeMatrix(void *param)
{
    ZvTPFileWriteMatrix *p = (ZvTPFileWriteMatrix *)param;
    ZV_ERR_RUN(zv_file_writeMatrix(p->mat, p->name, p->type));
}
void zv_fileWriteMatrix(ZvMatrix mat, char *name, int type)
{
    ZvTPFileWriteMatrix taskParam_0 = {mat, name, type};
    zv_mod_registerRun(zv_task_file_writeMatrix, &taskParam_0, sizeof(taskParam_0));
}


//img    core/zv_image.cpp
int zv_imgWidth(ZvImage img)
{
    return zv_img_width(img);
}

int zv_imgHeight(ZvImage img)
{
    return zv_img_height(img);
}

int zv_imgChannels(ZvImage img)
{
    return zv_img_channels(img);
}

int zv_imgDataType(ZvImage img)
{
    return zv_img_dataType(img);
}

int zv_imgValueSize(ZvImage img)
{
    return zv_img_valueSize(img);
}

typedef struct
{
    ZvImage img;
    int width;
    int height;
    int type;
    int channel;
    double *value;
}ZvTPImgGenConst;
void zv_task_img_genConst(void *param)
{
    ZvTPImgGenConst *p = (ZvTPImgGenConst *)param;
    ZV_ERR_RUN(zv_img_genConst(p->img, p->width, p->height, p->type, p->channel, p->value));
}
void zv_imgGenConst(ZvImage img, int width, int height, int type, int channel, double *value)
{
    ZvTPImgGenConst taskParam_0 = {img, width, height, type, channel, value};
    zv_mod_registerRun(zv_task_img_genConst, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    int width;
    int height;
    int type;
    int channel;
    double *data;
}ZvTPImgGenData;
void zv_task_img_genData(void *param)
{
    ZvTPImgGenData *p = (ZvTPImgGenData *)param;
    ZV_ERR_RUN(zv_img_genData(p->img, p->width, p->height, p->type, p->channel, p->data));
}
void zv_imgGenData(ZvImage img, int width, int height, int type, int channel, double *data)
{
    ZvTPImgGenData taskParam_0 = {img, width, height, type, channel, data};
    zv_mod_registerRun(zv_task_img_genData, &taskParam_0, sizeof(taskParam_0));
}

double zv_imgGetValue(ZvImage img, int x, int y, int channel)
{
    return zv_img_getValue(img, x, y, channel);
}

void zv_imgSetValue(ZvImage img, int x, int y, int channel, double value)
{
    ZV_ERR_RUN(zv_img_setValue(img, x, y, channel, value));
}

void zv_imgGetElement(ZvImage img, int x, int y, double *element)
{
    ZV_ERR_RUN(zv_img_getElement(img, x, y, element));
}

void zv_imgSetElement(ZvImage img, int x, int y, double *element)
{
    ZV_ERR_RUN(zv_img_setElement(img, x, y, element));
}

typedef struct
{
    ZvImage img;
    void *buf;
    int size;
    bool isAlign;
}ZvTPImgGetData;
void zv_task_img_getData(void *param)
{
    ZvTPImgGetData *p = (ZvTPImgGetData *)param;
    ZV_ERR_RUN(zv_img_getData(p->img, p->buf, p->size, p->isAlign));
}
void zv_imgGetData(ZvImage img, void *buf, int size, bool isAlign)
{
    ZvTPImgGetData taskParam_0 = {img, buf, size, isAlign};
    zv_mod_registerRun(zv_task_img_getData, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    void *buf;
}ZvTPImgSetData;
void zv_task_img_setData(void *param)
{
    ZvTPImgSetData *p = (ZvTPImgSetData *)param;
    ZV_ERR_RUN(zv_img_setData(p->img, p->buf));
}
void zv_imgSetData(ZvImage img, void *buf)
{
    ZvTPImgSetData taskParam_0 = {img, buf};
    zv_mod_registerRun(zv_task_img_setData, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvImage sub;
    int x;
    int y;
    int width;
    int height;
}ZvTPImgGetSub;
void zv_task_img_getSub(void *param)
{
    ZvTPImgGetSub *p = (ZvTPImgGetSub *)param;
    ZV_ERR_RUN(zv_img_getSub(p->img, p->sub, p->x, p->y, p->width, p->height));
}
void zv_imgGetSub(ZvImage img, ZvImage sub, int x, int y, int width, int height)
{
    ZvTPImgGetSub taskParam_0 = {img, sub, x, y, width, height};
    zv_mod_registerRun(zv_task_img_getSub, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvImage sub;
    int x;
    int y;
}ZvTPImgSetSub;
void zv_task_img_setSub(void *param)
{
    ZvTPImgSetSub *p = (ZvTPImgSetSub *)param;
    ZV_ERR_RUN(zv_img_setSub(p->img, p->sub, p->x, p->y));
}
void zv_imgSetSub(ZvImage img, ZvImage sub, int x, int y)
{
    ZvTPImgSetSub taskParam_0 = {img, sub, x, y};
    zv_mod_registerRun(zv_task_img_setSub, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int dstType;
    double mult;
    double add;
}ZvTPImgConvert;
void zv_task_img_convert(void *param)
{
    ZvTPImgConvert *p = (ZvTPImgConvert *)param;
    ZV_ERR_RUN(zv_img_convert(p->src, p->dst, p->dstType, p->mult, p->add));
}
void zv_imgConvert(ZvImage src, ZvImage dst, int dstType, double mult, double add)
{
    ZvTPImgConvert taskParam_0 = {src, dst, dstType, mult, add};
    zv_mod_registerRun(zv_task_img_convert, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
}ZvTPImgCopy;
void zv_task_img_copy(void *param)
{
    ZvTPImgCopy *p = (ZvTPImgCopy *)param;
    ZV_ERR_RUN(zv_img_copy(p->src, p->dst));
}
void zv_imgCopy(ZvImage src, ZvImage dst)
{
    ZvTPImgCopy taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_img_copy, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst1;
    ZvImage dst2;
}ZvTPImgSplit2;
void zv_task_img_split2(void *param)
{
    ZvTPImgSplit2 *p = (ZvTPImgSplit2 *)param;
    ZV_ERR_RUN(zv_img_split2(p->src, p->dst1, p->dst2));
}
void zv_imgSplit2(ZvImage src, ZvImage dst1, ZvImage dst2)
{
    ZvTPImgSplit2 taskParam_0 = {src, dst1, dst2};
    zv_mod_registerRun(zv_task_img_split2, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst1;
    ZvImage dst2;
    ZvImage dst3;
}ZvTPImgSplit3;
void zv_task_img_split3(void *param)
{
    ZvTPImgSplit3 *p = (ZvTPImgSplit3 *)param;
    ZV_ERR_RUN(zv_img_split3(p->src, p->dst1, p->dst2, p->dst3));
}
void zv_imgSplit3(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3)
{
    ZvTPImgSplit3 taskParam_0 = {src, dst1, dst2, dst3};
    zv_mod_registerRun(zv_task_img_split3, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst1;
    ZvImage dst2;
    ZvImage dst3;
    ZvImage dst4;
}ZvTPImgSplit4;
void zv_task_img_split4(void *param)
{
    ZvTPImgSplit4 *p = (ZvTPImgSplit4 *)param;
    ZV_ERR_RUN(zv_img_split4(p->src, p->dst1, p->dst2, p->dst3, p->dst4));
}
void zv_imgSplit4(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3, ZvImage dst4)
{
    ZvTPImgSplit4 taskParam_0 = {src, dst1, dst2, dst3, dst4};
    zv_mod_registerRun(zv_task_img_split4, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage dst;
}ZvTPImgMerge2;
void zv_task_img_merge2(void *param)
{
    ZvTPImgMerge2 *p = (ZvTPImgMerge2 *)param;
    ZV_ERR_RUN(zv_img_merge2(p->src1, p->src2, p->dst));
}
void zv_imgMerge2(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZvTPImgMerge2 taskParam_0 = {src1, src2, dst};
    zv_mod_registerRun(zv_task_img_merge2, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage src3;
    ZvImage dst;
}ZvTPImgMerge3;
void zv_task_img_merge3(void *param)
{
    ZvTPImgMerge3 *p = (ZvTPImgMerge3 *)param;
    ZV_ERR_RUN(zv_img_merge3(p->src1, p->src2, p->src3, p->dst));
}
void zv_imgMerge3(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage dst)
{
    ZvTPImgMerge3 taskParam_0 = {src1, src2, src3, dst};
    zv_mod_registerRun(zv_task_img_merge3, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage src3;
    ZvImage src4;
    ZvImage dst;
}ZvTPImgMerge4;
void zv_task_img_merge4(void *param)
{
    ZvTPImgMerge4 *p = (ZvTPImgMerge4 *)param;
    ZV_ERR_RUN(zv_img_merge4(p->src1, p->src2, p->src3, p->src4, p->dst));
}
void zv_imgMerge4(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage src4, ZvImage dst)
{
    ZvTPImgMerge4 taskParam_0 = {src1, src2, src3, src4, dst};
    zv_mod_registerRun(zv_task_img_merge4, &taskParam_0, sizeof(taskParam_0));
}


//mat    core/zv_matrix.cpp
int zv_matRows(ZvMatrix mat)
{
    return zv_mat_rows(mat);
}

int zv_matCols(ZvMatrix mat)
{
    return zv_mat_cols(mat);
}

typedef struct
{
    ZvMatrix mat;
    int rows;
    int cols;
    double value;
}ZvTPMatGenConst;
void zv_task_mat_genConst(void *param)
{
    ZvTPMatGenConst *p = (ZvTPMatGenConst *)param;
    ZV_ERR_RUN(zv_mat_genConst(p->mat, p->rows, p->cols, p->value));
}
void zv_matGenConst(ZvMatrix mat, int rows, int cols, double value)
{
    ZvTPMatGenConst taskParam_0 = {mat, rows, cols, value};
    zv_mod_registerRun(zv_task_mat_genConst, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    int size;
}ZvTPMatGenEye;
void zv_task_mat_genEye(void *param)
{
    ZvTPMatGenEye *p = (ZvTPMatGenEye *)param;
    ZV_ERR_RUN(zv_mat_genEye(p->mat, p->size));
}
void zv_matGenEye(ZvMatrix mat, int size)
{
    ZvTPMatGenEye taskParam_0 = {mat, size};
    zv_mod_registerRun(zv_task_mat_genEye, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    int rows;
    int cols;
    double *data;
}ZvTPMatGenData;
void zv_task_mat_genData(void *param)
{
    ZvTPMatGenData *p = (ZvTPMatGenData *)param;
    ZV_ERR_RUN(zv_mat_genData(p->mat, p->rows, p->cols, p->data));
}
void zv_matGenData(ZvMatrix mat, int rows, int cols, double *data)
{
    ZvTPMatGenData taskParam_0 = {mat, rows, cols, data};
    zv_mod_registerRun(zv_task_mat_genData, &taskParam_0, sizeof(taskParam_0));
}

double zv_matGetValue(ZvMatrix mat, int row, int col)
{
    return zv_mat_getValue(mat, row, col);
}

void zv_matSetValue(ZvMatrix mat, int row, int col, double value)
{
    ZV_ERR_RUN(zv_mat_setValue(mat, row, col, value));
}

typedef struct
{
    ZvMatrix mat;
    int row;
    double *data;
}ZvTPMatGetRow;
void zv_task_mat_getRow(void *param)
{
    ZvTPMatGetRow *p = (ZvTPMatGetRow *)param;
    ZV_ERR_RUN(zv_mat_getRow(p->mat, p->row, p->data));
}
void zv_matGetRow(ZvMatrix mat, int row, double *data)
{
    ZvTPMatGetRow taskParam_0 = {mat, row, data};
    zv_mod_registerRun(zv_task_mat_getRow, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    int row;
    double *data;
}ZvTPMatSetRow;
void zv_task_mat_setRow(void *param)
{
    ZvTPMatSetRow *p = (ZvTPMatSetRow *)param;
    ZV_ERR_RUN(zv_mat_setRow(p->mat, p->row, p->data));
}
void zv_matSetRow(ZvMatrix mat, int row, double *data)
{
    ZvTPMatSetRow taskParam_0 = {mat, row, data};
    zv_mod_registerRun(zv_task_mat_setRow, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    int col;
    double * data;
}ZvTPMatGetCol;
void zv_task_mat_getCol(void *param)
{
    ZvTPMatGetCol *p = (ZvTPMatGetCol *)param;
    ZV_ERR_RUN(zv_mat_getCol(p->mat, p->col, p->data));
}
void zv_matGetCol(ZvMatrix mat, int col, double * data)
{
    ZvTPMatGetCol taskParam_0 = {mat, col, data};
    zv_mod_registerRun(zv_task_mat_getCol, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    int col;
    double * data;
}ZvTPMatSetCol;
void zv_task_mat_setCol(void *param)
{
    ZvTPMatSetCol *p = (ZvTPMatSetCol *)param;
    ZV_ERR_RUN(zv_mat_setCol(p->mat, p->col, p->data));
}
void zv_matSetCol(ZvMatrix mat, int col, double * data)
{
    ZvTPMatSetCol taskParam_0 = {mat, col, data};
    zv_mod_registerRun(zv_task_mat_setCol, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *data;
}ZvTPMatGetData;
void zv_task_mat_getData(void *param)
{
    ZvTPMatGetData *p = (ZvTPMatGetData *)param;
    ZV_ERR_RUN(zv_mat_getData(p->mat, p->data));
}
void zv_matGetData(ZvMatrix mat, double *data)
{
    ZvTPMatGetData taskParam_0 = {mat, data};
    zv_mod_registerRun(zv_task_mat_getData, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *data;
}ZvTPMatSetData;
void zv_task_mat_setData(void *param)
{
    ZvTPMatSetData *p = (ZvTPMatSetData *)param;
    ZV_ERR_RUN(zv_mat_setData(p->mat, p->data));
}
void zv_matSetData(ZvMatrix mat, double *data)
{
    ZvTPMatSetData taskParam_0 = {mat, data};
    zv_mod_registerRun(zv_task_mat_setData, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    ZvMatrix sub;
    int x;
    int y;
    int width;
    int height;
}ZvTPMatGetSub;
void zv_task_mat_getSub(void *param)
{
    ZvTPMatGetSub *p = (ZvTPMatGetSub *)param;
    ZV_ERR_RUN(zv_mat_getSub(p->mat, p->sub, p->x, p->y, p->width, p->height));
}
void zv_matGetSub(ZvMatrix mat, ZvMatrix sub, int x, int y, int width, int height)
{
    ZvTPMatGetSub taskParam_0 = {mat, sub, x, y, width, height};
    zv_mod_registerRun(zv_task_mat_getSub, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    ZvMatrix sub;
    int x;
    int y;
}ZvTPMatSetSub;
void zv_task_mat_setSub(void *param)
{
    ZvTPMatSetSub *p = (ZvTPMatSetSub *)param;
    ZV_ERR_RUN(zv_mat_setSub(p->mat, p->sub, p->x, p->y));
}
void zv_matSetSub(ZvMatrix mat, ZvMatrix sub, int x, int y)
{
    ZvTPMatSetSub taskParam_0 = {mat, sub, x, y};
    zv_mod_registerRun(zv_task_mat_setSub, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix src;
    ZvMatrix dst;
}ZvTPMatCopy;
void zv_task_mat_copy(void *param)
{
    ZvTPMatCopy *p = (ZvTPMatCopy *)param;
    ZV_ERR_RUN(zv_mat_copy(p->src, p->dst));
}
void zv_matCopy(ZvMatrix src, ZvMatrix dst)
{
    ZvTPMatCopy taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_mat_copy, &taskParam_0, sizeof(taskParam_0));
}


//cont   core/zv_contour.cpp
int zv_contCount(ZvContList contList)
{
    return zv_cont_count(contList);
}

typedef struct
{
    ZvContList contList;
    int id;
    ZvContour cont;
}ZvTPContGetContour;
void zv_task_cont_getContour(void *param)
{
    ZvTPContGetContour *p = (ZvTPContGetContour *)param;
    ZV_ERR_RUN(zv_cont_getContour(p->contList, p->id, p->cont));
}
void zv_contGetContour(ZvContList contList, int id, ZvContour cont)
{
    ZvTPContGetContour taskParam_0 = {contList, id, cont};
    zv_mod_registerRun(zv_task_cont_getContour, &taskParam_0, sizeof(taskParam_0));
}

int zv_contPointCount(ZvContour cont)
{
    return zv_cont_pointCount(cont);
}

void zv_contGetPoint(ZvContour cont, int id, double *pt)
{
    ZV_ERR_RUN(zv_cont_getPoint(cont, id, pt));
}

typedef struct
{
    ZvContour cont;
    double *pts;
}ZvTPContGetPointsAll;
void zv_task_cont_getPointsAll(void *param)
{
    ZvTPContGetPointsAll *p = (ZvTPContGetPointsAll *)param;
    ZV_ERR_RUN(zv_cont_getPointsAll(p->cont, p->pts));
}
void zv_contGetPointsAll(ZvContour cont, double *pts)
{
    ZvTPContGetPointsAll taskParam_0 = {cont, pts};
    zv_mod_registerRun(zv_task_cont_getPointsAll, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvContList contList;
    bool isExter;
}ZvTPContGenContours;
void zv_task_cont_genContours(void *param)
{
    ZvTPContGenContours *p = (ZvTPContGenContours *)param;
    ZV_ERR_RUN(zv_cont_genContours(p->img, p->contList, p->isExter));
}
void zv_contGenContours(ZvImage img, ZvContList contList, bool isExter)
{
    ZvTPContGenContours taskParam_0 = {img, contList, isExter};
    zv_mod_registerRun(zv_task_cont_genContours, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvContList contList;
    int mode;
    int appro;
}ZvTPContGenContoursEx;
void zv_task_cont_genContoursEx(void *param)
{
    ZvTPContGenContoursEx *p = (ZvTPContGenContoursEx *)param;
    ZV_ERR_RUN(zv_cont_genContoursEx(p->img, p->contList, p->mode, p->appro));
}
void zv_contGenContoursEx(ZvImage img, ZvContList contList, int mode, int appro)
{
    ZvTPContGenContoursEx taskParam_0 = {img, contList, mode, appro};
    zv_mod_registerRun(zv_task_cont_genContoursEx, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    ZvMatrix mat;
}ZvTPContToMatrix;
void zv_task_cont_toMatrix(void *param)
{
    ZvTPContToMatrix *p = (ZvTPContToMatrix *)param;
    ZV_ERR_RUN(zv_cont_toMatrix(p->cont, p->mat));
}
void zv_contToMatrix(ZvContour cont, ZvMatrix mat)
{
    ZvTPContToMatrix taskParam_0 = {cont, mat};
    zv_mod_registerRun(zv_task_cont_toMatrix, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    ZvMatrix mat;
}ZvTPContFromMatrix;
void zv_task_cont_fromMatrix(void *param)
{
    ZvTPContFromMatrix *p = (ZvTPContFromMatrix *)param;
    ZV_ERR_RUN(zv_cont_fromMatrix(p->cont, p->mat));
}
void zv_contFromMatrix(ZvContour cont, ZvMatrix mat)
{
    ZvTPContFromMatrix taskParam_0 = {cont, mat};
    zv_mod_registerRun(zv_task_cont_fromMatrix, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    bool isOriented;
    double *area;
}ZvTPContArea;
void zv_task_cont_area(void *param)
{
    ZvTPContArea *p = (ZvTPContArea *)param;
    *p->area = zv_cont_area(p->cont, p->isOriented);
}
void zv_contArea(ZvContour cont, bool isOriented, double *area)
{
    ZvTPContArea taskParam_0 = {cont, isOriented, area};
    zv_mod_registerRun(zv_task_cont_area, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    bool isClosed;
    double *len;
}ZvTPContLength;
void zv_task_cont_length(void *param)
{
    ZvTPContLength *p = (ZvTPContLength *)param;
    *p->len = zv_cont_length(p->cont, p->isClosed);
}
void zv_contLength(ZvContour cont, bool isClosed, double *len)
{
    ZvTPContLength taskParam_0 = {cont, isClosed, len};
    zv_mod_registerRun(zv_task_cont_length, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    double *center;
}ZvTPContCenter;
void zv_task_cont_center(void *param)
{
    ZvTPContCenter *p = (ZvTPContCenter *)param;
    ZV_ERR_RUN(zv_cont_center(p->cont, p->center));
}
void zv_contCenter(ZvContour cont, double *center)
{
    ZvTPContCenter taskParam_0 = {cont, center};
    zv_mod_registerRun(zv_task_cont_center, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    int *isConvex;
}ZvTPContIsConvex;
void zv_task_cont_isConvex(void *param)
{
    ZvTPContIsConvex *p = (ZvTPContIsConvex *)param;
    *p->isConvex = zv_cont_isConvex(p->cont);
}
void zv_contIsConvex(ZvContour cont, int *isConvex)
{
    ZvTPContIsConvex taskParam_0 = {cont, isConvex};
    zv_mod_registerRun(zv_task_cont_isConvex, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    double *value;
}ZvTPContCircularity;
void zv_task_cont_circularity(void *param)
{
    ZvTPContCircularity *p = (ZvTPContCircularity *)param;
    *p->value = zv_cont_circularity(p->cont);
}
void zv_contCircularity(ZvContour cont, double *value)
{
    ZvTPContCircularity taskParam_0 = {cont, value};
    zv_mod_registerRun(zv_task_cont_circularity, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    double *value;
}ZvTPContCompactness;
void zv_task_cont_compactness(void *param)
{
    ZvTPContCompactness *p = (ZvTPContCompactness *)param;
    *p->value = zv_cont_compactness(p->cont);
}
void zv_contCompactness(ZvContour cont, double *value)
{
    ZvTPContCompactness taskParam_0 = {cont, value};
    zv_mod_registerRun(zv_task_cont_compactness, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    int *rect;
}ZvTPContSmallestRect;
void zv_task_cont_smallestRect(void *param)
{
    ZvTPContSmallestRect *p = (ZvTPContSmallestRect *)param;
    ZV_ERR_RUN(zv_cont_smallestRect(p->cont, p->rect));
}
void zv_contSmallestRect(ZvContour cont, int *rect)
{
    ZvTPContSmallestRect taskParam_0 = {cont, rect};
    zv_mod_registerRun(zv_task_cont_smallestRect, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    double *rect2;
}ZvTPContSmallestRect2;
void zv_task_cont_smallestRect2(void *param)
{
    ZvTPContSmallestRect2 *p = (ZvTPContSmallestRect2 *)param;
    ZV_ERR_RUN(zv_cont_smallestRect2(p->cont, p->rect2));
}
void zv_contSmallestRect2(ZvContour cont, double *rect2)
{
    ZvTPContSmallestRect2 taskParam_0 = {cont, rect2};
    zv_mod_registerRun(zv_task_cont_smallestRect2, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    double *circle;
}ZvTPContSmallestCircle;
void zv_task_cont_smallestCircle(void *param)
{
    ZvTPContSmallestCircle *p = (ZvTPContSmallestCircle *)param;
    ZV_ERR_RUN(zv_cont_smallestCircle(p->cont, p->circle));
}
void zv_contSmallestCircle(ZvContour cont, double *circle)
{
    ZvTPContSmallestCircle taskParam_0 = {cont, circle};
    zv_mod_registerRun(zv_task_cont_smallestCircle, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    ZvMatrix hull;
}ZvTPContConvexHull;
void zv_task_cont_convexHull(void *param)
{
    ZvTPContConvexHull *p = (ZvTPContConvexHull *)param;
    ZV_ERR_RUN(zv_cont_convexHull(p->cont, p->hull));
}
void zv_contConvexHull(ZvContour cont, ZvMatrix hull)
{
    ZvTPContConvexHull taskParam_0 = {cont, hull};
    zv_mod_registerRun(zv_task_cont_convexHull, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    ZvMatrix poly;
    double epsilon;
    bool isClosed;
}ZvTPContApproxPoly;
void zv_task_cont_approxPoly(void *param)
{
    ZvTPContApproxPoly *p = (ZvTPContApproxPoly *)param;
    ZV_ERR_RUN(zv_cont_approxPoly(p->cont, p->poly, p->epsilon, p->isClosed));
}
void zv_contApproxPoly(ZvContour cont, ZvMatrix poly, double epsilon, bool isClosed)
{
    ZvTPContApproxPoly taskParam_0 = {cont, poly, epsilon, isClosed};
    zv_mod_registerRun(zv_task_cont_approxPoly, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContList contlist;
    int *sortedId;
    int type;
    bool isInc;
    bool isRowFirst;
}ZvTPContSort;
void zv_task_cont_sort(void *param)
{
    ZvTPContSort *p = (ZvTPContSort *)param;
    ZV_ERR_RUN(zv_cont_sort(p->contlist, p->sortedId, p->type, p->isInc, p->isRowFirst));
}
void zv_contSort(ZvContList contlist, int *sortedId, int type, bool isInc, bool isRowFirst)
{
    ZvTPContSort taskParam_0 = {contlist, sortedId, type, isInc, isRowFirst};
    zv_mod_registerRun(zv_task_cont_sort, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContList contlist;
    ZvContList selected;
    char *feature;
    double min;
    double max;
}ZvTPContSelect;
void zv_task_cont_select(void *param)
{
    ZvTPContSelect *p = (ZvTPContSelect *)param;
    ZV_ERR_RUN(zv_cont_select(p->contlist, p->selected, p->feature, p->min, p->max));
}
void zv_contSelect(ZvContList contlist, ZvContList selected, char *feature, double min, double max)
{
    ZvTPContSelect taskParam_0 = {contlist, selected, feature, min, max};
    zv_mod_registerRun(zv_task_cont_select, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    int type;
    int orderX;
    int orderY;
    double *m;
}ZvTPContMoments;
void zv_task_cont_moments(void *param)
{
    ZvTPContMoments *p = (ZvTPContMoments *)param;
    *p->m = zv_cont_moments(p->cont, p->type, p->orderX, p->orderY);
}
void zv_contMoments(ZvContour cont, int type, int orderX, int orderY, double *m)
{
    ZvTPContMoments taskParam_0 = {cont, type, orderX, orderY, m};
    zv_mod_registerRun(zv_task_cont_moments, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour cont;
    double *hu;
}ZvTPContHuMoments;
void zv_task_cont_huMoments(void *param)
{
    ZvTPContHuMoments *p = (ZvTPContHuMoments *)param;
    ZV_ERR_RUN(zv_cont_huMoments(p->cont, p->hu));
}
void zv_contHuMoments(ZvContour cont, double *hu)
{
    ZvTPContHuMoments taskParam_0 = {cont, hu};
    zv_mod_registerRun(zv_task_cont_huMoments, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour contSrc;
    ZvContour contDst;
    ZvMatrix mat;
}ZvTPContAffine;
void zv_task_cont_affine(void *param)
{
    ZvTPContAffine *p = (ZvTPContAffine *)param;
    ZV_ERR_RUN(zv_cont_affine(p->contSrc, p->contDst, p->mat));
}
void zv_contAffine(ZvContour contSrc, ZvContour contDst, ZvMatrix mat)
{
    ZvTPContAffine taskParam_0 = {contSrc, contDst, mat};
    zv_mod_registerRun(zv_task_cont_affine, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvContour contSrc;
    ZvContour contDst;
    ZvMatrix mat;
}ZvTPContPerspective;
void zv_task_cont_perspective(void *param)
{
    ZvTPContPerspective *p = (ZvTPContPerspective *)param;
    ZV_ERR_RUN(zv_cont_perspective(p->contSrc, p->contDst, p->mat));
}
void zv_contPerspective(ZvContour contSrc, ZvContour contDst, ZvMatrix mat)
{
    ZvTPContPerspective taskParam_0 = {contSrc, contDst, mat};
    zv_mod_registerRun(zv_task_cont_perspective, &taskParam_0, sizeof(taskParam_0));
}


//arith  basic/   zv_arithmetic.cpp    zv_stat.cpp'
//zv_arithmetic.cpp  代数（矩阵图像的四则运算、逆矩阵、逐点函数运算、逻辑、比较、矩阵运算、LUT）
//zv_stat.cpp  统计（直方图、均值方差、）
typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithAbs;
void zv_task_arith_abs(void *param)
{
    ZvTPArithAbs *p = (ZvTPArithAbs *)param;
    ZV_ERR_RUN(zv_arith_abs(p->src, p->dst));
}
void zv_arithAbs(ZvObject src, ZvObject dst)
{
    ZvTPArithAbs taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_abs, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
}ZvTPArithAbsDiff;
void zv_task_arith_absDiff(void *param)
{
    ZvTPArithAbsDiff *p = (ZvTPArithAbsDiff *)param;
    ZV_ERR_RUN(zv_arith_absDiff(p->src1, p->src2, p->dst, p->mult));
}
void zv_arithAbsDiff(ZvObject src1, ZvObject src2, ZvObject dst, double mult)
{
    ZvTPArithAbsDiff taskParam_0 = {src1, src2, dst, mult};
    zv_mod_registerRun(zv_task_arith_absDiff, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithAdd;
void zv_task_arith_add(void *param)
{
    ZvTPArithAdd *p = (ZvTPArithAdd *)param;
    ZV_ERR_RUN(zv_arith_add(p->src1, p->src2, p->dst, p->mult, p->add));
}
void zv_arithAdd(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add)
{
    ZvTPArithAdd taskParam_0 = {src1, src2, dst, mult, add};
    zv_mod_registerRun(zv_task_arith_add, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithSub;
void zv_task_arith_sub(void *param)
{
    ZvTPArithSub *p = (ZvTPArithSub *)param;
    ZV_ERR_RUN(zv_arith_sub(p->src1, p->src2, p->dst, p->mult, p->add));
}
void zv_arithSub(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add)
{
    ZvTPArithSub taskParam_0 = {src1, src2, dst, mult, add};
    zv_mod_registerRun(zv_task_arith_sub, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithMul;
void zv_task_arith_mul(void *param)
{
    ZvTPArithMul *p = (ZvTPArithMul *)param;
    ZV_ERR_RUN(zv_arith_mul(p->src1, p->src2, p->dst, p->mult, p->add));
}
void zv_arithMul(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add)
{
    ZvTPArithMul taskParam_0 = {src1, src2, dst, mult, add};
    zv_mod_registerRun(zv_task_arith_mul, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithDiv;
void zv_task_arith_div(void *param)
{
    ZvTPArithDiv *p = (ZvTPArithDiv *)param;
    ZV_ERR_RUN(zv_arith_div(p->src1, p->src2, p->dst, p->mult, p->add));
}
void zv_arithDiv(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add)
{
    ZvTPArithDiv taskParam_0 = {src1, src2, dst, mult, add};
    zv_mod_registerRun(zv_task_arith_div, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
    double mult;
    double add;
}ZvTPArithScale;
void zv_task_arith_scale(void *param)
{
    ZvTPArithScale *p = (ZvTPArithScale *)param;
    ZV_ERR_RUN(zv_arith_scale(p->src, p->dst, p->mult, p->add));
}
void zv_arithScale(ZvObject src, ZvObject dst, double mult, double add)
{
    ZvTPArithScale taskParam_0 = {src, dst, mult, add};
    zv_mod_registerRun(zv_task_arith_scale, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
    double weight1;
    double weight2;
    double add;
}ZvTPArithAddWeighted;
void zv_task_arith_addWeighted(void *param)
{
    ZvTPArithAddWeighted *p = (ZvTPArithAddWeighted *)param;
    ZV_ERR_RUN(zv_arith_addWeighted(p->src1, p->src2, p->dst, p->weight1, p->weight2, p->add));
}
void zv_arithAddWeighted(ZvObject src1, ZvObject src2, ZvObject dst, double weight1, double weight2, double add)
{
    ZvTPArithAddWeighted taskParam_0 = {src1, src2, dst, weight1, weight2, add};
    zv_mod_registerRun(zv_task_arith_addWeighted, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithSin;
void zv_task_arith_sin(void *param)
{
    ZvTPArithSin *p = (ZvTPArithSin *)param;
    ZV_ERR_RUN(zv_arith_sin(p->src, p->dst));
}
void zv_arithSin(ZvObject src, ZvObject dst)
{
    ZvTPArithSin taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_sin, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithCos;
void zv_task_arith_cos(void *param)
{
    ZvTPArithCos *p = (ZvTPArithCos *)param;
    ZV_ERR_RUN(zv_arith_cos(p->src, p->dst));
}
void zv_arithCos(ZvObject src, ZvObject dst)
{
    ZvTPArithCos taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_cos, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithTan;
void zv_task_arith_tan(void *param)
{
    ZvTPArithTan *p = (ZvTPArithTan *)param;
    ZV_ERR_RUN(zv_arith_tan(p->src, p->dst));
}
void zv_arithTan(ZvObject src, ZvObject dst)
{
    ZvTPArithTan taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_tan, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithAsin;
void zv_task_arith_asin(void *param)
{
    ZvTPArithAsin *p = (ZvTPArithAsin *)param;
    ZV_ERR_RUN(zv_arith_asin(p->src, p->dst));
}
void zv_arithAsin(ZvObject src, ZvObject dst)
{
    ZvTPArithAsin taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_asin, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithAcos;
void zv_task_arith_acos(void *param)
{
    ZvTPArithAcos *p = (ZvTPArithAcos *)param;
    ZV_ERR_RUN(zv_arith_acos(p->src, p->dst));
}
void zv_arithAcos(ZvObject src, ZvObject dst)
{
    ZvTPArithAcos taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_acos, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithAtan;
void zv_task_arith_atan(void *param)
{
    ZvTPArithAtan *p = (ZvTPArithAtan *)param;
    ZV_ERR_RUN(zv_arith_atan(p->src, p->dst));
}
void zv_arithAtan(ZvObject src, ZvObject dst)
{
    ZvTPArithAtan taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_atan, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
}ZvTPArithAtan2;
void zv_task_arith_atan2(void *param)
{
    ZvTPArithAtan2 *p = (ZvTPArithAtan2 *)param;
    ZV_ERR_RUN(zv_arith_atan2(p->src1, p->src2, p->dst));
}
void zv_arithAtan2(ZvObject src1, ZvObject src2, ZvObject dst)
{
    ZvTPArithAtan2 taskParam_0 = {src1, src2, dst};
    zv_mod_registerRun(zv_task_arith_atan2, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
    int baseType;
}ZvTPArithExp;
void zv_task_arith_exp(void *param)
{
    ZvTPArithExp *p = (ZvTPArithExp *)param;
    ZV_ERR_RUN(zv_arith_exp(p->src, p->dst, p->baseType));
}
void zv_arithExp(ZvObject src, ZvObject dst, int baseType)
{
    ZvTPArithExp taskParam_0 = {src, dst, baseType};
    zv_mod_registerRun(zv_task_arith_exp, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
    int baseType;
}ZvTPArithLog;
void zv_task_arith_log(void *param)
{
    ZvTPArithLog *p = (ZvTPArithLog *)param;
    ZV_ERR_RUN(zv_arith_log(p->src, p->dst, p->baseType));
}
void zv_arithLog(ZvObject src, ZvObject dst, int baseType)
{
    ZvTPArithLog taskParam_0 = {src, dst, baseType};
    zv_mod_registerRun(zv_task_arith_log, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
    double exponent;
}ZvTPArithPow;
void zv_task_arith_pow(void *param)
{
    ZvTPArithPow *p = (ZvTPArithPow *)param;
    ZV_ERR_RUN(zv_arith_pow(p->src, p->dst, p->exponent));
}
void zv_arithPow(ZvObject src, ZvObject dst, double exponent)
{
    ZvTPArithPow taskParam_0 = {src, dst, exponent};
    zv_mod_registerRun(zv_task_arith_pow, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithSqrt;
void zv_task_arith_sqrt(void *param)
{
    ZvTPArithSqrt *p = (ZvTPArithSqrt *)param;
    ZV_ERR_RUN(zv_arith_sqrt(p->src, p->dst));
}
void zv_arithSqrt(ZvObject src, ZvObject dst)
{
    ZvTPArithSqrt taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_sqrt, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvImage dst;
    int op;
}ZvTPArithCompare;
void zv_task_arith_compare(void *param)
{
    ZvTPArithCompare *p = (ZvTPArithCompare *)param;
    ZV_ERR_RUN(zv_arith_compare(p->src1, p->src2, p->dst, p->op));
}
void zv_arithCompare(ZvObject src1, ZvObject src2, ZvImage dst, int op)
{
    ZvTPArithCompare taskParam_0 = {src1, src2, dst, op};
    zv_mod_registerRun(zv_task_arith_compare, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
}ZvTPArithMax;
void zv_task_arith_max(void *param)
{
    ZvTPArithMax *p = (ZvTPArithMax *)param;
    ZV_ERR_RUN(zv_arith_max(p->src1, p->src2, p->dst));
}
void zv_arithMax(ZvObject src1, ZvObject src2, ZvObject dst)
{
    ZvTPArithMax taskParam_0 = {src1, src2, dst};
    zv_mod_registerRun(zv_task_arith_max, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject src2;
    ZvObject dst;
}ZvTPArithMin;
void zv_task_arith_min(void *param)
{
    ZvTPArithMin *p = (ZvTPArithMin *)param;
    ZV_ERR_RUN(zv_arith_min(p->src1, p->src2, p->dst));
}
void zv_arithMin(ZvObject src1, ZvObject src2, ZvObject dst)
{
    ZvTPArithMin taskParam_0 = {src1, src2, dst};
    zv_mod_registerRun(zv_task_arith_min, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject dst;
    double *scalar;
}ZvTPArithMaxS;
void zv_task_arith_maxS(void *param)
{
    ZvTPArithMaxS *p = (ZvTPArithMaxS *)param;
    ZV_ERR_RUN(zv_arith_maxS(p->src1, p->dst, p->scalar));
}
void zv_arithMaxS(ZvObject src1, ZvObject dst, double *scalar)
{
    ZvTPArithMaxS taskParam_0 = {src1, dst, scalar};
    zv_mod_registerRun(zv_task_arith_maxS, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src1;
    ZvObject dst;
    double *scalar;
}ZvTPArithMinS;
void zv_task_arith_minS(void *param)
{
    ZvTPArithMinS *p = (ZvTPArithMinS *)param;
    ZV_ERR_RUN(zv_arith_minS(p->src1, p->dst, p->scalar));
}
void zv_arithMinS(ZvObject src1, ZvObject dst, double *scalar)
{
    ZvTPArithMinS taskParam_0 = {src1, dst, scalar};
    zv_mod_registerRun(zv_task_arith_minS, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject x;
    ZvObject y;
    ZvObject magnitude;
}ZvTPArithMagnitude;
void zv_task_arith_magnitude(void *param)
{
    ZvTPArithMagnitude *p = (ZvTPArithMagnitude *)param;
    ZV_ERR_RUN(zv_arith_magnitude(p->x, p->y, p->magnitude));
}
void zv_arithMagnitude(ZvObject x, ZvObject y, ZvObject magnitude)
{
    ZvTPArithMagnitude taskParam_0 = {x, y, magnitude};
    zv_mod_registerRun(zv_task_arith_magnitude, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject x;
    ZvObject y;
    ZvObject angle;
}ZvTPArithPhase;
void zv_task_arith_phase(void *param)
{
    ZvTPArithPhase *p = (ZvTPArithPhase *)param;
    ZV_ERR_RUN(zv_arith_phase(p->x, p->y, p->angle));
}
void zv_arithPhase(ZvObject x, ZvObject y, ZvObject angle)
{
    ZvTPArithPhase taskParam_0 = {x, y, angle};
    zv_mod_registerRun(zv_task_arith_phase, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
    int dstType;
}ZvTPArithIntegral;
void zv_task_arith_integral(void *param)
{
    ZvTPArithIntegral *p = (ZvTPArithIntegral *)param;
    ZV_ERR_RUN(zv_arith_integral(p->src, p->dst, p->dstType));
}
void zv_arithIntegral(ZvObject src, ZvObject dst, int dstType)
{
    ZvTPArithIntegral taskParam_0 = {src, dst, dstType};
    zv_mod_registerRun(zv_task_arith_integral, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
    ZvObject dstSqrt;
    int dstType;
}ZvTPArithIntegral2;
void zv_task_arith_integral2(void *param)
{
    ZvTPArithIntegral2 *p = (ZvTPArithIntegral2 *)param;
    ZV_ERR_RUN(zv_arith_integral2(p->src, p->dst, p->dstSqrt, p->dstType));
}
void zv_arithIntegral2(ZvObject src, ZvObject dst, ZvObject dstSqrt, int dstType)
{
    ZvTPArithIntegral2 taskParam_0 = {src, dst, dstSqrt, dstType};
    zv_mod_registerRun(zv_task_arith_integral2, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage dst;
}ZvTPArithAnd;
void zv_task_arith_and(void *param)
{
    ZvTPArithAnd *p = (ZvTPArithAnd *)param;
    ZV_ERR_RUN(zv_arith_and(p->src1, p->src2, p->dst));
}
void zv_arithAnd(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZvTPArithAnd taskParam_0 = {src1, src2, dst};
    zv_mod_registerRun(zv_task_arith_and, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage dst;
}ZvTPArithOr;
void zv_task_arith_or(void *param)
{
    ZvTPArithOr *p = (ZvTPArithOr *)param;
    ZV_ERR_RUN(zv_arith_or(p->src1, p->src2, p->dst));
}
void zv_arithOr(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZvTPArithOr taskParam_0 = {src1, src2, dst};
    zv_mod_registerRun(zv_task_arith_or, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
}ZvTPArithNot;
void zv_task_arith_not(void *param)
{
    ZvTPArithNot *p = (ZvTPArithNot *)param;
    ZV_ERR_RUN(zv_arith_not(p->src, p->dst));
}
void zv_arithNot(ZvImage src, ZvImage dst)
{
    ZvTPArithNot taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_not, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src1;
    ZvImage src2;
    ZvImage dst;
}ZvTPArithXor;
void zv_task_arith_xor(void *param)
{
    ZvTPArithXor *p = (ZvTPArithXor *)param;
    ZV_ERR_RUN(zv_arith_xor(p->src1, p->src2, p->dst));
}
void zv_arithXor(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZvTPArithXor taskParam_0 = {src1, src2, dst};
    zv_mod_registerRun(zv_task_arith_xor, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix src;
    ZvMatrix dst;
}ZvTPArithTranspose;
void zv_task_arith_transpose(void *param)
{
    ZvTPArithTranspose *p = (ZvTPArithTranspose *)param;
    ZV_ERR_RUN(zv_arith_transpose(p->src, p->dst));
}
void zv_arithTranspose(ZvMatrix src, ZvMatrix dst)
{
    ZvTPArithTranspose taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_transpose, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix src;
    ZvMatrix dst;
    int method;
}ZvTPArithInvert;
void zv_task_arith_invert(void *param)
{
    ZvTPArithInvert *p = (ZvTPArithInvert *)param;
    ZV_ERR_RUN(zv_arith_invert(p->src, p->dst, p->method));
}
void zv_arithInvert(ZvMatrix src, ZvMatrix dst, int method)
{
    ZvTPArithInvert taskParam_0 = {src, dst, method};
    zv_mod_registerRun(zv_task_arith_invert, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    int normType;
    double *value;
}ZvTPArithNorm;
void zv_task_arith_norm(void *param)
{
    ZvTPArithNorm *p = (ZvTPArithNorm *)param;
    *p->value = zv_arith_norm(p->mat, p->normType);
}
void zv_arithNorm(ZvMatrix mat, int normType, double *value)
{
    ZvTPArithNorm taskParam_0 = {mat, normType, value};
    zv_mod_registerRun(zv_task_arith_norm, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat1;
    ZvMatrix mat2;
    ZvMatrix dst;
}ZvTPArithMatrixMult;
void zv_task_arith_matrixMult(void *param)
{
    ZvTPArithMatrixMult *p = (ZvTPArithMatrixMult *)param;
    ZV_ERR_RUN(zv_arith_matrixMult(p->mat1, p->mat2, p->dst));
}
void zv_arithMatrixMult(ZvMatrix mat1, ZvMatrix mat2, ZvMatrix dst)
{
    ZvTPArithMatrixMult taskParam_0 = {mat1, mat2, dst};
    zv_mod_registerRun(zv_task_arith_matrixMult, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix src;
    ZvMatrix eigenvalues;
    ZvMatrix eigenvectors;
    bool isSymmetric;
}ZvTPArithEigen;
void zv_task_arith_eigen(void *param)
{
    ZvTPArithEigen *p = (ZvTPArithEigen *)param;
    ZV_ERR_RUN(zv_arith_eigen(p->src, p->eigenvalues, p->eigenvectors, p->isSymmetric));
}
void zv_arithEigen(ZvMatrix src, ZvMatrix eigenvalues, ZvMatrix eigenvectors, bool isSymmetric)
{
    ZvTPArithEigen taskParam_0 = {src, eigenvalues, eigenvectors, isSymmetric};
    zv_mod_registerRun(zv_task_arith_eigen, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    int *cnt;
}ZvTPArithZeroCount;
void zv_task_arith_zeroCount(void *param)
{
    ZvTPArithZeroCount *p = (ZvTPArithZeroCount *)param;
    *p->cnt = zv_arith_zeroCount(p->src);
}
void zv_arithZeroCount(ZvObject src, int *cnt)
{
    ZvTPArithZeroCount taskParam_0 = {src, cnt};
    zv_mod_registerRun(zv_task_arith_zeroCount, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    double * sum;
}ZvTPArithSum;
void zv_task_arith_sum(void *param)
{
    ZvTPArithSum *p = (ZvTPArithSum *)param;
    ZV_ERR_RUN(zv_arith_sum(p->src, p->sum));
}
void zv_arithSum(ZvObject src, double * sum)
{
    ZvTPArithSum taskParam_0 = {src, sum};
    zv_mod_registerRun(zv_task_arith_sum, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithSumRow;
void zv_task_arith_sumRow(void *param)
{
    ZvTPArithSumRow *p = (ZvTPArithSumRow *)param;
    ZV_ERR_RUN(zv_arith_sumRow(p->src, p->dst));
}
void zv_arithSumRow(ZvObject src, ZvObject dst)
{
    ZvTPArithSumRow taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_sumRow, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    ZvObject dst;
}ZvTPArithSumCol;
void zv_task_arith_sumCol(void *param)
{
    ZvTPArithSumCol *p = (ZvTPArithSumCol *)param;
    ZV_ERR_RUN(zv_arith_sumCol(p->src, p->dst));
}
void zv_arithSumCol(ZvObject src, ZvObject dst)
{
    ZvTPArithSumCol taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_arith_sumCol, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    double *mean;
}ZvTPArithMean;
void zv_task_arith_mean(void *param)
{
    ZvTPArithMean *p = (ZvTPArithMean *)param;
    ZV_ERR_RUN(zv_arith_mean(p->src, p->mean));
}
void zv_arithMean(ZvObject src, double *mean)
{
    ZvTPArithMean taskParam_0 = {src, mean};
    zv_mod_registerRun(zv_task_arith_mean, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    double *mean;
    double *stdDev;
}ZvTPArithMeanSdev;
void zv_task_arith_meanSdev(void *param)
{
    ZvTPArithMeanSdev *p = (ZvTPArithMeanSdev *)param;
    ZV_ERR_RUN(zv_arith_meanSdev(p->src, p->mean, p->stdDev));
}
void zv_arithMeanSdev(ZvObject src, double *mean, double *stdDev)
{
    ZvTPArithMeanSdev taskParam_0 = {src, mean, stdDev};
    zv_mod_registerRun(zv_task_arith_meanSdev, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvObject src;
    double *value;
    int *pos;
}ZvTPArithMinMaxLoc;
void zv_task_arith_minMaxLoc(void *param)
{
    ZvTPArithMinMaxLoc *p = (ZvTPArithMinMaxLoc *)param;
    ZV_ERR_RUN(zv_arith_minMaxLoc(p->src, p->value, p->pos));
}
void zv_arithMinMaxLoc(ZvObject src, double *value, int *pos)
{
    ZvTPArithMinMaxLoc taskParam_0 = {src, value, pos};
    zv_mod_registerRun(zv_task_arith_minMaxLoc, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvMatrix hist;
    int size;
    double low;
    double upper;
}ZvTPArithHist;
void zv_task_arith_hist(void *param)
{
    ZvTPArithHist *p = (ZvTPArithHist *)param;
    ZV_ERR_RUN(zv_arith_hist(p->img, p->hist, p->size, p->low, p->upper));
}
void zv_arithHist(ZvImage img, ZvMatrix hist, int size, double low, double upper)
{
    ZvTPArithHist taskParam_0 = {img, hist, size, low, upper};
    zv_mod_registerRun(zv_task_arith_hist, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvMatrix hist;
}ZvTPArithHistRgb;
void zv_task_arith_histRgb(void *param)
{
    ZvTPArithHistRgb *p = (ZvTPArithHistRgb *)param;
    ZV_ERR_RUN(zv_arith_histRgb(p->img, p->hist));
}
void zv_arithHistRgb(ZvImage img, ZvMatrix hist)
{
    ZvTPArithHistRgb taskParam_0 = {img, hist};
    zv_mod_registerRun(zv_task_arith_histRgb, &taskParam_0, sizeof(taskParam_0));
}


//ip imgproc 图像处理模块 basic/ zv_geometric_trans.cpp filter.cpp zv_morph.cpp zv_segment.cpp zv_color.cpp
//zv_geometric_trans.cpp  几何（旋转、缩放、畸变矫正、仿射透视变换）
//zv_color.cpp 颜色（Bayer、HSV）、其它（颜色映射)
//filter.cpp 滤波（高斯、中值、均值、边缘、自定义、FFT、DCT）
//zv_morph.cpp 形态学（腐蚀、膨胀、开、闭）
//zv_segment.cpp 分割（二值、分类分割、区域增长、边缘分割）
typedef struct
{
    ZvImage src;
    ZvImage dst;
    int type;
}ZvTPIpMirror;
void zv_task_ip_mirror(void *param)
{
    ZvTPIpMirror *p = (ZvTPIpMirror *)param;
    ZV_ERR_RUN(zv_ip_mirror(p->src, p->dst, p->type));
}
void zv_ipMirror(ZvImage src, ZvImage dst, int type)
{
    ZvTPIpMirror taskParam_0 = {src, dst, type};
    zv_mod_registerRun(zv_task_ip_mirror, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double angle;
    int interp;
}ZvTPIpRotate;
void zv_task_ip_rotate(void *param)
{
    ZvTPIpRotate *p = (ZvTPIpRotate *)param;
    ZV_ERR_RUN(zv_ip_rotate(p->src, p->dst, p->angle, p->interp));
}
void zv_ipRotate(ZvImage src, ZvImage dst, double angle, int interp)
{
    ZvTPIpRotate taskParam_0 = {src, dst, angle, interp};
    zv_mod_registerRun(zv_task_ip_rotate, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double scaleW;
    double scaleH;
    int interp;
}ZvTPIpZoom;
void zv_task_ip_zoom(void *param)
{
    ZvTPIpZoom *p = (ZvTPIpZoom *)param;
    ZV_ERR_RUN(zv_ip_zoom(p->src, p->dst, p->scaleW, p->scaleH, p->interp));
}
void zv_ipZoom(ZvImage src, ZvImage dst, double scaleW, double scaleH, int interp)
{
    ZvTPIpZoom taskParam_0 = {src, dst, scaleW, scaleH, interp};
    zv_mod_registerRun(zv_task_ip_zoom, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int dstW;
    int dstH;
    int interp;
}ZvTPIpResize;
void zv_task_ip_resize(void *param)
{
    ZvTPIpResize *p = (ZvTPIpResize *)param;
    ZV_ERR_RUN(zv_ip_resize(p->src, p->dst, p->dstW, p->dstH, p->interp));
}
void zv_ipResize(ZvImage src, ZvImage dst, int dstW, int dstH, int interp)
{
    ZvTPIpResize taskParam_0 = {src, dst, dstW, dstH, interp};
    zv_mod_registerRun(zv_task_ip_resize, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    ZvMatrix mat;
    int dstW;
    int dstH;
    int interp;
    char *border;
}ZvTPIpAffine;
void zv_task_ip_affine(void *param)
{
    ZvTPIpAffine *p = (ZvTPIpAffine *)param;
    ZV_ERR_RUN(zv_ip_affine(p->src, p->dst, p->mat, p->dstW, p->dstH, p->interp, p->border));
}
void zv_ipAffine(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border)
{
    ZvTPIpAffine taskParam_0 = {src, dst, mat, dstW, dstH, interp, border};
    zv_mod_registerRun(zv_task_ip_affine, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    ZvMatrix mat;
    int dstW;
    int dstH;
    int interp;
    char *border;
}ZvTPIpPerspective;
void zv_task_ip_perspective(void *param)
{
    ZvTPIpPerspective *p = (ZvTPIpPerspective *)param;
    ZV_ERR_RUN(zv_ip_perspective(p->src, p->dst, p->mat, p->dstW, p->dstH, p->interp, p->border));
}
void zv_ipPerspective(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border)
{
    ZvTPIpPerspective taskParam_0 = {src, dst, mat, dstW, dstH, interp, border};
    zv_mod_registerRun(zv_task_ip_perspective, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage binImg;
    int type;
    int orderX;
    int orderY;
    double *m;
}ZvTPIpMoments;
void zv_task_ip_moments(void *param)
{
    ZvTPIpMoments *p = (ZvTPIpMoments *)param;
    *p->m = zv_ip_moments(p->binImg, p->type, p->orderX, p->orderY);
}
void zv_ipMoments(ZvImage binImg, int type, int orderX, int orderY, double *m)
{
    ZvTPIpMoments taskParam_0 = {binImg, type, orderX, orderY, m};
    zv_mod_registerRun(zv_task_ip_moments, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage rgb;
    ZvImage gray;
    bool isRgba;
}ZvTPIpRgbToGray;
void zv_task_ip_rgbToGray(void *param)
{
    ZvTPIpRgbToGray *p = (ZvTPIpRgbToGray *)param;
    ZV_ERR_RUN(zv_ip_rgbToGray(p->rgb, p->gray, p->isRgba));
}
void zv_ipRgbToGray(ZvImage rgb, ZvImage gray, bool isRgba)
{
    ZvTPIpRgbToGray taskParam_0 = {rgb, gray, isRgba};
    zv_mod_registerRun(zv_task_ip_rgbToGray, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage gray;
    ZvImage rgb;
}ZvTPIpGrayToRgb;
void zv_task_ip_grayToRgb(void *param)
{
    ZvTPIpGrayToRgb *p = (ZvTPIpGrayToRgb *)param;
    ZV_ERR_RUN(zv_ip_grayToRgb(p->gray, p->rgb));
}
void zv_ipGrayToRgb(ZvImage gray, ZvImage rgb)
{
    ZvTPIpGrayToRgb taskParam_0 = {gray, rgb};
    zv_mod_registerRun(zv_task_ip_grayToRgb, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage color;
    ZvImage rgb;
    int colorSpace;
}ZvTPIpColorToRgb;
void zv_task_ip_colorToRgb(void *param)
{
    ZvTPIpColorToRgb *p = (ZvTPIpColorToRgb *)param;
    ZV_ERR_RUN(zv_ip_colorToRgb(p->color, p->rgb, p->colorSpace));
}
void zv_ipColorToRgb(ZvImage color, ZvImage rgb, int colorSpace)
{
    ZvTPIpColorToRgb taskParam_0 = {color, rgb, colorSpace};
    zv_mod_registerRun(zv_task_ip_colorToRgb, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage rgb;
    ZvImage color;
    int colorSpace;
}ZvTPIpRgbToColor;
void zv_task_ip_rgbToColor(void *param)
{
    ZvTPIpRgbToColor *p = (ZvTPIpRgbToColor *)param;
    ZV_ERR_RUN(zv_ip_rgbToColor(p->rgb, p->color, p->colorSpace));
}
void zv_ipRgbToColor(ZvImage rgb, ZvImage color, int colorSpace)
{
    ZvTPIpRgbToColor taskParam_0 = {rgb, color, colorSpace};
    zv_mod_registerRun(zv_task_ip_rgbToColor, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage bayer;
    ZvImage rgb;
    int bayerType;
}ZvTPIpBayerToRgb;
void zv_task_ip_bayerToRgb(void *param)
{
    ZvTPIpBayerToRgb *p = (ZvTPIpBayerToRgb *)param;
    ZV_ERR_RUN(zv_ip_bayerToRgb(p->bayer, p->rgb, p->bayerType));
}
void zv_ipBayerToRgb(ZvImage bayer, ZvImage rgb, int bayerType)
{
    ZvTPIpBayerToRgb taskParam_0 = {bayer, rgb, bayerType};
    zv_mod_registerRun(zv_task_ip_bayerToRgb, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int size;
}ZvTPIpMedianBlur;
void zv_task_ip_medianBlur(void *param)
{
    ZvTPIpMedianBlur *p = (ZvTPIpMedianBlur *)param;
    ZV_ERR_RUN(zv_ip_medianBlur(p->src, p->dst, p->size));
}
void zv_ipMedianBlur(ZvImage src, ZvImage dst, int size)
{
    ZvTPIpMedianBlur taskParam_0 = {src, dst, size};
    zv_mod_registerRun(zv_task_ip_medianBlur, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int size;
}ZvTPIpMeanBlur;
void zv_task_ip_meanBlur(void *param)
{
    ZvTPIpMeanBlur *p = (ZvTPIpMeanBlur *)param;
    ZV_ERR_RUN(zv_ip_meanBlur(p->src, p->dst, p->size));
}
void zv_ipMeanBlur(ZvImage src, ZvImage dst, int size)
{
    ZvTPIpMeanBlur taskParam_0 = {src, dst, size};
    zv_mod_registerRun(zv_task_ip_meanBlur, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int size;
}ZvTPIpGaussBlur;
void zv_task_ip_gaussBlur(void *param)
{
    ZvTPIpGaussBlur *p = (ZvTPIpGaussBlur *)param;
    ZV_ERR_RUN(zv_ip_gaussBlur(p->src, p->dst, p->size));
}
void zv_ipGaussBlur(ZvImage src, ZvImage dst, int size)
{
    ZvTPIpGaussBlur taskParam_0 = {src, dst, size};
    zv_mod_registerRun(zv_task_ip_gaussBlur, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double sigmaSpace;
    double sigmaColor;
}ZvTPIpBilateralFilter;
void zv_task_ip_bilateralFilter(void *param)
{
    ZvTPIpBilateralFilter *p = (ZvTPIpBilateralFilter *)param;
    ZV_ERR_RUN(zv_ip_bilateralFilter(p->src, p->dst, p->sigmaSpace, p->sigmaColor));
}
void zv_ipBilateralFilter(ZvImage src, ZvImage dst, double sigmaSpace, double sigmaColor)
{
    ZvTPIpBilateralFilter taskParam_0 = {src, dst, sigmaSpace, sigmaColor};
    zv_mod_registerRun(zv_task_ip_bilateralFilter, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int dx;
    int dy;
    int size;
}ZvTPIpSobel;
void zv_task_ip_sobel(void *param)
{
    ZvTPIpSobel *p = (ZvTPIpSobel *)param;
    ZV_ERR_RUN(zv_ip_sobel(p->src, p->dst, p->dx, p->dy, p->size));
}
void zv_ipSobel(ZvImage src, ZvImage dst, int dx, int dy, int size)
{
    ZvTPIpSobel taskParam_0 = {src, dst, dx, dy, size};
    zv_mod_registerRun(zv_task_ip_sobel, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int dx;
    int dy;
}ZvTPIpScharr;
void zv_task_ip_scharr(void *param)
{
    ZvTPIpScharr *p = (ZvTPIpScharr *)param;
    ZV_ERR_RUN(zv_ip_scharr(p->src, p->dst, p->dx, p->dy));
}
void zv_ipScharr(ZvImage src, ZvImage dst, int dx, int dy)
{
    ZvTPIpScharr taskParam_0 = {src, dst, dx, dy};
    zv_mod_registerRun(zv_task_ip_scharr, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int size;
}ZvTPIpLaplace;
void zv_task_ip_laplace(void *param)
{
    ZvTPIpLaplace *p = (ZvTPIpLaplace *)param;
    ZV_ERR_RUN(zv_ip_laplace(p->src, p->dst, p->size));
}
void zv_ipLaplace(ZvImage src, ZvImage dst, int size)
{
    ZvTPIpLaplace taskParam_0 = {src, dst, size};
    zv_mod_registerRun(zv_task_ip_laplace, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvImage dst;
    double thresh1;
    double thresh2;
    int size;
}ZvTPIpCanny;
void zv_task_ip_canny(void *param)
{
    ZvTPIpCanny *p = (ZvTPIpCanny *)param;
    ZV_ERR_RUN(zv_ip_canny(p->img, p->dst, p->thresh1, p->thresh2, p->size));
}
void zv_ipCanny(ZvImage img, ZvImage dst, double thresh1, double thresh2, int size)
{
    ZvTPIpCanny taskParam_0 = {img, dst, thresh1, thresh2, size};
    zv_mod_registerRun(zv_task_ip_canny, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
}ZvTPIpEqualizeHist;
void zv_task_ip_equalizeHist(void *param)
{
    ZvTPIpEqualizeHist *p = (ZvTPIpEqualizeHist *)param;
    ZV_ERR_RUN(zv_ip_equalizeHist(p->src, p->dst));
}
void zv_ipEqualizeHist(ZvImage src, ZvImage dst)
{
    ZvTPIpEqualizeHist taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_ip_equalizeHist, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int seWidth;
    int seHeight;
}ZvTPIpDilate;
void zv_task_ip_dilate(void *param)
{
    ZvTPIpDilate *p = (ZvTPIpDilate *)param;
    ZV_ERR_RUN(zv_ip_dilate(p->src, p->dst, p->seWidth, p->seHeight));
}
void zv_ipDilate(ZvImage src, ZvImage dst, int seWidth, int seHeight)
{
    ZvTPIpDilate taskParam_0 = {src, dst, seWidth, seHeight};
    zv_mod_registerRun(zv_task_ip_dilate, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int seWidth;
    int seHeight;
}ZvTPIpErode;
void zv_task_ip_erode(void *param)
{
    ZvTPIpErode *p = (ZvTPIpErode *)param;
    ZV_ERR_RUN(zv_ip_erode(p->src, p->dst, p->seWidth, p->seHeight));
}
void zv_ipErode(ZvImage src, ZvImage dst, int seWidth, int seHeight)
{
    ZvTPIpErode taskParam_0 = {src, dst, seWidth, seHeight};
    zv_mod_registerRun(zv_task_ip_erode, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int seWidth;
    int seHeight;
}ZvTPIpOpening;
void zv_task_ip_opening(void *param)
{
    ZvTPIpOpening *p = (ZvTPIpOpening *)param;
    ZV_ERR_RUN(zv_ip_opening(p->src, p->dst, p->seWidth, p->seHeight));
}
void zv_ipOpening(ZvImage src, ZvImage dst, int seWidth, int seHeight)
{
    ZvTPIpOpening taskParam_0 = {src, dst, seWidth, seHeight};
    zv_mod_registerRun(zv_task_ip_opening, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    int seWidth;
    int seHeight;
}ZvTPIpClosing;
void zv_task_ip_closing(void *param)
{
    ZvTPIpClosing *p = (ZvTPIpClosing *)param;
    ZV_ERR_RUN(zv_ip_closing(p->src, p->dst, p->seWidth, p->seHeight));
}
void zv_ipClosing(ZvImage src, ZvImage dst, int seWidth, int seHeight)
{
    ZvTPIpClosing taskParam_0 = {src, dst, seWidth, seHeight};
    zv_mod_registerRun(zv_task_ip_closing, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage kernel;
    int width;
    int height;
    double sigma;
    double theta;
    double lambd;
    double gamma;
    double psi;
}ZvTPIpGaborKernel;
void zv_task_ip_gaborKernel(void *param)
{
    ZvTPIpGaborKernel *p = (ZvTPIpGaborKernel *)param;
    ZV_ERR_RUN(zv_ip_gaborKernel(p->kernel, p->width, p->height, p->sigma, p->theta, p->lambd, p->gamma, p->psi));
}
void zv_ipGaborKernel(ZvImage kernel, int width, int height, double sigma, double theta, double lambd, double gamma, double psi)
{
    ZvTPIpGaborKernel taskParam_0 = {kernel, width, height, sigma, theta, lambd, gamma, psi};
    zv_mod_registerRun(zv_task_ip_gaborKernel, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage kernelX;
    ZvImage kernelY;
    int dX;
    int dY;
    int size;
}ZvTPIpDerivKernel;
void zv_task_ip_derivKernel(void *param)
{
    ZvTPIpDerivKernel *p = (ZvTPIpDerivKernel *)param;
    ZV_ERR_RUN(zv_ip_derivKernel(p->kernelX, p->kernelY, p->dX, p->dY, p->size));
}
void zv_ipDerivKernel(ZvImage kernelX, ZvImage kernelY, int dX, int dY, int size)
{
    ZvTPIpDerivKernel taskParam_0 = {kernelX, kernelY, dX, dY, size};
    zv_mod_registerRun(zv_task_ip_derivKernel, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
}ZvTPIpDct;
void zv_task_ip_dct(void *param)
{
    ZvTPIpDct *p = (ZvTPIpDct *)param;
    ZV_ERR_RUN(zv_ip_dct(p->src, p->dst));
}
void zv_ipDct(ZvImage src, ZvImage dst)
{
    ZvTPIpDct taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_ip_dct, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
}ZvTPIpIdct;
void zv_task_ip_idct(void *param)
{
    ZvTPIpIdct *p = (ZvTPIpIdct *)param;
    ZV_ERR_RUN(zv_ip_idct(p->src, p->dst));
}
void zv_ipIdct(ZvImage src, ZvImage dst)
{
    ZvTPIpIdct taskParam_0 = {src, dst};
    zv_mod_registerRun(zv_task_ip_idct, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage kernel;
    ZvImage dst;
    int dstType;
    int anchorX;
    int anchorY;
    double delta;
    char * border;
}ZvTPIpFilter;
void zv_task_ip_filter(void *param)
{
    ZvTPIpFilter *p = (ZvTPIpFilter *)param;
    ZV_ERR_RUN(zv_ip_filter(p->src, p->kernel, p->dst, p->dstType, p->anchorX, p->anchorY, p->delta, p->border));
}
void zv_ipFilter(ZvImage src, ZvImage kernel, ZvImage dst, int dstType, int anchorX, int anchorY, double delta, char * border)
{
    ZvTPIpFilter taskParam_0 = {src, kernel, dst, dstType, anchorX, anchorY, delta, border};
    zv_mod_registerRun(zv_task_ip_filter, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage kernelX;
    ZvImage kernelY;
    ZvImage dst;
    int dstType;
    int anchorX;
    int anchorY;
    double delta;
    char *border;
}ZvTPIpSepFilter;
void zv_task_ip_sepFilter(void *param)
{
    ZvTPIpSepFilter *p = (ZvTPIpSepFilter *)param;
    ZV_ERR_RUN(zv_ip_sepFilter(p->src, p->kernelX, p->kernelY, p->dst, p->dstType, p->anchorX, p->anchorY, p->delta, p->border));
}
void zv_ipSepFilter(ZvImage src, ZvImage kernelX, ZvImage kernelY, ZvImage dst, int dstType, int anchorX, int anchorY, double delta, char *border)
{
    ZvTPIpSepFilter taskParam_0 = {src, kernelX, kernelY, dst, dstType, anchorX, anchorY, delta, border};
    zv_mod_registerRun(zv_task_ip_sepFilter, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dstRe;
    ZvImage dstIm;
}ZvTPIpFft;
void zv_task_ip_fft(void *param)
{
    ZvTPIpFft *p = (ZvTPIpFft *)param;
    ZV_ERR_RUN(zv_ip_fft(p->src, p->dstRe, p->dstIm));
}
void zv_ipFft(ZvImage src, ZvImage dstRe, ZvImage dstIm)
{
    ZvTPIpFft taskParam_0 = {src, dstRe, dstIm};
    zv_mod_registerRun(zv_task_ip_fft, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage srcRe;
    ZvImage srcIm;
    ZvImage dst;
}ZvTPIpIfft;
void zv_task_ip_ifft(void *param)
{
    ZvTPIpIfft *p = (ZvTPIpIfft *)param;
    ZV_ERR_RUN(zv_ip_ifft(p->srcRe, p->srcIm, p->dst));
}
void zv_ipIfft(ZvImage srcRe, ZvImage srcIm, ZvImage dst)
{
    ZvTPIpIfft taskParam_0 = {srcRe, srcIm, dst};
    zv_mod_registerRun(zv_task_ip_ifft, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage *dst;
    int level;
    char *border;
}ZvTPIpPyramid;
void zv_task_ip_pyramid(void *param)
{
    ZvTPIpPyramid *p = (ZvTPIpPyramid *)param;
    ZV_ERR_RUN(zv_ip_pyramid(p->src, p->dst, p->level, p->border));
}
void zv_ipPyramid(ZvImage src, ZvImage *dst, int level, char *border)
{
    ZvTPIpPyramid taskParam_0 = {src, dst, level, border};
    zv_mod_registerRun(zv_task_ip_pyramid, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double factor;
    char *border;
}ZvTPIpPyramidDown;
void zv_task_ip_pyramidDown(void *param)
{
    ZvTPIpPyramidDown *p = (ZvTPIpPyramidDown *)param;
    ZV_ERR_RUN(zv_ip_pyramidDown(p->src, p->dst, p->factor, p->border));
}
void zv_ipPyramidDown(ZvImage src, ZvImage dst, double factor, char *border)
{
    ZvTPIpPyramidDown taskParam_0 = {src, dst, factor, border};
    zv_mod_registerRun(zv_task_ip_pyramidDown, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double factor;
    char *border;
}ZvTPIpPyramidUp;
void zv_task_ip_pyramidUp(void *param)
{
    ZvTPIpPyramidUp *p = (ZvTPIpPyramidUp *)param;
    ZV_ERR_RUN(zv_ip_pyramidUp(p->src, p->dst, p->factor, p->border));
}
void zv_ipPyramidUp(ZvImage src, ZvImage dst, double factor, char *border)
{
    ZvTPIpPyramidUp taskParam_0 = {src, dst, factor, border};
    zv_mod_registerRun(zv_task_ip_pyramidUp, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage kernel;
    int shape;
    int sizeX;
    int sizeY;
    int anchorX;
    int anchorY;
}ZvTPIpMorphSe;
void zv_task_ip_morphSe(void *param)
{
    ZvTPIpMorphSe *p = (ZvTPIpMorphSe *)param;
    ZV_ERR_RUN(zv_ip_morphSe(p->kernel, p->shape, p->sizeX, p->sizeY, p->anchorX, p->anchorY));
}
void zv_ipMorphSe(ZvImage kernel, int shape, int sizeX, int sizeY, int anchorX, int anchorY)
{
    ZvTPIpMorphSe taskParam_0 = {kernel, shape, sizeX, sizeY, anchorX, anchorY};
    zv_mod_registerRun(zv_task_ip_morphSe, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    ZvImage kernel;
    int op;
    int anchorX;
    int anchorY;
    int iter;
    char *border;
}ZvTPIpMorphology;
void zv_task_ip_morphology(void *param)
{
    ZvTPIpMorphology *p = (ZvTPIpMorphology *)param;
    ZV_ERR_RUN(zv_ip_morphology(p->src, p->dst, p->kernel, p->op, p->anchorX, p->anchorY, p->iter, p->border));
}
void zv_ipMorphology(ZvImage src, ZvImage dst, ZvImage kernel, int op, int anchorX, int anchorY, int iter, char *border)
{
    ZvTPIpMorphology taskParam_0 = {src, dst, kernel, op, anchorX, anchorY, iter, border};
    zv_mod_registerRun(zv_task_ip_morphology, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage label;
    int connectivity;
    int labelType;
}ZvTPIpLabel;
void zv_task_ip_label(void *param)
{
    ZvTPIpLabel *p = (ZvTPIpLabel *)param;
    ZV_ERR_RUN(zv_ip_label(p->src, p->label, p->connectivity, p->labelType));
}
void zv_ipLabel(ZvImage src, ZvImage label, int connectivity, int labelType)
{
    ZvTPIpLabel taskParam_0 = {src, label, connectivity, labelType};
    zv_mod_registerRun(zv_task_ip_label, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage label;
    ZvMatrix stat;
    ZvMatrix centroid;
    int connectivity;
    int labelType;
}ZvTPIpLabelStat;
void zv_task_ip_labelStat(void *param)
{
    ZvTPIpLabelStat *p = (ZvTPIpLabelStat *)param;
    ZV_ERR_RUN(zv_ip_labelStat(p->src, p->label, p->stat, p->centroid, p->connectivity, p->labelType));
}
void zv_ipLabelStat(ZvImage src, ZvImage label, ZvMatrix stat, ZvMatrix centroid, int connectivity, int labelType)
{
    ZvTPIpLabelStat taskParam_0 = {src, label, stat, centroid, connectivity, labelType};
    zv_mod_registerRun(zv_task_ip_labelStat, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    double thresh0;
    double thresh1;
    bool isInv;
}ZvTPIpThreshold;
void zv_task_ip_threshold(void *param)
{
    ZvTPIpThreshold *p = (ZvTPIpThreshold *)param;
    ZV_ERR_RUN(zv_ip_threshold(p->src, p->dst, p->thresh0, p->thresh1, p->isInv));
}
void zv_ipThreshold(ZvImage src, ZvImage dst, double thresh0, double thresh1, bool isInv)
{
    ZvTPIpThreshold taskParam_0 = {src, dst, thresh0, thresh1, isInv};
    zv_mod_registerRun(zv_task_ip_threshold, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage thresh;
    ZvImage dst;
    double offset;
    bool isInv;
}ZvTPIpAdpThreshold;
void zv_task_ip_adpThreshold(void *param)
{
    ZvTPIpAdpThreshold *p = (ZvTPIpAdpThreshold *)param;
    ZV_ERR_RUN(zv_ip_adpThreshold(p->src, p->thresh, p->dst, p->offset, p->isInv));
}
void zv_ipAdpThreshold(ZvImage src, ZvImage thresh, ZvImage dst, double offset, bool isInv)
{
    ZvTPIpAdpThreshold taskParam_0 = {src, thresh, dst, offset, isInv};
    zv_mod_registerRun(zv_task_ip_adpThreshold, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage src;
    ZvImage dst;
    bool isInv;
}ZvTPIpAutoThreshold;
void zv_task_ip_autoThreshold(void *param)
{
    ZvTPIpAutoThreshold *p = (ZvTPIpAutoThreshold *)param;
    ZV_ERR_RUN(zv_ip_autoThreshold(p->src, p->dst, p->isInv));
}
void zv_ipAutoThreshold(ZvImage src, ZvImage dst, bool isInv)
{
    ZvTPIpAutoThreshold taskParam_0 = {src, dst, isInv};
    zv_mod_registerRun(zv_task_ip_autoThreshold, &taskParam_0, sizeof(taskParam_0));
}


//match    match
//match：灰度、形状、几何特征、点、3D
typedef struct
{
    ZvImage img;
    ZvImage templ;
    int *x;
    int *y;
    ZvImage mask;
}ZvTPMatchFastTempl;
void zv_task_match_fastTempl(void *param)
{
    ZvTPMatchFastTempl *p = (ZvTPMatchFastTempl *)param;
    ZV_ERR_RUN(zv_match_fastTempl(p->img, p->templ, p->x, p->y, p->mask));
}
void zv_matchFastTempl(ZvImage img, ZvImage templ, int *x, int *y, ZvImage mask)
{
    ZvTPMatchFastTempl taskParam_0 = {img, templ, x, y, mask};
    zv_mod_registerRun(zv_task_match_fastTempl, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvImage templ;
    double minScore;
    double *x;
    double *y;
    double *score;
    int method;
    bool isSubPix;
}ZvTPMatchBestTempl;
void zv_task_match_bestTempl(void *param)
{
    ZvTPMatchBestTempl *p = (ZvTPMatchBestTempl *)param;
    ZV_ERR_RUN(zv_match_bestTempl(p->img, p->templ, p->minScore, p->x, p->y, p->score, p->method, p->isSubPix));
}
void zv_matchBestTempl(ZvImage img, ZvImage templ, double minScore, double *x, double *y, double *score, int method, bool isSubPix)
{
    ZvTPMatchBestTempl taskParam_0 = {img, templ, minScore, x, y, score, method, isSubPix};
    zv_mod_registerRun(zv_task_match_bestTempl, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvImage templ;
    ZvMatrix matches;
    double minScore;
    int method;
    bool isSubPix;
}ZvTPMatchMultiTempl;
void zv_task_match_multiTempl(void *param)
{
    ZvTPMatchMultiTempl *p = (ZvTPMatchMultiTempl *)param;
    ZV_ERR_RUN(zv_match_multiTempl(p->img, p->templ, p->matches, p->minScore, p->method, p->isSubPix));
}
void zv_matchMultiTempl(ZvImage img, ZvImage templ, ZvMatrix matches, double minScore, int method, bool isSubPix)
{
    ZvTPMatchMultiTempl taskParam_0 = {img, templ, matches, minScore, method, isSubPix};
    zv_mod_registerRun(zv_task_match_multiTempl, &taskParam_0, sizeof(taskParam_0));
}


//meas    measure
//measure：圆、直线、椭圆、矩形、点、间距
void zv_measGenRect(void * mr, int x, int y, int width, int height, int filterSize)
{
    ZV_ERR_RUN(zv_meas_genRect(mr, x, y, width, height, filterSize));
}

void zv_measGenRect2(void *mr, double cx, double cy, double size1, double size2, double angle, int filterSize, int interp)
{
    ZV_ERR_RUN(zv_meas_genRect2(mr, cx, cy, size1, size2, angle, filterSize, interp));
}

void zv_measGenArc(void *mr, double cx, double cy, double r, double angleStart, double angleEnd, double rAnnulus, int filterSize, int interp)
{
    ZV_ERR_RUN(zv_meas_genArc(mr, cx, cy, r, angleStart, angleEnd, rAnnulus, filterSize, interp));
}

typedef struct
{
    ZvImage img;
    ZvMatrix proj;
    void *mr;
}ZvTPMeasProjection;
void zv_task_meas_projection(void *param)
{
    ZvTPMeasProjection *p = (ZvTPMeasProjection *)param;
    ZV_ERR_RUN(zv_meas_projection(p->img, p->proj, p->mr));
}
void zv_measProjection(ZvImage img, ZvMatrix proj, void *mr)
{
    ZvTPMeasProjection taskParam_0 = {img, proj, mr};
    zv_mod_registerRun(zv_task_meas_projection, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvMatrix pts;
    void *mr;
    int thresh;
    int type;
    int select;
}ZvTPMeasPos;
void zv_task_meas_pos(void *param)
{
    ZvTPMeasPos *p = (ZvTPMeasPos *)param;
    ZV_ERR_RUN(zv_meas_pos(p->img, p->pts, p->mr, p->thresh, p->type, p->select));
}
void zv_measPos(ZvImage img, ZvMatrix pts, void *mr, int thresh, int type, int select)
{
    ZvTPMeasPos taskParam_0 = {img, pts, mr, thresh, type, select};
    zv_mod_registerRun(zv_task_meas_pos, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvMatrix pairs;
    void *mr;
    int thresh;
    int type;
    int select;
}ZvTPMeasPairs;
void zv_task_meas_pairs(void *param)
{
    ZvTPMeasPairs *p = (ZvTPMeasPairs *)param;
    ZV_ERR_RUN(zv_meas_pairs(p->img, p->pairs, p->mr, p->thresh, p->type, p->select));
}
void zv_measPairs(ZvImage img, ZvMatrix pairs, void *mr, int thresh, int type, int select)
{
    ZvTPMeasPairs taskParam_0 = {img, pairs, mr, thresh, type, select};
    zv_mod_registerRun(zv_task_meas_pairs, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvMatrix lines;
    void *mr;
    int thresh;
    int type;
    int select;
    int subNum;
    int subWidth;
}ZvTPMeasLines;
void zv_task_meas_lines(void *param)
{
    ZvTPMeasLines *p = (ZvTPMeasLines *)param;
    ZV_ERR_RUN(zv_meas_lines(p->img, p->lines, p->mr, p->thresh, p->type, p->select, p->subNum, p->subWidth));
}
void zv_measLines(ZvImage img, ZvMatrix lines, void *mr, int thresh, int type, int select, int subNum, int subWidth)
{
    ZvTPMeasLines taskParam_0 = {img, lines, mr, thresh, type, select, subNum, subWidth};
    zv_mod_registerRun(zv_task_meas_lines, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvMatrix circles;
    void *mr;
    int thresh;
    int type;
    int select;
    int subNum;
    int subWidth;
}ZvTPMeasCircle;
void zv_task_meas_circle(void *param)
{
    ZvTPMeasCircle *p = (ZvTPMeasCircle *)param;
    ZV_ERR_RUN(zv_meas_circle(p->img, p->circles, p->mr, p->thresh, p->type, p->select, p->subNum, p->subWidth));
}
void zv_measCircle(ZvImage img, ZvMatrix circles, void *mr, int thresh, int type, int select, int subNum, int subWidth)
{
    ZvTPMeasCircle taskParam_0 = {img, circles, mr, thresh, type, select, subNum, subWidth};
    zv_mod_registerRun(zv_task_meas_circle, &taskParam_0, sizeof(taskParam_0));
}


//feat  feature
//feature：角点、霍夫、边缘
typedef struct
{
    ZvImage img;
    ZvMatrix lines;
    double rho;
    double theta;
    int thresh;
    double minLinelen;
    double maxLineGap;
}ZvTPFeatHoughLine;
void zv_task_feat_houghLine(void *param)
{
    ZvTPFeatHoughLine *p = (ZvTPFeatHoughLine *)param;
    ZV_ERR_RUN(zv_feat_houghLine(p->img, p->lines, p->rho, p->theta, p->thresh, p->minLinelen, p->maxLineGap));
}
void zv_featHoughLine(ZvImage img, ZvMatrix lines, double rho, double theta, int thresh, double minLinelen, double maxLineGap)
{
    ZvTPFeatHoughLine taskParam_0 = {img, lines, rho, theta, thresh, minLinelen, maxLineGap};
    zv_mod_registerRun(zv_task_feat_houghLine, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvMatrix circles;
    double minDist;
    double param1;
    double param2;
    double minR;
    double maxR;
}ZvTPFeatHoughCircle;
void zv_task_feat_houghCircle(void *param)
{
    ZvTPFeatHoughCircle *p = (ZvTPFeatHoughCircle *)param;
    ZV_ERR_RUN(zv_feat_houghCircle(p->img, p->circles, p->minDist, p->param1, p->param2, p->minR, p->maxR));
}
void zv_featHoughCircle(ZvImage img, ZvMatrix circles, double minDist, double param1, double param2, double minR, double maxR)
{
    ZvTPFeatHoughCircle taskParam_0 = {img, circles, minDist, param1, param2, minR, maxR};
    zv_mod_registerRun(zv_task_feat_houghCircle, &taskParam_0, sizeof(taskParam_0));
}


//tk    tools
//tools：几何变换、几何特征、交点、夹角、拟合、插值
void zv_tkGetRotScaleMat(ZvMatrix mat, double cx, double cy, double angle, double scale)
{
    ZV_ERR_RUN(zv_tk_getRotScaleMat(mat, cx, cy, angle, scale));
}

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
}ZvTPTkGetRigid;
void zv_task_tk_getRigid(void *param)
{
    ZvTPTkGetRigid *p = (ZvTPTkGetRigid *)param;
    ZV_ERR_RUN(zv_tk_getRigid(p->mat, p->from, p->to));
}
void zv_tkGetRigid(ZvMatrix mat, double *from, double *to)
{
    ZvTPTkGetRigid taskParam_0 = {mat, from, to};
    zv_mod_registerRun(zv_task_tk_getRigid, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double xFrom;
    double yFrom;
    double angleFrom;
    double xTo;
    double yTo;
    double angleTo;
}ZvTPTkGetRigidVector;
void zv_task_tk_getRigidVector(void *param)
{
    ZvTPTkGetRigidVector *p = (ZvTPTkGetRigidVector *)param;
    ZV_ERR_RUN(zv_tk_getRigidVector(p->mat, p->xFrom, p->yFrom, p->angleFrom, p->xTo, p->yTo, p->angleTo));
}
void zv_tkGetRigidVector(ZvMatrix mat, double xFrom, double yFrom, double angleFrom, double xTo, double yTo, double angleTo)
{
    ZvTPTkGetRigidVector taskParam_0 = {mat, xFrom, yFrom, angleFrom, xTo, yTo, angleTo};
    zv_mod_registerRun(zv_task_tk_getRigidVector, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
}ZvTPTkGetSimilarity;
void zv_task_tk_getSimilarity(void *param)
{
    ZvTPTkGetSimilarity *p = (ZvTPTkGetSimilarity *)param;
    ZV_ERR_RUN(zv_tk_getSimilarity(p->mat, p->from, p->to));
}
void zv_tkGetSimilarity(ZvMatrix mat, double *from, double *to)
{
    ZvTPTkGetSimilarity taskParam_0 = {mat, from, to};
    zv_mod_registerRun(zv_task_tk_getSimilarity, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
}ZvTPTkGetAffine;
void zv_task_tk_getAffine(void *param)
{
    ZvTPTkGetAffine *p = (ZvTPTkGetAffine *)param;
    ZV_ERR_RUN(zv_tk_getAffine(p->mat, p->from, p->to));
}
void zv_tkGetAffine(ZvMatrix mat, double *from, double *to)
{
    ZvTPTkGetAffine taskParam_0 = {mat, from, to};
    zv_mod_registerRun(zv_task_tk_getAffine, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
    int maxIters;
    int *inliersId;
}ZvTPTkEstimateSimilarity;
void zv_task_tk_estimateSimilarity(void *param)
{
    ZvTPTkEstimateSimilarity *p = (ZvTPTkEstimateSimilarity *)param;
    ZV_ERR_RUN(zv_tk_estimateSimilarity(p->mat, p->from, p->to, p->maxIters, p->inliersId));
}
void zv_tkEstimateSimilarity(ZvMatrix mat, double *from, double *to, int maxIters, int *inliersId)
{
    ZvTPTkEstimateSimilarity taskParam_0 = {mat, from, to, maxIters, inliersId};
    zv_mod_registerRun(zv_task_tk_estimateSimilarity, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double * from;
    double * to;
    int maxIters;
    int * inliersId;
    double thresh;
}ZvTPTkEstimateAffine;
void zv_task_tk_estimateAffine(void *param)
{
    ZvTPTkEstimateAffine *p = (ZvTPTkEstimateAffine *)param;
    ZV_ERR_RUN(zv_tk_estimateAffine(p->mat, p->from, p->to, p->maxIters, p->inliersId, p->thresh));
}
void zv_tkEstimateAffine(ZvMatrix mat, double * from, double * to, int maxIters, int * inliersId, double thresh)
{
    ZvTPTkEstimateAffine taskParam_0 = {mat, from, to, maxIters, inliersId, thresh};
    zv_mod_registerRun(zv_task_tk_estimateAffine, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
    int ptNum;
}ZvTPTkAffineTrans;
void zv_task_tk_affineTrans(void *param)
{
    ZvTPTkAffineTrans *p = (ZvTPTkAffineTrans *)param;
    ZV_ERR_RUN(zv_tk_affineTrans(p->mat, p->from, p->to, p->ptNum));
}
void zv_tkAffineTrans(ZvMatrix mat, double *from, double *to, int ptNum)
{
    ZvTPTkAffineTrans taskParam_0 = {mat, from, to, ptNum};
    zv_mod_registerRun(zv_task_tk_affineTrans, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
}ZvTPTkGetProjective;
void zv_task_tk_getProjective(void *param)
{
    ZvTPTkGetProjective *p = (ZvTPTkGetProjective *)param;
    ZV_ERR_RUN(zv_tk_getProjective(p->mat, p->from, p->to));
}
void zv_tkGetProjective(ZvMatrix mat, double *from, double *to)
{
    ZvTPTkGetProjective taskParam_0 = {mat, from, to};
    zv_mod_registerRun(zv_task_tk_getProjective, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
    int num;
}ZvTPTkProjectiveTrans2d;
void zv_task_tk_projectiveTrans2d(void *param)
{
    ZvTPTkProjectiveTrans2d *p = (ZvTPTkProjectiveTrans2d *)param;
    ZV_ERR_RUN(zv_tk_projectiveTrans2d(p->mat, p->from, p->to, p->num));
}
void zv_tkProjectiveTrans2d(ZvMatrix mat, double *from, double *to, int num)
{
    ZvTPTkProjectiveTrans2d taskParam_0 = {mat, from, to, num};
    zv_mod_registerRun(zv_task_tk_projectiveTrans2d, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix mat;
    double *from;
    double *to;
    int num;
}ZvTPTkProjectiveTrans3d;
void zv_task_tk_projectiveTrans3d(void *param)
{
    ZvTPTkProjectiveTrans3d *p = (ZvTPTkProjectiveTrans3d *)param;
    ZV_ERR_RUN(zv_tk_projectiveTrans3d(p->mat, p->from, p->to, p->num));
}
void zv_tkProjectiveTrans3d(ZvMatrix mat, double *from, double *to, int num)
{
    ZvTPTkProjectiveTrans3d taskParam_0 = {mat, from, to, num};
    zv_mod_registerRun(zv_task_tk_projectiveTrans3d, &taskParam_0, sizeof(taskParam_0));
}

double zv_tkDistPoints(double x1, double y1, double x2, double y2)
{
    return zv_tk_distPoints(x1, y1, x2, y2);
}

double zv_tkDistPointLine(double px, double py, double lineX1, double lineY1, double lineX2, double lineY2)
{
    return zv_tk_distPointLine(px, py, lineX1, lineY1, lineX2, lineY2);
}

typedef struct
{
    ZvContour cont;
    double px;
    double py;
    double * dist;
}ZvTPTkDistPointCont;
void zv_task_tk_distPointCont(void *param)
{
    ZvTPTkDistPointCont *p = (ZvTPTkDistPointCont *)param;
    *p->dist = zv_tk_distPointCont(p->cont, p->px, p->py);
}
void zv_tkDistPointCont(ZvContour cont, double px, double py, double * dist)
{
    ZvTPTkDistPointCont taskParam_0 = {cont, px, py, dist};
    zv_mod_registerRun(zv_task_tk_distPointCont, &taskParam_0, sizeof(taskParam_0));
}

void zv_tkRect2Vertex(double cx, double cy, double size1, double size2, double angle, double *pt)
{
    ZV_ERR_RUN(zv_tk_rect2Vertex(cx, cy, size1, size2, angle, pt));
}

bool zv_tkIntersectLines(double l1x1, double l1y1, double l1x2, double l1y2, double l2x1, double l2y1, double l2x2, double l2y2, double *sectX, double *sectY)
{
    return zv_tk_intersectLines(l1x1, l1y1, l1x2, l1y2, l2x1, l2y1, l2x2, l2y2, sectX, sectY);
}

double zv_tkAngleLines(double line1X1, double line1Y1, double line1X2, double line1Y2, double line2X1, double line2Y1, double line2X2, double line2Y2)
{
    return zv_tk_angleLines(line1X1, line1Y1, line1X2, line1Y2, line2X1, line2Y1, line2X2, line2Y2);
}

double zv_tkAngleXAxis(double x1, double y1, double x2, double y2)
{
    return zv_tk_angleXAxis(x1, y1, x2, y2);
}

typedef struct
{
    ZvMatrix pts;
    double *line;
}ZvTPTkFitLine;
void zv_task_tk_fitLine(void *param)
{
    ZvTPTkFitLine *p = (ZvTPTkFitLine *)param;
    ZV_ERR_RUN(zv_tk_fitLine(p->pts, p->line));
}
void zv_tkFitLine(ZvMatrix pts, double *line)
{
    ZvTPTkFitLine taskParam_0 = {pts, line};
    zv_mod_registerRun(zv_task_tk_fitLine, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix pts;
    double *ellipse;
}ZvTPTkFitEllipse;
void zv_task_tk_fitEllipse(void *param)
{
    ZvTPTkFitEllipse *p = (ZvTPTkFitEllipse *)param;
    ZV_ERR_RUN(zv_tk_fitEllipse(p->pts, p->ellipse));
}
void zv_tkFitEllipse(ZvMatrix pts, double *ellipse)
{
    ZvTPTkFitEllipse taskParam_0 = {pts, ellipse};
    zv_mod_registerRun(zv_task_tk_fitEllipse, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    double R1X;
    double R1Y;
    double R1Size1;
    double R1Size2;
    double R1Angle;
    double R2X;
    double R2Y;
    double R2Size1;
    double R2Size2;
    double R2angle;
    ZvMatrix pts;
}ZvTPTkIntersectRect2;
void zv_task_tk_intersectRect2(void *param)
{
    ZvTPTkIntersectRect2 *p = (ZvTPTkIntersectRect2 *)param;
    ZV_ERR_RUN(zv_tk_intersectRect2(p->R1X, p->R1Y, p->R1Size1, p->R1Size2, p->R1Angle, p->R2X, p->R2Y, p->R2Size1, p->R2Size2, p->R2angle, p->pts));
}
void zv_tkIntersectRect2(double R1X, double R1Y, double R1Size1, double R1Size2, double R1Angle, double R2X, double R2Y, double R2Size1, double R2Size2, double R2angle, ZvMatrix pts)
{
    ZvTPTkIntersectRect2 taskParam_0 = {R1X, R1Y, R1Size1, R1Size2, R1Angle, R2X, R2Y, R2Size1, R2Size2, R2angle, pts};
    zv_mod_registerRun(zv_task_tk_intersectRect2, &taskParam_0, sizeof(taskParam_0));
}

void zv_tkLineToParam(double x1, double y1, double x2, double y2, double *lineParam)
{
    ZV_ERR_RUN(zv_tk_lineToParam(x1, y1, x2, y2, lineParam));
}

void zv_tkLineFromParam(double cx, double cy, double angle, double len, double *line)
{
    ZV_ERR_RUN(zv_tk_lineFromParam(cx, cy, angle, len, line));
}

typedef struct
{
    ZvMatrix pts;
    double *line;
    int method;
    double reps;
    double aeps;
}ZvTPTkFitLineEx;
void zv_task_tk_fitLineEx(void *param)
{
    ZvTPTkFitLineEx *p = (ZvTPTkFitLineEx *)param;
    ZV_ERR_RUN(zv_tk_fitLineEx(p->pts, p->line, p->method, p->reps, p->aeps));
}
void zv_tkFitLineEx(ZvMatrix pts, double *line, int method, double reps, double aeps)
{
    ZvTPTkFitLineEx taskParam_0 = {pts, line, method, reps, aeps};
    zv_mod_registerRun(zv_task_tk_fitLineEx, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvMatrix pts;
    double *ellipse;
    int method;
}ZvTPTkFitEllipseEx;
void zv_task_tk_fitEllipseEx(void *param)
{
    ZvTPTkFitEllipseEx *p = (ZvTPTkFitEllipseEx *)param;
    ZV_ERR_RUN(zv_tk_fitEllipseEx(p->pts, p->ellipse, p->method));
}
void zv_tkFitEllipseEx(ZvMatrix pts, double *ellipse, int method)
{
    ZvTPTkFitEllipseEx taskParam_0 = {pts, ellipse, method};
    zv_mod_registerRun(zv_task_tk_fitEllipseEx, &taskParam_0, sizeof(taskParam_0));
}


//dra模块，绘制图形和文字
int zv_draColor(int r, int g, int b)
{
    return zv_dra_color(r, g, b);
}

int zv_draColorName(char *colorName)
{
    return zv_dra_colorName(colorName);
}

typedef struct
{
    ZvImage img;
    int x;
    int y;
    int color;
}ZvTPDraPoint;
void zv_task_dra_point(void *param)
{
    ZvTPDraPoint *p = (ZvTPDraPoint *)param;
    ZV_ERR_RUN(zv_dra_point(p->img, p->x, p->y, p->color));
}
void zv_draPoint(ZvImage img, int x, int y, int color)
{
    ZvTPDraPoint taskParam_0 = {img, x, y, color};
    zv_mod_registerRun(zv_task_dra_point, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    int x1;
    int y1;
    int x2;
    int y2;
    int color;
}ZvTPDraLine;
void zv_task_dra_line(void *param)
{
    ZvTPDraLine *p = (ZvTPDraLine *)param;
    ZV_ERR_RUN(zv_dra_line(p->img, p->x1, p->y1, p->x2, p->y2, p->color));
}
void zv_draLine(ZvImage img, int x1, int y1, int x2, int y2, int color)
{
    ZvTPDraLine taskParam_0 = {img, x1, y1, x2, y2, color};
    zv_mod_registerRun(zv_task_dra_line, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    int x;
    int y;
    int w;
    int h;
    int color;
}ZvTPDraRect;
void zv_task_dra_rect(void *param)
{
    ZvTPDraRect *p = (ZvTPDraRect *)param;
    ZV_ERR_RUN(zv_dra_rect(p->img, p->x, p->y, p->w, p->h, p->color));
}
void zv_draRect(ZvImage img, int x, int y, int w, int h, int color)
{
    ZvTPDraRect taskParam_0 = {img, x, y, w, h, color};
    zv_mod_registerRun(zv_task_dra_rect, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    double cx;
    double cy;
    double size1;
    double size2;
    double angle;
    int color;
}ZvTPDraRect2;
void zv_task_dra_rect2(void *param)
{
    ZvTPDraRect2 *p = (ZvTPDraRect2 *)param;
    ZV_ERR_RUN(zv_dra_rect2(p->img, p->cx, p->cy, p->size1, p->size2, p->angle, p->color));
}
void zv_draRect2(ZvImage img, double cx, double cy, double size1, double size2, double angle, int color)
{
    ZvTPDraRect2 taskParam_0 = {img, cx, cy, size1, size2, angle, color};
    zv_mod_registerRun(zv_task_dra_rect2, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    int cx;
    int cy;
    int r;
    int color;
}ZvTPDraCircle;
void zv_task_dra_circle(void *param)
{
    ZvTPDraCircle *p = (ZvTPDraCircle *)param;
    ZV_ERR_RUN(zv_dra_circle(p->img, p->cx, p->cy, p->r, p->color));
}
void zv_draCircle(ZvImage img, int cx, int cy, int r, int color)
{
    ZvTPDraCircle taskParam_0 = {img, cx, cy, r, color};
    zv_mod_registerRun(zv_task_dra_circle, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    int cx;
    int cy;
    int size1;
    int size2;
    double angle;
    int color;
}ZvTPDraEllipse;
void zv_task_dra_ellipse(void *param)
{
    ZvTPDraEllipse *p = (ZvTPDraEllipse *)param;
    ZV_ERR_RUN(zv_dra_ellipse(p->img, p->cx, p->cy, p->size1, p->size2, p->angle, p->color));
}
void zv_draEllipse(ZvImage img, int cx, int cy, int size1, int size2, double angle, int color)
{
    ZvTPDraEllipse taskParam_0 = {img, cx, cy, size1, size2, angle, color};
    zv_mod_registerRun(zv_task_dra_ellipse, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    int cx;
    int cy;
    int size1;
    int size2;
    double angle;
    double angleStart;
    double angleEnd;
    int color;
}ZvTPDraEllipseArc;
void zv_task_dra_ellipseArc(void *param)
{
    ZvTPDraEllipseArc *p = (ZvTPDraEllipseArc *)param;
    ZV_ERR_RUN(zv_dra_ellipseArc(p->img, p->cx, p->cy, p->size1, p->size2, p->angle, p->angleStart, p->angleEnd, p->color));
}
void zv_draEllipseArc(ZvImage img, int cx, int cy, int size1, int size2, double angle, double angleStart, double angleEnd, int color)
{
    ZvTPDraEllipseArc taskParam_0 = {img, cx, cy, size1, size2, angle, angleStart, angleEnd, color};
    zv_mod_registerRun(zv_task_dra_ellipseArc, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvMatrix pts;
    bool isClosed;
    int color;
}ZvTPDraPolygon;
void zv_task_dra_polygon(void *param)
{
    ZvTPDraPolygon *p = (ZvTPDraPolygon *)param;
    ZV_ERR_RUN(zv_dra_polygon(p->img, p->pts, p->isClosed, p->color));
}
void zv_draPolygon(ZvImage img, ZvMatrix pts, bool isClosed, int color)
{
    ZvTPDraPolygon taskParam_0 = {img, pts, isClosed, color};
    zv_mod_registerRun(zv_task_dra_polygon, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvContour cont;
    int color;
}ZvTPDraContour;
void zv_task_dra_contour(void *param)
{
    ZvTPDraContour *p = (ZvTPDraContour *)param;
    ZV_ERR_RUN(zv_dra_contour(p->img, p->cont, p->color));
}
void zv_draContour(ZvImage img, ZvContour cont, int color)
{
    ZvTPDraContour taskParam_0 = {img, cont, color};
    zv_mod_registerRun(zv_task_dra_contour, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    int x;
    int y;
    int type;
    int size;
    int color;
}ZvTPDraMarker;
void zv_task_dra_marker(void *param)
{
    ZvTPDraMarker *p = (ZvTPDraMarker *)param;
    ZV_ERR_RUN(zv_dra_marker(p->img, p->x, p->y, p->type, p->size, p->color));
}
void zv_draMarker(ZvImage img, int x, int y, int type, int size, int color)
{
    ZvTPDraMarker taskParam_0 = {img, x, y, type, size, color};
    zv_mod_registerRun(zv_task_dra_marker, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    char * text;
    int x;
    int y;
    double scale;
    int color;
}ZvTPDraText;
void zv_task_dra_text(void *param)
{
    ZvTPDraText *p = (ZvTPDraText *)param;
    ZV_ERR_RUN(zv_dra_text(p->img, p->text, p->x, p->y, p->scale, p->color));
}
void zv_draText(ZvImage img, char * text, int x, int y, double scale, int color)
{
    ZvTPDraText taskParam_0 = {img, text, x, y, scale, color};
    zv_mod_registerRun(zv_task_dra_text, &taskParam_0, sizeof(taskParam_0));
}

typedef struct
{
    ZvImage img;
    ZvImage mask;
}ZvTPDraMask;
void zv_task_dra_mask(void *param)
{
    ZvTPDraMask *p = (ZvTPDraMask *)param;
    ZV_ERR_RUN(zv_dra_mask(p->img, p->mask));
}
void zv_draMask(ZvImage img, ZvImage mask)
{
    ZvTPDraMask taskParam_0 = {img, mask};
    zv_mod_registerRun(zv_task_dra_mask, &taskParam_0, sizeof(taskParam_0));
}


int zv_modInit(bool isBlocking)
{
    s_zv_mod_isBlocking = isBlocking;
    ZV_RUN_RTN(zv_cam_init());
    return ZV_ST_OK;
}

int zv_modExit()
{
    ZV_RUN_RTN(zv_cam_exit());
    return ZV_ST_OK;
}
