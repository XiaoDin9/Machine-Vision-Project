#pragma execution_character_set("utf-8")
#include "camera_setparm.h"
//加载QT API.
#include <qdebug.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qwidget.h>
#include "qprocess.h" 
#include <qdir.h>
#include <qtextcodec.h>
#include <qdatetime.h>
#include <qsettings.h>
#include <qmutex.h>

#define USE_NOW_PYLON     //使用现在的工程项目，用来配置相机的初始化参数

#define DEFAULT_DEPTH 8

//命名空间.  

using namespace std;

//全局变量
QMutex mutex;
bool flag_parea_set = true;
QString iniFilePath = "MyINI.ini";      //写相机参数配置到配置文件
QSettings settings(iniFilePath, QSettings::IniFormat);

/*====================初始化相机的参数====================*/
//初始化相机的参数
CCameraParam::CCameraParam()
{
    m_X = 0;
    m_Y = 0;
    m_Width = 64;
    m_Height = 64;
    m_Depth = DEFAULT_DEPTH;
    m_Channel = 1;
    m_ExpTime = 1000;
    m_Heartbeat = 3000;
    m_strPixelFormat = "Mono 8";
    m_strCamName = "未定义";
    m_strUserId = "-1";

    m_isTrigger = false;
    m_isAttach = false;
}

Camera_SetParm::Camera_SetParm(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_CamParamsNum = 1;
    m_CamActNum = 1;
    m_pCamParams = NULL;
    m_ParamsBufSize = 0;
    m_isInit = false;
}

//析构函数达到释放资源的作用
Camera_SetParm::~Camera_SetParm(){
    Destroy();
}

//若摄像机 准备好了就会返回一个 true
bool Camera_SetParm::IsCameraReady(int index)
{
    if (index < 0 || index >= m_CamParamsNum)   // index 无效的情况
    {
        return false;
    }

    if (!m_pCamParams[index].m_isAttach)    // 如出现这种情况，也是无效的情况
    {
        return false;
    }

    return true;
}

//给数据分配缓冲区
void Camera_SetParm::AllocDataBuffer()
{
    if (m_CamParamsNum > m_ParamsBufSize && 0 != m_ParamsBufSize)  //如果相机所采集的图像量 不满足 缓冲区的要求的情况下
    {
        Destroy();
    }

    if (NULL == m_pCamParams)    // 初始化的 m_pCamParams 为 NULL
    {
        m_pCamParams = new CCameraParam[m_CamParamsNum];   //定义 对象指针
        m_ParamsBufSize = m_CamParamsNum;
    }
    else
    {
        for (int i = 0; i<m_ParamsBufSize; i++)
        {
            m_pCamParams[i] = CCameraParam();   //对缓冲区的每个可以存图像的块 进行初始化工作
        }
    }
}

//初始化 系统参数
bool Camera_SetParm::InitSystem(int cameraCnt)
{
    ReadIniFile();   // 读初始化设备的文件


    InitCamerasAndGetPara();   //包括了打开摄像头操作
    GetParaFromCamera(0);


    return true;
}

//得到摄像头的数量
int Camera_SetParm::GetCameraCount()
{
    return m_CamParamsNum;
}

int Camera_SetParm::GetCameraActCount()
{
    return m_CamActNum;
}

//调整 值
int64_t Camera_SetParm::Adjust(int64_t val, int64_t minimum, int64_t maximum, int64_t inc)
{
    // Check the input parameters.
    if (inc <= 0)
    {
        return minimum;
    }
    if (minimum > maximum)
    {
        return minimum;
    }

    // Check the lower bound.
    if (val < minimum)
    {
        return minimum;
    }

    // Check the upper bound.
    if (val > maximum)
    {
        return maximum;
    }

    // Check the increment.
    if (inc == 1)
    {
        return val;
    }
    else
    {
        return minimum + (((val - minimum) / inc) * inc);
    }
}

void Camera_SetParm::InitCamerasAndGetPara(void)
{

}

