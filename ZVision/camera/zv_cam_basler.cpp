#include "zv_private.h"
#include "zv_cam_gige_vision.h"
#include "zv_camera.h"
#include "zv_cam_basler.h"


#define ZV_USE_BASLER

#ifdef ZV_USE_BASLER
#include <pylon/PylonIncludes.h>
using namespace Pylon;
using namespace GenApi;

#pragma comment( lib, "GCBase_MD_VC120_v3_0_Basler_pylon_v5_0.lib" ) 
#pragma comment( lib, "GenApi_MD_VC120_v3_0_Basler_pylon_v5_0.lib" ) 
#pragma comment( lib, "PylonUtility_MD_VC120_v5_0.lib" ) 
#pragma comment( lib, "PylonBase_MD_VC120_v5_0.lib" ) 
#pragma comment( lib, "PylonC_MD_VC120.lib" ) 

CInstantCamera s_zv_cam_basler_data[ZV_CAM_MAX_NUM];

static char *zv_cam_basler_getPropStr(int id)
{
    static std::vector<std::string> propCvt;
    propCvt.push_back(ZV_CAM_P_OFFSETX);
    propCvt.push_back(ZV_CAM_P_OFFSETY);
    propCvt.push_back(ZV_CAM_P_WIDTH);
    propCvt.push_back(ZV_CAM_P_HEIGHT);
    propCvt.push_back(ZV_CAM_P_EXPOSURE);
    propCvt.push_back(ZV_CAM_P_GAIN);
    if (propCvt.size() <= id)
    {
        return NULL;
    }

    return (char *)propCvt[id].c_str();
}
#endif

char * s_zv_cam_basler_infoName[] = {
    ZV_CAM_INFO_SN,
    ZV_CAM_INFO_MODEL,
    ZV_CAM_INFO_DEVICE_ID,
    ZV_CAM_INFO_FULL_NAME,
    ZV_CAM_INFO_VENDOR_NAME,
    ZV_CAM_INFO_CLASS,
    ZV_CAM_INFO_PORT,
    ZV_CAM_INFO_MAC,
    ZV_CAM_INFO_IP,
    ZV_CAM_INFO_HOST_IP,
    ZV_CAM_INFO_USER_NAME,
};

