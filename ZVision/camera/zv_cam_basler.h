#ifndef ZV_CAM_BASLER_H
#define ZV_CAM_BASLER_H


#define ZV_CAM_INFO_MANUFACTUR   "ManufacturerInfo"
#define ZV_CAM_INFO_SN           "SerialNumber"
#define ZV_CAM_INFO_USER_NAME    "UserDefinedName"
#define ZV_CAM_INFO_MODEL        "ModelName"
#define ZV_CAM_INFO_FRIENDLY_NAME "FriendlyName"
#define ZV_CAM_INFO_FULL_NAME     "FullName"
#define ZV_CAM_INFO_VENDOR_NAME   "VendorName"
#define ZV_CAM_INFO_CLASS     "DeviceClass"    //设备构造类--Basler1394
#define ZV_CAM_INFO_IP        "IpAddress"        //IP
#define ZV_CAM_INFO_PORT      "PortNr"        //端口号
#define ZV_CAM_INFO_MAC       "MacAddress"
#define ZV_CAM_INFO_HOST_IP   "Interface"        //主机IP
#define ZV_CAM_INFO_DEVICE_ID "DeviceID"


#ifdef __cplusplus
extern "C" {
#endif

int zv_cam_basler_release(int scanId);
int zv_cam_basler_init();
int zv_cam_basler_exit();

int zv_cam_basler_scan(int startScanId);
int zv_cam_basler_getInfo(int scanId, int info, char *value, int maxValLen);
int zv_cam_basler_open(int scanId);
int zv_cam_basler_status(int scanId);
int zv_cam_basler_close(int scanId);
int zv_cam_basler_grab(cv::Mat &img, int scanId);
int zv_cam_basler_payloadSize(int scanId);
int zv_cam_basler_getROI(int scanId, int &offsetX, int &offsetY, int &width, int &height);
int zv_cam_basler_setROI(int scanId, int offsetX, int offsetY, int width, int height);
int zv_cam_basler_param(int scanId, char *prop, char *value, int valueLen, bool isGet);
int zv_cam_basler_cmd(int scanId, int prop);
int zv_cam_basler_value(int scanId, int prop, double &value, bool isGet);
//int zv_cam_basler_valueRange(int scanId, int prop, double &minV, double &maxV, double &step);
//int zv_cam_basler_string(int scanId, int prop, char *value, int valueLen, bool isGet);


#ifdef __cplusplus
}
#endif

#endif