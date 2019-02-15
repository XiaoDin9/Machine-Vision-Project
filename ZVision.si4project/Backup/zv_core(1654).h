#ifndef ZV_CORE_H
#define ZV_CORE_H

#ifdef __cplusplus
extern "C"{
#endif

// zv_image.cpp 中的函数声明
//获取图像结构信息
inline int zv_img_width(ZvImage img) { return NULL == (img) ? 0 : ZV_ADP_IMG_GETM(img).cols; };
inline int zv_img_height(ZvImage img) { return NULL == (img) ? 0 : ZV_ADP_IMG_GETM(img).rows; };
inline int zv_img_channels(ZvImage img) { return NULL == (img) ? 0 : ZV_ADP_IMG_GETM(img).channels(); };
inline int zv_img_valueSize(ZvImage img) { return NULL == (img) ? 0 : (int)ZV_ADP_IMG_GETM(img).elemSize1();};
inline int zv_img_type(ZvImage img) { return NULL == (img) ? 0 : ZV_ADP_IMG_GETM(img).depth(); };
inline int zv_img_dataSize(ZvImage img)
{
    cv::Mat src = ZV_ADP_IMG_GETM_CHK(img);
    return (int)(src.total() * src.elemSize());
};

int zv_img_getData(ZvImage img, void * buf, int size, bool isAlign);
int zv_img_getSub(ZvImage src, ZvImage dst, int x, int y, int width, int height);
int zv_img_copy(ZvImage src, ZvImage dst);

// zv_matrix.cpp 中的函数声明
int zvMatrixRows(ZvMatrix mat);
int zvMatrixCols(ZvMatrix mat);
int zvGenMatrix(ZvMatrix mat, int rows, int cols, double value);
int zvGenMatrixIdentity(ZvMatrix mat, int size);
int zvGenMatrixData(ZvMatrix mat, int rows, int cols, double * data);
double zvMatrixVal(ZvMatrix mat, int row, int col);
int zvMatrixRow(ZvMatrix src, int id, double * buf, int bufSize);
int zvMatrixCol(ZvMatrix src, int id, double * buf, int bufSize);
int zvSubMatrix(ZvMatrix src, ZvMatrix dst, int x, int y, int width, int height);

int zvContoursCount(ZvContList list);
ZvContour zvGetContour(ZvContList list, int contId);
int zvContourPointCount(ZvContour contour);
int zvGetContourPoint(ZvContour contour, int ptId, int * pt);
int zvGetContourData(ZvContList list, int contId, int *ptBuf, int bufLen);


#ifdef __cplusplus
}
#endif

#endif