int zv_cam_basler_release(int scanId)
{
#ifdef ZV_USE_BASLER
    s_zv_cam_basler_data[scanId].StopGrabbing();   //camera 停止抓取
    s_zv_cam_basler_data[scanId].DestroyDevice();  //对设备进行释放
    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_basler_init()
{
#ifdef ZV_USE_BASLER
    PylonInitialize();
#endif
    return ZV_ST_OK;
}

int zv_cam_basler_exit()
{
#ifdef ZV_USE_BASLER
    PylonTerminate();
#endif
    return ZV_ST_OK;
}

int zv_cam_basler_scan(int startScanId)
{
#ifdef ZV_USE_BASLER
    //判断相机驱动有没有检查到设备
    CTlFactory& factory = CTlFactory::GetInstance();
    Pylon::DeviceInfoList_t devices;
    int num = factory.EnumerateDevices(devices);
    int cnt = startScanId;
    for (int i = 0; i < num; i++)
    {
        if (!factory.IsDeviceAccessible(devices[i]))
        {
            continue;
        }

        s_zv_cam_basler_data[cnt].Attach(factory.CreateDevice(devices[i]));
        if (s_zv_cam_basler_data[cnt].IsPylonDeviceAttached())
        {
            cnt++;
            if (cnt >= ZV_CAM_MAX_NUM)
            {
                break;
            }
        }
    }

    return cnt - startScanId;
#endif
    return 0;
}

int zv_cam_basler_getInfo(int scanId, int info, char *value, int maxValLen)
{
#ifdef ZV_USE_BASLER
    const CDeviceInfo &devInfo = s_zv_cam_basler_data[scanId].GetDeviceInfo();
    if (info >= sizeof(s_zv_cam_basler_infoName) / sizeof(s_zv_cam_basler_infoName[0])
        || NULL == s_zv_cam_basler_infoName[info])
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    if (devInfo.GetPropertyAvailable(s_zv_cam_basler_infoName[info]))
    {
        String_t str;
        if (devInfo.GetPropertyValue(s_zv_cam_basler_infoName[info], str))
        {
            snprintf(value, maxValLen, "%s", str.c_str());
            return ZV_ST_OK;
        }
    }
    return ZV_ERR_CAM_PARAM_RD;
#endif
   return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_basler_open(int scanId)
{
#ifdef ZV_USE_BASLER
    if (!s_zv_cam_basler_data[scanId].IsOpen())
    {
        s_zv_cam_basler_data[scanId].Open();
        if (s_zv_cam_basler_data[scanId].IsOpen())
        {
            return ZV_ST_OK;
        }
    }
    return ZV_ERR_CAM_UNBOUND;

#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_basler_status(int scanId)
{
#ifdef ZV_USE_BASLER
    if (s_zv_cam_basler_data[scanId].IsCameraDeviceRemoved())
    {
        return ZV_CAM_ST_REMOVED;
    }
    if (s_zv_cam_basler_data[scanId].IsOpen())
    {
        return ZV_CAM_ST_OPENED;
    }
    if (s_zv_cam_basler_data[scanId].IsPylonDeviceAttached())
    {
        return ZV_CAM_ST_CONNECT;
    }
    else
    {
        return ZV_CAM_ST_NULL;
    }
#endif
    return ZV_CAM_ST_ERROR;
}

int zv_cam_basler_close(int scanId)
{
#ifdef ZV_USE_BASLER
    s_zv_cam_basler_data[scanId].Close();
    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_basler_grab(cv::Mat &img, int scanId)
{
#ifdef ZV_USE_BASLER
    CGrabResultPtr pGrabResult;
    s_zv_cam_basler_data[scanId].GrabOne(cvRound(g_zv_sys_grabTimeout), pGrabResult);

    if (!pGrabResult->GrabSucceeded())
    {
        return ZV_ERR_CAM_GRAB;
    }
    EPixelType pt = pGrabResult->GetPixelType();
    int type = CV_8UC1;
    switch (pt)
    {
    case PixelType_Mono8:
    case PixelType_Mono8signed:
        break;
    case PixelType_BayerGR8:
    case PixelType_BayerRG8:
    case PixelType_BayerGB8:
    case PixelType_BayerBG8:
        break;
    case PixelType_RGB8packed:
        type = CV_8UC3;
        break;
    case PixelType_BGR8packed:
        type = CV_8UC3;
        break;
    case PixelType_RGBA8packed:
        type = CV_8UC4;
        break;
    case PixelType_BGRA8packed:
        type = CV_8UC4;
        break;
    case PixelType_RGB8planar: //RGB通道分开存放
        return ZV_ERR_CAM_GRAB;
        break;
    default:
        return ZV_ERR_CAM_GRAB;
    }

    cv::Mat tmp = cv::Mat(pGrabResult->GetHeight(), pGrabResult->GetWidth(), type, pGrabResult->GetBuffer());
    tmp.copyTo(img);

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_basler_payloadSize(int scanId)
{
    char val[ZV_INT_STR_LEN] = { 0 };
    zv_cam_basler_param(scanId, ZV_CAM_P_PAYLOAD_SIZE, val, ZV_INT_STR_LEN, true);
    return atoi(val);
}

int zv_cam_basler_getROI(int scanId, int &offsetX, int &offsetY, int &width, int &height)
{
#ifdef ZV_USE_BASLER
    char val[ZV_INT_STR_LEN] = { 0 };
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_OFFSETX, val, ZV_INT_STR_LEN, true));
    offsetX = atoi(val);
  
    memset(val, 0, sizeof(val));
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_OFFSETY, val, ZV_INT_STR_LEN, true));
    offsetY = atoi(val);

    memset(val, 0, sizeof(val));
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_WIDTH, val, ZV_INT_STR_LEN, true));
    width = atoi(val);
   
    memset(val, 0, sizeof(val));
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_HEIGHT, val, ZV_INT_STR_LEN, true));
    height = atoi(val);

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

int zv_cam_basler_setROI(int scanId, int offsetX, int offsetY, int width, int height)
{
#ifdef ZV_USE_BASLER
    string val = "0";
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_OFFSETX, const_cast<char*>(val.c_str()), (int)val.size(), false));
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_OFFSETY, const_cast<char*>(val.c_str()), (int)val.size(), false));
    
    val = std::to_string(width);
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_WIDTH, const_cast<char*>(val.c_str()), (int)val.size(), false));
    val = std::to_string(height);
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_HEIGHT, const_cast<char*>(val.c_str()), (int)val.size(), false));
    val = std::to_string(offsetX);
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_OFFSETX, const_cast<char*>(val.c_str()), (int)val.size(), false));
    val = std::to_string(offsetY);
    ZV_RUN_RTN(zv_cam_basler_param(scanId, ZV_CAM_P_OFFSETY, const_cast<char*>(val.c_str()), (int)val.size(), false));

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_UNFINISHED;
}

