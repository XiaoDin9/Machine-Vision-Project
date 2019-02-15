/*************************************************************
该文件为自动生成文件，如果修改请注意备份，重新生成将被覆盖
////由zv_module_gen.py生成，需要zv_module_templ.py模块内的
////固定字符串定义和zv_module.h文件内的函数声明，声明需要符
////合特定格式
*************************************************************/

#include "zv_private.h"
#include "zv_task_param.h"
#include "zv_task.h"
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


typedef struct _ZvTaskData
{
    ZvTaskFun fun;
    unsigned char paramBuf[10 * sizeof(double)];
}ZvTaskData;

static ZvTaskData s_zv_task_taskData[ZV_SYS_THREAD_MAX] = { 0 };
bool s_zv_task_isBlocking = false;


int zv_task_init(bool isBlocking)
{
    s_zv_task_isBlocking = isBlocking;
    return ZV_ST_OK;
}

int zv_task_registerRun(ZvTaskFun fun, void *param, int paramSize)
{
    int id = 0;

    if (paramSize > sizeof(s_zv_task_taskData[0].paramBuf))
    {
        return ZV_ERR_T_PARAM_SIZE;
    }

    memset(s_zv_task_taskData[id].paramBuf, 0, sizeof(s_zv_task_taskData[id].paramBuf));
    memcpy(s_zv_task_taskData[id].paramBuf, param, paramSize);
    s_zv_task_taskData[id].fun = fun;
    if (s_zv_task_isBlocking)
    {
        s_zv_task_taskData[id].fun(s_zv_task_taskData[id].paramBuf);
    }

    return ZV_ST_OK;
}

void zv_task_threadRun()
{
    int id = 0; // 获取线程ID
    if (NULL != s_zv_task_taskData[id].fun && false == s_zv_task_isBlocking)
    {
        s_zv_task_taskData[id].fun(s_zv_task_taskData[id].paramBuf);
    }
    else
    {
        zv_sys_sleep(1);
    }
    s_zv_task_taskData[id].fun = NULL;
}

void zv_task_cam_scan(void *param)
{
    ZvTPCamScan *p = (ZvTPCamScan *)param;
    ZV_ERR_RUN(zv_cam_scan(p->type));
}

void zv_task_cam_getInfo(void *param)
{
    ZvTPCamGetInfo *p = (ZvTPCamGetInfo *)param;
    ZV_ERR_RUN(zv_cam_getInfo(p->scanId, p->prop, p->value, p->maxValLen));
}

void zv_task_cam_open(void *param)
{
    ZvTPCamOpen *p = (ZvTPCamOpen *)param;
    ZV_ERR_RUN(zv_cam_open(p->camId, p->scanId));
}

void zv_task_cam_status(void *param)
{
    ZvTPCamStatus *p = (ZvTPCamStatus *)param;
    *p->status = zv_cam_status(p->camId);
}

void zv_task_cam_close(void *param)
{
    ZvTPCamClose *p = (ZvTPCamClose *)param;
    ZV_ERR_RUN(zv_cam_close(p->camId));
}

void zv_task_cam_payloadSize(void *param)
{
    ZvTPCamPayloadSize *p = (ZvTPCamPayloadSize *)param;
    *p->size = zv_cam_payloadSize(p->camId);
}

void zv_task_cam_grab(void *param)
{
    ZvTPCamGrab *p = (ZvTPCamGrab *)param;
    ZV_ERR_RUN(zv_cam_grab(p->img, p->camId));
}

void zv_task_cam_getROI(void *param)
{
    ZvTPCamGetROI *p = (ZvTPCamGetROI *)param;
    ZV_ERR_RUN(zv_cam_getROI(p->camId, p->camROI, p->camROI+1, p->camROI+2, p->camROI+3));
}

void zv_task_cam_setROI(void *param)
{
    ZvTPCamSetROI *p = (ZvTPCamSetROI *)param;
    ZV_ERR_RUN(zv_cam_setROI(p->camId, p->x, p->y, p->width, p->height));
}

void zv_task_cam_getExposure(void *param)
{
    ZvTPCamGetExposure *p = (ZvTPCamGetExposure *)param;
    *p->time = zv_cam_getExposure(p->camId);
}

void zv_task_cam_setExposure(void *param)
{
    ZvTPCamSetExposure *p = (ZvTPCamSetExposure *)param;
    ZV_ERR_RUN(zv_cam_setExposure(p->camId, p->time));
}

void zv_task_cam_startGrabbing(void *param)
{
    ZvTPCamStartGrabbing *p = (ZvTPCamStartGrabbing *)param;
    ZV_ERR_RUN(zv_cam_startGrabbing(p->camId, p->bufCount));
}

void zv_task_cam_isGrabbing(void *param)
{
    ZvTPCamIsGrabbing *p = (ZvTPCamIsGrabbing *)param;
    ZV_ERR_RUN(zv_cam_isGrabbing(p->camId, p->isGrabbing));
}

void zv_task_cam_retrieve(void *param)
{
    ZvTPCamRetrieve *p = (ZvTPCamRetrieve *)param;
    ZV_ERR_RUN(zv_cam_retrieve(p->img, p->camId, p->bufId));
}

void zv_task_cam_reset(void *param)
{
    ZvTPCamReset *p = (ZvTPCamReset *)param;
    ZV_ERR_RUN(zv_cam_reset(p->camId));
}

void zv_task_cam_getParam(void *param)
{
    ZvTPCamGetParam *p = (ZvTPCamGetParam *)param;
    ZV_ERR_RUN(zv_cam_getParam(p->camId, p->name, p->value, p->maxValLen));
}

void zv_task_cam_setParam(void *param)
{
    ZvTPCamSetParam *p = (ZvTPCamSetParam *)param;
    ZV_ERR_RUN(zv_cam_setParam(p->camId, p->name, p->value));
}

void zv_task_file_readImage(void *param)
{
    ZvTPFileReadImage *p = (ZvTPFileReadImage *)param;
    ZV_ERR_RUN(zv_file_readImage(p->img, p->fileName, p->type));
}

