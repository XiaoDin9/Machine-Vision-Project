#ifndef ZV_MODULE_H
#define ZV_MODULE_H

//宏定义 - 接口函数分类标记，用于自动代码生成
//代码基本固定后，可以删除
#define ZV_TASK         //位于声明前部，复杂指令，通过任务线程执行，返回void
#define ZV_CALL         //位于声明前部，简单指令，直接调用内部函数（一般为inline）
#define ZV_INCMPL       //位于声明前部，简单指令，输出参数转返回值，默认输出参数位于最后，否则需人工修改
#define ZV_TRAN_OUT     //用于复杂指令，返回值转输出参数的标记，内部函数返回值通过此输出参数导出
#define ZV_UNFOLD(num)  //定义指针参数展开，int *p -->&p[0], &p[1], &p[2]



#ifdef __cplusplus
extern "C"
{
#endif


//mod模块，库管理接口，解释器调用，仅运行在阻塞模式下
ZV_INTERPRETER ZV_EXPORTS int zv_modInit(bool isBlocking);
ZV_INTERPRETER ZV_EXPORTS int zv_modExit();

/*************************************************************
Description:    //创建图像结构体并初始化内存区域 和 释放图像的内存
Input:          //info 创建图像参数，可传入NULL创建空图像
Output:         //无
Return:         //创建的图像，释放图像后是否成功
*************************************************************/
ZV_INTERPRETER ZV_EXPORTS ZvImage zv_modImgCreate();

/*************************************************************
Description:    //创建图像结构体头并关联外部数据区
Input:          //width  宽度 - 列数
Input:          //height 高度 - 行数
Input:          //depth  数据类型
Input:          //cn     通道数
Input:          //data   数据区，要求图像生存期内可用，释放图像时不释放该数据区内存
Output:         //无
Return:         //创建的图像指针
*************************************************************/
ZV_INTERPRETER ZV_EXPORTS ZvImage zv_modImgCreateData(int width, int height, int depth, int cn, void *data);

/*************************************************************
Description:    //创建图像结构体并初始化数据区域
Input:          //width  宽度 - 列数
Input:          //height 高度 - 行数
Input:          //depth  数据类型
Input:          //cn     通道数
Input:          //value  数据区的初始化值
Output:         //无
Return:         //创建的图像指针
*************************************************************/
ZV_INTERPRETER ZV_EXPORTS ZvImage zv_modImgCreateConst(int width, int height, int depth, int cn, double value);

/*************************************************************
Description:    //释放图像内存
Input:          //img 待释放的图像指针的地址
Output:         //无
Return:         //错误码
*************************************************************/
ZV_INTERPRETER ZV_EXPORTS int zv_modImgRelease(ZvImage * img);

/*************************************************************
Description:    //创建图像Matrix矩阵并初始化内存区域 和 释放图像的内存
Input:          //img 待释放的图像指针
Output:         //无
Return:         //创建的矩阵，释放矩阵
*************************************************************/
ZV_EXPORTS ZvMatrix zv_modMatCreate();
ZV_EXPORTS ZvMatrix zv_modMatCreateData(int width, int height, void *data);
ZV_EXPORTS ZvMatrix zv_modMatCreateConst(int width, int height, double value ZV_CPP_DEF(0));
ZV_EXPORTS int zv_modMatRelease(ZvMatrix * img);
ZV_EXPORTS ZvContList zv_modContListCreate();
ZV_EXPORTS int zv_modContListRelease(ZvContList * contList);
ZV_EXPORTS ZvContour zv_modContCreate();
ZV_EXPORTS int zv_modContRelease(ZvContour * contour);


ZV_INTERPRETER ZV_EXPORTS ZvModel zv_templCreate(double angleStart, double angleExt, double angleStep);

//sys
#ifndef ZV_BUILD_DLL
extern ZV_IMPORTS int g_zv_sysIsDrawFill;   //是否填充绘图
extern ZV_IMPORTS int g_zv_sysLineWidth;    //线宽
extern ZV_IMPORTS int g_zv_sysLineType;
#endif
/*************************************************************
Description:    //获取整数类型的参数值
Input:          //name 参数名字
Output:         //无
Return:         //参数值
*************************************************************/
ZV_INCMPL ZV_EXPORTS int zv_sysGetParamInt(char *name);
ZV_CALL ZV_EXPORTS void zv_sysSetParamInt(char *name, int value);
ZV_INCMPL ZV_EXPORTS double zv_sysGetParamDouble(char *name);
ZV_CALL ZV_EXPORTS void zv_sysSetParamDouble(char *name, double value);

/*************************************************************
Description:    //获取字符串类型的参数值
Input:          //name 参数名字
Input:          //maxValLen value数组长度
Output:         //value 参数值
Return:         //无
*************************************************************/
ZV_CALL ZV_EXPORTS void zv_sysGetParamString(char *name, char *value, int maxValLen);
ZV_CALL ZV_EXPORTS void zv_sysSetParamString(char *name, char *value);

/*************************************************************
Description:    //获取微秒单位的时刻值
Input:          //无
Output:         //无
Return:         //时刻值，单位us
*************************************************************/
ZV_CALL ZV_EXPORTS double zv_sysGetTimeUs();
ZV_CALL ZV_EXPORTS double zv_sysGetTimeMs();
ZV_CALL ZV_EXPORTS int64 zv_sysGetTickCount();
ZV_CALL ZV_EXPORTS double zv_sysGetTickFreq();


//err
#ifndef ZV_BUILD_DLL
extern ZV_IMPORTS int g_zv_errStatus;
extern ZV_IMPORTS int g_zv_errLastError;
extern ZV_IMPORTS char g_zv_errLastErrorMsg[];
#endif
ZV_EXPORTS char *zv_errStatusStr(int status);


//cam模块
ZV_TASK ZV_EXPORTS int zv_camScan(char *type);
ZV_CALL ZV_EXPORTS int zv_camCount();
ZV_TASK ZV_EXPORTS int zv_camGetInfo(int scanId, int prop, char *value, int maxValLen);
ZV_TASK ZV_EXPORTS int zv_camOpen(int camId, int scanId);
ZV_TASK ZV_EXPORTS int zv_camStatus(int camId, ZV_TRAN_OUT int *status);
ZV_TASK ZV_EXPORTS int zv_camClose(int camId);
ZV_TASK ZV_EXPORTS int zv_camPayloadSize(int camId, ZV_TRAN_OUT int *size);
ZV_TASK ZV_EXPORTS int zv_camGrab(ZvImage img, int camId);
ZV_CALL ZV_EXPORTS int zv_camGetIO(int camId);
ZV_CALL ZV_EXPORTS void zv_camSetIO(int camId, int offset);
ZV_TASK ZV_EXPORTS int zv_camGetROI(int camId, ZV_UNFOLD(4) int *camROI);
ZV_TASK ZV_EXPORTS int zv_camSetROI(int camId, int x, int y, int width, int height);
ZV_TASK ZV_EXPORTS int zv_camGetExposure(int camId, ZV_TRAN_OUT double *time);
ZV_TASK ZV_EXPORTS int zv_camSetExposure(int camId, double time);
ZV_TASK ZV_EXPORTS int zv_camStartGrabbing(int camId, int bufCount);
ZV_TASK ZV_EXPORTS int zv_camIsGrabbing(int camId, int *isGrabbing);
ZV_TASK ZV_EXPORTS int zv_camRetrieve(ZvImage img, int camId, int bufId);
ZV_TASK ZV_EXPORTS int zv_camReset(int camId);
ZV_TASK ZV_EXPORTS int zv_camGetParam(int camId, char *name, char *value, int maxValLen);
ZV_TASK ZV_EXPORTS int zv_camSetParam(int camId, char *name, char *value);


//file 
ZV_TASK ZV_EXPORTS int zv_fileReadImage(ZvImage img, char *fileName, int type ZV_CPP_DEF(0));

/*************************************************************
Description:    //保存图像到文件
Input:          //img 待保存的图像
Input:          //fileName 保存的文件名
Input:          //param 图像质量，越大则图像质量越高，压缩程度越低
Output:         //无
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_fileWriteImage(ZvImage img, char *fileName, int param);
ZV_TASK ZV_EXPORTS int zv_fileReadMatrix(ZvMatrix mat, char *fileName, char *nodeName, int type ZV_CPP_DEF(0));
ZV_TASK ZV_EXPORTS int zv_fileWriteMatrix(ZvMatrix mat, char *fileName, char *nodeName, int type ZV_CPP_DEF(0));


//core模块 - img 图像

/*************************************************************
Description:    //获取图像的宽度
Input:          //img 图像
Output:         //无
Return:         //图像宽度
*************************************************************/
ZV_CALL ZV_EXPORTS int zv_imgWidth(ZvImage img);

/*************************************************************
Description:    //获取图像的高度
Input:          //img 图像
Output:         //无
Return:         //图像高度
*************************************************************/
ZV_CALL ZV_EXPORTS int zv_imgHeight(ZvImage img);

/*************************************************************
Description:    //获取图像的通道数
Input:          //img 图像
Output:         //无
Return:         //图像通道数量
*************************************************************/
ZV_CALL ZV_EXPORTS int zv_imgChannels(ZvImage img);

/*************************************************************
Description:    //获取图像的数据类型
Input:          //img 图像
Output:         //无
Return:         //数据类型0-8U,1-16U,2-32S,3-64F,-1-未定义
*************************************************************/
ZV_CALL ZV_EXPORTS int zv_imgDataType(ZvImage img);

/*************************************************************
Description:    //获取图像的单个数据的字节大小
Input:          //img 图像
Output:         //无
Return:         //图像单个数据的大小
*************************************************************/
ZV_CALL ZV_EXPORTS int zv_imgValueSize(ZvImage img);

/*************************************************************
Description:    //获取图像的数据区字节大小
Input:          //img 图像
Output:         //无
Return:         //图像数据区大小
*************************************************************/
ZV_CALL ZV_EXPORTS int zv_imgDataSize(ZvImage img);

/*************************************************************
Description:    //判断图像是否为空
Input:          //img 图像
Output:         //无
Return:         //true-为空，false-非空
*************************************************************/
ZV_CALL ZV_EXPORTS int zv_imgIsEmpty(ZvImage img);

/*************************************************************
Description:    //使用常数生成图像
Input:          //img 图像
                //width 图像宽度
                //height 图像高度
                //type 数据类型
                //channel 通道数
                //element 各通道对应常量 如果为空，则取常数0
Output:         //无
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_imgGenConst(ZvImage img, int width, int height, int type,
    int channel, double *element);


/*************************************************************
Description:    //使用已有的数据区生成图像
Input:          //img 图像
                //width 图像宽度
                //height 图像高度
                //type 数据类型
                //channel 通道数
                //data 数据区，格式需与图像参数匹配，
                //     内存区域不受图像管理需在图像生命周期内有效，
Output:         //无
Return:         //任务状态码
*************************************************************/	
ZV_TASK ZV_EXPORTS int zv_imgGenData(ZvImage img, int width, int height, int type,
    int channel, void *data);
ZV_CALL ZV_EXPORTS double zv_imgGetValue(ZvImage img, int x, int y, int channel);
ZV_CALL ZV_EXPORTS void zv_imgSetValue(ZvImage img, int x, int y, int channel, double value);
ZV_CALL ZV_EXPORTS void zv_imgGetElement(ZvImage img, int x, int y, double *element);
ZV_CALL ZV_EXPORTS void zv_imgSetElement(ZvImage img, int x, int y, double *element);
ZV_TASK ZV_EXPORTS int zv_imgGetData(ZvImage img, void *buf, int size, bool isAlign);
ZV_TASK ZV_EXPORTS int zv_imgSetData(ZvImage img, void *buf);
ZV_TASK ZV_EXPORTS int zv_imgGetSub(ZvImage img, ZvImage sub, int x, int y, int width, int height);
ZV_TASK ZV_EXPORTS int zv_imgSetSub(ZvImage img, ZvImage sub, int x, int y);
ZV_TASK ZV_EXPORTS int zv_imgConvert(ZvImage src, ZvImage dst, int dstType, double mult, double add);
ZV_TASK ZV_EXPORTS int zv_imgCopy(ZvImage src, ZvImage dst);
ZV_TASK ZV_EXPORTS int zv_imgSplit2(ZvImage src, ZvImage dst1, ZvImage dst2);
ZV_TASK ZV_EXPORTS int zv_imgSplit3(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3);
ZV_TASK ZV_EXPORTS int zv_imgSplit4(ZvImage src, ZvImage dst1, ZvImage dst2, ZvImage dst3, ZvImage dst4);
ZV_TASK ZV_EXPORTS int zv_imgMerge2(ZvImage src1, ZvImage src2, ZvImage dst);
ZV_TASK ZV_EXPORTS int zv_imgMerge3(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage dst);
ZV_TASK ZV_EXPORTS int zv_imgMerge4(ZvImage src1, ZvImage src2, ZvImage src3, ZvImage src4, ZvImage dst);


//core模块 - mat 矩阵
ZV_CALL ZV_EXPORTS int zv_matRows(ZvMatrix mat);
ZV_CALL ZV_EXPORTS int zv_matCols(ZvMatrix mat);
ZV_CALL ZV_EXPORTS int zv_matIsEmpty(ZvMatrix mat);
ZV_TASK ZV_EXPORTS int zv_matGenConst(ZvMatrix mat, int rows, int cols, double value);
ZV_TASK ZV_EXPORTS int zv_matGenEye(ZvMatrix mat, int size);
ZV_TASK ZV_EXPORTS int zv_matGenData(ZvMatrix mat, int rows, int cols, double *data);
ZV_CALL ZV_EXPORTS double zv_matGetValue(ZvMatrix mat, int row, int col);
ZV_CALL ZV_EXPORTS void zv_matSetValue(ZvMatrix mat, int row, int col, double value);
ZV_TASK ZV_EXPORTS int zv_matGetRow(ZvMatrix mat, int row, double *data, int bufLen);
ZV_TASK ZV_EXPORTS int zv_matSetRow(ZvMatrix mat, int row, double *data);
ZV_TASK ZV_EXPORTS int zv_matGetCol(ZvMatrix mat, int col, double * data, int bufLen);
ZV_TASK ZV_EXPORTS int zv_matSetCol(ZvMatrix mat, int col, double * data);
ZV_TASK ZV_EXPORTS int zv_matGetData(ZvMatrix mat, double *data, int bufLen);
ZV_TASK ZV_EXPORTS int zv_matSetData(ZvMatrix mat, double *data);
ZV_TASK ZV_EXPORTS int zv_matGetSub(ZvMatrix mat, ZvMatrix sub, int x, int y, int width, int height);
ZV_TASK ZV_EXPORTS int zv_matSetSub(ZvMatrix mat, ZvMatrix sub, int x, int y);
ZV_TASK ZV_EXPORTS int zv_matCopy(ZvMatrix src, ZvMatrix dst);


//core模块 - cont 轮廓
ZV_CALL ZV_EXPORTS int zv_contCount(ZvContList contList);
ZV_CALL ZV_EXPORTS ZvContour zv_contGetContour(ZvContList contList, int id);
ZV_CALL ZV_EXPORTS int zv_contPointCount(ZvContour cont);
ZV_CALL ZV_EXPORTS void zv_contGetPoint(ZvContour cont, int id, ZV_UNFOLD(2) double *pt);
/*************************************************************
Description:    //获取轮廓的所有点坐标
Input:          //cont 轮廓
Input/Output:   //bufLen 输入pts的长度，输出坐标值的数量
Output:         //pts 坐标点x、y依次存放
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_contGetPointsAll(ZvContour cont, double *pts, int *ptsLen);
/*************************************************************
Description:    //生成二值图像的轮廓
Input:          //img 8UC1类型的二值图像
Input:          //mode 提取模式：0-仅提取外轮廓 1-提取所有轮廓
Input:          //appro 是否精简：0-提取轮廓所有点 1-对轮廓点进行近似
Output:         //contList 生成的轮廓列表
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_contGen(ZvImage img, ZvContList contList, int mode, int appro);
ZV_TASK ZV_EXPORTS int zv_contToMatrix(ZvContour cont, ZvMatrix mat);
ZV_TASK ZV_EXPORTS int zv_contFromMatrix(ZvContour cont, ZvMatrix mat);

/*************************************************************
Description:    //计算轮廓面积
Input:          //cont 轮廓点
Input:          //isOriented 是否考虑方向：false-返回面积绝对值 true-返回带符号的面积
Output:         //area 轮廓面积
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_contArea(ZvContour cont, bool isOriented, ZV_TRAN_OUT double *area);
/*************************************************************
Description:    //计算轮廓长度（周长）
Input:          //cont 轮廓点
Input:          //isClosed 轮廓是否闭合
Output:         //len 轮廓长度
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_contLength(ZvContour cont, bool isClosed, ZV_TRAN_OUT double *len);
ZV_TASK ZV_EXPORTS int zv_contCenter(ZvContour cont, ZV_UNFOLD(2) double *center);
ZV_TASK ZV_EXPORTS int zv_contIsConvex(ZvContour cont, ZV_TRAN_OUT int *isConvex);
ZV_TASK ZV_EXPORTS int zv_contConvexity(ZvContour cont, ZV_TRAN_OUT double *convexity);
ZV_TASK ZV_EXPORTS int zv_contCircularity(ZvContour cont, ZV_TRAN_OUT double *value);
ZV_TASK ZV_EXPORTS int zv_contCompactness(ZvContour cont, ZV_TRAN_OUT double *value);
ZV_TASK ZV_EXPORTS int zv_contSmallestRect(ZvContour cont, ZV_UNFOLD(4) int *rect);
ZV_TASK ZV_EXPORTS int zv_contSmallestRect2(ZvContour cont, ZV_UNFOLD(5) double *rect2);
ZV_TASK ZV_EXPORTS int zv_contSmallestCircle(ZvContour cont, ZV_UNFOLD(3) double *circle);
ZV_TASK ZV_EXPORTS int zv_contEllipticAxis(ZvContour cont, double *major, double * minor, double *angle);
ZV_TASK ZV_EXPORTS int zv_contConvexHullIdx(ZvContour cont, int *ptIdx, int *bufLen);
ZV_TASK ZV_EXPORTS int zv_contApproxPoly(ZvContour cont, ZvContour poly, double epsilon, bool isClosed);
ZV_TASK ZV_EXPORTS int zv_contSort(ZvContList contlist, int feature, bool isInc);

ZV_TASK ZV_EXPORTS int zv_contFilter(ZvContList contlist, int feature,
    double min, double max, bool isInvert ZV_CPP_DEF(false));
ZV_TASK ZV_EXPORTS int zv_contMoments(ZvContour cont, int type, int orderX, int orderY, ZV_TRAN_OUT double *m);
ZV_TASK ZV_EXPORTS int zv_contHuMoments(ZvContour cont, double *hu);
ZV_TASK ZV_EXPORTS int zv_contAffine(ZvContour contSrc, ZvContour contDst, ZvMatrix mat);
ZV_TASK ZV_EXPORTS int zv_contPerspective(ZvContour contSrc, ZvContour contDst, ZvMatrix mat);

//basis 模块 - arith 算术运算
ZV_TASK ZV_EXPORTS int zv_arithAbs(ZvObject src, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithAbsDiff(ZvObject src1, ZvObject src2, ZvObject dst, double mult);

/*************************************************************
Description:    //矩阵或图像相加 dst = (src1+src2)*mult+add
Input:          //src1 
Input:          //src2 
Input:          //mult 默认值1
Input:          //add  默认值0
Output:         //dst 类型与src1相同
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithAdd(ZvObject src1, ZvObject src2, ZvObject dst, double mult ZV_CPP_DEF(1), double add ZV_CPP_DEF(0));

/*************************************************************
Description:    //矩阵或图像相减 dst = (src1-src2)*mult+add
Input:          //src1
Input:          //src2
Input:          //mult 默认值1
Input:          //add  默认值0
Output:         //dst 类型与src1相同
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithSub(ZvObject src1, ZvObject src2, ZvObject dst, double mult ZV_CPP_DEF(1), double add ZV_CPP_DEF(0));

/*************************************************************
Description:    //矩阵或图像点乘 dst = (src1.*src2)*mult+add
Input:          //src1
Input:          //src2
Input:          //mult 默认值1
Input:          //add  默认值0
Output:         //dst 类型与src1相同
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithMul(ZvObject src1, ZvObject src2, ZvObject dst, double mult ZV_CPP_DEF(1), double add ZV_CPP_DEF(0));

/*************************************************************
Description:    //矩阵或图像点除 dst = (src1./src2)*mult+add
Input:          //src1
Input:          //src2
Input:          //mult 默认值1
Input:          //add  默认值0
Output:         //dst 类型与src1相同
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithDiv(ZvObject src1, ZvObject src2, ZvObject dst, double mult ZV_CPP_DEF(1), double add ZV_CPP_DEF(0));

/*************************************************************
Description:    //矩阵或图像灰度重映射 dst = src*mult+add
Input:          //src
Input:          //mult 默认值1
Input:          //add  默认值0
Output:         //dst 类型与src相同


Return:         //任务状态码
*************************************************************/




ZV_TASK ZV_EXPORTS int zv_arithScale(ZvObject src, ZvObject dst, double mult, double add);

/*************************************************************
Description:    //矩阵或图像加权和 dst = (src1*weight1+src2*weight2)+add
Input:          //src1
Input:          //src2
Input:          //weight1
Input:          //weight2
Input:          //add  默认值0
Output:         //dst 类型与src1相同
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithAddWeighted(ZvObject src1, ZvObject src2, ZvObject dst,
    double weight1, double weight2, double add);

/*************************************************************
Description:    //矩阵或图像逐元素求正弦值
Input:          //src 64F类型，弧度值
Output:         //dst 类型与src相同
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithSin(ZvObject src, ZvObject dst);

/*************************************************************
Description:    //矩阵或图像逐元素求余弦值
Input:          //src 64F类型，弧度值
Output:         //dst 类型与src相同
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithCos(ZvObject src, ZvObject dst);

/*************************************************************
Description:    //矩阵或图像逐元素求正切值
Input:          //src 64F类型，弧度值
Output:         //dst 类型与src相同
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithTan(ZvObject src, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithAsin(ZvObject src, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithAcos(ZvObject src, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithAtan(ZvObject src, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithAtan2(ZvObject y, ZvObject x, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithExp(ZvObject src, ZvObject dst, int baseType);
ZV_TASK ZV_EXPORTS int zv_arithLog(ZvObject src, ZvObject dst, int baseType);
ZV_TASK ZV_EXPORTS int zv_arithPow(ZvObject src, ZvObject dst, double exponent);
ZV_TASK ZV_EXPORTS int zv_arithSqrt(ZvObject src, ZvObject dst);

/*************************************************************
Description:    //矩阵或单通道图像比较
Input:          //src1
Input:          //src2
Input:          //op 0-相等、1-大于、2-大于等于、3小于、4小于等于、5不等
Output:         //dst 8位单通道图像，255-比较通过，0-未通过
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithCompare(ZvObject src1, ZvObject src2, ZvImage dst, int op);
ZV_TASK ZV_EXPORTS int zv_arithMax(ZvObject src1, ZvObject src2, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithMin(ZvObject src1, ZvObject src2, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithMaxS(ZvObject src1, ZvObject dst, double *scalar);
ZV_TASK ZV_EXPORTS int zv_arithMinS(ZvObject src1, ZvObject dst, double *scalar);
ZV_TASK ZV_EXPORTS int zv_arithMagnitude(ZvObject x, ZvObject y, ZvObject magnitude);
ZV_TASK ZV_EXPORTS int zv_arithPhase(ZvObject x, ZvObject y, ZvObject radian);
ZV_TASK ZV_EXPORTS int zv_arithIntegral(ZvObject src, ZvObject dst);
ZV_TASK ZV_EXPORTS int zv_arithIntegral2(ZvObject src, ZvObject dst, ZvObject dstSqrt);
ZV_TASK ZV_EXPORTS int zv_arithAnd(ZvImage src1, ZvImage src2, ZvImage dst);
ZV_TASK ZV_EXPORTS int zv_arithOr(ZvImage src1, ZvImage src2, ZvImage dst);
ZV_TASK ZV_EXPORTS int zv_arithNot(ZvImage src, ZvImage dst);
ZV_TASK ZV_EXPORTS int zv_arithXor(ZvImage src1, ZvImage src2, ZvImage dst);
ZV_TASK ZV_EXPORTS int zv_arithTranspose(ZvMatrix src, ZvMatrix dst);
ZV_TASK ZV_EXPORTS int zv_arithInvert(ZvMatrix src, ZvMatrix dst, int method);
/*************************************************************
Description:    //计算矩阵的范数
Input:          //mat 输入矩阵
Input:          //normType 范数类型 0 - 无穷范数（最大绝对值）
                //1 - 1范数（绝对值和），2 - 欧式范数
Output:         //value 计算结果
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithNorm(ZvMatrix mat, int normType, ZV_TRAN_OUT double *value);
ZV_TASK ZV_EXPORTS int zv_arithMatrixMult(ZvMatrix mat1, ZvMatrix mat2, ZvMatrix dst);
ZV_TASK ZV_EXPORTS int zv_arithEigen(ZvMatrix src, ZvMatrix eigenvalues,
    ZvMatrix eigenvectors, bool isSymmetric);

ZV_TASK ZV_EXPORTS int zv_arithZeroCount(ZvObject src, ZV_TRAN_OUT int *cnt);
ZV_TASK ZV_EXPORTS int zv_arithSum(ZvObject src, double * sum);

/*************************************************************
Description:    //矩阵或图像的行元素统计：行方向求和、均值、最值
Input:          //src 矩阵或图像
Input:          //type 0-和，1-均值，2-最大值，3-最小值
Output:         //dst type为0、1则类型为64F，为2、3则类型与src相同，大小1xN。
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithStatRow(ZvObject src, ZvObject dst, int type);
/*************************************************************
Description:    //矩阵或图像的列元素统计
Input:          //src 矩阵或图像
Input:          //type 0-和，1-均值，2-最大值，3-最小值
Output:         //dst type为0、1则类型为64F，为2、3则类型与src相同，大小Nx1。
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_arithStatCol(ZvObject src, ZvObject dst, int type);
ZV_TASK ZV_EXPORTS int zv_arithMean(ZvObject src, double *mean);
ZV_TASK ZV_EXPORTS int zv_arithMeanSdev(ZvObject src, double *mean, double *stdDev);
ZV_TASK ZV_EXPORTS int zv_arithMinMaxLoc(ZvObject src, ZV_UNFOLD(2) double *value, ZV_UNFOLD(4) int *pos);
ZV_TASK ZV_EXPORTS int zv_arithHist(ZvImage img, ZvMatrix hist, int size, double low, double upper);
//ZV_TASK ZV_EXPORTS int zv_arithHistRgb(ZvImage img, ZvImage hist);

//ip imgproc
ZV_TASK ZV_EXPORTS int zv_ipMirror(ZvImage src, ZvImage dst, int type);
ZV_TASK ZV_EXPORTS int zv_ipRotate(ZvImage src, ZvImage dst, double angle, int interp);
ZV_TASK ZV_EXPORTS int zv_ipZoom(ZvImage src, ZvImage dst, double scaleW, double scaleH, int interp);
ZV_TASK ZV_EXPORTS int zv_ipResize(ZvImage src, ZvImage dst, int dstW, int dstH, int interp);
ZV_TASK ZV_EXPORTS int zv_ipAffine(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW,
    int dstH, int interp, char *border); 
ZV_TASK ZV_EXPORTS int zv_ipPerspective(ZvImage src, ZvImage dst, ZvMatrix mat, int dstW,
    int dstH, int interp, char *border);
ZV_TASK ZV_EXPORTS int zv_ipMoments(ZvImage binImg, int type, int orderX, int orderY, ZV_TRAN_OUT double *m);

ZV_TASK ZV_EXPORTS int zv_ipRgbToGray(ZvImage rgb, ZvImage gray);
ZV_TASK ZV_EXPORTS int zv_ipGrayToRgb(ZvImage gray, ZvImage rgb);
ZV_TASK ZV_EXPORTS int zv_ipColorToRgb(ZvImage color, ZvImage rgb, int colorSpace);
ZV_TASK ZV_EXPORTS int zv_ipRgbToColor(ZvImage rgb, ZvImage color, int colorSpace);
ZV_TASK ZV_EXPORTS int zv_ipBayerToRgb(ZvImage bayer, ZvImage rgb, int bayerType);

ZV_TASK ZV_EXPORTS int zv_ipMedianBlur(ZvImage src, ZvImage dst, int size);
ZV_TASK ZV_EXPORTS int zv_ipMeanBlur(ZvImage src, ZvImage dst, int size);
ZV_TASK ZV_EXPORTS int zv_ipGaussBlur(ZvImage src, ZvImage dst, int size);
/*************************************************************
Description:    //图像双边滤波
Input:          //src 输入图像8U
Input:          //sigmaSpace 空间域滤波参数
Input:          //sigmaRange 数值域滤波参数
Output:         //dst 输出图像。
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_ipBilateralFilter(ZvImage src, ZvImage dst, double sigmaSpace, double sigmaRange);
ZV_TASK ZV_EXPORTS int zv_ipSobel(ZvImage src, ZvImage dst, int dx, int dy, int size);
ZV_TASK ZV_EXPORTS int zv_ipScharr(ZvImage src, ZvImage dst, int dx, int dy);
ZV_TASK ZV_EXPORTS int zv_ipLaplace(ZvImage src, ZvImage dst, int size);
ZV_TASK ZV_EXPORTS int zv_ipCanny(ZvImage img, ZvImage dst, double thresh1, double thresh2, int size);
ZV_TASK ZV_EXPORTS int zv_ipEqualizeHist(ZvImage src, ZvImage dst);

ZV_TASK ZV_EXPORTS int zv_ipDilate(ZvImage src, ZvImage dst, int seWidth, int seHeight);
ZV_TASK ZV_EXPORTS int zv_ipErode(ZvImage src, ZvImage dst, int seWidth, int seHeight);
ZV_TASK ZV_EXPORTS int zv_ipOpening(ZvImage src, ZvImage dst, int seWidth, int seHeight);
ZV_TASK ZV_EXPORTS int zv_ipClosing(ZvImage src, ZvImage dst, int seWidth, int seHeight);
//ZV_TASK ZV_EXPORTS int zv_ipGaborKernel(ZvImage kernel, int width, int height,
//    double sigma, double theta, double lambd, double gamma, double psi);
//ZV_TASK ZV_EXPORTS int zv_ipDerivKernel(ZvImage kernelX, ZvImage kernelY, int dX, int dY, int size);
//ZV_TASK ZV_EXPORTS int zv_ipDct(ZvImage src, ZvImage dst);
//ZV_TASK ZV_EXPORTS int zv_ipIdct(ZvImage src, ZvImage dst);
//ZV_TASK ZV_EXPORTS int zv_ipFilter(ZvImage src, ZvImage kernel, ZvImage dst,
//    int dstType, int anchorX, int anchorY, double delta, char * border);
//ZV_TASK ZV_EXPORTS int zv_ipSepFilter(ZvImage src, ZvImage kernelX, ZvImage kernelY, ZvImage dst,
//    int dstType, int anchorX, int anchorY, double delta, char *border);
//ZV_TASK ZV_EXPORTS int zv_ipFft(ZvImage src, ZvImage dstRe, ZvImage dstIm);
//ZV_TASK ZV_EXPORTS int zv_ipIfft(ZvImage srcRe, ZvImage srcIm, ZvImage dst);
//ZV_TASK ZV_EXPORTS int zv_ipPyramid(ZvImage src, ZvImage *dst, int level, char *border);
//ZV_TASK ZV_EXPORTS int zv_ipPyramidDown(ZvImage src, ZvImage dst, double factor, char *border);
//ZV_TASK ZV_EXPORTS int zv_ipPyramidUp(ZvImage src, ZvImage dst, double factor, char *border);
ZV_TASK ZV_EXPORTS int zv_ipMorphSe(ZvImage kernel, int shape, int sizeX, int sizeY, int anchorX, int anchorY);
ZV_TASK ZV_EXPORTS int zv_ipMorph(ZvImage src, ZvImage dst, ZvImage kernel,
    int op, int anchorX, int anchorY, int iter, char *border);
ZV_TASK ZV_EXPORTS int zv_ipLabel(ZvImage src, ZvImage label, int connectivity);
//ZV_TASK ZV_EXPORTS int zv_ipLabelStat(ZvImage src, ZvImage label, ZvImage stat,
//    ZvMatrix centroid, int connectivity, int labelType);

ZV_TASK ZV_EXPORTS int zv_ipThreshold(ZvImage src, ZvImage dst, double thresh0, double thresh1, bool isInv);
ZV_TASK ZV_EXPORTS int zv_ipAdpThreshold(ZvImage src, ZvImage thresh,
    ZvImage dst, double offset, bool isInv);
ZV_TASK ZV_EXPORTS int zv_ipAutoThreshold(ZvImage src, ZvImage dst, double *thresh);


//match - 单通道图像
ZV_TASK ZV_EXPORTS int zv_matchFastTempl(ZvImage img, ZvImage templ, ZV_UNFOLD(2) int *pos, int method);
ZV_TASK ZV_EXPORTS int zv_matchBestTempl(ZvImage img, ZvImage templ, double minScore,
    ZV_UNFOLD(3) double *mRst, bool isSubPix, int polar);
ZV_TASK ZV_EXPORTS int zv_matchMultiTempl(ZvImage img, ZvImage templ, ZvMatrix matches,
    double minScore, int nums, double minDist, bool isSubPix, int polar);

/*
**新添加的匹配接口====================================================================================================================================================
*/
ZV_TASK ZV_EXPORTS int zv_matchGrayScale(ZvImage img, ZvImage templ, int NumLevel, double AngleStart,
    double AngleExtent, double AngleStep, double *x, double *y, double MinScore);
ZV_TASK ZV_EXPORTS int zv_matchNccCreate(ZvModel mod, ZvImage templ, double angleStart, double angleExt, double angleStep, int numLevel);
ZV_TASK ZV_EXPORTS int zv_matchNccFind(ZvModel mod, ZvImage img, ZvMatrix matchs, int NumLevel, double minScore, double *x, double *y, double minDist, int isSubPix);
/*==================================================================================================================================================================*/

//meas - 单通道图像
ZV_CALL ZV_EXPORTS void zv_measGenRect(void * mr, double x, double y, double width, double height);
ZV_CALL ZV_EXPORTS void zv_measGenRect2(void *mr, double cx, double cy, double width,
    double height, double angle, int interp);
ZV_CALL ZV_EXPORTS void zv_measGenArc(void *mr, double cx, double cy, double r,
    double startA, double extentA, double annR, int interp);
ZV_TASK ZV_EXPORTS int zv_measProjection(ZvImage img, ZvMatrix proj, void *mr);
/*************************************************************
Description:    //测量点
Input:          //img 单通道图像
                //mr 测量区域
                //filterSize 高斯滤波参数，必须为奇数
                //thresh 阈值，超过的为测量结果
                //type 边缘极性：0-白黑、1-黑白、2-所有
                //select 边缘位置：0-第一点、1-最后点、2-最强点、3-所有点
Output:         //pts 测量的结果，n行3列double类型，每行一个点分别为x、y坐标和差分值
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_measPos(ZvImage img, ZvMatrix pts, void *mr, int filterSize,
    double thresh, int type, int select);
ZV_TASK ZV_EXPORTS int zv_measPairs(ZvImage img, ZvMatrix pairs, void *mr, int filterSize,
    double thresh, int type, int select);
ZV_CALL ZV_EXPORTS int zv_measGenLineMr(void *mr, double cx, double cy, double width,
    double height, double angle, int interp, int subNum, int subWidth);
ZV_CALL ZV_EXPORTS int zv_measGenCircleMr(void *mr, double cx, double cy, double r,
    double startA, double extentA, double annR, int interp, int subNum, int subWidth);
ZV_CALL ZV_EXPORTS void zv_measSetMrAdvParam(void *mr, int filterSize, double thresh, int type, int select);
ZV_CALL ZV_EXPORTS void zv_measGetMrAdvParam(void *mr, int *filterSize, double *thresh, int *type, int *select);
ZV_TASK ZV_EXPORTS int zv_measLine(ZvImage img, void *mr, ZV_UNFOLD(4) double *line, ZvMatrix pts);

/*************************************************************
Description:    //测量圆
Input:          //img 单通道图像
                //mr 测量区域
Output:         //circle 测量的结果，3元素double类型，分别为中心x、y和半径r
                //pts  拟合圆的样本点 
Return:         //任务状态码
*************************************************************/
ZV_TASK ZV_EXPORTS int zv_measCircle(ZvImage img, void *mr, ZV_UNFOLD(3) double *circle, ZvMatrix pts);

//feat - 单通道图像
ZV_TASK ZV_EXPORTS int zv_featHoughLine(ZvImage img, ZvMatrix lines, double rho,
    double theta, int thresh, double minLinelen, double maxLineGap);
ZV_TASK ZV_EXPORTS int zv_featHoughCircle(ZvImage img, ZvMatrix circles,
    double minDist, double param1, double param2, double minR, double maxR);


//tk
ZV_CALL ZV_EXPORTS void zv_tkGetSimilarityParam(ZvMatrix mat, double cx, double cy, double angle, double scale);
ZV_TASK ZV_EXPORTS int zv_tkGetRigid(ZvMatrix mat, double *from, double *to);
ZV_TASK ZV_EXPORTS int zv_tkGetRigidVector(ZvMatrix mat, double xFrom, double yFrom,
    double angleFrom, double xTo, double yTo, double angleTo);
ZV_TASK ZV_EXPORTS int zv_tkGetSimilarity(ZvMatrix mat, double *from, double *to);
ZV_TASK ZV_EXPORTS int zv_tkGetAffine(ZvMatrix mat, double *from, double *to);
ZV_TASK ZV_EXPORTS int zv_tkEstimateSimilarity(ZvMatrix from, ZvMatrix to, ZvMatrix mat,
    double thresh, double confidence, bool * isInliers);
ZV_TASK ZV_EXPORTS int zv_tkEstimateAffine(ZvMatrix from, ZvMatrix to, ZvMatrix mat,
    double thresh, double confidence, bool * isInliers);
ZV_TASK ZV_EXPORTS int zv_tkAffineTrans(ZvMatrix mat, double *from, double *to, int ptNum);
ZV_TASK ZV_EXPORTS int zv_tkGetProjective(ZvMatrix mat, double *from, double *to);
ZV_TASK ZV_EXPORTS int zv_tkProjectiveTrans2d(ZvMatrix mat, double *from, double *to, int num);
ZV_TASK ZV_EXPORTS int zv_tkProjectiveTrans3d(ZvMatrix mat, double *from, double *to, int num);

ZV_CALL ZV_EXPORTS double zv_tkDistancePP(double x1, double y1, double x2, double y2);
ZV_CALL ZV_EXPORTS double zv_tkDistancePL(double px, double py,
    double x1, double y1, double x2, double y2);
ZV_CALL ZV_EXPORTS double zv_tkDistancePS(double px, double py,
    double x1, double y1, double x2, double y2);
ZV_TASK ZV_EXPORTS int zv_tkDistanceContP(ZvContour cont, double px, double py, ZV_TRAN_OUT double * dist);
ZV_CALL ZV_EXPORTS void zv_tkRect2Vertex(double cx, double cy, double width, double height,
    double angle, double *pt);

ZV_CALL ZV_EXPORTS void zv_tkIntersectPL(double px, double py,
    double x1, double y1, double x2, double y2, ZV_UNFOLD(2) double *sect);
/*************************************************************
Description:    //计算直线交点
Input:          //l1x1 直线1参数
                //l1y1 直线1参数
                //l1x2 直线1参数
                //l1y2 直线1参数
                //l2x1 直线2参数
                //l2y1 直线2参数
                //l2x2 直线2参数
                //l2y2 直线2参数
Output:         //sect 交点坐标，依次为x、y
Return:         //直线是否相交，true - 相交，false - 平行或出错
*************************************************************/
ZV_CALL ZV_EXPORTS bool zv_tkIntersectLL(double l1x1, double l1y1, double l1x2, double l1y2,
    double l2x1, double l2y1, double l2x2, double l2y2, ZV_UNFOLD(2) double *sect);

ZV_CALL ZV_EXPORTS double zv_tkAngleLines(double line1X1, double line1Y1, double line1X2,
    double line1Y2, double line2X1, double line2Y1, double line2X2, double line2Y2);

ZV_CALL ZV_EXPORTS double zv_tkAngleLineX(double x1, double y1, double x2, double y2);
ZV_TASK ZV_EXPORTS int zv_tkFitLine2D(ZvMatrix pts, ZV_UNFOLD(4) double *line);
//ZV_TASK ZV_EXPORTS int zv_tkFitLine3D(ZvMatrix pts, ZV_UNFOLD(6) double *line);
ZV_TASK ZV_EXPORTS int zv_tkFitEllipse(ZvMatrix pts, ZV_UNFOLD(5) double *ellipse);
ZV_TASK ZV_EXPORTS int zv_tkIntersectRect2(ZvMatrix pts, double R1X, double R1Y, double R1W, double R1H,
    double R1Angle, double R2X, double R2Y, double R2W, double R2H, double R2Angle);
ZV_CALL ZV_EXPORTS void zv_tkLineToParam(double x1, double y1, double x2,
    double y2, ZV_UNFOLD(4) double *lineParam);
ZV_CALL ZV_EXPORTS void zv_tkLineFromParam(double cx, double cy, double angle,
    double len, ZV_UNFOLD(4) double *line);
ZV_TASK ZV_EXPORTS int zv_tkFitLineEx(ZvMatrix pts, double *line, int method, double reps, double aeps);
ZV_TASK ZV_EXPORTS int zv_tkFitEllipseEx(ZvMatrix pts, ZV_UNFOLD(5) double *ellipse, int method);
ZV_TASK ZV_EXPORTS int zv_tkFitPolyn(ZvMatrix pts, int order, double *param);


//dra模块，绘制图形和文字
ZV_CALL ZV_EXPORTS int zv_draColor(int r, int g, int b);
ZV_CALL ZV_EXPORTS int zv_draColorId(int id);

ZV_TASK ZV_EXPORTS int zv_draLine(ZvImage img, double x1, double y1, double x2, double y2, int color);
ZV_TASK ZV_EXPORTS int zv_draRect(ZvImage img, double x, double y, double w, double h, int color);
ZV_TASK ZV_EXPORTS int zv_draRect2(ZvImage img, double cx, double cy, double width, double height, double angle, int color);
ZV_TASK ZV_EXPORTS int zv_draCircle(ZvImage img, double cx, double cy, double r, int color);
ZV_TASK ZV_EXPORTS int zv_draEllipse(ZvImage img, double cx, double cy, double xR, double yR, double angle, int color);
ZV_TASK ZV_EXPORTS int zv_draEllipseArc(ZvImage img, double cx, double cy, double xR, double yR, double angle,
    double angleStart, double angleEnd, int color);
ZV_TASK ZV_EXPORTS int zv_draArrow(ZvImage img, double x1, double y1, double x2, double y2, int color, int size);
ZV_TASK ZV_EXPORTS int zv_draPolygon(ZvImage img, ZvMatrix pts, bool isClosed, int color);
ZV_TASK ZV_EXPORTS int zv_draContour(ZvImage img, ZvContour cont, int color);
ZV_TASK ZV_EXPORTS int zv_draMarker(ZvImage img, double x, double y, int type, int size, int color);
ZV_TASK ZV_EXPORTS int zv_draText(ZvImage img, char * text, double x, double y, double scale, int color);
ZV_TASK ZV_EXPORTS int zv_draMask(ZvImage img, ZvImage mask);
ZV_TASK ZV_EXPORTS int zv_draMeasurer(ZvImage img, void *mr, int color, int subColor);
#ifdef ZV_WITH_TEST
////test 测试用到的关键函数，更改或优化可能导致测试失败
ZV_EXPORTS double zv_testNorm(ZvMatrix mat, int normType);
ZV_EXPORTS int zv_testAbsDiff(ZvObject _src1, ZvObject _src2, ZvObject _dst);
ZV_EXPORTS int zv_testFillRandU(ZvObject obj, double lower, double upper);
ZV_EXPORTS int zv_testFillRandN(ZvObject obj, double mean, double stddev);
ZV_EXPORTS int zv_testRandU();
ZV_EXPORTS double zv_testRandUD();
ZV_EXPORTS double zv_testRandN();

#endif
#ifdef __cplusplus
}
#endif

#endif
