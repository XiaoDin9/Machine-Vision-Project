#include "zv_private.h"
#include "zv_cam_gige_vision.h"
#include "zv_camera.h"
#include "zv_cam_tis.h"


#define ZV_USE_TIS

#ifdef ZV_USE_TIS
#include <tisudshl.h>
//#include "tisgrabber.h"
//#pragma comment(lib, "..\\tisgrabber.lib")
using namespace DShowLib;

struct _propElement
{
    GUID prop;
    GUID element;
};

vector <struct _propElement> s_zv_cam_tisCmdProp = {
    { VCDID_Trigger, VCDElement_SoftwareTrigger } };

vector <struct _propElement> s_zv_cam_tisBoolProp = {
    { VCDID_Exposure, VCDElement_Value },
    { VCDID_Gain, VCDElement_Value },
    { VCDID_TriggerMode,VCDElement_TriggerPolarity } };

vector <struct _propElement> s_zv_cam_tisValueProp = {
    { VCDID_Exposure, VCDElement_Value },
    { VCDID_Gain, VCDElement_Value },
    { VCDID_Gamma, VCDElement_Value }};

typedef struct _ZvCamTisData
{
    DShowLib::Grabber *cam; //使用数据类型会导致dll加载卡死和程序无法退出
    tIVCDPropertyItemsPtr pProps;
    smart_com<IFrameFilter> filterRF;
    smart_com<IFrameFilter> filterROI;
    tFrameFilterList filterChain;
}ZvCamTisData;

static ZvCamTisData s_zv_cam_tis_data[ZV_CAM_MAX_NUM];
static int s_zv_cam_tis_startScanId = 0;
static Grabber::tVidCapDevListPtr s_zv_cam_tis_devices;
#endif


