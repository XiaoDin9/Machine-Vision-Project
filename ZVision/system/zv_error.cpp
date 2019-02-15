#include "zv_private.h"
#include "zv_error.h"
#include "zv_system.h"


ZV_EXPORTS int g_zv_errStatus = ZV_ST_OK;
int g_zv_errError = ZV_ST_OK;
ZV_EXPORTS int g_zv_errLastError = ZV_ST_OK;

static char s_zv_err_statusMsg[ZV_ERR_MSG_BUF_LEN] = { 0 };
char g_zv_errErrorMsg[ZV_ERR_MSG_BUF_LEN] = { 0 };
ZV_EXPORTS char g_zv_errLastErrorMsg[ZV_ERR_MSG_BUF_LEN] = { 0 };

char *zv_err_statusStr(int status)
{
    switch (status)
    {
    case ZV_ST_OK:                  return "正常";
    case ZV_WARN_RELE_NULL:         return "警告类型，释放空指针";
    case ZV_WARN_RELE_NONE:         return "释放空类型";
    case ZV_WARN_RELE_UNINIT:       return "释放未初始化的结构";
    case ZV_WARN_FILE_NOT_EXIST:    return "文件不存在";
    case ZV_WARN_NODE_NOT_EXIST:    return "节点不存在";

    case ZV_ERR_G_UNDEF:            return "未定义错误";
    case ZV_ERR_G_CPP_EXCEP:        return "C++异常";
    case ZV_ERR_G_ASSERT:           return "断言错误";
    case ZV_ERR_G_NULL_PTR:         return "空指针";
    case ZV_ERR_G_STD_EXCEP:        return "std库异常";
    case ZV_ERR_G_LIB_EXCEP:        return "未知的第三方库异常";
    case ZV_ERR_G_LIB_RUN:          return "未知的第三方库错误状态";
    case ZV_ERR_G_DIV_ZERO:         return "除零错误";
    case ZV_ERR_G_VEC_SIZE:         return "vector长度错误";
    case ZV_ERR_G_BUF_SMALL:        return "输出TABLE长度不足";
    case ZV_ERR_G_OBJ_NOT_EXIST:    return "目标不存在";
    case ZV_ERR_G_LIB_ASSERT:       return "未知的第三方库断言失败";
    case ZV_ERR_G_UNFINISHED:       return "未完成的功能";
    case ZV_ERR_G_NOT_SUPPORT:      return "不支持的功能";
    case ZV_ERR_G_NSP_CL:           return "不支持的OPENCL应用";
    case ZV_ERR_G_NSP_GL:           return "不支持的OPENGL应用";
    case ZV_ERR_G_NSP_CUDA:         return "不支持的CUDA应用";

    case ZV_ERR_T_PARAM_SIZE:       return "任务参数缓冲区不足";
    case ZV_ERR_T_THREAD_ID:        return "任务线程ID超出范围";

    case ZV_ERR_MEM_ALLOC:          return "内存分配失败";
    case ZV_ERR_MEM_CORRUPTED:      return "分配的内存被破坏";

    case ZV_ERR_F_NOT_EXIST:        return "文件不存在";
    case ZV_ERR_F_OPEN_FAIL:        return "文件打开出错";
    case ZV_ERR_F_SAVE_FAIL:        return "文件保存出错";
    case ZV_ERR_F_FORMAT:           return "文件格式出错";

    case ZV_ERR_CAM_GRAB:           return "采集出错";
    case ZV_ERR_CAM_GRAB_TIMEOUT:   return "采集超时";
    case ZV_ERR_CAM_SCANID:         return "相机扫描索引超出范围";
    case ZV_ERR_CAM_CAMID:          return "相机索引超出范围";
    case ZV_ERR_CAM_UNBOUND:        return "未绑定的相机";
    case ZV_ERR_CAM_OPEN:           return "设备打开出错";
    case ZV_ERR_CAM_SCAN:           return "相机扫描出错";
    case ZV_ERR_CAM_NONE:           return "未发现相机";
    case ZV_ERR_CAM_UNKNOWN:        return "相机状态未知";
    case ZV_ERR_CAM_PARAM_UNDEF:    return "相机参数配置不支持";
    case ZV_ERR_CAM_PARAM_RD:       return "相机读取参数出错";
    case ZV_ERR_CAM_PARAM_WR :      return "相机写入参数出错";
    case ZV_ERR_CAM_INIT_TIS:       return "初始化TIS驱动失败";

    case ZV_ERR_FA_TYPE:            return "参数类型错误";
    case ZV_ERR_FA_TYPE_1:          return "参数1类型错误";
    case ZV_ERR_FA_TYPE_2:          return "参数2类型错误";
    case ZV_ERR_FA_TYPE_3:          return "参数3类型错误";
    case ZV_ERR_FA_RANGE:           return "参数超出范围";
    case ZV_ERR_FA_RANGE_1:         return "参数1超出范围";
    case ZV_ERR_FA_RANGE_2:         return "参数2超出范围";
    case ZV_ERR_FA_RANGE_3:         return "参数3超出范围";
    case ZV_ERR_FA_RANGE_4:         return "参数4超出范围";
    case ZV_ERR_FA_RANGE_5:         return "参数5超出范围";
    case ZV_ERR_FA_RANGE_6:         return "参数6超出范围";
    case ZV_ERR_FA_RANGE_7:         return "参数7超出范围";
    case ZV_ERR_FA_RANGE_8:         return "参数8超出范围";
    case ZV_ERR_FA_RANGE_9:         return "参数9超出范围";
    case ZV_ERR_FA_RANGE_10:        return "参数10超出范围";
    case ZV_ERR_FA_NULL:            return "参数为空";
    case ZV_ERR_FA_NULL_1:          return "参数1为空";
    case ZV_ERR_FA_NULL_2:          return "参数2为空";
    case ZV_ERR_FA_NULL_3:          return "参数3为空";
    case ZV_ERR_FA_NULL_4:          return "参数4为空";
    case ZV_ERR_FA_NULL_5:          return "参数5为空";
    case ZV_ERR_FA_NULL_6:          return "参数6为空";
    case ZV_ERR_FA_NULL_7:          return "参数7为空";
    case ZV_ERR_FA_NULL_8:          return "参数8为空";

    case ZV_ERR_M_SIZE:             return "尺寸不符合要求";
    case ZV_ERR_M_SIZE_INVALID:     return "尺寸无效";
    case ZV_ERR_M_OVER_SIZE:        return "尺寸超出范围";
    case ZV_ERR_M_EMPTY:            return "数据为空";
    case ZV_ERR_M_DATA_FORMAT:      return "不支持的数据格式";
    case ZV_ERR_M_DIM:              return "维度超出范围";
    case ZV_ERR_M_ROI:              return "ROI尺寸错误";
    case ZV_ERR_M_SIZE_UNMATCH:     return "输入输出尺寸不匹配";
    case ZV_ERR_M_TYPE_UNMATCH:     return "图像数据类型不匹配";

    case ZV_ERR_I_ONLY_8UC1:        return "图像格式错误，仅支持8位单通道";
    case ZV_ERR_I_DEPTH:            return "不支持或未定义的数据类型";
    case ZV_ERR_I_CN:               return "图像通道数错误";
    case ZV_ERR_I_CN_UNMATCH:       return "通道数量不匹配";
    case ZV_ERR_I_CN_SRC:           return "源图像通道数错误";
    case ZV_ERR_I_CN_DST:           return "目标图像通道数错误";
    case ZV_ERR_I_ONLY_CN1:         return "仅支持单通道图像";
    case ZV_ERR_I_ALIGN:            return "需要对齐的图像数据";
            
    case ZV_ERR_MAT_MUL_SIZE:       return "矩阵乘尺寸不匹配";
    case ZV_ERR_MAT_NOT_SQUARE:     return "矩阵不是方阵";

    case ZV_ERR_DRA_COLOR_NAME:     return "不支持的颜色名字:";
    case ZV_ERR_DRA_COLOR_RANGE:    return "颜色值超出范围";
    case ZV_ERR_DRA_MARKER_TYPE:    return "不支持的Marker类型";

    case ZV_ERR_FT_SIZE:            return "滤波器尺寸超出";
    case ZV_ERR_FT_ANCHOR:          return "滤波器偏移错误";
    case ZV_ERR_FT_STRUCT:          return "滤波器结构错误";
    case ZV_ERR_MP_TYPE:            return "错误的形态学类型";
    case ZV_ERR_MP_SHAPE:           return "错误的结构元素形状";

    case ZV_ERR_MC_METHOD:          return "未定义的匹配算法";

    case ZV_ERR_MR_MR_UNMATCH:      return "测量区域与测量功能不匹配";
    case ZV_ERR_MR_INVALID:         return "测量区域无效";
    case ZV_ERR_MR_PTS_NUM:         return "测量拟合点数量不足";
    case ZV_ERR_MR_PT_OUTER_X:      return "拟合点X坐标超出图像范围";
    case ZV_ERR_MR_PT_OUTER_Y:      return "拟合点Y坐标超出图像范围";
    case ZV_ERR_MR_CIRCLE:          return "测量圆出错";
    case ZV_ERR_MR_LINE:            return "测量直线出错";

    case ZV_ERR_FEAT_TYPE:          return "特征类型错误";
    case ZV_ERR_FEAT_CALC:          return "特征值计算出错";
    case ZV_ERR_FEAT_MOMENT_ORDER:  return "矩阶数错误";
    case ZV_ERR_FEAT_MOMENT_TYPE:   return "矩类型错误";

    case ZV_ERR_TK_FIT_PTS_NUM:     return "拟合点数量不足";
    case ZV_ERR_TK_INTERP2D_VAL:    return "插值结果出错";
    case ZV_ERR_TK_LINE_PT:         return "直线两点重合";
    case ZV_ERR_TK_TRANS_MAT:       return "变换矩阵错误";
    }
    static char buf[32];
    snprintf(buf, sizeof(buf), "未知的%s码：[0x%X]", status >= ZV_ERR_START ? "错误" : "状态", status);
    return buf;
}

