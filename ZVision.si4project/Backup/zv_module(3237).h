#ifndef ZV_MODULE_H
#define ZV_MODULE_H


typedef enum _ZvCreateType
{
    ZV_CRT_NULL, //Mat()
    ZV_CRT_TYPE, //Mat(row, col, type)
    ZV_CRT_DATA, //Mat(row, col, type, data)
    ZV_CRT_CONST, //Mat(row, col, type, scalar)
}ZvCreateType;

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _ZvMatInfo
{
    ZvCreateType crtType;
    int width;
    int height;
    int type;
    void * data;
    double constant[ZV_SYS_CHANNELS_MAX];
}ZvMatInfo;

//库管理接口，解释器调用
/*************************************************************
Description:    //创建图像结构体并初始化内存区域
Input:          //info 创建图像参数，可传入NULL创建空图像
Output:         //无
Return:         //创建的图像
*************************************************************/
INTERPRETER ZV_EXPORTS ZvImage zv_imgCreate(ZvMatInfo *info ZV_CPP_DEF(NULL));
/*************************************************************
Description:    //释放图像内存
Input:          //img 待释放的图像指针
Output:         //无
Return:         //错误码
*************************************************************/
INTERPRETER ZV_EXPORTS int zv_imgRelease(ZvImage * img);
INTERPRETER ZV_EXPORTS ZvMatrix zv_matCreate(ZvMatInfo *info);
INTERPRETER ZV_EXPORTS int zv_matRelease(ZvMatrix * img);


//cam模块    camera/zv_camera.cpp
ZV_EXPORTS void zv_camScan(char *type);
ZV_EXPORTS int zv_camCount();
ZV_EXPORTS void zv_camGetInfo(int scanId, char *name, char *value, int maxValLen);
ZV_EXPORTS void zv_camOpen(int camId, int scanId);
ZV_EXPORTS int zv_camStatus(int camId);
ZV_EXPORTS void zv_camClose(int camId);
ZV_EXPORTS int zv_camPayloadSize(int camId);
ZV_EXPORTS void zv_camGrab(int camId, ZvImage img);
ZV_EXPORTS int zv_camGetIO(int camId);
ZV_EXPORTS void zv_camSetIO(int camId);
ZV_EXPORTS void zv_camGetROI(int camId, int *x, int *y, int *width, int *height);
ZV_EXPORTS void zv_camSetROI(int camId, int x, int y, int width, int height);
ZV_EXPORTS void zv_camGetExposure(int camId, double *time);
ZV_EXPORTS void zv_camSetExposure(int camId, double time);
ZV_EXPORTS void zv_camStartGrabbing(int camId, int bufCount);
ZV_EXPORTS bool zv_camIsGrabbing(int camId);
ZV_EXPORTS void zv_camRetrieve(int camId, int bufId, ZvImage img);
ZV_EXPORTS void zv_camReset(int camId);
ZV_EXPORTS void zv_camGetParam(int camId, char *name, char *value, int maxValLen);
ZV_EXPORTS void zv_camSetParam(int camId, char *name, char *value);

//file    file
ZV_EXPORTS void zv_fileReadImage(ZvImage img, char *name, int type);
ZV_EXPORTS void zv_fileWriteImage(ZvImage img, char *name, int *param, int num);
ZV_EXPORTS void zv_fileReadMatrix(ZvMatrix mat, char *name, int type);
ZV_EXPORTS void zv_fileWriteMatrix(ZvMatrix mat, char *name, int type);

//img    core / zv_image.cpp
ZV_EXPORTS int zv_imgWidth(ZvImage img);
ZV_EXPORTS int zv_imgHeight(ZvImage img);
ZV_EXPORTS int zv_imgChannels(ZvImage img);
ZV_EXPORTS int zv_imgDataType(ZvImage img);
ZV_EXPORTS int zv_imgStep(ZvImage img, int dimId);//考虑替换elemSize
ZV_EXPORTS void zv_imgGenConst(ZvImage img, int width, int height, int type,
    int channel, double *value);
ZV_EXPORTS void zv_imgGenData(ZvImage img, int width, int height, int type,
    int channel, double *data);
