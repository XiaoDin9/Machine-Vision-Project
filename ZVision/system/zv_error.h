#ifndef ZV_ERROR_H
#define ZV_ERROR_H


typedef enum _ZvStatus
{
    ZV_ST_OK = 0x0,
//    1    数据类型自动转换
//    2    接收终止等待信号
    ZV_ST_MATCH_FAIL = 0x400,

    ZV_WARN_RELE_NULL = 0x800,          //警告类型，释放空指针
    ZV_WARN_RELE_NONE = 0x801,          //释放空类型
    ZV_WARN_RELE_UNINIT = 0x802,        //释放未初始化的结构
    ZV_WARN_FILE_NOT_EXIST = 0x900,     //文件不存在
    ZV_WARN_NODE_NOT_EXIST = 0x901,     //节点不存在

    ZV_ERR_START = ZV_SYS_ERR_START,     //0x1000 错误代码开始
    ZV_ERR_GENERAL_START = 0x1001,      //一般错误 0x1001-1DFF
    ZV_ERR_G_UNDEF = ZV_ERR_GENERAL_START,  //未知的错误
    ZV_ERR_G_CPP_EXCEP = 0x1002,        //C++异常
    ZV_ERR_G_ASSERT = 0x1003,           //断言错误
    ZV_ERR_G_NULL_PTR = 0x1004,
    ZV_ERR_G_STD_EXCEP = 0x1005,        //std库异常
    ZV_ERR_G_LIB_EXCEP = 0x1006,        //未知的第三方库异常 驱动、相机、编解码等
    ZV_ERR_G_LIB_RUN = 0x1007,          //未知的第三方库错误状态
    ZV_ERR_G_DIV_ZERO = 0x1008,         //除零错误
    ZV_ERR_G_VEC_SIZE = 0x1009,         //vector长度错误
    ZV_ERR_G_BUF_SMALL = 0x100C,        //输出TABLE长度不足
    ZV_ERR_G_OBJ_NOT_EXIST = 0x100D,    //目标不存在
    ZV_ERR_G_LIB_ASSERT,
    
    ZV_ERR_G_UNFINISHED = 0x1D30,
    ZV_ERR_G_NOT_SUPPORT = 0x1D40,      //不支持的功能
    ZV_ERR_G_NSP_CL = 0x1D50,           //不支持的OPENCL应用
    ZV_ERR_G_NSP_GL = 0x1D51,           //不支持的OPENGL应用
    ZV_ERR_G_NSP_CUDA = 0x1D52,         //不支持的CUDA应用

    ZV_ERR_TASK_START = 0x1E00,         //任务
    ZV_ERR_T_PARAM_SIZE = 0x1E00,       //任务参数缓冲区不足
    ZV_ERR_T_THREAD_ID = 0x1E01,        //任务线程ID超出范围

    ZV_ERR_MEN_START = 0x2000,              //0x2000-0x20FF
    ZV_ERR_MEM_ALLOC = ZV_ERR_MEN_START,    //内存分配失败    内存MEM
    ZV_ERR_MEM_CORRUPTED = 0x2001,          //分配的内存被破坏
    
    ZV_ERR_FILE_START = 0x2100,
    ZV_ERR_F_NOT_EXIST = ZV_ERR_FILE_START, //文件不存在
    ZV_ERR_F_OPEN_FAIL = 0x2101,            //文件打开出错
    ZV_ERR_F_SAVE_FAIL = 0x2102,
    ZV_ERR_F_FORMAT = 0x2121,               //错误的文件格式

    ZV_ERR_CAM_START = 0x2200,
    ZV_ERR_CAM_GRAB = ZV_ERR_CAM_START,
    ZV_ERR_CAM_GRAB_TIMEOUT = 0x2201,
    ZV_ERR_CAM_SCANID = 0x2202,         //设备枚举ID超出范围
    ZV_ERR_CAM_CAMID = 0x2203,          //设备ID超出范围
    ZV_ERR_CAM_UNBOUND = 0x2204,        //未绑定设备
    ZV_ERR_CAM_OPEN = 0x2205,           //设备打开出错
    ZV_ERR_CAM_SCAN,
    ZV_ERR_CAM_NONE = 0x2209,           //未发现设备
    ZV_ERR_CAM_UNKNOWN = 0x220F,        //设备状态未知
    ZV_ERR_CAM_PARAM_UNDEF = 0x2210,    //参数名字不支持
    ZV_ERR_CAM_PARAM_RD = 0x2211,       //读取参数出错
    ZV_ERR_CAM_PARAM_WR = 0x2212,       //写入参数出错
    ZV_ERR_CAM_INIT_TIS = 0x22E0,       //初始化TIS驱动失败

    ZV_ERR_FUN_ARG_START = 0x2600,      //函数参数错误
    ZV_ERR_FA_TYPE = 0x2640,            //参数类型错误
    ZV_ERR_FA_TYPE_1 = 0x2641,
    ZV_ERR_FA_TYPE_2 = 0x2642,
    ZV_ERR_FA_TYPE_3 = 0x2643,
    ZV_ERR_FA_RANGE = 0x2660,           //参数超出范围，标志错误或不支持
    ZV_ERR_FA_RANGE_1 = 0x2661,
    ZV_ERR_FA_RANGE_2 = 0x2662,
    ZV_ERR_FA_RANGE_3 = 0x2663,
    ZV_ERR_FA_RANGE_4 = 0x2664,
    ZV_ERR_FA_RANGE_5 = 0x2665,
    ZV_ERR_FA_RANGE_6 = 0x2666,
    ZV_ERR_FA_RANGE_7 = 0x2667,
    ZV_ERR_FA_RANGE_8 = 0x2668,
    ZV_ERR_FA_RANGE_9 = 0x2669,
    ZV_ERR_FA_RANGE_10 = 0x266A,
    ZV_ERR_FA_NULL = 0x2680,            //参数为空
    ZV_ERR_FA_NULL_1 = 0x2681,          //参数1为空
    ZV_ERR_FA_NULL_2 = 0x2682,
    ZV_ERR_FA_NULL_3 = 0x2683,
    ZV_ERR_FA_NULL_4 = 0x2684,
    ZV_ERR_FA_NULL_5 = 0x2685,
    ZV_ERR_FA_NULL_6 = 0x2686,
    ZV_ERR_FA_NULL_7 = 0x2687,
    ZV_ERR_FA_NULL_8 = 0x2688,

    ZV_ERR_M_START = 0x3000,            //M Mat类型通用操作
    ZV_ERR_M_SIZE = 0x3001,             //尺寸不符合要求
    ZV_ERR_M_SIZE_INVALID = 0x3002,     //尺寸无效
    ZV_ERR_M_OVER_SIZE = 0x3003,        //尺寸超出范围
    ZV_ERR_M_EMPTY = 0x3004,            //数据为空
    ZV_ERR_M_DATA_FORMAT = 0x3005,      //不支持的数据格式   //如不连续存放
    ZV_ERR_M_DIM = 0x300B,              //维度超出范围
    ZV_ERR_M_ROI = 0x3020,              //ROI尺寸错误
    ZV_ERR_M_SIZE_UNMATCH = 0x3030,     //输入输出尺寸不匹配
    ZV_ERR_M_TYPE_UNMATCH = 0x3031,     //输入输出类型不匹配

    ZV_ERR_IMG_START = 0x3200,              //IMG 图像操作错误I
    ZV_ERR_I_ONLY_8UC1 = ZV_ERR_IMG_START,  //图像格式错误，仅支持8位单通道
    ZV_ERR_I_DEPTH = 0x3201,                //不支持或未定义的数据类型
    ZV_ERR_I_CN = 0x3204,
    ZV_ERR_I_CN_UNMATCH = 0x3205,           //通道数量不匹配
    ZV_ERR_I_CN_SRC = 0x3206,               //源图像通道数错误
    ZV_ERR_I_CN_DST = 0x3207,
    ZV_ERR_I_ONLY_CN1 = 0x3208,             //仅支持单通道图像
    ZV_ERR_I_ALIGN = 0x3209,

    ZV_ERR_MAT_START = 0x3300,              //MAT 矩阵
    ZV_ERR_MAT_MUL_SIZE = ZV_ERR_MAT_START, //矩阵乘尺寸不匹配
    ZV_ERR_MAT_NOT_SQUARE = 0x3301,         //矩阵不是方阵
    
    ZV_ERR_C_START = 0x3400,                //CONT 轮廓C
    
    ZV_ERR_DRA_START = 0x3500,              //绘图dra
    ZV_ERR_DRA_COLOR_NAME = ZV_ERR_DRA_START,   //不支持的颜色名字
    ZV_ERR_DRA_COLOR_RANGE = 0x3501,        // 颜色值超出范围
    ZV_ERR_DRA_MARKER_TYPE = 0x3502,        //不支持的Marker类型

    ZV_ERR_FILTER_START = 0x3600,           //滤波FT
    ZV_ERR_FT_SIZE = ZV_ERR_FILTER_START,   //滤波器尺寸超出
    ZV_ERR_FT_ANCHOR = 0x3601,              //滤波器偏移错误
    ZV_ERR_FT_STRUCT = 0x3602,              //滤波器结构错误
    
    ZV_ERR_MP_START = 0x3700,               //形态学MP
    ZV_ERR_MP_TYPE = ZV_ERR_MP_START,       //错误的形态学类型
    ZV_ERR_MP_SHAPE = 0x3701,               //错误的结构元素形状
   
    ZV_ERR_SEG_START = 0x3780,              //分割 S

    ZV_ERR_MC_START = 0x3900,               //匹配MC
    ZV_ERR_MC_METHOD = ZV_ERR_MC_START,     //匹配算法不支持

    ZV_ERR_MR_START = 0x3A00,               //3A00   测量MR
    ZV_ERR_MR_MR_UNMATCH = ZV_ERR_MR_START, //测量区域与测量功能不匹配
    ZV_ERR_MR_INVALID = 0x3A01,             //测量区域无效
    ZV_ERR_MR_PTS_NUM = 0x3A02,             //测量拟合点数量不足
    ZV_ERR_MR_PT_OUTER_X = 0x3A03,          //拟合点X坐标超出图像范围
    ZV_ERR_MR_PT_OUTER_Y = 0x3A04,          //拟合点Y坐标超出图像范围
    ZV_ERR_MR_CIRCLE = 0x3A10,
    ZV_ERR_MR_LINE = 0x3A11,

    ZV_ERR_FEAT_START = 0x3A80,             //特征
    ZV_ERR_FEAT_TYPE = ZV_ERR_FEAT_START,   //特征类型错误
    ZV_ERR_FEAT_CALC,                       //特征值计算出错
    ZV_ERR_FEAT_MOMENT_ORDER,               //矩阶数错误
    ZV_ERR_FEAT_MOMENT_TYPE,                //矩类型错误

    ZV_ERR_TK_START = 0x3B00,               //3B00 tools
    ZV_ERR_TK_FIT_PTS_NUM = ZV_ERR_TK_START,
    ZV_ERR_TK_INTERP2D_VAL = 0x3B01,            //插值结果出错
    ZV_ERR_TK_LINE_PT,
    ZV_ERR_TK_TRANS_MAT,

    ZV_ST_MAX = 0xFFFF,
}ZvStatus;

#endif
