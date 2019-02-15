#include "zv_private.h"
#include "zv_cam_gige_vision.h"
#include "zv_camera.h"
#include "system/zv_system.h"
#include "zv_cam_opencv.h"
#include "zv_cam_basler.h"
#include "zv_cam_tis.h"


typedef enum _ZvCamOpenType
{
    ZV_CAMTYPE_INIT,
    ZV_CAMTYPE_GIGE,
    ZV_CAMTYPE_V4L2,
    ZV_CAMTYPE_ARAVIS,
    ZV_CAMTYPE_OPENCV,
    ZV_CAMTYPE_BASLER,
    ZV_CAMTYPE_TIS,
}ZvCamOpenType;

typedef struct _ZvCamera
{
    ZvCamOpenType type; //相机的类型和打开方式，用于识别相机结构体类型。
}ZvCamera;

ZvCamera s_zv_cam_camera[ZV_CAM_MAX_NUM];

int g_zv_cam_count = 0;
int s_zv_cam_scanId[ZV_CAM_MAX_NUM] = { -1 };


static int zv_cam_release(int scanId)
{
    if (scanId >= g_zv_cam_count)
    {
        return ZV_ERR_CAM_SCANID;
    }

    //对相机进行释放处理
    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_INIT:
        return ZV_WARN_RELE_UNINIT;
    case ZV_CAMTYPE_OPENCV:
        ZV_RUN_RTN(zv_cam_cv_release(scanId));
        break;
    case ZV_CAMTYPE_BASLER:
        ZV_RUN_RTN(zv_cam_basler_release(scanId));
        break;
    case ZV_CAMTYPE_TIS:
        ZV_RUN_RTN(zv_cam_tis_release(scanId));
        break;
    default:
        return ZV_ERR_G_NOT_SUPPORT;
    }

    s_zv_cam_camera[scanId].type = ZV_CAMTYPE_INIT;
    return ZV_ST_OK;
}

inline int zv_cam_getScanId(int camId)
{
    if (camId >= ZV_CAM_MAX_NUM)
    {
        return -ZV_ERR_CAM_CAMID;
    }

    if (-1 == s_zv_cam_scanId[camId])
    {
        return -ZV_ERR_CAM_UNBOUND;
    }
    return s_zv_cam_scanId[camId];
}

//软件启动时调用一次，用于环境准备；BASIC由解释器调用。
int zv_cam_init()
{
    for (int i = 0; i < ZV_CAM_MAX_NUM; i++)
    {
        s_zv_cam_camera[i].type = ZV_CAMTYPE_INIT;
    }
    ZV_RUN_RTN(zv_cam_basler_init());
    ZV_RUN_RTN(zv_cam_tis_init());
    return ZV_ST_OK;
}

//软件退出时调用，用于环境释放；BASIC由解释器调用。
int zv_cam_exit()
{
    for (int i = 0; i < g_zv_cam_count; i++)
    {
        zv_cam_release(i);
    }

    ZV_RUN_RTN(zv_cam_basler_exit());
    ZV_RUN_RTN(zv_cam_tis_exit());

    return ZV_ST_OK;
}

/*
需要加锁
扫描相机
*/
int zv_cam_scan(char *type)
{
    ZV_CHK_NULL1(type);
    g_zv_cam_count = 0;
    vector<string> types = zv_sys_stringSplit(string(type), ';');
    if (0 == types.size())
    {
        return ZV_ERR_FA_NULL_1;
    }

    ZvCamOpenType openType = ZV_CAMTYPE_INIT;
    for (int i = 0; i < types.size(); i++)
    {
        int rst = 0;
        if ("Basler" == types[i])
        {
            rst = zv_cam_basler_scan(g_zv_cam_count);  //返回扫描到的相机数量
            openType = ZV_CAMTYPE_BASLER;
        }
        else if ("TIS" == types[i])
        {
            rst = zv_cam_tis_scan(g_zv_cam_count);
            openType = ZV_CAMTYPE_TIS;
        }
        else if ("SampleAll" == types[i])
        {
            rst = zv_cam_cv_scan(g_zv_cam_count);
            openType = ZV_CAMTYPE_OPENCV;
        }
        else
        {
            g_zv_cam_count = 0;
            return ZV_ERR_G_NOT_SUPPORT;
        }

        if (0 >= rst)
        {
            continue;
        }

        int k = g_zv_cam_count;
        g_zv_cam_count += rst;
        if (g_zv_cam_count > ZV_CAM_MAX_NUM)
        {
            g_zv_cam_count = 0; 
            return ZV_ERR_CAM_SCAN;
        }

        for (; k < g_zv_cam_count; k++)
        {
            s_zv_cam_camera[k].type = openType;
        }
    }

    return 0 == g_zv_cam_count ? ZV_ERR_CAM_NONE : ZV_ST_OK;
}