ZV_EXPORTS double zv_imgGetValue(ZvImage img, int x, int y, int channel);
ZV_EXPORTS void zv_imgSetValue(ZvImage img, int x, int y, int channel, double value);
ZV_EXPORTS void zv_imgGetElement(ZvImage img, int x, int y, double *element);
ZV_EXPORTS void zv_imgSetElement(ZvImage img, int x, int y, double *element);
ZV_EXPORTS void zv_imgGetData(ZvImage img, void *buf, int size, bool isAlign);
ZV_EXPORTS void zv_imgSetData(ZvImage img, void *buf);
ZV_EXPORTS void zv_imgGetSub(ZvImage img, ZvImage sub, int x, int y, int width, int height);
ZV_EXPORTS void zv_imgSetSub(ZvImage img, ZvImage sub, int x, int y);
ZV_EXPORTS void zv_imgConvert(ZvImage src, ZvImage dst, int dstType, double mult, double add);
ZV_EXPORTS void zv_imgRgbToGray(ZvImage rgb, ZvImage gray, bool isRgba);
ZV_EXPORTS void zv_imgGrayToRgb(ZvImage gray, ZvImage rgb);
ZV_EXPORTS void zv_imgColorToRgb(ZvImage color, ZvImage rgb, int colorSpace);
ZV_EXPORTS void zv_imgRgbToColor(ZvImage rgb, ZvImage color, int colorSpace);
ZV_EXPORTS void zv_imgBayerToRgb(ZvImage bayer, ZvImage rgb, int bayerType);
ZV_EXPORTS void zv_imgSplit2(ZvImage src, ZvImage dst1, ZvImage dst2);
ZV_EXPORTS void zv_imgSplit3(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3);
ZV_EXPORTS void zv_imgSplit4(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3, ZvImage dst4);
ZV_EXPORTS void zv_imgMerge2(ZvImage src1, ZvImage src2, ZvImage dst);
ZV_EXPORTS void zv_imgMerge3(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage dst);
ZV_EXPORTS void zv_imgMerge4(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage src4, ZvImage dst);
ZV_EXPORTS void zv_imgHist(ZvImage img, ZvMatrix hist, int size, double low, double upper);
ZV_EXPORTS void zv_imgHistRgb(ZvImage img, ZvMatrix hist);

//mat    core / zv_matrix.cpp
ZV_EXPORTS int zv_matRows(ZvMatrix mat);
ZV_EXPORTS int zv_matCols(ZvMatrix mat);
ZV_EXPORTS void zv_matGenConst(ZvMatrix mat, int rows, int cols, double value);
ZV_EXPORTS void zv_matGenEye(ZvMatrix mat, int size);
ZV_EXPORTS void zv_matGenData(ZvMatrix mat, int rows, int cols, double *data);
ZV_EXPORTS double zv_matGetValue(ZvMatrix mat, int row, int col);
ZV_EXPORTS void zv_matSetValue(ZvMatrix mat, int row, int col, double value);
ZV_EXPORTS void zv_matGetRow(ZvMatrix mat, int row, double *data);
ZV_EXPORTS void zv_matSetRow(ZvMatrix mat, int row, double *data);
ZV_EXPORTS void zv_matGetCol(ZvMatrix mat, int col, double * data);
ZV_EXPORTS void zv_matSetCol(ZvMatrix mat, int col, double * data);
ZV_EXPORTS void zv_matGetData(ZvMatrix mat, double *data);
ZV_EXPORTS void zv_matSetData(ZvMatrix mat, double *data);
ZV_EXPORTS void zv_matGetSub(ZvMatrix mat, ZvMatrix sub, int x, int y, int width, int height);
ZV_EXPORTS void zv_matSetSub(ZvMatrix mat, ZvMatrix sub, int x, int y);
ZV_EXPORTS void zv_matTranspose(ZvMatrix src, ZvMatrix dst);
ZV_EXPORTS void zv_matInvert(ZvMatrix src, ZvMatrix dst, int method);
ZV_EXPORTS void zv_matMult(ZvMatrix mat1, ZvMatrix mat2, ZvMatrix dst);
ZV_EXPORTS void zv_matEigen(ZvMatrix src, ZvMatrix eigenvalues, ZvMatrix eigenvectors, bool isSymmetric);