int zv_err_statusStrToFile(char *fileName)
{
    //打开文件
    for (int i = 0; i < ZV_ST_MAX; i++)
    {
        char * str = zv_err_statusStr(i);
        //if ()
    }
    return ZV_ST_OK;
}

void zv_err_checkStatus(int status, char * file, char *func, int line, char *format, ...)
{
    if (ZV_ERR_START >= status)
    {
        return;
    }

    char * stStr = zv_err_statusStr(status);
    g_zv_errLastError = status;
    //20180702 10:24:36.145211 错误[0x2100]：文件不存在（附加消息）
    //位置[0478]:zv_module.cpp/zv_fileReadImage
    string dt = zv_sys_dateTimeString(true);
    int msgIdx = snprintf(g_zv_errLastErrorMsg, sizeof(g_zv_errLastErrorMsg), "%s 错误[0x%04X]：%s", dt.c_str(), status, stStr);
    if (format && (format[0] != 0))
    {
        va_list args;
        msgIdx += snprintf(&g_zv_errLastErrorMsg[msgIdx], sizeof(g_zv_errLastErrorMsg) - msgIdx, "（");
        va_start(args, format);
        msgIdx += vsnprintf(&g_zv_errLastErrorMsg[msgIdx], sizeof(g_zv_errLastErrorMsg)-msgIdx, format, args);
        va_end(args);
        msgIdx += snprintf(&g_zv_errLastErrorMsg[msgIdx], sizeof(g_zv_errLastErrorMsg) - msgIdx,"） ");
    }

#ifdef ZV_TRACE_FUNC_NAME
    if (string(func).size() > 0)
    {
        msgIdx += snprintf(&g_zv_errLastErrorMsg[msgIdx], sizeof(g_zv_errLastErrorMsg) - msgIdx,
            "函数：%s，", func);
    }
#endif
    msgIdx += snprintf(&g_zv_errLastErrorMsg[msgIdx], sizeof(g_zv_errLastErrorMsg) - msgIdx,
        "位置[%04d]：%s\n", line, file);

    if (ZV_ST_OK == g_zv_errError)
    {
        g_zv_errError = status;
        memcpy(g_zv_errErrorMsg, g_zv_errLastErrorMsg, sizeof(g_zv_errErrorMsg));
    }
}