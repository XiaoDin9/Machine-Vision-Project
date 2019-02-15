#include "zv_private.h"
#include "system/zv_system.h"

#include <sys/timeb.h>

#if (defined _WIN32 || defined WINCE || defined __CYGWIN__)
#include <windows.h>
#else
#include <sys/time.h>
#endif

string zv_sys_dateTimeString(bool withUs)
{
    char buf[32] = { 0 }; //2018-07-04 18:21:33
#if (defined _WIN32 || defined WINCE || defined __CYGWIN__)
    SYSTEMTIME cTime;
    GetLocalTime(&cTime);
    int num = snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
        cTime.wYear, cTime.wMonth, cTime.wDay, cTime.wHour, cTime.wMinute, cTime.wSecond);
    if (withUs)
    {
        snprintf(buf+num, sizeof(buf)-num, ".%06d", (int)cTime.wMilliseconds * 1000);
    }
#else
    struct timeval cTime;
    //struct timezone tz;
    gettimeofday(&cTime, NULL);
    time_t tt = cTime.tv_sec;
    tm *temp = localtime(&tt);
    int num = snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d", temp->tm_year + 1900,
        temp->tm_mon + 1, temp->tm_mday, temp->tm_hour, temp->tm_min, temp->tm_sec);
    if (withUs)
    {
        snprintf(buf + num, sizeof(buf) - num, ".%06d", (int)cTime.tv_usec);
    }
#endif
    return string(buf);
}

void zv_sys_platform(string info)
{
#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
    //define something for Windows (64-bit only)
    info = "Win_X64";
#else
    //define something for Windows (32-bit only)
    info = "Win_X86";
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
    // iOS Simulator
    info = "iOS_Simulator";
#elif TARGET_OS_IPHONE
    // iOS device
    info = "iOS";
#elif TARGET_OS_MAC
    // Other kinds of Mac OS
    info = "MacOS";
#else
#   error "Unknown Apple platform"
#endif
#elif __ANDROID__
    // android
    info = "Android";
#elif __linux__
    info = "Linux";
#elif __unix__ // all unices not caught above
    // Unix
    info = "Unix";
#elif defined(_POSIX_VERSION)
    // POSIX
    info = "POSIX";
#else
#   error "Unknown compiler"
    //info = "Unknown";
#endif
}

void zv_sys_sleep(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#endif
}

vector<string> zv_sys_stringSplit(string& str, char delimiter, bool allowEmpty)
{
    vector<string> strSplit;

    size_t pos = str.find(delimiter);
    size_t start = 0;
    while (string::npos != pos)
    {
        string item = str.substr(start, pos - start);
        if (!item.empty() || allowEmpty)
        {
            strSplit.push_back(item);
        }

        start = pos + 1;
        pos = str.find(delimiter, start);
    }

    string item(str.substr(start));
    if (!item.empty() || allowEmpty)
    {
        strSplit.push_back(item);
    }

    return strSplit;
}