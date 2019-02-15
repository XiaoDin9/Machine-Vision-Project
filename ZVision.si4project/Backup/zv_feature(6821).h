#ifndef ZV_FEATURE_H
#define ZV_FEATURE_H

#define ZV_FCONT_AREA           "Area"
#define ZV_FCONT_CIRCULARITY    "Circularity"
#define ZV_FCONT_CONVEXITY      "Convexity"
#define ZV_FCONT_INERTIA        "Inertia"

#ifdef __cplusplus
extern "C"
{
#endif

int zvGenContours(ZvImage img, ZvContList conts, bool isExter, int offsetX, int offsetY);
int zvSelectContours(ZvContList conts, ZvContList selected, char *feature, double minVal, double maxVal);
int zvFilterContours(ZvContList conts, char *feature, double minVal, double maxVal);
int zvSmallestRect(ZvContour cont, double *cx, double *cy, double *width, double *height, double *angle);

int zvBlobLabel(ZvImage src, ZvImage label, int connectivity, int labelType);

#ifdef __cplusplus
}
#endif

#endif