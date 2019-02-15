# -*- coding: utf-8 -*-
"""
Created on Tue Jul  3 20:07:49 2018

@author: Administrator
"""

file_name = 'include\zv_module.h'

#输出到文件
module_file = 'zv_module.cpp'
task_cpp_file = 'system/zv_task.cpp'
task_h_file = 'system/zv_task.h'
task_param_h_file = 'system/zv_task_param.h'

"""
使用正则表达式的分组捕获功能，匹配并拆分指定类型接口函数，拆分结果如下：
分类前缀，返回值，模块，函数首字母，函数其余字符，参数列表
('ZV_TASK', 'void', 'cam', 'G', 'etInfo', 'int scanId, char *name, char *value, int maxValLen')
"""
re_func_type = 'ZV_TASK|ZV_CALL|ZV_INCMPL'
re_func_rst_type = 'void|double|int64|int|bool|ZvContour'
pat_src = '(%s) ZV_EXPORTS (%s) zv_([a-z]+)([A-Z])([a-zA-Z0-9]*)\(([^\)]*)\)' % (re_func_type, re_func_rst_type)
pat_unfold_str = '\s*ZV_UNFOLD\((\d+)\)\s*'
pat_cpp_def_str = ' ZV_CPP_DEF\([^\)]*\)'

# 所有字符串都进行了格式调整，包括空格和空行，请勿随意更改

# demo 函数原型示例
incmpl_fun_demo = """
int zv_sysGetParamInt(char *name)
{
    int value = 0;
    ZV_ERR_RUN_MSG(zv_sys_getParamInt(TODO), "Param:%s", name);
    return value;
}
"""

call_fun_demo = """
int zv_camCount() #返回值
{
    return zv_cam_count();
}
void zv_sysSetParamInt(char *name, int value)  #无返回值
{
    ZV_ERR_RUN(zv_sys_setParamInt(name, value));
}
"""

param_struct_demo = """
typedef struct 
{
    int scanId;
    char *name;
    char *value;
    int maxValLen;
}ZvTPCamGetInfo;
"""

func_basic_demo = """
int zv_camGetInfo(int scanId, char *name, char *value, int maxValLen)
{
    ZvTPCamGetInfo param = { scanId, name, value, maxValLen };
    return zv_mod_registerRun(zv_task_cam_getInfo, &param, sizeof(param));
}
"""

func_task_demo = """
void zv_task_cam_getInfo(void *param)
{
    ZvTPCamGetInfo * p = (ZvTPCamGetInfo *)param;
    ZV_ERR_RUN(zv_cam_getInfo(p->scanId, p->name, p->value, p->maxValLen));
}
void zv_task_cam_status(void *param)
{
    ZvTPCamStatus *p = (ZvTPCamStatus *)param;
    *p->status = zv_cam_status(p->camId);
}
"""




#模块注释
mod_comment_dict = {
        'sys'  : '''\n//sys system：参数、时间、日志、调试
char *zv_errStatusStr(int status)
{
    return zv_err_statusStr(status);
}

''',
        'cam'  : '\n//cam\n',
        'file' : '\n//file\n',
        'img'  : '\n//img    core/zv_image.cpp\n',
        'mat'  : '\n//mat    core/zv_matrix.cpp\n',
        'cont' : '\n//cont   core/zv_contour.cpp\n',
        'arith': '''
//arith  basic/   zv_arithmetic.cpp    zv_stat.cpp'
//zv_arithmetic.cpp  代数（矩阵图像的四则运算、逆矩阵、逐点函数运算、逻辑、比较、矩阵运算、LUT）
//zv_stat.cpp  统计（直方图、均值方差、）
''',
        'ip'   :'''
//ip imgproc 图像处理模块 basic/ zv_geometric_trans.cpp filter.cpp zv_morph.cpp zv_segment.cpp zv_color.cpp
//zv_geometric_trans.cpp  几何（旋转、缩放、畸变矫正、仿射透视变换）
//zv_color.cpp 颜色（Bayer、HSV）、其它（颜色映射)
//filter.cpp 滤波（高斯、中值、均值、边缘、自定义、FFT、DCT）
//zv_morph.cpp 形态学（腐蚀、膨胀、开、闭）
//zv_segment.cpp 分割（二值、分类分割、区域增长、边缘分割）
''',
    'match' : '''
//match    match
//match：灰度、形状、几何特征、点、3D
''',
    'meas' : '''
//meas    measure
//measure：圆、直线、椭圆、矩形、点、间距
''',
    'feat' :'''
//feat  feature
//feature：角点、霍夫、边缘
''',
    'tk' :'''
//tk    tools
//tools：几何变换、几何特征、交点、夹角、拟合、插值
''',
    'dra'  : '\n//dra模块，绘制图形和文字\n'}


file_comment = """/*************************************************************
该文件为自动生成文件，如果修改请注意备份，重新生成将被覆盖
////由zv_module_gen.py生成，需要zv_module_templ.py模块内的
////固定字符串定义和zv_module.h文件内的函数声明，声明需要符
////合特定格式
*************************************************************/
"""