void zv_task_file_writeImage(void *param)
{
    ZvTPFileWriteImage *p = (ZvTPFileWriteImage *)param;
    ZV_ERR_RUN(zv_file_writeImage(p->img, p->fileName, p->param));
}

void zv_task_file_readMatrix(void *param)
{
    ZvTPFileReadMatrix *p = (ZvTPFileReadMatrix *)param;
    ZV_ERR_RUN(zv_file_readMatrix(p->mat, p->fileName, p->nodeName, p->type));
}

void zv_task_file_writeMatrix(void *param)
{
    ZvTPFileWriteMatrix *p = (ZvTPFileWriteMatrix *)param;
    ZV_ERR_RUN(zv_file_writeMatrix(p->mat, p->fileName, p->nodeName, p->type));
}

void zv_task_img_genConst(void *param)
{
    ZvTPImgGenConst *p = (ZvTPImgGenConst *)param;
    ZV_ERR_RUN(zv_img_genConst(p->img, p->width, p->height, p->type, p->channel, p->element));
}

void zv_task_img_genData(void *param)
{
    ZvTPImgGenData *p = (ZvTPImgGenData *)param;
    ZV_ERR_RUN(zv_img_genData(p->img, p->width, p->height, p->type, p->channel, p->data));
}

void zv_task_img_getData(void *param)
{
    ZvTPImgGetData *p = (ZvTPImgGetData *)param;
    ZV_ERR_RUN(zv_img_getData(p->img, p->buf, p->size, p->isAlign));
}

void zv_task_img_setData(void *param)
{
    ZvTPImgSetData *p = (ZvTPImgSetData *)param;
    ZV_ERR_RUN(zv_img_setData(p->img, p->buf));
}

void zv_task_img_getSub(void *param)
{
    ZvTPImgGetSub *p = (ZvTPImgGetSub *)param;
    ZV_ERR_RUN(zv_img_getSub(p->img, p->sub, p->x, p->y, p->width, p->height));
}

void zv_task_img_setSub(void *param)
{
    ZvTPImgSetSub *p = (ZvTPImgSetSub *)param;
    ZV_ERR_RUN(zv_img_setSub(p->img, p->sub, p->x, p->y));
}

void zv_task_img_convert(void *param)
{
    ZvTPImgConvert *p = (ZvTPImgConvert *)param;
    ZV_ERR_RUN(zv_img_convert(p->src, p->dst, p->dstType, p->mult, p->add));
}

void zv_task_img_copy(void *param)
{
    ZvTPImgCopy *p = (ZvTPImgCopy *)param;
    ZV_ERR_RUN(zv_img_copy(p->src, p->dst));
}

void zv_task_img_split2(void *param)
{
    ZvTPImgSplit2 *p = (ZvTPImgSplit2 *)param;
    ZV_ERR_RUN(zv_img_split2(p->src, p->dst1, p->dst2));
}

void zv_task_img_split3(void *param)
{
    ZvTPImgSplit3 *p = (ZvTPImgSplit3 *)param;
    ZV_ERR_RUN(zv_img_split3(p->src, p->dst1, p->dst2, p->dst3));
}

void zv_task_img_split4(void *param)
{
    ZvTPImgSplit4 *p = (ZvTPImgSplit4 *)param;
    ZV_ERR_RUN(zv_img_split4(p->src, p->dst1, p->dst2, p->dst3, p->dst4));
}

void zv_task_img_merge2(void *param)
{
    ZvTPImgMerge2 *p = (ZvTPImgMerge2 *)param;
    ZV_ERR_RUN(zv_img_merge2(p->src1, p->src2, p->dst));
}

void zv_task_img_merge3(void *param)
{
    ZvTPImgMerge3 *p = (ZvTPImgMerge3 *)param;
    ZV_ERR_RUN(zv_img_merge3(p->src1, p->src2, p->src3, p->dst));
}

void zv_task_img_merge4(void *param)
{
    ZvTPImgMerge4 *p = (ZvTPImgMerge4 *)param;
    ZV_ERR_RUN(zv_img_merge4(p->src1, p->src2, p->src3, p->src4, p->dst));
}

void zv_task_mat_genConst(void *param)
{
    ZvTPMatGenConst *p = (ZvTPMatGenConst *)param;
    ZV_ERR_RUN(zv_mat_genConst(p->mat, p->rows, p->cols, p->value));
}

void zv_task_mat_genEye(void *param)
{
    ZvTPMatGenEye *p = (ZvTPMatGenEye *)param;
    ZV_ERR_RUN(zv_mat_genEye(p->mat, p->size));
}

void zv_task_mat_genData(void *param)
{
    ZvTPMatGenData *p = (ZvTPMatGenData *)param;
    ZV_ERR_RUN(zv_mat_genData(p->mat, p->rows, p->cols, p->data));
}

void zv_task_mat_getRow(void *param)
{
    ZvTPMatGetRow *p = (ZvTPMatGetRow *)param;
    ZV_ERR_RUN(zv_mat_getRow(p->mat, p->row, p->data, p->bufLen));
}

void zv_task_mat_setRow(void *param)
{
    ZvTPMatSetRow *p = (ZvTPMatSetRow *)param;
    ZV_ERR_RUN(zv_mat_setRow(p->mat, p->row, p->data));
}

void zv_task_mat_getCol(void *param)
{
    ZvTPMatGetCol *p = (ZvTPMatGetCol *)param;
    ZV_ERR_RUN(zv_mat_getCol(p->mat, p->col, p->data, p->bufLen));
}

void zv_task_mat_setCol(void *param)
{
    ZvTPMatSetCol *p = (ZvTPMatSetCol *)param;
    ZV_ERR_RUN(zv_mat_setCol(p->mat, p->col, p->data));
}

void zv_task_mat_getData(void *param)
{
    ZvTPMatGetData *p = (ZvTPMatGetData *)param;
    ZV_ERR_RUN(zv_mat_getData(p->mat, p->data, p->bufLen));
}

