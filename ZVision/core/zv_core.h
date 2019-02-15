#ifndef ZV_CORE_H
#define ZV_CORE_H

#ifdef __cplusplus
extern "C"{
#endif


// zv_image.cpp 中的函数声明
//获取图像结构信息
inline int zv_img_width(ZvImage img)
{
    return NULL == (img) ? 0 : ZV_ADP_IMG_GETM(img).cols;
}

inline int zv_img_height(ZvImage img)
{
    return NULL == (img) ? 0 : ZV_ADP_IMG_GETM(img).rows;
}

inline int zv_img_channels(ZvImage img)
{
    return NULL == (img) ? 0 : ZV_ADP_IMG_GETM(img).channels();
}

inline int zv_img_valueSize(ZvImage img)
{
    return NULL == (img) ? 0 : (int)ZV_ADP_IMG_GETM(img).elemSize1();
}

inline int zv_img_dataType(ZvImage img)
{
    return NULL == (img) ? ZV_PIXEL_UNDEF : g_zv_adp_depthFromCV[ZV_ADP_IMG_GETM(img).depth()];
}

inline int zv_img_dataSize(ZvImage img)
{
    cv::Mat src = ZV_ADP_IMG_GETM_CHK(img);
    return (int)(src.total() * src.elemSize());
}

inline bool zv_img_isEmpty(ZvImage img)
{
    return NULL == (img) ? true : ZV_ADP_IMG_GETM(img).empty();
}

int zv_img_genConst(ZvImage img, int width, int height, int type, int channel, double *element);
int zv_img_genData(ZvImage img, int width, int height, int type, int channel, void *data);
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

// zv_matrix.cpp 中的函数声明
inline int zv_mat_rows(ZvMatrix mat)
{
    return NULL == mat ? 0 : ZV_ADP_MAT_GETM(mat).rows;
}

inline int zv_mat_cols(ZvMatrix mat)
{
    return NULL == mat ? 0 : ZV_ADP_MAT_GETM(mat).cols;
}

inline bool zv_mat_isEmpty(ZvMatrix mat)
{
    return NULL == (mat) ? true : ZV_ADP_IMG_GETM(mat).empty();
}

int zv_mat_genConst(ZvMatrix mat, int rows, int cols, double value);
int zv_mat_genEye(ZvMatrix mat, int size);
int zv_mat_genData(ZvMatrix mat, int rows, int cols, double *data);
double zv_mat_getValue(ZvMatrix mat, int row, int col);
int zv_mat_setValue(ZvMatrix mat, int row, int col, double value);
int zv_mat_getRow(ZvMatrix mat, int row, double *data, int bufLen);
int zv_mat_setRow(ZvMatrix mat, int row, double *data);
int zv_mat_getCol(ZvMatrix mat, int col, double * data, int bufLen);
int zv_mat_setCol(ZvMatrix mat, int col, double * data);
int zv_mat_getData(ZvMatrix mat, double *data, int bufLen);
int zv_mat_setData(ZvMatrix mat, double *data);
int zv_mat_getSub(ZvMatrix mat, ZvMatrix sub, int x, int y, int width, int height);
int zv_mat_setSub(ZvMatrix mat, ZvMatrix sub, int x, int y);
int zv_mat_copy(ZvMatrix src, ZvMatrix dst);


inline int zv_cont_count(ZvContList contList)
{
    return NULL == contList ? 0 : (int)contList->size();
}

inline ZvContour zv_cont_getContour(ZvContList contList, int id)
{
    if (NULL == contList || id >= (int)contList->size())
    {
        return NULL;
    }

    return (*contList)[id];
}

inline int zv_cont_pointCount(ZvContour cont)
{
    return NULL == cont ? 0 : (int)cont->size();
}

int zv_cont_getPoint(ZvContour cont, int id, double *ptX, double *ptY);
int zv_cont_getPointsAll(ZvContour cont, double *pts, int *ptsLen);
int zv_cont_gen(ZvImage img, ZvContList contList, int mode, int appro);
int zv_cont_toMatrix(ZvContour cont, ZvMatrix mat);
int zv_cont_fromMatrix(ZvContour cont, ZvMatrix mat);

#ifdef __cplusplus
}
#endif

#endif