//cont    core / zv_contour.cpp
ZV_EXPORTS int zv_contCount(ZvContList contList);
ZV_EXPORTS void zv_contGetContour(ZvContList contList, int id, ZvContour cont);
ZV_EXPORTS int zv_contPointCount(ZvContour cont);
ZV_EXPORTS void zv_contGetPoint(ZvContour cont, int id, double *pt);
ZV_EXPORTS void zv_contGetPointsAll(ZvContour cont, double *pts);
ZV_EXPORTS void zv_contGenContours(ZvImage img, ZvContList contList, bool isExter);
ZV_EXPORTS void zv_contToMatrix(ZvContour cont, ZvMatrix mat);
ZV_EXPORTS void zv_contFromMatrix(ZvContour cont, ZvMatrix mat);
ZV_EXPORTS void zv_contArea(ZvContour cont, bool isOriented, double *area);
ZV_EXPORTS void zv_contLength(ZvContour cont, bool isClosed, double *len);
ZV_EXPORTS void zv_contCenter(ZvContour cont, double *center);
ZV_EXPORTS void zv_contIsConvex(ZvContour cont, bool *isConvex);
ZV_EXPORTS void zv_contCircularity(ZvContour cont, double *value);
ZV_EXPORTS void zv_contCompactness(ZvContour cont, double *value);
ZV_EXPORTS void zv_contSmallestRect(ZvContour cont, int *rect);
ZV_EXPORTS void zv_contSmallestRect2(ZvContour cont, double *rect2);
ZV_EXPORTS void zv_contSmallestCircle(ZvContour cont, double *circle);
ZV_EXPORTS void zv_contConvexHull(ZvContour cont, ZvMatrix hull);
ZV_EXPORTS void zv_contApproxPoly(ZvContour cont, ZvMatrix poly, double epsilon, bool isClosed);
ZV_EXPORTS void zv_contSort(ZvContList contlist, int *sortedId, int type,
    bool isInc, bool isRowFirst);
ZV_EXPORTS void zv_contSelect(ZvContList contlist, ZvContList selected,
    char *feature, double min, double max);
ZV_EXPORTS void zv_contHoughLine(ZvImage img, ZvMatrix lines, double rho,
    double theta, int thresh, double minLinelen, double maxLineGap);
ZV_EXPORTS void zv_contHoughCircle(ZvImage img, ZvMatrix circles,
    double minDist, double param1, double param2, double minR, double maxR);
ZV_EXPORTS void zv_contGenContoursEx(ZvImage img, ZvContList contList, ZvMatrix hierarchy,
    int mode, int appro, int offsetX, int offsetY);
ZV_EXPORTS void zv_contMoments(ZvContour cont, int type, int orderX, int orderY, double *m);
ZV_EXPORTS void zv_contHuMoments(double *ncm, double *hu);
ZV_EXPORTS void zv_contAffine(ZvContour contSrc, ZvContour contDst, ZvMatrix mat);
ZV_EXPORTS void zv_contPerspective(ZvContour contSrc, ZvContour contDst, ZvMatrix mat);


//tk    tools
ZV_EXPORTS void zv_tkGetRotScaleMat(ZvMatrix mat, double cx, double cy, double angle, double scale);
ZV_EXPORTS void zv_tkGetRigid(ZvMatrix mat, double *from, double *to);
ZV_EXPORTS void zv_tkGetRigidVector(ZvMatrix mat, double xFrom, double yFrom,
    double angleFrom, double xTo, double yTo, double angleTo);
ZV_EXPORTS void zv_tkGetSimilarity(ZvMatrix mat, double *from, double *to);
ZV_EXPORTS void zv_tkGetAffine(ZvMatrix mat, double *from, double *to);
ZV_EXPORTS void zv_tkEstimateSimilarity(ZvMatrix mat, double *from, double *to,
    int maxIters, int *inliersId);
ZV_EXPORTS void zv_tkEstimateAffine(ZvMatrix mat, double * from, double * to,
    int maxIters, int * inliersId, double thresh);
ZV_EXPORTS void zv_tkAffineTrans(ZvMatrix mat, double *from, double *to, int ptNum);
ZV_EXPORTS void zv_tkGetProjective(ZvMatrix mat, double *from, double *to);
ZV_EXPORTS void zv_tkProjectiveTrans2d(ZvMatrix mat, double *from, double *to, int num);
ZV_EXPORTS void zv_tkProjectiveTrans3d(ZvMatrix mat, double *from, double *to, int num);

ZV_EXPORTS double zv_tkDistPoints(double x1, double y1, double x2, double y2);
ZV_EXPORTS double zv_tkDistPointLine(double px, double py,
    double lineX1, double lineY1, double lineX2, double lineY2);
ZV_EXPORTS double zv_tkDistPointCont(ZvContour cont, double px, double py);
ZV_EXPORTS void zv_tkRect2Vertex(double cx, double cy, double size1, double size2,
    double angle, double *pt);