// 从Camare 中获取参数
bool Camera_SetParm::GetParaFromCamera(int index)
{
    if (!IsCameraReady(index))
    {
        return false;
    }

    return true;
}

//　设置Camare 内部的参数
void Camera_SetParm::SetParaToCamera(int index)
{
    if (!IsCameraReady(index))
    {
        return;
    }

    return ;
    zv_camSetROI(index, m_pCamParams[index].m_X, m_pCamParams[index].m_Y, m_pCamParams[index].m_Width, m_pCamParams[index].m_Height);
    zv_camSetExposure(index, m_pCamParams[index].m_ExpTime);
    double exposure = 0;
    zv_camGetExposure(index, &exposure);
    m_pCamParams[index].m_ExpTime = (int)exposure;
}


//设置曝光时间和得到曝光时间
int Camera_SetParm::GetExposureTime(int index)
{
    if (index < 0 || index >= m_CamParamsNum)
    {
        return -1;
    }

    return m_pCamParams[index].m_ExpTime;
}

void Camera_SetParm::SetExposureTime(int index, int ExposureTime)
{
    if (!IsCameraReady(index))
    {
        return;
    }

    if (ExposureTime == m_pCamParams[index].m_ExpTime)
    {
        return;
    }

    zv_camSetExposure(index, ExposureTime);
    m_pCamParams[index].m_ExpTime = ExposureTime;
    WriteIni();
}


//得到图像的实际尺寸
bool Camera_SetParm::GetImageSize(int index, int &width, int &height)
{
    width = height = 0;
    if (index < 0 || index >= m_CamParamsNum)
    {
        return false;
    }
    width = m_pCamParams[index].m_Width;
    height = m_pCamParams[index].m_Height;
    return true;
}

bool Camera_SetParm::GetImageInfo(int index, int *width, int *height, int *channel, int *depth)
{
    int w = 0, h = 0, c = 0, d = 0;
    if (index >= 0 && index < m_CamParamsNum)  //index 无效的情况下
    {
        w = m_pCamParams[index].m_Width;
        h = m_pCamParams[index].m_Height;
        c = m_pCamParams[index].m_Channel;
        d = m_pCamParams[index].m_Depth;
    }
    //初始化 w 、 h 、c 、d 的值为 0
    if (width) *width = w;
    if (height) *height = h;
    if (channel) *channel = c;
    if (depth) *depth = d;
    return (0 != w);
}

//得到图像的长度
int Camera_SetParm::GetImageLength(int index)
{
    if (index < 0 || index >= m_CamParamsNum)   // 判断index 是否是对的值
    {
        return 0;
    }

    CCameraParam *p = m_pCamParams + index;   // 指向Camare 类的指针 + 偏移的值
    return p->m_Width*p->m_Height*p->m_Channel*p->m_Depth / (sizeof(char) * 8);    //得到图像的长度 = I_h * I_w * I_D * I_C / (sizeof(char)*8)
}

//对相机进行释放处理
void Camera_SetParm::Destroy()
{
    // m_Cameras 是camera 临时的对象
    zv_modExit();

    if (m_pCamParams != NULL)   //相机参数类的变量，初始化的值设置为 NULL
    {
        delete[] m_pCamParams;       //  m_pCamParams 是指向 CamParams 类的指针变量 
        m_pCamParams = NULL;
        m_ParamsBufSize = 0;    //把缓冲去的大小归零化
    }
}


//停止抓取图像
//void Camera_SetParm::GrabStopAll()
//{
//    m_Cameras.StopGrabbing();   // Camare 停止抓取工作
//}

//bool Camera_SetParm::GrabStop(int index){
//    if (!IsCameraReady(index))  //　判断　camare 是否准备好啦
//    {
//        return false;
//    }
//    m_Cameras[index].StopGrabbing();
//    return false;
//}

// 继续抓取
//bool Camera_SetParm::GrabContinue(int index){
//    if (!IsCameraReady(index)){
//        return false;
//    }
//
//    if (!m_Cameras[index].IsGrabbing())   // 判断有没有开始抓取过图像，即：是否曾经开启过图像的抓取
//    {
//        m_Cameras[index].StartGrabbing(GrabStrategy_OneByOne);   // 设置相机以one-by-on 的模式进行抓取图像
//    }
//    return m_Cameras[index].IsGrabbing();   // 继续抓取
//}