void zv_task_mat_setData(void *param)
{
    ZvTPMatSetData *p = (ZvTPMatSetData *)param;
    ZV_ERR_RUN(zv_mat_setData(p->mat, p->data));
}

void zv_task_mat_getSub(void *param)
{
    ZvTPMatGetSub *p = (ZvTPMatGetSub *)param;
    ZV_ERR_RUN(zv_mat_getSub(p->mat, p->sub, p->x, p->y, p->width, p->height));
}

void zv_task_mat_setSub(void *param)
{
    ZvTPMatSetSub *p = (ZvTPMatSetSub *)param;
    ZV_ERR_RUN(zv_mat_setSub(p->mat, p->sub, p->x, p->y));
}

void zv_task_mat_copy(void *param)
{
    ZvTPMatCopy *p = (ZvTPMatCopy *)param;
    ZV_ERR_RUN(zv_mat_copy(p->src, p->dst));
}

void zv_task_cont_getPointsAll(void *param)
{
    ZvTPContGetPointsAll *p = (ZvTPContGetPointsAll *)param;
    ZV_ERR_RUN(zv_cont_getPointsAll(p->cont, p->pts, p->ptsLen));
}

void zv_task_cont_gen(void *param)
{
    ZvTPContGen *p = (ZvTPContGen *)param;
    ZV_ERR_RUN(zv_cont_gen(p->img, p->contList, p->mode, p->appro));
}

void zv_task_cont_toMatrix(void *param)
{
    ZvTPContToMatrix *p = (ZvTPContToMatrix *)param;
    ZV_ERR_RUN(zv_cont_toMatrix(p->cont, p->mat));
}

void zv_task_cont_fromMatrix(void *param)
{
    ZvTPContFromMatrix *p = (ZvTPContFromMatrix *)param;
    ZV_ERR_RUN(zv_cont_fromMatrix(p->cont, p->mat));
}

void zv_task_cont_area(void *param)
{
    ZvTPContArea *p = (ZvTPContArea *)param;
    *p->area = zv_cont_area(p->cont, p->isOriented);
}

void zv_task_cont_length(void *param)
{
    ZvTPContLength *p = (ZvTPContLength *)param;
    *p->len = zv_cont_length(p->cont, p->isClosed);
}

void zv_task_cont_center(void *param)
{
    ZvTPContCenter *p = (ZvTPContCenter *)param;
    ZV_ERR_RUN(zv_cont_center(p->cont, p->center, p->center+1));
}

void zv_task_cont_isConvex(void *param)
{
    ZvTPContIsConvex *p = (ZvTPContIsConvex *)param;
    *p->isConvex = zv_cont_isConvex(p->cont);
}

void zv_task_cont_convexity(void *param)
{
    ZvTPContConvexity *p = (ZvTPContConvexity *)param;
    *p->convexity = zv_cont_convexity(p->cont);
}

void zv_task_cont_circularity(void *param)
{
    ZvTPContCircularity *p = (ZvTPContCircularity *)param;
    *p->value = zv_cont_circularity(p->cont);
}

void zv_task_cont_compactness(void *param)
{
    ZvTPContCompactness *p = (ZvTPContCompactness *)param;
    *p->value = zv_cont_compactness(p->cont);
}

void zv_task_cont_smallestRect(void *param)
{
    ZvTPContSmallestRect *p = (ZvTPContSmallestRect *)param;
    ZV_ERR_RUN(zv_cont_smallestRect(p->cont, p->rect, p->rect+1, p->rect+2, p->rect+3));
}

void zv_task_cont_smallestRect2(void *param)
{
    ZvTPContSmallestRect2 *p = (ZvTPContSmallestRect2 *)param;
    ZV_ERR_RUN(zv_cont_smallestRect2(p->cont, p->rect2, p->rect2+1, p->rect2+2, p->rect2+3, p->rect2+4));
}

void zv_task_cont_smallestCircle(void *param)
{
    ZvTPContSmallestCircle *p = (ZvTPContSmallestCircle *)param;
    ZV_ERR_RUN(zv_cont_smallestCircle(p->cont, p->circle, p->circle+1, p->circle+2));
}

void zv_task_cont_ellipticAxis(void *param)
{
    ZvTPContEllipticAxis *p = (ZvTPContEllipticAxis *)param;
    ZV_ERR_RUN(zv_cont_ellipticAxis(p->cont, p->major, p->minor, p->angle));
}

void zv_task_cont_convexHullIdx(void *param)
{
    ZvTPContConvexHullIdx *p = (ZvTPContConvexHullIdx *)param;
    ZV_ERR_RUN(zv_cont_convexHullIdx(p->cont, p->ptIdx, p->bufLen));
}

void zv_task_cont_approxPoly(void *param)
{
    ZvTPContApproxPoly *p = (ZvTPContApproxPoly *)param;
    ZV_ERR_RUN(zv_cont_approxPoly(p->cont, p->poly, p->epsilon, p->isClosed));
}

void zv_task_cont_sort(void *param)
{
    ZvTPContSort *p = (ZvTPContSort *)param;
    ZV_ERR_RUN(zv_cont_sort(p->contlist, p->feature, p->isInc));
}

void zv_task_cont_filter(void *param)
{
    ZvTPContFilter *p = (ZvTPContFilter *)param;
    ZV_ERR_RUN(zv_cont_filter(p->contlist, p->feature, p->min, p->max, p->isInvert));
}

void zv_task_cont_moments(void *param)
{
    ZvTPContMoments *p = (ZvTPContMoments *)param;
    *p->m = zv_cont_moments(p->cont, p->type, p->orderX, p->orderY);
}

void zv_task_cont_huMoments(void *param)
{
    ZvTPContHuMoments *p = (ZvTPContHuMoments *)param;
    ZV_ERR_RUN(zv_cont_huMoments(p->cont, p->hu));
}

void zv_task_cont_affine(void *param)
{
    ZvTPContAffine *p = (ZvTPContAffine *)param;
    ZV_ERR_RUN(zv_cont_affine(p->contSrc, p->contDst, p->mat));
}