//SN号、IP、MAC、用户自定义名字UserID、设备类型（GIGE）
int zv_cam_getInfo(int scanId, int info, char *value, int valueLen)
{
    if (NULL == value)
    {
        return ZV_ERR_FA_NULL_3;
    }
    if (scanId >= g_zv_cam_count)
    {
        return ZV_ERR_CAM_SCANID;
    }

    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_BASLER:
        return zv_cam_basler_getInfo(scanId, info, value, valueLen);
    case ZV_CAMTYPE_TIS:
        return zv_cam_tis_getInfo(scanId, info, value, valueLen);
    default:
        break;
    }

   return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_open(int camId, int scanId)
{
    if (camId >= ZV_CAM_MAX_NUM)
    {
        return ZV_ERR_CAM_CAMID;
    }
    if (scanId >= g_zv_cam_count)
    {
        return ZV_ERR_CAM_SCANID;
    }

    int stCode = ZV_ERR_G_NOT_SUPPORT;
    s_zv_cam_scanId[camId] = -1; //取消绑定
    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_OPENCV:
        stCode = ZV_ST_OK;
        break;
    case ZV_CAMTYPE_BASLER:
        stCode = zv_cam_basler_open(scanId);
        break;
    case ZV_CAMTYPE_TIS:
        stCode = zv_cam_tis_open(scanId);
        break;
    default:
        break;
    }

    if (ZV_ST_OK == stCode)
    {
        s_zv_cam_scanId[camId] = scanId;
    }
    return stCode;
}

int zv_cam_status(int camId)
{
    if ((uint)camId >= ZV_CAM_MAX_NUM)
    {
        return ZV_CAM_ST_ERROR;
    }
    int scanId = s_zv_cam_scanId[camId];
    if (-1 == scanId)
    {
        return ZV_CAM_ST_NULL;
    }
    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_OPENCV:
        return zv_cam_cv_status(scanId);
    case ZV_CAMTYPE_BASLER:
        return zv_cam_basler_status(scanId);
    case ZV_CAMTYPE_TIS:
        return zv_cam_tis_status(scanId);
    default:
        return ZV_CAM_ST_ERROR;
    }
}

int zv_cam_close(int camId)
{
    if (camId >= ZV_CAM_MAX_NUM)
    {
        return ZV_CAM_ST_ERROR;
    }
    int scanId = s_zv_cam_scanId[camId];
    if (-1 == scanId)
    {
        return ZV_CAM_ST_NULL;
    }
    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_OPENCV:
        return ZV_ERR_G_NOT_SUPPORT;
    case ZV_CAMTYPE_BASLER:
        return zv_cam_basler_close(scanId);
    case ZV_CAMTYPE_TIS:
        return zv_cam_tis_close(scanId);
    default:
        return ZV_ERR_G_NOT_SUPPORT;
    }
}

int zv_cam_grab(ZvImage img, int camId)
{
    ZV_CHK_NULL1(img);
    int scanId = zv_cam_getScanId(camId);
    if (0 > scanId)
    {
        return -scanId;
    }

    cv::Mat _img = ZV_ADP_IMG_GETM(img);
    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_OPENCV:
        ZV_RUN_RTN(zv_cam_cv_grab(_img, scanId));
        break;
    case ZV_CAMTYPE_BASLER:
        ZV_RUN_RTN(zv_cam_basler_grab(_img, scanId));
        break;
    case ZV_CAMTYPE_TIS:
        ZV_RUN_RTN(zv_cam_tis_grab(_img, scanId));
        break;
    default:
        return ZV_ERR_G_NOT_SUPPORT;
    }

    ZV_ADP_IMG_SETM(img, _img);
    return ZV_ST_OK;
}

int zv_cam_getIO(int camId)
{
    return 0;
}

int zv_cam_setIO(int camId, int offset)
{
    return ZV_ST_OK;
}

int zv_cam_payloadSize(int camId)
{
    int scanId = zv_cam_getScanId(camId);
    if (0 > scanId)
    {
        return 0;
    }

    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_TIS:
        return zv_cam_tis_payloadSize(scanId);
    case ZV_CAMTYPE_BASLER:
        return zv_cam_basler_payloadSize(scanId);
    default:
        break;
    }
    return 0;
}

