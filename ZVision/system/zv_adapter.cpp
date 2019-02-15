#include "zv_private.h"
#include "zv_adapter.h"

using namespace cv;

static int s_zv_adp_reserve = 0;
int * g_zv_adp_notNull = &s_zv_adp_reserve;

int g_zv_adp_interp[ZV_INTERP_MAX] = {0, 1, 2, 4};

int g_zv_adp_depthToCV[] = {CV_8U, CV_16U, CV_32S, CV_64F };
int g_zv_adp_depthFromCV[] = { ZV_PIXEL_8U, ZV_PIXEL_UNDEF, ZV_PIXEL_16U, ZV_PIXEL_UNDEF, ZV_PIXEL_32S, ZV_PIXEL_UNDEF, ZV_PIXEL_64F, ZV_PIXEL_UNDEF };

int zv_adp_cvErrorCallback(int status, const char* func_name, const char* err_msg,
    const char* file_name, int line, void* userdata)
{
    return 0;
}

int zv_adp_cvStatus(int status)
{
    switch (status)
    {
    case CV_StsOk:                  return ZV_ST_OK;
    case CV_StsInternal:            return ZV_ERR_G_LIB_RUN;
    case CV_StsNoMem:               return ZV_ERR_MEM_ALLOC;
    case CV_StsBadArg:              return ZV_ERR_FA_TYPE;
    case CV_HeaderIsNull:           return ZV_ERR_F_FORMAT;
    case CV_BadDataPtr:             return ZV_ERR_M_EMPTY;
    case CV_BadStep:                return ZV_ERR_M_DATA_FORMAT;
    case CV_BadNumChannels:         return ZV_ERR_I_CN;
    case CV_BadNumChannel1U:        return ZV_ERR_I_ONLY_CN1;
    case CV_BadDepth:               return ZV_ERR_I_DEPTH;
    case CV_BadOrder:               return ZV_ERR_M_DIM;
    case CV_BadAlign:               return ZV_ERR_I_ALIGN;
    case CV_BadCOI:                 return ZV_ERR_G_NOT_SUPPORT;
    case CV_BadROISize:             return ZV_ERR_M_ROI;
    case CV_StsNullPtr:             return ZV_ERR_G_NULL_PTR;
    case CV_StsVecLengthErr:        return ZV_ERR_G_VEC_SIZE;
    case CV_StsFilterStructContentErr:  return ZV_ERR_FT_STRUCT;
    case CV_StsFilterOffsetErr:     return ZV_ERR_FT_ANCHOR;
    case CV_BadImageSize:
    case CV_StsBadSize:             return ZV_ERR_M_SIZE_INVALID;
    case CV_StsDivByZero:           return ZV_ERR_G_DIV_ZERO;
    case CV_StsObjectNotFound:      return ZV_ERR_G_OBJ_NOT_EXIST;
    case CV_StsUnmatchedFormats:    return ZV_ERR_M_TYPE_UNMATCH;
    case CV_StsBadFlag:             return ZV_ERR_FA_RANGE;
    case CV_StsBadPoint:            return ZV_ERR_FA_TYPE;
    case CV_StsUnmatchedSizes:      return ZV_ERR_M_SIZE_UNMATCH;
    case CV_StsUnsupportedFormat:   return ZV_ERR_I_DEPTH;
    case CV_StsOutOfRange:          return ZV_ERR_FA_RANGE;
    case CV_StsParseError:          return ZV_ERR_F_FORMAT;
    case CV_StsNotImplemented:      return ZV_ERR_G_UNFINISHED;
    case CV_StsBadMemBlock:         return ZV_ERR_MEM_CORRUPTED;
    case CV_StsAssert:              return ZV_ERR_G_LIB_ASSERT;

    case CV_GpuNotSupported:
    case CV_GpuApiCallError:
        return ZV_ERR_G_NSP_CUDA;
    case CV_OpenGlApiCallError:
    case CV_OpenGlNotSupported:
        return ZV_ERR_G_NSP_GL;
    case CV_OpenCLApiCallError:
    case CV_OpenCLDoubleNotSupported:
    case CV_OpenCLNoAMDBlasFft:
    case CV_OpenCLInitError:
        return ZV_ERR_G_NSP_CL;
    default:
        return ZV_ERR_G_UNDEF;
    }
    return ZV_ERR_G_UNDEF;
}

void zv_adp_borderInfo(string border, int &borderType, double &borderValue)
{
    if ("elem_mirror" == border)
    {
        borderType = BORDER_REFLECT_101;
    }
    else if ("bord_mirror" == border)
    {
        borderType = BORDER_REFLECT;
    }
    else if ("continue" == border)
    {
        borderType = BORDER_REPLICATE;
    }
    else if ("wrap" == border)
    {
        borderType = BORDER_WRAP;
    }
    else
    {
        borderType = BORDER_CONSTANT;
    }
    borderValue = atof(border.c_str());
}
