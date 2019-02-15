#ifndef ZV_MEAS_H
#define ZV_MEAS_H


enum _ZvMeasurerType
{
    ZV_MEAS_UNDEF,
    ZV_MEAS_RECT,
    ZV_MEAS_RECT2,
    ZV_MEAS_ARC,
    ZV_MEAS_LINE,
    ZV_MEAS_CIRCLE,
};

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _ZvRectMeas
{
    int type;
    double x;
    double y;
    double w;
    double h;
}ZvRectMeas;

typedef struct _ZvRect2Meas
{
    int type;
    int interp;
    double cx;
    double cy;
    double w;
    double h;
    double angle;
}ZvRect2Meas;

typedef struct _ZvArcMeas
{
    int type;
    int interp;
    double cx;
    double cy;
    double r;
    double annR;
    double startA;
    double extA;
}ZvArcMeas;

typedef struct _ZvLineMeas
{
    int mrType;
    int filterSize;
    ZvRect2Meas rt2Mr;
    int subNum;
    int subWidth;
    double thresh;
    int type;
    int select;
}ZvLineMeas;

typedef struct _ZvCircleMeas
{
    int mrType;
    int filterSize;
    ZvArcMeas arcMr;
    int subNum;
    int subWidth;
    double thresh;
    int type;
    int select;
}ZvCircleMeas;


inline int zv_meas_mrType(void *mr)
{
    if (NULL == mr)
        return ZV_MEAS_UNDEF;
    return ((ZvRectMeas*)mr)->type;
}

int zv_meas_genRect(void * mr, double x, double y, double width, double height);
int zv_meas_genRect2(void *mr, double cx, double cy, double width, double height,
    double angle, int interp);
int zv_meas_genArc(void *mr, double cx, double cy, double r, double startA, double extentA, double annR, int interp);
int zv_meas_projection(ZvImage img, ZvMatrix proj, void *mr);
//type边缘极性：0-白黑、1-黑白、2-所有；select边缘位置：0-第一点、1-最后点、2-最强点、3-所有点。
int zv_meas_pos(ZvImage img, ZvMatrix pts, void *mr, int filterSize, double thresh, int type, int select);
int zv_meas_pairs(ZvImage img, ZvMatrix pairs, void *mr, int filterSize, double thresh, int type, int select);

int zv_meas_genLineMr(void *mr, double cx, double cy, double width, double height,
    double angle, int interp, int subNum, int subWidth);
int zv_meas_genCircleMr(void *mr, double cx, double cy, double r, double startA,
    double extentA, double annR, int interp, int subNum, int subWidth);
int zv_meas_setMrAdvParam(void *mr, int filterSize, double thresh, int type, int select);
int zv_meas_getMrAdvParam(void *mr, int *filterSize, double *thresh, int *type, int *select);
int zv_meas_line(ZvImage img, void *mr, double *cx, double *cy, double *angle, double *length, ZvMatrix pts);
int zv_meas_circle(ZvImage img, void *mr, double *cx, double * cy, double *r, ZvMatrix pts);


#ifdef __cplusplus
}
#endif

#endif