void zv_task_cont_perspective(void *param)
{
    ZvTPContPerspective *p = (ZvTPContPerspective *)param;
    ZV_ERR_RUN(zv_cont_perspective(p->contSrc, p->contDst, p->mat));
}

void zv_task_arith_abs(void *param)
{
    ZvTPArithAbs *p = (ZvTPArithAbs *)param;
    ZV_ERR_RUN(zv_arith_abs(p->src, p->dst));
}

void zv_task_arith_absDiff(void *param)
{
    ZvTPArithAbsDiff *p = (ZvTPArithAbsDiff *)param;
    ZV_ERR_RUN(zv_arith_absDiff(p->src1, p->src2, p->dst, p->mult));
}

void zv_task_arith_add(void *param)
{
    ZvTPArithAdd *p = (ZvTPArithAdd *)param;
    ZV_ERR_RUN(zv_arith_add(p->src1, p->src2, p->dst, p->mult, p->add));
}

void zv_task_arith_sub(void *param)
{
    ZvTPArithSub *p = (ZvTPArithSub *)param;
    ZV_ERR_RUN(zv_arith_sub(p->src1, p->src2, p->dst, p->mult, p->add));
}

void zv_task_arith_mul(void *param)
{
    ZvTPArithMul *p = (ZvTPArithMul *)param;
    ZV_ERR_RUN(zv_arith_mul(p->src1, p->src2, p->dst, p->mult, p->add));
}

void zv_task_arith_div(void *param)
{
    ZvTPArithDiv *p = (ZvTPArithDiv *)param;
    ZV_ERR_RUN(zv_arith_div(p->src1, p->src2, p->dst, p->mult, p->add));
}

void zv_task_arith_scale(void *param)
{
    ZvTPArithScale *p = (ZvTPArithScale *)param;
    ZV_ERR_RUN(zv_arith_scale(p->src, p->dst, p->mult, p->add));
}

void zv_task_arith_addWeighted(void *param)
{
    ZvTPArithAddWeighted *p = (ZvTPArithAddWeighted *)param;
    ZV_ERR_RUN(zv_arith_addWeighted(p->src1, p->src2, p->dst, p->weight1, p->weight2, p->add));
}

void zv_task_arith_sin(void *param)
{
    ZvTPArithSin *p = (ZvTPArithSin *)param;
    ZV_ERR_RUN(zv_arith_sin(p->src, p->dst));
}

void zv_task_arith_cos(void *param)
{
    ZvTPArithCos *p = (ZvTPArithCos *)param;
    ZV_ERR_RUN(zv_arith_cos(p->src, p->dst));
}

void zv_task_arith_tan(void *param)
{
    ZvTPArithTan *p = (ZvTPArithTan *)param;
    ZV_ERR_RUN(zv_arith_tan(p->src, p->dst));
}

void zv_task_arith_asin(void *param)
{
    ZvTPArithAsin *p = (ZvTPArithAsin *)param;
    ZV_ERR_RUN(zv_arith_asin(p->src, p->dst));
}

void zv_task_arith_acos(void *param)
{
    ZvTPArithAcos *p = (ZvTPArithAcos *)param;
    ZV_ERR_RUN(zv_arith_acos(p->src, p->dst));
}

void zv_task_arith_atan(void *param)
{
    ZvTPArithAtan *p = (ZvTPArithAtan *)param;
    ZV_ERR_RUN(zv_arith_atan(p->src, p->dst));
}

void zv_task_arith_atan2(void *param)
{
    ZvTPArithAtan2 *p = (ZvTPArithAtan2 *)param;
    ZV_ERR_RUN(zv_arith_atan2(p->y, p->x, p->dst));
}

void zv_task_arith_exp(void *param)
{
    ZvTPArithExp *p = (ZvTPArithExp *)param;
    ZV_ERR_RUN(zv_arith_exp(p->src, p->dst, p->baseType));
}

void zv_task_arith_log(void *param)
{
    ZvTPArithLog *p = (ZvTPArithLog *)param;
    ZV_ERR_RUN(zv_arith_log(p->src, p->dst, p->baseType));
}

void zv_task_arith_pow(void *param)
{
    ZvTPArithPow *p = (ZvTPArithPow *)param;
    ZV_ERR_RUN(zv_arith_pow(p->src, p->dst, p->exponent));
}

void zv_task_arith_sqrt(void *param)
{
    ZvTPArithSqrt *p = (ZvTPArithSqrt *)param;
    ZV_ERR_RUN(zv_arith_sqrt(p->src, p->dst));
}

void zv_task_arith_compare(void *param)
{
    ZvTPArithCompare *p = (ZvTPArithCompare *)param;
    ZV_ERR_RUN(zv_arith_compare(p->src1, p->src2, p->dst, p->op));
}

void zv_task_arith_max(void *param)
{
    ZvTPArithMax *p = (ZvTPArithMax *)param;
    ZV_ERR_RUN(zv_arith_max(p->src1, p->src2, p->dst));
}

void zv_task_arith_min(void *param)
{
    ZvTPArithMin *p = (ZvTPArithMin *)param;
    ZV_ERR_RUN(zv_arith_min(p->src1, p->src2, p->dst));
}

void zv_task_arith_maxS(void *param)
{
    ZvTPArithMaxS *p = (ZvTPArithMaxS *)param;
    ZV_ERR_RUN(zv_arith_maxS(p->src1, p->dst, p->scalar));
}

void zv_task_arith_minS(void *param)
{
    ZvTPArithMinS *p = (ZvTPArithMinS *)param;
    ZV_ERR_RUN(zv_arith_minS(p->src1, p->dst, p->scalar));
}

void zv_task_arith_magnitude(void *param)
{
    ZvTPArithMagnitude *p = (ZvTPArithMagnitude *)param;
    ZV_ERR_RUN(zv_arith_magnitude(p->x, p->y, p->magnitude));
}

void zv_task_arith_phase(void *param)
{
    ZvTPArithPhase *p = (ZvTPArithPhase *)param;
    ZV_ERR_RUN(zv_arith_phase(p->x, p->y, p->radian));
}

