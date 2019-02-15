#ifndef ZV_TOOLS_H
#define ZV_TOOLS_H

#ifdef __cplusplus
extern "C"
{
#endif

int zv_tk_getSimilarityParam(ZvMatrix mat, double x, double y, double angle, double scale);
int zv_tk_getRigid(ZvMatrix mat, double *srcPos, double *dstPos);
int zv_tk_getRigidVector(ZvMatrix mat, double x1, double y1, double angle1,
    double x2, double y2, double angle2);
int zv_tk_getSimilarity(ZvMatrix mat, double *from, double *to);
int zv_tk_getAffine(ZvMatrix mat, double *from, double *to);
int zv_tk_estimateSimilarity(ZvMatrix srcPos, ZvMatrix dstPos, ZvMatrix mat,
    double thresh, double confidence, bool * isInliers);
int zv_tk_estimateAffine(ZvMatrix srcPos, ZvMatrix dstPos, ZvMatrix mat,
    double thresh, double confidence, bool * isInliers);
int zv_tk_affineTrans(ZvMatrix mat, double *from, double *to, int ptNum);
int zv_tk_getProjective(ZvMatrix mat, double *from, double *to);
int zv_tk_projectiveTrans2d(ZvMatrix mat, double *from, double *to, int num);
int zv_tk_projectiveTrans3d(ZvMatrix mat, double *from, double *to, int num);

inline double zv_tk_distancePP(double x1, double y1, double x2, double y2)
{
    x2 = x2 - x1;
    y2 = y2 - y1;
    return sqrt(x2*x2 + y2*y2);
}

double zv_tk_distancePL(double px, double py, double lineX1, double lineY1, double lineX2, double lineY2);
double zv_tk_distancePS(double px, double py, double lineX1, double lineY1, double lineX2, double lineY2);
double zv_tk_distanceContP(ZvContour cont, double px, double py);
int zv_tk_rect2Vertex(double cx, double cy, double size1, double size2, double angle, double *pt);
int zv_tk_intersectPL(double px, double py,
    double x1, double y1, double x2, double y2, double *sectX, double *sectY);
bool zv_tk_intersectLL(double l1x1, double l1y1, double l1x2, double l1y2,
    double l2x1, double l2y1, double l2x2, double l2y2, double *sectX, double *sectY);
double zv_tk_angleLines(double line1X1, double line1Y1, double line1X2, double line1Y2,
    double line2X1, double line2Y1, double line2X2, double line2Y2);
double zv_tk_angleLineX(double x1, double y1, double x2, double y2);
int zv_tk_fitLine2D(ZvMatrix pts, double *x, double *y, double *angle, double *len);
//int zv_tk_fitLine3D(ZvMatrix pts, double *param1, double *param2, double *param3,
//    double *param4, double *param5, double *param6);
int zv_tk_fitCircle(ZvMatrix pts, double *cx, double *cy, double *r);
int zv_tk_fitEllipse(ZvMatrix pts, double *cx, double *cy, double *size1, double *size2, double *angle);
int zv_tk_intersectRect2(ZvMatrix pts, double R1X, double R1Y, double R1W, double R1H,
    double R1Angle, double R2X, double R2Y, double R2W, double R2H, double R2Angle);
int zv_tk_lineToParam(double x1, double y1, double x2, double y2,
    double *cx, double *cy, double *angle, double *len);
int zv_tk_lineFromParam(double cx, double cy, double angle, double len,
    double *x1, double *y1, double *x2, double *y2);
int zv_tk_fitLineEx(ZvMatrix pts, double *line, int method, double reps, double aeps);
int zv_tk_fitEllipseEx(ZvMatrix pts, double *cx, double *cy, double *size1,
    double *size2, double *angle, int method);

//低次项系数在前
int zv_tk_fitPolyn(ZvMatrix pts, int order, double *param);
int zv_tk_subPixInterp1d(double * pts, int ptNum, double &pos, double &value);

//x/y/z依次排列
int zv_tk_subPixInterp2d(double * pts, int ptNum, double &posX, double &posY, double &value);

#ifdef __cplusplus
}
#endif

#endif
