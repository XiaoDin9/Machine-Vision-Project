#ifndef ZV_CAMERA_H
#define ZV_CAMERA_H


#define ZV_CAM_MAX_NUM    ZV_SYS_CAMERA_MAX

#ifdef __cplusplus
extern "C" {
#endif

extern int g_zv_cam_count;

int zv_cam_init();
int zv_cam_exit();

int zv_cam_scan(char *type);
inline int zv_cam_count() { return g_zv_cam_count; };
int zv_cam_getInfo(int scanId, int prop, char *value, int maxValLen);
int zv_cam_open(int camId, int scanId);
int zv_cam_status(int camId);
int zv_cam_close(int camId);
int zv_cam_payloadSize(int camId);
int zv_cam_grab(ZvImage img, int camId);
int zv_cam_getIO(int camId);
int zv_cam_setIO(int camId, int offset);
int zv_cam_getROI(int camId, int *offsetX, int *offsetY, int *width, int *height);
int zv_cam_setROI(int camId, int offsetX, int offsetY, int width, int height);
double zv_cam_getExposure(int camId);
int zv_cam_setExposure(int camId, double time);
int zv_cam_getParam(int camId, char *param, char *value, int valueLen);
int zv_cam_setParam(int camId, char *param, char *value);
int zv_cam_startGrabbing(int camId, int bufCount);
int zv_cam_isGrabbing(int camId, int *isGrabbing);
int zv_cam_retrieve(ZvImage img, int camId, int bufId);
int zv_cam_reset(int camId);


#ifdef __cplusplus
}
#endif

#endif