char * s_zv_cam_basler_boolProp[] = { ZV_CAM_P_EXPOSURE_AUTO , ZV_CAM_P_GAIN_AUTO };
int zv_cam_basler_value(int scanId, int prop, double &value, bool isGet)
{
#ifdef ZV_USE_BASLER
    char *propStr = zv_cam_basler_getPropStr(prop);
    if (prop >= ZV_CAM_PV_EXPOSURE_AUTO && prop <= ZV_CAM_PV_GAIN_AUTO)
    {
        propStr = s_zv_cam_basler_boolProp[prop - ZV_CAM_PV_EXPOSURE_AUTO];
    }
    if (NULL == propStr)
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    INode *node = s_zv_cam_basler_data[scanId].GetNodeMap().GetNode(propStr);
    if (NULL == node)
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    switch (node->GetPrincipalInterfaceType())
    {
    case intfIBoolean:
    {
        GenApi::CBooleanPtr ptr(node);
        if (isGet)
        {
            if (!GenApi::IsReadable(ptr))
            {
                return ZV_ERR_CAM_PARAM_RD;
            }
            value = (double)ptr->GetValue();
        }
        else
        {
            if (!GenApi::IsWritable(ptr))
            {
                return ZV_ERR_CAM_PARAM_WR;
            }
            ptr->SetValue(value > 0.5);
        }
        break;
    }
    case intfIInteger:
    {
        GenApi::CIntegerPtr ptr(node);
        if (isGet)
        {
            if (!GenApi::IsReadable(ptr))
            {
                return ZV_ERR_CAM_PARAM_RD;
            }
            value = (double)ptr->GetValue();
        }
        else
        {
            if (!GenApi::IsWritable(ptr))
            {
                return ZV_ERR_CAM_PARAM_WR;
            }

            int64_t v = cvRound(value);
            v = v - v % ptr->GetInc();
            int64_t limit = ptr->GetMin();
            if (v < limit)
            {
                v = limit;
            }
            limit = ptr->GetMax();
            if (v > limit)
            {
                v = limit;
            }

            value = (double)v;
            ptr->SetValue(v);
        }
        break;
    }
    case intfIFloat:
    {
        GenApi::CFloatPtr ptr(node);
        if (isGet)
        {
            if (!GenApi::IsReadable(ptr))
            {
                return ZV_ERR_CAM_PARAM_RD;
            }
            value = ptr->GetValue();
        }
        else
        {
            if (!GenApi::IsWritable(ptr))
            {
                return ZV_ERR_CAM_PARAM_WR;
            }

            double v = ptr->GetInc();
            v = (int64_t)(value / v + 0.5) * v;
            double limit = ptr->GetMin();
            if (v < limit)
            {
                v = limit;
            }
            limit = ptr->GetMax();
            if (v > limit)
            {
                v = limit;
            }

            value = v;
            ptr->SetValue(v);
        }
        break;
    }
    default:
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

int zv_cam_basler_param(int scanId, char *param, char *value, int valueLen, bool isGet)
{
#ifdef ZV_USE_BASLER
    INode *node = s_zv_cam_basler_data[scanId].GetNodeMap().GetNode(param);
    if (NULL == node)
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    GenApi::CValuePtr ptr(node);
    if (isGet)
    {
        if (!GenApi::IsReadable(ptr))
        {
            return ZV_ERR_CAM_PARAM_RD;
        }
        GenICam::gcstring val = ptr->ToString();
        snprintf(value, valueLen, "%s", val.c_str());
    }
    else
    {
        if (!GenApi::IsWritable(ptr))
        {
            return ZV_ERR_CAM_PARAM_WR;
        }
        ptr->FromString(value); //Ptr1->SetValue(val - (val % Ptr1->GetInc()));
    }
    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}

char * s_zv_cam_basler_cmdProp[] = { ZV_CAM_CMD_TRG_SOFTWARE , ZV_CAM_CMD_ACQUI_START };
int zv_cam_basler_cmd(int scanId, int prop)
{
#ifdef ZV_USE_BASLER
    if (prop >= sizeof(s_zv_cam_basler_cmdProp) / sizeof(s_zv_cam_basler_cmdProp[0]))
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    INode *node = s_zv_cam_basler_data[scanId].GetNodeMap().GetNode(s_zv_cam_basler_cmdProp[prop]);
    if (NULL == node || intfICommand != node->GetPrincipalInterfaceType())
    {
        return ZV_ERR_CAM_PARAM_UNDEF;
    }

    GenApi::CCommandPtr ptr(node);
    ptr->Execute();

    return ZV_ST_OK;
#endif
    return ZV_ERR_G_NOT_SUPPORT;
}