void zv_task_arith_integral(void *param)
{
    ZvTPArithIntegral *p = (ZvTPArithIntegral *)param;
    ZV_ERR_RUN(zv_arith_integral(p->src, p->dst));
}

void zv_task_arith_integral2(void *param)
{
    ZvTPArithIntegral2 *p = (ZvTPArithIntegral2 *)param;
    ZV_ERR_RUN(zv_arith_integral2(p->src, p->dst, p->dstSqrt));
}

void zv_task_arith_and(void *param)
{
    ZvTPArithAnd *p = (ZvTPArithAnd *)param;
    ZV_ERR_RUN(zv_arith_and(p->src1, p->src2, p->dst));
}

void zv_task_arith_or(void *param)
{
    ZvTPArithOr *p = (ZvTPArithOr *)param;
    ZV_ERR_RUN(zv_arith_or(p->src1, p->src2, p->dst));
}

void zv_task_arith_not(void *param)
{
    ZvTPArithNot *p = (ZvTPArithNot *)param;
    ZV_ERR_RUN(zv_arith_not(p->src, p->dst));
}

void zv_task_arith_xor(void *param)
{
    ZvTPArithXor *p = (ZvTPArithXor *)param;
    ZV_ERR_RUN(zv_arith_xor(p->src1, p->src2, p->dst));
}

void zv_task_arith_transpose(void *param)
{
    ZvTPArithTranspose *p = (ZvTPArithTranspose *)param;
    ZV_ERR_RUN(zv_arith_transpose(p->src, p->dst));
}

void zv_task_arith_invert(void *param)
{
    ZvTPArithInvert *p = (ZvTPArithInvert *)param;
    ZV_ERR_RUN(zv_arith_invert(p->src, p->dst, p->method));
}

void zv_task_arith_norm(void *param)
{
    ZvTPArithNorm *p = (ZvTPArithNorm *)param;
    *p->value = zv_arith_norm(p->mat, p->normType);
}

void zv_task_arith_matrixMult(void *param)
{
    ZvTPArithMatrixMult *p = (ZvTPArithMatrixMult *)param;
    ZV_ERR_RUN(zv_arith_matrixMult(p->mat1, p->mat2, p->dst));
}

void zv_task_arith_eigen(void *param)
{
    ZvTPArithEigen *p = (ZvTPArithEigen *)param;
    ZV_ERR_RUN(zv_arith_eigen(p->src, p->eigenvalues, p->eigenvectors, p->isSymmetric));
}

void zv_task_arith_zeroCount(void *param)
{
    ZvTPArithZeroCount *p = (ZvTPArithZeroCount *)param;
    *p->cnt = zv_arith_zeroCount(p->src);
}

void zv_task_arith_sum(void *param)
{
    ZvTPArithSum *p = (ZvTPArithSum *)param;
    ZV_ERR_RUN(zv_arith_sum(p->src, p->sum));
}

void zv_task_arith_statRow(void *param)
{
    ZvTPArithStatRow *p = (ZvTPArithStatRow *)param;
    ZV_ERR_RUN(zv_arith_statRow(p->src, p->dst, p->type));
}

void zv_task_arith_statCol(void *param)
{
    ZvTPArithStatCol *p = (ZvTPArithStatCol *)param;
    ZV_ERR_RUN(zv_arith_statCol(p->src, p->dst, p->type));
}

void zv_task_arith_mean(void *param)
{
    ZvTPArithMean *p = (ZvTPArithMean *)param;
    ZV_ERR_RUN(zv_arith_mean(p->src, p->mean));
}

void zv_task_arith_meanSdev(void *param)
{
    ZvTPArithMeanSdev *p = (ZvTPArithMeanSdev *)param;
    ZV_ERR_RUN(zv_arith_meanSdev(p->src, p->mean, p->stdDev));
}

void zv_task_arith_minMaxLoc(void *param)
{
    ZvTPArithMinMaxLoc *p = (ZvTPArithMinMaxLoc *)param;
    ZV_ERR_RUN(zv_arith_minMaxLoc(p->src, p->value, p->value+1, p->pos, p->pos+1, p->pos+2, p->pos+3));
}

void zv_task_arith_hist(void *param)
{
    ZvTPArithHist *p = (ZvTPArithHist *)param;
    ZV_ERR_RUN(zv_arith_hist(p->img, p->hist, p->size, p->low, p->upper));
}

void zv_task_ip_mirror(void *param)
{
    ZvTPIpMirror *p = (ZvTPIpMirror *)param;
    ZV_ERR_RUN(zv_ip_mirror(p->src, p->dst, p->type));
}

void zv_task_ip_rotate(void *param)
{
    ZvTPIpRotate *p = (ZvTPIpRotate *)param;
    ZV_ERR_RUN(zv_ip_rotate(p->src, p->dst, p->angle, p->interp));
}

void zv_task_ip_zoom(void *param)
{
    ZvTPIpZoom *p = (ZvTPIpZoom *)param;
    ZV_ERR_RUN(zv_ip_zoom(p->src, p->dst, p->scaleW, p->scaleH, p->interp));
}

void zv_task_ip_resize(void *param)
{
    ZvTPIpResize *p = (ZvTPIpResize *)param;
    ZV_ERR_RUN(zv_ip_resize(p->src, p->dst, p->dstW, p->dstH, p->interp));
}

void zv_task_ip_affine(void *param)
{
    ZvTPIpAffine *p = (ZvTPIpAffine *)param;
    ZV_ERR_RUN(zv_ip_affine(p->src, p->dst, p->mat, p->dstW, p->dstH, p->interp, p->border));
}

void zv_task_ip_perspective(void *param)
{
    ZvTPIpPerspective *p = (ZvTPIpPerspective *)param;
    ZV_ERR_RUN(zv_ip_perspective(p->src, p->dst, p->mat, p->dstW, p->dstH, p->interp, p->border));
}

