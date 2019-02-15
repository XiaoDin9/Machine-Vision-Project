#ifndef ZV_TYPES_H
#define ZV_TYPES_H


typedef enum _ZvPixelType
{
    ZV_PIXEL_UNDEF = -1,
    ZV_PIXEL_8U = 0,
    ZV_PIXEL_16U,
    ZV_PIXEL_32S,
    ZV_PIXEL_64F,
}ZvPixelType;

typedef enum _ZvInterpolation
{
    ZV_INTERP_NEAREST = 0,
    ZV_INTERP_LINEAR,
    ZV_INTERP_CUBIC,
    ZV_INTERP_LANCZOS,
    ZV_INTERP_MAX,
}ZvInterpolation;

typedef enum _ZvReadImgType
{
    ZV_READ_RAW = 0,        //原格式
    ZV_READ_TO_GRAY = 1,    //灰度
    ZV_READ_TO_RGB = 2,    //彩色
    //ZV_READ_EXDEPTH = 3,    //支持16和32位深度
    //ZV_READ_EXCOLOR = 4,    //支持扩展的颜色空间
    ZV_READ_TYPE_MAX,
}ZvReadImgType;

typedef enum _ZvCamPropertyVal
{
    ZV_CAM_PV_ROI_X = 0,        //ROI
    ZV_CAM_PV_ROI_Y,
    ZV_CAM_PV_ROI_W,
    ZV_CAM_PV_ROI_H,
    ZV_CAM_PV_EXPOSURE,         //曝光
    ZV_CAM_PV_GAIN,             //增益
    ZV_CAM_PV_GAMMA,            //Gamma
    ZV_CAM_PV_BIN_HORI,         //合并像素X
    ZV_CAM_PV_BIN_VERT,         //合并像素Y
    ZV_CAM_PV_FPS,              //帧率
    ZV_CAM_PV_GAIN_R,           //增益R
    ZV_CAM_PV_GAIN_G,           //增益G
    ZV_CAM_PV_GAIN_B,           //增益B
    ZV_CAM_PV_WBALANCE_R,       //白平衡R
    ZV_CAM_PV_WBALANCE_G,       //白平衡G
    ZV_CAM_PV_WBALANCE_B,       //白平衡B

    ZV_CAM_PV_BITS = 80,        //只读 位宽
    ZV_CAM_PV_BUF_SIZE,         //内存大小

    ZV_CAM_PV_EXPOSURE_AUTO = 100, //布尔 自动曝光
    ZV_CAM_PV_GAIN_AUTO,        //自动增益
    ZV_CAM_PV_WBALANCE_AUTO,    //自动白平衡
    ZV_CAM_PV_GAMMA_ENABLE,     //启用Gamma

    ZV_CAM_PV_INPUT0 = 110, //IO
    ZV_CAM_PV_INPUT1,
    ZV_CAM_PV_INPUT2,

    ZV_CAM_PV_OUTPUT0 = 120,
    ZV_CAM_PV_OUTPUT1,
    ZV_CAM_PV_OUTPUT2,
}ZvCamPropertyVal;

typedef enum _ZvCamPropertyCmd
{
    ZV_CAM_PC_SOFT_TRIGGER = 0,
    ZV_CAM_PC_ACQUI_START,
}ZvCamPropertyCmd;

typedef enum _ZvCamPropertyStr
{
    ZV_CAM_PS_SN = 0,       //SN
    ZV_CAM_PS_MODEL,        //型号
    ZV_CAM_PS_DEV_ID,       //设备ID
    ZV_CAM_PS_DEV_NAME,     //设备名称
    ZV_CAM_PS_DISPLAY,      //显示名称
    ZV_CAM_PS_INTERFACE,    //接口类型
    ZV_CAM_PS_PORT,         //端口号
    ZV_CAM_PS_MAC,          //Mac地址
    ZV_CAM_PS_IP,           //IP
    ZV_CAM_PS_HOST_IP,      //主机IP
    ZV_CAM_PS_USER_NAME,    //用户自定义名称
    ZV_CAM_PS_USER_PARAM,   //用户自定义参数

    ZV_CAM_PS_FORMAT = 100, //格式
    ZV_CAM_PS_TRG_MODE,     //触发模式
    ZV_CAM_PS_TRG_POLAR,    //触发极性
    ZV_CAM_PS_TRG_SOURCE,   //触发源
    ZV_CAM_PS_WBALANCE_T,   //白平衡类型
    ZV_CAM_PS_GAMMA_T,      //Gamma类型
}ZvCamPropertyStr;

typedef enum _ZvCamStatus
{
    ZV_CAM_ST_ERROR = -1,    //错误
    ZV_CAM_ST_NULL = 0,        //未绑定
    ZV_CAM_ST_CONNECT,        //未打开
    ZV_CAM_ST_OPENED,        //已打开
    ZV_CAM_ST_REMOVED,        //断开连接
}ZvCamStatus;

