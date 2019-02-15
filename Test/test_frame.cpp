#include "test_frame.h"
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdarg.h>
#include <io.h>
#include <QDir>

using namespace std;

//静态的代表整个生命周期中都是有效的
static char *s_testSrcImgName[TEST_IMAGE_COUNT] =
{
    "0-RGB.jpg", "1-RGBA.jpg", "2.bmp", "3.bmp", "4-RGB.jpg", "5-GRAY.jpg", "6-GRAY.png", "matchPicture/2.bmp", "matchPicture/TemplImg.bmp","Temp/2.bmp", //"10.png",
};

TestSet g_testAll[TEST_SET_MAX] = { 0 };

//输入图像信息和缓存区 输出和中间图像信息及缓存区
TestImageInfo g_testImgInfo[TEST_IMAGE_COUNT + TEST_IMAGE_COUNT] = { 0 };
TestImageInfo g_testStdOutImgInfo[STD_OUT_IMG_COUNT] = { 0 };

//错误结果缓存
vector<TestInfo> g_testNgInfo;

TestInfo * test_frm_getNgInfo(int id)
{
    if (id >= g_testNgInfo.size())
    {
        return NULL;
    }
    return &g_testNgInfo[id];
}

int test_frm_appendNgInfo(TestInfo * info)
{
    if (NULL != info)
    {
        g_testNgInfo.push_back(*info);
        return g_testNgInfo.size()-1;
    }
    return -1;
}

void test_frm_clearNgInfo()
{
    for (int i = 0; i < g_testNgInfo.size(); i++)
    {
        for (int k = 0; k < TEST_IMAGE_COUNT; k++)
        {
            zv_modImgRelease(&g_testNgInfo[i].imgOut[k]);
        }
    }
    g_testNgInfo.clear();
}

ZvImage test_frm_getImgSrc(int id)
{
    if (id >= TEST_IMAGE_LOAD_COUNT)
    {
        return NULL;
    }

    g_testImgInfo[id].isParam = true;
    return g_testImgInfo[id].img;
}

ZvImage test_frm_loadImgSrc(char *name)
{
    string fileName(name);
    if (fileName.empty())
    {
        return NULL;
    }

    for (int i = TEST_IMAGE_LOAD_COUNT; i < TEST_IMAGE_COUNT; i++)
    {
        if (!g_testImgInfo[i].isUse)
        {
            snprintf(g_testImgInfo[i].path, sizeof(g_testImgInfo[i].path), "%s%s", TEST_DATA_PATH, name);
            zv_fileReadImage(g_testImgInfo[i].img, g_testImgInfo[i].path, 0);
            if (0 != g_zv_errLastError)
            {
                g_zv_errLastError = 0;
                return NULL;
            }
            g_testImgInfo[i].width = zv_imgWidth(g_testImgInfo[i].img);
            g_testImgInfo[i].height = zv_imgHeight(g_testImgInfo[i].img);
            g_testImgInfo[i].channels = zv_imgChannels(g_testImgInfo[i].img);
            return g_testImgInfo[i].img;
        }
    }

    return NULL;
}

ZvImage test_frm_getImgDst(bool isOut)
{
    for (int i = 0; i < TEST_IMAGE_COUNT; i++)
    {
        if (!g_testImgInfo[DST_IMAGE_OFFSET + i].isUse)
        {
            g_testImgInfo[DST_IMAGE_OFFSET + i].isUse = true;
            g_testImgInfo[DST_IMAGE_OFFSET + i].isParam = isOut;
            return g_testImgInfo[DST_IMAGE_OFFSET + i].img;
        }
    }

    return NULL;
}

ZvImage test_frm_loadImgStd(char *_fileName)
{
    string fileName(_fileName);
    if (fileName.empty())
    {
        return NULL;
    }

    for (int i = 0; i < STD_OUT_IMG_COUNT; i++)
    {
        if (!g_testStdOutImgInfo[i].isUse)
        {
            snprintf(g_testStdOutImgInfo[i].path, sizeof(g_testStdOutImgInfo[i].path), "%s%s", TEST_DATA_PATH, _fileName);
            zv_fileReadImage(g_testStdOutImgInfo[i].img, g_testStdOutImgInfo[i].path, 0);
            if (0 != g_zv_errLastError)
            {
                g_zv_errLastError = 0;
                return NULL;
            }
            g_testStdOutImgInfo[i].width = zv_imgWidth(g_testStdOutImgInfo[i].img);
            g_testStdOutImgInfo[i].height = zv_imgHeight(g_testStdOutImgInfo[i].img);
            g_testStdOutImgInfo[i].channels = zv_imgChannels(g_testStdOutImgInfo[i].img);
            return g_testStdOutImgInfo[i].img;
        }
    }

    return NULL;
}

