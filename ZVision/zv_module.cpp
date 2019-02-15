/*************************************************************
该文件为自动生成文件，如果修改请注意备份，重新生成将被覆盖
////由zv_module_gen.py生成，需要zv_module_templ.py模块内的
////固定字符串定义和zv_module.h文件内的函数声明，声明需要符
////合特定格式
*************************************************************/

#include "zv_private.h"
#include "zv_module.h"
#include "system/zv_task_param.h"
#include "system/zv_task.h"
#include "system/zv_system.h"
#include "core/zv_core.h"
#include "basis/zv_basis.h"
#include "camera/zv_camera.h"
#include "file/zv_file.h"
#include "match/zv_match.h"
#include "measure/zv_meas.h"
#include "feature/zv_feature.h"
#include "tools/zv_tools.h"
#include "graphics/zv_graphics.h"


ZvImage zv_modImgCreate()
{
    return new _ZvImage();
}

ZvModel zv_zvModelCreate()
{
    return new _ZvModel();        //会调用_ZvModel 类的无参构造函数;
}

ZvImage zv_modImgCreateData(int width, int height, int depth, int cn, void *data)
{
    return new _ZvImage(height, width, CV_MAKE_TYPE(depth, cn), data);
}

ZvImage zv_modImgCreateConst(int width, int height, int depth, int cn, double value)
{
    return new _ZvImage(height, width, CV_MAKE_TYPE(depth, cn), value);
}

int zv_modImgRelease(ZvImage * img)
{
    ZV_CHK_NULL1(img);
    if (NULL != *img)
    {
        delete *img;
        *img = NULL;
    }
    return ZV_ST_OK;
}

ZvMatrix zv_modMatCreate()
{
    return new _ZvMatrix();
}

ZvMatrix zv_modMatCreateData(int width, int height, void *data)
{
    return new _ZvMatrix(height, width, CV_64F, data);
}

ZvMatrix zv_modMatCreateConst(int width, int height, double value)
{
    return new _ZvMatrix(height, width, CV_64F, value);
}

int zv_modMatRelease(ZvMatrix * mat)
{
    ZV_CHK_NULL1(mat);
    if (NULL != *mat)
    {
        delete *mat;
        *mat = NULL;
    }
    return ZV_ST_OK;
}

ZvContList zv_modContListCreate()
{
    return new _ZvContList();
}

int zv_modContListRelease(ZvContList * contList)
{
    ZV_CHK_NULL1(contList);
    if (NULL != *contList)
    {
        delete *contList;
        *contList = NULL;
    }
    return ZV_ST_OK;
}

ZvContour zv_modContCreate()
{
    return new _ZvContour();
}

int zv_modContRelease(ZvContour * contour)
{
    ZV_CHK_NULL1(contour);
    if (NULL != *contour)
    {
        delete *contour;
        *contour = NULL;
    }
    return ZV_ST_OK;
}


//sys system：参数、时间、日志、调试
char *zv_errStatusStr(int status)
{
    return zv_err_statusStr(status);
}

int zv_sysGetParamInt(char *name)
{
    int value = 0;
    ZV_ERR_RUN(zv_sys_getParamInt(name, &value));
    return value;
}

void zv_sysSetParamInt(char *name, int value)
{
    ZV_ERR_RUN(zv_sys_setParamInt(name, value));
}

double zv_sysGetParamDouble(char *name)
{
    double value = 0;
    ZV_ERR_RUN(zv_sys_getParamDouble(name, &value));
    return value;
}

void zv_sysSetParamDouble(char *name, double value)
{
    ZV_ERR_RUN(zv_sys_setParamDouble(name, value));
}

void zv_sysGetParamString(char *name, char *value, int maxValLen)
{
    ZV_ERR_RUN(zv_sys_getParamString(name, value, maxValLen));
}

void zv_sysSetParamString(char *name, char *value)
{
    ZV_ERR_RUN(zv_sys_setParamString(name, value));
}

double zv_sysGetTimeUs()
{
    return zv_sys_getTimeUs();
}

double zv_sysGetTimeMs()
{
    return zv_sys_getTimeMs();
}

int64 zv_sysGetTickCount()
{
    return zv_sys_getTickCount();
}

double zv_sysGetTickFreq()
{
    return zv_sys_getTickFreq();
}


//cam
int zv_camScan(char *type)
{
    ZvTPCamScan taskParam_0 = {type};
    return zv_task_registerRun(zv_task_cam_scan, &taskParam_0, sizeof(taskParam_0));
}

int zv_camCount()
{
    return zv_cam_count();
}

int zv_camGetInfo(int scanId, int prop, char *value, int maxValLen)
{
    ZvTPCamGetInfo taskParam_0 = {scanId, prop, value, maxValLen};
    return zv_task_registerRun(zv_task_cam_getInfo, &taskParam_0, sizeof(taskParam_0));
}

int zv_camOpen(int camId, int scanId)
{
    ZvTPCamOpen taskParam_0 = {camId, scanId};
    return zv_task_registerRun(zv_task_cam_open, &taskParam_0, sizeof(taskParam_0));
}

int zv_camStatus(int camId, int *status)
{
    ZvTPCamStatus taskParam_0 = {camId, status};
    return zv_task_registerRun(zv_task_cam_status, &taskParam_0, sizeof(taskParam_0));
}

int zv_camClose(int camId)
{
    ZvTPCamClose taskParam_0 = {camId};
    return zv_task_registerRun(zv_task_cam_close, &taskParam_0, sizeof(taskParam_0));
}

int zv_camPayloadSize(int camId, int *size)
{
    ZvTPCamPayloadSize taskParam_0 = {camId, size};
    return zv_task_registerRun(zv_task_cam_payloadSize, &taskParam_0, sizeof(taskParam_0));
}

int zv_camGrab(ZvImage img, int camId)
{
    ZvTPCamGrab taskParam_0 = {img, camId};
    return zv_task_registerRun(zv_task_cam_grab, &taskParam_0, sizeof(taskParam_0));
}

int zv_camGetIO(int camId)
{
    return zv_cam_getIO(camId);
}

void zv_camSetIO(int camId, int offset)
{
    ZV_ERR_RUN(zv_cam_setIO(camId, offset));
}

int zv_camGetROI(int camId, int *camROI)
{
    ZvTPCamGetROI taskParam_0 = {camId, camROI};
    return zv_task_registerRun(zv_task_cam_getROI, &taskParam_0, sizeof(taskParam_0));
}

int zv_camSetROI(int camId, int x, int y, int width, int height)
{
    ZvTPCamSetROI taskParam_0 = {camId, x, y, width, height};
    return zv_task_registerRun(zv_task_cam_setROI, &taskParam_0, sizeof(taskParam_0));
}

int zv_camGetExposure(int camId, double *time)
{
    ZvTPCamGetExposure taskParam_0 = {camId, time};
    return zv_task_registerRun(zv_task_cam_getExposure, &taskParam_0, sizeof(taskParam_0));
}

int zv_camSetExposure(int camId, double time)
{
    ZvTPCamSetExposure taskParam_0 = {camId, time};
    return zv_task_registerRun(zv_task_cam_setExposure, &taskParam_0, sizeof(taskParam_0));
}

int zv_camStartGrabbing(int camId, int bufCount)
{
    ZvTPCamStartGrabbing taskParam_0 = {camId, bufCount};
    return zv_task_registerRun(zv_task_cam_startGrabbing, &taskParam_0, sizeof(taskParam_0));
}