void zv_task_ip_moments(void *param)
{
    ZvTPIpMoments *p = (ZvTPIpMoments *)param;
    *p->m = zv_ip_moments(p->binImg, p->type, p->orderX, p->orderY);
}

void zv_task_ip_rgbToGray(void *param)
{
    ZvTPIpRgbToGray *p = (ZvTPIpRgbToGray *)param;
    ZV_ERR_RUN(zv_ip_rgbToGray(p->rgb, p->gray));
}

void zv_task_ip_grayToRgb(void *param)
{
    ZvTPIpGrayToRgb *p = (ZvTPIpGrayToRgb *)param;
    ZV_ERR_RUN(zv_ip_grayToRgb(p->gray, p->rgb));
}

void zv_task_ip_colorToRgb(void *param)
{
    ZvTPIpColorToRgb *p = (ZvTPIpColorToRgb *)param;
    ZV_ERR_RUN(zv_ip_colorToRgb(p->color, p->rgb, p->colorSpace));
}

void zv_task_ip_rgbToColor(void *param)
{
    ZvTPIpRgbToColor *p = (ZvTPIpRgbToColor *)param;
    ZV_ERR_RUN(zv_ip_rgbToColor(p->rgb, p->color, p->colorSpace));
}

void zv_task_ip_bayerToRgb(void *param)
{
    ZvTPIpBayerToRgb *p = (ZvTPIpBayerToRgb *)param;
    ZV_ERR_RUN(zv_ip_bayerToRgb(p->bayer, p->rgb, p->bayerType));
}

void zv_task_ip_medianBlur(void *param)
{
    ZvTPIpMedianBlur *p = (ZvTPIpMedianBlur *)param;
    ZV_ERR_RUN(zv_ip_medianBlur(p->src, p->dst, p->size));
}

void zv_task_ip_meanBlur(void *param)
{
    ZvTPIpMeanBlur *p = (ZvTPIpMeanBlur *)param;
    ZV_ERR_RUN(zv_ip_meanBlur(p->src, p->dst, p->size));
}

void zv_task_ip_gaussBlur(void *param)
{
    ZvTPIpGaussBlur *p = (ZvTPIpGaussBlur *)param;
    ZV_ERR_RUN(zv_ip_gaussBlur(p->src, p->dst, p->size));
}

void zv_task_ip_bilateralFilter(void *param)
{
    ZvTPIpBilateralFilter *p = (ZvTPIpBilateralFilter *)param;
    ZV_ERR_RUN(zv_ip_bilateralFilter(p->src, p->dst, p->sigmaSpace, p->sigmaRange));
}

void zv_task_ip_sobel(void *param)
{
    ZvTPIpSobel *p = (ZvTPIpSobel *)param;
    ZV_ERR_RUN(zv_ip_sobel(p->src, p->dst, p->dx, p->dy, p->size));
}

void zv_task_ip_scharr(void *param)
{
    ZvTPIpScharr *p = (ZvTPIpScharr *)param;
    ZV_ERR_RUN(zv_ip_scharr(p->src, p->dst, p->dx, p->dy));
}

void zv_task_ip_laplace(void *param)
{
    ZvTPIpLaplace *p = (ZvTPIpLaplace *)param;
    ZV_ERR_RUN(zv_ip_laplace(p->src, p->dst, p->size));
}

void zv_task_ip_canny(void *param)
{
    ZvTPIpCanny *p = (ZvTPIpCanny *)param;
    ZV_ERR_RUN(zv_ip_canny(p->img, p->dst, p->thresh1, p->thresh2, p->size));
}

void zv_task_ip_equalizeHist(void *param)
{
    ZvTPIpEqualizeHist *p = (ZvTPIpEqualizeHist *)param;
    ZV_ERR_RUN(zv_ip_equalizeHist(p->src, p->dst));
}

void zv_task_ip_dilate(void *param)
{
    ZvTPIpDilate *p = (ZvTPIpDilate *)param;
    ZV_ERR_RUN(zv_ip_dilate(p->src, p->dst, p->seWidth, p->seHeight));
}

void zv_task_ip_erode(void *param)
{
    ZvTPIpErode *p = (ZvTPIpErode *)param;
    ZV_ERR_RUN(zv_ip_erode(p->src, p->dst, p->seWidth, p->seHeight));
}

void zv_task_ip_opening(void *param)
{
    ZvTPIpOpening *p = (ZvTPIpOpening *)param;
    ZV_ERR_RUN(zv_ip_opening(p->src, p->dst, p->seWidth, p->seHeight));
}

void zv_task_ip_closing(void *param)
{
    ZvTPIpClosing *p = (ZvTPIpClosing *)param;
    ZV_ERR_RUN(zv_ip_closing(p->src, p->dst, p->seWidth, p->seHeight));
}

void zv_task_ip_morphSe(void *param)
{
    ZvTPIpMorphSe *p = (ZvTPIpMorphSe *)param;
    ZV_ERR_RUN(zv_ip_morphSe(p->kernel, p->shape, p->sizeX, p->sizeY, p->anchorX, p->anchorY));
}

void zv_task_ip_morph(void *param)
{
    ZvTPIpMorph *p = (ZvTPIpMorph *)param;
    ZV_ERR_RUN(zv_ip_morph(p->src, p->dst, p->kernel, p->op, p->anchorX, p->anchorY, p->iter, p->border));
}

void zv_task_ip_label(void *param)
{
    ZvTPIpLabel *p = (ZvTPIpLabel *)param;
    ZV_ERR_RUN(zv_ip_label(p->src, p->label, p->connectivity));
}

void zv_task_ip_threshold(void *param)
{
    ZvTPIpThreshold *p = (ZvTPIpThreshold *)param;
    ZV_ERR_RUN(zv_ip_threshold(p->src, p->dst, p->thresh0, p->thresh1, p->isInv));
}

void zv_task_ip_adpThreshold(void *param)
{
    ZvTPIpAdpThreshold *p = (ZvTPIpAdpThreshold *)param;
    ZV_ERR_RUN(zv_ip_adpThreshold(p->src, p->thresh, p->dst, p->offset, p->isInv));
}