bool test_frm_chkDstImgInfo(int id)
{
    if (DST_IMAGE_OFFSET + TEST_IMAGE_COUNT <= id || DST_IMAGE_OFFSET > id)
    {
        return false;
    }

    if (!g_testImgInfo[id].isUse)
    {
        return false;
    }

    if (NULL == g_testImgInfo[id].img)
    {
        return false;
    }

    g_testImgInfo[id].width = zv_imgWidth(g_testImgInfo[id].img);
    g_testImgInfo[id].height = zv_imgHeight(g_testImgInfo[id].img);
    g_testImgInfo[id].channels = zv_imgChannels(g_testImgInfo[id].img);

    return true;
}

//在测试集set中添加函数func，函数界面显示信息为disp
void test_frm_setSetDisp(int set, char *name)
{
    if (set >= TEST_SET_MAX)
        return;
    int len = string(name).length();
    len = std::min(len, (int)(sizeof(g_testAll[set].disp) - 1));
    memset(g_testAll[set].disp, 0, sizeof(g_testAll[set].disp));
    strncpy(g_testAll[set].disp, name, len);
}

////REG_FUNCTION(TEST_TEST, "版本打印", testCBase);    TEST_TEST是枚举变量值 = 0；
//#define REG_FUNCTION(set, disp, fun) test_frm_addFunc((set), (disp), (test_##fun), ("test_"#fun))  
//实际上掉用的函数是：test_frm_addFunc(0， "版本打印", test_testCBase, "test_testCBase");
//TestSet g_testAll[10] = { 0 };
void test_frm_addFunc(int set, char *disp, TestFuncPtr func, char *name)
{
    if (set >= TEST_SET_MAX)
    {
        return;
    }
    TestSet * p = &g_testAll[set];   //虽然定义了结构体数组，但是没有对每个数组成员进行赋值操作;
   
    // if语句里面的代码还不算很懂 ， nounderstand!
    if (p->size >= p->capacity)
    {
        TestFunction * f = p->funcList;
        p->funcList = (TestFunction*)malloc(sizeof(TestFunction) * p->capacity * 2);
        if (NULL == p->funcList)
        {
            p->funcList = f;
            return;
        }
        p->capacity *= 2;
        memcpy(p->funcList, f, sizeof(TestFunction)*p->size);

        if (sizeof(p->_fList) / sizeof(p->_fList[0]) != p->capacity)
        {
            free(f);
        }
    }
    
    //给TestFunction结构体中变量进行赋值；
    strncpy(p->funcList[p->size].disp, disp, sizeof(p->funcList[p->size].disp)-1);
    strncpy(p->funcList[p->size].name, name, sizeof(p->funcList[p->size].name)-1);
    p->funcList[p->size].func = func;

    p->size++;
}

//test_frm_log(p, "进入函数：%s\n", ZV_FUNC__)
void test_frm_log(TestLog *p, char * format, ...)
{
    if (!p)
    {
        return;
    }

    int count = TEST_INFO_BUF_LEN - p->cur;
    if (count < 1)
    {
        return;
    }
    va_list args;
    va_start(args, format);
    int num = vsnprintf_s(p->buf + p->cur, count, count-1, format, args);
    va_end(args);
    if (num <= 0)
    {
        return;
    }

    string timestamp = string(test_frm_currPath()) + "log.txt";
    FILE * logFile = fopen(timestamp.c_str(), "a");
    if (logFile)
    {
        fwrite(p->buf + p->cur, num, 1, logFile);
        fflush(logFile);
        fclose(logFile);
    }
    p->cur += num;
}

int test_frm_clearCurInfo()   /// 清除当前的显示信息
{
    for (int i = 0; i < TEST_IMAGE_COUNT; i++)
    {
        g_testImgInfo[i].isParam = false;
        if (i >= TEST_IMAGE_LOAD_COUNT) g_testImgInfo[i].isUse = false;
        g_testImgInfo[DST_IMAGE_OFFSET + i].isUse = false;
        g_testImgInfo[DST_IMAGE_OFFSET + i].isParam = false;
    }
    for (int i = 0; i < STD_OUT_IMG_COUNT; i++)
    {
        g_testStdOutImgInfo[i].isUse = false;
    }
    return 0;
}