ZV_EXPORTS bool zv_tkIntersectLines(double l1x1, double l1y1, double l1x2, double l1y2,
    double l2x1, double l2y1, double l2x2, double l2y2, double *sectX, double *sectY);
ZV_EXPORTS double zv_tkAngleLines(double line1X1, double line1Y1, double line1X2,
    double line1Y2, double line2X1, double line2Y1, double line2X2, double line2Y2);
ZV_EXPORTS double zv_tkAngleXAxis(double x1, double y1, double x2, double y2);
ZV_EXPORTS void zv_tkFitLine(ZvMatrix pts, double *line);
ZV_EXPORTS void zv_tkFitEllipse(ZvMatrix pts, double *ellipse);
ZV_EXPORTS void zv_tkIntersectRect2(double R1X, double R1Y, double R1Size1, double R1Size2,
    double R1Angle, double R2X, double R2Y, double R2Size1, double R2Size2, double R2angle, ZvMatrix pts);
ZV_EXPORTS void zv_tkLineToParam(double x1, double y1, double x2, double y2, double *lineParam);
ZV_EXPORTS void zv_tkLineFromParam(double cx, double cy, double angle, double len, double *line);
ZV_EXPORTS void zv_tkFitLineEx(ZvMatrix pts, double *line, int method, double reps, double aeps);
ZV_EXPORTS void zv_tkFitEllipseEx(ZvMatrix pts, double *ellipse, int method);


//match    match
ZV_EXPORTS void zv_matchFastTempl(ZvImage img, ZvImage templ, int *x, int *y, ZvImage mask);
ZV_EXPORTS void zv_matchBestTempl(ZvImage img, ZvImage templ, double minScore,
    double *x, double *y, double *score, int method, bool isSubPix);
ZV_EXPORTS void zv_matchMultiTempl(ZvImage img, ZvImage templ, ZvMatrix matches,
    double minScore, int method, bool isSubPix);


//meas    measure
ZV_EXPORTS void zv_measGenRect(void * mr, int x, int y, int width, int height, int filterSize);
ZV_EXPORTS void zv_measGenRect2(void *mr, double cx, double cy, double size1,
    double size2, double angle, int filterSize, int interp);
ZV_EXPORTS void zv_measGenArc(void *mr, double cx, double cy, double r, double angleStart,
    double angleEnd, double rAnnulus, int filterSize, int interp);
ZV_EXPORTS void zv_measProjection(ZvImage img, ZvMatrix proj, void *mr);
ZV_EXPORTS void zv_measPos(ZvImage img, ZvMatrix pts, void *mr, int thresh, int type, int select);
ZV_EXPORTS void zv_measPairs(ZvImage img, ZvMatrix pairs, void *mr, int thresh,
    int type, int select);
ZV_EXPORTS void zv_measLines(ZvImage img, ZvMatrix lines, void *mr, int thresh,
    int type, int select, int subNum, int subWidth);
ZV_EXPORTS void zv_measCircle(ZvImage img, ZvMatrix circles, void *mr,
    int thresh, int type, int select, int subNum, int subWidth);

