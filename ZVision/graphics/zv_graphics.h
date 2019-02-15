#ifndef ZV_GRAPHICS_H
#define ZV_GRAPHICS_H


#ifdef __cplusplus
extern "C"
{
#endif

inline int zv_dra_color(int r, int g, int b)
{
    return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}

inline int zv_dra_color1(int r, int g, int b, int a)
{
    return (a << 24) + ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}

extern int g_zv_dra_colorMap[];
inline int zv_dra_colorId(int id)
{
    return g_zv_dra_colorMap[id % ZV_DEF_CLR_MAX];
}

int zv_dra_line(ZvImage img, double x1, double y1, double x2, double y2, int color);
int zv_dra_rect(ZvImage img, double x, double y, double w, double h, int color);
int zv_dra_rect2(ZvImage img, double cx, double cy, double width, double height, double angle, int color);
int zv_dra_circle(ZvImage img, double cx, double cy, double r, int color);
int zv_dra_ellipse(ZvImage img, double cx, double cy, double xR, double yR, double angle, int color);
int zv_dra_ellipseArc(ZvImage img, double cx, double cy, double xR, double yR, double angle, double angleStart, double angleEnd, int color);
int zv_dra_arrow(ZvImage img, double x1, double y1, double x2, double y2, int color, int size);
int zv_dra_polygon(ZvImage img, ZvMatrix pts, bool isClosed, int color);
int zv_dra_contour(ZvImage img, ZvContour cont, int color);
int zv_dra_marker(ZvImage img, double x, double y, int type, int size, int color);
int zv_dra_text(ZvImage img, char * text, double x, double y, double scale, int color);
int zv_dra_mask(ZvImage img, ZvImage mask);
int zv_dra_measurer(ZvImage img, void *mr, int color1, int color2);


#ifdef __cplusplus
}
#endif

#endif