//测试成功返回0；其它失败返回错误缓存索引
int test_frm_rstSet(TestLog *p, bool isPass)
{
    test_frm_log(p, "测试结果：%s\n", isPass ? "通过" : "失败");
    test_frm_log(p, "离开函数\n");

    int ngId = 0;
    if (!isPass)
    {
        TestInfo info;
        info.tLog = *p;
        int cnt = 0;
        for (int i = 0; i < TEST_IMAGE_COUNT; i++)
        {
            info.isSrcImgUse[i] = g_testImgInfo[i].isParam;
            info.isDstImgOut[i] = g_testImgInfo[DST_IMAGE_OFFSET + i].isParam;
            if (g_testImgInfo[DST_IMAGE_OFFSET + i].isUse)
            {
                info.imgOut[i] = zv_modImgCreate();
                zv_imgCopy(g_testImgInfo[DST_IMAGE_OFFSET + i].img, info.imgOut[i]);
                ++cnt;
            }
            else
            {
                info.imgOut[i] = NULL;
            }
        }
        info.dstImgNum = cnt;
        ngId = test_frm_appendNgInfo(&info);
        test_frm_log(p, "数据缓存：%d\n", ngId);
    }
    test_frm_log(p, "\n");

    return isPass ? 0 : ngId + 1;
}

int test_frm_funcTest(TestLog *p, int set, int func)
{
    return test_frm_rstSet(p, g_testAll[set].funcList[func].func(p));
}

void test_frm_start()
{
    test_frm_clearNgInfo();
}

int test_frm_init()
{
    zv_modInit(true);
    test_frm_createPath(TEST_DATA_PATH"Temp/");   //创建路径..//Data//Templ//

    //缓存测试图像
    for (int i = 0; i < TEST_IMAGE_COUNT; i++)
    {
        g_testImgInfo[i].img = zv_modImgCreate();     //Mat *img = new Mat();
        if (i >= TEST_IMAGE_LOAD_COUNT)
        {
            g_testImgInfo[i].isUse = false;
            continue;
        }
        /*
        int snprintf(char *str, size_t size, const char *format, ...);
        (1) 如果格式化后的字符串长度 < size，则将此字符串全部复制到str中，并给其后添加一个字符串结束符('\0')；
        (2) 如果格式化后的字符串长度 >= size，则只将其中的(size - 1)个字符复制到str中，并给其后添加一个字符串结束符('\0')，返回值为欲写入的字符串长度。
        */
        snprintf(g_testImgInfo[i].path, sizeof(g_testImgInfo[i].path), "%s%s", TEST_DATA_PATH, s_testSrcImgName[i]);
        zv_fileReadImage(g_testImgInfo[i].img, g_testImgInfo[i].path, 0);   //从目录下读取文件并保存到 g_testImgInfo[i].img 文件中去；
        if (0 != g_zv_errLastError)
        {
            return TEST_DATA_PATH_ERR-i;
        }
        g_testImgInfo[i].width = zv_imgWidth(g_testImgInfo[i].img);
        g_testImgInfo[i].height = zv_imgHeight(g_testImgInfo[i].img);
        g_testImgInfo[i].channels = zv_imgChannels(g_testImgInfo[i].img);
        g_testImgInfo[i].isParam = false;
        g_testImgInfo[i].isUse = true;
        g_testImgInfo[DST_IMAGE_OFFSET + i].img = zv_modImgCreate();    // 创建输出图像缓存
    }

    for (int i = 0; i < STD_OUT_IMG_COUNT; i++)
    {
        g_testStdOutImgInfo[i].img = zv_modImgCreate();         //创建输出图像的内存空间
    }

    for (int i = 0; i < TEST_SET_MAX; i++)
    {
        g_testAll[i].funcList = &g_testAll[i]._fList[0];
        g_testAll[i].capacity = sizeof(g_testAll[i]._fList) / sizeof(g_testAll[i]._fList[0]);   //保存测试函数总的容量；
    }

    testRegisterC();       // C接口兼容性测试
    testRegisterCPP();
    testRegisterPerf();
    testRegisterFlow();

    return 0;
}

void test_frm_exit()
{
    for (int i = 0; i < TEST_IMAGE_COUNT + DST_IMAGE_OFFSET; i++)
    {
        zv_modImgRelease(&g_testImgInfo[i].img);
    }
    zv_modExit();                                      // zv 模块中的资源释放
}

char * test_frm_currPath()
{
    static std::string path(QDir::currentPath().toStdString());
    return (char *)path.c_str();
}

bool test_frm_createPath(const char * path)
{
    QDir tmpDir;
    return tmpDir.mkpath(QString(path));
}

char * test_frm_dataTypeStr(ZvImage img)
{
    static char * str[] = { "Undef", "8U", "16U", "32S", "64F" };
    int type = zv_imgDataType(img);
    return str[type];
}