//Camera 抓取一帧图像
int Camera_SetParm::GrabOne(int index, ZvImage img)   //index 是一个标记
{
    zv_camGrab(img, index);
    return 0;
}

//void Camera_SetParm::SetTrigger(int index, bool isTrigger)
//{
//    if (!IsCameraReady(index))
//    {
//        return;
//    }
//
//    GenApi::INodeMap& nodemap1 = m_Cameras[index].GetNodeMap();
//
//    m_pCamParams[index].m_isTrigger = isTrigger;
//    GenApi::CEnumerationPtr PtrTriggerSelector(nodemap1.GetNode("TriggerSelector"));
//    PtrTriggerSelector->FromString("FrameStart");
//    GenApi::CEnumerationPtr ptrTriggerMode(nodemap1.GetNode("TriggerMode"));
//    if (isTrigger)
//    {
//        ptrTriggerMode->FromString("On");//*/
//    }
//    else
//    {
//        ptrTriggerMode->FromString("Off");//*/
//    }
//}

//　得到camare 的名字
//QString Camera_SetParm::GetCameraName(int index)
//{
//    if (index < 0 || index >= m_CamParamsNum)
//    {
//        return "";
//    }
//    return m_pCamParams[index].m_strCamName;
//}

// 读初始化设备的文件
bool Camera_SetParm::ReadIniFile() {

    if (m_CamParamsNum <= 0)   //没有包含参数量，肯定有错误
    {
        return false;
    }

#ifdef USE_AGO_PYLON
    AllocDataBuffer();        // 分配数据缓冲区 
    mutex.lock();       //must lockbuffer, otherwise the buffer will be shared with other QString 必须加锁处理
    for (int i = 0; i < m_CamParamsNum; i++)    // m_CamParamsNum 为缓冲区的实际图像张数
    {
        // 设置图像的一些参数,如果文件.ini 中有值，直接从中获得对应“键”对应的值，否则=默认值
        if (ui.lineEdit->text() != NULL) {     //之前有载入值的情况
            QString PixelFormat = settings.value("Basler Camera/PixelFormat").toString();
            m_pCamParams[i].m_strPixelFormat = PixelFormat;
            m_pCamParams[i].m_Depth = DEFAULT_DEPTH;

            m_pCamParams[i].m_X = settings.value("Basler Camera/OffsetX").toInt();
            m_pCamParams[i].m_Y = settings.value("Basler Camera/OffsetY").toInt();
            m_pCamParams[i].m_Width = settings.value("Basler Camera/Width").toInt();
            m_pCamParams[i].m_Height = settings.value("Basler Camera/Height").toInt();
            m_pCamParams[i].m_ExpTime = settings.value("Basler Camera/ExposureTime").toInt();
            m_pCamParams[i].m_Heartbeat = settings.value("Basler Camera/Heartbeat").toInt();

            QString UserID = settings.value("Basler Camera/UserID").toString();
            m_pCamParams[i].m_strUserId = UserID;

            QString CameraName = settings.value("Basler Camera/CameraName").toString();
            m_pCamParams[i].m_strCamName = CameraName;
        }
        else {    //一直没有进行初始的时候
            QString PixelFormat = "Mono 8";
            m_pCamParams[i].m_strPixelFormat = PixelFormat;
            m_pCamParams[i].m_Depth = DEFAULT_DEPTH;

            m_pCamParams[i].m_X = 0;
            m_pCamParams[i].m_Y = 0;
            m_pCamParams[i].m_Width = 1024;
            m_pCamParams[i].m_Height = 768;
            m_pCamParams[i].m_ExpTime = 35000;
            m_pCamParams[i].m_Heartbeat = 500;

            QString UserID = "00";
            m_pCamParams[i].m_strUserId = UserID;

            QString CameraName = "未定义";
            m_pCamParams[i].m_strCamName = CameraName;
        }
    }
    mutex.unlock();   //关锁处理
    return true;
#elif defined USE_NOW_PYLON
    camsetparam = new CameraSetParam;
    mutex.lock();       //must lockbuffer, otherwise the buffer will be shared with other QString 必须加锁处理
    for (int i = 0; i < m_CamParamsNum; i++)    // m_CamParamsNum 为缓冲区的实际图像张数
    {
        // 设置图像的一些参数,如果文件.ini 中有值，直接从中获得对应“键”对应的值，否则=默认值
        if (ui.lineEdit->text() != NULL) {     //之前有载入值的情况
            QString PixelFormat = settings.value("Basler Camera/PixelFormat").toString();
            camsetparam->m_strPixelFormat = PixelFormat;
            camsetparam->m_Depth = DEFAULT_DEPTH;
            camsetparam->offsetX = settings.value("Basler Camera/OffsetX").toInt();
            camsetparam->offsetY = settings.value("Basler Camera/OffsetY").toInt();
            camsetparam->Width = settings.value("Basler Camera/Width").toInt();
            camsetparam->Height = settings.value("Basler Camera/Height").toInt();
            camsetparam->ExpTime = settings.value("Basler Camera/ExposureTime").toInt();
            camsetparam->Heartbeat = settings.value("Basler Camera/Heartbeat").toInt();

            QString UserID = settings.value("Basler Camera/UserID").toString();
            camsetparam->m_strUserId = UserID;

            QString CameraName = settings.value("Basler Camera/CameraName").toString();
            camsetparam->m_strCamName = CameraName;
        }
        else {
            QString PixelFormat = "Mono 8";
            camsetparam->m_strPixelFormat = PixelFormat;
            camsetparam->m_Depth = DEFAULT_DEPTH;

            camsetparam->offsetX = 0;
            camsetparam->offsetY = 0;
            camsetparam->Width = 2592;
            camsetparam->Height = 1944;
            camsetparam->ExpTime = 35000;
            camsetparam->Heartbeat = 500;

            QString UserID = "00";
            camsetparam->m_strUserId = UserID;

            QString CameraName = "Basler acA2500-14gm(22533411)";
            camsetparam->m_strCamName = CameraName;
        }
    }
    mutex.unlock();   //关锁处理
    return true;
#endif    
}