void zv_task_ip_autoThreshold(void *param)
{
    ZvTPIpAutoThreshold *p = (ZvTPIpAutoThreshold *)param;
    ZV_ERR_RUN(zv_ip_autoThreshold(p->src, p->dst, p->thresh));
}

void zv_task_match_fastTempl(void *param)
{
    ZvTPMatchFastTempl *p = (ZvTPMatchFastTempl *)param;
    ZV_ERR_RUN(zv_match_fastTempl(p->img, p->templ, p->pos, p->pos+1, p->method));
}

void zv_task_match_bestTempl(void *param)
{
    ZvTPMatchBestTempl *p = (ZvTPMatchBestTempl *)param;
    ZV_ERR_RUN(zv_match_bestTempl(p->img, p->templ, p->minScore, p->mRst, p->mRst+1, p->mRst+2, p->isSubPix, p->polar));
}

void zv_task_match_multiTempl(void *param)
{
    ZvTPMatchMultiTempl *p = (ZvTPMatchMultiTempl *)param;
    ZV_ERR_RUN(zv_match_multiTempl(p->img, p->templ, p->matches, p->minScore, p->nums, p->minDist, p->isSubPix, p->polar));
}

void zv_task_match_nccCreate(void *param)
{
    ZvTPMatchNccCreate *p = (ZvTPMatchNccCreate *)param;
    ZV_ERR_RUN(zv_match_nccCreate(p->mod, p->templ, p->angleStart, p->angleExt, p->angleStep, p->numLevel));
}

void zv_task_match_nccFind(void *param)
{
    ZvTPMatchNccFind *p = (ZvTPMatchNccFind *)param;
    ZV_ERR_RUN(zv_match_nccFind(p->mod, p->img, p->matchs, p->NumLevel, p->minScore, p->x, p->y, p->minDist, p->isSubPix));
}

void zv_task_meas_projection(void *param)
{
    ZvTPMeasProjection *p = (ZvTPMeasProjection *)param;
    ZV_ERR_RUN(zv_meas_projection(p->img, p->proj, p->mr));
}

void zv_task_meas_pos(void *param)
{
    ZvTPMeasPos *p = (ZvTPMeasPos *)param;
    ZV_ERR_RUN(zv_meas_pos(p->img, p->pts, p->mr, p->filterSize, p->thresh, p->type, p->select));
}

void zv_task_meas_pairs(void *param)
{
    ZvTPMeasPairs *p = (ZvTPMeasPairs *)param;
    ZV_ERR_RUN(zv_meas_pairs(p->img, p->pairs, p->mr, p->filterSize, p->thresh, p->type, p->select));
}

void zv_task_meas_line(void *param)
{
    ZvTPMeasLine *p = (ZvTPMeasLine *)param;
    ZV_ERR_RUN(zv_meas_line(p->img, p->mr, p->line, p->line+1, p->line+2, p->line+3, p->pts));
}

void zv_task_meas_circle(void *param)
{
    ZvTPMeasCircle *p = (ZvTPMeasCircle *)param;
    ZV_ERR_RUN(zv_meas_circle(p->img, p->mr, p->circle, p->circle+1, p->circle+2, p->pts));
}

void zv_task_feat_houghLine(void *param)
{
    ZvTPFeatHoughLine *p = (ZvTPFeatHoughLine *)param;
    ZV_ERR_RUN(zv_feat_houghLine(p->img, p->lines, p->rho, p->theta, p->thresh, p->minLinelen, p->maxLineGap));
}

void zv_task_feat_houghCircle(void *param)
{
    ZvTPFeatHoughCircle *p = (ZvTPFeatHoughCircle *)param;
    ZV_ERR_RUN(zv_feat_houghCircle(p->img, p->circles, p->minDist, p->param1, p->param2, p->minR, p->maxR));
}

void zv_task_tk_getRigid(void *param)
{
    ZvTPTkGetRigid *p = (ZvTPTkGetRigid *)param;
    ZV_ERR_RUN(zv_tk_getRigid(p->mat, p->from, p->to));
}

void zv_task_tk_getRigidVector(void *param)
{
    ZvTPTkGetRigidVector *p = (ZvTPTkGetRigidVector *)param;
    ZV_ERR_RUN(zv_tk_getRigidVector(p->mat, p->xFrom, p->yFrom, p->angleFrom, p->xTo, p->yTo, p->angleTo));
}

void zv_task_tk_getSimilarity(void *param)
{
    ZvTPTkGetSimilarity *p = (ZvTPTkGetSimilarity *)param;
    ZV_ERR_RUN(zv_tk_getSimilarity(p->mat, p->from, p->to));
}

void zv_task_tk_getAffine(void *param)
{
    ZvTPTkGetAffine *p = (ZvTPTkGetAffine *)param;
    ZV_ERR_RUN(zv_tk_getAffine(p->mat, p->from, p->to));
}

void zv_task_tk_estimateSimilarity(void *param)
{
    ZvTPTkEstimateSimilarity *p = (ZvTPTkEstimateSimilarity *)param;
    ZV_ERR_RUN(zv_tk_estimateSimilarity(p->from, p->to, p->mat, p->thresh, p->confidence, p->isInliers));
}

void zv_task_tk_estimateAffine(void *param)
{
    ZvTPTkEstimateAffine *p = (ZvTPTkEstimateAffine *)param;
    ZV_ERR_RUN(zv_tk_estimateAffine(p->from, p->to, p->mat, p->thresh, p->confidence, p->isInliers));
}

void zv_task_tk_affineTrans(void *param)
{
    ZvTPTkAffineTrans *p = (ZvTPTkAffineTrans *)param;
    ZV_ERR_RUN(zv_tk_affineTrans(p->mat, p->from, p->to, p->ptNum));
}

void zv_task_tk_getProjective(void *param)
{
    ZvTPTkGetProjective *p = (ZvTPTkGetProjective *)param;
    ZV_ERR_RUN(zv_tk_getProjective(p->mat, p->from, p->to));
}