typedef ZvImage ZvObject;
//arith  op
ZV_EXPORTS void zv_arithCopy(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithAbs(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithAbsDiff(ZvObject src1, ZvObject src2, ZvObject dst, double mult);
ZV_EXPORTS void zv_arithAdd(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add);
ZV_EXPORTS void zv_arithSub(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add);
ZV_EXPORTS void zv_arithMul(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add);
ZV_EXPORTS void zv_arithDiv(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add);
ZV_EXPORTS void zv_arithScale(ZvObject src, ZvObject dst, double mult, double add);
ZV_EXPORTS void zv_arithAddWeighted(ZvObject src1, ZvObject src2, ZvObject dst,
    double weight1, double weight2, double add);
ZV_EXPORTS void zv_arithSin(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithCos(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithTan(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithAsin(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithAcos(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithAtan(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithAtan2(ZvObject src1, ZvObject src2, ZvObject dst);
ZV_EXPORTS void zv_arithExp(ZvObject src, ZvObject dst, int baseType);
ZV_EXPORTS void zv_arithLog(ZvObject src, ZvObject dst, int baseType);
ZV_EXPORTS void zv_arithPow(ZvObject src, ZvObject dst, double exponent);
ZV_EXPORTS void zv_arithSqrt(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithCompare(ZvObject src1, ZvObject src2, ZvImage dst, int op);
ZV_EXPORTS void zv_arithAnd(ZvImage src1, ZvImage src2, ZvImage dst);
ZV_EXPORTS void zv_arithOr(ZvImage src1, ZvImage src2, ZvImage dst);
ZV_EXPORTS void zv_arithNot(ZvImage src, ZvImage dst);
ZV_EXPORTS void zv_arithXor(ZvImage src1, ZvImage src2, ZvImage dst);

ZV_EXPORTS void zv_arithMax(ZvObject src1, ZvObject src2, ZvObject dst);
ZV_EXPORTS void zv_arithMin(ZvObject src1, ZvObject src2, ZvObject dst);
ZV_EXPORTS void zv_arithMaxS(ZvObject src1, ZvObject dst, double *scalar);
ZV_EXPORTS void zv_arithMinS(ZvObject src1, ZvObject dst, double *scalar);

ZV_EXPORTS void zv_arithMagnitude(ZvObject x, ZvObject y, ZvObject magnitude);
ZV_EXPORTS void zv_arithPhase(ZvObject x, ZvObject y, ZvObject angle);

ZV_EXPORTS void zv_arithZeroCount(ZvObject src, int *cnt);
ZV_EXPORTS void zv_arithSum(ZvObject src, double * sum);
ZV_EXPORTS void zv_arithSumRow(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithSumCol(ZvObject src, ZvObject dst);
ZV_EXPORTS void zv_arithMean(ZvObject src, double *mean);
ZV_EXPORTS void zv_arithMeanSdev(ZvObject src, double *mean, double *stdDev);
ZV_EXPORTS void zv_arithMinMaxLoc(ZvObject src, double *value, int *pos);
ZV_EXPORTS void zv_arithNorm(ZvObject mat, int normType, double *value);


//ip iproc imgproc
ZV_EXPORTS void zv_ipMirror(ZvImage src, ZvImage dst, int type);
ZV_EXPORTS void zv_ipRotate(ZvImage src, ZvImage dst, double angle, int interp);
ZV_EXPORTS void zv_ipZoom(ZvImage src, ZvImage dst, double scaleW, double scaleH, int interp);
ZV_EXPORTS void zv_ipResize(ZvImage src, ZvImage dst, int dstW, int dstH, int interp);
ZV_EXPORTS void zv_ipAffine(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW,
    int dstH, int interp, char *border);
ZV_EXPORTS void zv_ipPerspective(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW,
    int dstH, int interp, char *border);
    
ZV_EXPORTS void zv_ipIntegral(ZvImage src, ZvImage dst, int dstType);
ZV_EXPORTS void zv_ipIntegral2(ZvImage src, ZvImage dst, ZvImage dstSqrt, int dstType);
ZV_EXPORTS void zv_ipMoments(ZvImage binImg, int type, int orderX, int orderY, double *m);
ZV_EXPORTS void zv_ipMedianBlur(ZvImage src, ZvImage dst, int size);
ZV_EXPORTS void zv_ipMeanBlur(ZvImage src, ZvImage dst, int size);
ZV_EXPORTS void zv_ipGaussBlur(ZvImage src, ZvImage dst, int size);
ZV_EXPORTS void zv_ipBilateralFilter(ZvImage src, ZvImage dst, double sigmaSpace, double sigmaColor);
ZV_EXPORTS void zv_ipSobel(ZvImage src, ZvImage dst, int dx, int dy, int size);
ZV_EXPORTS void zv_ipScharr(ZvImage src, ZvImage dst, int dx, int dy);
ZV_EXPORTS void zv_ipLaplace(ZvImage src, ZvImage dst, int size);

ZV_EXPORTS void zv_ipCanny(ZvImage img, ZvImage dst, double thresh1, double thresh2, int size);
ZV_EXPORTS void zv_ipEqualizeHist(ZvImage src, ZvImage dst);
ZV_EXPORTS void zv_dilate(ZvImage src, ZvImage dst, int seWidth, int seHeight);
ZV_EXPORTS void zv_erode(ZvImage src, ZvImage dst, int seWidth, int seHeight);
ZV_EXPORTS void zv_opening(ZvImage src, ZvImage dst, int seWidth, int seHeight);
ZV_EXPORTS void zv_closing(ZvImage src, ZvImage dst, int seWidth, int seHeight);

/************************************************************************
ZV_EXPORTS void zv_ipGaborKernel(ZvImage kernel, int width, int height,
    double sigma, double theta, double lambd, double gamma, double psi);
ZV_EXPORTS void zv_ipDerivKernel(ZvImage kernelX, ZvImage kernelY, int dX, int dY, int size);
ZV_EXPORTS void zv_ipDct(ZvImage src, ZvImage dst);
ZV_EXPORTS void zv_ipIdct(ZvImage src, ZvImage dst);
ZV_EXPORTS void zv_ipFilter(ZvImage src, ZvImage kernel, ZvImage dst,
    int dstType, int anchorX, int anchorY, double delta, char * border);
ZV_EXPORTS void zv_ipSepFilter(ZvImage src, ZvImage kernelX, ZvImage kernelY, ZvImage dst,
    int dstType, int anchorX, int anchorY, double delta, char *border);
ZV_EXPORTS void zv_ipFft(ZvImage src, ZvImage dstRe, ZvImage dstIm);
ZV_EXPORTS void zv_ipIfft(ZvImage srcRe, ZvImage srcIm, ZvImage dst);
ZV_EXPORTS void zv_ipPyramid(ZvImage src, ZvImage *dst, int level, char *border);
ZV_EXPORTS void zv_ipPyramidDown(ZvImage src, ZvImage dst, double factor, char *border);
ZV_EXPORTS void zv_ipPyramidUp(ZvImage src, ZvImage dst, double factor, char *border);
ZV_EXPORTS void zv_ipMorphSe(ZvImage kernel, int shape, int sizeX, int sizeY, int anchorX, int anchorY);
ZV_EXPORTS void zv_ipMorphology(ZvImage src, ZvImage dst, ZvImage kernel,
    int op, int anchorX, int anchorY, int iter, char *border);
ZV_EXPORTS void zv_ipLabel(ZvImage src, ZvImage label, int connectivity, int labelType);
ZV_EXPORTS void zv_ipLabelStat(ZvImage src, ZvImage label, ZvMatrix stat,
    ZvMatrix centroid, int connectivity, int labelType);
**************************************************************************/

ZV_EXPORTS void zv_ipThreshold(ZvImage src, ZvImage dst, double thresh0, double thresh1, bool isInv);
ZV_EXPORTS void zv_ipAdpThreshold(ZvImage src, ZvImage thresh, ZvImage dst, double offset, bool isInv);
ZV_EXPORTS void zv_ipAutoThreshold(ZvImage src, ZvImage dst, bool isInv);

//err    system / zv_error.cpp
//sys    system 
bool g_zv_sys_DrawFill;
int g_zv_sys_LineWidth;
int g_zv_sys_LineType;
ZV_EXPORTS int zv_sysGetParamInt(char *name);
ZV_EXPORTS void zv_sysSetParamInt(char *name, int value);
ZV_EXPORTS double zv_sysGetParamDouble(char *name);
ZV_EXPORTS void zv_sysSetParamDouble(char *name, double value);
ZV_EXPORTS void zv_sysGetParamString(char *name, char *value, int maxValLen);
ZV_EXPORTS void zv_sysSetParamString(char *name, char *value);

//dra
ZV_EXPORTS int zv_draColor(int r, int g, int b);
ZV_EXPORTS int zv_draColorName(char *colorName);
ZV_EXPORTS int zv_draPoint(ZvImage img, int x, int y, int color);
ZV_EXPORTS int zv_draLine(ZvImage img, int x1, int y1, int x2, int y2, int color);
ZV_EXPORTS int zv_draRect(ZvImage img, int x, int y, int w, int h, int color);
ZV_EXPORTS int zv_draRect2(ZvImage img, double cx, double cy, double size1, double size2, double angle, int color);
ZV_EXPORTS int zv_draCircle(ZvImage img, int cx, int cy, int r, int color);
ZV_EXPORTS int zv_draEllipse (ZvImage img, int cx, int cy, int size1, int size2, double angle, int color);
ZV_EXPORTS int zv_draEllipseArc(ZvImage img, int cx, int cy, int size1, int size2, double angle,
    double angleStart, double angleEnd, int color);
ZV_EXPORTS int zv_draPolygon(ZvImage img, ZvMatrix pts, bool isClosed, int color);
ZV_EXPORTS int zv_draContour(ZvImage img, ZvContour cont, int color);
ZV_EXPORTS int zv_draMarker(ZvImage img, int x, int y, int type, int size, int color);
ZV_EXPORTS int zv_draText(ZvImage img, char * text, int x, int y, double scale, int color);
ZV_EXPORTS int zv_draMask(ZvImage img, ZvImage mask);


#ifdef __cplusplus
}
#endif

#endif
