#ifndef ZV_CAM_OPENCV_H
#define ZV_CAM_OPENCV_H


#ifdef __cplusplus
extern "C" {
#endif

int zv_cam_cv_release(int scanId);
int zv_cam_cv_scan(int startScanId);
int zv_cam_cv_status(int scanId);
int zv_cam_cv_close(int scanId);
int zv_cam_cv_grab(cv::Mat &img, int scanId);
int zv_cam_cv_roi(int scanId, int &offsetX, int &offsetY, int &width, int &height, bool isGet);
int zv_cam_cv_double(int scanId, int prop, double &value, bool isGet);

#ifdef __cplusplus
}
#endif

#endif