include_and_frame = """
#include "zv_private.h"
#include "zv_module.h"
#include "system/zv_task_param.h"
#include "system/zv_task.h"
#include "system/zv_system.h"
#include "core/zv_core.h"
#include "basis/zv_basis.h"
#include "camera/zv_camera.h"
#include "file/zv_file.h"
#include "match/zv_match.h"
#include "measure/zv_meas.h"
#include "feature/zv_feature.h"
#include "tools/zv_tools.h"
#include "graphics/zv_graphics.h"


ZvImage zv_modImgCreate()
{
    return new _ZvImage();
}

ZvImage zv_modImgCreateData(int width, int height, int depth, int cn, void *data)
{
    return new _ZvImage(height, width, CV_MAKE_TYPE(depth, cn), data);
}

ZvImage zv_modImgCreateConst(int width, int height, int depth, int cn, double value)
{
    return new _ZvImage(height, width, CV_MAKE_TYPE(depth, cn), value);
}

int zv_modImgRelease(ZvImage * img)
{
    ZV_CHK_NULL1(img);
    if (NULL != *img)
    {
        delete *img;
        *img = NULL;
    }
    return ZV_ST_OK;
}

ZvMatrix zv_modMatCreate()
{
    return new _ZvMatrix();
}

ZvMatrix zv_modMatCreateData(int width, int height, void *data)
{
    return new _ZvMatrix(height, width, CV_64F, data);
}

ZvMatrix zv_modMatCreateConst(int width, int height, double value)
{
    return new _ZvMatrix(height, width, CV_64F, value);
}

int zv_modMatRelease(ZvMatrix * mat)
{
    ZV_CHK_NULL1(mat);
    if (NULL != *mat)
    {
        delete *mat;
        *mat = NULL;
    }
    return ZV_ST_OK;
}

ZvContList zv_modContListCreate()
{
    return new _ZvContList();
}

int zv_modContListRelease(ZvContList * contList)
{
    ZV_CHK_NULL1(contList);
    if (NULL != *contList)
    {
        delete *contList;
        *contList = NULL;
    }
    return ZV_ST_OK;
}

ZvContour zv_modContCreate()
{
    return new _ZvContour();
}

int zv_modContRelease(ZvContour * contour)
{
    ZV_CHK_NULL1(contour);
    if (NULL != *contour)
    {
        delete *contour;
        *contour = NULL;
    }
    return ZV_ST_OK;
}

"""


mod_function = """
int zv_modInit(bool isBlocking)
{
    cv::setBreakOnError(false);
    cv::redirectError((cv::ErrorCallback)zv_adp_cvErrorCallback);
    ZV_RUN_RTN(zv_task_init(isBlocking));
    ZV_RUN_RTN(zv_cam_init());
    return ZV_ST_OK;
}

int zv_modExit()
{
    ZV_RUN_RTN(zv_cam_exit());
    return ZV_ST_OK;
}
"""

task_param_file_head = """
#ifndef ZV_TASK_PARAM_H
#define ZV_TASK_PARAM_H

#ifdef __cplusplus
extern "C"
{
#endif


"""

task_param_file_tail = """
#ifdef __cplusplus
}
#endif

#endif
"""

task_cpp_file_head = """
#include "zv_private.h"
#include "zv_task_param.h"
#include "zv_task.h"
#include "system/zv_system.h"
#include "core/zv_core.h"
#include "basis/zv_basis.h"
#include "camera/zv_camera.h"
#include "file/zv_file.h"
#include "match/zv_match.h"
#include "measure/zv_meas.h"
#include "feature/zv_feature.h"
#include "tools/zv_tools.h"
#include "graphics/zv_graphics.h"


typedef struct _ZvTaskData
{
    ZvTaskFun fun;
    unsigned char paramBuf[8 * sizeof(double)];
}ZvTaskData;

static ZvTaskData s_zv_task_taskData[ZV_SYS_THREAD_MAX] = { 0 };
bool s_zv_task_isBlocking = false;


int zv_task_init(bool isBlocking)
{
    s_zv_task_isBlocking = isBlocking;
    return ZV_ST_OK;
}

int zv_task_registerRun(ZvTaskFun fun, void *param, int paramSize)
{
    int id = 0;

    if (paramSize > sizeof(s_zv_task_taskData[0].paramBuf))
    {
        return ZV_ERR_T_PARAM_SIZE;
    }

    memset(s_zv_task_taskData[id].paramBuf, 0, sizeof(s_zv_task_taskData[id].paramBuf));
    memcpy(s_zv_task_taskData[id].paramBuf, param, paramSize);
    s_zv_task_taskData[id].fun = fun;
    if (s_zv_task_isBlocking)
    {
        s_zv_task_taskData[id].fun(s_zv_task_taskData[id].paramBuf);
    }

    return ZV_ST_OK;
}

void zv_task_threadRun()
{
    int id = 0; // 获取线程ID
    if (NULL != s_zv_task_taskData[id].fun && false == s_zv_task_isBlocking)
    {
        s_zv_task_taskData[id].fun(s_zv_task_taskData[id].paramBuf);
    }
    else
    {
        zv_sys_sleep(1);
    }
    s_zv_task_taskData[id].fun = NULL;
}

"""

task_h_file_head = """
#ifndef ZV_TASK_H
#define ZV_TASK_H

#ifdef __cplusplus
extern "C"
{
#endif


typedef void(*ZvTaskFun)(void *);

int zv_task_init(bool isBlocking);
int zv_task_registerRun(ZvTaskFun fun, void *param, int paramSize);

"""

task_h_file_tail = """
#ifdef __cplusplus
}
#endif

#endif
"""
