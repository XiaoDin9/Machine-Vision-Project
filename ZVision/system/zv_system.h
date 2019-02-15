#ifndef ZV_SYSTEM_H
#define ZV_SYSTEM_H

#define ZV_SYS_P_TEST           "Test"
#define ZV_SYS_P_LINE_TYPE      "LineType"
#define ZV_SYS_P_GRAB_TIMEOUT   "GrabTimeout"
#define ZV_SYS_P_ERROR_LEVEL    "ErrorLevel"
#define ZV_SYS_P_OPT_LEVEL      "OptLevel"

#ifdef __cplusplus
#define ZV_ERR_RUN(func, ...) do { int runCode = ZV_ERR_G_UNDEF; \
    try { runCode = (func); } catch(cv::Exception& e){ runCode = zv_adp_cvStatus(e.code); } \
    catch(std::exception&) { runCode = ZV_ERR_G_STD_EXCEP; } \
    catch(...){ runCode = ZV_ERR_G_CPP_EXCEP; } \
    g_zv_errStatus = runCode; \
    if (ZV_ST_OK != runCode){ \
        zv_err_checkStatus(runCode, __FILE__, ZV_FUNC__, __LINE__, ##__VA_ARGS__); \
    }} while(0)
#else
#define ZV_ERR_RUN(func) do { int runCode = ZV_ERR_G_UNDEF; \
    try { runCode = (func); } catch(cv::Exception& e){ runCode = zv_adp_cvStatus(e.code); } \
    catch(std::exception&) { runCode = ZV_ERR_G_STD_EXCEP; } \
    catch(...){ runCode = ZV_ERR_G_CPP_EXCEP; } \
    g_zv_errStatus = runCode; \
    if (ZV_ST_OK != runCode){ \
        zv_err_checkStatus(runCode, __FILE__, ZV_FUNC__, __LINE__, ""); \
    }} while(0)
#endif

vector<string> zv_sys_stringSplit(string& str, char delimiter, bool allowEmpty = false);
string zv_sys_dateTimeString(bool withUs);

#ifdef __cplusplus
extern "C"{
#endif
   
//error
extern ZV_EXPORTS int g_zv_errStatus;
extern ZV_EXPORTS int g_zv_errLastError;
extern ZV_EXPORTS char g_zv_errLastErrorMsg[];

extern ZV_EXPORTS int g_zv_sysIsDrawFill;
extern ZV_EXPORTS int g_zv_sysLineWidth;

char *zv_err_statusStr(int status);
void zv_err_checkStatus(int status, char *file, char *func, int line, char * format ZV_CPP_DEF(NULL), ...);
void zv_sys_platform(string info);
void zv_sys_sleep(int ms);

int zv_sys_getParamInt(char *name, int *value);
int zv_sys_setParamInt(char *name, int value);
int zv_sys_getParamDouble(char *name, double *value);
int zv_sys_setParamDouble(char *name, double value);
int zv_sys_getParamString(char *name, char *value, int maxValLen);
int zv_sys_setParamString(char *name, char *value);

inline int64 zv_sys_getTickCount()
{
    return cv::getTickCount();
}

inline double zv_sys_getTickFreq()
{
    return cv::getTickFrequency();
}

inline double zv_sys_getTimeUs()
{
    return zv_sys_getTickCount() * 1000000.0 / zv_sys_getTickFreq();
}

inline double zv_sys_getTimeMs()
{
    return zv_sys_getTickCount() * 1000.0 / zv_sys_getTickFreq();
}


#ifdef __cplusplus
}
#endif

#endif