#ifndef ZV_MEAS_H
#define ZV_MEAS_H


#ifdef __cplusplus
extern "C"
{
#endif

    enum _ZvMeasurerType
    {
        ZV_MEAS_RECT,
        ZV_MEAS_RECT2,
        ZV_MEAS_ARC,
    };

    typedef struct _ZvRectMeas
    {
        int type;
        int filterSize;
        double x;
        double y;
        double w;
        double h;
    }ZvRectMeas;

    typedef struct _ZvRect2Meas
    {
        int type;
        int filterSize;
        double cx;
        double cy;
        double w;
        double h;
        double angle;
        int interp;
    }ZvRect2Meas;

    typedef struct _ZvArcMeas
    {
        int type;
        int filterSize;
        double cx;
        double cy;
        double r;
        double aStart;
        double aEnd;
        double annulusR;
        int interp;
    }ZvArcMeas;


int zv_meas_genRect(void * mr, double x, double y, double width, double height, int filterSize);
int zv_meas_genRect2(void *mr, double cx, double cy, double size1, double size2,
    double angle, int filterSize, int interp);
int zv_meas_genArc(void *mr, double cx, double cy, double r, double angleStart, double angleEnd, double rAnnulus, int filterSize, int interp);
int zv_meas_projection(ZvImage img, ZvMatrix proj, void *mr);
int zv_meas_pos(ZvImage img, ZvMatrix pts, void *mr, int thresh, int type, int select);
int zv_meas_pairs(ZvImage img, ZvMatrix pairs, void *mr, int thresh, int type, int select);
//type边缘极性：0-黑白、1-白黑、2-所有；select边缘位置：0-第一点、1-最后点、2-最强点、3-所有点。
int zv_meas_lines(ZvImage img, ZvMatrix lines, void *mr, int thresh, int type, int select, int subNum, int subWidth);
int zv_meas_circle(ZvImage img, ZvMatrix circles, void *mr, int thresh, int type, int select, int subNum, int subWidth);

int zv_ip_arcMeasurer(ZvImage src, ZvImage Roi, double cX, double cY, double r, double edgeWidth, double aStart, double aEnd, double annulusR, int interp);
int zv_ip_rect2Measurer(ZvImage src, ZvImage Roi, double x, double y, double width, double height, double angle);

#ifdef __cplusplus
}
#endif

#endif