//加载外部设置的参数到相机中去
bool Camera_SetParm::WriteIni(){
    for (int i = 0; i<m_CamParamsNum; i++){
        if (ui.lineEdit->text() != NULL) {
            settings.setValue("Basler Camera/PixelFormat", ui.lineEdit->text());
        
            settings.setValue("Basler Camera/OffsetX", ui.lineEdit_4->text().toInt());
            settings.setValue("Basler Camera/OffsetY", ui.lineEdit_5->text().toInt());        
            settings.setValue("Basler Camera/Width", ui.lineEdit_9->text().toInt());
            settings.setValue("Basler Camera/Height", ui.lineEdit_10->text().toInt());    
            settings.setValue("Basler Camera/ExposureTime", ui.lineEdit_11->text().toInt());
            settings.setValue("Basler Camera/Heartbeat", ui.lineEdit_12->text().toInt());

            settings.setValue("Basler Camera/UserID", ui.lineEdit_13->text());
            settings.setValue("Basler Camera/CameraName", ui.lineEdit_14->text());
        }
    }

    return true;
}

void Camera_SetParm::on_load_clicked() {
    int cameraCnt = 1;         //为要构造总的相机数目

    if(flag_parea_set) m_CamParamsNum = ui.comboBox->itemText(ui.comboBox->currentIndex()).toInt();   //获得配置的摄像头个数
    //InitSystem(cameraCnt);     //初始化, 在新版本中使用的时候不需要这条语句
    ReadIniFile();   // 读初始化设备的文件
}

void Camera_SetParm::on_update_clicked() {
    m_CamParamsNum = ui.comboBox->itemText(ui.comboBox->currentIndex()).toInt();   //获得配置的摄像头个数
    WriteIni();
    flag_parea_set = false;
}