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

//BASIC interpreter
INTERPRETER ZV_EXPORTS ZvImage zv_imgCreate(ZvMatInfo *info);
INTERPRETER ZV_EXPORTS int zv_imgRelease(ZvImage * img);
INTERPRETER ZV_EXPORTS ZvMatrix zv_matCreate(ZvMatInfo *info);
INTERPRETER ZV_EXPORTS int zv_matRelease(ZvMatrix * img);


//cam    camera / zv_camera.cpp
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

ZV_EXPORTS void zv_imgRgbToGray(ZvImage rgb, ZvImage gray, bool isRgba);
ZV_EXPORTS void zv_imgGrayToRgb(ZvImage gray, ZvImage rgb);
ZV_EXPORTS void zv_imgColorToRgb(ZvImage color, ZvImage rgb, int colorSpace);
ZV_EXPORTS void zv_imgRgbToColor(ZvImage rgb, ZvImage color, int colorSpace);
ZV_EXPORTS void zv_imgBayerToRgb(ZvImage bayer, ZvImage rgb, int bayerType);
ZV_EXPORTS void zv_imgScale(ZvImage src, ZvImage dst, int dType, double scale, double add);
ZV_EXPORTS void zv_imgSplit2(ZvImage src, ZvImage dst1, ZvImage dst2);
ZV_EXPORTS void zv_imgSplit3(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3);
ZV_EXPORTS void zv_imgSplit4(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3, ZvImage dst4);
ZV_EXPORTS void zv_imgMerge2(ZvImage src1, ZvImage src2, ZvImage dst);
ZV_EXPORTS void zv_imgMerge3(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage dst);
ZV_EXPORTS void zv_imgMerge4(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage src4, ZvImage dst);

//mat    core / zv_matrix.cpp
ZV_EXPORTS int zv_matRows(ZvMatrix mat);
ZV_EXPORTS int zv_matCols(ZvMatrix mat);
ZV_EXPORTS void zv_matGenConst(ZvMatrix mat, int rows, int cols, double value);
ZV_EXPORTS void zv_matGen





//basis    basis
//cont    core / zv_contour.cpp
//err    system / zv_error.cpp
//adp    system / zv_adapter.cpp
//sys    system 
//tk    tools
//match    match
//feat    feature
//meas    measure
//

ZV_EXPORTS bool zv_tkIntersectionLL(double l1x1, double l1y1, double l1x2, double l1y2,
    double l2x1, double l2y1, double l2x2, double l2y2, double *sectX, double *sectY);
ZV_EXPORTS double zv_tkAngleLine(double x1, double y1, double x2, double y2);


#ifdef __cplusplus
}
#endif

#endif