void zv_task_tk_projectiveTrans2d(void *param)
{
    ZvTPTkProjectiveTrans2d *p = (ZvTPTkProjectiveTrans2d *)param;
    ZV_ERR_RUN(zv_tk_projectiveTrans2d(p->mat, p->from, p->to, p->num));
}

void zv_task_tk_projectiveTrans3d(void *param)
{
    ZvTPTkProjectiveTrans3d *p = (ZvTPTkProjectiveTrans3d *)param;
    ZV_ERR_RUN(zv_tk_projectiveTrans3d(p->mat, p->from, p->to, p->num));
}

void zv_task_tk_distanceContP(void *param)
{
    ZvTPTkDistanceContP *p = (ZvTPTkDistanceContP *)param;
    *p->dist = zv_tk_distanceContP(p->cont, p->px, p->py);
}

void zv_task_tk_fitLine2D(void *param)
{
    ZvTPTkFitLine2D *p = (ZvTPTkFitLine2D *)param;
    ZV_ERR_RUN(zv_tk_fitLine2D(p->pts, p->line, p->line+1, p->line+2, p->line+3));
}

void zv_task_tk_fitEllipse(void *param)
{
    ZvTPTkFitEllipse *p = (ZvTPTkFitEllipse *)param;
    ZV_ERR_RUN(zv_tk_fitEllipse(p->pts, p->ellipse, p->ellipse+1, p->ellipse+2, p->ellipse+3, p->ellipse+4));
}

void zv_task_tk_intersectRect2(void *param)
{
    ZvTPTkIntersectRect2 *p = (ZvTPTkIntersectRect2 *)param;
    ZV_ERR_RUN(zv_tk_intersectRect2(p->pts, p->R1X, p->R1Y, p->R1W, p->R1H, p->R1Angle, p->R2X, p->R2Y, p->R2W, p->R2H, p->R2Angle));
}

void zv_task_tk_fitLineEx(void *param)
{
    ZvTPTkFitLineEx *p = (ZvTPTkFitLineEx *)param;
    ZV_ERR_RUN(zv_tk_fitLineEx(p->pts, p->line, p->method, p->reps, p->aeps));
}

void zv_task_tk_fitEllipseEx(void *param)
{
    ZvTPTkFitEllipseEx *p = (ZvTPTkFitEllipseEx *)param;
    ZV_ERR_RUN(zv_tk_fitEllipseEx(p->pts, p->ellipse, p->ellipse+1, p->ellipse+2, p->ellipse+3, p->ellipse+4, p->method));
}

void zv_task_tk_fitPolyn(void *param)
{
    ZvTPTkFitPolyn *p = (ZvTPTkFitPolyn *)param;
    ZV_ERR_RUN(zv_tk_fitPolyn(p->pts, p->order, p->param));
}

void zv_task_dra_line(void *param)
{
    ZvTPDraLine *p = (ZvTPDraLine *)param;
    ZV_ERR_RUN(zv_dra_line(p->img, p->x1, p->y1, p->x2, p->y2, p->color));
}

void zv_task_dra_rect(void *param)
{
    ZvTPDraRect *p = (ZvTPDraRect *)param;
    ZV_ERR_RUN(zv_dra_rect(p->img, p->x, p->y, p->w, p->h, p->color));
}

void zv_task_dra_rect2(void *param)
{
    ZvTPDraRect2 *p = (ZvTPDraRect2 *)param;
    ZV_ERR_RUN(zv_dra_rect2(p->img, p->cx, p->cy, p->width, p->height, p->angle, p->color));
}

void zv_task_dra_circle(void *param)
{
    ZvTPDraCircle *p = (ZvTPDraCircle *)param;
    ZV_ERR_RUN(zv_dra_circle(p->img, p->cx, p->cy, p->r, p->color));
}

void zv_task_dra_ellipse(void *param)
{
    ZvTPDraEllipse *p = (ZvTPDraEllipse *)param;
    ZV_ERR_RUN(zv_dra_ellipse(p->img, p->cx, p->cy, p->xR, p->yR, p->angle, p->color));
}

void zv_task_dra_ellipseArc(void *param)
{
    ZvTPDraEllipseArc *p = (ZvTPDraEllipseArc *)param;
    ZV_ERR_RUN(zv_dra_ellipseArc(p->img, p->cx, p->cy, p->xR, p->yR, p->angle, p->angleStart, p->angleEnd, p->color));
}

void zv_task_dra_arrow(void *param)
{
    ZvTPDraArrow *p = (ZvTPDraArrow *)param;
    ZV_ERR_RUN(zv_dra_arrow(p->img, p->x1, p->y1, p->x2, p->y2, p->color, p->size));
}

void zv_task_dra_polygon(void *param)
{
    ZvTPDraPolygon *p = (ZvTPDraPolygon *)param;
    ZV_ERR_RUN(zv_dra_polygon(p->img, p->pts, p->isClosed, p->color));
}

void zv_task_dra_contour(void *param)
{
    ZvTPDraContour *p = (ZvTPDraContour *)param;
    ZV_ERR_RUN(zv_dra_contour(p->img, p->cont, p->color));
}

void zv_task_dra_marker(void *param)
{
    ZvTPDraMarker *p = (ZvTPDraMarker *)param;
    ZV_ERR_RUN(zv_dra_marker(p->img, p->x, p->y, p->type, p->size, p->color));
}

void zv_task_dra_text(void *param)
{
    ZvTPDraText *p = (ZvTPDraText *)param;
    ZV_ERR_RUN(zv_dra_text(p->img, p->text, p->x, p->y, p->scale, p->color));
}

void zv_task_dra_mask(void *param)
{
    ZvTPDraMask *p = (ZvTPDraMask *)param;
    ZV_ERR_RUN(zv_dra_mask(p->img, p->mask));
}

void zv_task_dra_measurer(void *param)
{
    ZvTPDraMeasurer *p = (ZvTPDraMeasurer *)param;
    ZV_ERR_RUN(zv_dra_measurer(p->img, p->mr, p->color, p->subColor));
}