int zv_cam_getROI(int camId, int *offsetX, int *offsetY, int *width, int *height)
{
    ZV_CHK_NULL5(g_zv_adp_notNull, offsetX, offsetY, width, height);
    int scanId = zv_cam_getScanId(camId);
    if (0 > scanId)
    {
        return -scanId;
    }

    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_OPENCV:
        return zv_cam_cv_roi(scanId, *offsetX, *offsetY, *width, *height, true);
    case ZV_CAMTYPE_BASLER:
        return zv_cam_basler_getROI(scanId, *offsetX, *offsetY, *width, *height);
    case ZV_CAMTYPE_TIS:
        return zv_cam_tis_getROI(scanId, *offsetX, *offsetY, *width, *height);
    default:
        break;
    }

    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_setROI(int camId, int offsetX, int offsetY, int width, int height)
{
    int scanId = zv_cam_getScanId(camId);
    if (0 > scanId)
    {
        return -scanId;
    }

    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_OPENCV:
        return zv_cam_cv_roi(scanId, offsetX, offsetY, width, height, false);
    case ZV_CAMTYPE_BASLER:
        return zv_cam_basler_setROI(scanId, offsetX, offsetY, width, height);
    case ZV_CAMTYPE_TIS:
        return zv_cam_tis_setROI(scanId, offsetX, offsetY, width, height);
    default:
        break;
    }

    return ZV_ERR_G_NOT_SUPPORT;
}

double zv_cam_getExposure(int camId)
{
    int scanId = zv_cam_getScanId(camId);
    if (0 > scanId)
    {
        return 0;
    }

    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_OPENCV:
    {
        double val = 0;
        zv_cam_cv_double(scanId, CV_CAP_PROP_EXPOSURE, val, true);
        return val;
    }
    case ZV_CAMTYPE_BASLER:
    {
        char val[ZV_DOUBLE_STR_LEN] = { 0 };
        zv_cam_basler_param(scanId, ZV_CAM_P_EXPOSURE, val, sizeof(val), true);
        return atof(val);
    }
    case ZV_CAMTYPE_TIS:
    {
        double val = 0;
        zv_cam_tis_value(scanId, ZV_CAM_PV_EXPOSURE, val, true);
        return val;
    }
    default:
        break;
    }
    return 0;
}

int zv_cam_setExposure(int camId, double time)
{
    int scanId = zv_cam_getScanId(camId);
    if (0 > scanId)
    {
        return -scanId;
    }

    switch (s_zv_cam_camera[scanId].type)
    {
    case ZV_CAMTYPE_OPENCV:
    {
        return zv_cam_cv_double(scanId, CV_CAP_PROP_EXPOSURE, time, false);
    }
    case ZV_CAMTYPE_BASLER:
    {
        char val[ZV_DOUBLE_STR_LEN] = { 0 };
        snprintf(val, sizeof(val), "%.7f", time);
        return zv_cam_basler_param(scanId, ZV_CAM_P_EXPOSURE, val, sizeof(val), false);
    }
    case ZV_CAMTYPE_TIS:
    {
        return zv_cam_tis_value(scanId, ZV_CAM_PV_EXPOSURE, time, false);
    }
    default:
        break;
    }
    return ZV_ERR_G_NOT_SUPPORT;
}

static int zv_cam_param(int camId, char *param, char *value, int valueLen, bool isGet)
{
    ZV_CHK_NULL3(g_zv_adp_notNull, param, value);
    if (camId >= ZV_CAM_MAX_NUM)
    {
        return ZV_ERR_CAM_CAMID;
    }
    int scanId = s_zv_cam_scanId[camId];
    if (-1 == scanId)
    {
        return ZV_ERR_CAM_UNBOUND;
    }
    if (ZV_CAMTYPE_BASLER == s_zv_cam_camera[scanId].type)
    {
        return zv_cam_basler_param(scanId, param, value, valueLen, isGet);
    }

    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_getParam(int camId, char *param, char *value, int valueLen)
{
    return zv_cam_param(camId, param, value, valueLen, true);
}

int zv_cam_setParam(int camId, char *param, char *value)
{
    return zv_cam_param(camId, param, value, (int)strlen(value), false);
}

static int zv_cam_value(int camId, int prop, double &value, bool isGet)
{
    if (camId >= ZV_CAM_MAX_NUM)
    {
        return ZV_ERR_CAM_CAMID;
    }
    int scanId = s_zv_cam_scanId[camId];
    if (-1 == scanId)
    {
        return ZV_ERR_CAM_UNBOUND;
    }

    if (ZV_CAMTYPE_OPENCV == s_zv_cam_camera[scanId].type)
    {
        return zv_cam_cv_double(scanId, prop, value, isGet);
    }
    else if (ZV_CAMTYPE_TIS == s_zv_cam_camera[scanId].type)
    {
        return zv_cam_tis_value(scanId, prop, value, isGet);
    }

    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_getValue(int camId, int prop, double *value)
{
    if (NULL == value)
    {
        return ZV_ERR_FA_NULL_3;
    }
    return zv_cam_value(camId, prop, *value, true);
}

int zv_cam_setValue(int camId, int prop, double value)
{
    return zv_cam_value(camId, prop, value, false);
}

int zv_cam_startGrabbing(int camId, int bufCount)
{
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_isGrabbing(int camId, int *isGrabbing)
{
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_retrieve(ZvImage img, int camId, int bufId)
{
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_reset(int camId)
{
    return ZV_ERR_G_NOT_SUPPORT;
}
