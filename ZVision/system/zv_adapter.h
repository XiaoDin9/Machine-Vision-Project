#ifndef ZV_ADAPTER_H
#define ZV_ADAPTER_H
/*
与OpenCV相关并且不导出的定义。
*/
#include "opencv2\opencv.hpp"

#define ZV_MAGIC_NUM_ST     0x1234FF00
typedef enum _ZvMagicNum
{
    ZV_MAGIC_CONTLIST = ZV_MAGIC_NUM_ST,
    ZV_MAGIC_CONTOUR,
}ZvMagicNum;

typedef struct _ZvFeatState
{
    int area : 1;               // 表示使用了int 的 1个bit 位
    int gc : 1;
    int perimeter : 1;
    int circularity : 1;
    int compact : 1;
    int gmean : 1;
    int holeNums : 1;
    int isConvex : 1;
    int convexity : 1;
    int rect : 1;
    int elliAxis : 1;
    int rect2 : 1;
    int outerCircle : 1;

    int mSpatial : 1;
    int mCentral : 1;
    int mNormalC : 1;
    int hu : 1;
}ZvFeatState;

typedef struct _ZvFeatValue
{
    double area;
    double gcX;
    double gcY;
    double perimeter;
    double circularity;
    double compact;
    double mean;
    double holeNums;
    double isConvex;
    double hullArea;
    double convexity;

    double rectX;
    double rectY;
    double rectW;
    double rectH;
    double rectRX;
    double rectBY;
    double rectRatio;
    double axisMajor;
    double axisMinor;
    double axisAngle;
    double axisRatio;
    double rect2CX;
    double rect2CY;
    double rect2W;
    double rect2H;
    double rect2Anale;
    double rect2Ratio;
    double outerCX;
    double outerCY;
    double outerCR;
    double reserve[5];
    cv::Moments moment; //24double
    double hu[7];
}ZvFeatValue;

typedef struct _ZvContour
{
    int magicNum;
    int curId;                  //对应指针的索引
    int contId;                 //cont指向对应的位置索引
    bool isRele;
    vector< cv::Point > *cont;
    vector< int > hullId;       //凸包点索引
    ZvFeatState status;
    union
    {
        double value[ZV_FEAT_MAX];
        ZvFeatValue featVal;
    };

    _ZvContour()
    {
        magicNum = ZV_MAGIC_CONTOUR;
        cont = NULL;
        isRele = false;
        curId = 0; 
        contId = 0;
        memset(&status, 0, sizeof(status));
        memset(&featVal, 0, sizeof(featVal));
    }

    ~_ZvContour()
    {
        release();
    }

    inline bool release()
    {
        if (isRele)
        {
            delete cont;
            isRele = false;
        }
        cont = NULL;
        return true;
    }

    inline bool createContour()
    {
        release();
        isRele = true;
        cont = new vector< cv::Point >;
        return NULL != cont;
    }

    inline bool createContour(int size)
    {
        release();
        isRele = true;
        cont = new vector< cv::Point >(size);
        return NULL != cont;
    }

    inline cv::Point& operator [] (int i)
    {
        return (*cont)[i];
    }

    inline int size()
    {
        return NULL == cont ? 0 : (int)cont->size();
    }
}_ZvContour;

typedef struct _ZvContList
{
    int magicNum;
    int _size;
    vector< vector< cv::Point > > cdata;
    vector< cv::Vec4i > hierarchy;
    vector< _ZvContour > clist;
    vector< _ZvContour * > cptr;

    _ZvContList()
    {
        magicNum = ZV_MAGIC_CONTLIST;
        _size = 0;
    }

    inline _ZvContour * operator [] (int i)
    {
        return cptr[i];
    }

    inline int size()
    {
        return _size;
    }
}_ZvContList;

typedef cv::Mat _ZvMatrix;
typedef _ZvMatrix _ZvImage;


typedef _ZvMatrix * ZvMatrix;
typedef _ZvImage * ZvImage;
typedef void * ZvObject;
typedef _ZvContour * ZvContour;
typedef _ZvContList * ZvContList;

typedef struct _ZvModel
{
    bool isRele;
    double angleStart;
    double angleExt;
    double angleStep;
    int numRotateTempl;
    int numLevel;
    vector<cv::Mat> *Zvmod;

    _ZvModel()
    {
        isRele = false;
        angleStart = 0.0;
        angleExt = 0.0;
        angleStep = 0.0;
        numRotateTempl = 0;
        numLevel = 0;
        Zvmod = NULL;
    }

    ~_ZvModel()
    {
        release();
    }

    inline bool release()
    {
        if (isRele)
        {
            delete Zvmod;
            isRele = false;
        }
        Zvmod = NULL;
        return true;
    }
    inline bool createZvModel(int size)
    {
        release();
        isRele = true;
        Zvmod = new vector<cv::Mat >[size];
        return NULL != Zvmod;
    }
}_ZvModel;

typedef _ZvModel * ZvModel;    //注意：_ZvModel 是结构体类型

extern int * g_zv_adp_notNull;

#define ZV_ADP_OBJ_MP(_zvObj)  ((cv::Mat *)(_zvObj))

#define ZV_ADP_IMG_MP(_zvImage) ((cv::Mat *)(_zvImage))
#define ZV_ADP_IMG_SETM(_zvImage, _mat) (*((cv::Mat *)(_zvImage)) = (_mat))
#define ZV_ADP_IMG_GETM(_zvImage) (*((cv::Mat *)(_zvImage)))
#define ZV_ADP_IMG_GETM_CHK(_zvImage) ((NULL == (_zvImage)) ? cv::Mat() : *((cv::Mat *)(_zvImage)))

#define ZV_ADP_MAT_MP(_zvMat) ((cv::Mat *)(_zvMat))
#define ZV_ADP_MAT_SETM(_zvMat, _mat) (*(_zvMat) = (_mat))
#define ZV_ADP_MAT_GETM(_zvMat) (*((cv::Mat *)(_zvMat)))
#define ZV_ADP_MAT_GETM_CHK(_zvMat) ((NULL == (_zvMat)) ? cv::Mat() : *((cv::Mat *)(_zvMat)))

#define ZV_ADP_CONT(_cont) (*((ZvContour)(_cont))->cont)

extern int g_zv_adp_interp[];
#define ZV_ADP_INTERP(p) (g_zv_adp_interp[(p)])

extern int g_zv_adp_depthToCV[];
extern int g_zv_adp_depthFromCV[];

extern int zv_adp_cvErrorCallback(int status, const char* func_name, const char* err_msg,
    const char* file_name, int line, void* userdata);
extern int zv_adp_cvStatus(int status);

extern void zv_adp_borderInfo(string border, int &borderType, double &borderValue);


#endif