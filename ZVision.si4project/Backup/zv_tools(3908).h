#ifndef ZV_TOOLS_H
#define ZV_TOOLS_H

#ifdef __cplusplus
extern "C"
{
#endif

int zv_tk_getSimilarityParam(ZvMatrix mat, double x, double y, double angle, double scale);
int zv_tk_getRigid(ZvMatrix mat, double *srcPos, double *dstPos);
int zv_tk_getRigidVector(ZvMatrix mat, double x1, double y1, double angle1, double x2, double y2, double angle2);
int zv_tk_estimateSimilarity(ZvMatrix srcPos, ZvMatrix dstPos, ZvMatrix mat, ZvMatrix inliers, int maxIters);
int zv_tk_affineTrans(ZvMatrix mat, double *srcPt, double *dstPt, int ptNum);


#ifdef __cplusplus
}
#endif

#endif