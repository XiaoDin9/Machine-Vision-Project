#include "zv_private.h"
#include "zv_cam_gige_vision.h"
#include "zv_camera.h"
#include "zv_cam_opencv.h"


#define ZV_USE_OPENCV

#ifdef ZV_USE_OPENCV
#pragma comment( lib, "vfw32.lib" ) 
#pragma comment( lib, "comctl32.lib" ) 

cv::VideoCapture *cvCap[ZV_CAM_MAX_NUM] = { 0 };

static bool zv_cam_cv_getPropId(int prop, int &id)
{
    static int cvPropCvt[] = {
        CV_CAP_PROP_GIGA_FRAME_OFFSET_X,
        CV_CAP_PROP_GIGA_FRAME_OFFSET_Y,
        CV_CAP_PROP_FRAME_WIDTH,
        CV_CAP_PROP_FRAME_HEIGHT,
        CV_CAP_PROP_EXPOSURE,
        CV_CAP_PROP_GAIN,
    };

    if (sizeof(cvPropCvt)/sizeof(cvPropCvt[0]) <= prop)
    {
        return false;
    }

    id = cvPropCvt[prop];
    return true;
}
#endif

int zv_cam_cv_release(int scanId)
{
#ifdef ZV_USE_OPENCV
    delete cvCap[scanId];
    cvCap[scanId] = NULL;
    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_cv_scan(int startScanId)
{
#ifdef ZV_USE_OPENCV
    int cnt = 0;
    for (int i = 0; i < ZV_CAM_MAX_NUM - startScanId; i++)
    {
        zv_cam_cv_release(cnt + startScanId);
        //需传入domain_offset，获取确定的相机打开方式
        cv::VideoCapture *p = new cv::VideoCapture(i);
        if (!p)
            break;
        if (!p->isOpened())
        {
            delete p;
        }
        else
        {
            cvCap[cnt + startScanId] = p;
            cnt++;
        }
    }
    
    return cnt;
#endif
    return 0;
}

int zv_cam_cv_status(int scanId)
{
#ifdef ZV_USE_OPENCV
    if (NULL != cvCap[scanId])
    {
        return ZV_CAM_ST_OPENED;
    }
#endif
    return ZV_CAM_ST_ERROR;
}

int zv_cam_cv_close(int scanId)
{
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_cv_grab(cv::Mat &img, int scanId)
{
#ifdef ZV_USE_OPENCV
    if (cvCap[scanId] && cvCap[scanId]->read(img))
    {
        if (3 == img.channels())
        {
            cvtColor(img, img, cv::COLOR_BGR2RGB);
        }
        if (4 == img.channels())
        {
            cvtColor(img, img, cv::COLOR_BGRA2RGBA);
        }
        return ZV_ST_OK;
    }
    return ZV_ERR_CAM_GRAB;

#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_cv_roi(int scanId, int &offsetX, int &offsetY, int &width, int &height, bool isGet)
{
#ifdef ZV_USE_OPENCV
    double valX = offsetX;
    double valY = offsetY;
    double valW = width;
    double valH = height;

    if (!isGet)
    {
        double val = 0;
        ZV_RUN_RTN(zv_cam_cv_double(scanId, CV_CAP_PROP_GIGA_FRAME_OFFSET_X, val, isGet));
        ZV_RUN_RTN(zv_cam_cv_double(scanId, CV_CAP_PROP_GIGA_FRAME_OFFSET_Y, val, isGet));
    }
    ZV_RUN_RTN(zv_cam_cv_double(scanId, CV_CAP_PROP_GIGA_FRAME_OFFSET_X, valX, isGet));
    ZV_RUN_RTN(zv_cam_cv_double(scanId, CV_CAP_PROP_GIGA_FRAME_OFFSET_Y, valY, isGet));
    ZV_RUN_RTN(zv_cam_cv_double(scanId, CV_CAP_PROP_FRAME_WIDTH, valW, isGet));
    ZV_RUN_RTN(zv_cam_cv_double(scanId, CV_CAP_PROP_FRAME_HEIGHT, valH, isGet));

    if (isGet)
    {
        offsetX = cvRound(valX);
        offsetY = cvRound(valY);
        width = cvRound(valW);
        height = cvRound(valH);
    }

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_cv_double(int scanId, int prop, double &value, bool isGet)
{
#ifdef ZV_USE_OPENCV
    int propId = prop;
    if (!zv_cam_cv_getPropId(prop, propId))
        return ZV_ERR_CAM_PARAM_UNDEF;
    if (isGet)
    {
        value = cvCap[scanId]->get(propId);
        if (fabs(value - (-1.0)) < 0.00001)
        {
            value = 0;
            return ZV_ERR_CAM_PARAM_RD;
        }
    }
    else
    {
        if (!cvCap[scanId]->set(propId, value))
        {
            return ZV_ERR_CAM_PARAM_WR;
        }
    }
    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}