int zv_camIsGrabbing(int camId, int *isGrabbing)
{
    ZvTPCamIsGrabbing taskParam_0 = {camId, isGrabbing};
    return zv_task_registerRun(zv_task_cam_isGrabbing, &taskParam_0, sizeof(taskParam_0));
}

int zv_camRetrieve(ZvImage img, int camId, int bufId)
{
    ZvTPCamRetrieve taskParam_0 = {img, camId, bufId};
    return zv_task_registerRun(zv_task_cam_retrieve, &taskParam_0, sizeof(taskParam_0));
}

int zv_camReset(int camId)
{
    ZvTPCamReset taskParam_0 = {camId};
    return zv_task_registerRun(zv_task_cam_reset, &taskParam_0, sizeof(taskParam_0));
}

int zv_camGetParam(int camId, char *name, char *value, int maxValLen)
{
    ZvTPCamGetParam taskParam_0 = {camId, name, value, maxValLen};
    return zv_task_registerRun(zv_task_cam_getParam, &taskParam_0, sizeof(taskParam_0));
}

int zv_camSetParam(int camId, char *name, char *value)
{
    ZvTPCamSetParam taskParam_0 = {camId, name, value};
    return zv_task_registerRun(zv_task_cam_setParam, &taskParam_0, sizeof(taskParam_0));
}


//file
int zv_fileReadImage(ZvImage img, char *fileName, int type)
{
    ZvTPFileReadImage taskParam_0 = {img, fileName, type};
    return zv_task_registerRun(zv_task_file_readImage, &taskParam_0, sizeof(taskParam_0));
}

int zv_fileWriteImage(ZvImage img, char *fileName, int param)
{
    ZvTPFileWriteImage taskParam_0 = {img, fileName, param};
    return zv_task_registerRun(zv_task_file_writeImage, &taskParam_0, sizeof(taskParam_0));
}

int zv_fileReadMatrix(ZvMatrix mat, char *fileName, char *nodeName, int type)
{
    ZvTPFileReadMatrix taskParam_0 = {mat, fileName, nodeName, type};
    return zv_task_registerRun(zv_task_file_readMatrix, &taskParam_0, sizeof(taskParam_0));
}

int zv_fileWriteMatrix(ZvMatrix mat, char *fileName, char *nodeName, int type)
{
    ZvTPFileWriteMatrix taskParam_0 = {mat, fileName, nodeName, type};
    return zv_task_registerRun(zv_task_file_writeMatrix, &taskParam_0, sizeof(taskParam_0));
}


//img    core/zv_image.cpp
int zv_imgWidth(ZvImage img)
{
    return zv_img_width(img);
}

int zv_imgHeight(ZvImage img)
{
    return zv_img_height(img);
}

int zv_imgChannels(ZvImage img)
{
    return zv_img_channels(img);
}

int zv_imgDataType(ZvImage img)
{
    return zv_img_dataType(img);
}

int zv_imgValueSize(ZvImage img)
{
    return zv_img_valueSize(img);
}

int zv_imgDataSize(ZvImage img)
{
    return zv_img_dataSize(img);
}

int zv_imgIsEmpty(ZvImage img)
{
    return zv_img_isEmpty(img);
}

