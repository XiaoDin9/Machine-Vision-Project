#ifndef CAMERA_SETPARM_H
#define CAMERA_SETPARM_H

//加载QT API.
#include <qdebug.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qwidget.h>
#include "qprocess.h" 
#include <qdir.h>
#include <qtextcodec.h>
#include <qdatetime.h>

#include <QWidget>
#include "ui_camera_setparm.h"

#include "zv.h"
using namespace std;

class CameraSetParam {
public:
    CameraSetParam() {};
    ~CameraSetParam() {};

    int offsetX;
    int offsetY;
    int m_Depth;
    int Width;
    int Height;
    int ExpTime;    //曝光时间
    int Heartbeat;  //心跳时间

    QString m_strPixelFormat;    //像素的格式
    QString m_strUserId;
    QString m_strCamName;        //相机的名字
};

class CCameraParam    //param 参数
{
public:
    CCameraParam();
    virtual ~CCameraParam() {};

    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;
    int m_Depth;
    int m_Channel;
    int m_ExpTime;    //曝光时间
    int m_Heartbeat;  //心跳时间

    QString m_strPixelFormat;    //像素的格式
    QString m_strUserId;
    QString m_strCamName;        //相机的名字

    bool m_isTrigger;
    bool m_isAttach;
};

class Camera_SetParm : public QWidget
{
    Q_OBJECT

public:
    Camera_SetParm(QWidget *parent = 0);
    ~Camera_SetParm();

    int GrabOne(int index, ZvImage img);
    //void GrabStopAll();
    //bool GrabStop(int index);
    //bool GrabContinue(int index);
    void SetExposureTime(int index, int exposureTime);
    int GetExposureTime(int index);
    //void GetExposureTimeMinMax(int index, int &min, int &max);
    int GetCameraCount();
    int GetCameraActCount();
    bool GetImageSize(int index, int &width, int &height);
    bool GetImageInfo(int index, int *width, int *height, int *channel, int *depth);
    int GetImageLength(int index);
    //QString GetCameraName(int index);
    //int GetDepth(QString pixFormat);
    //int GetDepth(int index);

    //相机硬件触发
    //void SetTrigger(int index, bool isTrigger);
    
    CameraSetParam *camsetparam;

private:
    Ui::Camera_SetParm ui;
    CCameraParam * m_pCamParams;
    int m_CamActNum;    //加载的相机总数
    int m_CamParamsNum;
    int m_ParamsBufSize;   //缓冲区的大小
    QString m_strConfigFile;
    int m_isInit;

    bool IsCameraReady(int index);    //判断camera 是否准备好啦
    bool GetParaFromCamera(int index);
    void SetParaToCamera(int index);
    void AllocDataBuffer();
    bool InitSystem(int cameraCnt);
    void Destroy();
    bool WriteIni();
    bool ReadIniFile();
    void InitCamerasAndGetPara(void);
    int64_t Adjust(int64_t val, int64_t minimum, int64_t maximum, int64_t inc);
    
private slots :
    void on_load_clicked();
    void on_update_clicked();
};


#endif // CAMERA_SETPARM_H