int zv_cam_tis_release(int scanId)
{
#ifdef ZV_USE_TIS
    s_zv_cam_tis_data[scanId].cam->closeDev();
    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_tis_init()
{
#ifdef ZV_USE_TIS
    if (!DShowLib::InitLibrary(""))
    {
        return ZV_ERR_CAM_INIT_TIS;
    }
    for (int i = 0; i < ZV_CAM_MAX_NUM; i++)
    {
        s_zv_cam_tis_data[i].cam = new Grabber();
        s_zv_cam_tis_data[i].filterChain.clear();
    }
#endif
    return ZV_ST_OK;
}

int zv_cam_tis_exit()
{
#ifdef ZV_USE_TIS
    s_zv_cam_tis_devices = 0;
    for (int i = 0; i < ZV_CAM_MAX_NUM; i++)
    {
        delete s_zv_cam_tis_data[i].cam;
        s_zv_cam_tis_data[i].cam = NULL;
        s_zv_cam_tis_data[i].pProps = 0;
    }
    DShowLib::ExitLibrary();
#endif
    return ZV_ST_OK;
}

int zv_cam_tis_scan(int startScanId)
{
#ifdef ZV_USE_TIS
    s_zv_cam_tis_startScanId = startScanId;
    s_zv_cam_tis_devices = s_zv_cam_tis_data[0].cam->getAvailableVideoCaptureDevices();
    if (s_zv_cam_tis_devices != NULL)
    {
        return (int)s_zv_cam_tis_devices->size();
    }
#endif
    return 0;
}

int zv_cam_tis_getInfo(int scanId, int prop, char *value, int valueLen)
{
#ifdef ZV_USE_TIS
    Grabber::tVideoCaptureDeviceItem &item = (*s_zv_cam_tis_devices)[scanId - s_zv_cam_tis_startScanId];
    switch (prop)
    {
    case ZV_CAM_PS_SN:
    {
        int64 sn = 0;
        if (!item.getSerialNumber(sn))
        {
            return ZV_ERR_CAM_PARAM_RD;
        }
        snprintf(value, valueLen, "%I64X", sn);
        break;
    }
    case ZV_CAM_PS_DISPLAY:
        snprintf(value, valueLen, "%s", item.getUniqueName().c_str());
        break;
    case ZV_CAM_PS_MODEL:
        snprintf(value, valueLen, "%s", item.getName().c_str());
        break;
    case ZV_CAM_PS_DEV_NAME:
        snprintf(value, valueLen, "%s", item.toString().c_str());
        break;
    default:
        return ZV_ERR_CAM_PARAM_UNDEF;
    }
    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_tis_open(int scanId)
{
#ifdef ZV_USE_TIS
    ZvCamTisData & tisData = s_zv_cam_tis_data[scanId];
    if (!tisData.cam->isDevOpen())
    {
        if (!tisData.cam->openDev((*s_zv_cam_tis_devices)[scanId - s_zv_cam_tis_startScanId]))
        {
            return ZV_ERR_CAM_OPEN;
        }

        tFrameHandlerSinkPtr pSink = FrameHandlerSink::create(3);
        pSink->setSnapMode(true);
        tisData.cam->setSinkType(pSink);

        tisData.filterChain.clear();
        tisData.filterRF = FilterLoader::createFilter("Rotate Flip", "stdfiltersd.ftf");
        tisData.filterROI = FilterLoader::createFilter("ROI");
        if (tisData.filterRF != NULL)  //采集的图像出现了未知原因的垂直镜像，添加此功能进行还原
        {
            tisData.filterRF->setParameter("Flip H", false);
            tisData.filterRF->setParameter("Flip V", true);
            tisData.filterChain.push_back(tisData.filterRF.get());
        }

        if (tisData.filterROI != NULL) //实现ROI功能
        {
            tisData.filterROI->setParameter("Left", 0);
            tisData.filterROI->setParameter("Top", 0);
            tisData.filterROI->setParameter("Height", tisData.cam->getAcqSizeMaxY());
            tisData.filterROI->setParameter("Width", tisData.cam->getAcqSizeMaxX());
            tisData.filterChain.push_back(tisData.filterROI.get());
        }
        tisData.cam->setDeviceFrameFilters(tisData.filterChain);

        tisData.pProps = tisData.cam->getAvailableVCDProperties();
        if (tisData.pProps == 0)
        {
            return ZV_ERR_CAM_OPEN;
        }
    }

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_tis_status(int scanId)
{
#ifdef ZV_USE_TIS
    if (!s_zv_cam_tis_data[scanId].cam->isDevValid())
    {
        return ZV_CAM_ST_REMOVED;
    }
    if (s_zv_cam_tis_data[scanId].cam->isDevOpen())
    {
        return ZV_CAM_ST_OPENED;
    }

    return ZV_CAM_ST_NULL;
#else
    return ZV_CAM_ST_ERROR;
#endif
}

int zv_cam_tis_close(int scanId)
{
#ifdef ZV_USE_TIS
    s_zv_cam_tis_data[scanId].cam->closeDev();
    return ZV_ST_OK;
#else
    return ZV_ERR_G_UNFINISHED;
#endif
}

int zv_cam_tis_grab(cv::Mat &_img, int scanId)
{
#ifdef ZV_USE_TIS
    tFrameHandlerSinkPtr pSink = s_zv_cam_tis_data[scanId].cam->getSinkTypePtr();
    s_zv_cam_tis_data[scanId].cam->startLive(false);
    Error e = pSink->snapImages(1, (DWORD)cvRound(g_zv_sys_grabTimeout));
    s_zv_cam_tis_data[scanId].cam->stopLive();
    if (e.isError())
    {
        return ZV_ERR_CAM_GRAB;
    }
  
    smart_ptr<MemBuffer> pBuffer = pSink->getLastAcqMemBuffer();
    tColorformatEnum cf = pBuffer->getColorformat();
    int srcType = CV_8UC1;
    int cvtCode = -1;
    switch (cf)
    {
    case eY800:
        break;
    case eBY8: //8 - bit bayer
    {
        DeBayerTransform::tStartPattern bayerType = s_zv_cam_tis_data[scanId].cam->
            getDeBayerTransform()->getStartPattern();
        switch (bayerType)
        {
        case DeBayerTransform::eBG:
            cvtCode = cv::COLOR_BayerBG2RGB;
            break;
        case DeBayerTransform::eGB:
            cvtCode = cv::COLOR_BayerGB2RGB;
            break;
        case DeBayerTransform::eGR:
            cvtCode = cv::COLOR_BayerGR2RGB;
            break;
        case DeBayerTransform::eRG:
            cvtCode = cv::COLOR_BayerRG2RGB;
            break;
        default:
            return ZV_ERR_CAM_GRAB;
        }
        break;
    }
    case eRGB32:
        srcType = CV_8UC4;
        break;
    case eRGB24:
        srcType = CV_8UC3;
        break;
    case eY16: //16 - bit grayscale
        srcType = CV_16UC1;
        break;
    case eYGB0: //10 bit grayscale format
    case eYGB1: //
        //break;
    case eUYVY:  //UYVY 16 bit color format
        //break;
    case eRGB555:
    case eRGB565:  //16 - bit color depth with red 5 green 6 blue 5 bit encoding
    case eRGB8:
    case eInvalidColorformat:
        return ZV_ERR_CAM_GRAB;
        break;
    default:
        return ZV_ERR_CAM_GRAB;
    }

    SIZE imgSize = pBuffer->getSize();
    cv::Mat tmp = cv::Mat(imgSize.cy, imgSize.cx, srcType, pBuffer->getPtr());
    if (-1 != cvtCode)
    {
        cv::cvtColor(tmp, _img, cvtCode);
    }
    else
    {
        tmp.copyTo(_img);
    }

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_tis_payloadSize(int scanId)
{
#ifdef ZV_USE_TIS
    tFrameHandlerSinkPtr pSink = s_zv_cam_tis_data[scanId].cam->getSinkTypePtr();
    if (NULL != pSink)
    {
        return (int)pSink->getMemBufferCollection()->getBufferSize();
    }
#endif
    return 0;
}

int zv_cam_tis_getROI(int scanId, int &offsetX, int &offsetY, int &width, int &height)
{
#ifdef ZV_USE_TIS
    smart_com<IFrameFilter> filterROI = s_zv_cam_tis_data[scanId].filterROI;
    if (filterROI == NULL)
    {
        return ZV_ERR_G_NOT_SUPPORT;
    }

    bool runOk = true;
    runOk = runOk && eNO_ERROR == filterROI->getParameter("Left", offsetX);
    runOk = runOk && eNO_ERROR == filterROI->getParameter("Top", offsetY);
    runOk = runOk && eNO_ERROR == filterROI->getParameter("Height", height);
    runOk = runOk && eNO_ERROR == filterROI->getParameter("Width", width);
    if (!runOk)
    {
        return ZV_ERR_CAM_PARAM_RD;
    }

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_tis_setROI(int scanId, int offsetX, int offsetY, int width, int height)
{
#ifdef ZV_USE_TIS
    smart_com<IFrameFilter> filterROI = s_zv_cam_tis_data[scanId].filterROI;
    if (filterROI == NULL)
    {
        return ZV_ERR_G_NOT_SUPPORT;
    }

    bool runOk = true;
    runOk = runOk && eNO_ERROR == filterROI->setParameter("Left", offsetX);
    runOk = runOk && eNO_ERROR == filterROI->setParameter("Top", offsetY);
    runOk = runOk && eNO_ERROR == filterROI->setParameter("Height", height);
    runOk = runOk && eNO_ERROR == filterROI->setParameter("Width", width);
    if (!runOk)
    {
        return ZV_ERR_CAM_PARAM_WR;
    }

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_tis_cmd(int scanId, int prop)
{
#ifdef ZV_USE_TIS
    if (prop >= s_zv_cam_tisCmdProp.size())
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    tIVCDPropertyInterfacePtr pItf = s_zv_cam_tis_data[scanId].pProps->findInterface(
        s_zv_cam_tisCmdProp[prop].prop, s_zv_cam_tisCmdProp[prop].element, VCDInterface_Button);
    if (pItf != 0)
    {
        tIVCDButtonPropertyPtr pBtnItf;
        pItf->QueryInterface(pBtnItf);
        pBtnItf->push();
        return ZV_ST_OK;
    }

    return ZV_ERR_CAM_PARAM_UNDEF;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_tis_bool(int scanId, int prop, bool & value, bool isGet)
{
#ifdef ZV_USE_TIS
    if (prop >= s_zv_cam_tisBoolProp.size())
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    tIVCDPropertyInterfacePtr pItf = s_zv_cam_tis_data[scanId].pProps->findInterface(
        s_zv_cam_tisBoolProp[prop].prop, s_zv_cam_tisBoolProp[prop].element, VCDInterface_Switch);
    tIVCDSwitchPropertyPtr pSwItf;
    if (pItf != 0)
    {
        pItf->QueryInterface(pSwItf);
    }

    if (isGet)
    {
        value = pSwItf->getSwitch();
    }
    else
    {
        pSwItf->setSwitch(value);
    }
    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_tis_value(int scanId, int prop, double &value, bool isGet)
{
#ifdef ZV_USE_TIS
    if (prop >= ZV_CAM_PV_EXPOSURE_AUTO && prop <= ZV_CAM_PV_GAIN_AUTO)
    {
        bool state = isGet ? false : 0 != value;
        zv_cam_tis_bool(scanId, prop - ZV_CAM_PV_EXPOSURE_AUTO, state, isGet);
        if (isGet)  value = state;
    }

    prop -= ZV_CAM_PV_EXPOSURE;
    if ((uint)prop >= s_zv_cam_tisValueProp.size())
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    tIVCDPropertyInterfacePtr pItf = s_zv_cam_tis_data[scanId].pProps->findInterface(
        s_zv_cam_tisValueProp[prop].prop, s_zv_cam_tisValueProp[prop].element, VCDInterface_Range);
    if (pItf == 0)
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    if (prop == 0)
    {
        tIVCDAbsoluteValuePropertyPtr AbspRangeItf;
        pItf->QueryInterface(AbspRangeItf);
        if (isGet)
        {
            value = AbspRangeItf->getValue();
        }
        else
        {
            if (value <= AbspRangeItf->getRangeMin())
            {
                AbspRangeItf->setValue(AbspRangeItf->getRangeMin());
            }
            else if (value >= AbspRangeItf->getRangeMax())
            {
                AbspRangeItf->setValue(AbspRangeItf->getRangeMax());
            }
            else
            {
                AbspRangeItf->setValue(value);
            }
        }
    }
    else
    {
        tIVCDRangePropertyPtr pRangeItf;
        pItf->QueryInterface(pRangeItf);
        if (isGet)
        {
            value = (double)pRangeItf->getValue();
        }
        else
        {
            if (value <= (double)pRangeItf->getRangeMin())
            {
                pRangeItf->setValue(pRangeItf->getRangeMin());
            }
            else if (value >= (double)pRangeItf->getRangeMax())
            {
                pRangeItf->setValue(pRangeItf->getRangeMax());
            }
            else
            {
                pRangeItf->setValue((long)cvRound(value));
            }
        }
    }

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_tis_valueRange(int scanId, int prop, double &minV, double &maxV, double &step)
{
#ifdef ZV_USE_TIS
    if (prop >= ZV_CAM_PV_EXPOSURE_AUTO && prop <= ZV_CAM_PV_GAIN_AUTO)
    {
        minV = 0;
        maxV = 1;
        step = 1;
        return ZV_ST_OK;
    }

    prop -= ZV_CAM_PV_EXPOSURE;
    if ((uint)prop >= s_zv_cam_tisValueProp.size())
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    tIVCDPropertyInterfacePtr pItf;
    if ((pItf = s_zv_cam_tis_data[scanId].pProps->findInterface(s_zv_cam_tisValueProp[prop].prop,
        s_zv_cam_tisValueProp[prop].element, VCDInterface_AbsoluteValue)) == 0)
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    if (0 == prop)
    {
        tIVCDAbsoluteValuePropertyPtr AbspRangeItf;
        pItf->QueryInterface(AbspRangeItf);

        minV = AbspRangeItf->getRangeMin();
        maxV = AbspRangeItf->getRangeMax();
        step = (maxV - minV) / 1000.0;
    }
    else
    {
        tIVCDRangePropertyPtr pRangeItf;
        pItf->QueryInterface(pRangeItf);

        minV = (double)pRangeItf->getRangeMin();
        maxV = (double)pRangeItf->getRangeMax();
        step = 1;
    }

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

#if 0
int IC_LoadDeviceSettings(HGRABBER hGrabber, char* szFilename);
int IC_ResetProperties(HGRABBER hGrabber);

typedef void(*FRAME_READY_CALLBACK)
(HGRABBER hGrabber, unsigned char* pData, unsigned long frameNumber, void*);
typedef void(*DEVICE_LOST_CALLBACK)(HGRABBER hGrabber, void*);

/*!	Set callback function
@param hGrabber      Handle to a grabber object.
@param cb Callback function of type FRAME_READY_CALLBACK, can be NULL, if no callback is needed
@param dlcb Callback function of type DEVICE:LOST_CALLBACK, can be NULL, if no device lost handler is needed
@param x1_argument_in_void_userdata Pointer to some userdata.

@sa FRAME_READY_CALLBACK
*/
int AC IC_SetCallbacks(
    HGRABBER				hGrabber,
    FRAME_READY_CALLBACK	cb,
    void*					x1_argument_in_void_userdata,
    DEVICE_LOST_CALLBACK	dlCB,
    void*					x2_argument_in_void_userdata);


//////////////////////////////////////////////////////////////////////////
/*! Open a video capture device. The hGrabber handle must have been created previously by
a call to IC_CreateGrabber(). Once a hGrabber handle has been created it can be
recycled to open different video capture devices in sequence.
@param hGrabber The handle to grabber object, that has been created by a call to IC_CreateGrabber
@param szDeviceName Friendly name of the video capture device e.g. "DFK 21F04".
@retval IC_SUCCESS on success.
@retval IC_ERROR on errors.
@sa IC_CloseVideoCaptureDevice

@code
#include "tisgrabber.h"
void main()
{
HGRABBER hGrabber;
if( IC_InitLibrary(0) == IC_SUCCESS )
{
hGrabber = IC_CreateGrabber();
if( hGrabber )
{
if( IC_OpenVideoCaptureDevice(hGrabber,"DFK 21F04") == IC_SUCCESS )
{

// .. do something with the video capture device.

// Now clean up.
IC_CloseVideoCaptureDevice( hGrabber );
IC_ReleaseGrabber( hGrabber );
}
IC_CloseLibrary();
}
}
@endcode
*/
int AC IC_OpenVideoCaptureDevice(HGRABBER hGrabber, char *szDeviceName); ///< Opens a video capture device.

int AC IC_GetVideoFormatWidth(HGRABBER hGrabber); ///<Returns the width of the video format.
int AC IC_GetVideoFormatHeight(HGRABBER hGrabber);///<returns the height of the video format.

                                                  //////////////////////////////////////////////////////////////////////////
                                                  /*! Set the sink type. A sink type must be set before images can be snapped.
                                                  The sink type basically describes the format of the buffer where the snapped
                                                  images are stored.

                                                  Possible values for format are:
                                                  @li Y800
                                                  @li RGB24
                                                  @li RGB32
                                                  @li UYVY

                                                  The sink type may differ from the currently set video format.

                                                  @param hGrabber The handle to the grabber object.
                                                  @param format The desired color format. Possible values for format are:
                                                  @li Y800
                                                  @li RGB24
                                                  @li RGB32
                                                  @li UYVY
                                                  @retval IC_SUCCESS on success
                                                  @retval IC_ERROR if something went wrong.

                                                  @note Please note that UYVY can only be used in conjunction with a UYVY video format.


                                                  */
int AC IC_SetFormat(HGRABBER hGrabber, COLORFORMAT format); ///< Sets the color format of the sink. 
COLORFORMAT AC IC_GetFormat(HGRABBER hGrabber); ///<Returns the current color format of the sink.


                                                //////////////////////////////////////////////////////////////////////////
                                                /*! Set a video format for the current video capture device. The video format
                                                must be supported by the current video capture device.
                                                @param hGrabber The handle to the grabber object.
                                                @param szFormat A string that contains the desired video format.
                                                @retval IC_SUCCESS on success
                                                @retval IC_ERROR if something went wrong.

                                                @code
                                                #include "tisgrabber.h"
                                                void main()
                                                {
                                                HGRABBER hGrabber;
                                                if( IC_InitLibrary(0) == IC_SUCCESS )
                                                {
                                                hGrabber = IC_CreateGrabber();
                                                if( hGrabber )
                                                {
                                                if( IC_OpenVideoCaptureDevice(hGrabber,"DFK 21F04") == IC_SUCCESS )
                                                {
                                                if( IC_SetVideoFormat(hGrabber,"UYVY (640x480)" == IC_SUCCESS )
                                                {
                                                // .. do something with the video capture device.
                                                }
                                                // Now clean up.
                                                IC_CloseVideoCaptureDevice( hGrabber );
                                                IC_ReleaseGrabber( hGrabber );
                                                }
                                                IC_CloseLibrary();
                                                }
                                                }
                                                }
                                                @endcode
                                                */
int AC IC_SetVideoFormat(HGRABBER hGrabber, char *szFormat); ///<Sets the video format.
int AC IC_SetVideoNorm(HGRABBER hGrabber, char *szNorm); ///<Set the video norm.



                                                         //////////////////////////////////////////////////////////////////////////
                                                         /*! Start the live video.
                                                         @param hGrabber The handle to the grabber object.
                                                         @param iShow The parameter indicates:   @li 1 : Show the video	@li 0 : Do not show the video, but deliver frames. (For callbacks etc.)
                                                         @retval IC_SUCCESS on success
                                                         @retval IC_ERROR if something went wrong.
                                                         @sa IC_StopLive
                                                         */
int AC IC_StartLive(HGRABBER hGrabber, int iShow); ///<Starts the live video.
void AC IC_StopLive(HGRABBER hGrabber); ///<Stops the live video.

int AC IC_IsCameraPropertyAvailable(HGRABBER hGrabber, CAMERA_PROPERTY eProperty); ///< Check whether a camera property is available.


int AC IC_SetCameraProperty(HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long lValue); ///< Set a camera property.
int AC IC_CameraPropertyGetRange(HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long *lMin, long *lMax); ///<Get the minimum and maximum value of a camera property
int AC IC_GetCameraProperty(HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long *lValue);  ///< Get a camera property's value.



int AC IC_IsVideoPropertyAvailable(HGRABBER hGrabber, VIDEO_PROPERTY eProperty); ///<Check whether the specified video property is available. 
int AC IC_VideoPropertyGetRange(HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long *lMin, long *lMax); ///<Retrieve the lower and upper limit of a video property.
int AC IC_GetVideoProperty(HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long *lValue); ///< Retrieve the the current value of the specified video property.

                                                                                       //////////////////////////////////////////////////////////////////////////
                                                                                       /*! Set a video property like brightness, contrast.

                                                                                       @param hGrabber The handle to the grabber object.
                                                                                       @param eProperty The property to be set. It can have following values:
                                                                                       @li PROP_VID_BRIGHTNESS ,
                                                                                       @li PROP_VID_CONTRAST,
                                                                                       @li PROP_VID_HUE,
                                                                                       @li PROP_VID_SATURATION,
                                                                                       @li PROP_VID_SHARPNESS,
                                                                                       @li PROP_VID_GAMMA,
                                                                                       @li PROP_VID_COLORENABLE,
                                                                                       @li PROP_VID_WHITEBALANCE,
                                                                                       @li PROP_VID_BLACKLIGHTCOMPENSATION,
                                                                                       @li PROP_VID_GAIN
                                                                                       @param lValue The value the property is to be set to.
                                                                                       @retval IC_SUCCESS on success
                                                                                       @retval IC_ERROR if something went wrong.

                                                                                       @note lValue should be in the range of the specified property.
                                                                                       If the value could not be set (out of range, auto is currently enabled), the
                                                                                       function returns 0. On success, the functions returns 1.
                                                                                       */
int AC IC_SetVideoProperty(HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long lValue); ///<Set a video property.


                                                                                      //////////////////////////////////////////////////////////////////////////
int AC IC_GetImageDescription(HGRABBER hGrabber, long *lWidth, long *lHeight, int *iBitsPerPixel, COLORFORMAT *format);///<Retrieve the properties of the current video format and sink typ.


int AC IC_SnapImage(HGRABBER hGrabber, int iTimeOutMillisek); ///<Snaps an image from the live stream. 
unsigned char* AC IC_GetImagePtr(HGRABBER hGrabber); ///< Retuns a pointer to the image data


                                                     //////////////////////////////////////////////////////////////////////////
                                                     //IC_OpenVideoCaptureDevice(hGrabber, "DFK 21F04" );
                                                     //iFormatCount = IC_ListDevices(hGrabber, (char*)szFormatList,40 );
int AC IC_ListVideoFormats(HGRABBER hGrabber, char *szFormatList, int iSize);///<List available video formats.

int AC IC_GetDeviceCount(); ///<Get the number of the currently available devices. 

                            //////////////////////////////////////////////////////////////////////////
                            /*! Get a string representation of a device specified by iIndex. iIndex
                            must be between 0 and IC_GetDeviceCount(). IC_GetDeviceCount() must
                            have been called before this function, otherwise it will always fail.

                            @param iIndex The number of the device whose name is to be returned. It must be
                            in the range from 0 to IC_GetDeviceCount(),
                            @return Returns the string representation of the device on success, NULL
                            otherwise.

                            @sa IC_GetDeviceCount
                            @sa IC_GetUniqueNamefromList
                            */
char* AC IC_GetDevice(int iIndex); ///< Get the name of a video capture device.

                                   //////////////////////////////////////////////////////////////////////////
                                   /*! Get unique device name of a device specified by iIndex. The unique device name
                                   consist from the device name and its serial number. It allows to differ between
                                   more then one device of the same type connected to the computer. The unique device name
                                   is passed to the function IC_OpenDevByUniqueName

                                   @param iIndex The number of the device whose name is to be returned. It must be
                                   in the range from 0 to IC_GetDeviceCount(),
                                   @return Returns the string representation of the device on success, NULL
                                   otherwise.

                                   @sa IC_GetDeviceCount
                                   @sa IC_GetUniqueNamefromList
                                   @sa IC_OpenDevByUniqueName
                                   */
char* AC IC_GetUniqueNamefromList(int iIndex);///< Get the unique name of a video capture device.

                                              //////////////////////////////////////////////////////////////////////////
                                              /*! Get the number of the available video formats for the current device.
                                              A video capture device must have been opened before this call.

                                              @param hGrabber The handle to the grabber object.

                                              @retval >= 0 Success
                                              @retval < 0 An error occured.

                                              @sa IC_GetVideoFormat
                                              */
int AC IC_GetVideoFormatCount(HGRABBER hGrabber); ///< Returns the count of available video formats.


                                                  //////////////////////////////////////////////////////////////////////////
                                                  /*! Get a string representation of the video format specified by iIndex.
                                                  iIndex must be between 0 and IC_GetVideoFormatCount().
                                                  IC_GetVideoFormatCount() must have been called before this function,
                                                  otherwise it will always fail.

                                                  @param hGrabber The handle to the grabber object.
                                                  @param iIndex Number of the video format to be used.

                                                  @retval Nonnull The name of the specified video format.
                                                  @retval NULL An error occured.
                                                  @sa IC_GetVideoFormatCount
                                                  */
char* AC IC_GetVideoFormat(HGRABBER hGrabber, int iIndex); ///<Return the name of a video format.

                                                           //////////////////////////////////////////////////////////////////////////
                                                           /*! Get a DisplayName from a currently open device. The display name of a
                                                           device can be another on different computer for the same video capture
                                                           device.

                                                           @param hGrabber       Handle to a grabber object
                                                           @param szDisplayName  Memory that will take the display name. If it is NULL, the
                                                           length of the display name will be returned.
                                                           @param iLen           Size in Bytes of the memory allocated by szDisplayName.


                                                           @retval IC_SUCCESS     On success. szDisplayName contains the display name of the device.
                                                           @retval IC_ERROR	   iLen is less than the length of the retrieved display name.
                                                           @retval IC_NO_HANDLE   hGrabber is not a valid handle. GetGrabber was not called.
                                                           @retval IC_NO_DEVICE   No device opened. Open a device, before this function can be used.
                                                           @retval >1             Length of the display name, if szDisplayName is NULL.

                                                           @sa IC_OpenDevByDisplayName
                                                           @sa IC_ReleaseGrabber

                                                           */
int AC IC_GetDisplayName(HGRABBER hGrabber, char *szDisplayname, int iLen); ///<Get the display name of a device.

int AC IC_IsDevValid(HGRABBER hGrabber); ///<Returns whether a video capture device is valid.

int AC IC_IsTriggerAvailable(HGRABBER hGrabber); ///<Check for external trigger support.
int AC IC_EnableTrigger(HGRABBER hGrabber, int iEnable); ///<Enable or disable the external trigger. 

                                                         //////////////////////////////////////////////////////////////////////////
                                                         /*! Get trigger modes.
                                                         Simple sample to list the video capture devices:

                                                         @param hGrabber      Handle to a grabber object.
                                                         @param szModeList	Twodimensional array of char that will recieve the mode list.
                                                         @param iSze			Size of the array (first dimension)

                                                         @retval 0 : No trigger modes available
                                                         @retval >0 : Count of available trigger modes
                                                         @retval IC_ERROR  No video signal detected
                                                         @retval IC_NO_HANDLE  Invalid grabber handle
                                                         @retval IC_NO_DEVICE    No video capture device opened

                                                         @code
                                                         char szModes[20][10];
                                                         int iModeCount;

                                                         iModeCount = IC_GetTriggerModes(hGrabber, (char*)szModes,20);
                                                         for( int i = 0; i < min( iModeCount, 20); i++ )
                                                         {
                                                         printf("%2d. %s\n",i+1,szModes[i]);
                                                         }
                                                         @endcode
                                                         */
int AC IC_GetTriggerModes(HGRABBER hGrabber, char *szModeList, int iSize); ///<Get trigger modes.
int AC IC_SetTriggerMode(HGRABBER hGrabber, char* szMode); ///<Set the trigger mode.

                                                           //////////////////////////////////////////////////////////////////////////
                                                           /*! Set the trigger polarity
                                                           @param iPolarity
                                                           @li 0 : Polarity on direction
                                                           @li 1 : Polarity the other direction

                                                           @retval 0 : No trigger polarity available
                                                           @retval 1 : Count of available trigger modes
                                                           @retval IC_NO_HANDLE	Invalid grabber handle
                                                           @retval IC_NO_DEVICE    No video capture device opened
                                                           */
int AC IC_SetTriggerPolarity(HGRABBER hGrabber, int iPolarity); ///< Set the trigger polarity.



int AC IC_IsExpAbsValAvailable(HGRABBER hGrabber);
int AC IC_GetExpAbsValRange(HGRABBER hGrabber, float *fMin, float *fMax);
int AC IC_GetExpAbsVal(HGRABBER hGrabber, float *fValue);
int AC IC_SetExpAbsVal(HGRABBER hGrabber, float fValue);


/*! Sends a software trigger to the camera. The camera must support
external trigger. The external trigger has to be enabled previously

@param hGrabber	Handle to a grabber object.
@retval IC_SUCCESS : Success
@retval IC_NOT:AVAILABLE : The property is not supported by the current device
@retval IC_NO_HANDLE	Invalid grabber handle
@retval IC_NO_DEVICE    No video capture device opened

@seealso IC_EnableTrigger

*/
int AC IC_SoftwareTrigger(HGRABBER hGrabber);

///////////////////////////////////////////////////////////////////
/*! Sets a new frame rate.
@param hGrabber	Handle to a grabber object.
@param FrameRate The new frame rate.
@retval IC_SUCCESS : Success
@retval IC_NOT_AVAILABLE : The property is not supported by the current device
@retval IC_NO_HANDLE	Invalid grabber handle
@retval IC_NO_DEVICE    No video capture device opened
@retval IC_NOT_IN_LIVEMODE Frame rate can not set, while live video is shown. Stop Live video first!
*/
int AC IC_SetFrameRate(HGRABBER hGrabber, float FrameRate);
float AC IC_GetFrameRate(HGRABBER hGrabber);

int AC IC_SetWhiteBalanceAuto(HGRABBER hGrabber, int iOnOff);
///////////////////////////////////////////////////////////////////
/*! Sets the value for white balance red.

@param hGrabber	Handle to a grabber object.
@param Value	Value of the red white balance to be set
@retval IC_SUCCESS			: Success
@retval IC_NO_HANDLE		: Invalid grabber handle
@retval IC_NO_DEVICE		: No video capture device opened
@retval IC_NOT_AVAILABLE	: The property is not supported by the current device

*/
int AC IC_SetWhiteBalanceRed(HGRABBER hGrabber, long Value);
int AC IC_SetWhiteBalanceGreen(HGRABBER hGrabber, long Value);
int AC IC_SetWhiteBalanceBlue(HGRABBER hGrabber, long Value);
int AC IC_FocusOnePush(HGRABBER hGrabber);


int AC IC_ShowInternalPropertyPage(HGRABBER hGrabber);

///////////////////////////////////////////////////////////////////
/*! Check, whether a property is available..  For a list of properties and elements
use the VCDPropertyInspector of IC Imaging Control.

@param hGrabber	Handle to a grabber object.
@param Property  The name of the property, e.g. Gain, Exposure
@param Element  The type of the interface, e.g. Value, Auto. If NULL, it is not checked.

@retval IC_SUCCESS			Success
@retval IC_NO_HANDLE		Invalid grabber handle
@retval IC_NO_DEVICE		No video capture device opened
@retval IC_PROPERTY_ELEMENT_NOT_AVAILABLE		A requested element of a given property item is not available
@retval IC_PROPERTY_ELEMENT_WRONG_INTERFACE		requested element has not the interface, which is needed.

if( IC_IsPropertyAvailable( hGrabber, "Brightness",NULL) == IC_SUCCESS )
if( IC_IsPropertyAvailable( hGrabber, "Trigger","Software Trigger") == IC_SUCCESS )

*/
int AC IC_IsPropertyAvailable(HGRABBER hGrabber, char* Property, char *Element);

///////////////////////////////////////////////////////////////////
/*! This returns the range of a property.  For a list of properties and elements
use the VCDPropertyInspector of IC Imaging Control.

@param hGrabber	Handle to a grabber object.
@param Property  The name of the property, e.g. Gain, Exposure
@param Element  The type of the interface, e.g. Value, Auto. If NULL, it is "Value".
@param Min  Receives the min value of the property
@param Max  Receives the max value of the property

@retval IC_SUCCESS			Success
@retval IC_NO_HANDLE		Invalid grabber handle
@retval IC_NO_DEVICE		No video capture device opened
@retval IC_PROPERTY_ITEM_NOT_AVAILABLE		A requested property item is not available
@retval IC_PROPERTY_ELEMENT_NOT_AVAILABLE		A requested element of a given property item is not available
@retval IC_PROPERTY_ELEMENT_WRONG_INTERFACE		requested element has not the interface, which is needed.

@code
HGRABBER hGrabber; // The handle of the grabber object.

int Min;
int Max;
int Result = IC_ERROR;
HGRABBER hGrabber;

if( IC_InitLibrary(0) )
{
hGrabber = IC_CreateGrabber();
IC_OpenVideoCaptureDevice(hGrabber, "DFx 31BG03.H");

if( hGrabber )
{
Result = IC_GetPropertyValueRange(hGrabber,"Exposure","Auto Reference", &Min, &Max );

if( Result == IC_SUCCESS )
printf("Expsure Auto Reference Min %d, Max %d\n", Min, Max);

Result = IC_GetPropertyValueRange(hGrabber,"Exposure",NULL, &Min, &Max );

if( Result == IC_SUCCESS )
printf("Exposure Value Min %d, Max %d\n", Min, Max);
}
IC_ReleaseGrabber( hGrabber );
@endcode


*/
int AC IC_GetPropertyValueRange(HGRABBER hGrabber, char* Property, char *Element, int *Min, int *Max);

///////////////////////////////////////////////////////////////////
/*! This returns the current value of a property. For a list of properties and elements
use the VCDPropertyInspector of IC Imaging Control.

@param hGrabber	Handle to a grabber object.
@param Property  The name of the property, e.g. Gain, Exposure
@param Element  The type of the interface, e.g. Value, Auto. If NULL, it is "Value".
@param Value  Receives the value of the property

@retval IC_SUCCESS			Success
@retval IC_NO_HANDLE		Invalid grabber handle
@retval IC_NO_DEVICE		No video capture device opened
@retval IC_PROPERTY_ITEM_NOT_AVAILABLE		A requested property item is not available
@retval IC_PROPERTY_ELEMENT_NOT_AVAILABLE		A requested element of a given property item is not available
@retval IC_PROPERTY_ELEMENT_WRONG_INTERFACE		requested element has not the interface, which is needed.
*/
int AC IC_GetPropertyValue(HGRABBER hGrabber, char* Property, char *Element, int *Value);
int AC IC_SetPropertyValue(HGRABBER hGrabber, char* Property, char *Element, int Value);

int AC IC_GetPropertyAbsoluteValueRange(HGRABBER hGrabber, char* Property, char *Element, float *Min, float *Max);
int AC IC_GetPropertyAbsoluteValue(HGRABBER hGrabber, char* Property, char *Element, float *Value);
int AC IC_SetPropertyAbsoluteValue(HGRABBER hGrabber, char* Property, char *Element, float Value);

int AC IC_GetPropertySwitch(HGRABBER hGrabber, char* Property, char *Element, int *On);
int AC IC_SetPropertySwitch(HGRABBER hGrabber, char* Property, char *Element, int On);

#endif