int zv_imgGenConst(ZvImage img, int width, int height, int type, int channel, double *element)
{
    ZvTPImgGenConst taskParam_0 = {img, width, height, type, channel, element};
    return zv_task_registerRun(zv_task_img_genConst, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgGenData(ZvImage img, int width, int height, int type, int channel, void *data)
{
    ZvTPImgGenData taskParam_0 = {img, width, height, type, channel, data};
    return zv_task_registerRun(zv_task_img_genData, &taskParam_0, sizeof(taskParam_0));
}

double zv_imgGetValue(ZvImage img, int x, int y, int channel)
{
    return zv_img_getValue(img, x, y, channel);
}

void zv_imgSetValue(ZvImage img, int x, int y, int channel, double value)
{
    ZV_ERR_RUN(zv_img_setValue(img, x, y, channel, value));
}

void zv_imgGetElement(ZvImage img, int x, int y, double *element)
{
    ZV_ERR_RUN(zv_img_getElement(img, x, y, element));
}

void zv_imgSetElement(ZvImage img, int x, int y, double *element)
{
    ZV_ERR_RUN(zv_img_setElement(img, x, y, element));
}

int zv_imgGetData(ZvImage img, void *buf, int size, bool isAlign)
{
    ZvTPImgGetData taskParam_0 = {img, buf, size, isAlign};
    return zv_task_registerRun(zv_task_img_getData, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgSetData(ZvImage img, void *buf)
{
    ZvTPImgSetData taskParam_0 = {img, buf};
    return zv_task_registerRun(zv_task_img_setData, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgGetSub(ZvImage img, ZvImage sub, int x, int y, int width, int height)
{
    ZvTPImgGetSub taskParam_0 = {img, sub, x, y, width, height};
    return zv_task_registerRun(zv_task_img_getSub, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgSetSub(ZvImage img, ZvImage sub, int x, int y)
{
    ZvTPImgSetSub taskParam_0 = {img, sub, x, y};
    return zv_task_registerRun(zv_task_img_setSub, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgConvert(ZvImage src, ZvImage dst, int dstType, double mult, double add)
{
    ZvTPImgConvert taskParam_0 = {src, dst, dstType, mult, add};
    return zv_task_registerRun(zv_task_img_convert, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgCopy(ZvImage src, ZvImage dst)
{
    ZvTPImgCopy taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_img_copy, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgSplit2(ZvImage src, ZvImage dst1, ZvImage dst2)
{
    ZvTPImgSplit2 taskParam_0 = {src, dst1, dst2};
    return zv_task_registerRun(zv_task_img_split2, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgSplit3(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3)
{
    ZvTPImgSplit3 taskParam_0 = {src, dst1, dst2, dst3};
    return zv_task_registerRun(zv_task_img_split3, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgSplit4(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3, ZvImage dst4)
{
    ZvTPImgSplit4 taskParam_0 = {src, dst1, dst2, dst3, dst4};
    return zv_task_registerRun(zv_task_img_split4, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgMerge2(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZvTPImgMerge2 taskParam_0 = {src1, src2, dst};
    return zv_task_registerRun(zv_task_img_merge2, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgMerge3(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage dst)
{
    ZvTPImgMerge3 taskParam_0 = {src1, src2, src3, dst};
    return zv_task_registerRun(zv_task_img_merge3, &taskParam_0, sizeof(taskParam_0));
}

int zv_imgMerge4(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage src4, ZvImage dst)
{
    ZvTPImgMerge4 taskParam_0 = {src1, src2, src3, src4, dst};
    return zv_task_registerRun(zv_task_img_merge4, &taskParam_0, sizeof(taskParam_0));
}


//mat    core/zv_matrix.cpp
int zv_matRows(ZvMatrix mat)
{
    return zv_mat_rows(mat);
}

int zv_matCols(ZvMatrix mat)
{
    return zv_mat_cols(mat);
}

int zv_matIsEmpty(ZvMatrix mat)
{
    return zv_mat_isEmpty(mat);
}

int zv_matGenConst(ZvMatrix mat, int rows, int cols, double value)
{
    ZvTPMatGenConst taskParam_0 = {mat, rows, cols, value};
    return zv_task_registerRun(zv_task_mat_genConst, &taskParam_0, sizeof(taskParam_0));
}

int zv_matGenEye(ZvMatrix mat, int size)
{
    ZvTPMatGenEye taskParam_0 = {mat, size};
    return zv_task_registerRun(zv_task_mat_genEye, &taskParam_0, sizeof(taskParam_0));
}

int zv_matGenData(ZvMatrix mat, int rows, int cols, double *data)
{
    ZvTPMatGenData taskParam_0 = {mat, rows, cols, data};
    return zv_task_registerRun(zv_task_mat_genData, &taskParam_0, sizeof(taskParam_0));
}

double zv_matGetValue(ZvMatrix mat, int row, int col)
{
    return zv_mat_getValue(mat, row, col);
}

void zv_matSetValue(ZvMatrix mat, int row, int col, double value)
{
    ZV_ERR_RUN(zv_mat_setValue(mat, row, col, value));
}

int zv_matGetRow(ZvMatrix mat, int row, double *data, int bufLen)
{
    ZvTPMatGetRow taskParam_0 = {mat, row, data, bufLen};
    return zv_task_registerRun(zv_task_mat_getRow, &taskParam_0, sizeof(taskParam_0));
}

int zv_matSetRow(ZvMatrix mat, int row, double *data)
{
    ZvTPMatSetRow taskParam_0 = {mat, row, data};
    return zv_task_registerRun(zv_task_mat_setRow, &taskParam_0, sizeof(taskParam_0));
}

int zv_matGetCol(ZvMatrix mat, int col, double * data, int bufLen)
{
    ZvTPMatGetCol taskParam_0 = {mat, col, data, bufLen};
    return zv_task_registerRun(zv_task_mat_getCol, &taskParam_0, sizeof(taskParam_0));
}

int zv_matSetCol(ZvMatrix mat, int col, double * data)
{
    ZvTPMatSetCol taskParam_0 = {mat, col, data};
    return zv_task_registerRun(zv_task_mat_setCol, &taskParam_0, sizeof(taskParam_0));
}

int zv_matGetData(ZvMatrix mat, double *data, int bufLen)
{
    ZvTPMatGetData taskParam_0 = {mat, data, bufLen};
    return zv_task_registerRun(zv_task_mat_getData, &taskParam_0, sizeof(taskParam_0));
}

int zv_matSetData(ZvMatrix mat, double *data)
{
    ZvTPMatSetData taskParam_0 = {mat, data};
    return zv_task_registerRun(zv_task_mat_setData, &taskParam_0, sizeof(taskParam_0));
}

int zv_matGetSub(ZvMatrix mat, ZvMatrix sub, int x, int y, int width, int height)
{
    ZvTPMatGetSub taskParam_0 = {mat, sub, x, y, width, height};
    return zv_task_registerRun(zv_task_mat_getSub, &taskParam_0, sizeof(taskParam_0));
}

int zv_matSetSub(ZvMatrix mat, ZvMatrix sub, int x, int y)
{
    ZvTPMatSetSub taskParam_0 = {mat, sub, x, y};
    return zv_task_registerRun(zv_task_mat_setSub, &taskParam_0, sizeof(taskParam_0));
}

int zv_matCopy(ZvMatrix src, ZvMatrix dst)
{
    ZvTPMatCopy taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_mat_copy, &taskParam_0, sizeof(taskParam_0));
}


//cont   core/zv_contour.cpp
int zv_contCount(ZvContList contList)
{
    return zv_cont_count(contList);
}

ZvContour zv_contGetContour(ZvContList contList, int id)
{
    return zv_cont_getContour(contList, id);
}

int zv_contPointCount(ZvContour cont)
{
    return zv_cont_pointCount(cont);
}

void zv_contGetPoint(ZvContour cont, int id, double *pt)
{
    ZV_ERR_RUN(zv_cont_getPoint(cont, id, pt, pt+1));
}

int zv_contGetPointsAll(ZvContour cont, double *pts, int *ptsLen)
{
    ZvTPContGetPointsAll taskParam_0 = {cont, pts, ptsLen};
    return zv_task_registerRun(zv_task_cont_getPointsAll, &taskParam_0, sizeof(taskParam_0));
}

int zv_contGen(ZvImage img, ZvContList contList, int mode, int appro)
{
    ZvTPContGen taskParam_0 = {img, contList, mode, appro};
    return zv_task_registerRun(zv_task_cont_gen, &taskParam_0, sizeof(taskParam_0));
}

int zv_contToMatrix(ZvContour cont, ZvMatrix mat)
{
    ZvTPContToMatrix taskParam_0 = {cont, mat};
    return zv_task_registerRun(zv_task_cont_toMatrix, &taskParam_0, sizeof(taskParam_0));
}

int zv_contFromMatrix(ZvContour cont, ZvMatrix mat)
{
    ZvTPContFromMatrix taskParam_0 = {cont, mat};
    return zv_task_registerRun(zv_task_cont_fromMatrix, &taskParam_0, sizeof(taskParam_0));
}

int zv_contArea(ZvContour cont, bool isOriented, double *area)
{
    ZvTPContArea taskParam_0 = {cont, isOriented, area};
    return zv_task_registerRun(zv_task_cont_area, &taskParam_0, sizeof(taskParam_0));
}

int zv_contLength(ZvContour cont, bool isClosed, double *len)
{
    ZvTPContLength taskParam_0 = {cont, isClosed, len};
    return zv_task_registerRun(zv_task_cont_length, &taskParam_0, sizeof(taskParam_0));
}

int zv_contCenter(ZvContour cont, double *center)
{
    ZvTPContCenter taskParam_0 = {cont, center};
    return zv_task_registerRun(zv_task_cont_center, &taskParam_0, sizeof(taskParam_0));
}

int zv_contIsConvex(ZvContour cont, int *isConvex)
{
    ZvTPContIsConvex taskParam_0 = {cont, isConvex};
    return zv_task_registerRun(zv_task_cont_isConvex, &taskParam_0, sizeof(taskParam_0));
}

int zv_contConvexity(ZvContour cont, double *convexity)
{
    ZvTPContConvexity taskParam_0 = {cont, convexity};
    return zv_task_registerRun(zv_task_cont_convexity, &taskParam_0, sizeof(taskParam_0));
}

int zv_contCircularity(ZvContour cont, double *value)
{
    ZvTPContCircularity taskParam_0 = {cont, value};
    return zv_task_registerRun(zv_task_cont_circularity, &taskParam_0, sizeof(taskParam_0));
}

int zv_contCompactness(ZvContour cont, double *value)
{
    ZvTPContCompactness taskParam_0 = {cont, value};
    return zv_task_registerRun(zv_task_cont_compactness, &taskParam_0, sizeof(taskParam_0));
}

int zv_contSmallestRect(ZvContour cont, int *rect)
{
    ZvTPContSmallestRect taskParam_0 = {cont, rect};
    return zv_task_registerRun(zv_task_cont_smallestRect, &taskParam_0, sizeof(taskParam_0));
}

int zv_contSmallestRect2(ZvContour cont, double *rect2)
{
    ZvTPContSmallestRect2 taskParam_0 = {cont, rect2};
    return zv_task_registerRun(zv_task_cont_smallestRect2, &taskParam_0, sizeof(taskParam_0));
}

int zv_contSmallestCircle(ZvContour cont, double *circle)
{
    ZvTPContSmallestCircle taskParam_0 = {cont, circle};
    return zv_task_registerRun(zv_task_cont_smallestCircle, &taskParam_0, sizeof(taskParam_0));
}

int zv_contEllipticAxis(ZvContour cont, double *major, double * minor, double *angle)
{
    ZvTPContEllipticAxis taskParam_0 = {cont, major, minor, angle};
    return zv_task_registerRun(zv_task_cont_ellipticAxis, &taskParam_0, sizeof(taskParam_0));
}

int zv_contConvexHullIdx(ZvContour cont, int *ptIdx, int *bufLen)
{
    ZvTPContConvexHullIdx taskParam_0 = {cont, ptIdx, bufLen};
    return zv_task_registerRun(zv_task_cont_convexHullIdx, &taskParam_0, sizeof(taskParam_0));
}

int zv_contApproxPoly(ZvContour cont, ZvContour poly, double epsilon, bool isClosed)
{
    ZvTPContApproxPoly taskParam_0 = {cont, poly, epsilon, isClosed};
    return zv_task_registerRun(zv_task_cont_approxPoly, &taskParam_0, sizeof(taskParam_0));
}

int zv_contSort(ZvContList contlist, int feature, bool isInc)
{
    ZvTPContSort taskParam_0 = {contlist, feature, isInc};
    return zv_task_registerRun(zv_task_cont_sort, &taskParam_0, sizeof(taskParam_0));
}

int zv_contFilter(ZvContList contlist, int feature, double min, double max, bool isInvert)
{
    ZvTPContFilter taskParam_0 = {contlist, feature, min, max, isInvert};
    return zv_task_registerRun(zv_task_cont_filter, &taskParam_0, sizeof(taskParam_0));
}

int zv_contMoments(ZvContour cont, int type, int orderX, int orderY, double *m)
{
    ZvTPContMoments taskParam_0 = {cont, type, orderX, orderY, m};
    return zv_task_registerRun(zv_task_cont_moments, &taskParam_0, sizeof(taskParam_0));
}

int zv_contHuMoments(ZvContour cont, double *hu)
{
    ZvTPContHuMoments taskParam_0 = {cont, hu};
    return zv_task_registerRun(zv_task_cont_huMoments, &taskParam_0, sizeof(taskParam_0));
}

int zv_contAffine(ZvContour contSrc, ZvContour contDst, ZvMatrix mat)
{
    ZvTPContAffine taskParam_0 = {contSrc, contDst, mat};
    return zv_task_registerRun(zv_task_cont_affine, &taskParam_0, sizeof(taskParam_0));
}

int zv_contPerspective(ZvContour contSrc, ZvContour contDst, ZvMatrix mat)
{
    ZvTPContPerspective taskParam_0 = {contSrc, contDst, mat};
    return zv_task_registerRun(zv_task_cont_perspective, &taskParam_0, sizeof(taskParam_0));
}


//arith  basic/   zv_arithmetic.cpp    zv_stat.cpp'
//zv_arithmetic.cpp  代数（矩阵图像的四则运算、逆矩阵、逐点函数运算、逻辑、比较、矩阵运算、LUT）
//zv_stat.cpp  统计（直方图、均值方差、）
int zv_arithAbs(ZvObject src, ZvObject dst)
{
    ZvTPArithAbs taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_abs, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithAbsDiff(ZvObject src1, ZvObject src2, ZvObject dst, double mult)
{
    ZvTPArithAbsDiff taskParam_0 = {src1, src2, dst, mult};
    return zv_task_registerRun(zv_task_arith_absDiff, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithAdd(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add)
{
    ZvTPArithAdd taskParam_0 = {src1, src2, dst, mult, add};
    return zv_task_registerRun(zv_task_arith_add, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithSub(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add)
{
    ZvTPArithSub taskParam_0 = {src1, src2, dst, mult, add};
    return zv_task_registerRun(zv_task_arith_sub, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMul(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add)
{
    ZvTPArithMul taskParam_0 = {src1, src2, dst, mult, add};
    return zv_task_registerRun(zv_task_arith_mul, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithDiv(ZvObject src1, ZvObject src2, ZvObject dst, double mult, double add)
{
    ZvTPArithDiv taskParam_0 = {src1, src2, dst, mult, add};
    return zv_task_registerRun(zv_task_arith_div, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithScale(ZvObject src, ZvObject dst, double mult, double add)
{
    ZvTPArithScale taskParam_0 = {src, dst, mult, add};
    return zv_task_registerRun(zv_task_arith_scale, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithAddWeighted(ZvObject src1, ZvObject src2, ZvObject dst, double weight1, double weight2, double add)
{
    ZvTPArithAddWeighted taskParam_0 = {src1, src2, dst, weight1, weight2, add};
    return zv_task_registerRun(zv_task_arith_addWeighted, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithSin(ZvObject src, ZvObject dst)
{
    ZvTPArithSin taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_sin, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithCos(ZvObject src, ZvObject dst)
{
    ZvTPArithCos taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_cos, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithTan(ZvObject src, ZvObject dst)
{
    ZvTPArithTan taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_tan, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithAsin(ZvObject src, ZvObject dst)
{
    ZvTPArithAsin taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_asin, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithAcos(ZvObject src, ZvObject dst)
{
    ZvTPArithAcos taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_acos, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithAtan(ZvObject src, ZvObject dst)
{
    ZvTPArithAtan taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_atan, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithAtan2(ZvObject y, ZvObject x, ZvObject dst)
{
    ZvTPArithAtan2 taskParam_0 = {y, x, dst};
    return zv_task_registerRun(zv_task_arith_atan2, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithExp(ZvObject src, ZvObject dst, int baseType)
{
    ZvTPArithExp taskParam_0 = {src, dst, baseType};
    return zv_task_registerRun(zv_task_arith_exp, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithLog(ZvObject src, ZvObject dst, int baseType)
{
    ZvTPArithLog taskParam_0 = {src, dst, baseType};
    return zv_task_registerRun(zv_task_arith_log, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithPow(ZvObject src, ZvObject dst, double exponent)
{
    ZvTPArithPow taskParam_0 = {src, dst, exponent};
    return zv_task_registerRun(zv_task_arith_pow, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithSqrt(ZvObject src, ZvObject dst)
{
    ZvTPArithSqrt taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_sqrt, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithCompare(ZvObject src1, ZvObject src2, ZvImage dst, int op)
{
    ZvTPArithCompare taskParam_0 = {src1, src2, dst, op};
    return zv_task_registerRun(zv_task_arith_compare, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMax(ZvObject src1, ZvObject src2, ZvObject dst)
{
    ZvTPArithMax taskParam_0 = {src1, src2, dst};
    return zv_task_registerRun(zv_task_arith_max, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMin(ZvObject src1, ZvObject src2, ZvObject dst)
{
    ZvTPArithMin taskParam_0 = {src1, src2, dst};
    return zv_task_registerRun(zv_task_arith_min, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMaxS(ZvObject src1, ZvObject dst, double *scalar)
{
    ZvTPArithMaxS taskParam_0 = {src1, dst, scalar};
    return zv_task_registerRun(zv_task_arith_maxS, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMinS(ZvObject src1, ZvObject dst, double *scalar)
{
    ZvTPArithMinS taskParam_0 = {src1, dst, scalar};
    return zv_task_registerRun(zv_task_arith_minS, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMagnitude(ZvObject x, ZvObject y, ZvObject magnitude)
{
    ZvTPArithMagnitude taskParam_0 = {x, y, magnitude};
    return zv_task_registerRun(zv_task_arith_magnitude, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithPhase(ZvObject x, ZvObject y, ZvObject radian)
{
    ZvTPArithPhase taskParam_0 = {x, y, radian};
    return zv_task_registerRun(zv_task_arith_phase, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithIntegral(ZvObject src, ZvObject dst)
{
    ZvTPArithIntegral taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_integral, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithIntegral2(ZvObject src, ZvObject dst, ZvObject dstSqrt)
{
    ZvTPArithIntegral2 taskParam_0 = {src, dst, dstSqrt};
    return zv_task_registerRun(zv_task_arith_integral2, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithAnd(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZvTPArithAnd taskParam_0 = {src1, src2, dst};
    return zv_task_registerRun(zv_task_arith_and, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithOr(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZvTPArithOr taskParam_0 = {src1, src2, dst};
    return zv_task_registerRun(zv_task_arith_or, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithNot(ZvImage src, ZvImage dst)
{
    ZvTPArithNot taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_not, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithXor(ZvImage src1, ZvImage src2, ZvImage dst)
{
    ZvTPArithXor taskParam_0 = {src1, src2, dst};
    return zv_task_registerRun(zv_task_arith_xor, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithTranspose(ZvMatrix src, ZvMatrix dst)
{
    ZvTPArithTranspose taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_arith_transpose, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithInvert(ZvMatrix src, ZvMatrix dst, int method)
{
    ZvTPArithInvert taskParam_0 = {src, dst, method};
    return zv_task_registerRun(zv_task_arith_invert, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithNorm(ZvMatrix mat, int normType, double *value)
{
    ZvTPArithNorm taskParam_0 = {mat, normType, value};
    return zv_task_registerRun(zv_task_arith_norm, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMatrixMult(ZvMatrix mat1, ZvMatrix mat2, ZvMatrix dst)
{
    ZvTPArithMatrixMult taskParam_0 = {mat1, mat2, dst};
    return zv_task_registerRun(zv_task_arith_matrixMult, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithEigen(ZvMatrix src, ZvMatrix eigenvalues, ZvMatrix eigenvectors, bool isSymmetric)
{
    ZvTPArithEigen taskParam_0 = {src, eigenvalues, eigenvectors, isSymmetric};
    return zv_task_registerRun(zv_task_arith_eigen, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithZeroCount(ZvObject src, int *cnt)
{
    ZvTPArithZeroCount taskParam_0 = {src, cnt};
    return zv_task_registerRun(zv_task_arith_zeroCount, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithSum(ZvObject src, double * sum)
{
    ZvTPArithSum taskParam_0 = {src, sum};
    return zv_task_registerRun(zv_task_arith_sum, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithStatRow(ZvObject src, ZvObject dst, int type)
{
    ZvTPArithStatRow taskParam_0 = {src, dst, type};
    return zv_task_registerRun(zv_task_arith_statRow, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithStatCol(ZvObject src, ZvObject dst, int type)
{
    ZvTPArithStatCol taskParam_0 = {src, dst, type};
    return zv_task_registerRun(zv_task_arith_statCol, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMean(ZvObject src, double *mean)
{
    ZvTPArithMean taskParam_0 = {src, mean};
    return zv_task_registerRun(zv_task_arith_mean, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMeanSdev(ZvObject src, double *mean, double *stdDev)
{
    ZvTPArithMeanSdev taskParam_0 = {src, mean, stdDev};
    return zv_task_registerRun(zv_task_arith_meanSdev, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithMinMaxLoc(ZvObject src, double *value, int *pos)
{
    ZvTPArithMinMaxLoc taskParam_0 = {src, value, pos};
    return zv_task_registerRun(zv_task_arith_minMaxLoc, &taskParam_0, sizeof(taskParam_0));
}

int zv_arithHist(ZvImage img, ZvMatrix hist, int size, double low, double upper)
{
    ZvTPArithHist taskParam_0 = {img, hist, size, low, upper};
    return zv_task_registerRun(zv_task_arith_hist, &taskParam_0, sizeof(taskParam_0));
}


//ip imgproc 图像处理模块 basic/ zv_geometric_trans.cpp filter.cpp zv_morph.cpp zv_segment.cpp zv_color.cpp
//zv_geometric_trans.cpp  几何（旋转、缩放、畸变矫正、仿射透视变换）
//zv_color.cpp 颜色（Bayer、HSV）、其它（颜色映射)
//filter.cpp 滤波（高斯、中值、均值、边缘、自定义、FFT、DCT）
//zv_morph.cpp 形态学（腐蚀、膨胀、开、闭）
//zv_segment.cpp 分割（二值、分类分割、区域增长、边缘分割）
int zv_ipMirror(ZvImage src, ZvImage dst, int type)
{
    ZvTPIpMirror taskParam_0 = {src, dst, type};
    return zv_task_registerRun(zv_task_ip_mirror, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipRotate(ZvImage src, ZvImage dst, double angle, int interp)
{
    ZvTPIpRotate taskParam_0 = {src, dst, angle, interp};
    return zv_task_registerRun(zv_task_ip_rotate, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipZoom(ZvImage src, ZvImage dst, double scaleW, double scaleH, int interp)
{
    ZvTPIpZoom taskParam_0 = {src, dst, scaleW, scaleH, interp};
    return zv_task_registerRun(zv_task_ip_zoom, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipResize(ZvImage src, ZvImage dst, int dstW, int dstH, int interp)
{
    ZvTPIpResize taskParam_0 = {src, dst, dstW, dstH, interp};
    return zv_task_registerRun(zv_task_ip_resize, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipAffine(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border)
{
    ZvTPIpAffine taskParam_0 = {src, dst, mat, dstW, dstH, interp, border};
    return zv_task_registerRun(zv_task_ip_affine, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipPerspective(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW, int dstH, int interp, char *border)
{
    ZvTPIpPerspective taskParam_0 = {src, dst, mat, dstW, dstH, interp, border};
    return zv_task_registerRun(zv_task_ip_perspective, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipMoments(ZvImage binImg, int type, int orderX, int orderY, double *m)
{
    ZvTPIpMoments taskParam_0 = {binImg, type, orderX, orderY, m};
    return zv_task_registerRun(zv_task_ip_moments, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipRgbToGray(ZvImage rgb, ZvImage gray)
{
    ZvTPIpRgbToGray taskParam_0 = {rgb, gray};
    return zv_task_registerRun(zv_task_ip_rgbToGray, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipGrayToRgb(ZvImage gray, ZvImage rgb)
{
    ZvTPIpGrayToRgb taskParam_0 = {gray, rgb};
    return zv_task_registerRun(zv_task_ip_grayToRgb, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipColorToRgb(ZvImage color, ZvImage rgb, int colorSpace)
{
    ZvTPIpColorToRgb taskParam_0 = {color, rgb, colorSpace};
    return zv_task_registerRun(zv_task_ip_colorToRgb, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipRgbToColor(ZvImage rgb, ZvImage color, int colorSpace)
{
    ZvTPIpRgbToColor taskParam_0 = {rgb, color, colorSpace};
    return zv_task_registerRun(zv_task_ip_rgbToColor, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipBayerToRgb(ZvImage bayer, ZvImage rgb, int bayerType)
{
    ZvTPIpBayerToRgb taskParam_0 = {bayer, rgb, bayerType};
    return zv_task_registerRun(zv_task_ip_bayerToRgb, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipMedianBlur(ZvImage src, ZvImage dst, int size)
{
    ZvTPIpMedianBlur taskParam_0 = {src, dst, size};
    return zv_task_registerRun(zv_task_ip_medianBlur, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipMeanBlur(ZvImage src, ZvImage dst, int size)
{
    ZvTPIpMeanBlur taskParam_0 = {src, dst, size};
    return zv_task_registerRun(zv_task_ip_meanBlur, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipGaussBlur(ZvImage src, ZvImage dst, int size)
{
    ZvTPIpGaussBlur taskParam_0 = {src, dst, size};
    return zv_task_registerRun(zv_task_ip_gaussBlur, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipBilateralFilter(ZvImage src, ZvImage dst, double sigmaSpace, double sigmaRange)
{
    ZvTPIpBilateralFilter taskParam_0 = {src, dst, sigmaSpace, sigmaRange};
    return zv_task_registerRun(zv_task_ip_bilateralFilter, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipSobel(ZvImage src, ZvImage dst, int dx, int dy, int size)
{
    ZvTPIpSobel taskParam_0 = {src, dst, dx, dy, size};
    return zv_task_registerRun(zv_task_ip_sobel, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipScharr(ZvImage src, ZvImage dst, int dx, int dy)
{
    ZvTPIpScharr taskParam_0 = {src, dst, dx, dy};
    return zv_task_registerRun(zv_task_ip_scharr, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipLaplace(ZvImage src, ZvImage dst, int size)
{
    ZvTPIpLaplace taskParam_0 = {src, dst, size};
    return zv_task_registerRun(zv_task_ip_laplace, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipCanny(ZvImage img, ZvImage dst, double thresh1, double thresh2, int size)
{
    ZvTPIpCanny taskParam_0 = {img, dst, thresh1, thresh2, size};
    return zv_task_registerRun(zv_task_ip_canny, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipEqualizeHist(ZvImage src, ZvImage dst)
{
    ZvTPIpEqualizeHist taskParam_0 = {src, dst};
    return zv_task_registerRun(zv_task_ip_equalizeHist, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipDilate(ZvImage src, ZvImage dst, int seWidth, int seHeight)
{
    ZvTPIpDilate taskParam_0 = {src, dst, seWidth, seHeight};
    return zv_task_registerRun(zv_task_ip_dilate, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipErode(ZvImage src, ZvImage dst, int seWidth, int seHeight)
{
    ZvTPIpErode taskParam_0 = {src, dst, seWidth, seHeight};
    return zv_task_registerRun(zv_task_ip_erode, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipOpening(ZvImage src, ZvImage dst, int seWidth, int seHeight)
{
    ZvTPIpOpening taskParam_0 = {src, dst, seWidth, seHeight};
    return zv_task_registerRun(zv_task_ip_opening, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipClosing(ZvImage src, ZvImage dst, int seWidth, int seHeight)
{
    ZvTPIpClosing taskParam_0 = {src, dst, seWidth, seHeight};
    return zv_task_registerRun(zv_task_ip_closing, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipMorphSe(ZvImage kernel, int shape, int sizeX, int sizeY, int anchorX, int anchorY)
{
    ZvTPIpMorphSe taskParam_0 = {kernel, shape, sizeX, sizeY, anchorX, anchorY};
    return zv_task_registerRun(zv_task_ip_morphSe, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipMorph(ZvImage src, ZvImage dst, ZvImage kernel, int op, int anchorX, int anchorY, int iter, char *border)
{
    ZvTPIpMorph taskParam_0 = {src, dst, kernel, op, anchorX, anchorY, iter, border};
    return zv_task_registerRun(zv_task_ip_morph, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipLabel(ZvImage src, ZvImage label, int connectivity)
{
    ZvTPIpLabel taskParam_0 = {src, label, connectivity};
    return zv_task_registerRun(zv_task_ip_label, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipThreshold(ZvImage src, ZvImage dst, double thresh0, double thresh1, bool isInv)
{
    ZvTPIpThreshold taskParam_0 = {src, dst, thresh0, thresh1, isInv};
    return zv_task_registerRun(zv_task_ip_threshold, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipAdpThreshold(ZvImage src, ZvImage thresh, ZvImage dst, double offset, bool isInv)
{
    ZvTPIpAdpThreshold taskParam_0 = {src, thresh, dst, offset, isInv};
    return zv_task_registerRun(zv_task_ip_adpThreshold, &taskParam_0, sizeof(taskParam_0));
}

int zv_ipAutoThreshold(ZvImage src, ZvImage dst, double *thresh)
{
    ZvTPIpAutoThreshold taskParam_0 = {src, dst, thresh};
    return zv_task_registerRun(zv_task_ip_autoThreshold, &taskParam_0, sizeof(taskParam_0));
}


//match    match
//match：灰度、形状、几何特征、点、3D
int zv_matchFastTempl(ZvImage img, ZvImage templ, int *pos, int method)
{
    ZvTPMatchFastTempl taskParam_0 = {img, templ, pos, method};
    return zv_task_registerRun(zv_task_match_fastTempl, &taskParam_0, sizeof(taskParam_0));
}

int zv_matchBestTempl(ZvImage img, ZvImage templ, double minScore, double *mRst, bool isSubPix, int polar)
{
    ZvTPMatchBestTempl taskParam_0 = {img, templ, minScore, mRst, isSubPix, polar};
    return zv_task_registerRun(zv_task_match_bestTempl, &taskParam_0, sizeof(taskParam_0));
}

int zv_matchMultiTempl(ZvImage img, ZvImage templ, ZvMatrix matches, double minScore, int nums, double minDist, bool isSubPix, int polar)
{
    ZvTPMatchMultiTempl taskParam_0 = {img, templ, matches, minScore, nums, minDist, isSubPix, polar};
    return zv_task_registerRun(zv_task_match_multiTempl, &taskParam_0, sizeof(taskParam_0));
}

int zv_matchNccCreate(ZvModel mod, ZvImage templ, double angleStart, double angleExt, double angleStep, int numLevel)
{
    ZvTPMatchNccCreate taskParam_0 = { mod, templ, angleStart, angleExt, angleStep, numLevel };
    return zv_task_registerRun(zv_task_match_nccCreate, &taskParam_0, sizeof(taskParam_0));
}

int zv_matchNccFind(ZvModel mod, ZvImage img, ZvMatrix matchs, int NumLevel, double minScore, double *x, double *y, double minDist, int isSubPix)
{
    ZvTPMatchNccFind taskParam_0 = { mod, img, matchs, NumLevel, minScore, x, y, minDist, isSubPix };
    return zv_task_registerRun(zv_task_match_nccFind, &taskParam_0, sizeof(taskParam_0));
}

//meas    measure
//measure：圆、直线、椭圆、矩形、点、间距
void zv_measGenRect(void * mr, double x, double y, double width, double height)
{
    ZV_ERR_RUN(zv_meas_genRect(mr, x, y, width, height));
}

void zv_measGenRect2(void *mr, double cx, double cy, double width, double height, double angle, int interp)
{
    ZV_ERR_RUN(zv_meas_genRect2(mr, cx, cy, width, height, angle, interp));
}

void zv_measGenArc(void *mr, double cx, double cy, double r, double startA, double extentA, double annR, int interp)
{
    ZV_ERR_RUN(zv_meas_genArc(mr, cx, cy, r, startA, extentA, annR, interp));
}

int zv_measProjection(ZvImage img, ZvMatrix proj, void *mr)
{
    ZvTPMeasProjection taskParam_0 = {img, proj, mr};
    return zv_task_registerRun(zv_task_meas_projection, &taskParam_0, sizeof(taskParam_0));
}

int zv_measPos(ZvImage img, ZvMatrix pts, void *mr, int filterSize, double thresh, int type, int select)
{
    ZvTPMeasPos taskParam_0 = {img, pts, mr, filterSize, thresh, type, select};
    return zv_task_registerRun(zv_task_meas_pos, &taskParam_0, sizeof(taskParam_0));
}

int zv_measPairs(ZvImage img, ZvMatrix pairs, void *mr, int filterSize, double thresh, int type, int select)
{
    ZvTPMeasPairs taskParam_0 = {img, pairs, mr, filterSize, thresh, type, select};
    return zv_task_registerRun(zv_task_meas_pairs, &taskParam_0, sizeof(taskParam_0));
}

int zv_measGenLineMr(void *mr, double cx, double cy, double width, double height, double angle, int interp, int subNum, int subWidth)
{
    return zv_meas_genLineMr(mr, cx, cy, width, height, angle, interp, subNum, subWidth);
}

int zv_measGenCircleMr(void *mr, double cx, double cy, double r, double startA, double extentA, double annR, int interp, int subNum, int subWidth)
{
    return zv_meas_genCircleMr(mr, cx, cy, r, startA, extentA, annR, interp, subNum, subWidth);
}

void zv_measSetMrAdvParam(void *mr, int filterSize, double thresh, int type, int select)
{
    ZV_ERR_RUN(zv_meas_setMrAdvParam(mr, filterSize, thresh, type, select));
}

void zv_measGetMrAdvParam(void *mr, int *filterSize, double *thresh, int *type, int *select)
{
    ZV_ERR_RUN(zv_meas_getMrAdvParam(mr, filterSize, thresh, type, select));
}

int zv_measLine(ZvImage img, void *mr, double *line, ZvMatrix pts)
{
    ZvTPMeasLine taskParam_0 = {img, mr, line, pts};
    return zv_task_registerRun(zv_task_meas_line, &taskParam_0, sizeof(taskParam_0));
}

int zv_measCircle(ZvImage img, void *mr, double *circle, ZvMatrix pts)
{
    ZvTPMeasCircle taskParam_0 = {img, mr, circle, pts};
    return zv_task_registerRun(zv_task_meas_circle, &taskParam_0, sizeof(taskParam_0));
}


//feat  feature
//feature：角点、霍夫、边缘
int zv_featHoughLine(ZvImage img, ZvMatrix lines, double rho, double theta, int thresh, double minLinelen, double maxLineGap)
{
    ZvTPFeatHoughLine taskParam_0 = {img, lines, rho, theta, thresh, minLinelen, maxLineGap};
    return zv_task_registerRun(zv_task_feat_houghLine, &taskParam_0, sizeof(taskParam_0));
}

int zv_featHoughCircle(ZvImage img, ZvMatrix circles, double minDist, double param1, double param2, double minR, double maxR)
{
    ZvTPFeatHoughCircle taskParam_0 = {img, circles, minDist, param1, param2, minR, maxR};
    return zv_task_registerRun(zv_task_feat_houghCircle, &taskParam_0, sizeof(taskParam_0));
}


//tk    tools
//tools：几何变换、几何特征、交点、夹角、拟合、插值
void zv_tkGetSimilarityParam(ZvMatrix mat, double cx, double cy, double angle, double scale)
{
    ZV_ERR_RUN(zv_tk_getSimilarityParam(mat, cx, cy, angle, scale));
}

int zv_tkGetRigid(ZvMatrix mat, double *from, double *to)
{
    ZvTPTkGetRigid taskParam_0 = {mat, from, to};
    return zv_task_registerRun(zv_task_tk_getRigid, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkGetRigidVector(ZvMatrix mat, double xFrom, double yFrom, double angleFrom, double xTo, double yTo, double angleTo)
{
    ZvTPTkGetRigidVector taskParam_0 = {mat, xFrom, yFrom, angleFrom, xTo, yTo, angleTo};
    return zv_task_registerRun(zv_task_tk_getRigidVector, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkGetSimilarity(ZvMatrix mat, double *from, double *to)
{
    ZvTPTkGetSimilarity taskParam_0 = {mat, from, to};
    return zv_task_registerRun(zv_task_tk_getSimilarity, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkGetAffine(ZvMatrix mat, double *from, double *to)
{
    ZvTPTkGetAffine taskParam_0 = {mat, from, to};
    return zv_task_registerRun(zv_task_tk_getAffine, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkEstimateSimilarity(ZvMatrix from, ZvMatrix to, ZvMatrix mat, double thresh, double confidence, bool * isInliers)
{
    ZvTPTkEstimateSimilarity taskParam_0 = {from, to, mat, thresh, confidence, isInliers};
    return zv_task_registerRun(zv_task_tk_estimateSimilarity, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkEstimateAffine(ZvMatrix from, ZvMatrix to, ZvMatrix mat, double thresh, double confidence, bool * isInliers)
{
    ZvTPTkEstimateAffine taskParam_0 = {from, to, mat, thresh, confidence, isInliers};
    return zv_task_registerRun(zv_task_tk_estimateAffine, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkAffineTrans(ZvMatrix mat, double *from, double *to, int ptNum)
{
    ZvTPTkAffineTrans taskParam_0 = {mat, from, to, ptNum};
    return zv_task_registerRun(zv_task_tk_affineTrans, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkGetProjective(ZvMatrix mat, double *from, double *to)
{
    ZvTPTkGetProjective taskParam_0 = {mat, from, to};
    return zv_task_registerRun(zv_task_tk_getProjective, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkProjectiveTrans2d(ZvMatrix mat, double *from, double *to, int num)
{
    ZvTPTkProjectiveTrans2d taskParam_0 = {mat, from, to, num};
    return zv_task_registerRun(zv_task_tk_projectiveTrans2d, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkProjectiveTrans3d(ZvMatrix mat, double *from, double *to, int num)
{
    ZvTPTkProjectiveTrans3d taskParam_0 = {mat, from, to, num};
    return zv_task_registerRun(zv_task_tk_projectiveTrans3d, &taskParam_0, sizeof(taskParam_0));
}

double zv_tkDistancePP(double x1, double y1, double x2, double y2)
{
    return zv_tk_distancePP(x1, y1, x2, y2);
}

double zv_tkDistancePL(double px, double py, double x1, double y1, double x2, double y2)
{
    return zv_tk_distancePL(px, py, x1, y1, x2, y2);
}

double zv_tkDistancePS(double px, double py, double x1, double y1, double x2, double y2)
{
    return zv_tk_distancePS(px, py, x1, y1, x2, y2);
}

int zv_tkDistanceContP(ZvContour cont, double px, double py, double * dist)
{
    ZvTPTkDistanceContP taskParam_0 = {cont, px, py, dist};
    return zv_task_registerRun(zv_task_tk_distanceContP, &taskParam_0, sizeof(taskParam_0));
}

void zv_tkRect2Vertex(double cx, double cy, double width, double height, double angle, double *pt)
{
    ZV_ERR_RUN(zv_tk_rect2Vertex(cx, cy, width, height, angle, pt));
}

void zv_tkIntersectPL(double px, double py, double x1, double y1, double x2, double y2, double *sect)
{
    ZV_ERR_RUN(zv_tk_intersectPL(px, py, x1, y1, x2, y2, sect, sect+1));
}

bool zv_tkIntersectLL(double l1x1, double l1y1, double l1x2, double l1y2, double l2x1, double l2y1, double l2x2, double l2y2, double *sect)
{
    return zv_tk_intersectLL(l1x1, l1y1, l1x2, l1y2, l2x1, l2y1, l2x2, l2y2, sect, sect+1);
}

double zv_tkAngleLines(double line1X1, double line1Y1, double line1X2, double line1Y2, double line2X1, double line2Y1, double line2X2, double line2Y2)
{
    return zv_tk_angleLines(line1X1, line1Y1, line1X2, line1Y2, line2X1, line2Y1, line2X2, line2Y2);
}

double zv_tkAngleLineX(double x1, double y1, double x2, double y2)
{
    return zv_tk_angleLineX(x1, y1, x2, y2);
}

int zv_tkFitLine2D(ZvMatrix pts, double *line)
{
    ZvTPTkFitLine2D taskParam_0 = {pts, line};
    return zv_task_registerRun(zv_task_tk_fitLine2D, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkFitEllipse(ZvMatrix pts, double *ellipse)
{
    ZvTPTkFitEllipse taskParam_0 = {pts, ellipse};
    return zv_task_registerRun(zv_task_tk_fitEllipse, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkIntersectRect2(ZvMatrix pts, double R1X, double R1Y, double R1W, double R1H, double R1Angle, double R2X, double R2Y, double R2W, double R2H, double R2Angle)
{
    ZvTPTkIntersectRect2 taskParam_0 = {pts, R1X, R1Y, R1W, R1H, R1Angle, R2X, R2Y, R2W, R2H, R2Angle};
    return zv_task_registerRun(zv_task_tk_intersectRect2, &taskParam_0, sizeof(taskParam_0));
}

void zv_tkLineToParam(double x1, double y1, double x2, double y2, double *lineParam)
{
    ZV_ERR_RUN(zv_tk_lineToParam(x1, y1, x2, y2, lineParam, lineParam+1, lineParam+2, lineParam+3));
}

void zv_tkLineFromParam(double cx, double cy, double angle, double len, double *line)
{
    ZV_ERR_RUN(zv_tk_lineFromParam(cx, cy, angle, len, line, line+1, line+2, line+3));
}

int zv_tkFitLineEx(ZvMatrix pts, double *line, int method, double reps, double aeps)
{
    ZvTPTkFitLineEx taskParam_0 = {pts, line, method, reps, aeps};
    return zv_task_registerRun(zv_task_tk_fitLineEx, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkFitEllipseEx(ZvMatrix pts, double *ellipse, int method)
{
    ZvTPTkFitEllipseEx taskParam_0 = {pts, ellipse, method};
    return zv_task_registerRun(zv_task_tk_fitEllipseEx, &taskParam_0, sizeof(taskParam_0));
}

int zv_tkFitPolyn(ZvMatrix pts, int order, double *param)
{
    ZvTPTkFitPolyn taskParam_0 = {pts, order, param};
    return zv_task_registerRun(zv_task_tk_fitPolyn, &taskParam_0, sizeof(taskParam_0));
}


//dra模块，绘制图形和文字
int zv_draColor(int r, int g, int b)
{
    return zv_dra_color(r, g, b);
}

int zv_draColorId(int id)
{
    return zv_dra_colorId(id);
}

int zv_draLine(ZvImage img, double x1, double y1, double x2, double y2, int color)
{
    ZvTPDraLine taskParam_0 = {img, x1, y1, x2, y2, color};
    return zv_task_registerRun(zv_task_dra_line, &taskParam_0, sizeof(taskParam_0));
}

int zv_draRect(ZvImage img, double x, double y, double w, double h, int color)
{
    ZvTPDraRect taskParam_0 = {img, x, y, w, h, color};
    return zv_task_registerRun(zv_task_dra_rect, &taskParam_0, sizeof(taskParam_0));
}

int zv_draRect2(ZvImage img, double cx, double cy, double width, double height, double angle, int color)
{
    ZvTPDraRect2 taskParam_0 = {img, cx, cy, width, height, angle, color};
    return zv_task_registerRun(zv_task_dra_rect2, &taskParam_0, sizeof(taskParam_0));
}

int zv_draCircle(ZvImage img, double cx, double cy, double r, int color)
{
    ZvTPDraCircle taskParam_0 = {img, cx, cy, r, color};
    return zv_task_registerRun(zv_task_dra_circle, &taskParam_0, sizeof(taskParam_0));
}

int zv_draEllipse(ZvImage img, double cx, double cy, double xR, double yR, double angle, int color)
{
    ZvTPDraEllipse taskParam_0 = {img, cx, cy, xR, yR, angle, color};
    return zv_task_registerRun(zv_task_dra_ellipse, &taskParam_0, sizeof(taskParam_0));
}

int zv_draEllipseArc(ZvImage img, double cx, double cy, double xR, double yR, double angle, double angleStart, double angleEnd, int color)
{
    ZvTPDraEllipseArc taskParam_0 = {img, cx, cy, xR, yR, angle, angleStart, angleEnd, color};
    return zv_task_registerRun(zv_task_dra_ellipseArc, &taskParam_0, sizeof(taskParam_0));
}

int zv_draArrow(ZvImage img, double x1, double y1, double x2, double y2, int color, int size)
{
    ZvTPDraArrow taskParam_0 = {img, x1, y1, x2, y2, color, size};
    return zv_task_registerRun(zv_task_dra_arrow, &taskParam_0, sizeof(taskParam_0));
}

int zv_draPolygon(ZvImage img, ZvMatrix pts, bool isClosed, int color)
{
    ZvTPDraPolygon taskParam_0 = {img, pts, isClosed, color};
    return zv_task_registerRun(zv_task_dra_polygon, &taskParam_0, sizeof(taskParam_0));
}

int zv_draContour(ZvImage img, ZvContour cont, int color)
{
    ZvTPDraContour taskParam_0 = {img, cont, color};
    return zv_task_registerRun(zv_task_dra_contour, &taskParam_0, sizeof(taskParam_0));
}

int zv_draMarker(ZvImage img, double x, double y, int type, int size, int color)
{
    ZvTPDraMarker taskParam_0 = {img, x, y, type, size, color};
    return zv_task_registerRun(zv_task_dra_marker, &taskParam_0, sizeof(taskParam_0));
}

int zv_draText(ZvImage img, char * text, double x, double y, double scale, int color)
{
    ZvTPDraText taskParam_0 = {img, text, x, y, scale, color};
    return zv_task_registerRun(zv_task_dra_text, &taskParam_0, sizeof(taskParam_0));
}

int zv_draMask(ZvImage img, ZvImage mask)
{
    ZvTPDraMask taskParam_0 = {img, mask};
    return zv_task_registerRun(zv_task_dra_mask, &taskParam_0, sizeof(taskParam_0));
}

int zv_draMeasurer(ZvImage img, void *mr, int color, int subColor)
{
    ZvTPDraMeasurer taskParam_0 = {img, mr, color, subColor};
    return zv_task_registerRun(zv_task_dra_measurer, &taskParam_0, sizeof(taskParam_0));
}


int zv_modInit(bool isBlocking)
{
    cv::setBreakOnError(false);                                      //设置了break-on-error模式时，默认错误处理程序会发出硬件异常，这可以使调试更方便。
    cv::redirectError((cv::ErrorCallback)zv_adp_cvErrorCallback);    //设置新的错误处理程序和可选的用户数据。
    ZV_RUN_RTN(zv_task_init(isBlocking));                            //任务初始化
    ZV_RUN_RTN(zv_cam_init());                                       //相机初始化
    return ZV_ST_OK; 
}

int zv_modExit()
{
    ZV_RUN_RTN(zv_cam_exit());
    return ZV_ST_OK;
}
