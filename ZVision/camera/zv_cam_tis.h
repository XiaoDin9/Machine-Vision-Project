#ifndef ZV_CAM_TIS_H
#define ZV_CAM_TSI_H


#ifdef __cplusplus
extern "C" {
#endif

int zv_cam_tis_release(int scanId);
int zv_cam_tis_init();
int zv_cam_tis_exit();

int zv_cam_tis_scan(int startScanId);
int zv_cam_tis_getInfo(int scanId, int info, char *value, int maxValLen);
int zv_cam_tis_open(int scanId);
int zv_cam_tis_status(int scanId);
int zv_cam_tis_close(int scanId);
int zv_cam_tis_grab(cv::Mat &img, int scanId);
int zv_cam_tis_payloadSize(int scanId);
int zv_cam_tis_getROI(int scanId, int &offsetX, int &offsetY, int &width, int &height);
int zv_cam_tis_setROI(int scanId, int offsetX, int offsetY, int width, int height);
int zv_cam_tis_cmd(int scanId, int prop);
int zv_cam_tis_value(int scanId, int prop, double &value, bool isGet);
int zv_cam_tis_valueRange(int scanId, int prop, double &minV, double &maxV, double &step);


#ifdef __cplusplus
}
#endif

#endif