typedef enum _ZvColorSpace
{
    ZV_CLR_YUV = 0,
    ZV_CLR_HSV,
    ZV_CLR_LAB,
    ZV_CLR_HLS,
    ZV_CLR_YCRCB,
    ZV_CLR_LUV,
    ZV_CLR_XYZ,
    ZV_CLR_RGBA,
    ZV_CLR_MAX,
}ZvColorSpace;

typedef enum _ZvBayerType
{
    ZV_BAYER_BG = 0,
    ZV_BAYER_GB,
    ZV_BAYER_RG,
    ZV_BAYER_GR,
}ZvBayerType;

typedef enum _ZvGeoFeature
{
    ZV_FEAT_AREA = 0,       //面积
    ZV_FEAT_GX,             //重心X
    ZV_FEAT_GY,             //重心Y
    ZV_FEAT_PERIMETER,      //周长
    ZV_FEAT_CIRCULARITY,    //圆度
    ZV_FEAT_COMPACT,        //紧致度
    ZV_FEAT_MEAN,           //原图灰度均值
    ZV_FEAT_HOLE_NUMS,      //孔数量
    ZV_FEAT_ISCONVEX,       //凸性
    ZV_FEAT_HULL_AREA,      //凸包面积
    ZV_FEAT_CONVEXITY,      //凸度
    ZV_FEAT_RECT_X,         //外接矩形x
    ZV_FEAT_RECT_Y,         //外接矩形y
    ZV_FEAT_RECT_W,         //外接矩形宽度
    ZV_FEAT_RECT_H,         //外接矩形高度
    ZV_FEAT_RECT_RX,        //外接矩形x + w
    ZV_FEAT_RECT_BY,        //外接矩形y + h
    ZV_FEAT_RECT_RATIO,     //外接矩形h / w
    ZV_FEAT_EA_MAJOR,       //惯量主轴
    ZV_FEAT_EA_MINOR,       //惯量次轴
    ZV_FEAT_EA_ANGLE,       //主轴角度
    ZV_FEAT_EA_RATIO,       //次轴/主轴
    ZV_FEAT_RECT2_CX,       //最小矩形中心X
    ZV_FEAT_RECT2_CY,       //最小矩形中心Y
    ZV_FEAT_RECT2_W,        //最小矩形宽度
    ZV_FEAT_RECT2_H,        //最小矩形高度
    ZV_FEAT_RECT2_ANGLE,    //最小矩形角度
    ZV_FEAT_RECT2_RATIO,    //最小矩形h/w
    ZV_FEAT_OC_X,           //外接圆X
    ZV_FEAT_OC_Y,           //外接圆Y
    ZV_FEAT_OC_R,           //外接圆R

    ZV_FEAT_M_S00 = 36,          //空间矩 10个
    ZV_FEAT_M_S10,
    ZV_FEAT_M_S01,
    ZV_FEAT_M_S20,
    ZV_FEAT_M_S11,
    ZV_FEAT_M_S02,
    ZV_FEAT_M_S30,
    ZV_FEAT_M_S21,
    ZV_FEAT_M_S12,
    ZV_FEAT_M_S03,

    ZV_FEAT_M_C20,          //中心矩 7个
    ZV_FEAT_M_C11,
    ZV_FEAT_M_C02,
    ZV_FEAT_M_C30,
    ZV_FEAT_M_C21,
    ZV_FEAT_M_C12,
    ZV_FEAT_M_C03,
    ZV_FEAT_M_N20,          //归一化中心距 7个
    ZV_FEAT_M_N11,
    ZV_FEAT_M_N02,
    ZV_FEAT_M_N30,
    ZV_FEAT_M_N21,
    ZV_FEAT_M_N12,
    ZV_FEAT_M_N03,

    ZV_FEAT_HU0,            //hu矩7个
    ZV_FEAT_HU1,
    ZV_FEAT_HU2,
    ZV_FEAT_HU3,
    ZV_FEAT_HU4,
    ZV_FEAT_HU5,
    ZV_FEAT_HU6,
    ZV_FEAT_MAX,
}ZvGeoFeature;

typedef enum _ZvDefColor
{
    ZV_RED = 0,
    ZV_GREEN,
    ZV_BLUE,
    ZV_WHITE,
    ZV_BLACK,
    ZV_DEF_CLR_MAX,
}ZvDefColor;

typedef enum _ZvThreshPolar //边缘极性
{
    ZV_POLAR_TODARK,    //白黑
    ZV_POLAR_TOLIGHT,   //黑白
    ZV_POLAR_ALL,       //所有
}ZvThreshPolar;

typedef enum _ZvEdgePos //边缘位置
{
    ZV_EDGE_FIRST,      //第一点
    ZV_EDGE_LAST,       //最后点
    ZV_EDGE_MAX,        //最强点
    ZV_EDGE_ALL,        //所有点
}ZvEdgePos;

#endif // ZV_DEFINE_H
